#include "sysmon_us/inc/imagermon/imager_mon_parse_runnable.hpp"
#include "sysmon_us_cfg/inc/imager_mon_cfg.hpp"
#include "sysmon_us_cfg/inc/imager_mon_send_demEvents.hpp"

namespace imager_mon
{
    void CImagerMonRunnable::initUser()
    {

    }
    void CImagerMonRunnable::runUser()
    {
        //Getting embedded line infromation of all camera from the lad_lcam sender port
        for(const auto camId : lad_lcam::CLadLcamSatCameraIndex::ALL)
        {
            if(m_satCamPorts[camId]->hasNewData())
            {
                const vfc::TImageView<const uint32_t> l_imageView =m_satCamPorts[camId]->getData()->getImageView();
                
                m_CamData[camId].m_avdd=getVoltage(l_imageView,avdd_voltage);
                m_CamData[camId].m_dvdd=getVoltage(l_imageView,dvdd_voltage);
                m_CamData[camId].m_dovdd=getVoltage(l_imageView,dovdd_voltage);
                m_CamData[camId].m_temp=getTemp(l_imageView);
                m_CamData[camId].m_watchdog_top_2=getRegisterData(l_imageView,WATCHDOG_TOP_2);
                m_CamData[camId].m_watchdog_top_3=getRegisterData(l_imageView,WATCHDOG_TOP_3);
                
                //Internal Voltage Monitoring
                doImagerVoltageMonitor(m_CamData[camId],camId);
                //Temperature Monitoring
                doImagerTempMonitor(m_CamData[camId],camId);
                // Processing Unit Monitoring
                doImagerProcessingUnitMonitor(m_CamData[camId].m_watchdog_top_2,m_CamData[camId].m_watchdog_top_3,camId);
            }
        }
        //Send internal vooltages to sysmon
        CImagerMonOutput& l_imagerData = m_imagerDataSenderPort.reserve();
        l_imagerData.m_CImagerData.m_camera_avdd[lad_lcam::ETabCameraConfig::REAR]  =m_CamData[lad_lcam::ETabCameraConfig::REAR].m_avdd;
        l_imagerData.m_CImagerData.m_camera_avdd[lad_lcam::ETabCameraConfig::LEFT]  =m_CamData[lad_lcam::ETabCameraConfig::LEFT].m_avdd;
        l_imagerData.m_CImagerData.m_camera_avdd[lad_lcam::ETabCameraConfig::FRONT] =m_CamData[lad_lcam::ETabCameraConfig::FRONT].m_avdd;
        l_imagerData.m_CImagerData.m_camera_avdd[lad_lcam::ETabCameraConfig::RIGHT] =m_CamData[lad_lcam::ETabCameraConfig::RIGHT].m_avdd;
        l_imagerData.m_CImagerData.m_camera_dovdd[lad_lcam::ETabCameraConfig::REAR] =m_CamData[lad_lcam::ETabCameraConfig::REAR].m_dovdd;
        l_imagerData.m_CImagerData.m_camera_dovdd[lad_lcam::ETabCameraConfig::LEFT] =m_CamData[lad_lcam::ETabCameraConfig::LEFT].m_dovdd;
        l_imagerData.m_CImagerData.m_camera_dovdd[lad_lcam::ETabCameraConfig::FRONT]=m_CamData[lad_lcam::ETabCameraConfig::FRONT].m_dovdd;
        l_imagerData.m_CImagerData.m_camera_dovdd[lad_lcam::ETabCameraConfig::RIGHT]=m_CamData[lad_lcam::ETabCameraConfig::RIGHT].m_dovdd;
        l_imagerData.m_CImagerData.m_camera_dvdd[lad_lcam::ETabCameraConfig::REAR]  =m_CamData[lad_lcam::ETabCameraConfig::REAR].m_dvdd;
        l_imagerData.m_CImagerData.m_camera_dvdd[lad_lcam::ETabCameraConfig::LEFT]  =m_CamData[lad_lcam::ETabCameraConfig::LEFT].m_dvdd;
        l_imagerData.m_CImagerData.m_camera_dvdd[lad_lcam::ETabCameraConfig::FRONT] =m_CamData[lad_lcam::ETabCameraConfig::FRONT].m_dvdd;
        l_imagerData.m_CImagerData.m_camera_dvdd[lad_lcam::ETabCameraConfig::RIGHT] =m_CamData[lad_lcam::ETabCameraConfig::RIGHT].m_dvdd;
        l_imagerData.m_CImagerData.m_camera_temp[lad_lcam::ETabCameraConfig::REAR]  =m_CamData[lad_lcam::ETabCameraConfig::REAR].m_temp;
        l_imagerData.m_CImagerData.m_camera_temp[lad_lcam::ETabCameraConfig::LEFT]  =m_CamData[lad_lcam::ETabCameraConfig::LEFT].m_temp;
        l_imagerData.m_CImagerData.m_camera_temp[lad_lcam::ETabCameraConfig::FRONT] =m_CamData[lad_lcam::ETabCameraConfig::FRONT].m_temp;
        l_imagerData.m_CImagerData.m_camera_temp[lad_lcam::ETabCameraConfig::RIGHT] =m_CamData[lad_lcam::ETabCameraConfig::RIGHT].m_temp;
        m_imagerDataSenderPort.deliver();
            
        

    }
    void CImagerMonRunnable::doImagerVoltageMonitor(const CCamData &f_monitorCam,vfc::int32_t f_camId)
    {
        if( (AVDD_UV_THRESH > f_monitorCam.m_avdd) ||   (DVDD_UV_THRESH > f_monitorCam.m_dvdd)  ||  (DOVDD_UV_THRESH > f_monitorCam.m_dovdd) )
        {
            //dem event for undervoltage for  cam
            UnderVoltDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREFAILED_NAR);
        }
        else if( (AVDD_OV_THRESH < f_monitorCam.m_avdd) ||   (DVDD_OV_THRESH < f_monitorCam.m_dvdd)  ||  (DOVDD_OV_THRESH < f_monitorCam.m_dovdd) )
        {
            //dem event for over voltage  cam
            OverVoltDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREFAILED_NAR);
        }
        else
        {
            //clear dem
            UnderVoltDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREPASSED_NAR );
            OverVoltDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREPASSED_NAR );
        
        }
    }
    void CImagerMonRunnable::doImagerTempMonitor(const CCamData &f_monitorCam,vfc::int32_t f_camId)
    {
        if(IMG_TEMP_UPPER < f_monitorCam.m_temp)
        {
            // over temp
            OverTempDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREFAILED_NAR);

        }else if(IMG_TEMP_LOWER > f_monitorCam.m_temp  )
        {
            // send lower temp
            UnderTempDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREFAILED_NAR);
        }
        else
        {
            // clear dem
            OverTempDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREPASSED_NAR );
            UnderTempDtc(f_camId,RBSYSEVM_EVENT_STATUS_PREPASSED_NAR );
        }
    }
    void CImagerMonRunnable::doImagerProcessingUnitMonitor(const vfc::uint8_t f_watchDogTop2Data,const vfc::uint8_t f_watchDogTop3Data,vfc::int32_t f_camId)
    {
        if((f_watchDogTop2Data & WATCHDOG_BIT_0)== WATCHDOG_STATUS_FAILED)
        {
            //DTPR check Failed
            m_PUM_failure[f_camId].dtpr_failed=true;
        }
        else
        {
            //DTPR check passed
            m_PUM_failure[f_camId].dtpr_failed=false;
        }
        if(((f_watchDogTop2Data & WATCHDOG_BIT_1) >> 1U)== WATCHDOG_STATUS_FAILED)
        {
            //Internal register failed
            m_PUM_failure[f_camId].internal_register_failed=true;
        }
        else
        {
            //Internal register passed
            m_PUM_failure[f_camId].internal_register_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_2) >> 2U)== WATCHDOG_STATUS_FAILED)
        {
            //ATPR checker Failed
            m_PUM_failure[f_camId].atpr_failed=true;
        }
        else
        {
            //ATPR checker Passed
            m_PUM_failure[f_camId].atpr_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_3) >> 3U)== WATCHDOG_STATUS_FAILED)
        {
            //Unique Id check failed
            m_PUM_failure[f_camId].unique_id_failed=true;
        }
        else
        {
            //Unique Id check passed
            m_PUM_failure[f_camId].unique_id_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_7) >> 7U)== WATCHDOG_STATUS_FAILED)
        {
            //Array row address check failed
            m_PUM_failure[f_camId].array_addresscheck_failed=true;
        }
        else
        {
            //Array address check passed
            m_PUM_failure[f_camId].array_addresscheck_failed=false;
        }
        if(((f_watchDogTop3Data & WATCHDOG_BIT_1) >> 1) == WATCHDOG_STATUS_FAILED)
        {
            //Online Pixel test failed
            m_PUM_failure[f_camId].online_pixelTest_failed=true;
        }
        else
        {
            //Online Pixel test passed
            m_PUM_failure[f_camId].online_pixelTest_failed=false;
        }

    }
}
