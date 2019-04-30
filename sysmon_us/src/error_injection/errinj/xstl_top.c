/******************************************************************************
* (c) Copyright 2016 - 2017 Xilinx, Inc. All rights reserved.
* 
* This file contains confidential and proprietary information
* of Xilinx, Inc. and is protected under U.S. and
* international copyright and other intellectual property
* laws.
* 
* DISCLAIMER
* This disclaimer is not a license and does not grant any
* rights to the materials distributed herewith. Except as
* otherwise provided in a valid license issued to you by
* Xilinx, and to the maximum extent permitted by applicable
* law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
* WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
* AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
* INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
* (2) Xilinx shall not be liable (whether in contract or tort,
* including negligence, or under any other theory of
* liability) for any loss or damage of any kind or nature
* related to, arising under or in connection with these
* materials, including for any direct, or any indirect,
* special, incidental, or consequential loss or damage
* (including loss of data, profits, goodwill, or any type of
* loss or damage suffered as a result of any action brought
* by a third party) even if such damage or loss was
* reasonably foreseeable or Xilinx had been advised of the
* possibility of the same.
* 
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-
* safe, or for use in any application requiring fail-safe
* performance, such as life-support or safety devices or
* systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any
* other applications that could lead to death, personal
* injury, or severe property or environmental damage
* (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and
* liability of any use of Xilinx products in Critical
* Applications, subject only to applicable laws and
* regulations governing limitations on product liability.
* 
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
* PART OF THIS FILE AT ALL TIMES.
******************************************************************************/

/*****************************************************************************/
/**
* @file xstl_top.c
*  This file contains STL top level interface routines common to R5 and PMU
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------  -------- -----------------------------------------------------
* 1.0  Naresh  03/08/2016  Initial creation
* 1.1  Naresh  03/24/2016  Changes to address FMEA analysis
* 1.2  Naresh  04/18/2016  Updated file header copyright information
* 1.3  Naresh  04/22/2016  Fixed Misra-C violations
* 1.4  Naresh  05/16/2016  Addressed the review comments,Fixed Misra Violations
* 1.5  Naresh  07/18/2016  Changed return type for XStl_MemScrub routine
* 1.6  Naresh  10/14/2016  Added new APIs for TTC, Interconnect, Error injection:
*                          RPULS,ATB,PMURAMECC,PMUTMR,Sysmon, Loopback:UART,CAN 
*                          and fixed CRs:958375,953990,953983
* 1.7  Naresh  10/20/2016  Added new API XStl_TtcTestEvntTmrTop
* 1.8  Naresh  10/21/2016  Updated API XStl_IntcInvApbAccTestTop to handle the
*                          return type change in the interconnect invalid APB
*                          access test
* 1.9  Naresh  10/22/2016  Fixed Misra-C Violations
* 1.10 Naresh  12/22/2016  Added Top API stubs for MBIST,GEM_LPBK,XPPU,WDT
* 1.11 Rama    01/03/2017  Updated TOP interface for MBIST and GEM STLs
* 1.12 Rama    01/04/2017  Removed duplicate macro for MBIST 
* 1.13 Naresh  02/07/2017  Updated code to address CR#968342
* 1.14 Rama    02/16/2017  Updated XPPU,WDT Top API stubs
* 1.15 Rama    02/22/2017  Updated to address Review comments
* 1.16 Rama    03/15/2017  Updated PMU configuration for WDT and XPPU STLs
* 1.17 Naresh  04/06/2017  Updated to address PR#2497
* 1.18 Naresh  04/18/2017  Updated code to address CR#969232
* 1.19 Naresh  04/18/2017  Updated code to address CR#972834
* 1.20 Naresh  04/26/2017  Updated code to address CR#974513
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "sysmon_us/inc/error_injection/errinj/xstl_defs.h"
#include "sysmon_us/inc/error_injection/errinj/xstl_common.h"
#include "sysmon_us/inc/error_injection/errinj/xstl_top.h"
#if defined(XSTL_GCPY_CREATE_RPUREGS) || defined(XSTL_GCPY_CREATE_PMUREGS) ||\
    defined(XSTL_ON_RPU_CHKCOMMREGS) || defined(XSTL_ON_PMU_CHKCOMMREGS) ||\
    defined(XSTL_ON_RPU_CHKRPUREGS) || defined(XSTL_ON_PMU_CHKPMUREGS)
#include "xstl_regs.h"
#endif
#if defined(XSTL_ON_RPU_ADMATEST) || defined(XSTL_ON_PMU_ADMATEST)
#include "xstl_adma.h"
#endif
#if defined(XSTL_ON_RPU_CLK_ERRINJ) || defined(XSTL_ON_PMU_CLK_ERRINJ)
#include "xstl_clkerr.h"
#endif

#if defined(XSTL_ON_PMU_MEMSCRUBPMU) ||\
    defined(XSTL_ON_RPU_MEMSCRUBOCM) || defined(XSTL_ON_PMU_MEMSCRUBOCM)
#include "xstl_mem.h"
#endif
#if defined(XSTL_ON_RPU_SYSERRINJ) || defined(XSTL_ON_PMU_SYSERRINJ)
#include "xstl_sysmonerr.h"
#endif
#define XSTL_ON_RPU_CLK_ERRINJ          

/************************** Variable Definitions *****************************/
#if defined(XSTL_ON_RPU_CANLPBT) || defined(XSTL_ON_PMU_CANLPBT)
extern u32 CanClkHz;
#endif

