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
//        Department: CC-DA/ESI1
//=============================================================================
/// @swcomponent sysmon_config
/// @file sysmon_pl_ps.cpp
//=============================================================================
extern "C"
{
#include "lal_cfg/inc/lalio.h"
#include "usgpio.h"
}
#include "sysmon_us/inc/sysmon/sysmon_pl_ps.hpp"
#include "sysmon_us_cfg/inc/sysmon_sample_cfg.hpp"
#include "iwd/inc/iwd_partial_response_interface.hpp"

namespace sysmon_base
{
    sysmon_config sysmon_config_instance;
   
    void sysmon_config::init_sysmon_ps_pl(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        uint32 ret_SetupResVal_uo = E_OK;
        rba_Sysmon_Init(&rba_Sysmon_Config);
        ret_SetupResVal_uo = static_cast<uint32>(rba_Sysmon_SetupResultBuffer( RBA_SYSMON_PS, sysmon_ps_resultbuffer.begin() ));
        if(E_OK != ret_SetupResVal_uo)
        {
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_LPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_FPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTLP = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTFP = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSAUX = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        }
        ret_SetupResVal_uo = static_cast<uint32>(rba_Sysmon_SetupResultBuffer( RBA_SYSMON_PL, sysmon_pl_resultbuffer.begin() ));
        if(E_OK != ret_SetupResVal_uo)
        {
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_LPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR; // to be replaced by PL DTCs once available
        }
        rba_Sysmon_StartGroupConversion(RBA_SYSMON_PS,RBA_SYSMON_SEQ_MODE_CONTINPASS);
        rba_Sysmon_StartGroupConversion(RBA_SYSMON_PL,RBA_SYSMON_SEQ_MODE_CONTINPASS);
        rba_Sysmon_GetGroupData(RBA_SYSMON_PL);
        rba_Sysmon_GetGroupData(RBA_SYSMON_PS);
        
        /*Initialization  of the camera current monitoring pins of the cameras*/
        g_USGPIO_InitOutput_vd(static_cast<sint32>(g_LALIO_hss1_diag_en_enm + GPIO_EMIO_OFFSET), 1u);
        g_USGPIO_InitOutput_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel1_enm + GPIO_EMIO_OFFSET), 0u);
        g_USGPIO_InitOutput_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel0_enm + GPIO_EMIO_OFFSET), 0u); 
        
        #ifdef MONITOR_ARCAM
        g_USGPIO_InitOutput_vd(static_cast<sint32>(g_LALIO_hss2_diag_en_enm + GPIO_EMIO_OFFSET), 1u);
        #endif
        
        /* --> PL <--SYSMON setting ALARMS for the temperature and Voltage */
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_TEMP_UPPER, sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PLTemp_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_TEMP_LOWER, sysmon_config_instance.m_sysmonThresholds  \
                                                                        .m_sysmon_PLTemp_lower_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_OT_UPPER,XSysMonPsu_TemperatureToRaw_OnChip(TEST_TEMP_UPPER));
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_OT_LOWER,XSysMonPsu_TemperatureToRaw_OnChip(TEST_TEMP_LOWER));    
        //Voltages
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP1_UPPER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PLVccInt_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP1_LOWER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PLVccInt_lower_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP2_UPPER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PLVccAux_upper_treshold_ui16);      
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP2_LOWER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PLVccAux_lower_treshold_ui16);   
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP3_UPPER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PLVccBram_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP3_LOWER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PLVccBram_lower_treshold_ui16);
                                                                        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_VCCAMS_UPPER,TEST_VOLT_UPPER_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_VCCAMS_LOWER,TEST_VOLT_LOWER_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP4_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP4_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
                                                                        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP5_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP5_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP6_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP6_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP7_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP7_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP8_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP8_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP9_UPPER,TEST_VOLT_UPPER_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP9_LOWER,TEST_VOLT_LOWER_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP10_UPPER,TEST_VOLT_UPPER_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PL,RBA_SYSMON_ATR_SUP10_LOWER,TEST_VOLT_LOWER_RAW);
           
        /*  End Setting Alaram for PL<-SYSMON  */
        
        
        
        /* --> PS <--SYSMON setting ALARMS for the temperature and Voltage */
        // Temperatures...
        /*@TODO complete exact threshold is not given by CDG need to raise ticket for Xilinx*/
        /*Threshold is set to MAX and MIN value of the voltages and Temperatures according to manual*/
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_TEMP_UPPER, sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSTempLpd_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_TEMP_LOWER, sysmon_config_instance.m_sysmonThresholds  \
                                                                        .m_sysmon_PSTempLpd_lower_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_TEMP_RMTE_UPPER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSTempFpd_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_TEMP_RMTE_LOWER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSTempFpd_lower_treshold_ui16);       
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_OT_UPPER,XSysMonPsu_TemperatureToRaw_OnChip(TEST_TEMP_UPPER));
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_OT_LOWER,XSysMonPsu_TemperatureToRaw_OnChip(TEST_TEMP_LOWER));    
        //Voltages
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP1_UPPER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSVccIntlp_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP1_LOWER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSVccIntlp_lower_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP2_UPPER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSVccIntfp_upper_treshold_ui16);      
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP2_LOWER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PSVccIntfp_lower_treshold_ui16);   
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP3_UPPER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PSVccAux_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP3_LOWER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PSVccAux_lower_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_VCCAMS_UPPER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSVccAms_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_VCCAMS_LOWER,sysmon_config_instance.m_sysmonThresholds \
                                                                        .m_sysmon_PSVccAms_lower_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP4_UPPER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PSVccPSDdrPll_upper_treshold_ui16);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP4_LOWER,sysmon_config_instance.m_sysmonThresholds. \
                                                                        m_sysmon_PSVccPSDdrPll_lower_treshold_ui16);
                                                                        
                
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP5_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP5_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP6_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP6_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP7_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP7_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP8_UPPER,TEST_VOLT_UPPER_PSIO_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP8_LOWER,TEST_VOLT_LOWER_PSIO_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP9_UPPER,TEST_VOLT_UPPER_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP9_LOWER,TEST_VOLT_LOWER_RAW);
        
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP10_UPPER,TEST_VOLT_UPPER_RAW);
        rba_Sysmon_SetAlarmThreshold(RBA_SYSMON_PS,RBA_SYSMON_ATR_SUP10_LOWER,TEST_VOLT_LOWER_RAW);
            
        /*  End Setting Alaram for PS<-SYSMON  */
        
        
        rba_Sysmon_AlarmEnable(RBA_SYSMON_PS,RBA_PS_SYSMON_ENABLE);    //Enabling all the PS SYSMON error Alarm
        rba_Sysmon_AlarmEnable(RBA_SYSMON_PL,RBA_PL_SYSMON_ENABLE);    //Enabling all the PL SYSMON error Alarm    
    }

    vfc::uint32_t sysmon_config::read_sysmon_ps_pl()
    {
        vfc::uint32_t status = static_cast<vfc::uint32_t>(rba_Sysmon_PSGetStatus(RBA_SYSMON_END_OF_SEQUENCE));
        vfc::float32_t value = 0;
        if(RBA_SYSMON_END_OF_SEQUENCE == status)
        {
            rba_Sysmon_GetGroupData(RBA_SYSMON_PL);
            rba_Sysmon_GetGroupData(RBA_SYSMON_PS);
        }
        else
        {
            return status;
        }
        //rba_Sysmon_StopGroupConversion(RBA_SYSMON_PS);
        rba_Sysmon_GetGroupData(RBA_SYSMON_PL);
        switch(sysmon_currentcamera_state)
            {
            case g_sysmon_CameraCurrent_camera1:
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel1_enm + GPIO_EMIO_OFFSET), 0u);
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel0_enm + GPIO_EMIO_OFFSET), 0u);
                break;
            case g_sysmon_CameraCurrent_camera2:
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel1_enm + GPIO_EMIO_OFFSET), 0u);
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel0_enm + GPIO_EMIO_OFFSET), 1u);
                break;
            case g_sysmon_CameraCurrent_camera3:
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel1_enm + GPIO_EMIO_OFFSET), 1u);
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel0_enm + GPIO_EMIO_OFFSET), 0u);
                break;
            case g_sysmon_CameraCurrent_camera4:
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel1_enm + GPIO_EMIO_OFFSET), 1u);
                g_USGPIO_Set_vd(static_cast<sint32>(g_LALIO_hss1_diag_sel0_enm + GPIO_EMIO_OFFSET), 1u);
                break;
            }               
        /*** storing the converted physical values to the buffer *******/
        value = XSysMonPsu_RawToTemperature_OnChip(sysmon_ps_resultbuffer[Enumpssysmon::TEMP_LPD]);
        sysmon_ps_physical_values[Enumpssysmon::TEMP_LPD] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP1]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP1] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP2]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP2] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP3]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP3] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP4]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP4] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP5]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP5] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP6]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP6] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP7]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP7] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP8]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP8] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP9]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP9] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_SUP10]);
        sysmon_ps_physical_values[Enumpssysmon::PS_SUP10] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_ps_resultbuffer[Enumpssysmon::PS_VCCAMS]);
        sysmon_ps_physical_values[Enumpssysmon::PS_VCCAMS] = value;
        value = XSysMonPsu_RawToTemperature_OnChip(sysmon_ps_resultbuffer[Enumpssysmon::TEMP_REMTE]);
        sysmon_ps_physical_values[Enumpssysmon::TEMP_REMTE] = value;
            
        //updating the temperature values read by sysmon module to transfer to D3
        sysmon_config_instance.sysmon_us_temp_values[0] = sysmon_ps_physical_values[Enumpssysmon::TEMP_LPD];
        sysmon_config_instance.sysmon_us_temp_values[1] = sysmon_ps_physical_values[Enumpssysmon::TEMP_REMTE];
        
        /*** storing the converted physical values to the buffer *******/
        value = XSysMonPsu_RawToTemperature_OnChip(sysmon_pl_resultbuffer[Enumplsysmon::TEMP_PL]);
        sysmon_pl_physical_values[Enumplsysmon::TEMP_PL] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VCCINT]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VCCINT] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VCCAUX]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VCCAUX] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VPVN]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VPVN] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VREFP]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VREFP] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VREFN]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VREFN] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VCCBRAM]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VCCBRAM] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_PSINTLP]);
        sysmon_pl_physical_values[Enumplsysmon::PL_PSINTLP] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_PSINTFP]);
        sysmon_pl_physical_values[Enumplsysmon::PL_PSINTFP] = value;
        value = XSysMonPsu_VccopsioRawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_PSAUX]);
        sysmon_pl_physical_values[Enumplsysmon::PL_PSAUX] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX00]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX00] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX01]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX01] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX02]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX02] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX03]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX03] = value;
        value = XSysMonPsu_RawToVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX04]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX04] = value;
        value = XSysMonPlu_RawToCameraCurrent(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX05]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX05] = value;
        value = XSysMonPlu_RawToCameraCurrent(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX06]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX06] = value; 
        value = XSysMonPlu_RawToHSSVoltage(sysmon_pl_resultbuffer[Enumplsysmon::PL_VAUX08]);
        sysmon_pl_physical_values[Enumplsysmon::PL_VAUX08] = value; 

        m_satcam_current[sysmon_currentcamera_state] = sysmon_pl_physical_values[Enumcamcurrent::SATCAM_CURRENT];
        m_Hss_voltage = sysmon_pl_physical_values[EnumHssvoltage::HSS_VOLTAGE];
        #ifdef MONITOR_ARCAM
        m_ar_camera_current = sysmon_pl_physical_values[Enumcamcurrent::ARCAM_CURRENT];
        #endif
                
        rba_Sysmon_StartGroupConversion(RBA_SYSMON_PS,RBA_SYSMON_SEQ_MODE_CONTINPASS);
        rba_Sysmon_StartGroupConversion(RBA_SYSMON_PL,RBA_SYSMON_SEQ_MODE_CONTINPASS);
        return status;  
    }
    
    void sysmon_config::over_current(vfc::int32_t sysmon_currentcamera_state, ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
       switch(sysmon_currentcamera_state)
            {
                case g_sysmon_CameraCurrent_camera1:
                        l_evmpfEvents_st.m_FAULT_IBS_CamRight_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
                case g_sysmon_CameraCurrent_camera2:
                        l_evmpfEvents_st.m_FAULT_IBS_CamFront_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
                case g_sysmon_CameraCurrent_camera3:
                        l_evmpfEvents_st.m_FAULT_IBS_CamLeft_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
                case g_sysmon_CameraCurrent_camera4:
                        l_evmpfEvents_st.m_FAULT_IBS_CamRear_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
            } 
    }
            
    void sysmon_config::over_load(vfc::int32_t sysmon_currentcamera_state, ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
         switch(sysmon_currentcamera_state)
            {
                case g_sysmon_CameraCurrent_camera1:
                        l_evmpfEvents_st.m_FAULT_IBS_CamRight_OpenLoad = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
                case g_sysmon_CameraCurrent_camera2:
                        l_evmpfEvents_st.m_FAULT_IBS_CamFront_OpenLoad = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
                case g_sysmon_CameraCurrent_camera3:
                        l_evmpfEvents_st.m_FAULT_IBS_CamLeft_OpenLoad = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
                case g_sysmon_CameraCurrent_camera4:
                        l_evmpfEvents_st.m_FAULT_IBS_CamRear_OpenLoad = RBSYSEVM_EVENT_STATUS_PREFAILED_NAR;
                        break;
            }
    }
            
    void sysmon_config::nominal_current(vfc::int32_t sysmon_currentcamera_state, ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        switch(sysmon_currentcamera_state)
            {
                case g_sysmon_CameraCurrent_camera1:
                        l_evmpfEvents_st.m_FAULT_IBS_CamRight_OpenLoad = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        l_evmpfEvents_st.m_FAULT_IBS_CamRight_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        break;
                case g_sysmon_CameraCurrent_camera2:
                        l_evmpfEvents_st.m_FAULT_IBS_CamFront_OpenLoad = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        l_evmpfEvents_st.m_FAULT_IBS_CamFront_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        break;
                case g_sysmon_CameraCurrent_camera3:
                        l_evmpfEvents_st.m_FAULT_IBS_CamLeft_OpenLoad = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        l_evmpfEvents_st.m_FAULT_IBS_CamLeft_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        break;
                case g_sysmon_CameraCurrent_camera4:
                        l_evmpfEvents_st.m_FAULT_IBS_CamRear_OpenLoad = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        l_evmpfEvents_st.m_FAULT_IBS_CamRear_ShortCircuit = RBSYSEVM_EVENT_STATUS_PREPASSED_NAR ;
                        break;
            }
    }
            
    void sysmon_config::check_TEMPLPD(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_TEMP_LPD),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_TEMP_LPD);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_LPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_TEMP_LPD);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_LPD = RBSYSEVM_EVENT_STATUS_PASSED_NAR;            
        }
    }
            
    void sysmon_config::check_TEMPFPD(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_TEMP_FPD),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_TEMP_FPD);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_FPD = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_TEMP_FPD);
            //reporting the no error to the EVM Interface
            //giving prepass/passed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnTEMP_FPD = RBSYSEVM_EVENT_STATUS_PASSED_NAR;            
        }
    }
            
    void sysmon_config::check_VCCPSINTLP(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
       if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCC_PSINTLP),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCC_PSINTLP);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTLP = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCC_PSINTLP);
            //reporting the no error to the EVM Interface
            //giving prepass/passed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTLP = RBSYSEVM_EVENT_STATUS_PASSED_NAR;       
        } 
    }
            
    void sysmon_config::check_VCCPSINTFP(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
         if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCC_PSINTFP),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCC_PSINTFP);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTFP = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCC_PSINTFP);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSINTFP = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
        }
    }
            
    void sysmon_config::check_VCCPSAUX(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCC_PSAUX),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCC_PSAUX);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSAUX = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCC_PSAUX);
            //reporting the no error to the EVM Interface
            //giving prepass/passed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_PSAUX = RBSYSEVM_EVENT_STATUS_PASSED_NAR;         
        }
    }
            
    void sysmon_config::check_PLVCCINT(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
         if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCCINT),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCCINT);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnPL_VCCINT = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCCINT);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnPL_VCCINT = RBSYSEVM_EVENT_STATUS_PASSED_NAR;   
        }
    }
            
    void sysmon_config::check_VCCAUX(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCCAUX),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCCAUX);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_AUX = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCCAUX);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCC_AUX = RBSYSEVM_EVENT_STATUS_PASSED_NAR;   
        }
    }
            
    void sysmon_config::check_PLVCCBRAM(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCCBRAM),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCCBRAM);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnPL_VCCBRAM = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCCBRAM);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnPL_VCCBRAM = RBSYSEVM_EVENT_STATUS_PASSED_NAR;   
        }
    }
            
    void sysmon_config::check_VCCPSDDRPLL(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st)
    {
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCC_PSDDRPLL),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCC_PSDDRPLL);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCCPSDDRPLL = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCC_PSDDRPLL);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            l_evmpfEvents_st.m_FAULT_IBS_CompuVisnVCCPSDDRPLL = RBSYSEVM_EVENT_STATUS_PASSED_NAR;   
        }
    }
            
    void sysmon_config::check_VCCPSADC(USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st)
    {
        #ifdef MONITOR_VCC_PSADC
        if(rba_Sysmon_AlarmGetStatus((1u << ALARM_VCC_PSADC),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_VCC_PSADC);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            f_USSysMonEvents_st.m_FAULT_IBS_CompuVisionVCC_PSADC = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_VCC_PSADC);
            //reporting the no error to the EVM Interface
            //giving prepass/passed
            f_USSysMonEvents_st.m_FAULT_IBS_CompuVisionVCC_PSADC = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
        }
        #endif
    }
            
    void sysmon_config::check_TEMPPL(USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st)
    {
         #ifdef MONITOR_TEMP_PL
         if(rba_Sysmon_AlarmGetStatus((1u << ALARM_TEMP_PL),RBA_AMS_ISR0))
        {
            //setting alram status variable respective bit.
            sysmon_config_instance.alram_status |= (MASK_ONE << ALARM_TEMP_PL);
            //reporting the error to the EVM Interface
            //giving prefail/failed
            f_USSysMonEvents_st.m_FAULT_IBS_CompuVisnTEMP_PL = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else
        {
            //clearing alram status variable respective bit.
            sysmon_config_instance.alram_status &= ~(MASK_ONE << ALARM_TEMP_PL);
            //reporting the no error to the EVM Interface
            //giving prepass/passed 
            f_USSysMonEvents_st.m_FAULT_IBS_CompuVisnTEMP_PL = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
        }
        #endif
    } 
       
    void sysmon_config::error_sysmon_ps_pl(ussysmonpf::SysMonPfRunnable_Events& l_evmpfEvents_st, USSysMon::SysMonRunnable_Events& f_USSysMonEvents_st)
    {
        if(sysmon_pl_physical_values[15] > sysmon_config_instance.m_sysmonThresholds.m_sysmon_satcam_current_upper_treshold_ui16)
        {                   
            //short circuit
            over_current(sysmon_currentcamera_state, l_evmpfEvents_st);
            
        } 
        else if (sysmon_pl_physical_values[15] < sysmon_config_instance.m_sysmonThresholds.m_sysmon_satcam_current_lower_treshold_ui16)
        {
            //open circuit
            over_load(sysmon_currentcamera_state, l_evmpfEvents_st);
        }
        else
        {
            //Current in nominal range
            nominal_current(sysmon_currentcamera_state, l_evmpfEvents_st);
           
        }
        
        #ifdef MONITOR_ARCAM
        if(sysmon_pl_physical_values[16] > 590.0) /*590 mA is the overlimit threshold*/
        {
            //short circuit
            f_USSysMonEvents_st.m_FAULT_IBS_CamAR_ShortCircuit = RBSYSEVM_EVENT_STATUS_FAILED_NAR;
        } 
        else if (sysmon_pl_physical_values[16] < 10.0) /*10 mA is the lowerlimit threshold*/
        {
            //open circuit
            f_USSysMonEvents_st.m_FAULT_IBS_CamAR_OpenLoad = RBSYSEVM_EVENT_STATUS_FAILED_NAR;	
        }
        else
        {
            //Current in nominal range			
            f_USSysMonEvents_st.m_FAULT_IBS_CamAR_OpenLoad = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
            f_USSysMonEvents_st.m_FAULT_IBS_CamAR_ShortCircuit = RBSYSEVM_EVENT_STATUS_PASSED_NAR;
        }
        #endif
            
        sysmon_currentcamera_state++;
        if(sysmon_currentcamera_state >= g_sysmon_CameraCurrent_Max_enm)
        {
            sysmon_currentcamera_state = g_sysmon_CameraCurrent_camera1;
        }    
        /* Checking the status of the  TEMP_LPD voltage */  
        check_TEMPLPD(l_evmpfEvents_st);
        
        /* Checking the status of the  TEMP_FPD voltage */  
        check_TEMPFPD(l_evmpfEvents_st);
        
        /* Checking the status of the  VCC_PSINTLP voltage */  
        check_VCCPSINTLP(l_evmpfEvents_st);
        
        /* Checking the status of the  VCC_PSINTFP voltage */
        check_VCCPSINTFP(l_evmpfEvents_st);
        
        /* Checking the status of the  VCC_PSAUX voltage */
        check_VCCPSAUX(l_evmpfEvents_st);
        
        /* Checking the status of the PL_VCCINT Voltage */
        check_PLVCCINT(l_evmpfEvents_st);
        
        /* Checking the status of the PL_VCCAUX Voltage */
        check_VCCAUX(l_evmpfEvents_st);
        
        /* Checking the status of the PL_VCCBRAM Voltage */
        check_PLVCCBRAM(l_evmpfEvents_st);
        
        /* Checking the status of the VCC_PSDDRPLL Voltage */
        check_VCCPSDDRPLL(l_evmpfEvents_st);
        
        // EVM event not available for JLR hence this is not monitored for JLR currently
        #ifdef MONITOR_VCC_PSADC
        /* Checking the status of the  VCC_PSADC voltage */
        check_VCCPSADC(f_USSysMonEvents_st);
        
        #endif
        
        // EVM event not available for JLR hence this is not monitored for JLR currently
        #ifdef MONITOR_TEMP_PL
        /* Checking the status of the  TEMP_PL */  
        check_TEMPPL(f_USSysMonEvents_st);
       
        #endif
        
    }
}

