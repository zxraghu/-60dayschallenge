//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2011 - 2017 by Robert Bosch GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//     Projectname: NRCS2
//  Target systems: US
//       Compilers: ARM
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//        Name: Oliver Brösamle
//  Department: CC-DA/ESI4
//=============================================================================
/// @file  iwd_partial_response_interface.cpp
//=============================================================================

#include "iwd/inc/iwd_partial_response_interface.hpp"

extern "C"
{
    #include "Os.h"
}

namespace iwd
{
    //---------------------------------------------------------------------
    /// Lower taks activation bound for Task_C0_Task_10ms
    /// The time between getting the challenge and sending the response is 15ms.
    /// So the activation needs to be there at least once.
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t TASK_ACTIVATION_COUNTER_LOWER_BOUND  = 1U;

    //---------------------------------------------------------------------
    /// Upper taks activation bound for Task_C0_Task_10ms
    /// The time between getting the challenge and sending the response is 15ms.
    /// So the activation is done at maximum twice.
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t TASK_ACTIVATION_COUNTER_UPPER_BOUND  = 2U;

    //---------------------------------------------------------------------
    /// Uint32 mask to get only the last byte
    //---------------------------------------------------------------------
    constexpr vfc::uint32_t LAST_BYTE_MASK                      = 0x0000000FU; 

    //---------------------------------------------------------------------
    /// Number of different challenges
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t NUMBER_OF_CHALLENGES                 = 16U;

    //---------------------------------------------------------------------
    /// Challenge dependent correction values
    /// These values need to be adapted if a component is added or removed.
    //---------------------------------------------------------------------
    const vfc::uint32_t CORRECTION_VALUES[NUMBER_OF_CHALLENGES] =
    {
        0xA7756CBDU,
        0xF92B32E1U,
        0xD3459889U,
        0x8D1BC6C9U,
        0x69BB1A0BU,
        0x37E564B7U,
        0x9DB32EFFU,
        0xC3CD1087U,
        0x3220F968U,
        0x4D9E8754U,
        0x05D0CD1CU,
        0x39AF736CU,
        0xFB6DBFAEU,
        0x8351C012U,
        0xCB19885AU,
        0x7769B422U
    };

    CIwdPartialResponseInterface& CIwdPartialResponseInterface::instance()
    {
        static CIwdPartialResponseInterface iwdPartialResponseInterface;
        return iwdPartialResponseInterface;
    }

    void CIwdPartialResponseInterface::receiveChallenge(const vfc::uint32_t f_challenge)
    {
        // set new challenge
        m_challenge = f_challenge;

        // reset partial responses
        for(auto& partialResponse : m_partialResponses)
        {
            partialResponse = 0U;
        }

        // reset error states
        for(auto& errorStateOfCycle : m_errorStateOfCycle)
        {
            errorStateOfCycle.write(false);
        }

        // reset task activation counter
        m_taskActivationCounter = 0U;
    }

    
    void CIwdPartialResponseInterface::setPartialResponse(const vfc::uint8_t f_componentIndex, const vfc::uint32_t f_signature)
    {
        // check if component index is in range
        if(m_partialResponses.size() > f_componentIndex)
        {  
            // check if partial response is set the first time
            if(0U == m_partialResponses[f_componentIndex])
            {
                // partial response gets set the first time in cycle
                m_partialResponses[f_componentIndex] = f_signature + m_challenge;
            }
            else 
            {
                // partial response gets set the second time in the cycle, responses should be equal
                if(m_partialResponses[f_componentIndex] != (f_signature + m_challenge))
                {
                    m_errorStateOfCycle[f_componentIndex].write(true);
                }
            }

            // check if monitoring was already executed for the current activation
            if(m_monitoringExecutedSuccessfull[f_componentIndex])
            {
                // if the monitoring was already executed without another activation this is an error
                m_errorStateOfCycle[f_componentIndex].write(true);
            }

            // monitoring was executed successfully
            m_monitoringExecutedSuccessfull[f_componentIndex] = true;
        }
        else
        {
            // component index out of range, we are not trustworthy anymore => no healing from this
            m_generalErrorOccured = true;
        }
    }

    vfc::uint32_t CIwdPartialResponseInterface::getCombinedResponse()
    {
        vfc::uint32_t combinedResponse = 0U;

        // if the task activation count is out of range or a general error occured the combined response is zero
        if( m_taskActivationCounter < TASK_ACTIVATION_COUNTER_LOWER_BOUND   || 
            TASK_ACTIVATION_COUNTER_UPPER_BOUND < m_taskActivationCounter   ||
            m_generalErrorOccured)
        {
            // return combined response 0
        }
        else
        {    
            // xor the partial responses if there was no error in last cycle
            for(PartialResponseArray::size_type i = 0; i < m_partialResponses.size(); ++i)
            {
                // if no errors occurred and the bit inverse storage is still matching, we can take the partial response
                if(!m_errorStateOfCycle[i].read() && m_errorStateOfCycle[i].doMatch())
                {
                    combinedResponse ^= m_partialResponses[i];
                }
                else
                {
                    // XOR with zero; can be omitted
                }
            }

            // xor challenge dependent correction value
            combinedResponse ^= getCorrectionValue(m_challenge);   
        }

        return combinedResponse;
    }

    void CIwdPartialResponseInterface::taskActivated(const vfc::int32_t f_taskIndex)
    {
        // monitorings are executed in 10ms task => keep only track of 10ms task activation
        if(Task_C0_Task_10ms == OS_INDEX_TO_TASKTYPE(f_taskIndex))
        {
            // increment task activation counter
            ++m_taskActivationCounter;

            // run through all monitorings
            for(BoolArray::size_type i = 0; i < m_monitoringExecutedSuccessfull.size(); ++i)
            {
                // if the monitoring was not successfully executed since last activation, this is an error
                if(!m_monitoringExecutedSuccessfull[i])
                {
                    m_errorStateOfCycle[i].write(true);
                }

                // set successfull execution to false
                m_monitoringExecutedSuccessfull[i] = false;
            }
        }
    }

    vfc::uint32_t CIwdPartialResponseInterface::getCorrectionValue(const vfc::uint32_t f_challenge) const
    {
        // the last byte of the challenges are the numbers from 0 to 15 (each challenge has its own number)
        // this can be used to get the according correction value
        return CORRECTION_VALUES[LAST_BYTE_MASK & f_challenge];
    }

    CIwdPartialResponseInterface::CIwdPartialResponseInterface() :
        m_partialResponses(),
        m_monitoringExecutedSuccessfull(),
        m_errorStateOfCycle(),
        m_taskActivationCounter(0U),
        m_challenge(0U),
        m_generalErrorOccured(false)
    {
    }

}

//=============================================================================
