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

#include "sysmon_us/inc/ramtest/ram_test.hpp"
#include "trace/inc/trace.hpp"

extern "C" {
#include "RamTst.h"
};

namespace sysmon_base
{
    void ramTest_Apu()
    {
        /* RAM Test init */
        RamTst_Init();
        RamTst_Allow();
        RamTst_MainFunction();
        
        // Check if the RamTst is successful
        if (RAMTST_RESULT_OK == RamTst_GetTestResult())
        {
            /// @deviation NRCS2_001
            /// Rule  qacpp-4.2.1-3842 
            /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
            trace::trace_mprintf("\nAPU Ramtst successs\r\n");
        }
        
        else
        {
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnModlExtRamCode = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            
            /// @deviation NRCS2_001
            /// Rule  qacpp-4.2.1-3842 
            /// Rule can’t be followed, as string literal decays to a pointer type argument in the function call. 
            trace::trace_mprintf("\nAPU Ramtst failed\r\n");  
        }
    }
}

