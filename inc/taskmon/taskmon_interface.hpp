#ifndef TASKMON_INTERFACE_HPP_INCLUDED
#define TASKMON_INTERFACE_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp"
#include "daddy/inc/daddy_ifbase.hpp"

namespace sysmon_base
{  
    class CTaskMonEvents 
    {
        public:
        
        vfc::uint8_t m_FAULT_IBS_CompuVisnA53Core0OvrActTsks    ;
        vfc::uint8_t m_FAULT_IBS_CompuVisnA53Core0NonActTsks    ;
        vfc::uint8_t m_FAULT_IBS_CompuVisnA53Core1OvrActTsks    ;
        vfc::uint8_t m_FAULT_IBS_CompuVisnA53Core1NonActTsks    ;
        vfc::uint8_t m_FAULT_IBS_CompuVisnA53Core2OvrActTsks    ;
        vfc::uint8_t m_FAULT_IBS_CompuVisnA532Core2NonActTsks   ;
        vfc::uint8_t m_taskmonStatustoIWD;
    
    };
    class CTaskMonError : public daddy::CInterfaceBase
    {
        public:
        enum {     ID = 1 };
        enum {     VERSION = 1 };
        CTaskMonEvents m_ctaskMonEvents;
        
        CTaskMonError() : daddy::CInterfaceBase(ID, VERSION),
        
        m_ctaskMonEvents()
        {
            
        }
       
    };
}

#endif //TASKMON_INTERFACE_HPP_INCLUDED
