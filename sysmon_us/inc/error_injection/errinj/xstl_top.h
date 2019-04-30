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
* @file xstl_top.h
*  This file contains structures, global variables and Macro definitions
*  required for STL top level interface component
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------  -------- -----------------------------------------------------
* 1.0  Naresh   03/08/2016  Initial creation
* 1.1  Naresh   03/24/2016  Changes to address FMEA analysis
* 1.2  Naresh   04/18/2016  Updated file header copyright information
* 1.3  Naresh   04/22/2016  Fixed Misra-C violations
* 1.4  Naresh   06/29/2016  Updated the register STL macros to be inline with
*                           the code changes as per CR#954040
* 1.5  Naresh   10/14/2016  Added new APIs for TTC, Interconnect, Error injection:
*                           RPULS,ATB,PMURAMECC,PMUTMR,Sysmon, Loopbk:UART,CAN
* 1.6  Naresh   10/17/2016  Fixed typo in the IPI timeout macro
* 1.7  Naresh   10/20/2016  Added macros and API for the TTC event timer test
* 1.8  Naresh   10/26/2016  Updated code to addess CR#962582
* 1.9  Naresh   12/22/2016  Added Top API stubs for MBIST,GEM_LPBK,XPPU,SWDT
* 1.10 Naresh   02/07/2017  Updated code to address CR#968342
* 1.11 Rama     02/16/2017  Updated WDT Top API prototype
* 1.12 Rama     02/23/2017  Updated to address Review comments
* 1.13 Naresh   04/06/2017  Updated to address PR#2497
* 1.14 Naresh   04/26/2017  Updated to address CR#974513
* </pre>
*
******************************************************************************/
#include "sysmon_us/inc/error_injection/errinj/xstl_clkerr.h"
#ifndef XSTL_TOP_H      /* prevent circular inclusions */
#define XSTL_TOP_H      /* by using protection macros */

/***************************** Include Files *********************************/

/***************************** Global variables *********************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Constant Definitions *****************************/
/** @name Temporary placeholder for the STL compilation macros
 * @{
 */
#define XSTL_ID_CLK_ERRINJ              0xCU


#define XSTL_STL_INITIALIZED            0x600DC0DEU /* Symbolizing literal "Good Code" */
#define XSTL_DISABLE                    0x0U
#define XSTL_CXT_REG_CNTRCTRL           0xFF260000U
#define XSTL_CXT_REG_CNTRSTAT           0xFF260004U
#define XSTL_CXT_REG_CNTRLOW            0xFF260008U
#define XSTL_CXT_REG_CNTRHIGH           0xFF26000CU
#define XSTL_CXT_REG_CNTRFREQ           0xFF260020U

/* Macros for CLKMON Error injection STL */
#define XSTL_TS_RECORD_ENABLE          0x8U
#define XSTL_NUM_STLS                  0x20U


typedef void (*XStl_ErrFuncPtr)(void *StlErrRef);

typedef struct
{
    //XScuGic_Config *Config;  /**< Configuration table entry */
    u32 IsReady;         /**< Device is initialized and ready */
    u32 UnhandledInterrupts; /**< Intc Statistics */
} XScuGic;

typedef struct {
    //XIpiPsu_Config Config; /**< Configuration structure */
    u32 IsReady; /**< Device is initialized and ready */
    u32 Options; /**< Options set in the device */
} XIpiPsu;


typedef struct {
    XStl_ErrFuncPtr StlErrFuncPtr;
    void *StlErrRef;
    XIpiPsu *IpiInstPtr;
} XStl_StlGblInst;

/**************************** Type Definitions *******************************/
typedef struct {
    u32 State;
    u32 StlAttr;
    u32 StlFreq;
    u32 StlId;
    u32 StlCmd;
    u32 StlSem;
    u32 StlTsRec;
    u32 CurrTrigs;
    u32 NumTrigs;
    u32 IsRunning;
    u32 CurrCounter;
    u32 PrevCounter;
    u32 InitCxtTsLow;
    u32 InitCxtTsHigh;
    u32 PreCxtTsLow;
    u32 PreCxtTsHigh;
    u32 PostCxtTsLow;
    u32 PostCxtTsHigh;
    u32 ExecState;
    u32 RetStatus;
    XStl_ErrReport ErrInfo;
} XStl_InstanceStr;

/************************** Function Prototypes ******************************/

u32 XStl_ClkErrInjTop(XStl_InstanceStr *ClkInstPtr, u32 StlAttr,  u32 StlFreq, u32 *ArgPtr);

void XStl_StlInstanceInit(XStl_InstanceStr *StlInstPtr, u32 StlId, u32 StlAttr, u32 StlFreq);
void XStl_GetErrInfo(XStl_InstanceStr *StlInstPtr, XStl_ErrReport *ErrInfoPtr);
#endif      /* end of protection macro */
