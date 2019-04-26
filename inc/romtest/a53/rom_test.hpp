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
//            Name: Ashwath Prakash
//      Department: ESD-NR6
//=============================================================================

//=============================================================================
#ifndef ROM_TEST_HPP_INCLUDED
#define ROM_TEST_HPP_INCLUDED


#include "sys_cfg/inc/layout_defines.hpp"
#include "sysmon_us/inc/romtest/romtest_interface.hpp"
#include "evm/inc/rbSysEvM_NArInterfaces.hpp"

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
        FLSTST_CYCLIC_UNINIT = 0,
        FLSTST_CYCLIC_INIT,
        FLSTST_CYCLIC_DONE
    } FlsTst_Cyclic_StateType;
    
    class CFlsTstA53
    {
        public:
        
        /**
        *@brief Constructor for initializing the variables.
        */
        CFlsTstA53();
                
        /**
        *@brief Function to perform APU flstst cyclically
        */
        void romTest_Cyclic_Apu(void);
        
        /**
        *@brief Class variable to store status of Flash Test
        */
        CRomTestEvents m_romtest_failure;
        
        
        private:
        
        FlsTst_Cyclic_StateType m_FlsTst_APU_Cyclic_StateType_en;
        
        vfc::uint32_t m_FlsTst_Cyclic_Failed_counter_u32;
    };
    
    extern CFlsTstA53 g_FlsTst_instncA53;

}

#endif


