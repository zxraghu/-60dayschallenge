
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
#ifndef SYSMON_US_INTERFACES_HPP_INCLUDED
#define SYSMON_US_INTERFACES_HPP_INCLUDED

#include "vfc/inc/core/vfc_types.hpp" 


namespace sysmon
{

    class CsysMonD3Data 
    {
        public:
        vfc::uint16_t m_temp_sensor1_u16;
        vfc::uint16_t m_temp_sensor2_u16;
        vfc::uint16_t m_battery_voltage_u16;
        vfc::uint16_t m_internal_voltage_0v85_raw_u16;
        vfc::uint16_t m_internal_voltage_1v2_raw_u16;
        vfc::uint16_t m_internal_voltage_1v35_raw_u16;
        vfc::uint16_t m_internal_voltage_1v8_raw_u16;
        vfc::uint16_t m_internal_voltage_3v3_raw_u16;
        vfc::uint16_t m_internal_voltage_4v5_raw_u16;
        vfc::uint16_t m_internal_voltage_5v0_raw_u16;
        vfc::uint16_t m_internal_voltage_9v_raw_u16;
        vfc::uint16_t m_internal_voltage_3v3_USS_raw_u16;
        vfc::uint16_t m_internal_voltage_ISP1_PK_1V1_raw_u16;
        vfc::uint16_t m_internal_voltage_ISP1_PD_1V1_raw_u16;
        vfc::uint16_t m_internal_voltage_VTT_raw_u16;
        vfc::uint16_t m_internal_voltage_Vref_raw_u16;
    };

}
#endif