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

#include "sysmon_us/inc/romtest/r5/rom_test.hpp"
#include "trace/inc/trace.hpp"

extern "C" {
#include "FlsTst.h"
};

namespace sysmon_base
{
    
    CFlsTstR5 g_FlsTst_instncR5;
    
    CFlsTstR5::CFlsTstR5(): m_FlsTst_APU_Startup_StateType_en(FLSTST_STARTUP_APU_INIT), 
                        m_FlsTst_RPU_Cyclic_StateType_en(FLSTST_CYCLIC_UNINIT),
                        m_FlsTst_Cyclic_Failed_counter_u32(0)
    {
        
    }
    
    void CFlsTstR5::romTest_Apu_startup()
    {
        // give the fls test block reference address here
        FlsTst_Init((const FlsTst_ConfigType*)APU_BASE);
        
        FlsTst_TestResultBgndType l_FlsTstStatus;
        
        // FlsTst
        do
        {
            FlsTst_MainFunction();
        }while(FLSTST_RUNNING == FlsTst_GetCurrentState());
        
        // Get the result of the Fls Background Test
        l_FlsTstStatus = FlsTst_GetTestResultBgnd();
        
        // Check if the FlsTst is successful
        if (FLSTST_RESULT_OK == l_FlsTstStatus.FlsTst_Result)
        {
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnModlExtRomCode128 = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
            
            /// @deviation NRCS2_001
            /// Rule  qacpp-4.2.1-3842 
            /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
            trace::trace_mprintf("\nAPU Romtst successs\r\n");
        }
        
        else
        {
			l_evmpfEvents_st.m_FAULT_IBS_CompuVisnModlExtRomCode128 = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            
            /// @deviation NRCS2_001
            /// Rule  qacpp-4.2.1-3842 
            /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
            trace::trace_mprintf("\nAPU Romtst failed\r\n");  
        }
        
        FlsTst_DeInit();
        m_FlsTst_APU_Startup_StateType_en = FLSTST_STARTUP_APU_DONE;
    }
    
    void CFlsTstR5::romTest_Cyclic_Rpu()
    {
        if (FLSTST_STARTUP_APU_DONE == m_FlsTst_APU_Startup_StateType_en)
        {
            FlsTst_TestResultBgndType l_FlsTstStatus;
            
            if (FLSTST_UNINIT == FlsTst_GetCurrentState())
            {
                // give the fls test block reference address here
                FlsTst_Init((const FlsTst_ConfigType*)RPU_EXEC_RPU_FLS_TEST_BASE);
                m_FlsTst_RPU_Cyclic_StateType_en = FLSTST_CYCLIC_INIT;
            }
            
            // FlsTst
            FlsTst_MainFunction();
                    
            // Get the result of the Fls Background Test
            l_FlsTstStatus = FlsTst_GetTestResultBgnd();
            
            // Check if the FlsTst is successful
            if (FLSTST_RESULT_OK == l_FlsTstStatus.FlsTst_Result)
            {
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnModlExtRomCode128 = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
                if (FlsTst_GetTestSignatureBgnd().FlsTst_IntervalId_u8 >= ((FlsTst_Config.FlsTst_BlockNumberBgnd) - 1))
                {
                    FlsTst_DeInit();
                    m_FlsTst_RPU_Cyclic_StateType_en = FLSTST_CYCLIC_DONE;
                    
                    /// @deviation NRCS2_001
                    /// Rule  qacpp-4.2.1-3842 
                    /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
                    trace::trace_mprintf("\nRPU Romtst Cyclic successs\r\n");
                }
            }
            
            else if (FLSTST_RESULT_NOT_OK == l_FlsTstStatus.FlsTst_Result)
            {
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnModlExtRomCode128 = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
                m_FlsTst_RPU_Cyclic_StateType_en = FLSTST_CYCLIC_DONE;
                m_FlsTst_Cyclic_Failed_counter_u32++;
                if (m_FlsTst_Cyclic_Failed_counter_u32 < 4)
                {
                    /// @deviation NRCS2_001
                    /// Rule  qacpp-4.2.1-3842 
                    /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
                    trace::trace_mprintf("\nRPU Romtst Cyclic failed\r\n");
                }
            }
            
            else
            {
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnModlExtRomCode128 = RBSYSEVM_EVENT_STATUS_NOUPDATE_NAR;
            }
        }
    }
}

