#include "sysmon_us/inc/imagermon/imager_mon_parse_runnable.hpp"

namespace imager_mon
{
    void CImagerMonRunnable::init()
    {
        onInitEntry();

     //   initUser();

        onInitExit();
    }
    
    CImagerMonRunnable::CImagerMonRunnable():
    daddy::CRunnable(),
    m_embHdrRearOutputReceiverPort(),
    m_embHdrLeftOutputReceiverPort(),
    m_embHdrFrontOutputReceiverPort(),
    m_embHdrRightOutputReceiverPort()
    {
        m_satCamPorts[lad_lcam::ETabCameraConfig::REAR]=&m_embHdrRearOutputReceiverPort;
        m_satCamPorts[lad_lcam::ETabCameraConfig::LEFT]=&m_embHdrLeftOutputReceiverPort;
        m_satCamPorts[lad_lcam::ETabCameraConfig::FRONT]=&m_embHdrFrontOutputReceiverPort;
        m_satCamPorts[lad_lcam::ETabCameraConfig::RIGHT]=&m_embHdrRightOutputReceiverPort;

    }

    void CImagerMonRunnable::run()
    {
        onRunEntry();

        // update the receiver ports with new data
        m_embHdrRearOutputReceiverPort.update();
        m_embHdrLeftOutputReceiverPort.update();
        m_embHdrFrontOutputReceiverPort.update();
        m_embHdrRightOutputReceiverPort.update();

        runUser();
        // cleanup the receiver ports
        m_embHdrRearOutputReceiverPort.cleanup();
        m_embHdrLeftOutputReceiverPort.cleanup();
        m_embHdrFrontOutputReceiverPort.cleanup();
        m_embHdrRightOutputReceiverPort.cleanup();
  

        onRunExit();
    }



}
