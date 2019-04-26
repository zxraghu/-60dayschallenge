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
* @file xstl_common.h
*  This file contains structures, global variables and Macro definitions
*  required for the common routines
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------  -------- -----------------------------------------------------
* 1.0  Naresh  08/05/2016  Initial creation
* 1.1  Naresh  10/04/2016  Added function prototypes for IOU TX cntr init
*                          and the STL delay routine
* 1.2  Naresh  04/06/2017  Updated to address PR#2497
* 1.3  Naresh  04/18/2017  Updated code to address CR#969232
* </pre>
*
******************************************************************************/
#ifndef XSTL_COMMON_H       /* prevent circular inclusions */
#define XSTL_COMMON_H       /* by using protection macros */

/***************************** Include Files *********************************/

/***************************** Global variables ******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define XSTL_XREG_CP15_CFLR         "p15, 0, %0,  c15,  c3, 0"
#define XSTL_XREG_CP15_CCSIDR       "p15, 1, %0,  c0,  c0, 0"

#define XSTL_REG_RST_LPD_IOU2       0xFF5E0238U
#define XSTL_REG_TS_REF_CTRL        0xFF5E0128U

#define XSTL_CXT_REG_CNTRCTRL       0xFF260000U
#define XSTL_CXT_REG_CNTRSTAT       0xFF260004U
#define XSTL_CXT_REG_CNTRLOW        0xFF260008U
#define XSTL_CXT_REG_CNTRHIGH       0xFF26000CU
#define XSTL_CXT_REG_CNTRFREQ       0xFF260020U

/* Change these parameters manually if the source PLL or PLL freq are changed */
#define XSTL_CXTINIT_PLL_SRC        0U          /* SRCSEL = IOPLL */
#define XSTL_CXTINIT_CLKDIV         0xFU        /* Assuming IOPLL=1500 MHz */
#define XSTL_CXTINIT_FREQ_HZ        0x05F5E100U /* Freq = 100 MHz */

#define XSTL_CXTINIT_WAIT_LOOP      1000U

#define XStl_In32                   Xil_In32
#define XStl_In16                   Xil_In16
#define XStl_In8                    Xil_In8

#define XStl_Out64                  Xil_Out64
#define XStl_Out32                  Xil_Out32
#define XStl_Out16                  Xil_Out16
#define XStl_Out8                   Xil_Out8



/************************** Constant Definitions *****************************/

#endif      /* end of protection macro */
