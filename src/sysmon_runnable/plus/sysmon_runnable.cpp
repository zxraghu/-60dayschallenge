#include "sysmon_us/inc/sysmon_runnable.hpp"
#include "sysmon_us/inc/sysmon/sysmon_pl_ps.hpp"
#include "sysmon_us/inc/clockmon/Clma_clk.hpp"
namespace sysmon_base
{
    /*CSysmonBaseRunnable::CSysmonBaseRunnable():daddy::CRunnable(),
    m_sys_mon_base_senderport()
    {
        //empty
    } */  
    void CSysmonBaseRunnable::init()
    {
        onInitEntry();      
        initUser();
        onInitExit();
    }       
    void CSysmonBaseRunnable::run()
    {
        onRunEntry();
        m_taskMonReceiverPort.update();
        m_taskMonAlgoReceiverPort.update();             
        m_RomTestReceiverPort.update();    
        runUser();
        m_taskMonReceiverPort.cleanup();
        m_taskMonAlgoReceiverPort.cleanup();             
        m_RomTestReceiverPort.cleanup();
        onRunExit();
     }       
}