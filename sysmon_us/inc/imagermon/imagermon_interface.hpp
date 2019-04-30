
//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
//  copyright(C) 2009 - 2017 Robert Bosch GmbH.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited.Offenders will be held liable for the
//  payment of damages.All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//     Projectname: NRCS2
//  Target systems: 
//       Compilers: ISO C++11 compliant
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//            Name: DERINE JOY
//      Department: 
//=============================================================================

//=============================================================================
#ifndef IMAGERMON_INTERFACES_HPP_INCLUDED
#define IMAGERMON_INTERFACES_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp" 
#include "daddy/inc/daddy_ifbase.hpp"
#include "sysmon_us_cfg/inc/imager_mon_cfg.hpp"
namespace imager_mon
{
    class CImagerData
    {

       public:
        vfc::TCArray<vfc::float32_t, G_NO_OF_SAT_CAM>  m_camera_avdd;
        vfc::TCArray<vfc::float32_t, G_NO_OF_SAT_CAM>  m_camera_dovdd;
        vfc::TCArray<vfc::float32_t, G_NO_OF_SAT_CAM>  m_camera_dvdd;
        vfc::TCArray<vfc::float32_t, G_NO_OF_SAT_CAM>  m_camera_temp;
    };
    class CImagerMonOutput : public daddy::CInterfaceBase
    {
        public:
        enum {     ID = 1 };
        enum {     VERSION = 1 };
        CImagerData m_CImagerData;
        
        CImagerMonOutput() : daddy::CInterfaceBase(ID, VERSION),       
        m_CImagerData()
        {
            
        }
    };
    class CImager1Data
    {

       public:
        vfc::float32_t m_camera_avdd;
        vfc::float32_t m_camera_dovdd;
        vfc::float32_t m_camera_dvdd;
        vfc::float32_t m_camera_temp;
    };
    class CImagerMon1Output : public daddy::CInterfaceBase
    {
        public:
        enum {     ID = 1 };
        enum {     VERSION = 1 };
        CImager1Data m_CImagerData;
        
        CImagerMon1Output() : daddy::CInterfaceBase(ID, VERSION),       
        m_CImagerData()
        {
            
        }
    };
}
#endif