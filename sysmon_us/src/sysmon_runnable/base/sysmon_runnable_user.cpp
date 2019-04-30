#include "sysmon_us/inc/sysmon_runnable.hpp"
#include "iwd/inc/iwd_partial_response_interface.hpp"
#include "sysmon_us/inc/error_injection/clma_errinj/clma_errinj.hpp"

/// object of evmuser event status list @TODO temproray get info from camera falilures to be removed.
ussysmonpf::SysMonPfRunnable_Events l_evmpfEvents_st; 
USSysMon::SysMonRunnable_Events l_USSysMonEvents_st;

namespace sysmon_base
{
    extern sysmon_config sysmon_config_instance;
    void CSysmonBaseRunnable::initUser()
    {
        sysmon_base::sysmon_config_instance.init_sysmon_ps_pl(l_evmpfEvents_st);
        sysmon_base::ClockMon::getinstance().InitClk(l_evmpfEvents_st);
    }
    
    void CSysmonBaseRunnable::runUser()
    {
        vfc:uint32_t status = RBA_SYSMON_BUSY;
        status = sysmon_base::sysmon_config_instance.read_sysmon_ps_pl();           

        if(RBA_SYSMON_END_OF_SEQUENCE == status )
        {
            sysmon_base::sysmon_config_instance.error_sysmon_ps_pl(l_evmpfEvents_st, l_USSysMonEvents_st);
        }
        else
        {
            //Error reading the rba_sysmon registers. 
        }
        sysmon_base::ClockMon::getinstance().ClkMain(l_evmpfEvents_st);
        
        if(m_taskMonReceiverPort.hasNewData())
        {
            const CTaskMonError *CtaskmonA53error =m_taskMonReceiverPort.getData();
           if(CtaskmonA53error!=NULL)
           {
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnA53Core0NonActTsks = CtaskmonA53error->m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core0NonActTsks;
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnA53Core1NonActTsks = CtaskmonA53error->m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core1NonActTsks;
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnA532Core2NonActTsks = CtaskmonA53error->m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA532Core2NonActTsks;
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnA53Core0OvrActTsks = CtaskmonA53error->m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core0OvrActTsks;
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnA53Core1OvrActTsks = CtaskmonA53error->m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core1OvrActTsks;
                l_evmpfEvents_st.m_FAULT_IBS_CompuVisnA53Core2OvrActTsks = CtaskmonA53error->m_ctaskMonEvents.m_FAULT_IBS_CompuVisnA53Core2OvrActTsks;
            }
            if(CtaskmonA53error->m_ctaskMonEvents.m_taskmonStatustoIWD)
            {

            }
        }        
        
        if(m_RomTestReceiverPort.hasNewData())
        {
                const CRomTestError *CRomTestA53error = m_RomTestReceiverPort.getData();
                l_USSysMonEvents_st.m_FAULT_IBS_CompuVisnModlExtRomVar128 = CRomTestA53error->m_cRomTestEvents.m_FAULT_IBS_CompuVisnModlExtRomVar128;
        }
        
        sysmontst_instnc.error_injection_sysmon(l_evmpfEvents_st, l_USSysMonEvents_st);
        clmatst_instnc.error_injection_clma();
        
        /// how to report the event states list to the evm software component
        m_evmUsSysmonEvents2D3Evm_SenderPort.m_reportEventStatesListToEvm(l_evmpfEvents_st);
        
        // set DTC
        TUSSysMonEventInterface& l_USSysMonoutputEventStatesToEvm = m_USSysMonEventStatesListToEvmSenderPort_out.reserve();
        rbSysEvM::rbSysEvM_SendEventStatusInfo_v<USSysMon::SysMonRunnable_Events,USSysMon::SysMonRunnable_EventSize_cu8>(l_USSysMonEvents_st, l_USSysMonoutputEventStatesToEvm);
        m_USSysMonEventStatesListToEvmSenderPort_out.deliver();


    }
}