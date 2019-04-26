#ifndef IMAGER_MON_1_CAM_RUNNABLE_HPP
#define IMAGER_MON_1_CAM_RUNNABLE_HPP
#include "daddy/inc/daddy_runnable.hpp"
#include "lad_lcam/inc/lad_lcam_output.hpp"
#include "daddy/inc/daddy_receiverport.hpp"
#include "daddy/inc/daddy_senderport.hpp"
#include "sysmon_us/inc/imagermon/imager_mon_emb_lines_extract.hpp"
#include "sysmon_us/inc/imagermon/imagermon_interface.hpp"


namespace imager_mon
{
    
    template<typename CameraEmbeddedLineType>
    class TImagerMon1CamRunnable :daddy::CRunnable
    {
        public:
            using embdLineOutputData_t = CameraEmbeddedLineType;
            //! Daddy receiver port for getting embedded line info
            daddy::TNewestReceiverPort<CameraEmbeddedLineType>  m_embHdrOutputReceiverPort;
            //Daddy sender port to send voltage and temperature to sysmon
            daddy::TSenderPort<imager_mon::CImagerMon1Output> m_imagerDataSenderPort;
            //!constructor
            TImagerMon1CamRunnable(lad_lcam::ETabCameraConfig f_camConfig);
            /// @in_module{sysmon_runnable}
            /// @brief Init method to initialize the runnable.
            ///
            /// Init Method provided by runnable as an interface for the operating system
            void init();
                
            /// @in_module{sysmon_runnable}
            /// @brief Method provided by a runnable
            ///
            /// Run Method provided by runnable as an interface for the operating system
            void run();

            /// @brief rear camera voltage and temperature
            CCamData m_CamData;
            //!to be removed when EVM is available
            CPumDebug m_PUM_failure;

        private:

            /// @in_module{sysmon_runnable}
            /// @brief Init user Method provided by a runnable
            ///
            /// Method provided by runnable as an interface for the operating system
            void initUser();
             
            /// @in_module{sysmon_runnable}
            /// @brief Run user Method provided by a runnable
            ///
            /// Method provided by runnable as an interface for the operating system
            void runUser();

            // @in_module{sysmon_runnable}
            /// @brief doImagerTempMonitor Method provided by a runnable
            /// @param[in] f_camId Camera Id , which represent the which camera had triggerd error
            /// @param[in] f_monitorCam It contains temperature of the f_camId
            /// Method provided by runnable as an interface for the operating system
            void doImagerTempMonitor(const CCamData &f_monitorCam);
            // @in_module{sysmon_runnable}
            /// @brief doImagerVoltageMonitor Method provided by a runnable
            /// @param[in] f_camId Camera Id , which represent the which camera had triggerd error
            /// @param[in] f_monitorCam It contains internal voltages of the f_camId
            /// Method provided by runnable as an interface for the operating system
            void doImagerVoltageMonitor(const CCamData &f_monitorCam);
            // @in_module{sysmon_runnable}
            /// @brief doImagerProcessingUnitMonitor Method provided by a runnable
            /// @param[in] f_camId Camera Id , which represent the which camera had triggerd error
            /// @param[in] f_watchDogTop2Data It contains dat in watchdog_top_2 register data
            /// @param[in] f_watchDogTop3Data It contains dat in watchdog_top_3 register data
            /// Method provided by runnable as an interface for the operating system
            void doImagerProcessingUnitMonitor(const vfc::uint8_t f_watchDogTop2Data,const vfc::uint8_t f_watchDogTop3Data);
            //! camera which this runnable represents
            const lad_lcam::ETabCameraConfig m_camConfig;
    };
    

    using TImagerMon1ArCAMRunnable = TImagerMon1CamRunnable<lad_lcam::CArCamEmbLinesHdrOutput>;
    using TImagerMon1SatCAMRunnable = TImagerMon1CamRunnable<lad_lcam::CSatCamEmbLinesHdrOutput>;

}

#include "sysmon_us/inc/imagermon/imager_mon_parse_1_cam_runnable.inl"
#endif