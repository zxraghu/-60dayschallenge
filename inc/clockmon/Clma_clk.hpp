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
#ifndef CLMA_CLK_HPP_INCLUDED
#define CLMA_CLK_HPP_INCLUDED
extern "C"
{
    #include "rba_Clma.h"
}
#include "sysmon_us/gen/sysmonpf_cfg_rbsysevm.hpp"
#include "vfc/inc/core/vfc_types.hpp" 


namespace sysmon_base
{
class ClockMon
{
  public:    
    /**
     * @brief Main Function of clock Monitoring.
     */
    void ClkMain(ussysmonpf::SysMonPfRunnable_Events &l_evmpfEvents_st);

    /**
     * @brief Initializing the clock
     */
    void InitClk(ussysmonpf::SysMonPfRunnable_Events &l_evmpfEvents_st);

    /**
     * @brief Default constructor 
     */
    static ClockMon& getinstance();
    
    /**
     * @brief Type of error in clock. 
     */
    rba_ClmaErrorType_ten error_type;
    
  private:
    /**
     * @brief Clock monitoring constructor. Private for implementing the singleton design pattern.
     */
    ClockMon();

    /**
     * @brief Copy constructor, does nothing. Private for implementing the singleton design pattern.
     */
    ClockMon(const ClockMon&);

    /**
     * @brief Overloaded = operator, does nothing. Private for implementing the
     *        singleton design pattern.
     */
    ClockMon& operator=(const ClockMon &);
    /**
     * @brief Delay Function.
     */
    void delay();
};// class ClockMon 

// Inline definitions        
inline ClockMon& ClockMon::getinstance()
{
            static ClockMon m_clockMoninstance;
            return m_clockMoninstance;
}
}//namespace sysmon_base
#endif