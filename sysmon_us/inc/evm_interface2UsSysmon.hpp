//---------------------------------------------------------------------------
/// @file
//---------------------------------------------------------------------------
/// @brief Generated header file do not change
//---------------------------------------------------------------------------
/// @details file contains the interfaces relevant data between the runnables
/// evmuser and evm
//----------------------------------------------------------------------------

#ifndef EVMUSER_US_SYSMON_SERVICES_HPP_INCLUDED
#define EVMUSER_US_SYSMON_SERVICES_HPP_INCLUDED

#include "evm/inc/evm_interface.hpp"
#include "vfc/inc/core/vfc_types.hpp"

 namespace evm
{
    /// @brief Size of event status list of the evmuser software component
    const vfc::uint8_t g_evmUsSysmonEventsSize_u8 = 32;
 
    /// @brief Event status list of the evmuser software component
    struct CUsSysmonEvents{
        vfc::uint8_t m_event_PSVccIntlp                         = NO_UPDATE;
        vfc::uint8_t m_event_PSVccIntfp                         = NO_UPDATE;
        vfc::uint8_t m_event_PSVccAux                           = NO_UPDATE;
        vfc::uint8_t m_event_PLVccAux                           = NO_UPDATE;
        vfc::uint8_t m_event_PSTempLpd                          = NO_UPDATE;
        vfc::uint8_t m_event_PSTempFpd                          = NO_UPDATE;
        vfc::uint8_t m_event_ClockUs                            = NO_UPDATE;
        vfc::uint8_t Rear_cam_failure                           = NO_UPDATE;
        vfc::uint8_t Front_Bumper_cam_failure                   = NO_UPDATE;
        vfc::uint8_t Left_Mirror_cam_failure                    = NO_UPDATE;
        vfc::uint8_t Right_Mirror_cam_failure                   = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam1OvrCurr                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam2OvrCurr                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam3OvrCurr                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam4OvrCurr                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam1OvrTemp                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam2OvrTemp                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam3OvrTemp                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_IBS_Cam4OvrTemp                = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnR5OvrActTsks          = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnR5NonActTsks          = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnA53Core0OvrActTsks    = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnA53Core0NonActTsks    = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnA53Core1OvrActTsks    = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnA53Core1NonActTsks    = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnA53Core2OvrActTsks    = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnA532Core2NonActTsks   = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnPL_VCCINT             = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnPL_VCCBRAM            = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnVCCPSDDRPLL           = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnModlExtRomCode128     = NO_UPDATE;
        vfc::uint8_t m_event_IBS_CompuVisnModlExtRamCode        = NO_UPDATE;
    };
    
    /// @brief FIDs size used in the evmuser software component
    const vfc::uint8_t g_evmUsSysmonFidsSize_u8 = 1;

    /// @brief Function permission needed in the evmuser software component
    struct CUsSysmonFuncPermission{
        bool m_dummy1_b  = true;
    };
   
   /// @brief FIDs used in the evmuser software component
   const vfc::uint16_t g_UsSysmonFIds_u16[] =
          {0
           };
}// namespace evm closed

#endif // EVMUSER_US_SYSMON_SERVICES_HPP_INCLUDED
