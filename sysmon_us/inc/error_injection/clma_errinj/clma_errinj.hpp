#ifndef CLMA_ERRINJ_HPP_INCLUDED
#define CLMA_ERRINJ_HPP_INCLUDED

extern "C"
{
    #include "sysmon_us/inc/error_injection/errinj/xstl_defs.h"
    #include "sysmon_us/inc/error_injection/errinj/xstl_top.h"
    #include "sysmon_us/inc/error_injection/errinj/xstl_clkerr.h"
}
namespace sysmon_base
{
class clmatst
    {
        public:
        /**
        * @brief Main Function of clock Monitoring error injection.
         */
        void error_injection_clma();
        clmatst();
        /**
        * @brief Type of clock ID. 
         */
        enum CLKERR_CHECKER_NUM
        {
            CLMA0 = 0,
            CLMA1,
            CLMA2,
            CLMA3,
            CLMA4,
            CLMA5,
            CLMA6,
            CLMA7
        };    
        u32 Status;
        u32 XStl_PmuStlFreqMs;
        u32 ArgList[8U] = {0U};
        /**
        * @brief XCP variables to trigger error. 
         */
        bool g_triggerclma0error;
        bool g_triggerclma1error;
        bool g_triggerclma2error;
        bool g_triggerclma3error;
        bool g_triggerclma4error;
        bool g_triggerclma5error;
        bool g_triggerclma6error;
        bool g_triggerclma7error;
    };// class clmatst
    
    extern clmatst clmatst_instnc;
}//namespace sysmon_base
#endif