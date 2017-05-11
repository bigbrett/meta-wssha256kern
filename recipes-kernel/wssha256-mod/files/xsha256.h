// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.4
// Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

#ifndef XSHA256_H
#define XSHA256_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
//#ifndef __linux__
//#include "xil_types.h"
//#include "xil_assert.h"
//#include "xstatus.h"
//#include "xil_io.h"
//#else
//#include <stdint.h>
//#include <assert.h>
//#include <dirent.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/mman.h>
//#include <unistd.h>
//#include <stddef.h>
//#endif
#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <asm/uaccess.h>          // Required for the copy to user function
#include <linux/io.h>
#include "xsha256_hw.h"
#include <linux/types.h>

/**************************** Type Definitions ******************************/
//#ifdef __linux__
//typedef uint8_t u8;
//typedef uint16_t u16;
//typedef uint32_t u32;
//#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XSha256_Config;
//#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XSha256;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XSha256_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XSha256_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XSha256_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XSha256_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    printk(KERN_INFO "assertion\n")
#define Xil_AssertNonvoid(expr) printk(KERN_INFO "assertion\n")
//#define foo(x) ((x) > 32 ? (x) : (2 * (x)))

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XSha256_Initialize(XSha256 *InstancePtr, u16 DeviceId);
XSha256_Config* XSha256_LookupConfig(u16 DeviceId);
int XSha256_CfgInitialize(XSha256 *InstancePtr, XSha256_Config *ConfigPtr);
#else
int XSha256_Initialize(XSha256 *InstancePtr, const char* InstanceName);
int XSha256_Release(XSha256 *InstancePtr);
#endif

void XSha256_Start(XSha256 *InstancePtr);
u32 XSha256_IsDone(XSha256 *InstancePtr);
u32 XSha256_IsIdle(XSha256 *InstancePtr);
u32 XSha256_IsReady(XSha256 *InstancePtr);
void XSha256_EnableAutoRestart(XSha256 *InstancePtr);
void XSha256_DisableAutoRestart(XSha256 *InstancePtr);

void XSha256_Set_base_offset(XSha256 *InstancePtr, u32 Data);
u32 XSha256_Get_base_offset(XSha256 *InstancePtr);
void XSha256_Set_bytes(XSha256 *InstancePtr, u32 Data);
u32 XSha256_Get_bytes(XSha256 *InstancePtr);
u32 XSha256_Get_data_BaseAddress(XSha256 *InstancePtr);
u32 XSha256_Get_data_HighAddress(XSha256 *InstancePtr);
u32 XSha256_Get_data_TotalBytes(XSha256 *InstancePtr);
u32 XSha256_Get_data_BitWidth(XSha256 *InstancePtr);
u32 XSha256_Get_data_Depth(XSha256 *InstancePtr);
u32 XSha256_Write_data_Words(XSha256 *InstancePtr, int offset, int *data, int length);
u32 XSha256_Read_data_Words(XSha256 *InstancePtr, int offset, int *data, int length);
u32 XSha256_Write_data_Bytes(XSha256 *InstancePtr, int offset, char *data, int length);
u32 XSha256_Read_data_Bytes(XSha256 *InstancePtr, int offset, char *data, int length);
u32 XSha256_Get_digest_BaseAddress(XSha256 *InstancePtr);
u32 XSha256_Get_digest_HighAddress(XSha256 *InstancePtr);
u32 XSha256_Get_digest_TotalBytes(XSha256 *InstancePtr);
u32 XSha256_Get_digest_BitWidth(XSha256 *InstancePtr);
u32 XSha256_Get_digest_Depth(XSha256 *InstancePtr);
u32 XSha256_Write_digest_Words(XSha256 *InstancePtr, int offset, int *data, int length);
u32 XSha256_Read_digest_Words(XSha256 *InstancePtr, int offset, int *data, int length);
u32 XSha256_Write_digest_Bytes(XSha256 *InstancePtr, int offset, char *data, int length);
u32 XSha256_Read_digest_Bytes(XSha256 *InstancePtr, int offset, char *data, int length);

void XSha256_InterruptGlobalEnable(XSha256 *InstancePtr);
void XSha256_InterruptGlobalDisable(XSha256 *InstancePtr);
void XSha256_InterruptEnable(XSha256 *InstancePtr, u32 Mask);
void XSha256_InterruptDisable(XSha256 *InstancePtr, u32 Mask);
void XSha256_InterruptClear(XSha256 *InstancePtr, u32 Mask);
u32 XSha256_InterruptGetEnabled(XSha256 *InstancePtr);
u32 XSha256_InterruptGetStatus(XSha256 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
