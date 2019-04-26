#include "sysmon_us/inc/taskmon/a53/task_monitoring_runnable.hpp"

namespace sysmon_base
{

  CTaskMonitorRunnable::CTaskMonitorRunnable(vfc::uint32_t f_runnableId_ui16): daddy::CRunnable(),m_taskMonSenderPort()
  {
        taskmonType =f_runnableId_ui16;
  }

  void CTaskMonitorRunnable::run ()
  {
        onRunEntry();
       
        runUser();
        
        onRunExit();;

  }

  void CTaskMonitorRunnable::init ()
  {
        onInitEntry();
        
        initUser();
        
        onInitExit();
  }

}

