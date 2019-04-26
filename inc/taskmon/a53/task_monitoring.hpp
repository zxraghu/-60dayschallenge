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
#include "os_cfg/a53/os_task_monitoring_cfg.hpp"
#include "sysmon_us/inc/taskmon/taskmon_interface.hpp"   

namespace sysmon_base
{

class TaskMonA53
{
    
    public:
    // taskMon fai
    CTaskMonEvents taskmon_failures;
    /**
    * @brief Function to call the task monitoring for the A53 cyclic tasks
    */
    void taskMonitoring(vfc::uint32_t taskmonType);
    /**
    * @brief Structure to hold the individual update counter and failure flags
    */
    sysmon_base::TaskMon_AliveSupervisionRAMType  taskMon_SupEntityVar_st[sysmon_base::G_NO_OF_SCHEDULED_TASKS];
    /** 
    * @brief Function that monitors the C0 10ms and c0 33ms task
    */    
    void checkA53MonitoringTaskAliveness();
    /** 
    * @brief Function that update the non activations errors for each core separately to send to R5
    */
    void taskmonSetOverActDTC(vfc::uint32_t taskId);
    /** 
    * @brief Function that update the non activations errors for each core separately to send to R5
    */
    void taskmonSetNonActDTC(vfc::uint32_t taskId);
    /**
    * @brief taskMonitoring_AliveSupervision is a wrapper function to OS tasks. This should be called from all the scheduled OS tasks to activate task monitoring for them.
    */
    void taskMonitoring_AliveSupervision(vfc::uint32_t f_supervisionEntity);
    /**
    * @brief Function to getinstance of the class
    */
    static TaskMonA53& getInstance();
    
    private:
    /**
    *@brief Constructor for initializing the variables.
    */
    TaskMonA53();
    /**
    *@brief Copy Constructor does nothing. Private for implementing the singleton design pattern
    */
    TaskMonA53(const TaskMonA53&);
    /**
    * @brief Overloaded = operator, does nothing. Private for implementing the
    *        singleton design pattern.
    */
    TaskMonA53& operator=(const TaskMonA53 &);
    

};


}
#endif
