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
* @file xstl_clkerr.h
*   This file contains data declarations and definitions required for Clockmon
*   error injection
*
* <pre>
* MODIFICATION HISTORY:
*
* * Ver   Who  Date     Changes
* ----- ---- -------- --------------------------------------------------------
* 0.1   Ramadevi    1/20/2015  Initial creation
* 0.2   Ramadevi    1/22/2015  Updated for code inspection results
* 0.3   Ramadevi    3/08/3016  Fixed MISRA-C violations
* 1.0   Ramadevi    4/18/2016  Updated file header copyright information
* 1.1   Ramadevi    5/02/2016  Updated the code as per the design doc ver 1.3
* 1.2   Ramadevi    4/24/2017  Updated code to address CR#974773
*
* </pre>
*
******************************************************************************/
#ifndef XSTL_CLKERR_H       /* prevent circular inclusions */
#define XSTL_CLKERR_H       /* by using protection macros */

/***************************** Include Files *********************************/

/***************************** Global variables ******************************/

/************************** Constant Definitions *****************************/
/** @name Clock monitor error injection registers
 * @{
 */
#define XSTL_CLKMON_STATUS              0xFF5E0140U
#define XSTL_CLKMON_ENABLE              0xFF5E0148U
#define XSTL_CLKMON_DISABLE             0xFF5E014CU
#define XSTL_CLKMON_IMR                 0xFF5E0144U
#define XSTL_CHKR_CLK_BASE              0xFF5E0160U
#define XSTL_CLKA_UPPER_OFFSET          0x00000000U
#define XSTL_CLKA_LOWER_OFFSET          0x00000004U
#define XSTL_CLKB_COUNT_OFFSET          0x00000008U
#define XSTL_CHKR_CTRL_OFFSET           0x0000000CU

/* Error Codes */
#define XSTL_CLKMON_STS_FAIL            0x66U
#define XSTL_CLKMON_IE_FAIL             0x6CU
#define XSTL_CLKMON_INVLD_INPUT_FAIL    0x6DU

#define XSTL_CLKMON_TIMEOUT             0xFFU



/************************** Function prototypes *****************************/
u32 XStl_ClkErrInj(u8 ClkMonitor, u32 ClkBcntVal, u32 IntrCntl,
                                                XStl_ErrReport *ErrInfoPtr);
void XStl_ClrArgList(u32 *ArgListPtr);

#endif
