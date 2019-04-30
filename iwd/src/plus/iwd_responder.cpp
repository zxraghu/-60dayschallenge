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
/// @file  iwd_responder.cpp
//=============================================================================

#include "iwd/inc/iwd_responder.hpp"
#include "iwd/inc/iwd_partial_response_interface.hpp"
#include "iwd/inc/iwd_variant.hpp"

#include "uart/inc/uart_interface.hpp"

extern "C"
{
    #include "Os.h"
}

// error injection variable, global because it needs to be a XCP variable
CIwdErrorInjection g_iwdErrorInjection;

namespace iwd 
{
    constexpr vfc::uint8_t BITS_PER_BYTE     = 8U;
    constexpr vfc::uint8_t UINT32_BYTESIZE   = sizeof(vfc::uint32_t);
    constexpr vfc::uint8_t MAXIMUM_SHIFT     = 3U;
    constexpr vfc::uint32_t BYTE_BITMASK     = 0x000000FFU;
    
    CIwdResponder& CIwdResponder::instance() 
    {
        static CIwdResponder responder;
        return responder;
    }

    void CIwdResponder::processChallenge(uart::CUartFrame& f_uartFrame) 
    {
        iwd::CIwdPartialResponseInterface::instance().receiveChallenge(getChallengePayload(f_uartFrame));
                    
        // inject early or late response errors
        if(g_iwdErrorInjection.m_earlyResponseErrorInjection)
        {
            m_alarmDelayMs = ALARM_DELAY_EARLY_RESPONSE;
        }
        else if(g_iwdErrorInjection.m_lateResponseErrorInjection)
        {
            m_alarmDelayMs = ALARM_DELAY_LATE_RESPONSE;
        }

        //Activate alarm for delayed execution of sending
        if(E_OK != SetRelAlarm(OS_Iwd_Alarm, m_alarmDelayMs, ALARM_CYCLE_TIME))
        {
            // no error reaction needed here, if the call fails the IWD will react on D3 side
        }
    }

    void CIwdResponder::sendResponse() 
    {
        if(!g_iwdErrorInjection.m_noResponseErrorInjection)
        {
            setResponsePayload(iwd::CIwdPartialResponseInterface::instance().getCombinedResponse());

            // we only send packets in release mode
            #ifndef IWD_DEBUG_MODE_ENABLED
            uart::CUartInterface::instance().sendPacket(m_responsePacket);
            #endif //IWD_DEBUG_MODE_ENABLED
        }
        else
        {
            // no response error was triggered, so we do not send
        }
    }

    void CIwdResponder::sendStartPacket()
    {
        setResponsePayload(START_PACKET_PAYLOAD);
        // we only send packets in release mode
        #ifndef IWD_DEBUG_MODE_ENABLED
        uart::CUartInterface::instance().sendPacket(m_responsePacket);
        #endif //IWD_DEBUG_MODE_ENABLED
    }

    CIwdResponder::CIwdResponder() :
        m_responsePacket(uart::EUserIdentifier::IWD),
        m_alarmDelayMs(ALARM_DELAY_TIME_WINDOW)
    {    
    }


    vfc::uint32_t CIwdResponder::getChallengePayload(uart::CUartFrame& f_uartFrame)
    {
        vfc::TSpan<const vfc::uint8_t> payload = f_uartFrame.getPayload();

        vfc::uint32_t retValue = 0U;
        // get all four bytes of the reponse 
        for(vfc::int32_t i = 0; i < static_cast<vfc::int32_t>(sizeof(vfc::uint32_t)); ++i) 
        {
            // shift:
            // byte 0: 24
            // byte 1: 16
            // byte 2: 8
            // byte 3: 0
            const vfc::uint32_t responseByte = static_cast<const vfc::uint32_t>(payload[i]);
            retValue <<= BITS_PER_BYTE;
            retValue |= responseByte;
        }
        return retValue;
    }

    void CIwdResponder::setResponsePayload(const vfc::uint32_t f_response)
    {
        m_responsePacket.clearPayload();
        // set all four bytes of the reponse 
        for(vfc::uint8_t i = 0U; i < UINT32_BYTESIZE; ++i)
        {
            // shifting:
            // byte 0: 24
            // byte 1: 16
            // byte 2: 8
            // byte 3: 0
            const vfc::uint8_t shift = BITS_PER_BYTE * (MAXIMUM_SHIFT - i);
            const vfc::uint8_t payloadByte = static_cast<vfc::uint8_t>(BYTE_BITMASK & (f_response >> shift));
            m_responsePacket.addPayloadByte(payloadByte);
        }
    }

}

//=============================================================================
