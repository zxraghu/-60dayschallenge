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
//      Department: CC-DA
//=============================================================================

//=============================================================================
#ifndef TASK_MONITORING_HPP_INCLUDED
#define TASK_MONITORING_HPP_INCLUDED
#include "os_cfg/r5/os_task_monitoring_cfg.hpp"
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"


extern ussysmonpf::SysMonPfRunnable_Events l_evmpfEvents_st;
namespace sysmon_base
{
    class TaskMonR5
    {
        public:
        /**
        * @brief Structure to hold the individual update counter and failure flags
        */
        sysmon_base::TaskMon_AliveSupervisionRAMType  taskMon_SupEntityVar_st[sysmon_base::G_NO_OF_SCHEDULED_TASKS];
        /** 
        * @brief Function that monitors the C0 10ms 
        */
        void checkR5TaskAliveness10ms();
        /** 
        * @brief Function that monitors the C0 100ms from 10ms
        */
        void checkR5TaskAliveness();
        /**
        * @brief taskMonitoring_AliveSupervision is a wrapper function to OS tasks. This should be called from all the scheduled OS tasks to activate task monitoring for them.
        */
        void taskMonitoring_AliveSupervision(vfc::uint32_t f_supervisionEntity); 
        /**
        * @brief Function to getinstance of the class
        */
        static TaskMonR5& getInstance();
    
        private:
        /**
        *@brief Constructor for initializing the variables.
        */
        TaskMonR5();
        /**
        *@brief Copy Constructor does nothing. Private for implementing the singleton design pattern
        */
        TaskMonR5(const TaskMonR5&);
        /**
        * @brief Overloaded = operator, does nothing. Private for implementing the
        *        singleton design pattern.
        */
        TaskMonR5& operator=(const TaskMonR5 &);
        
    };
       
      

}
#endif
