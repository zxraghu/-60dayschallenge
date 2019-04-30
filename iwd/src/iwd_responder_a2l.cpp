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
/// @file  iwd_responder_a2l.cpp
//=============================================================================

/*
@@ SYMBOL     = g_iwdErrorInjection.m_earlyResponseErrorInjection
@@ A2L_TYPE   = PARAMETER g_iwdErrorInjection.m_earlyResponseErrorInjection
@@ DATA_TYPE  = UBYTE
@@ DESCRIPTION = "Error injection: Trigger the send back early, such that we get a early response on D3 side."
@@ END
*/

/*
@@ SYMBOL     = g_iwdErrorInjection.m_lateResponseErrorInjection
@@ A2L_TYPE   = PARAMETER g_iwdErrorInjection.m_lateResponseErrorInjection
@@ DATA_TYPE  = UBYTE
@@ DESCRIPTION = "Error injection: Trigger the send back late, such that we get a late response on D3 side."
@@ END
*/

/*
@@ SYMBOL     = g_iwdErrorInjection.m_noResponseErrorInjection
@@ A2L_TYPE   = PARAMETER g_iwdErrorInjection.m_noResponseErrorInjection
@@ DATA_TYPE  = UBYTE
@@ DESCRIPTION = "Error injection: Not send back a response to inject a no response error on D3 side."
@@ END
*/

//=============================================================================
