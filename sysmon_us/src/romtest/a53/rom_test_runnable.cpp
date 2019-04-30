#include "sysmon_us/inc/romtest/a53/rom_test_runnable.hpp"

namespace sysmon_base
{

  CRomTestRunnable::CRomTestRunnable(): daddy::CRunnable(),m_RomTestSenderPort()
  {
      
  }

  void CRomTestRunnable::run ()
  {
        onRunEntry();
       
        runUser();
        
        onRunExit();;

  }

  void CRomTestRunnable::init ()
  {
        onInitEntry();
        
        initUser();
        
        onInitExit();
  }

}

