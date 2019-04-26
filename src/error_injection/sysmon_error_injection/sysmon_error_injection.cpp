#include "sysmon_us/inc/error_injection/sysmon_error_injection/sysmon_error_injection.hpp"

namespace sysmon_base
{
    
    CSysmonTest sysmontst_instnc;
    
    CSysmonTest::CSysmonTest():g_triggerPSTempLpdError(0),g_triggerPSTempFpdError(0),g_triggerPLTempError(0),
                               g_triggerPSVccIntLpError(0),g_triggerPSVccIntFpError(0),g_triggerPSVccAuxError(0),
                               g_triggerPLVccIntError(0),g_triggerPLVccBramError(0),g_triggerPLVccAuxError(0),
                               g_triggerPSVccADCError(0)
    {
    }
    
    void CSysmonTest::error_injection_sysmon(ussysmonpf::SysMonPfRunnable_Events& f_evmpfEvents_st, USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st)
    {
        if (1 == g_triggerPSTempLpdError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_LPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        if (1 == g_triggerPSTempFpdError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_FPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        // EVM event not available for JLR hence this is not monitored for JLR currently
        #ifdef MONITOR_TEMP_PL
        if (1 == g_triggerPLTempError)
        {
            f_USSysMonEvents_st.m_FAULT_IBS_CompuVisnTEMP_PL = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        #endif
        if (1 == g_triggerPSVccIntLpError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTLP = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        if (1 == g_triggerPSVccIntFpError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTFP = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        if (1 == g_triggerPSVccAuxError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSAUX = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        if (1 == g_triggerPLVccIntError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnPL_VCCINT = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        if (1 == g_triggerPLVccBramError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnPL_VCCBRAM = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        if (1 == g_triggerPLVccAuxError)
        {
            f_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_AUX = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        // EVM event not available for JLR hence this is not monitored for JLR currently
        #ifdef MONITOR_VCC_PSADC
        if (1 == g_triggerPSVccADCError)
        {
            f_USSysMonEvents_st.m_FAULT_IBS_CompuVisionVCC_PSADC = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        #endif
    }
    
}
