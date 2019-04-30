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

namespace iwd {
    
    //---------------------------------------------------------------------
    /// Currently the IWD is not active in base
    //---------------------------------------------------------------------

    CIwdResponder& CIwdResponder::instance() 
    {
        static CIwdResponder responder;
        return responder;
    }

    void CIwdResponder::processChallenge(uart::CUartFrame& f_uartFrame) 
    {
    }

    void CIwdResponder::sendResponse() 
    {
    }

    void CIwdResponder::sendStartPacket()
    {
    }

    CIwdResponder::CIwdResponder() :
        m_responsePacket(uart::EUserIdentifier::IWD)
    {    
    }

    vfc::uint32_t CIwdResponder::getChallengePayload(uart::CUartFrame& f_uartFrame)
    {
        return 0U;
    }

    void CIwdResponder::setResponsePayload(const vfc::uint32_t f_response)
    {
    }

}

//=============================================================================
