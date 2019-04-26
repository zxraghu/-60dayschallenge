#ifndef ROMTEST_INTERFACE_HPP_INCLUDED
#define ROMTEST_INTERFACE_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp"
#include "daddy/inc/daddy_ifbase.hpp"

namespace sysmon_base
{  
    class CRomTestEvents 
    {
        public:
        
        vfc::uint8_t m_FAULT_IBS_CompuVisnModlExtRomVar128;
    
    };
    
    class CRomTestError : public daddy::CInterfaceBase
    {
        public:
        enum {     ID = 1 };
        enum {     VERSION = 1 };
        CRomTestEvents m_cRomTestEvents;
        
        CRomTestError() : daddy::CInterfaceBase(ID, VERSION),
        
        m_cRomTestEvents()
        {
            
        }
       
    };
}

#endif //TASKMON_INTERFACE_HPP_INCLUDED
