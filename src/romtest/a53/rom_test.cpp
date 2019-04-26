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

#include "sysmon_us/inc/romtest/a53/rom_test.hpp"
#include "trace/inc/trace.hpp"

extern "C" {
#include "FlsTst.h"
};

namespace sysmon_base
{
    
    CFlsTstA53 g_FlsTst_instncA53;
    
    CFlsTstA53::CFlsTstA53(): m_FlsTst_APU_Cyclic_StateType_en(FLSTST_CYCLIC_UNINIT),
                        m_FlsTst_Cyclic_Failed_counter_u32(0)
    {
        
    }
    
    void CFlsTstA53::romTest_Cyclic_Apu()
    {
        FlsTst_TestResultBgndType l_FlsTstStatus;
            
        if (FLSTST_UNINIT == FlsTst_GetCurrentState())
        {
            // give the fls test block reference address here
            FlsTst_Init((const FlsTst_ConfigType*)APU_BASE);
            m_FlsTst_APU_Cyclic_StateType_en = FLSTST_CYCLIC_INIT;
        }
            
        // FlsTst
        FlsTst_MainFunction();
                    
        // Get the result of the Fls Background Test
        l_FlsTstStatus = FlsTst_GetTestResultBgnd();
            
        // Check if the FlsTst is successful
        if (FLSTST_RESULT_OK == l_FlsTstStatus.FlsTst_Result)
        {
            m_romtest_failure.m_FAULT_IBS_CompuVisnModlExtRomVar128 = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
            if (FlsTst_GetTestSignatureBgnd().FlsTst_IntervalId_u8 >= ((FlsTst_Config.FlsTst_BlockNumberBgnd) - 1))
            {
                FlsTst_DeInit();
                m_FlsTst_APU_Cyclic_StateType_en = FLSTST_CYCLIC_DONE;
                
                /// @deviation NRCS2_001
                /// Rule  qacpp-4.2.1-3842 
                /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
                trace::trace_mprintf("\nAPU Romtst Cyclic successs\r\n");
            }
        }
            
        else if (FLSTST_RESULT_NOT_OK == l_FlsTstStatus.FlsTst_Result)
        {
            m_romtest_failure.m_FAULT_IBS_CompuVisnModlExtRomVar128 = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            m_FlsTst_APU_Cyclic_StateType_en = FLSTST_CYCLIC_DONE;
            m_FlsTst_Cyclic_Failed_counter_u32++;
            if (m_FlsTst_Cyclic_Failed_counter_u32 < 4)
            {
                /// @deviation NRCS2_001
                /// Rule  qacpp-4.2.1-3842 
                /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
                trace::trace_mprintf("\nAPU Romtst Cyclic failed\r\n");
            }
        }
            
        else
        {
            m_romtest_failure.m_FAULT_IBS_CompuVisnModlExtRomVar128 = RBSYSEVM_EVENT_STATUS_NOUPDATE_NAR;
        }
    }
}

