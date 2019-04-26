#ifndef SYSMON_ERROR_INJECTION_HPP_INCLUDED
#define SYSMON_ERROR_INJECTION_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp" 
#include "vfc/inc/container/vfc_carray.hpp" 
#include "sysmon_us/inc/sysmon/sysmon_pl_ps.hpp"
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"
#include "sysmon_us_cfg/gen/USSysMon_Cfg_rbSysEvM.hpp"

namespace sysmon_base
{
    class CSysmonTest
    {
        
        public:
        
        CSysmonTest();
        
        /**
          @brief Main Function of clock Monitoring error injection.
        **/
        void error_injection_sysmon(ussysmonpf::SysMonPfRunnable_Events& f_evmpfEvents_st, USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st);
        
        /**
        * @brief XCP variables to trigger error. 
        */
        bool g_triggerPSTempLpdError;
        bool g_triggerPSTempFpdError;
        bool g_triggerPLTempError;
        bool g_triggerPSVccIntLpError;
        bool g_triggerPSVccIntFpError;
        bool g_triggerPSVccAuxError;
        bool g_triggerPLVccIntError;
        bool g_triggerPLVccBramError;
        bool g_triggerPLVccAuxError;
        bool g_triggerPSVccADCError;
    };
    
    extern CSysmonTest sysmontst_instnc;
}

#endif
