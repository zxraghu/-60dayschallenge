/// @def_component{sysmon_base} system monitoring for dai
///
///
/// system monitoring provide the functionality of monitoring the internal voltage and temperature for the Uscale.
/// and functions using the CDG deliverd sysmon code. 
//=============================================================================
/// @def_module{sysmon_base_service_independent_runnable} 
/// @in_component{sysmon_base}
/// @brief Implementation of sysmon_base runnable
///
/// Service independent runnable to handle cyclic tasks.
//=============================================================================

#ifndef SYSMON_RUNNABLE_HPP_INCLUDED
#define SYSMON_RUNNABLE_HPP_INCLUDED

#include "sysmon_us/inc/sysmon/sysmon_pl_ps.hpp"
#include "sysmon_us/inc/clockmon/Clma_clk.hpp"
#include "daddy/inc/daddy_runnable.hpp"
#include "daddy/inc/daddy_receiverport.hpp"
#include "daddy/inc/daddy_senderport.hpp"
#include "vfc/inc/core/vfc_types.hpp"
#include "evm/inc/evm_interface.hpp"
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"
#include "sysmon_us_cfg/gen/USSysMon_Cfg_rbSysEvM.hpp"

#include "sysmon_us/inc/sysmon_interface.hpp"

#include "sysmon_us/inc/taskmon/taskmon_interface.hpp"
#include "sysmon_us/inc/romtest/romtest_interface.hpp"

#include "sysmon_us/inc/error_injection/sysmon_error_injection/sysmon_error_injection.hpp"

namespace sysmon_base
{
    // runnable class
    class CSysmonBaseRunnable : public daddy::CRunnable
    {
        public:
            //class constructor 
            CSysmonBaseRunnable():m_taskMonReceiverPort(),m_taskMonAlgoReceiverPort(), m_sys_mon_base_senderport(), m_RomTestReceiverPort()
            {
            }
            ///  example how to create instance of the evm interface to report the event states list to the evm software component
            evm::CEvmEventsHandling<ussysmonpf::SysMonPfRunnable_Events, ussysmonpf::SysMonPfRunnable_EventSize_cu8> m_evmUsSysmonEvents2D3Evm_SenderPort;
            
            // EVM interface type
            using TUSSysMonEventInterface = rbSysEvM::CEvmEventsPort_swcIO<USSysMon::SysMonRunnable_EventSize_cu8>;
             
            //create sender port to communicate from R5 to D3 for sys mon component to transfer the temperature data
            daddy::TSenderPort<sysmon::CSysMonOutput> m_sys_mon_base_senderport;
            
            //Daddy reciever to get errors fron A53 tasks
            daddy::TNewestReceiverPort<sysmon_base::CTaskMonError> m_taskMonReceiverPort;
            
            //Daddy reciever to get errors fron A53 algotasks
            daddy::TNewestReceiverPort<sysmon_base::CTaskMonError> m_taskMonAlgoReceiverPort;
            
            //Daddy sender port to send events to D3 EVM
            daddy::TSenderPort<TUSSysMonEventInterface> m_USSysMonEventStatesListToEvmSenderPort_out;
            
            //Daddy reciever to get errors fron A53 RomTest
            daddy::TNewestReceiverPort<sysmon_base::CRomTestError> m_RomTestReceiverPort;

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
    };
}

#endif // SYSMON_RUNNABLE_HPP_INCLUDE

