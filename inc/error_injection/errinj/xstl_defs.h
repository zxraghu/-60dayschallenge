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
* @file xstl_defs.h
*  This file contains structures, global variables and Macro definitions
*  that are common for all the STL components
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------  -------- -----------------------------------------------------
* 0.1  Naresh  01/13/2015  Initial creation
* 0.2  Naresh  01/13/2015  Updated to add header file xstatus.h
* 0.3  Naresh  06/11/2015  Added structure XStl_ErrReport for error reporting
* 0.4  Rama    07/17/2015  Fixed violations from MISRA rule checking
* 1.0  Naresh  03/10/2016  Removed static definition for XSTL_DEBUG
* 1.1  Naresh  04/18/2016  Updated file header copyright information
*
* </pre>
*
******************************************************************************/
#ifndef XSTL_DEFS_H     /* prevent circular inclusions */
#define XSTL_DEFS_H     /* by using protection macros */

/***************************** Include Files *********************************/
#include "xil_types.h"
#include "xil_io.h"
//#include "xil_cache.h"
//#include "xil_assert.h"
#include "xstatus.h"

/***************************** Global variables *********************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define XSTL_FAIL(infoptr, errcode, word0, word1, word2, word3, word4) \
                    if (infoptr != NULL) { \
                        infoptr->ErrCode = (u32)errcode; \
                        infoptr->ErrWord0 = (u32)word0; \
                        infoptr->ErrWord1 = (u32)word1; \
                        infoptr->ErrWord2 = (u32)word2; \
                        infoptr->ErrWord3 = (u32)word3; \
                        infoptr->ErrWord4 = (u32)word4; \
                    }

#define XSTL_CLEAR(infoptr) \
                    if (infoptr != NULL) { \
                        infoptr->ErrCode = (u32)0; \
                        infoptr->ErrWord0 = (u32)0; \
                        infoptr->ErrWord1 = (u32)0; \
                        infoptr->ErrWord2 = (u32)0; \
                        infoptr->ErrWord3 = (u32)0; \
                        infoptr->ErrWord4 = (u32)0; \
                    }

/************************** Constant Definitions *****************************/
/** @name Macro to limit value between min and max
 * @{
 */
#define XStl_limit(x,max,min)   (((x)<(min))?(min):(((x)>(max))?(max):(x)))

/**************************** Type Definitions *******************************/
/**
* This typedef contains....
* ErrCode   : Error code indicating which teh STL feature failed
* ErrWord0  : Word-0 of the error information
* ErrWord1  : Word-1 of the error information
* ErrWord2  : Word-2 of the error information
* ErrWord3  : Word-3 of the error information
* ErrWord4  : Word-4 of the error information
*/
typedef struct {
    u32 ErrCode;    /**< Error code indicating which teh STL feature failed */
    u32 ErrWord0;   /**< Word-0 of the error information */
    u32 ErrWord1;   /**< Word-1 of the error information */
    u32 ErrWord2;   /**< Word-2 of the error information */
    u32 ErrWord3;   /**< Word-3 of the error information */
    u32 ErrWord4;   /**< Word-4 of the error information */
} XStl_ErrReport;

/************************** Function Prototypes ******************************/

#endif
