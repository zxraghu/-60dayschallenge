#ifndef TASK_MONITORING_RUNNABLE_HPP_INCLUDED
#define TASK_MONITORING_RUNNABLE_HPP_INCLUDED

#include "vfc/core/vfc_types.hpp"
#include "daddy/daddy_runnable.hpp"
#include "sysmon_us/inc/taskmon/taskmon_interface.hpp"
#include "daddy/inc/daddy_senderport.hpp"
namespace sysmon_base
{
  
    
    // runnable class
    class CTaskMonitorRunnable : public daddy::CRunnable
    {
    public:    
        
        CTaskMonitorRunnable(vfc::uint32_t f_runnableId_ui16);
        
        /**@brief Init method to initialize the runnable.
        ** Init Method provided by runnable as an interface for the operating system
        */
        void init();

        /**@brief Method provided by a runnable
        ** Run Method provided by runnable as an interface for the operating system
        */
        void run();
        /**@brief  For sending the errors from A53 to R5*/
        daddy::TSenderPort<sysmon_base::CTaskMonError> m_taskMonSenderPort;
         

    protected:


    private:


    /**@brief Init user Method provided by a runnable
    ** Method provided by runnable as an interface for the operating system
    */
        void initUser();

    /** @brief Run user Method provided by a runnable
    ** Method provided by runnable as an interface for the operating system
    */
        void runUser();
        
    /** @brief doTaskMonitorWork is the main fucntion which starts the task monitoring  
    */
        void doTaskMonitorWork();
        vfc::uint32_t taskmonType;
    
        
    };


}
#endif
