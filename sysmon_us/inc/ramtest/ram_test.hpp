//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
//  copyright(C) 2009 - 2017 Robert Bosch GmbH.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited.Offenders will be held liable for the
//  payment of damages.All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//     Projectname: NRCS2
//  Target systems: 
//       Compilers: ISO C++11 compliant
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//            Name: Sandeep Bobba
//      Department: ESD
//=============================================================================

//=============================================================================
#ifndef RAM_TEST_HPP_INCLUDED
#define RAM_TEST_HPP_INCLUDED


#include "sys_cfg/inc/layout_defines.hpp"
#include "evm/inc/evm_interface.hpp"
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"

/// object of evmuser event status list @TODO temproray get info from camera falilures to be removed.
extern ussysmonpf::SysMonPfRunnable_Events l_evmpfEvents_st;

namespace sysmon_base
{

//---------------------------------------------------------------------
/// romtest :Api for perfoming ram test for APU RW, ZI regions
/// @par Reference (CS-CRM / DOORS ID / EA):
///   doors: 
///   TnR: https://rb-tracker.bosch.com/tracker08/browse/NRCSTWO-34825
///   ealink:
/// @param   void
/// @return  void
/// @test
///       - Test at the startup before copying APU code and data from flash to RAM
/// $Source: ram_test.hpp
/// @author  sbo5kor
/// @ingroup
//---------------------------------------------------------------------  	

void ramTest_Apu(void);

}

#endif


