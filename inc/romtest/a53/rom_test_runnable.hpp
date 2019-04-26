#ifndef ROM_TEST_RUNNABLE_HPP_INCLUDED
#define ROM_TEST_RUNNABLE_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp"
#include "daddy/inc/daddy_runnable.hpp"
#include "sysmon_us/inc/romtest/romtest_interface.hpp"
#include "daddy/inc/daddy_senderport.hpp"
namespace sysmon_base
{
  
    
    // runnable class
    class CRomTestRunnable : public daddy::CRunnable
    {
    public:    
        
        CRomTestRunnable();
        
        /**@brief Init method to initialize the runnable.
        ** Init Method provided by runnable as an interface for the operating system
        */
        void init();

        /**@brief Method provided by a runnable
        ** Run Method provided by runnable as an interface for the operating system
        */
        void run();
        
        /**@brief  For sending the errors from A53 to R5*/
        daddy::TSenderPort<sysmon_base::CRomTestError> m_RomTestSenderPort;
         

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
        
    };


}
#endif
