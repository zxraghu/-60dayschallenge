#include "sysmon_us/inc/taskmon/a53/task_monitoring_runnable.hpp"
#include "sysmon_us/inc/taskmon/a53/task_monitoring.hpp"

namespace sysmon_base
{
    
    void CTaskMonitorRunnable::initUser ()
    {
           
    }
    
    void CTaskMonitorRunnable::runUser ()
    {
    
        doTaskMonitorWork();
       
        CTaskMonError &CtaskmonA53error =  m_taskMonSenderPort.reserve();
        CtaskmonA53error.m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core0OvrActTsks=sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_FAULT_IBS_CompuVisnA53Core0OvrActTsks;
        CtaskmonA53error.m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core0NonActTsks= sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_FAULT_IBS_CompuVisnA53Core0NonActTsks;
        CtaskmonA53error.m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core1OvrActTsks=sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_FAULT_IBS_CompuVisnA53Core1OvrActTsks;
        CtaskmonA53error.m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core1NonActTsks=sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_FAULT_IBS_CompuVisnA53Core1NonActTsks;
        CtaskmonA53error.m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core2OvrActTsks=sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_FAULT_IBS_CompuVisnA53Core2OvrActTsks;
        CtaskmonA53error.m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA532Core2NonActTsks=sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_FAULT_IBS_CompuVisnA532Core2NonActTsks;
        m_taskMonSenderPort.deliver();
		
		//Reseting the variable after the data delivery
        sysmon_base::TaskMonA53::getInstance().taskmon_failures.m_taskmonStatustoIWD = false;
        
    }
    
    void CTaskMonitorRunnable::doTaskMonitorWork ()
    {
        sysmon_base::TaskMonA53::getInstance().taskMonitoring(taskmonType);       
    }
    
    
}
