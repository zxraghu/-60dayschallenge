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
* @file xstl_clkerr.c
*  This file contains Contains functions related to clkmon Error injection.
*
* <pre>
* MODIFICATION HISTORY:
*
* * Ver   Who  Date     Changes
* ----- ---- -------- --------------------------------------------------------
* 0.1   Ramadevi    1/20/2015  Initial creation
* 0.2   Ramadevi    1/22/2015  Updated for code inspection results
* 0.3   Ramadevi    3/08/2016  Fixed MISRA-C violations
* 0.4   Ramadevi    4/07/2016  Updated as per FMEA analysis ver 1.1
* 1.0   Ramadevi    4/18/2016  Updated file header copyright information
* 1.1   Ramadevi    5/02/2016  Updated the code as per the design doc ver 1.3
* 1.2   Ramadevi    5/16/2016  Updated for code inspection results
* 1.3   Ramadevi    6/09/2016  Updated to address CR#952980
* 1.4   Ramadevi    6/27/2016  Fixed the code to address CR#952980
* 1.5   Naresh      4/18/2017  Updated code to address CR#969232
* 1.6   Ramadevi    4/24/2017  Updated code to address CR#974773, CR#974863
*
* </pre>
*
******************************************************************************/
/***************************** Include Files *********************************/
#include "sysmon_us/inc/error_injection/errinj/xstl_defs.h"
#include "sysmon_us/inc/error_injection/errinj/xstl_common.h"
#include "sysmon_us/inc/error_injection/errinj/xstl_clkerr.h"

/************************** Variable Definitions *****************************/

/************************** Function Definitions *****************************/
/*****************************************************************************/
/**
*
* STL API that the user can use to test clock monitor error injection
*
* @param    ClkMonitor is 8-bit monitor id for error injection.
* @param    ClkBcntVal 32-bit value to be loaded in clock -B counter.
* @param    IntrCntl is 32 bit value indicates to enable or disable intr, 
*           wait time for ISR handling
* @param    *ErrInfoPtr - pointer to error information
*
* @return   XST_SUCCESS, if error injection is successful
*           XST_FAILURE, if error injection is not successful
*
******************************************************************************/

 void XStl_ClrArgList(u32 *ArgListPtr)
{
    u32 Idx;

    for(Idx = 0U; Idx < 8U; Idx++) {
        ArgListPtr[Idx] = 0U;
    }
}

u32 XStl_ClkErrInj(u8 ClkMonitor, u32 ClkBcntVal, u32 IntrCntl, 
                                            XStl_ErrReport *ErrInfoPtr)
{
    u32 HighThr;
    u32 LowThr;
    u32 ChkrBaseAddr;
    u32 ClkStatus = 0;
    u32 StatusMask;
    u32 StatusFlag;
    u32 InitChkrCtrl;
    u32 InitClkBval;
    u32 InitClkmonImr;
    u32 RetStatus = (u32)XST_FAILURE;
    u32 Timeout;
    u32 IntrEn;

    XSTL_CLEAR(ErrInfoPtr)

    if(ClkMonitor < 8U) {
        ChkrBaseAddr = XSTL_CHKR_CLK_BASE + ((u32)ClkMonitor * 16U);
        /* Calculate the mask for Clock mon status */
        StatusMask = (0x3U << ((u32)ClkMonitor * 2U));
        StatusFlag = 0U;
        IntrEn = (IntrCntl & 0xFFU);
        InitChkrCtrl = XStl_In32(ChkrBaseAddr + XSTL_CHKR_CTRL_OFFSET);
        InitClkmonImr = XStl_In32(XSTL_CLKMON_IMR);
        /* Disable CLKMON_ENABLE interrupt */
        XStl_Out32(XSTL_CLKMON_DISABLE, StatusMask);

        /* Reading Upper and Lower Clk values */
        HighThr = XStl_In32(ChkrBaseAddr + XSTL_CLKA_UPPER_OFFSET);
        LowThr = XStl_In32(ChkrBaseAddr + XSTL_CLKA_LOWER_OFFSET);
        /* Disable the checker to change the threhsolds */
        XStl_Out32(ChkrBaseAddr + XSTL_CHKR_CTRL_OFFSET,(InitChkrCtrl & 0x7EU));
        /* Swap the thresholds for Error injection*/
        XStl_Out32(ChkrBaseAddr + XSTL_CLKA_UPPER_OFFSET, LowThr);
        XStl_Out32(ChkrBaseAddr + XSTL_CLKA_LOWER_OFFSET, HighThr);
        /* Write clock B counter value */
        InitClkBval = XStl_In32(ChkrBaseAddr + XSTL_CLKB_COUNT_OFFSET);
        XStl_Out32(ChkrBaseAddr + XSTL_CLKB_COUNT_OFFSET, ClkBcntVal);
        /* Enable the checker to start the test */
        XStl_Out32(ChkrBaseAddr + XSTL_CHKR_CTRL_OFFSET,(InitChkrCtrl|0x101U));
        /* Poll the status */
        Timeout = XSTL_CLKMON_TIMEOUT;
        while((Timeout != 0U) && (StatusFlag != 1U)) {
            ClkStatus = XStl_In32(XSTL_CLKMON_STATUS);
            if((ClkStatus & StatusMask) != 0U){
                StatusFlag = 1U;
            }
            Timeout--;
        }
        if(Timeout == 0U) {
            XSTL_FAIL(ErrInfoPtr, XSTL_CLKMON_STS_FAIL, 
                                ClkMonitor, ClkStatus, 0U, 0U, 0U)
        }
        /*
        * If interrupt mode is selected, user has to check the status
        * in his ISR handler, otherwise check here
        */
        if(StatusFlag == 1U) {
            if(IntrEn == 0U) {
                /* Clear Clock mon status */
                XStl_Out32(XSTL_CLKMON_STATUS, StatusMask);
                RetStatus = (u32)XST_SUCCESS;
            }
            else {
                /* Enable the Interrupt */
                XStl_Out32(XSTL_CLKMON_ENABLE, StatusMask);
                /* Wait for ISR handling timeout */
                Timeout = (IntrCntl >> 8U);
                while((Timeout != 0U) && (RetStatus == (u32)XST_FAILURE)) {
                    Timeout--;
                    ClkStatus = XStl_In32(XSTL_CLKMON_STATUS);
                    if((ClkStatus & StatusMask) == 0U) {
                        RetStatus = (u32)XST_SUCCESS;
                    }
                }
                if(RetStatus == (u32)XST_FAILURE) {
                    XSTL_FAIL(ErrInfoPtr, XSTL_CLKMON_IE_FAIL, 
                                            ClkMonitor, ClkStatus, 0U, 0U, 0U)
                }
            }   
    return RetStatus;
}
}
}



