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
//       Compilers: 
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//        Name: Oliver Brösamle
//  Department: CC-DA/ESI4
//=============================================================================
/// @file  iwd_partial_response_interface.hpp
//=============================================================================

#ifndef IWD_PARTIAL_RESPONSE_INTERFACE_HPP_INCLUDED
#define IWD_PARTIAL_RESPONSE_INTERFACE_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp"
#include "vfc/inc/container/vfc_carray.hpp"

#include "fusa_picfreeze_mon/inc/bit_inverse_data_storage.hpp"

namespace iwd 
{
    //---------------------------------------------------------------------
    /// Number of components monitored by this partial response interface
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t NUMBER_MONITORED_COMPONENTS      = 1U;

    //---------------------------------------------------------------------
    /// Index for the picture freeze component
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t PICFREEZE_INDEX                  = 0U;

    //---------------------------------------------------------------------
    /// Index for the system monitoring component
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t SYSMON_INDEX                     = 1U;

    //---------------------------------------------------------------------
    /// Index for the task monitoring component
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t TASKMON_INDEX                    = 2U;

    //---------------------------------------------------------------------
    /// Index for the fpga monitoring component
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t FPGAMON_INDEX                    = 3U;

    //---------------------------------------------------------------------
    /// Index for the clock monitoring component
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t CLOCKMON_INDEX                   = 4U;

    //---------------------------------------------------------------------
    /// Partial response interface for the intelligent watchdog
    /// Used by the monitored components listed above
    //---------------------------------------------------------------------
    class CIwdPartialResponseInterface
    {
        public:
            //---------------------------------------------------------------------
            /// Get the singleton instance of the partial response interface
            //---------------------------------------------------------------------
            static CIwdPartialResponseInterface& instance();

            //---------------------------------------------------------------------
            /// Receive a new challenge
            /// Called at every reception of a challenge.
            /// Resets partial responses, errors of last cycle, task activation counter.
            /// Sets the challenge for the next partial responses.
            /// @param f_challenge is the challenge for the next cycle
            //---------------------------------------------------------------------
            void receiveChallenge(const vfc::uint32_t f_challenge);
            
            //---------------------------------------------------------------------
            /// Set the partial response for the given index
            /// This function should be called at the end of the monitored runnable
            /// if no error occured.
            /// @param f_componentIndex specifies the index for which the partial
            /// response should be set. Indices are defined in the partial response
            /// interface file.
            /// @param f_signature is the signature of the monitoring component. The
            /// signature shall be kept in the monitoring component and not be stored
            /// by the partial response interface.
            //---------------------------------------------------------------------
            void setPartialResponse(const vfc::uint8_t f_componentIndex, const vfc::uint32_t f_signature);

            //---------------------------------------------------------------------
            /// Get the combined response of all partial answers
            /// This function calculates the overall response by combining the
            /// partial responses and the challenge dependent correction value.
            /// @return calculated combined response
            //---------------------------------------------------------------------
            vfc::uint32_t getCombinedResponse();

            //---------------------------------------------------------------------
            /// The task with the given task index was activated.
            /// This is called by the task activation callback of the OS. This is
            /// important to keep track of activation of the task and successfull
            /// execution of the monitorings. For the current monitorings only the
            /// task Task_C0_Task_10ms is important, for all other activations no
            /// action is taken.
            //---------------------------------------------------------------------
            void taskActivated(const vfc::int32_t f_taskIndex);

        private:
            //---------------------------------------------------------------------
            /// Array type for the partial responses
            //---------------------------------------------------------------------
            typedef vfc::TCArray<vfc::uint32_t, NUMBER_MONITORED_COMPONENTS> PartialResponseArray;

            //---------------------------------------------------------------------
            /// Array for booleans
            //---------------------------------------------------------------------
            typedef vfc::TCArray<bool, NUMBER_MONITORED_COMPONENTS> BoolArray;

            //---------------------------------------------------------------------
            /// Array of bools with additional bitinverse respresentations
            //---------------------------------------------------------------------
            typedef vfc::TCArray<fusa_picfreeze::TCBitInverseDataStorage<bool>, NUMBER_MONITORED_COMPONENTS> BitInverseBoolArray;

            //---------------------------------------------------------------------
            /// Stores the partial responses for all monitored components
            //---------------------------------------------------------------------
            PartialResponseArray    m_partialResponses;

            //---------------------------------------------------------------------
            /// Keeps track of the current execution status of each monitoring
            /// false - task in which monitoring is executed was activated
            /// true  - monitoring was executed errors that need to be reported to IWD
            //---------------------------------------------------------------------
            BoolArray               m_monitoringExecutedSuccessfull;

            //---------------------------------------------------------------------
            /// Keeps track of the errors in the last cycle for each monitoring
            /// Cycle means in this case the cyclic occuring time between challenge
            /// and response
            //---------------------------------------------------------------------
            BitInverseBoolArray     m_errorStateOfCycle;

            //---------------------------------------------------------------------
            /// Task activation counter for the task in which the monitorings are running
            /// For the current monitorings this is the Task_C0_Task_10ms. It is
            /// reset to zero for every received challenge and checked before giving
            /// a combined response. The combined response will be zero if the activation
            /// counter is out of range.
            //---------------------------------------------------------------------
            vfc::uint8_t            m_taskActivationCounter;

            //---------------------------------------------------------------------
            /// Stores the current challenge
            //---------------------------------------------------------------------
            vfc::uint32_t           m_challenge;

            //---------------------------------------------------------------------
            /// Keeps track of general errors that occur.
            /// A general error is for example if a monitoring gives an index that is
            /// out of range. If this is set the combined response will be zero.
            //---------------------------------------------------------------------
            bool                    m_generalErrorOccured;

            //---------------------------------------------------------------------
            /// Returns the correction value for the given challenge
            /// @param f_challenge for which the correction value should be given
            /// @return correction value
            //---------------------------------------------------------------------
            vfc::uint32_t getCorrectionValue(const vfc::uint32_t f_challenge) const;

            //---------------------------------------------------------------------
            /// Private constructor because of partial response interface
            //---------------------------------------------------------------------
            CIwdPartialResponseInterface();
    };  
}

#endif // IWD_PARTIAL_RESPONSE_INTERFACE_HPP_INCLUDED

//=============================================================================
