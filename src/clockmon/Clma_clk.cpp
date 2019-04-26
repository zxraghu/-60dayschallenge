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
//            Name: 
//      Department: CC-DA/ESI1
//=============================================================================

//=============================================================================

#include "sysmon_us/inc/clockmon/Clma_clk.hpp"

//clock mon thresholds calculation
//(clock A/Clock B ref clock) * counter value = reference value to be checked
//(99/33.33)*3300 = 9802 = 0x264A
//lower threshold can be 0x264A-X and upper threshold can be 0x264A+X
//here X is equal or less than 15% as per xilinx Us+ soc TRM doc

namespace sysmon_base
{
const vfc::uint8_t CLMA_TOTAL_CLKMONITORS = 8;
ClockMon::ClockMon():error_type(RBA_CLMA_ALL_ERROR)
{
}

void ClockMon::InitClk(ussysmonpf::SysMonPfRunnable_Events &l_evmpfEvents_st)
{
    vfc::char_t init_status = (rba_Clma_InitClockMonitor(&rba_Clma_Config_cst));
    if(E_NOT_OK == init_status)
    {
      l_evmpfEvents_st.m_FAULT_IBS_CompuVisnWrgClock = RBSYSEVM_EVENT_STATUS_FAILED_NAR;  
    }
   
}

void ClockMon::ClkMain(ussysmonpf::SysMonPfRunnable_Events &l_evmpfEvents_st)
{
    bool failStatus=false;
    //loop over every clock module and check if the thresholds are within range
    for(vfc::uint8_t index=0; static_cast<vfc::uint32_t>(index) < CLMA_TOTAL_CLKMONITORS; index++)
    {
        //start the monitoring here
        rba_Clma_EnableInterrupts(index);

        //check if there is any clcok monitoring error or not
        error_type = rba_Clma_InterruptStatus(index);
        if (error_type != RBA_CLMA_NO_ERROR)
        {
            //raise a fault here
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnWrgClock = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            failStatus=true;
        }
        rba_Clma_DisableInterrupts(index);
    }
} 

}

