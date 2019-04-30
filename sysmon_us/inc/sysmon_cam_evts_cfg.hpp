//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//     Projectname: NRCS2
//  Target systems:
//       Compilers: ISO C++11 compliant; Doxygen
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//        Name: Christoph Linckh
//  Department: CC-DA/ESI4
//=============================================================================
/// @file  sysmon_cam_evts_cfg.hpp
//=============================================================================

#ifndef SYSMON_CAM_EVTS_CFG_HPP_INCLUDED
#define SYSMON_CAM_EVTS_CFG_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp"
#include "camdatamngr/inc/config_types_cam_events.hpp"

#include "sysmon_us/inc/gen/sysmonpf_cfg_rbsysevm.hpp"

namespace ussysmonpf
{

    // SYS-Mon configuration for FRONT-Camera
    constexpr cdm::CCamEvtStatMap g_camEvtTblSysMonFront_a[] =
    {
        { cdm::ECamEvtId::OPEN_LOAD,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_OpenLoad)},
        { cdm::ECamEvtId::OVER__CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_OvrCurr)},
        { cdm::ECamEvtId::SHORT_CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_ShortCircuit)},
        { cdm::ECamEvtId::OVER_TEMP,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_OvrTemp)},
        { cdm::ECamEvtId::UNDER_TEMP,                offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_UndrTemp)},
        { cdm::ECamEvtId::OVER_VOLTAGE,              offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_OvrVoltage)},
        { cdm::ECamEvtId::UNDER_VOLTAGE,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamFront_UndrVoltage)},
    };

    // SYS-Mon configuration for REAR-Camera
    constexpr cdm::CCamEvtStatMap g_camEvtTblSysMonRear_a[] =
    {
        { cdm::ECamEvtId::OPEN_LOAD,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_OpenLoad)},
        { cdm::ECamEvtId::OVER__CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_OvrCurr)},
        { cdm::ECamEvtId::SHORT_CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_ShortCircuit)},
        { cdm::ECamEvtId::OVER_TEMP,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_OvrTemp)},
        { cdm::ECamEvtId::UNDER_TEMP,                offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_UndrTemp)},
        { cdm::ECamEvtId::OVER_VOLTAGE,              offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_OvrVoltage)},
        { cdm::ECamEvtId::UNDER_VOLTAGE,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRear_UndrVoltage)},
    };

    // SYS-Mon configuration for LEFT-Camera
    constexpr cdm::CCamEvtStatMap g_camEvtTblSysMonLeft_a[] =
    {
        { cdm::ECamEvtId::OPEN_LOAD,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_OpenLoad)},
        { cdm::ECamEvtId::OVER__CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_OvrCurr)},
        { cdm::ECamEvtId::SHORT_CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_ShortCircuit)},
        { cdm::ECamEvtId::OVER_TEMP,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_OvrTemp)},
        { cdm::ECamEvtId::UNDER_TEMP,                offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_UndrTemp)},
        { cdm::ECamEvtId::OVER_VOLTAGE,              offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_OvrVoltage)},
        { cdm::ECamEvtId::UNDER_VOLTAGE,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamLeft_UndrVoltage)},
    };

     // SYS-Mon configuration for RIGHT-Camera
    constexpr cdm::CCamEvtStatMap g_camEvtTblSysMonRight_a[] =
    {
        { cdm::ECamEvtId::OPEN_LOAD,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_OpenLoad)},
        { cdm::ECamEvtId::OVER__CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_OvrCurr)},
        { cdm::ECamEvtId::SHORT_CIRCUIT,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_ShortCircuit)},
        { cdm::ECamEvtId::OVER_TEMP,                 offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_OvrTemp)},
        { cdm::ECamEvtId::UNDER_TEMP,                offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_UndrTemp)},
        { cdm::ECamEvtId::OVER_VOLTAGE,              offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_OvrVoltage)},
        { cdm::ECamEvtId::UNDER_VOLTAGE,             offsetof(ussysmonpf::SysMonPfRunnable_Events, m_FAULT_IBS_CamRight_UndrVoltage)},
    };

}

#endif /* SYSMON_CAM_EVTS_CFG_HPP_INCLUDED */
