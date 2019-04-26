#include "sysmon_us/inc/error_injection/clma_errinj/clma_errinj.hpp"

/* Macros for CLKMON Error injection STL */
 
#define XSTL_CLKERR_CLKBCNT_VAL        0x32U   
#define XSTL_SI_PMUSTL_FREQMS          0x64U
/* Array for the STL instance structures */
XStl_InstanceStr *XStl_InstPtr[XSTL_NUM_STLS] = {NULL};

namespace sysmon_base
{

    clmatst clmatst_instnc;
    void clmatst::error_injection_clma()
    {
        if(1 == g_triggerclma0error)
        {
            ArgList[0] = CLMA0;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma1error)
        {
            ArgList[0] = CLMA1;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma2error)
        {
            ArgList[0] = CLMA2;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma3error)
        {
            ArgList[0] = CLMA3;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma4error)
        {
            ArgList[0] = CLMA4;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma5error)
        {
            ArgList[0] = CLMA5;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma6error)
        {
            ArgList[0] = CLMA6;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }
        if(1 == g_triggerclma7error)
        {
            ArgList[0] = CLMA7;
            ArgList[1] = XSTL_CLKERR_CLKBCNT_VAL;
            ArgList[2] = 0U;
            XStl_PmuStlFreqMs = XSTL_SI_PMUSTL_FREQMS;
            Status = XStl_ClkErrInjTop(XStl_InstPtr[XSTL_ID_CLK_ERRINJ],XSTL_TS_RECORD_ENABLE, XStl_PmuStlFreqMs,&ArgList[0]);
        }    
    }
    clmatst::clmatst():g_triggerclma0error(0),g_triggerclma1error(0),g_triggerclma2error(0),g_triggerclma3error(0),g_triggerclma4error(0),g_triggerclma5error(0),g_triggerclma6error(0),g_triggerclma7error(0)
        {
        }
}
    
    