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
#ifndef ROM_TEST_HPP_INCLUDED
#define ROM_TEST_HPP_INCLUDED


#include "sys_cfg/inc/layout_defines.hpp"
#include "evm/inc/evm_interface.hpp"
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"

/// object of evmuser event status list @TODO temproray get info from camera falilures to be removed.
extern ussysmonpf::SysMonPfRunnable_Events l_evmpfEvents_st; 

namespace sysmon_base
{

//---------------------------------------------------------------------
/// romtest :Api for perfoming fls test for APU RO, RW regions
/// @par Reference (CS-CRM / DOORS ID / EA):
///   doors: 
///   TnR: https://rb-tracker.bosch.com/tracker08/browse/NRCSTWO-34825
///   ealink:
/// @param   void
/// @return  void
/// @test
///       - Test at the startup before jumping to APU
/// $Source: rom_test.hpp
/// @author  sbo5kor
/// @ingroup
//---------------------------------------------------------------------  	

    typedef enum
    {
        FLSTST_STARTUP_APU_INIT = 0,
        FLSTST_STARTUP_APU_DONE
    } FlsTst_Startup_StateType;
    
    typedef enum
    {
        FLSTST_CYCLIC_UNINIT = 0,
        FLSTST_CYCLIC_INIT,
        FLSTST_CYCLIC_DONE
    } FlsTst_Cyclic_StateType;
    
    class CFlsTstR5
    {
        public:
        
        /**
        *@brief Constructor for initializing the variables.
        */
        CFlsTstR5();
                
        /**
        *@brief Function to perform APU flstst at startup
        */
        void romTest_Apu_startup(void);
        
        /**
        *@brief Function to perform RPU flstst cyclically
        */
        void romTest_Cyclic_Rpu(void);
        
        
        private:
        
        FlsTst_Startup_StateType m_FlsTst_APU_Startup_StateType_en;
        FlsTst_Cyclic_StateType m_FlsTst_RPU_Cyclic_StateType_en;
        
        vfc::uint32_t m_FlsTst_Cyclic_Failed_counter_u32;
    };
    
    extern CFlsTstR5 g_FlsTst_instncR5;

}

#endif


