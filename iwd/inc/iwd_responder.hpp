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
/// @file  iwd_responder.hpp
/// @brief <add short description here>
//=============================================================================

#ifndef IWD_RESPONDER_HPP_INCLUDED
#define IWD_RESPONDER_HPP_INCLUDED

#include "uart/inc/uart_frame.hpp"

//---------------------------------------------------------------------
/// struct for error injection
//---------------------------------------------------------------------
typedef struct
{
    //---------------------------------------------------------------------
    /// Inject a early response error by setting this to true
    //---------------------------------------------------------------------
    bool m_earlyResponseErrorInjection       = false;

    //---------------------------------------------------------------------
    /// Inject a late response error by setting this to true
    /// note: A late response is not differentiable at the moment since the
    /// time window end is aligned to the sending of a new challenge. For this
    /// reason a late response will be recognized as no response followed by
    /// a early reponse.
    //---------------------------------------------------------------------
    bool m_lateResponseErrorInjection        = false;

    //---------------------------------------------------------------------
    /// Inject a no response error by setting this to true
    //---------------------------------------------------------------------
    bool m_noResponseErrorInjection          = false;
    
} CIwdErrorInjection;

namespace iwd 
{
    //---------------------------------------------------------------------
    /// Length of the payload in the response packet
    /// Since we send a uint32 as response, this is 4
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t RESPONSE_PAYLOAD_LENGTH      = 4U;

    //---------------------------------------------------------------------
    /// Payload for the start packet sent to D3 to start the challenge-
    /// response mechanism
    /// The number is the ASCII code for "IWWD"
    //---------------------------------------------------------------------
    constexpr vfc::uint32_t START_PACKET_PAYLOAD        = 0x49575744U;

    //---------------------------------------------------------------------
    /// Here the normal delay for the alarm is specified to meet the
    /// time window. To meet the time window we delay the sending task by
    /// 15ms.
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t ALARM_DELAY_TIME_WINDOW      = 15U;

    //---------------------------------------------------------------------
    /// Alarm delay to inject a early response error
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t ALARM_DELAY_EARLY_RESPONSE   = 3U;

    //---------------------------------------------------------------------
    /// Alarm delay to inject a late response error
    /// note: A late response is not differentiable at the moment since the
    /// time window end is aligned to the sending of a new challenge. For this
    /// reason a late response will be recognized as no response followed by
    /// a early reponse.
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t ALARM_DELAY_LATE_RESPONSE    = 22U;

    //---------------------------------------------------------------------
    /// The alarm triggered for sending has a cycle option. With this
    /// variable it is possible to trigger the alarm every ALARM_CYCLE_TIME
    /// ms. We only want to trigger once, so the value is 0.
    //---------------------------------------------------------------------
    constexpr vfc::uint8_t ALARM_CYCLE_TIME             = 0U;

    //---------------------------------------------------------------------
    /// Implementation of the responder for the intelligent watchdog
    /// It is used to process the received challenge from D3 and send a 
    /// response back. The response is calculated of the monitored components
    /// and has to meet a time window on D3 side.
    /// Sending back is only active in release mode.
    //---------------------------------------------------------------------
    class CIwdResponder 
    {
        public:
            //---------------------------------------------------------------------
            /// Singleton pattern is implemented through this function
            /// @return singleton instance of the responder
            //---------------------------------------------------------------------
            static CIwdResponder& instance();

            //---------------------------------------------------------------------
            /// Process the received challenge
            /// The challenge is received as a uart frame. The response is calculated
            /// from all the monitorings.
            /// @param 
            //---------------------------------------------------------------------
            void processChallenge(uart::CUartFrame& f_uartFrame);

            //---------------------------------------------------------------------
            /// This function calls the uart sending function to send the response
            /// back to D3. The sending of the packet is only enabled in release
            /// mode.
            //---------------------------------------------------------------------
            void sendResponse();

            //---------------------------------------------------------------------
            /// The current implementation requires the US to send a start packet
            /// to D3 to start the challenge/response mechanism. This is done here.
            //---------------------------------------------------------------------
            void sendStartPacket();

        private:
            //---------------------------------------------------------------------
            /// Uart response frame
            /// Before sending the response is given to the response packet as a
            /// payload. 
            //---------------------------------------------------------------------
            uart::CUartFrame m_responsePacket;

            //---------------------------------------------------------------------
            /// To meet the time window we need to trigger a alarm, which activates
            /// the sending task after the delay specified in this variable (in ms)
            /// Normally this could be made a constexpr, but it is used for error
            /// injection also.
            //---------------------------------------------------------------------
            vfc::uint8_t m_alarmDelayMs;

            //---------------------------------------------------------------------
            /// Private constructor because of singleton pattern
            //---------------------------------------------------------------------
            CIwdResponder();

            //---------------------------------------------------------------------
            /// Get the challenge out of the received uart frame
            /// @param f_uartFrame frame to get the challenge payload of
            /// @return challenge of the received uart frame
            //---------------------------------------------------------------------
            static vfc::uint32_t getChallengePayload(uart::CUartFrame& f_uartFrame);

            //---------------------------------------------------------------------
            /// Set the response in the uart frame as payload
            /// @param f_uartFrame set the payload in this frame
            /// @param f_response payload to set
            //---------------------------------------------------------------------
            void setResponsePayload(const vfc::uint32_t f_response);
    };

}

#endif // IWD_RESPONDER_HPP_INCLUDED

//=============================================================================
