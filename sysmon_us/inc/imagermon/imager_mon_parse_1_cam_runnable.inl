//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
//  Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
//  This file is property of Robert Bosch GmbH. Any unauthorized copy or use or
//  distribution is an offensive act against international law and may be
//  prosecuted under federal law. Its content is company confidential.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//       Projectname: NRC2
//  Target system(s):
//       Compiler(s): VS15, ARM
//=============================================================================
//  N O T E S
//-----------------------------------------------------------------------------
//  Notes:
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//        Name: Derine Joy
//  Department: 
//=============================================================================
//! @file
#include "sysmon_us/inc/imagermon/imager_mon_parse_1_cam_runnable.hpp"
#include "sysmon_us_cfg/inc/imager_mon_send_demEvents.hpp"
namespace imager_mon
{
    template<typename CameraEmbeddedLineType>
    void TImagerMon1CamRunnable<CameraEmbeddedLineType>::init()
    {
        onInitEntry();

     //   initUser();

        onInitExit();
    }

    template<typename CameraEmbeddedLineType>
    TImagerMon1CamRunnable<CameraEmbeddedLineType>::TImagerMon1CamRunnable(lad_lcam::ETabCameraConfig f_camConfig):
    daddy::CRunnable(),
    m_embHdrOutputReceiverPort(),
    m_camConfig(f_camConfig)
    {

    }
    template<typename CameraEmbeddedLineType>
    void TImagerMon1CamRunnable<CameraEmbeddedLineType>::run()
    {
        onRunEntry();

        // update the receiver ports with new data
        m_embHdrOutputReceiverPort.update();

        runUser();
        // cleanup the receiver ports
        m_embHdrOutputReceiverPort.cleanup();
  

        onRunExit();
    }
    template<typename CameraEmbeddedLineType>     
    void TImagerMon1CamRunnable<CameraEmbeddedLineType>::initUser()
    {

    }
    template<typename CameraEmbeddedLineType>
    void TImagerMon1CamRunnable <CameraEmbeddedLineType> ::runUser()
    {
        //Getting embedded line infromation of current camera from the lad_lcam sender port
        if(m_embHdrOutputReceiverPort.hasNewData())
        {
            const vfc::TImageView<const uint32_t> l_imageView =m_embHdrOutputReceiverPort.getData()->getImageView();

            m_CamData.m_avdd=getVoltage(l_imageView,avdd_voltage);
            m_CamData.m_dvdd=getVoltage(l_imageView,dvdd_voltage);
            m_CamData.m_dovdd=getVoltage(l_imageView,dovdd_voltage);
            m_CamData.m_temp=getTemp(l_imageView);
            m_CamData.m_watchdog_top_2=getRegisterData(l_imageView,WATCHDOG_TOP_2);
            m_CamData.m_watchdog_top_3=getRegisterData(l_imageView,WATCHDOG_TOP_3);

            //InternalVoltage Monitoring
            doImagerVoltageMonitor(m_CamData);
            //Temperature Monitoring
            doImagerTempMonitor(m_CamData);
            // Processing Unit Monitoring
            doImagerProcessingUnitMonitor(m_CamData.m_watchdog_top_2,m_CamData.m_watchdog_top_3);
        } 
        //Send internal vooltages to sysmon 
        CImagerMon1Output& l_imagerData = m_imagerDataSenderPort.reserve();
        l_imagerData.m_CImagerData.m_camera_avdd  = m_CamData.m_avdd;
        l_imagerData.m_CImagerData.m_camera_dovdd = m_CamData.m_dovdd; 
        l_imagerData.m_CImagerData.m_camera_dvdd  = m_CamData.m_dvdd;
        l_imagerData.m_CImagerData.m_camera_temp  = m_CamData.m_temp;
        m_imagerDataSenderPort.deliver();
        

       
    }
    template<typename CameraEmbeddedLineType>
    void TImagerMon1CamRunnable <CameraEmbeddedLineType> ::doImagerVoltageMonitor(const CCamData &f_monitorCam)
    {
        if(AVDD_UV_THRESH > f_monitorCam.m_avdd || DVDD_UV_THRESH > f_monitorCam.m_dvdd || DOVDD_UV_THRESH > f_monitorCam.m_dovdd )
        {
            //dem event for undervoltage for rear cam
            UnderVoltDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_FAILED_NAR);
        }
        else if(AVDD_OV_THRESH < f_monitorCam.m_avdd || DVDD_OV_THRESH < f_monitorCam.m_dvdd  ||  DOVDD_OV_THRESH < f_monitorCam.m_dovdd)
        {
            //dem event for over voltage rear cam
            OverVoltDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_FAILED_NAR);
        }
        else
        {
            //clear dem
            UnderVoltDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_PASSED_NAR);
            OverVoltDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_PASSED_NAR);
        
        }
    }
    template<typename CameraEmbeddedLineType>
    void TImagerMon1CamRunnable <CameraEmbeddedLineType> ::doImagerTempMonitor(const CCamData &f_monitorCam)
    {
        if(IMG_TEMP_UPPER < f_monitorCam.m_temp)
        {
            // over temp
            OverTempDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_FAILED_NAR);
        
        }else if(IMG_TEMP_LOWER > f_monitorCam.m_temp )
        {
            // send lower temp
            UnderTempDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_FAILED_NAR);
        }
        else
        {
            // clear dem
            OverTempDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_PASSED_NAR);
            UnderTempDtc(m_camConfig,RBSYSEVM_EVENT_STATUS_PASSED_NAR);
        }
    }

    template<typename CameraEmbeddedLineType>
    void TImagerMon1CamRunnable <CameraEmbeddedLineType> :: doImagerProcessingUnitMonitor(const vfc::uint8_t f_watchDogTop2Data,const vfc::uint8_t f_watchDogTop3Data)
    {

        if((f_watchDogTop2Data & WATCHDOG_BIT_0)== WATCHDOG_STATUS_FAILED)
        {
            //DTPR check Failed
            m_PUM_failure.dtpr_failed=true;
        }
        else
        {
            //DTPR check passed
            m_PUM_failure.dtpr_failed=false;
        }
        if(((f_watchDogTop2Data & WATCHDOG_BIT_1) >> 1)== WATCHDOG_STATUS_FAILED)
        {
            //Internal register failed
            m_PUM_failure.internal_register_failed=true;
        }
        else
        {
            //Internal register passed
            m_PUM_failure.internal_register_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_2) >> 2)== WATCHDOG_STATUS_FAILED)
        {
            //ATPR checker Failed
            m_PUM_failure.atpr_failed=true;
        }
        else
        {
            //ATPR checker Passed
            m_PUM_failure.atpr_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_3) >> 3)== WATCHDOG_STATUS_FAILED)
        {
            //Unique Id check failed
            m_PUM_failure.unique_id_failed=true;
        }
        else
        {
            //Unique Id check passed
            m_PUM_failure.unique_id_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_7) >> 7)== WATCHDOG_STATUS_FAILED)
        {
            //Array row address check failed
            m_PUM_failure.array_addresscheck_failed=true;
        }
        else
        {
            //Array address check passed
            m_PUM_failure.array_addresscheck_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_1) >> 1) == WATCHDOG_STATUS_FAILED)
        {
            //Online Pixel test failed
            m_PUM_failure.online_pixelTest_failed=true;
        }
        else
        {
            //Online Pixel test passed
            m_PUM_failure.online_pixelTest_failed=false;
            
        }
    }

}