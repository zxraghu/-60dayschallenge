#include "sysmon_us/inc/romtest/a53/rom_test_runnable.hpp"
#include "sysmon_us/inc/romtest/a53/rom_test.hpp"

namespace sysmon_base
{
    
    void CRomTestRunnable::initUser ()
    {
           
    }
    
    void CRomTestRunnable::runUser ()
    {
        g_FlsTst_instncA53.romTest_Cyclic_Apu();
        CRomTestError &CRomTestA53error =  m_RomTestSenderPort.reserve();
        CRomTestA53error.m_cRomTestEvents.m_FAULT_IBS_CompuVisnModlExtRomVar128 = g_FlsTst_instncA53.m_romtest_failure.m_FAULT_IBS_CompuVisnModlExtRomVar128;
        m_RomTestSenderPort.deliver();
    }
    
}
