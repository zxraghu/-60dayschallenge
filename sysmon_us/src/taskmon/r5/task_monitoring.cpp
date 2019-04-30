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
#include "sysmon_us/inc/taskmon/r5/task_monitoring.hpp"
#include "trace/inc/trace.hpp"
#include "evm/inc/evm_interface.hpp"
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"
#include "iwd/inc/iwd_partial_response_interface.hpp"

namespace sysmon_base
{ 

    TaskMonR5& TaskMonR5::getInstance()
    {
        static TaskMonR5 m_taskmonInstance;
        return m_taskmonInstance;
    }
    TaskMonR5::TaskMonR5()
    {
        vfc::uint32_t l_seId_u32 = 0u;
        //For all tasks initialise the variables
       
        for(l_seId_u32 = 0; l_seId_u32 < G_NO_OF_SCHEDULED_TASKS; l_seId_u32++)
        {
            taskMon_SupEntityVar_st[l_seId_u32].OveractCtr_u32 = 0u;
            taskMon_SupEntityVar_st[l_seId_u32].NonActCtr_u32 = 0u;
            taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32 = 0u;
            taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32 = taskMon_AliveSupParamPBR5[l_seId_u32].SupervisionReferenceCycle;
            taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32 = 0u;
        }
    }

   
    void TaskMonR5::checkR5TaskAliveness10ms()
    {
        vfc::uint32_t TempCounterdiff_u32 = 0u;
 
        
            taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].IndividualSupCycleCheckCtr_u32--;
            if (0u == taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].IndividualSupCycleCheckCtr_u32)
            {
               
                TempCounterdiff_u32 = taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].IndividualAliveUpdateCtr_u32 - taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].LastAliveUpdateCtr_u32;
                taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].LastAliveUpdateCtr_u32 = taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].IndividualAliveUpdateCtr_u32;
                if (TempCounterdiff_u32 < (taskMon_AliveSupParamPBR5[TASKMONSUPERVISEIDENTITY_10MS].NonActmargin))
                {
                    // Trigger DTC for Non Activation
                    taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].NonActCtr_u32++;
                    l_evmpfEvents_st.m_FAULT_IBS_CompuVisnR5NonActTsks= RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;

                }
                else if (TempCounterdiff_u32 > (taskMon_AliveSupParamPBR5[TASKMONSUPERVISEIDENTITY_10MS].OverActmargin))
                {
                    // Trigger DTC for OverActivation
                    taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].OveractCtr_u32++;
                    l_evmpfEvents_st.m_FAULT_IBS_CompuVisnR5OvrActTsks= RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                
                }
                else
                {
                    //Tasks are running as intended   
                }
                taskMon_SupEntityVar_st[TASKMONSUPERVISEIDENTITY_10MS].IndividualSupCycleCheckCtr_u32 = taskMon_AliveSupParamPBR5[TASKMONSUPERVISEIDENTITY_10MS].SupervisionReferenceCycle;
            }
            else
            {
                //Wait for the turn 
            }
  
    }
    void TaskMonR5::checkR5TaskAliveness()
    {
        vfc::uint32_t TempCounterdiff_u32 = 0u;
        vfc::uint32_t l_seId_u32 = 0u; 
		
        for(l_seId_u32 = 0; l_seId_u32 < G_NO_OF_TASKS_MONITORED_FROM_10MS; l_seId_u32++)
        {
            taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32--;
            if (0u == taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32)
            {
               
                TempCounterdiff_u32 = taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32 - taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32;
                taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32 = taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32;
                if (TempCounterdiff_u32 < (taskMon_AliveSupParamPBR5[l_seId_u32].NonActmargin))
                {
                    // Trigger DTC for Non Activation
                    taskMon_SupEntityVar_st[l_seId_u32].NonActCtr_u32++;
                    l_evmpfEvents_st.m_FAULT_IBS_CompuVisnR5NonActTsks= RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                }
                else if (TempCounterdiff_u32 > (taskMon_AliveSupParamPBR5[l_seId_u32].OverActmargin))
                {
                    // Trigger DTC for OverActivation
                    taskMon_SupEntityVar_st[l_seId_u32].OveractCtr_u32++;
                    l_evmpfEvents_st.m_FAULT_IBS_CompuVisnR5OvrActTsks= RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                }
                else
                {
                    //Tasks are running as intended   
                }
                taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32 = taskMon_AliveSupParamPBR5[l_seId_u32].SupervisionReferenceCycle;
            }
            else
            {
                //Wait for the turn 
            }
        }
        
    }
    
    void TaskMonR5:: taskMonitoring_AliveSupervision(vfc::uint32_t supervisionEntity_u8)
    {
   
        if(G_NO_OF_SCHEDULED_TASKS > supervisionEntity_u8)
        {
           taskMon_SupEntityVar_st[supervisionEntity_u8].IndividualAliveUpdateCtr_u32++;
        }
    }
}
