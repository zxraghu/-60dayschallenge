#ifndef IMAGER_MON_RUNNABLE_HPP
#define IMAGER_MON_RUNNABLE_HPP
#include "daddy/inc/daddy_runnable.hpp"
#include "lad_lcam/inc/lad_lcam_output.hpp"
#include "daddy/inc/daddy_receiverport.hpp"
#include "daddy/inc/daddy_senderport.hpp"
#include "lad_lcam/inc/lad_lcam_output_v3.hpp"
#include "sysmon_us/inc/imagermon/imager_mon_emb_lines_extract.hpp"
#include "sysmon_us/inc/imagermon/imagermon_interface.hpp"
namespace imager_mon
{
    class CImagerMonRunnable: public daddy::CRunnable
    {
        public:

            using CEmbLinesHdrSatPort = daddy::TNewestReceiverPort<lad_lcam::CSatCamEmbLinesHdrOutput>;
            //! Output port for embedded line header of the rear camera
            CEmbLinesHdrSatPort m_embHdrRearOutputReceiverPort;

            //! Output port for embedded line header of the left camera
            CEmbLinesHdrSatPort m_embHdrLeftOutputReceiverPort;

            //! Output port for embedded line header of the front camera
            CEmbLinesHdrSatPort m_embHdrFrontOutputReceiverPort;

            //! Output port for embedded line header of the right camera
            CEmbLinesHdrSatPort m_embHdrRightOutputReceiverPort;
            //Daddy sender port to send voltage and temperature to sysmon
            daddy::TSenderPort<imager_mon::CImagerMonOutput> m_imagerDataSenderPort;
            //! constructor
            CImagerMonRunnable();
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
            // structure holds the camera and current of all the voltages and current
            CCamData m_CamData[G_NO_OF_SAT_CAM];
            // structure holds the all camera ports
            CEmbLinesHdrSatPort *m_satCamPorts[G_NO_OF_SAT_CAM];
            //!to be removed when EVM is available
            CPumDebug m_PUM_failure[G_NO_OF_SAT_CAM];
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
            void doImagerTempMonitor(const CCamData &f_monitorCam,vfc::int32_t f_camId);
            // @in_module{sysmon_runnable}
            /// @brief doImagerVoltageMonitor Method provided by a runnable
            /// @param[in] f_camId Camera Id , which represent the which camera had triggerd error
            /// @param[in] f_monitorCam It contains internal voltages of the f_camId
            /// Method provided by runnable as an interface for the operating system
            void doImagerVoltageMonitor(const CCamData &f_monitorCam,vfc::int32_t f_camId);
            // @in_module{sysmon_runnable}
            /// @brief doImagerProcessingUnitMonitor Method provided by a runnable
            /// @param[in] f_camId Camera Id , which represent the which camera had triggerd error
            /// @param[in] f_watchDogTop2Data It contains dat in watchdog_top_2 register data
            /// @param[in] f_watchDogTop3Data It contains dat in watchdog_top_3 register data
            /// Method provided by runnable as an interface for the operating system
            void doImagerProcessingUnitMonitor(const vfc::uint8_t f_watchDogTop2Data,const vfc::uint8_t f_watchDogTop3Data,vfc::int32_t f_camId);




    };

}
#endif