#if defined(XSTL_ON_RPU_TTCTEST) || defined(XSTL_ON_PMU_TTCTEST)
extern u32 TtcClkHz;
#endif

XStl_StlGblInst StlGblInst;
/************************** Constant Definitions *****************************/

/************************** Function Definitions *****************************/
/*****************************************************************************/
/**
*
* This function will initialize the STL instance data structure.
*
* @param    StlInstPtr : Pointer to the STL instance data structure.
* @param    StlId : ID of the STL
* @param    StlAttr : Attributes of the STL
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
void XStl_StlInstanceInit(XStl_InstanceStr *StlInstPtr, u32 StlId,
                                                u32 StlAttr, u32 StlFreq)
{
    /* Initialize the STL instance data structure */
    StlInstPtr->State = XSTL_STL_INITIALIZED;
    StlInstPtr->StlAttr = StlAttr;
    StlInstPtr->StlId = StlId;
    StlInstPtr->StlTsRec = (StlAttr >> 3U) & 0x1U;
    StlInstPtr->StlFreq = StlFreq;
    StlInstPtr->StlCmd = 0U;
    StlInstPtr->StlSem = 0U;
    StlInstPtr->CurrTrigs = 0U;
    StlInstPtr->NumTrigs = 1U;
    StlInstPtr->IsRunning = 0U;
    StlInstPtr->CurrCounter = 0U;
    StlInstPtr->PrevCounter = 0U;
    StlInstPtr->InitCxtTsLow = 0xFFFFFFFFU;
    StlInstPtr->InitCxtTsHigh = 0xFFFFFFFFU;
    StlInstPtr->PreCxtTsLow = 0xFFFFFFFFU;
    StlInstPtr->PreCxtTsHigh = 0xFFFFFFFFU;
    StlInstPtr->PostCxtTsLow = 0xFFFFFFFFU;
    StlInstPtr->PostCxtTsHigh = 0xFFFFFFFFU;
    StlInstPtr->ExecState = XSTL_DISABLE;
    StlInstPtr->RetStatus = XST_FAILURE;

    /* Initialize the error info structure */
    StlInstPtr->ErrInfo.ErrCode = 0U;
    StlInstPtr->ErrInfo.ErrWord0 = 0U;
    StlInstPtr->ErrInfo.ErrWord1 = 0U;
    StlInstPtr->ErrInfo.ErrWord2 = 0U;
    StlInstPtr->ErrInfo.ErrWord3 = 0U;
    StlInstPtr->ErrInfo.ErrWord4 = 0U;
}

/*****************************************************************************/
/**
*
* STL interface for clock monitor error injection from R5 or PMU.
*
* @param    ClkInstPtr : Pointer to the STL instance data structure.
* @param    StlAttr : Attributes of the STL.
* @param    StlFreq : STL frequency.
* @param    ArgPtr : Pointer to the STL argument list.
*
* @return   XST_SUCCESS if successful, else XST_FAILURE.
*
* @note     None.
*
*******************************************************************************/
u32 XStl_ClkErrInjTop(XStl_InstanceStr *ClkInstPtr, u32 StlAttr,
                                                u32 StlFreq, u32 *ArgPtr)
{
    u32 Status = XST_FAILURE;

#if !defined(__MICROBLAZE__) && defined(XSTL_ON_RPU_CLK_ERRINJ) && \
                                defined(XSTL_ON_PMU_CLK_ERRINJ)
    return Status;
#endif

    /* Now, invoke the actual STL functionality */
    Status = XStl_ClkErrInj((u8)ArgPtr[0], ArgPtr[1], (u8)ArgPtr[2],
                                                &(ClkInstPtr->ErrInfo));

    return Status;
}
/*****************************************************************************/
/**
*
* This function will drive the STL error information from STL instance str.
*
* @param    StlInstPtr : Pointer to the STL instance data structure.
* @param    ErrInfoPtr : Pointer to err info str into which info to be derived
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
void XStl_GetErrInfo(XStl_InstanceStr *StlInstPtr, XStl_ErrReport *ErrInfoPtr)
{
    ErrInfoPtr->ErrCode = StlInstPtr->ErrInfo.ErrCode;
    ErrInfoPtr->ErrWord0 = StlInstPtr->ErrInfo.ErrWord0;
    ErrInfoPtr->ErrWord1 = StlInstPtr->ErrInfo.ErrWord1;
    ErrInfoPtr->ErrWord2 = StlInstPtr->ErrInfo.ErrWord2;
    ErrInfoPtr->ErrWord3 = StlInstPtr->ErrInfo.ErrWord3;
    ErrInfoPtr->ErrWord4 = StlInstPtr->ErrInfo.ErrWord4;
}
