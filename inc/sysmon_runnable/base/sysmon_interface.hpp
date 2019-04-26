
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
//            Name: SNEHA NAIK
//      Department: CC-DA/ESI1
//=============================================================================

//=============================================================================
#ifndef SYSMON_INTERFACES_HPP_INCLUDED
#define SYSMON_INTERFACES_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp" 
#include "daddy/inc/daddy_ifbase.hpp"
#include "sysmon_us_cfg/inc/sysmon_pl_ps_cfg.hpp"

namespace sysmon
{
    class CsysMonUscaleData
    {

       public:
        vfc::float32_t m_temperature_US_sens_f1;
        vfc::float32_t m_temperature_US_sens_f2;            
        vfc::float32_t m_Hss_voltage;
        vfc::TCArray<vfc::float32_t, sysmon_base::EnumCameras::CAMERA_ALL>  m_camera_current;
        vfc::TCArray<vfc::float32_t, sysmon_base::EnumCameras::CAMERA_ALL>  m_camera_avdd;
        vfc::TCArray<vfc::float32_t, sysmon_base::EnumCameras::CAMERA_ALL>  m_camera_dovdd;
        vfc::TCArray<vfc::float32_t, sysmon_base::EnumCameras::CAMERA_ALL>  m_camera_dvdd;
        vfc::TCArray<vfc::float32_t, sysmon_base::EnumCameras::CAMERA_ALL>  m_camera_temp;
        vfc::float32_t m_ar_camera_current;
        vfc::float32_t m_ar_camera_avdd;
        vfc::float32_t m_ar_camera_dovdd;
        vfc::float32_t m_ar_camera_dvdd;
        vfc::float32_t m_ar_camera_temp;
    };
    class CSysMonOutput : public daddy::CInterfaceBase
    {
        public:
        enum {     ID = 1 };
        enum {     VERSION = 1 };
        CsysMonUscaleData m_CSysMonUscaleData;
        
        CSysMonOutput() : daddy::CInterfaceBase(ID, VERSION),       
        m_CSysMonUscaleData()
        {
            
        }
    };
}
#endif