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
#include "sysmon_us/inc/taskmon/a53/task_monitoring_runnable.hpp"
#include "sysmon_us/inc/taskmon/a53/task_monitoring.hpp"
#include "trace/inc/trace.hpp"
#include "evm/inc/rbSysEvM_NArInterfaces.hpp"

namespace sysmon_base
{ 

      
     TaskMonA53& TaskMonA53::getInstance()
    {
        static TaskMonA53 m_taskmonInstance;
        return m_taskmonInstance;
    }

    TaskMonA53::TaskMonA53()
    {
        vfc::uint32_t l_seId_u32 = 0u;
        //For all tasks initialise the variables
        for(l_seId_u32 = 0; l_seId_u32 < G_NO_OF_SCHEDULED_TASKS; l_seId_u32++)
        {
            taskMon_SupEntityVar_st[l_seId_u32].OveractCtr_u32 = 0u;
            taskMon_SupEntityVar_st[l_seId_u32].NonActCtr_u32 = 0u;
            taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32 = 0u;
            taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32 = taskMon_AliveSupParamPBA53[l_seId_u32].SupervisionReferenceCycle;
            taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32 = 0u;
        }
    }

    void TaskMonA53::taskMonitoring(vfc::uint32_t taskmonType)
    {
        vfc::uint32_t TempCounterval_u32 = 0u;
        vfc::uint32_t TempCounterdiff_u32 = 0u;
        vfc::uint32_t l_seId_u32 = 0u;     
        vfc::uint32_t start_Id = 0u;
        vfc::uint32_t end_Id =G_NO_OF_SCHEDULED_TASKS;
        
        if (taskmonType ==TASKMON_ID)
        { 
            end_Id   = G_NO_OF_SCHEDULED_NONALGO_TASKS;
        }
        else if(taskmonType == TASKMON_ALGO_ID)
        {
            start_Id = G_NO_OF_SCHEDULED_NONALGO_TASKS;
            end_Id = G_NO_OF_SCHEDULED_NONALGO_TASKS+G_NO_OF_SCHEDULED_ALGO_TASKS;
        }
        
        for(l_seId_u32 = start_Id; l_seId_u32 < end_Id; l_seId_u32++)
        {
            taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32--;
            if (taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32 == 0u )
            {
                TempCounterval_u32 = taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32;
                TempCounterdiff_u32 = TempCounterval_u32 - taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32;
                taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32 = TempCounterval_u32;
                if (TempCounterdiff_u32 < (taskMon_AliveSupParamPBA53[l_seId_u32].NonActmargin))
                {
                    // Trigger DTC for Non Activation
                    taskMon_SupEntityVar_st[l_seId_u32].NonActCtr_u32++;
                    taskmonSetNonActDTC(l_seId_u32);

                }
                else if (TempCounterdiff_u32 >(taskMon_AliveSupParamPBA53[l_seId_u32].OverActmargin))
                {
                    // Trigger DTC for OverActivation
                    taskMon_SupEntityVar_st[l_seId_u32].OveractCtr_u32++;
                    taskmonSetOverActDTC(l_seId_u32);

            
                }
                else
                {
                    //Tasks are running as intended   
                }
                taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32 = taskMon_AliveSupParamPBA53[l_seId_u32].SupervisionReferenceCycle;
            }
            else
            {
                //Wait for the turn 
            }
        }
       
    }
    void TaskMonA53::taskmonSetOverActDTC(vfc::uint32_t  taskId)
    {
		taskmon_failures.m_taskmonStatustoIWD=true;
        if(taskId < G_NO_OF_SCHEDULED_TASKS)
        {
            if(0u == taskMon_AliveSupParamPBA53[taskId].coreId)
            {
                taskmon_failures.m_FAULT_IBS_CompuVisnA53Core0OvrActTsks=RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
            }
            else if(1u == taskMon_AliveSupParamPBA53[taskId].coreId)
            {
                taskmon_failures.m_FAULT_IBS_CompuVisnA53Core1OvrActTsks=RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
            }
            else 
            {
                taskmon_failures.m_FAULT_IBS_CompuVisnA53Core2OvrActTsks=RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
            }
        }
    }
    
    void TaskMonA53::taskmonSetNonActDTC(vfc::uint32_t taskId)
    {
		taskmon_failures.m_taskmonStatustoIWD=true;
        if(taskId < G_NO_OF_SCHEDULED_TASKS)
        {
            if(0u == taskMon_AliveSupParamPBA53[taskId].coreId)
            {
                taskmon_failures.m_FAULT_IBS_CompuVisnA53Core0NonActTsks=RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
            }
            else if(1u == taskMon_AliveSupParamPBA53[taskId].coreId)
            {
                taskmon_failures.m_FAULT_IBS_CompuVisnA53Core1NonActTsks=RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
            }
            else 
            {
                taskmon_failures.m_FAULT_IBS_CompuVisnA532Core2NonActTsks=RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
            }
        }
    }

    void TaskMonA53::taskMonitoring_AliveSupervision(vfc::uint32_t supervisionEntity_u8)
    {
   
        if(supervisionEntity_u8 < G_NO_OF_SCHEDULED_TASKS)
        {
           taskMon_SupEntityVar_st[supervisionEntity_u8].IndividualAliveUpdateCtr_u32++;
        }
    }

    void TaskMonA53::checkA53MonitoringTaskAliveness()
    {
   
       vfc::uint32_t TempCounterdiff_u32 = 0u;
       vfc::uint32_t l_seId_u32 = 0u; 
       vfc::uint32_t end_Id =G_NO_OF_SCHEDULED_TASKS;
       vfc::uint32_t start_Id = G_NO_OF_SCHEDULED_NONALGO_TASKS+G_NO_OF_SCHEDULED_ALGO_TASKS;
       for(l_seId_u32 = start_Id; l_seId_u32 < end_Id; l_seId_u32++)
        {
            taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32--;
            if (0u == taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32)
            {
               
                TempCounterdiff_u32 = taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32 - taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32;
                taskMon_SupEntityVar_st[l_seId_u32].LastAliveUpdateCtr_u32 = taskMon_SupEntityVar_st[l_seId_u32].IndividualAliveUpdateCtr_u32;
                if (TempCounterdiff_u32 < taskMon_AliveSupParamPBA53[l_seId_u32].NonActmargin)
                {
                    // Trigger DTC for Non Activation
                    taskMon_SupEntityVar_st[l_seId_u32].NonActCtr_u32++;
                    taskmon_failures.m_FAULT_IBS_CompuVisnA53Core0NonActTsks= RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;


                }
                else if (TempCounterdiff_u32 > taskMon_AliveSupParamPBA53[l_seId_u32].OverActmargin)
                {
                    // Trigger DTC for OverActivation
                    taskMon_SupEntityVar_st[l_seId_u32].OveractCtr_u32++;
                    taskmon_failures.m_FAULT_IBS_CompuVisnA53Core0OvrActTsks= RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;

                }
                else
                {
                    //Tasks are running as intended   
                }
                taskMon_SupEntityVar_st[l_seId_u32].IndividualSupCycleCheckCtr_u32 = taskMon_AliveSupParamPBA53[l_seId_u32].SupervisionReferenceCycle;
            }
            else
            {
                //Wait for the turn 
            }
        }
    }
}
