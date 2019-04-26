
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
//            Name: 
//      Department: CC-DA/ESI1
//=============================================================================

//=============================================================================
#ifndef SYSMON_PL_PS_INC_HPP_INCLUDED
#define SYSMON_PL_PS_INC_HPP_INCLUDED
extern "C"
{
    #include "rba_Sysmon.h"
}
#include "vfc/inc/core/vfc_types.hpp" 
#include "vfc/inc/container/vfc_carray.hpp" 
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"
#include "sysmon_us_cfg/gen/USSysMon_Cfg_rbSysEvM.hpp"
#include "sysmon_us_cfg/inc/sysmon_pl_ps_cfg.hpp"

namespace sysmon_base
{
    class sysmon_config
    {
        public:
            typedef vfc::TCArray<vfc::uint16_t, RBA_SYSMON_MAX_PS_CHANNEL> T_sys_mon_ps_array;
            typedef vfc::TCArray<vfc::uint16_t, RBA_SYSMON_MAX_PL_CHANNEL> T_sys_mon_pl_array;
            
            typedef vfc::TCArray<vfc::float32_t, RBA_SYSMON_MAX_PS_CHANNEL> T_sysmon_ps_values;
            typedef vfc::TCArray<vfc::float32_t, RBA_SYSMON_MAX_PL_CHANNEL> T_sysmon_pl_values;
        
            typedef vfc::TCArray<vfc::float32_t, 2> T_sysmon_US_cam_values;
            typedef vfc::TCArray<vfc::float32_t, EnumCameras::CAMERA_ALL> T_sysmon_satcam_current;
            typedef enum E_sysmon_CameraCurrentValue_en
            {
                g_sysmon_CameraCurrent_camera1 = 0,
                g_sysmon_CameraCurrent_camera2,
                g_sysmon_CameraCurrent_camera4,
                g_sysmon_CameraCurrent_camera3,
                g_sysmon_CameraCurrent_Max_enm
            }gType_sysmon_currentcamera_en;    
            
            /* Enable/Disable camera monitoring by default enabled */
            vfc::int32_t sysmon_currentcamera_state = 0;
            
            typedef vfc::TCArray<vfc::float32_t, 2> T_sysmon_US_temp_values;
            
            /*To Store all the thresholds values configured*/
            CsysmonThresholds m_sysmonThresholds;
        void init_sysmon_ps_pl(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);               // Initialization   
            vfc::uint32_t read_sysmon_ps_pl();      // Groupconversion of both channels and saving variables in two arrays      
        void error_sysmon_ps_pl(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st, USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st);     //read all error alrams     
            const T_sys_mon_pl_array& get_pl_result_array0()
            {
                return sysmon_pl_resultbuffer;
            }
            const T_sys_mon_ps_array& get_ps_result_array1()
            {
                return sysmon_ps_resultbuffer;
            }
        
            /*To Store the Alram Status*/
            vfc::uint32_t alram_status;

            //Below array to store US+ temp sensor values
            T_sysmon_US_temp_values sysmon_us_temp_values;
            vfc::float32_t m_ar_camera_current;
            T_sysmon_satcam_current m_satcam_current;
            vfc::float32_t m_Hss_voltage;    
            
            void over_current(vfc::int32_t sysmon_currentcamera_state, ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void over_load(vfc::int32_t sysmon_currentcamera_state, ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void nominal_current(vfc::int32_t sysmon_currentcamera_state, ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_TEMPLPD(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_TEMPFPD(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_VCCPSINTLP(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_VCCPSINTFP(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_VCCPSAUX(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_PLVCCINT(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_VCCAUX(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_PLVCCBRAM(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_VCCPSDDRPLL(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st);
            
            void check_VCCPSADC(USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st);
            
            void check_TEMPPL(USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st);
            
            
        private:
            T_sys_mon_ps_array sysmon_ps_resultbuffer;
            T_sys_mon_pl_array sysmon_pl_resultbuffer;
      
            /* Below Data for Debugging purpose */
            T_sysmon_ps_values sysmon_ps_physical_values;
            T_sysmon_pl_values sysmon_pl_physical_values;   
    };
    extern sysmon_config sysmon_config_instance;
}
#endif