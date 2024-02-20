/*++

Copyright (c) Microsoft Corporation

Module Name:

    HvGdk.h

Abstract:

    Type definitions for the hypervisor guest interface.

Author:

    Hypervisor Engineering Team (hvet) 01-May-2005

    *** Changes made based on DDK 7, symbols and TLFS 5.0c ***
    Alex Ionescu (@aionescu) 11-Jan-2018

    *** Changes made based on symbols ***
    Alex Ionescu (@aionescu) 28-Dec-2019

    *** Changes made based on new symbol source ***
    Alex Ionescu (@aionescu) 25-Aug-2020
--*/

#if !defined(_HVGDK_)
#define _HVGDK_

#if _MSC_VER > 1000
#pragma once
#endif

#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning(disable:4200) // zero length array
#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4214) // bit field types other than int
#pragma warning(disable:4324) // structure was padded due to __declspec(align())

#define DECLSPEC_ALIGN(x) __declspec(align(x))

//
// Define a 128bit type.
//
typedef struct DECLSPEC_ALIGN(16) _HV_UINT128 {

    unsigned long long  Low64;
    unsigned long long  High64;

} HV_UINT128, *PHV_UINT128;

//
// Define a 256bit type.
//
typedef struct DECLSPEC_ALIGN(32) _HV_UINT256 {

    HV_UINT128  Low128;
    HV_UINT128  High128;

} HV_UINT256, *PHV_UINT256;


//
// Define a 512bit type.
//
typedef struct DECLSPEC_ALIGN(32) _HV_UINT512 {

    HV_UINT256  Low128;
    HV_UINT256  High128;

} HV_UINT512, *PHV_UINT512;

//
// Define an alignment for structures passed via hypercall.
//
#define HV_CALL_ALIGNMENT   8

#define HV_CALL_ATTRIBUTES DECLSPEC_ALIGN(HV_CALL_ALIGNMENT)
#define HV_CALL_ATTRIBUTES_ALIGNED(__alignment__) DECLSPEC_ALIGN(__alignment__)

//
// Memory Types
//
//
// System physical addresses (SPAs) define the physical address space of the underlying
// hardware. There is only one system physical address space for the entire machine.
//
// Guest physical addresses (GPAs) define the guest's view of physical memory.
// GPAs can be mapped to underlying SPAs. There is one guest physical address space per
// partition.
//
// Guest virtual addresses (GVAs) are used within the guest when it enables address
// translation and provides a valid guest page table.
//

typedef unsigned long long HV_SPA, *PHV_SPA;
typedef unsigned long long HV_GPA, *PHV_GPA;
typedef unsigned long long HV_GVA, *PHV_GVA;

#ifndef X64_PAGE_SIZE
#define X64_PAGE_SIZE 0x1000
#endif

#define HV_X64_MAX_PAGE_NUMBER (MAXUINT64/X64_PAGE_SIZE)
#define HV_PAGE_SIZE X64_PAGE_SIZE
#define HV_LARGE_PAGE_SIZE X64_LARGE_PAGE_SIZE
#define HV_PAGE_MASK (HV_PAGE_SIZE - 1)

typedef unsigned long long HV_SPA_PAGE_NUMBER, *PHV_SPA_PAGE_NUMBER;
typedef unsigned long long HV_GPA_PAGE_NUMBER, *PHV_GPA_PAGE_NUMBER;
typedef unsigned long long HV_GVA_PAGE_NUMBER, *PHV_GVA_PAGE_NUMBER;

typedef const HV_SPA_PAGE_NUMBER *PCHV_SPA_PAGE_NUMBER;
typedef const HV_GPA_PAGE_NUMBER *PCHV_GPA_PAGE_NUMBER;
typedef const HV_GVA_PAGE_NUMBER *PCHV_GVA_PAGE_NUMBER;

typedef unsigned short HV_IO_PORT, *PHV_IO_PORT;

//
// Forward declare the loader block.
//
typedef struct _HV_LOADER_BLOCK *PHV_LOADER_BLOCK;
//
// Status codes for hypervisor operations.
//
typedef unsigned short HV_STATUS, *PHV_STATUS;

//
// MessageId: HV_STATUS_SUCCESS
//
// MessageText:
//
// The specified hypercall succeeded
//
#define HV_STATUS_SUCCESS                ((HV_STATUS)0x0000)

//
// MessageId: HV_STATUS_INVALID_HYPERCALL_CODE
//
// MessageText:
//
// The hypervisor does not support the operation because the specified hypercall code is not supported.
//
#define HV_STATUS_INVALID_HYPERCALL_CODE ((HV_STATUS)0x0002)

//
// MessageId: HV_STATUS_INVALID_HYPERCALL_INPUT
//
// MessageText:
//
// The hypervisor does not support the operation because the encoding for the hypercall input register is not supported.
//
#define HV_STATUS_INVALID_HYPERCALL_INPUT ((HV_STATUS)0x0003)

//
// MessageId: HV_STATUS_INVALID_ALIGNMENT
//
// MessageText:
//
// The hypervisor could not perform the operation beacuse a parameter has an invalid alignment.
//
#define HV_STATUS_INVALID_ALIGNMENT      ((HV_STATUS)0x0004)

//
// MessageId: HV_STATUS_INVALID_PARAMETER
//
// MessageText:
//
// The hypervisor could not perform the operation beacuse an invalid parameter was specified.
//
#define HV_STATUS_INVALID_PARAMETER      ((HV_STATUS)0x0005)

//
// MessageId: HV_STATUS_ACCESS_DENIED
//
// MessageText:
//
// Access to the specified object was denied.
//
#define HV_STATUS_ACCESS_DENIED          ((HV_STATUS)0x0006)

//
// MessageId: HV_STATUS_INVALID_PARTITION_STATE
//
// MessageText:
//
// The hypervisor could not perform the operation because the partition is entering or in an invalid state.
//
#define HV_STATUS_INVALID_PARTITION_STATE ((HV_STATUS)0x0007)

//
// MessageId: HV_STATUS_OPERATION_DENIED
//
// MessageText:
//
// The operation is not allowed in the current state.
//
#define HV_STATUS_OPERATION_DENIED       ((HV_STATUS)0x0008)

//
// MessageId: HV_STATUS_UNKNOWN_PROPERTY
//
// MessageText:
//
// The hypervisor does not recognize the specified partition property.
//
#define HV_STATUS_UNKNOWN_PROPERTY       ((HV_STATUS)0x0009)

//
// MessageId: HV_STATUS_PROPERTY_VALUE_OUT_OF_RANGE
//
// MessageText:
//
// The specified value of a partition property is out of range or violates an invariant.
//
#define HV_STATUS_PROPERTY_VALUE_OUT_OF_RANGE ((HV_STATUS)0x000A)

//
// MessageId: HV_STATUS_INSUFFICIENT_MEMORY
//
// MessageText:
//
// There is not enough memory in the hypervisor pool to complete the operation.
//
#define HV_STATUS_INSUFFICIENT_MEMORY    ((HV_STATUS)0x000B)

//
// MessageId: HV_STATUS_PARTITION_TOO_DEEP
//
// MessageText:
//
// The maximum partition depth has been exceeded for the partition hierarchy.
//
#define HV_STATUS_PARTITION_TOO_DEEP     ((HV_STATUS)0x000C)

//
// MessageId: HV_STATUS_INVALID_PARTITION_ID
//
// MessageText:
//
// A partition with the specified partition Id does not exist.
//
#define HV_STATUS_INVALID_PARTITION_ID   ((HV_STATUS)0x000D)

//
// MessageId: HV_STATUS_INVALID_VP_INDEX
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified VP index is invalid.
//
#define HV_STATUS_INVALID_VP_INDEX       ((HV_STATUS)0x000E)

//
// MessageId: HV_STATUS_NOT_FOUND
//
// MessageText:
//
// The iteration is complete; no addition items in the iteration could be found.
//
#define HV_STATUS_NOT_FOUND              ((HV_STATUS)0x0010)

//
// MessageId: HV_STATUS_INVALID_PORT_ID
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified port identifier is invalid.
//
#define HV_STATUS_INVALID_PORT_ID        ((HV_STATUS)0x0011)

//
// MessageId: HV_STATUS_INVALID_CONNECTION_ID
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified connection identifier is invalid.
//
#define HV_STATUS_INVALID_CONNECTION_ID  ((HV_STATUS)0x0012)

//
// MessageId: HV_STATUS_INSUFFICIENT_BUFFERS
//
// MessageText:
//
// You did not supply enough message buffers to send a message.
//
#define HV_STATUS_INSUFFICIENT_BUFFERS   ((HV_STATUS)0x0013)

//
// MessageId: HV_STATUS_NOT_ACKNOWLEDGED
//
// MessageText:
//
// The previous virtual interrupt has not been acknowledged.
//
#define HV_STATUS_NOT_ACKNOWLEDGED       ((HV_STATUS)0x0014)

//
// MessageId: HV_STATUS_INVALID_VP_STATE
//
// MessageText:
//
// A virtual processor is not in the correct state for the performance of the indicated operation.
//
#define HV_STATUS_INVALID_VP_STATE       ((HV_STATUS)0x0015)

//
// MessageId: HV_STATUS_ACKNOWLEDGED
//
// MessageText:
//
// The previous virtual interrupt has already been acknowledged.
//
#define HV_STATUS_ACKNOWLEDGED           ((HV_STATUS)0x0016)

//
// MessageId: HV_STATUS_INVALID_SAVE_RESTORE_STATE
//
// MessageText:
//
// The indicated partition is not in a valid state for saving or restoring.
//
#define HV_STATUS_INVALID_SAVE_RESTORE_STATE ((HV_STATUS)0x0017)

//
// MessageId: HV_STATUS_INVALID_SYNIC_STATE
//
// MessageText:
//
// The hypervisor could not complete the operation because a required feature of the synthetic interrupt controller (SynIC) was disabled.
//
#define HV_STATUS_INVALID_SYNIC_STATE    ((HV_STATUS)0x0018)

//
// MessageId: HV_STATUS_OBJECT_IN_USE
//
// MessageText:
//
// The hypervisor could not perform the operation because the object or value was either already in use or being used for a purpose that would not permit completing the operation.
//
#define HV_STATUS_OBJECT_IN_USE          ((HV_STATUS)0x0019)

//
// MessageId: HV_STATUS_INVALID_PROXIMITY_DOMAIN_INFO
//
// MessageText:
//
// The proximity domain information is invalid.
//
#define HV_STATUS_INVALID_PROXIMITY_DOMAIN_INFO ((HV_STATUS)0x001A)

//
// MessageId: HV_STATUS_NO_DATA
//
// MessageText:
//
// An attempt to retrieve debugging data failed because none was available.
//
#define HV_STATUS_NO_DATA                ((HV_STATUS)0x001B)

//
// MessageId: HV_STATUS_INACTIVE
//
// MessageText:
//
// The physical connection being used for debuggging has not recorded any receive activity since the last operation.
//
#define HV_STATUS_INACTIVE               ((HV_STATUS)0x001C)

//
// MessageId: HV_STATUS_NO_RESOURCES
//
// MessageText:
//
// There are not enough resources to complete the operation.
//
#define HV_STATUS_NO_RESOURCES           ((HV_STATUS)0x001D)

//
// MessageId: HV_STATUS_FEATURE_UNAVAILABLE
//
// MessageText:
//
// A hypervisor feature is not available to the user.
//
#define HV_STATUS_FEATURE_UNAVAILABLE    ((HV_STATUS)0x001E)

//
// MessageId: HV_STATUS_PARTIAL_PACKET
//
// MessageText:
//
// The debug packet returned is only a partial packet due to an io error.
//
#define HV_STATUS_PARTIAL_PACKET         ((HV_STATUS)0x001F)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SSE3_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (SSE3).
//
#define HV_STATUS_PROCESSOR_FEATURE_SSE3_NOT_SUPPORTED ((HV_STATUS)0x0020)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_LAHFSAHF_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (LAHFSAHF).
//
#define HV_STATUS_PROCESSOR_FEATURE_LAHFSAHF_NOT_SUPPORTED ((HV_STATUS)0x0021)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SSSE3_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (SSSE3).
//
#define HV_STATUS_PROCESSOR_FEATURE_SSSE3_NOT_SUPPORTED ((HV_STATUS)0x0022)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SSE4_1_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (SSE4.1).
//
#define HV_STATUS_PROCESSOR_FEATURE_SSE4_1_NOT_SUPPORTED ((HV_STATUS)0x0023)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SSE4_2_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (SSE4.2).
//
#define HV_STATUS_PROCESSOR_FEATURE_SSE4_2_NOT_SUPPORTED ((HV_STATUS)0x0024)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SSE4A_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (SSE4a).
//
#define HV_STATUS_PROCESSOR_FEATURE_SSE4A_NOT_SUPPORTED ((HV_STATUS)0x0025)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SSE5_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (SSE5).
//
#define HV_STATUS_PROCESSOR_FEATURE_SSE5_NOT_SUPPORTED ((HV_STATUS)0x0026)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_POPCNT_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (POPCNT).
//
#define HV_STATUS_PROCESSOR_FEATURE_POPCNT_NOT_SUPPORTED ((HV_STATUS)0x0027)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_CMPXCHG16B_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (CMPXCHG16B).
//
#define HV_STATUS_PROCESSOR_FEATURE_CMPXCHG16B_NOT_SUPPORTED ((HV_STATUS)0x0028)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_ALTMOVCR8_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (ALTMOVCR8).
//
#define HV_STATUS_PROCESSOR_FEATURE_ALTMOVCR8_NOT_SUPPORTED ((HV_STATUS)0x0029)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_LZCNT_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (LZCNT).
//
#define HV_STATUS_PROCESSOR_FEATURE_LZCNT_NOT_SUPPORTED ((HV_STATUS)0x002A)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_MISALIGNED_SSE_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (misaligned SSE).
//
#define HV_STATUS_PROCESSOR_FEATURE_MISALIGNED_SSE_NOT_SUPPORTED ((HV_STATUS)0x002B)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_MMX_EXT_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (MMX EXT).
//
#define HV_STATUS_PROCESSOR_FEATURE_MMX_EXT_NOT_SUPPORTED ((HV_STATUS)0x002C)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_3DNOW_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (3DNow!).
//
#define HV_STATUS_PROCESSOR_FEATURE_3DNOW_NOT_SUPPORTED ((HV_STATUS)0x002D)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_EXTENDED_3DNOW_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (extended 3DNow!).
//
#define HV_STATUS_PROCESSOR_FEATURE_EXTENDED_3DNOW_NOT_SUPPORTED ((HV_STATUS)0x002E)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_PAGE_1GB_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (1GB pages).
//
#define HV_STATUS_PROCESSOR_FEATURE_PAGE_1GB_NOT_SUPPORTED ((HV_STATUS)0x002F)

//
// MessageId: HV_STATUS_PROCESSOR_CACHE_LINE_FLUSH_SIZE_INCOMPATIBLE
//
// MessageText:
//
// The supplied restore state requires requires a processor with a different
// cache line flush size.
//
#define HV_STATUS_PROCESSOR_CACHE_LINE_FLUSH_SIZE_INCOMPATIBLE ((HV_STATUS)0x0030)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_XSAVE_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (XSAVE).
//
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_NOT_SUPPORTED ((HV_STATUS)0x0031)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_XSAVE_XSAVEOPT_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (XSAVEOPT).
//
#define HV_STATUS_PROCESSOR_FEATURE_XSAVEOPT_NOT_SUPPORTED ((HV_STATUS)0x0032)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_XSAVE_LEGACY_SSE_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (XSAVE Legacy SSE).
//
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_LEGACY_SSE_NOT_SUPPORTED ((HV_STATUS)0x0033)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_XSAVE_AVX_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (XSAVE AVX).
//
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_AVX_NOT_SUPPORTED ((HV_STATUS)0x0034)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_XSAVE_UNKNOWN_FEATURE_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor
// processor feature (XSAVE unknown feature).
//
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_UNKNOWN_FEATURE_NOT_SUPPORTED ((HV_STATUS)0x0035)

//
// MessageId: HV_STATUS_PROCESSOR_XSAVE_SAVE_AREA_INCOMPATIBLE
//
// MessageText:
//
// The supplied restore state is incompatible with the processor's XSAVE save
// layout.
//
#define HV_STATUS_PROCESSOR_XSAVE_SAVE_AREA_INCOMPATIBLE ((HV_STATUS)0x0036)

//
// MessageId: HV_STATUS_INCOMPATIBLE_PROCESSOR
//
// MessageText:
//
// The supplied restore state is for an incompatible processor
// vendor.
//
#define HV_STATUS_INCOMPATIBLE_PROCESSOR ((HV_STATUS)0x0037)

//
// MessageId: HV_STATUS_INSUFFICIENT_DEVICE_DOMAINS
//
// MessageText:
//
// The maximum number of domains supported by the platform I/O remapping
// hardware is currently in use.
//
#define HV_STATUS_INSUFFICIENT_DEVICE_DOMAINS ((HV_STATUS)0x0038)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_AES_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (AES).
//
#define HV_STATUS_PROCESSOR_FEATURE_AES_NOT_SUPPORTED   ((HV_STATUS)0x0039)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_PCLMULQDQ_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (PCLMULQDQ).
//
#define HV_STATUS_PROCESSOR_FEATURE_PCLMULQDQ_NOT_SUPPORTED ((HV_STATUS)0x003A)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_INCOMPATIBLE_XSAVE_FEATURES
//
// MessageText:
//
// The supplied restore state enables incompatible XSAVE features.
// (Enabling AVX without XSAVE / enabling XSAVEOPT without XSAVE)
//
#define HV_STATUS_PROCESSOR_FEATURE_INCOMPATIBLE_XSAVE_FEATURES ((HV_STATUS)0x003B)

//
// MessageId: HV_STATUS_CPUID_FEATURE_VALIDATION_ERROR
//
// MessageText:
//
// Generic logical processor CPUID feature set validation error.
//
#define HV_STATUS_CPUID_FEATURE_VALIDATION_ERROR ((HV_STATUS)0x003C)

//
// MessageId: HV_STATUS_CPUID_XSAVE_FEATURE_VALIDATION_ERROR
//
// MessageText:
//
// CPUID XSAVE feature validation error.
//
#define HV_STATUS_CPUID_XSAVE_FEATURE_VALIDATION_ERROR ((HV_STATUS)0x003D)

//
// MessageId: HV_STATUS_PROCESSOR_STARTUP_TIMEOUT
//
// MessageText:
//
// Processor startup timed out.
//
#define HV_STATUS_PROCESSOR_STARTUP_TIMEOUT ((HV_STATUS)0x003E)

//
// MessageId: HV_STATUS_SMX_ENABLED
//
// MessageText:
//
// SMX enabled by the BIOS.
//
#define HV_STATUS_SMX_ENABLED ((HV_STATUS)0x003F)

//
// MessageId: HV_STATUS_INVALID_LP_INDEX
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified LP index is invalid.
//
#define HV_STATUS_INVALID_LP_INDEX ((HV_STATUS)0x0041)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_FMA4_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (FMA4).
//
#define HV_STATUS_PROCESSOR_FEATURE_FMA4_NOT_SUPPORTED   ((HV_STATUS)0x0042)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_F16C_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (F16C).
//
#define HV_STATUS_PROCESSOR_FEATURE_F16C_NOT_SUPPORTED   ((HV_STATUS)0x0043)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_RDRAND_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (RDRAND).
//
#define HV_STATUS_PROCESSOR_FEATURE_RDRAND_NOT_SUPPORTED   ((HV_STATUS)0x0044)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_RDWRFSGS_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (Read/Write FS/GS).
//
#define HV_STATUS_PROCESSOR_FEATURE_RDWRFSGS_NOT_SUPPORTED   ((HV_STATUS)0x0045)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SMEP_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (SMEP).
//
#define HV_STATUS_PROCESSOR_FEATURE_SMEP_NOT_SUPPORTED   ((HV_STATUS)0x0046)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_ENHANCED_FAST_STRING_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (AES).
//
#define HV_STATUS_PROCESSOR_FEATURE_ENHANCED_FAST_STRING_NOT_SUPPORTED   ((HV_STATUS)0x0047)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_MOVBE_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (MOVBE).
//
#define HV_STATUS_PROCESSOR_FEATURE_MOVBE_NOT_SUPPORTED   ((HV_STATUS)0x0048)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_BMI2_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (BMI1).
//
#define HV_STATUS_PROCESSOR_FEATURE_BMI1_NOT_SUPPORTED   ((HV_STATUS)0x0049)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_BMI2_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (BMI2).
//
#define HV_STATUS_PROCESSOR_FEATURE_BMI2_NOT_SUPPORTED   ((HV_STATUS)0x004A)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_HLE_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (HLE).
//
#define HV_STATUS_PROCESSOR_FEATURE_HLE_NOT_SUPPORTED   ((HV_STATUS)0x004B)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_RTM_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (RTM).
//
#define HV_STATUS_PROCESSOR_FEATURE_RTM_NOT_SUPPORTED   ((HV_STATUS)0x004C)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_XSAVE_FMA_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (FMA).
//
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_FMA_NOT_SUPPORTED   ((HV_STATUS)0x004D)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_AVX2_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (AVX2).
//
#define HV_STATUS_PROCESSOR_FEATURE_AVX2_NOT_SUPPORTED   ((HV_STATUS)0x004E)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_NPIEP1_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (NPIEP1).
//
#define HV_STATUS_PROCESSOR_FEATURE_NPIEP1_NOT_SUPPORTED   ((HV_STATUS)0x004F)

//
// MessageId: HV_STATUS_INVALID_REGISTER_VALUE
//
// MessageText:
//
// The supplied register value is invalid.
//
#define HV_STATUS_INVALID_REGISTER_VALUE ((HV_STATUS)0x0050)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_RDSEED_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (RDSEED).
//
#define HV_STATUS_PROCESSOR_FEATURE_RDSEED_NOT_SUPPORTED   ((HV_STATUS)0x0052)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_ADX_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (ADX).
//
#define HV_STATUS_PROCESSOR_FEATURE_ADX_NOT_SUPPORTED   ((HV_STATUS)0x0053)

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_SMAP_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (SMAP).
//
#define HV_STATUS_PROCESSOR_FEATURE_SMAP_NOT_SUPPORTED   ((HV_STATUS)0x0054)

//
// MessageId: HV_STATUS_NX_NOT_DETECTED
//
// MessageText:
//
// NX not detected on the machine.
//
#define HV_STATUS_NX_NOT_DETECTED ((HV_STATUS)(0x0055))

//
// MessageId: HV_STATUS_PROCESSOR_FEATURE_INTEL_PREFETCH_NOT_SUPPORTED
//
// MessageText:
//
// The supplied restore state requires an unsupported processor feature
// (Intel Prefetch).
//
#define HV_STATUS_PROCESSOR_FEATURE_INTEL_PREFETCH_NOT_SUPPORTED   ((HV_STATUS)0x0056)

//
// MessageId: HV_STATUS_INVALID_DEVICE_ID
//
// MessageText:
//
// The supplied device ID is invalid.
//
#define HV_STATUS_INVALID_DEVICE_ID ((HV_STATUS)0x0057)

//
// MessageId: HV_STATUS_INVALID_DEVICE_STATE
//
// MessageText:
//
// The operation is not allowed in the current device state.
//
#define HV_STATUS_INVALID_DEVICE_STATE ((HV_STATUS)0x0058)

//
// MessageId: HV_STATUS_PENDING_PAGE_REQUESTS
//
// MessageText:
//
// The device had pending page requests which were discarded.
//
#define HV_STATUS_PENDING_PAGE_REQUESTS ((HV_STATUS)0x0059)

//
// MessageId: HV_STATUS_PAGE_REQUEST_INVALID
//
// MessageText:
//
// The supplied page request specifies a memory access that the guest does not
// have permissions to perform.
//
#define HV_STATUS_PAGE_REQUEST_INVALID ((HV_STATUS)0x0060)

//
// MessageId: HV_STATUS_OPERATION_FAILED
//
// MessageText:
//
// The requested operation failed.
//
#define HV_STATUS_OPERATION_FAILED       ((HV_STATUS)0x0071)

//
// MessageId: HV_STATUS_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE
//
// MessageText:
//
// The requested operation is not allowed due to one or more virtual processors
// having nested virtualization active.
//
#define HV_STATUS_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE  ((HV_STATUS)0x0072)

//
// MessageId: HV_STATUS_UNSUCCESSFUL
//
// MessageText:
//
// {Operation Failed}
// The requested operation was unsuccessful.
//
#define HV_STATUS_UNSUCCESSFUL           ((HV_STATUS)0x1001)

//
// MessageId: HV_STATUS_INSUFFICIENT_BUFFER
//
// MessageText:
//
// The specified buffer was too small to contain all of the requested data.
//
#define HV_STATUS_INSUFFICIENT_BUFFER    ((HV_STATUS)0x1002)

//
// MessageId: HV_STATUS_GPA_NOT_PRESENT
//
// MessageText:
//
// The guest physical address is not currently associated with a system physical address.
//
#define HV_STATUS_GPA_NOT_PRESENT        ((HV_STATUS)0x1003)

//
// MessageId: HV_STATUS_GUEST_PAGE_FAULT
//
// MessageText:
//
// The operation would have resulted in a page fault in the guest.
//
#define HV_STATUS_GUEST_PAGE_FAULT       ((HV_STATUS)0x1004)

//
// MessageId: HV_STATUS_RUNDOWN_DISABLED
//
// MessageText:
//
// The operation cannot proceed as the rundown object was marked disabled.
//
#define HV_STATUS_RUNDOWN_DISABLED       ((HV_STATUS)0x1005)

//
// MessageId: HV_STATUS_KEY_ALREADY_EXISTS
//
// MessageText:
//
// The entry cannot be added as another entry with the same key already exists.
//
#define HV_STATUS_KEY_ALREADY_EXISTS     ((HV_STATUS)0x1006)

//
// MessageId: HV_STATUS_GPA_INTERCEPT
//
// MessageText:
//
// The operation resulted an intercept on a region of guest physical memory.
//
#define HV_STATUS_GPA_INTERCEPT          ((HV_STATUS)0x1007)

//
// MessageId: HV_STATUS_GUEST_GENERAL_PROTECTION_FAULT
//
// MessageText:
//
// The operation would have resulted in a general protection fault in the guest.
//
#define HV_STATUS_GUEST_GENERAL_PROTECTION_FAULT ((HV_STATUS)0x1008)

//
// MessageId: HV_STATUS_GUEST_STACK_FAULT
//
// MessageText:
//
// The operation would have resulted in a stack fault in the guest.
//
#define HV_STATUS_GUEST_STACK_FAULT      ((HV_STATUS)0x1009)

//
// MessageId: HV_STATUS_GUEST_INVALID_OPCODE_FAULT
//
// MessageText:
//
// The operation would have resulted in an invalid opcode fault in the guest.
//
#define HV_STATUS_GUEST_INVALID_OPCODE_FAULT ((HV_STATUS)0x100A)

//
// MessageId: HV_STATUS_FINALIZE_INCOMPLETE
//
// MessageText:
//
// The partition is not completely finalized.
//
#define HV_STATUS_FINALIZE_INCOMPLETE    ((HV_STATUS)0x100B)

//
// MessageId: HV_STATUS_GUEST_MACHINE_CHECK_ABORT
//
// MessageText:
//
// The operation would have resulted in an machine check abort in the guest.
//
#define HV_STATUS_GUEST_MACHINE_CHECK_ABORT ((HV_STATUS)0x100C)

//
// MessageId: HV_STATUS_ILLEGAL_OVERLAY_ACCESS
//
// MessageText:
//
// An illegal access was attempted to an overlay page.
//
#define HV_STATUS_ILLEGAL_OVERLAY_ACCESS ((HV_STATUS)0x100D)

//
// MessageId: HV_STATUS_INSUFFICIENT_SYSTEM_VA
//
// MessageText:
//
// There is not enough system VA space available to satisfy the request,
//
#define HV_STATUS_INSUFFICIENT_SYSTEM_VA ((HV_STATUS)0x100E)

//
// MessageId: HV_STATUS_VIRTUAL_ADDRESS_NOT_MAPPED
//
// MessageText:
//
// The passed virtual address was not mapped in the hypervisor address space.
//
#define HV_STATUS_VIRTUAL_ADDRESS_NOT_MAPPED ((HV_STATUS)0x100F)

//
// MessageId: HV_STATUS_NOT_IMPLEMENTED
//
// MessageText:
//
// The requested operation is not implemented in this version of the hypervisor.
//
#define HV_STATUS_NOT_IMPLEMENTED        ((HV_STATUS)0x1010)

//
// MessageId: HV_STATUS_VMX_INSTRUCTION_FAILED
//
// MessageText:
//
// The requested VMX instruction failed to complete succesfully.
//
#define HV_STATUS_VMX_INSTRUCTION_FAILED ((HV_STATUS)0x1011)

//
// MessageId: HV_STATUS_VMX_INSTRUCTION_FAILED_WITH_STATUS
//
// MessageText:
//
// The requested VMX instruction failed to complete succesfully indicating status.
//
#define HV_STATUS_VMX_INSTRUCTION_FAILED_WITH_STATUS ((HV_STATUS)0x1012)

//
// MessageId: HV_STATUS_MSR_ACCESS_FAILED
//
// MessageText:
//
// The requested access to the model specific register failed.
//
#define HV_STATUS_MSR_ACCESS_FAILED      ((HV_STATUS)0x1013)

//
// MessageId: HV_STATUS_CR_ACCESS_FAILED
//
// MessageText:
//
// The requested access to the control register failed.
//
#define HV_STATUS_CR_ACCESS_FAILED       ((HV_STATUS)0x1014)

//
// MessageId: HV_STATUS_TIMEOUT
//
// MessageText:
//
// The specified timeout expired before the operation completed.
//
#define HV_STATUS_TIMEOUT                ((HV_STATUS)0x1016)

//
// MessageId: HV_STATUS_MSR_INTERCEPT
//
// MessageText:
//
// The requested access to the model specific register generated an intercept.
//
#define HV_STATUS_MSR_INTERCEPT          ((HV_STATUS)0x1017)

//
// MessageId: HV_STATUS_CPUID_INTERCEPT
//
// MessageText:
//
// The CPUID instruction generated an intercept.
//
#define HV_STATUS_CPUID_INTERCEPT        ((HV_STATUS)0x1018)

//
// MessageId: HV_STATUS_REPEAT_INSTRUCTION
//
// MessageText:
//
// The current instruction should be repeated and the instruction pointer not advanced.
//
#define HV_STATUS_REPEAT_INSTRUCTION     ((HV_STATUS)0x1019)

//
// MessageId: HV_STATUS_PAGE_PROTECTION_VIOLATION
//
// MessageText:
//
// The current instruction should be repeated and the instruction pointer not advanced.
//
#define HV_STATUS_PAGE_PROTECTION_VIOLATION ((HV_STATUS)0x101A)

//
// MessageId: HV_STATUS_PAGE_TABLE_INVALID
//
// MessageText:
//
// The current instruction should be repeated and the instruction pointer not advanced.
//
#define HV_STATUS_PAGE_TABLE_INVALID     ((HV_STATUS)0x101B)

//
// MessageId: HV_STATUS_PAGE_NOT_PRESENT
//
// MessageText:
//
// The current instruction should be repeated and the instruction pointer not advanced.
//
#define HV_STATUS_PAGE_NOT_PRESENT       ((HV_STATUS)0x101C)

//
// MessageId: HV_STATUS_IO_INTERCEPT
//
// MessageText:
//
// The requested access to the I/O port generated an intercept.
//
#define HV_STATUS_IO_INTERCEPT           ((HV_STATUS)0x101D)

//
// MessageId: HV_STATUS_NOTHING_TO_DO
//
// MessageText:
//
// There is nothing to do.
//
#define HV_STATUS_NOTHING_TO_DO          ((HV_STATUS)0x101E)

//
// MessageId: HV_STATUS_THREAD_TERMINATING
//
// MessageText:
//
// The requested thread is terminating.
//
#define HV_STATUS_THREAD_TERMINATING     ((HV_STATUS)0x101F)

//
// MessageId: HV_STATUS_SECTION_ALREADY_CONSTRUCTED
//
// MessageText:
//
// The specified section was already constructed.
//
#define HV_STATUS_SECTION_ALREADY_CONSTRUCTED ((HV_STATUS)0x1020)

//
// MessageId: HV_STATUS_SECTION_NOT_ALREADY_CONSTRUCTED
//
// MessageText:
//
// The specified section was not already constructed.
//
#define HV_STATUS_SECTION_NOT_ALREADY_CONSTRUCTED ((HV_STATUS)0x1021)

//
// MessageId: HV_STATUS_PAGE_ALREADY_COMMITTED
//
// MessageText:
//
// The specified virtual address was already backed by physical memory.
//
#define HV_STATUS_PAGE_ALREADY_COMMITTED ((HV_STATUS)0x1022)

//
// MessageId: HV_STATUS_PAGE_NOT_ALREADY_COMMITTED
//
// MessageText:
//
// The specified virtual address was not already backed by physical memory.
//
#define HV_STATUS_PAGE_NOT_ALREADY_COMMITTED ((HV_STATUS)0x1023)

//
// MessageId: HV_STATUS_COMMITTED_PAGES_REMAIN
//
// MessageText:
//
// Committed pages remain in the section.
//
#define HV_STATUS_COMMITTED_PAGES_REMAIN ((HV_STATUS)0x1024)

//
// MessageId: HV_STATUS_NO_REMAINING_COMMITTED_PAGES
//
// MessageText:
//
// No additional committed pages beyond the specified page exist in the section.
//
#define HV_STATUS_NO_REMAINING_COMMITTED_PAGES ((HV_STATUS)0x1025)

//
// MessageId: HV_STATUS_INSUFFICIENT_COMPARTMENT_VA
//
// MessageText:
//
// The VA space of the compartment is exhausted.
//
#define HV_STATUS_INSUFFICIENT_COMPARTMENT_VA ((HV_STATUS)0x1026)

//
// MessageId: HV_STATUS_INSUFFICIENT_CROM_SPACE
//
// MessageText:
//
// Insufficient space existed for copying over the CROM contents.
//
#define HV_STATUS_INSUFFICIENT_CROM_SPACE ((HV_STATUS)0x2000)

//
// MessageId: HV_STATUS_BAD_CROM_FORMAT
//
// MessageText:
//
// The contents of the CROM failed validation attempts.
//
#define HV_STATUS_BAD_CROM_FORMAT        ((HV_STATUS)0x2001)

//
// MessageId: HV_STATUS_UNSUPPORTED_CROM_FORMAT
//
// MessageText:
//
// The contents of the CROM contain contents the parser doesn't support.
//
#define HV_STATUS_UNSUPPORTED_CROM_FORMAT ((HV_STATUS)0x2002)

//
// MessageId: HV_STATUS_UNSUPPORTED_CONTROLLER
//
// MessageText:
//
// The register format of the OHCI controller specified for debugging is not supported.
//
#define HV_STATUS_UNSUPPORTED_CONTROLLER ((HV_STATUS)0x2003)

//
// MessageId: HV_STATUS_CROM_TOO_LARGE
//
// MessageText:
//
// The CROM contents were to large to copy over.
//
#define HV_STATUS_CROM_TOO_LARGE         ((HV_STATUS)0x2004)

//
// MessageId: HV_STATUS_CONTROLLER_IN_USE
//
// MessageText:
//
// The OHCI controller specified for debugging cannot be used as it is already in use.
//
#define HV_STATUS_CONTROLLER_IN_USE      ((HV_STATUS)0x2005)

//
// Time in the hypervisor is measured in 100 nanosecond units
//
typedef unsigned long long HV_NANO100_TIME, *PHV_NANO100_TIME;
typedef unsigned long long HV_NANO100_DURATION, *PHV_NANO100_DURATION;

//
// An architecture is a set of processor instruction sets and operating modes
//

typedef enum _HV_ARCHITECTURE
{
    HvArchitectureX64,
    HvArchitectureX86,
    HvArchitectureARM64,
    HvArchitectureMaximum
} HV_ARCHITECTURE, *PHV_ARCHITECTURE;

typedef union _HV_X64_FP_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        unsigned long long Mantissa;
        unsigned long long BiasedExponent:15;
        unsigned long long Sign:1;
        unsigned long long Reserved:48;
    };
} HV_X64_FP_REGISTER, *PHV_X64_FP_REGISTER;

typedef union _HV_X64_FP_CONTROL_STATUS_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        unsigned short FpControl;
        unsigned short FpStatus;
        unsigned char  FpTag;
        unsigned char  IgnNe:1;
        unsigned char  Reserved:7;
        unsigned short LastFpOp;
        union
        {
            // Long Mode
            unsigned long long LastFpRip;
            // 32 Bit Mode
            struct
            {
                unsigned long LastFpEip;
                unsigned short LastFpCs;
            };
        };
    };
} HV_X64_FP_CONTROL_STATUS_REGISTER, *PHV_X64_FP_CONTROL_STATUS_REGISTER;

typedef union _HV_X64_XMM_CONTROL_STATUS_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        union
        {
            // Long Mode
            unsigned long long LaftFpRdp;
            // 32 Bit Mode
            struct
            {
                unsigned long LastFpDp;
                unsigned short LastFpDs;
            };
        };
        unsigned long XmmStatusControl;
        unsigned long XmmStatusControlMask;
    };
} HV_X64_XMM_CONTROL_STATUS_REGISTER, *PHV_X64_XMM_CONTROL_STATUS_REGISTER;

typedef struct _HV_X64_SEGMENT_REGISTER
{
    unsigned long long Base;
    unsigned long Limit;
    unsigned short Selector;
    union
    {
        struct
        {
            unsigned short SegmentType:4;
            unsigned short NonSystemSegment:1;
            unsigned short DescriptorPrivilegeLevel:2;
            unsigned short Present:1;
            unsigned short Reserved:4;
            unsigned short Available:1;
            unsigned short Long:1;
            unsigned short Default:1;
            unsigned short Granularity:1;
        };
        unsigned short Attributes;
    };

} HV_X64_SEGMENT_REGISTER, *PHV_X64_SEGMENT_REGISTER;

typedef struct _HV_X64_TABLE_REGISTER
{
    unsigned short     Pad[3];
    unsigned short     Limit;
    unsigned long long     Base;
} HV_X64_TABLE_REGISTER, *PHV_X64_TABLE_REGISTER;

typedef union _HV_X64_FP_MMX_REGISTER
{
    HV_UINT128          AsUINT128;
    HV_X64_FP_REGISTER  Fp;
    unsigned long long              Mmx;
} HV_X64_FP_MMX_REGISTER, *PHV_X64_FP_MMX_REGISTER;

//
// The FX Save Area is defined to be 512 bytes in size
//
#define HV_X64_FXSAVE_AREA_SIZE  512

//
// FX registers are legacy extended state registers managed
// by the FXSAVE and and FXRSTOR instructions. This includes
// leagacy FP and SSE registers.
//
typedef DECLSPEC_ALIGN(16) union _HV_X64_FX_REGISTERS
{
    struct
    {
        HV_X64_FP_CONTROL_STATUS_REGISTER   FpControlStatus;
        HV_X64_XMM_CONTROL_STATUS_REGISTER  XmmControlStatus;
        HV_X64_FP_MMX_REGISTER              FpMmx[8];
        HV_UINT128                          Xmm[16];
    };

    //
    // The FX Save Area is defined to be 512 bytes in size
    //
    unsigned char FxSaveArea[HV_X64_FXSAVE_AREA_SIZE];

} HV_X64_FX_REGISTERS, *PHV_X64_FX_REGISTERS;

//
// XSAVE erea definitions.
//

//
// The XSAVE XFEM (XSAVE Feature Enabled Mask) register.
//
typedef union _HV_X64_XSAVE_XFEM_REGISTER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long LegacyX87 : 1;
        unsigned long long LegacySse : 1;
        unsigned long long Avx : 1;
        unsigned long long MpxBndreg : 1;
        unsigned long long MpxBndcsr : 1;
        unsigned long long Avx512Opmask : 1;
        unsigned long long Avx512Zmmhi : 1;
        unsigned long long Avx512Zmm16_31 : 1;
        unsigned long long Reserved : 56;
    };
} HV_X64_XSAVE_XFEM_REGISTER, *PHV_X64_XSAVE_XFEM_REGISTER;

//
// This structure represents the header area of an XSAVE area.
// This must be alligned on a 64 byte boundary.
//
typedef struct DECLSPEC_ALIGN(64) _HV_X64_XSAVE_HEADER
{
    //
    // Bit vector indicating which features have state store in the XSAVE
    // area.
    //
    HV_X64_XSAVE_XFEM_REGISTER  XstateBv;          // Bit 63 MBZ
    HV_X64_XSAVE_XFEM_REGISTER  XcompBv;

    unsigned long long  Reserved2;
    unsigned long long  Reserved3;

    unsigned long long  Reserved4;
    unsigned long long  Reserved5;

    unsigned long long  Reserved6;
    unsigned long long  Reserved7;
} HV_X64_XSAVE_HEADER, *PHV_X64_XSAVE_HEADER;

//
// This is the size of the legacy save area (512) plus the size of the
// XSAVE header (64) plus the size of the AVX context (16 128-bit
// registers.
//
#define HV_X64_XSAVE_AREA_HEADER_SIZE  64
#define HV_X64_XSAVE_AREA_AVX_SIZE     256
#define HV_X64_XSAVE_AREA_SIZE         (HV_X64_FXSAVE_AREA_SIZE + HV_X64_XSAVE_AREA_HEADER_SIZE + HV_X64_XSAVE_AREA_AVX_SIZE)

//
// This structure defines the format of the XSAVE save area, the area
// used to save and restore the context of processor extended state
// (including legacy FP and SSE state) by the XSAVE and XRSTOR instructions.
//
// N.B. The XSAVE header must be aligned on a 64 byte boundary. Therefore
// this structure must be 64 byte aligned,
//
typedef union DECLSPEC_ALIGN(64) _HV_X64_X_REGISTERS
{
    struct
    {
        HV_X64_FP_CONTROL_STATUS_REGISTER   FpControlStatus;
        HV_X64_XMM_CONTROL_STATUS_REGISTER  XmmControlStatus;
        HV_X64_FP_MMX_REGISTER              FpMmx[8];
        HV_UINT128                          Xmm[16];
        HV_UINT128                          Reserved[6];
        HV_X64_XSAVE_HEADER                 Header;
    };

    unsigned char XSaveArea[HV_X64_XSAVE_AREA_SIZE];
} HV_X64_X_REGISTERS, *PHV_X64_X_REGISTERS;

typedef struct _HV_X64_CONTEXT
{

    //
    // The Initial APIC ID pseudo register. This is the value returned
    // by CPUID.
    //
    unsigned long long InitialApicId;

    //
    // 16 64 bit general purpose registers, instruction pointer and
    // flags
    //

    unsigned long long Rax;
    unsigned long long Rbx;
    unsigned long long Rcx;
    unsigned long long Rdx;
    unsigned long long Rsi;
    unsigned long long Rdi;
    unsigned long long Rbp;
    unsigned long long Rsp;
    unsigned long long R8;
    unsigned long long R9;
    unsigned long long R10;
    unsigned long long R11;
    unsigned long long R12;
    unsigned long long R13;
    unsigned long long R14;
    unsigned long long R15;

    unsigned long long Rip;
    unsigned long long Rflags;

    //
    // Control Registers - on 32 bit platforms the upper 32 bits are
    // ignored. Efer is actually an Msr but it acts as an extension to
    // Cr4 and as such is treated as a processor register. Cr8 is only
    // valid on 64 bit systems.
    //

    unsigned long long Cr0;
    unsigned long long Cr2;
    unsigned long long Cr3;
    unsigned long long Cr4;
    unsigned long long Cr8;
    unsigned long long Efer;

    //
    // XSAVE Control Registers - only on platforms that support the
    // XSAVE/XRSTOR feature.
    //

    //
    // XCR0 is XFEM, XSAVE Feature Enabled Mask.
    //

    unsigned long long Xfem;

    //
    // Debug Registers - on 32 bit platforms the upper 32 bits are
    // ignored
    //

    unsigned long long Dr0;
    unsigned long long Dr1;
    unsigned long long Dr2;
    unsigned long long Dr3;
    unsigned long long Dr6;
    unsigned long long Dr7;

    //
    // Global and Interrupt Descriptor tables
    //

    HV_X64_TABLE_REGISTER Idtr;
    HV_X64_TABLE_REGISTER Gdtr;

    //
    // Segment selector registers together with their hidden state.
    //

    HV_X64_SEGMENT_REGISTER Cs;
    HV_X64_SEGMENT_REGISTER Ds;
    HV_X64_SEGMENT_REGISTER Es;
    HV_X64_SEGMENT_REGISTER Fs;
    HV_X64_SEGMENT_REGISTER Gs;
    HV_X64_SEGMENT_REGISTER Ss;
    HV_X64_SEGMENT_REGISTER Tr;
    HV_X64_SEGMENT_REGISTER Ldtr;

    //
    // MSRs needed for virtualization
    //

    unsigned long long KernelGsBase;
    unsigned long long Star;
    unsigned long long Lstar;
    unsigned long long Cstar;
    unsigned long long Sfmask;
    unsigned long long SysenterCs;
    unsigned long long SysenterEip;
    unsigned long long SysenterEsp;

    unsigned long long MsrCrPat;
    unsigned long long MsrMtrrCap;
    unsigned long long MsrMtrrDefType;
    unsigned long long MsrMtrrFixed[11];
    unsigned long long MsrMtrrVariableBase[8];
    unsigned long long MsrMtrrVariableMask[8];

    //
    // Local APIC state.
    //

    unsigned long LocalApicId;
    unsigned long LocalApicVersion;
    unsigned long LocalApicLdr;
    unsigned long LocalApicDfr;
    unsigned long LocalApicSpurious;
    unsigned long LocalApicIcrLow;
    unsigned long LocalApicIcrHigh;
    unsigned long LocalApicIsr[8];
    unsigned long LocalApicTmr[8];
    unsigned long LocalApicLvtTimer;
    unsigned long LocalApicLvtPerfmon;
    unsigned long LocalApicLvtLint0;
    unsigned long LocalApicLvtLint1;
    unsigned long LocalApicCurrentCount;
    unsigned long LocalApicInitialCount;
    unsigned long LocalApicDivider;
    unsigned long long LocalApicBaseMsr;

    union
    {
        //
        // x87 Floating point, MMX and XMM registers formatted as by
        // FXSAVE/FXSTOR.
        //

        HV_X64_FX_REGISTERS FxRegisters;

        //
        // x87 Floating point, MMX XMM and YMM registers formatted as by
        // XSAVE/XRSTOR.
        //
        // Only on platforms that support XSAVE/XRSTOR.
        //

        HV_X64_X_REGISTERS XRegisters;
    };

} HV_X64_CONTEXT, *PHV_X64_CONTEXT;

#define HV_VIRTUAL_PROCESSOR_REGISTERS_VERSION 1

typedef struct _HV_VP_CONTEXT
{
    //
    // The version of the HV_VP_CONTEXT structure
    //

    unsigned long Version;

    //
    // The architecture of these registers
    //

    HV_ARCHITECTURE Architecture;

    union
    {
        HV_X64_CONTEXT x64;
    };

} HV_VP_CONTEXT, *PHV_VP_CONTEXT;

#define HV_X64_MSR_STATS_PARTITION_RETAIL_PAGE      0x400000E0
#if defined(_PERF_FEATURES_ENABLED_)
#define HV_X64_MSR_STATS_PARTITION_INTERNAL_PAGE    0x400000E1
#endif

#define HV_X64_MSR_STATS_VP_RETAIL_PAGE             0x400000E2
#if defined(_PERF_FEATURES_ENABLED_)
#define HV_X64_MSR_STATS_VP_INTERNAL_PAGE           0x400000E3
#endif

typedef unsigned short  HV_STATISTICS_GROUP_TYPE;
typedef unsigned short  HV_STATISTICS_GROUP_LENGTH;

typedef struct _HV_STATISTICS_GROUP_VERSION
{
    unsigned short    Minor;
    unsigned short    Major;

} HV_STATISTICS_GROUP_VERSION;

//
// Group header
//
typedef struct DECLSPEC_ALIGN(2) _HV_STATISTICS_GROUP_HEADER
{

    HV_STATISTICS_GROUP_TYPE    Type;
    HV_STATISTICS_GROUP_VERSION Version;
    HV_STATISTICS_GROUP_LENGTH  Length;

} HV_STATISTICS_GROUP_HEADER, *PHV_STATISTICS_GROUP_HEADER;

#define HV_STATISTICS_GROUP_END_OF_LIST         0
#define HV_STATISTICS_GROUP_END_OF_PAGE         1

//
// Pseudo-group to use in manifest for counters accessible through hypercalls.
//
#define HV_STATISTICS_GROUP_HYPERCALL_BASED     15

//
// Definitions for the hypervisor counters statistics page
//
#define HV_STATISTICS_GROUP_HVA_ID              2
#define HV_STATISTICS_GROUP_HVA_VERSION         0x00010000
#define HV_STATISTICS_GROUP_HVV_ID              3
#define HV_STATISTICS_GROUP_HVV_VERSION         0x00010000
#define HV_STATISTICS_GROUP_HVI_ID              14
#define HV_STATISTICS_GROUP_HVI_VERSION         0x00010000

//
// Definitions for the logical processor counters statistics page
//
#define HV_STATISTICS_GROUP_LPA_ID              2
#define HV_STATISTICS_GROUP_LPA_VERSION         0x00010000
#define HV_STATISTICS_GROUP_LPV_ID              3
#define HV_STATISTICS_GROUP_LPV_VERSION         0x00010000
#define HV_STATISTICS_GROUP_LPI_ID              14
#define HV_STATISTICS_GROUP_LPI_VERSION         0x00010000

//
// Definitions for the partition counters statistics page
//
#define HV_STATISTICS_GROUP_PTA_ID              2
#define HV_STATISTICS_GROUP_PTA_VERSION         0x00010000
#define HV_STATISTICS_GROUP_PTV_ID              3
#define HV_STATISTICS_GROUP_PTV_VERSION         0x00010000
#define HV_STATISTICS_GROUP_PTI_ID              14
#define HV_STATISTICS_GROUP_PTI_VERSION         0x00010000

//
// Definitions for the virtual processor statistics page
//
#define HV_STATISTICS_GROUP_VPA_ID              2
#define HV_STATISTICS_GROUP_VPA_VERSION         0x00010000
#define HV_STATISTICS_GROUP_VPV_ID              3
#define HV_STATISTICS_GROUP_VPV_VERSION         0x00010000
#define HV_STATISTICS_GROUP_VPI_ID              14
#define HV_STATISTICS_GROUP_VPI_VERSION         0x00010000

//
// Maximum counters allowed per group. Calculated for the case when group
// occupies full page: there will be two headers (one for the group and one
// terminating the list).
//

#define HV_ST_MAX_COUNTERS_PER_GROUP \
    ((HV_PAGE_SIZE - 2 * sizeof(HV_STATISTICS_GROUP_HEADER)) / sizeof(unsigned long long))

//
// Definition of the counters structure.
//

typedef struct _HV_STATS_PAGE
{
    unsigned long long      Data[HV_PAGE_SIZE / sizeof(unsigned long long)];

} HV_STATS_PAGE, *PHV_STATS_PAGE;

//
// Definition for the stats object types.
//

typedef enum _HV_STATS_OBJECT_TYPE
{
    //
    // Global stats objects
    //

    HvStatsObjectHypervisor       = 0x00000001,
    HvStatsObjectLogicalProcessor = 0x00000002,

    //
    // Local stats objects
    //

    HvStatsObjectPartition        = 0x00010001,
    HvStatsObjectVp               = 0x00010002

} HV_STATS_OBJECT_TYPE;

//
// Definition for the stats map/unmap MSR value.
//

typedef union _HV_ST_MAP_LOCATION
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long MapEnabled : 1;
        unsigned long long ReservedP : 11;
        unsigned long long BaseMapGpaPageNumber : 52;
    };
} HV_ST_MAP_LOCATION, *PHV_ST_MAP_LOCATION;

//
// Hypervisor global counter set
//
typedef enum _HV_HYPERVISOR_COUNTER
{

    StHvCounterLogicalProcessors = 1,
    StHvCounterPartitions = 2,
    StHvCounterTotalPages = 3,
    StHvCounterVirtualProcessors = 4,
    StHvCounterMonitoredNotifications = 5,

    StHvCounterMAXIMUM

} HV_HYPERVISOR_COUNTER;

#define HV_STATISTICS_GROUP_HVA_LENGTH 16
#define HV_STATISTICS_GROUP_HVV_LENGTH 0

//
// Hypervisor Logical Processor counter set
//
typedef enum _HV_CPU_COUNTER 
{

    StLpCounterGlobalTime = 1,
    StLpCounterTotalRunTime = 2,
    StLpCounterHypervisorRunTime = 3,
    StLpCounterHardwareInterrupts = 4,
    StLpCounterContextSwitches = 5,
    StLpCounterInterProcessorInterrupts = 6,
    StLpCounterSchedulerInterrupts = 7,
    StLpCounterTimerInterrupts = 8,
    StLpCounterInterProcessorInterruptsSent = 9,
    StLpCounterProcessorHalts = 10,
    StLpCounterMonitorTransitionCost = 11,
    StLpCounterContextSwitchTime = 12,
    StLpCounterC1TransitionsCount = 13,
    StLpCounterC1RunTime = 14,
    StLpCounterC2TransitionsCount = 15,
    StLpCounterC2RunTime = 16,
    StLpCounterC3TransitionsCount = 17,
    StLpCounterC3RunTime = 18,

    StLpCounterMAXIMUM

} HV_CPU_COUNTER;

#define HV_STATISTICS_GROUP_LPA_LENGTH 144
#define HV_STATISTICS_GROUP_LPV_LENGTH 0

//
// Partition counter set
//
typedef enum _HV_PROCESS_COUNTER 
{

    StPtCounterVirtualProcessors = 1,

    StPtCounterTlbSize = 3,
    StPtCounterAddressSpaces = 4,
    StPtCounterDepositedPages = 5,
    StPtCounterGpaPages = 6,
    StPtCounterGpaSpaceModifications = 7,
    StPtCounterVirtualTlbFlushEntires = 8,
    StPtCounterRecommendedTlbSize = 9,
    StPtCounterGpaPages4K = 10,
    StPtCounterGpaPages2M = 11,
    StPtCounterGpaPages1G = 12,
    StPtCounterGpaPages512G = 13,
    StPtCounterMAXIMUM

} HV_PROCESS_COUNTER;

#define HV_STATISTICS_GROUP_PTA_LENGTH 8
#define HV_STATISTICS_GROUP_PTV_LENGTH 88

//
// Hypervisor Virtual Processor counter set
//
typedef enum _HV_THREAD_COUNTER 
{

    StVpCounterTotalRunTime = 1,
    StVpCounterHypervisorRunTime = 2,

    StVpCounterHypercallsCount = 4,
    StVpCounterHypercallsTime = 5,
    StVpCounterPageInvalidationsCount = 6,
    StVpCounterPageInvalidationsTime = 7,
    StVpCounterControlRegisterAccessesCount = 8,
    StVpCounterControlRegisterAccessesTime = 9,
    StVpCounterIoInstructionsCount = 10,
    StVpCounterIoInstructionsTime = 11,
    StVpCounterHltInstructionsCount = 12,
    StVpCounterHltInstructionsTime = 13,
    StVpCounterMwaitInstructionsCount = 14,
    StVpCounterMwaitInstructionsTime = 15,
    StVpCounterCpuidInstructionsCount = 16,
    StVpCounterCpuidInstructionsTime = 17,
    StVpCounterMsrAccessesCount = 18,
    StVpCounterMsrAccessesTime = 19,
    StVpCounterOtherInterceptsCount = 20,
    StVpCounterOtherInterceptsTime = 21,
    StVpCounterExternalInterruptsCount = 22,
    StVpCounterExternalInterruptsTime = 23,
    StVpCounterPendingInterruptsCount = 24,
    StVpCounterPendingInterruptsTime = 25,
    StVpCounterEmulatedInstructionsCount = 26,
    StVpCounterEmulatedInstructionsTime = 27,
    StVpCounterDebugRegisterAccessesCount = 28,
    StVpCounterDebugRegisterAccessesTime = 29,
    StVpCounterPageFaultInterceptsCount = 30,
    StVpCounterPageFaultInterceptsTime = 31,
    StVpCounterGuestPageTableMaps = 32,
    StVpCounterLargePageTlbFills = 33,
    StVpCounterSmallPageTlbFills = 34,
    StVpCounterReflectedGuestPageFaults = 35,
    StVpCounterApicMmioAccesses = 36,
    StVpCounterIoInterceptMessages = 37,
    StVpCounterMemoryInterceptMessages = 38,
    StVpCounterApicEoiAccesses = 39,
    StVpCounterOtherMessages = 40,
    StVpCounterPageTableAllocations = 41,
    StVpCounterLogicalProcessorMigrations = 42,
    StVpCounterAddressSpaceEvictions = 43,
    StVpCounterAddressSpaceSwitches = 44,
    StVpCounterAddressDomainFlushes = 45,
    StVpCounterAddressSpaceFlushes = 46,
    StVpCounterGlobalGvaRangeFlushes = 47,
    StVpCounterLocalGvaRangeFlushes = 48,
    StVpCounterPageTableEvictions = 49,
    StVpCounterPageTableReclamations = 50,
    StVpCounterPageTableResets = 51,
    StVpCounterPageTableValidations = 52,
    StVpCounterApicTprAccesses = 53,
    StVpCounterPageTableWriteIntercepts = 54,
    StVpCounterSyntheticInterrupts = 55,
    StVpCounterVirtualInterrupts = 56,
    StVpCounterApicIpisSent = 57,
    StVpCounterApicSelfIpisSent = 58,
    StVpCounterGpaSpaceHypercalls = 59,
    StVpCounterLogicalProcessorHypercalls = 60,
    StVpCounterLongSpinWaitHypercalls = 61,
    StVpCounterOtherHypercalls = 62,
    StVpCounterSyntheticInterruptHypercalls = 63,
    StVpCounterVirtualInterruptHypercalls = 64,
    StVpCounterVirtualMmuHypercalls = 65,
    StVpCounterVirtualProcessorHypercalls = 66,
    StVpCounterMAXIMUM

} HV_THREAD_COUNTER;

#define HV_STATISTICS_GROUP_VPA_LENGTH 16
#define HV_STATISTICS_GROUP_VPV_LENGTH 504

//
// Declare the timestamp type.
//
typedef unsigned long long HV_TIME_STAMP, *PHV_TIME_STAMP;

//
// Logical processors are defined by a 32-bit index
//
typedef unsigned long HV_LOGICAL_PROCESSOR_INDEX, *PHV_LOGICAL_PROCESSOR_INDEX;

//
// This described the various methods for changing power state
// 
typedef enum _HV_X64_POWER_CHANGE_METHOD
{
    HvX64PowerChangeIssueHlt,
    HvX64PowerChangeReadIoThenIssueHlt,
    HvX64PowerChangeReadIo,
    HvX64PowerChangeIssueMwait
} HV_X64_POWER_CHANGE_METHOD, *PHV_X64_POWER_CHANGE_METHOD;

//
// This described a recipe to take the processor to a specific low power state.
// 
typedef union _HV_X64_MSR_POWER_STATE_CONFIG
{
    unsigned long long AsUINT64;

    struct
    {
        unsigned long long TypeSpecific : 52;
        unsigned long long ChangeType : 4;    // use HV_X64_POWER_CHANGE_METHOD values
        unsigned long long CheckBM_STS : 1;
        unsigned long long SetBM_RST : 1;
        unsigned long long ClearBM_RST : 1;
        unsigned long long SetARB_DIS : 1;
        unsigned long long ReservedZ : 4;
    };

    struct
    {
        unsigned long long ReservedZ : 52;
    } Hlt;

    struct
    {
        unsigned short Port;
        unsigned short ReservedZ1;
        unsigned long ReservedZ2 : 20;
    } Io;

    struct
    {
        unsigned long long Address : 52;      // x64 has a 52 bit physical address space
    } Memory;

    struct
    {
        unsigned long Hints;
        unsigned long BreakOnMaskedInterrupt : 1;
        unsigned long ReservedZ : 19;
    } Mwait;

} HV_X64_MSR_POWER_STATE_CONFIG, *PHV_X64_MSR_POWER_STATE_CONFIG;

//
// Reading from the trigger register takes the processor idle from the 
// perspecive of the power management partition.  Upon wakeup the value returned
// contains information on the the idle operation attempted.
// 
typedef union _HV_X64_MSR_POWER_STATE_TRIGGER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned char IdleEntryCount;
        unsigned char Reserved[3];
        unsigned long Reserved2 : 31;
        unsigned long ActiveBM_STS : 1;
    };

} HV_X64_MSR_POWER_STATE_TRIGGER, *PHV_X64_MSR_POWER_STATE_TRIGGER;

//
// The following virtual MSRs are used to configure and trigger the C1-C3 power 
// states.  Space is reserved for power states C4-C15 should they ever be
// defined by ACPI.
// 

#define HV_X64_MSR_POWER_STATE_TRIGGER_C1   0x400000C1
#define HV_X64_MSR_POWER_STATE_TRIGGER_C2   0x400000C2
#define HV_X64_MSR_POWER_STATE_TRIGGER_C3   0x400000C3

#define HV_X64_MSR_POWER_STATE_CONFIG_C1    0x400000D1
#define HV_X64_MSR_POWER_STATE_CONFIG_C2    0x400000D2
#define HV_X64_MSR_POWER_STATE_CONFIG_C3    0x400000D3

//
// Define guest idle MSR. A guest virtual processor can enter idle state by 
// reading this MSR, and will be waken up when an interrupt arrives 
// regarldess interrupt is enabled or not.
//
// N.B. The guest idle MSR is only used by guests to enter idle state. Root
//      uses the power trigger MSRs defined above to enter idle states.
//

#define HV_X64_MSR_GUEST_IDLE               0x400000F0

//
// Define interrupt types.
//
typedef enum _HV_INTERRUPT_TYPE
{
    //
    // Explicit interrupt types.
    //
    HvX64InterruptTypeFixed             = 0x0000,
    HvX64InterruptTypeLowestPriority    = 0x0001,
    HvX64InterruptTypeSmi               = 0x0002,
    HvX64InterruptTypeNmi               = 0x0004,
    HvX64InterruptTypeInit              = 0x0005,
    HvX64InterruptTypeSipi              = 0x0006,
    HvX64InterruptTypeExtInt            = 0x0007,
    HvX64InterruptTypeLocalInt0         = 0x0008,
    HvX64InterruptTypeLocalInt1         = 0x0009,

    //
    // Maximum (exclusive) value of interrupt type.
    //
    HvX64InterruptTypeMaximum           = 0x000A

} HV_INTERRUPT_TYPE, *PHV_INTERRUPT_TYPE;

//
// Define interrupt vector type.
//
typedef unsigned long HV_INTERRUPT_VECTOR, *PHV_INTERRUPT_VECTOR;

//
// Define special "no interrupt vector" value used by hypercalls that indicate
// whether the previous virtual interrupt was acknowledged.
//
#define HV_INTERRUPT_VECTOR_NONE 0xFFFFFFFF

//
// Define profile sources. 
//
// N.B. The total number of profile sources is limited to 2048.
//

typedef enum _HV_PROFILE_SOURCE
{
    //
    // Profile sources for all processors
    //
    HvProfileInvalid,
    HvProfileCyclesNotHalted = 1,
    HvProfileCacheMisses,
    HvProfileBranchMispredictions,

    //
    // Profile sources for for AMD processors.
    //

    HvProfileDispatchedFPUOps = 64,
    HvProfileCyclesNoFPUOpsRetired,
    HvProfileDispathedFPUOpsWithFastFlag,
    HvProfileRetiredSSEOps,
    HvProfileRetiredMoveOps,
    HvProfileSegmentRegisterLoad,
    HvProfileResyncBySelfModifyingCode,
    HvProfileResyncBySnoop,
    HvProfileBuffer2Full,
    HvProfileLockedOperation,
    HvProfileRetiredCLFLUSH,
    HvProfileRetiredCPUID,
    HvProfileLSDispatch,
    HvProfileCancelledStoreToLoadFwdOperations,
    HvProfileSMIReceived,
    HvProfileDataAccess,
    HvProfileDataMiss,
    HvProfileDCRefillFromL2,
    HvProfileDCRefillFromSystem,
    HvProfileDCRefillCopyBack,
    HvProfileDCL1DTLBMissL2DTLBHit,
    HvProfileDCL1DTLBMissL2DTLBMiss,
    HvProfileDCMisalignedDataReference,
    HvProfileDCLateCancelOfAnAccess,
    HvProfileDCEarlyCancelOfAnAccess,
    HvProfileDCOneBitECCError,
    HvProfileDCDispatchedPrefetchInstructions,
    HvProfileDCacheMissByLockedInstructions,
    HvProfileL1DTLBHit,
    HvProfileL1DTLBReloadLatency,
    HvProfileIneffectiveSoftwarePrefetches,
    HvProfileGlobalTLBFlushes,
    HvProfileRetiredINVLPGAndINVLPGA,
    HvProfileMemoryAccessesToUC,
    HvProfileMemoryAccessesToWCAndWCBufferFlushToWB,
    HvProfileStreamStoreToWB,
    HvProfileDataPrefetchCancelled,
    HvProfileDataPrefetchAttempts,
    HvProfileMABRequests,
    HvProfileNBReadResponsesForForCacheRefill,
    HvProfileOctwordsWriitenToSystem,
    HvProfilePageTableWalkerPDPERefillHitInL2,
    HvProfilePageTableWalkerPDPELookupMissedInPDC,
    HvProfilePageTableWalkerPML4ERefillHitInL2,
    HvProfilePageTableWalkerPML4ELookupMissedInPDC,
    HvProfilePageTableWalkerPTERefillHitInL2,
    HvProfilePageTableWalkerPDERefillHitInL2,
    HvProfilePageTableWalkerPDELookupMissedInPDC,
    HvProfilePageTableWalkerPDELookupInPDC,
    HvProfileProbeHits,
    HvProfileCacheCrossInvalidates,
    HvProfileTLBFlushEvents,
    HvProfileL2Request,
    HvProfileL2CacheMisses,
    HvProfileL2CacheMissesICFill,
    HvProfileL2CacheMissesDCFill,
    HvProfileL2CacheMissesTLBPageTableWalk,
    HvProfileL2Fill,
    HvProfileICFetch,
    HvProfileICMiss,
    HvProfileICRefillFromL2,
    HvProfileICRefillFromSystem,
    HvProfileICL1TLBMissL2TLBHit,
    HvProfileICL1TLBMissL2TLBMiss,
    HvProfileICResyncBySnoop,
    HvProfileICInstructionFetchStall,
    HvProfileICReturnStackHit,
    HvProfileICReturnStackOverflow,
    HvProfileInstructionCacheVictims,
    HvProfileInstructionCacheLinesInvalidated,
    HvProfileITLBReloads,
    HvProfileITLBReloadsAborted,
    HvProfileRetiredInstructions,
    HvProfileRetireduops,
    HvProfileRetiredBranches,
    HvProfileRetiredBranchesMispredicted,
    HvProfileTakenBranches,
    HvProfileTakenBranchesMispredicted,
    HvProfileRetiredFarControlTransfers,
    HvProfileRetiredResyncsNonControlTransferBranches,
    HvProfileRetiredNearReturns,
    HvProfileRetiredNearReturnsMispredicted,
    HvProfileTakenBranchesMispredictedByAddressMiscompare,
    HvProfileRetiredFPUInstructions,
    HvProfileRetiredFastpathDoubleOpInstructions,
    HvProfileInterruptsMaskedCycles,
    HvProfileInterruptsMaskedWhilePendingCycles,
    HvProfileTakenHardwareInterrupts,
    HvProfileNothingToDispatch,
    HvProfileDispatchStalls,
    HvProfileDispatchStallsFromBranchAbortToRetire,
    HvProfileDispatchStallsForSerialization,
    HvProfileDispatchStallsForSegmentLoad,
    HvProfileDispatchStallsWhenReorderBufferFull,
    HvProfileDispatchStallsWhenReservationStationsFull,
    HvProfileDispatchStallsWhenFPUFull,
    HvProfileDispatchStallsWhenLSFull,
    HvProfileDispatchStallsWhenWaitingForAllQuiet,
    HvProfileDispatchStallsWhenFarControlOrResyncBranchPending,
    HvProfileFPUExceptions,
    HvProfileNumberOfBreakPointsForDR0,
    HvProfileNumberOfBreakPointsForDR1,
    HvProfileNumberOfBreakPointsForDR2,
    HvProfileNumberOfBreakPointsForDR3,
    HvProfileDRAMAccess,
    HvProfileDRAMPageTableOverflow,
    HvProfileDRAMDRAMCommandSlotsMissed,
    HvProfileMemoryControllerTurnAround,
    HvProfileMemoryControllerBypassCounter,
    HvProfileSizedCommands,
    HvProfileProbeResult,
    HvProfileUpstreamRequest,
    HvProfileHyperTransportBus0Bandwidth,
    HvProfileHyperTransportBus1Bandwidth,
    HvProfileHyperTransportBus2Bandwidth,
    HvProfileGuestTLBMissesAndInvalidates,
    HvProfileGuestTLBMisses,
    HvProfileGuestTLBInvalidates,
    HvProfileHostPageLargerThanGuestPage_RevC,
    HvProfilePageSizeMismatchCausedByMTRR_RevC,
    HvProfileGuestPageLargerThanHostPage_RevC,
    HvProfileInterruptChecks,
    HvProfileRetiredLFENCE,
    HvProfileRetiredSFENCE,
    HvProfileRetiredMFENCE,
    HvProfileCPUToDRAMRequestsLocalToNode0,
    HvProfileCPUToDRAMRequestsLocalToNode1,
    HvProfileCPUToDRAMRequestsLocalToNode2,
    HvProfileCPUToDRAMRequestsLocalToNode3,
    HvProfileCPUToDRAMRequestsLocalToNode4,
    HvProfileCPUToDRAMRequestsLocalToNode5,
    HvProfileCPUToDRAMRequestsLocalToNode6,
    HvProfileCPUToDRAMRequestsLocalToNode7,
    HvProfileIOToDRAMRequestsLocalToNode0,
    HvProfileIOToDRAMRequestsLocalToNode1,
    HvProfileIOToDRAMRequestsLocalToNode2,
    HvProfileIOToDRAMRequestsLocalToNode3,
    HvProfileIOToDRAMRequestsLocalToNode4,
    HvProfileIOToDRAMRequestsLocalToNode5,
    HvProfileIOToDRAMRequestsLocalToNode6,
    HvProfileIOToDRAMRequestsLocalToNode7,
    HvProfileCPURequestsToAPIC,

    //
    // Profile source descriptors for Intel processors.
    //

    HvProfileInstructionsRetired = 512,
    HvProfileUnhaltedReferenceCycles,
    HvProfileLLCReference,
    HvProfileLLCMisses,
    HvProfileBranchInstuctionRetired,
    HvProfileBranchMispredict
} HV_PROFILE_SOURCE;

//
// In a NUMA system processors, memory and devices may reside in different
// firmware described proximity domains.
//
// On a non-NUMA system everything resides in proximity domain 0.
//

typedef unsigned long HV_PROXIMITY_DOMAIN_ID, *PHV_PROXIMITY_DOMAIN_ID;

//
// Define the proximity domain information flags.
//

typedef struct _HV_PROXIMITY_DOMAIN_FLAGS
{
    //
    // This flag specifies whether the proximity information is preferred. If
    // so, then the memory allocations are done preferentially from the
    // specified proximity domain. In case there is insufficient memory in the
    // specified domain, other domains are tried. If this flag is false, then
    // all memory allocation must come from the specified domain.
    //
    unsigned long ProximityPreferred:1;

    unsigned long Reserved:30;

    //
    // This flag specifies that the specified proximity domain is valid. If
    // this flag is false then the memory allocation can come from any
    // proximity domain.
    //
    unsigned long ProximityInfoValid:1;

} HV_PROXIMITY_DOMAIN_FLAGS, *PHV_PROXIMITY_DOMAIN_FLAGS;

//
// Define the proximiy domain information structure.
//

typedef struct _HV_PROXIMITY_DOMAIN_INFO
{
    HV_PROXIMITY_DOMAIN_ID Id;
    HV_PROXIMITY_DOMAIN_FLAGS Flags;
} HV_PROXIMITY_DOMAIN_INFO, *PHV_PROXIMITY_DOMAIN_INFO;

//
// The HV_PROCESSOR_INFO structures contains additional information about
// each physical processor
//

typedef struct _HV_PROCESSOR_INFO
{
    //
    // The Local APIC ID for the processor.
    //
    unsigned long LocalApicId;

    //
    // The proximity domain the processor resides in
    //
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;

} HV_PROCESSOR_INFO, *PHV_PROCESSOR_INFO;

//
// The following structure contains the definition of a memory range.
//

typedef struct _HV_MEMORY_RANGE_INFO
{
    //
    // The system physical address where this range begins
    //
    HV_SPA BaseAddress;

    //
    // The length of this range of memory in bytes.
    //
    unsigned long long Length;

    //
    // The proximity domain this memory range resides in.
    //
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;

} HV_MEMORY_RANGE_INFO, *PHV_MEMORY_RANGE_INFO;

typedef const HV_MEMORY_RANGE_INFO* PCHV_MEMORY_RANGE_INFO;

//
// Define the trace buffer index type.
//

typedef unsigned long HV_EVENTLOG_BUFFER_INDEX, *PHV_EVENTLOG_BUFFER_INDEX;

#define HV_EVENTLOG_BUFFER_INDEX_NONE 0xffffffff

//
// Define all the trace buffer types.
//

typedef enum
{
    HvEventLogTypeGlobalSystemEvents = 0x00000000,
    HvEventLogTypeLocalDiagnostics   = 0x00000001,
    HvEventLogTypeSystemDiagnostics  = 0x00000002,

    HvEventLogTypeMaximum            = 0x00000002,
} HV_EVENTLOG_TYPE;


//
// Define all the trace buffer states.
//

typedef enum
{
    HvEventLogBufferStateStandby  = 0,
    HvEventLogBufferStateFree     = 1,
    HvEventLogBufferStateInUse    = 2,
    HvEventLogBufferStateComplete = 3,
    HvEventLogBufferStateReady    = 4
} HV_EVENTLOG_BUFFER_STATE;


//
// Define trace message header structure.
//

typedef struct _HV_EVENTLOG_MESSAGE_PAYLOAD
{

    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;

} HV_EVENTLOG_MESSAGE_PAYLOAD, *PHV_EVENTLOG_MESSAGE_PAYLOAD;


//
// Define time source enum and structure.
//

typedef enum
{
    HvEventLogEntryTimeReference = 0,
    HvEventLogEntryTimeTsc       = 1
} HV_EVENTLOG_ENTRY_TIME_BASIS;

typedef union
{

    HV_NANO100_TIME ReferenceTime;
    unsigned long long          TimeStamp;

} HV_EVENTLOG_ENTRY_TIME;


//
// Define trace buffer header.
//

typedef struct _HV_EVENTLOG_BUFFER_HEADER
{
    unsigned long                         BufferSize;        // BufferSize
    HV_EVENTLOG_BUFFER_INDEX       BufferIndex;       // SavedOffset   
    unsigned long                         EventsLost;        // CurrentOffset
    volatile unsigned long                ReferenceCounter;  // ReferenceCount

    union
    {
        unsigned long long                     TimeStamp;
        HV_NANO100_TIME            ReferenceTime;
    };
    unsigned long long                         Reserved1;

    unsigned long long                         Reserved2;    
    struct                                            // ClientContext
    {
        unsigned char                      LogicalProcessor;  // ProcessorNumber
        unsigned char                      Alignment;
        unsigned short                     LoggerId;
    };
    volatile HV_EVENTLOG_BUFFER_STATE BufferState;    // (Free/GeneralLogging/Flush)
    
    unsigned long                         NextBufferOffset;  // Offset
    HV_EVENTLOG_TYPE               Type;              // BufferFlag and BufferType
    HV_EVENTLOG_BUFFER_INDEX       NextBufferIndex;   // Padding1
    unsigned long                         Reserved3;         // Padding1

    unsigned long                         Reserved4[2];      // Padding1 
    
} HV_EVENTLOG_BUFFER_HEADER, *PHV_EVENTLOG_BUFFER_HEADER;


//
// Define trace entry header.
//
typedef struct _HV_EVENTLOG_ENTRY_HEADER
{
    unsigned long              Context;    // Marker    
    unsigned short              Size;       // Size in WMI_TRACE_PACKET
    unsigned short              Type;       // HookId in WMI_TRACE_PACKET
    
    union 
    {
        unsigned long long          TimeStamp;
        HV_NANO100_TIME ReferenceTime;
    };
} HV_EVENTLOG_ENTRY_HEADER, *PHV_EVENTLOG_ENTRY_HEADER;

//
// Definition of the HvCallAllocateBufferGroup hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_EVENTLOG_BUFFER
{

    HV_EVENTLOG_TYPE   EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
    HV_PROXIMITY_DOMAIN_INFO ProximityInfo;

} HV_INPUT_CREATE_EVENTLOG_BUFFER, *PHV_INPUT_CREATE_EVENTLOG_BUFFER;


//
// Definition of the HvCallCreateEventLogBuffer hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_EVENTLOG_BUFFER
{

    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;

} HV_INPUT_DELETE_EVENTLOG_BUFFER, *PHV_INPUT_DELETE_EVENTLOG_BUFFER;

//
// Definition of the HvCallRequestEventLogGroupFlush hypercall input
// structure.
//


typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_EVENTLOG_REQUEST_FLUSH
{

    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX VpIndex;

} HV_INPUT_EVENTLOG_REQUEST_FLUSH, *PHV_INPUT_EVENTLOG_REQUEST_FLUSH;


//
// Definition of the HvCallInitialzeEventLogBufferGroup hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP
{

    HV_EVENTLOG_TYPE EventLogType;
    unsigned long MaximumBufferCount;
    unsigned long BufferSizeInPages;
    unsigned long Threshold;
    HV_EVENTLOG_ENTRY_TIME_BASIS TimeBasis;
    HV_NANO100_TIME SystemTime;

} HV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP,
*PHV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP;


//
// Definition of the HvCallFinalizeEventLogBufferGroup hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FINALIZE_EVENTLOG_BUFFER_GROUP
{

    HV_EVENTLOG_TYPE EventLogType;

} HV_INPUT_FINALIZE_EVENTLOG_BUFFER_GROUP,
*PHV_INPUT_FINALIZE_EVENTLOG_BUFFER_GROUP;

//
// Definition of the HvCallMapEventLogBuffer hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_EVENTLOG_BUFFER
{

    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;

} HV_INPUT_MAP_EVENTLOG_BUFFER, *PHV_INPUT_MAP_EVENTLOG_BUFFER;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_MAP_EVENTLOG_BUFFER
{

    HV_GPA_PAGE_NUMBER GpaPageNumbers[512];

} HV_OUTPUT_MAP_EVENTLOG_BUFFER, *PHV_OUTPUT_MAP_EVENTLOG_BUFFER;


//
// Definition of the HvCallUnmapEventLogBuffer hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_EVENTLOG_BUFFER
{

    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;

} HV_INPUT_UNMAP_EVENTLOG_BUFFER, *PHV_INPUT_UNMAP_EVENTLOG_BUFFER;
//
// Definition of the HvCallSetEventLogGroupSources hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_EVENTLOG_SET_EVENTS
{

    HV_EVENTLOG_TYPE EventLogType;
    unsigned long long           EnableFlags;

} HV_INPUT_EVENTLOG_SET_EVENTS, *PHV_INPUT_EVENTLOG_SET_EVENTS;

//
// Definition of the HvCallReleaseEventLogBuffer hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_EVENTLOG_RELEASE_BUFFER
{

    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;

} HV_INPUT_EVENTLOG_RELEASE_BUFFER, *PHV_INPUT_EVENTLOG_RELEASE_BUFFER;

//
// N.B. These constants are temporary until we have the ability to allocate bigger
// chunks of memory with our Hv Mm component.
//
#if defined(_HV_ICECAP_ENABLED_)

#define HV_TR_MAX_DIAG_BUFFER_SIZE  (1024*1024*32) // 32MB
#define HV_TR_MAX_DIAG_BUFFER_COUNT (2)

#else

#define HV_TR_MAX_DIAG_BUFFER_SIZE  (1024*1024*2) // 2MB
#define HV_TR_MAX_DIAG_BUFFER_COUNT (8)

#endif

//
// Event & Trace Groups.
//
#define HV_TR_GROUP_NONE            0x0000000000000000

//
// Event Groups (Admin, Operational, Audit, ...)
//
#define HV_EVENTLOG_ENABLE_AUDIT_SUCCESS    0x0000000000000001
#define HV_EVENTLOG_ENABLE_AUDIT_FAILURE    0x0000000000000002
#define HV_EVENTLOG_ENABLE_PARTITION        0x0000000000000004
#define HV_EVENTLOG_ENABLE_TEST             0x8000000000000000

//
// Diagnostic Trace Groups.
//
#define HV_TR_GROUP_ADMIN           0x0000000000000001
#define HV_TR_GROUP_DIAG            0x0000000000000002
#define HV_TR_GROUP_WARN            0x0000000000000003

//
// Retail Performance Trace Groups (starting at 0x0000000000000100)
//
#define HV_TR_GROUP_BM              0x0000000000000100
#define HV_TR_GROUP_DM              0x0000000000000200
#define HV_TR_GROUP_HC              0x0000000000000400
#define HV_TR_GROUP_IM              0x0000000000000800
#define HV_TR_GROUP_IC              0x0000000000001000
#define HV_TR_GROUP_OB              0x0000000000002000
#define HV_TR_GROUP_PT              0x0000000000004000
#define HV_TR_GROUP_VP              0x0000000000008000
#define HV_TR_GROUP_SYNIC           0x0000000000010000
#define HV_TR_GROUP_SYNIC_TI        0x0000000000020000
#define HV_TR_GROUP_AM_GVA          0x0000000000040000
#define HV_TR_GROUP_AM              0x0000000000080000
#define HV_TR_GROUP_VAL             0x0000000000100000
#define HV_TR_GROUP_VM              0x0000000000200000
#define HV_TR_GROUP_SCH             0x0000000000400000
#define HV_TR_GROUP_TH              0x0000000000800000
#define HV_TR_GROUP_TI              0x0000000001000000
#define HV_TR_GROUP_KE              0x0000000002000000
#define HV_TR_GROUP_MM              0x0000000004000000
#define HV_TR_GROUP_PROFILER        0x0000000008000000

#define HV_TR_ALL_GROUPS (HV_TR_GROUP_BM | HV_TR_GROUP_DM | HV_TR_GROUP_HC | \
    HV_TR_GROUP_IM | HV_TR_GROUP_IC | HV_TR_GROUP_OB | \
    HV_TR_GROUP_PT | HV_TR_GROUP_VP | HV_TR_GROUP_SYNIC | \
    HV_TR_GROUP_SYNIC_TI | HV_TR_GROUP_AM_GVA | HV_TR_GROUP_AM | \
    HV_TR_GROUP_VAL | HV_TR_GROUP_VM | HV_TR_GROUP_SCH | \
    HV_TR_GROUP_TH | HV_TR_GROUP_TI | HV_TR_GROUP_KE | \
    HV_TR_GROUP_MM | HV_TR_GROUP_PROFILER)

#define HV_TR_IS_GROUP_RETAIL(_Group_) \
    (((unsigned long long)(_Group_) > 0) && \
    (((unsigned long long)(_Group_) & HV_TR_ALL_GROUPS) != 0) && \
    (((unsigned long long)(_Group_) & ((unsigned long long)(_Group_) - 1)) == 0))

//
// Internal Debugging Trace Groups (starting at 0x0000010000000000)
//
#define HV_TR_GROUP_BM_INTERNAL       0x0000010000000000
#define HV_TR_GROUP_DM_INTERNAL       0x0000020000000000
#define HV_TR_GROUP_HC_INTERNAL       0x0000040000000000
#define HV_TR_GROUP_IM_INTERNAL       0x0000080000000000
#define HV_TR_GROUP_IC_INTERNAL       0x0000100000000000
#define HV_TR_GROUP_OB_INTERNAL       0x0000200000000000
#define HV_TR_GROUP_PT_INTERNAL       0x0000400000000000
#define HV_TR_GROUP_VP_INTERNAL       0x0000800000000000
#define HV_TR_GROUP_SYNIC_INTERNAL    0x0001000000000000
#define HV_TR_GROUP_SYNIC_TI_INTERNAL 0x0002000000000000
#define HV_TR_GROUP_AM_GVA_INTERNAL   0x0004000000000000
#define HV_TR_GROUP_AM_INTERNAL       0x0008000000000000
#define HV_TR_GROUP_VAL_INTERNAL      0x0010000000000000
#define HV_TR_GROUP_VM_INTERNAL       0x0020000000000000
#define HV_TR_GROUP_SCH_INTERNAL      0x0040000000000000
#define HV_TR_GROUP_TH_INTERNAL       0x0080000000000000
#define HV_TR_GROUP_TI_INTERNAL       0x0100000000000000
#define HV_TR_GROUP_KE_INTERNAL       0x0200000000000000
#define HV_TR_GROUP_MM_INTERNAL       0x0400000000000000

//
// Tf, simulate full buffers and cyclic buffers are currently only
// supported for TEST_FEATURES_ENABLED builds.
//
#define HV_TR_GROUP_TF                0x1000000000000000
#define HV_TR_GROUP_SIMULATE_FULL     0x2000000000000000
#define HV_TR_GROUP_CYCLIC            0x4000000000000000

//
// IceCap Trace Group.
//
#define HV_TR_GROUP_ICE               0x8000000000000000

#define HV_TR_ALL_GROUPS_INTERNAL (HV_TR_GROUP_BM_INTERNAL | \
    HV_TR_GROUP_DM_INTERNAL | HV_TR_GROUP_HC_INTERNAL | \
    HV_TR_GROUP_IM_INTERNAL | HV_TR_GROUP_IC_INTERNAL | \
    HV_TR_GROUP_OB_INTERNAL | HV_TR_GROUP_PT_INTERNAL | \
    HV_TR_GROUP_VP_INTERNAL | HV_TR_GROUP_SYNIC_INTERNAL | \
    HV_TR_GROUP_SYNIC_TI_INTERNAL | HV_TR_GROUP_AM_GVA_INTERNAL | \
    HV_TR_GROUP_AM_INTERNAL | HV_TR_GROUP_VAL_INTERNAL | \
    HV_TR_GROUP_VM_INTERNAL | HV_TR_GROUP_SCH_INTERNAL | \
    HV_TR_GROUP_TH_INTERNAL | HV_TR_GROUP_TI_INTERNAL | \
    HV_TR_GROUP_KE_INTERNAL | HV_TR_GROUP_MM_INTERNAL | \
    HV_TR_GROUP_TF | HV_TR_GROUP_SIMULATE_FULL | \
    HV_TR_GROUP_CYCLIC | HV_TR_GROUP_ICE)

#define HV_TR_IS_GROUP_INTERNAL(_Group_) \
    (((unsigned long long)(_Group_) > 0) && \
    (((unsigned long long)(_Group_) & HV_TR_ALL_GROUPS_INTERNAL) != 0) && \
    (((unsigned long long)(_Group_) & ((unsigned long long)(_Group_) - 1)) == 0))


//
// Trace Types for the administrative group.
//
#define HV_EVENTLOG_OPERATIONAL_PARTITION_CREATED           0x4101
#define HV_EVENTLOG_OPERATIONAL_PARTITION_DELETED           0x4102
#define HV_EVENTLOG_OPERATIONAL_PARTITION_CREATION_FAILED   0x2103
#define HV_EVENTLOG_ADMIN_TEST                              0x4001

//
// Trace Types for the diagnostic group.
//

//
// Retail Bm Trace Types (0x1D 00-0F)
//
// None.
//

//
// Retail Dm Trace Types (0x1D 10-19).
//
// None.
//

//
// Retail Hc Trace Types (0x1D 1A-1F).
//

#define HV_TR_HC_HYPERCALL                  0x1A

//
// Retail Im Trace Types (0x1D 20-3B).
//

#define HV_TR_IM_GUEST_EXCEPTION            0x20
#define HV_TR_IM_MSR_READ                   0x21
#define HV_TR_IM_MSR_WRITE                  0x22
#define HV_TR_IM_CR_READ                    0x23
#define HV_TR_IM_CR_WRITE                   0x24
#define HV_TR_IM_HLT_INSTRUCTION            0x25
#define HV_TR_IM_MWAIT_INSTRUCTION          0x26
#define HV_TR_IM_CPUID_INSTRUCTION          0x27
#define HV_TR_IM_IO_PORT_READ               0x28
#define HV_TR_IM_IO_PORT_WRITE              0x29
#define HV_TR_IM_EXTERNAL_INTERRUPT         0x2A
#define HV_TR_IM_INTERRUPT_PENDING          0x2B
#define HV_TR_IM_GUEST_SHUTDOWN             0x2C
#define HV_TR_IM_EMULATED_INSTRUCTION       0x2D
#define HV_TR_IM_NMI_INTERRUPT              0x2E
#define HV_TR_IM_INVLPG_INSTRUCTION         0x2F
#define HV_TR_IM_IRET_INSTRUCTION           0x30
#define HV_TR_IM_TASK_SWITCH                0x31
#define HV_TR_IM_INVD_INSTRUCTION           0x32
#define HV_TR_IM_DR_ACCESS                  0x33
#define HV_TR_IM_FERR_FREEZE                0x34
#define HV_TR_IM_REAL_MODE_INTERRUPT        0x35
#define HV_TR_IM_MEMORY_INTERCEPT           0x36
#define HV_TR_IM_REFLECTED_EXCEPTION        0x37

//
// Retail Ic Trace Types (0x1D 3C-3F).
//
// None.
//

//
// Retail Ob Trace Types (0x1D 40-45).
//

#define HV_TR_OB_CREATE_PARTITION           0x40
#define HV_TR_OB_DELETE_PARTITION           0x41

//
// Retail Pt Trace Types (0x1D 46-4A).
//

#define HV_TR_PT_REFERENCE_TIME             0x46

//
// Retail Vp Trace Types (0x1D 4B-4F).
//

#define HV_TR_VP_CREATE_VP                  0x4B
#define HV_TR_VP_DELETE_VP                  0x4C

//
// Retail Synic Trace Types (0x1D 50-65).
//
// None.
//

//
// Retail Synic Timer Trace Types (0x1D 66-6F).
//
// None.
//

//
// Retail Am GVA Trace Types (0x1D 70-97).
//

#define HV_TR_AM_GVA_GROW_VIRTUAL_TLB       0x70
#define HV_TR_AM_GVA_SHRINK_VIRTUAL_TLB     0x71
#define HV_TR_AM_GVA_FLUSH_VIRTUAL_TLB      0x72

//
// Retail Am Trace Types (0x1D 98-AF).
//
// None.
//

//
// Retail Val Trace Types (0x1D A0-A7).
//
// None.
//

//
// Retail Vm Trace Types (0x1D A8-AF).
//
// None.
//

//
// Retail Sch Trace Types (0x1D B0-CD).
//

#define HV_TR_SCH_CONTEXT_SWITCH            0xB0

//
// Retail Th Trace Types (0x1D CE-CF).
//
// None.
//

//
// Retail Ti Trace Types (0x1D D0-DF).
//
// None.
//

//
// Retail Ke Trace Types (0x1D E0-E9).
//

#define HV_TR_KE_OVERRUN                    0xE0
#define HV_TR_KE_OVERRUN_PARAMS             0xE1

//
// Retail Mm Trace Types (0x1D EA-EF).
//
// None.
//

//
// Retail Hypervisor Profiler traces (0x1D F0-F4)
//

#define HV_TR_PROFILER_SAMPLE               0xF0
#define HV_TR_PROFILER_HV_MODULE            0xF1

#if defined(_HV_TEST_FEATURES_ENABLED_) || defined(_PERF_FEATURES_ENABLED_) || \
    defined(_HV_COVERAGE_ENABLED_)

//
// Internal Bm Trace Types (0x1E 00-0F)
//
// None.
//

//
// Internal Dm Trace Types (0x1E 10-19).
//

#define HV_TR_DMP_INTERCEPT                 0x10
#define HV_TR_DMP_DISPATCH_EVENTS           0x11

//
// Internal Hc Trace Types (0x1E 1A-1F).
//
// None.
//

//
// Internal Im Trace Types (0x1E 20-3B).
//

#define HV_TR_IMP_SEND_INTERCEPT_MESSAGE    0x20

//
// Internal Ic Trace Types (0x1E 3C-3F).
//

#define HV_TR_ICP_EMULATE_INSTR             0x3C

//
// Internal Ob Trace Types (0x1E 40-45).
//
// None.
//

//
// Internal Pt Trace Types (0x1E 46-4A).
//
// None.
//

//
// Internal Vp Trace Types (0x1E 4B-4F).
//
// None.
//

//
// Internal Synic Trace Types (0x1E 50-65).
//

#define HV_TR_SYNICP_ASSERT                 0x50
#define HV_TR_SYNICP_EVAL_LOW_PRI           0x51
#define HV_TR_SYNICP_EVAL_IMMEDIATE         0x52
#define HV_TR_SYNICP_EVAL_QUEUE             0x53
#define HV_TR_SYNICP_PENDING                0x54
#define HV_TR_SYNICP_EOI                    0x55
#define HV_TR_SYNICP_LATENCY_EXCEEDED       0x56
#define HV_TR_SYNICP_MARK_PENDING           0x57
#define HV_TR_SYNICP_EVAL_APIC_INTS         0x58
#define HV_TR_SYNICP_READ_APIC_GPA          0x59
#define HV_TR_SYNICP_WRITE_APIC_GPA         0x5A
#define HV_TR_SYNICP_READ_APIC_MSR          0x5B
#define HV_TR_SYNICP_WRITE_APIC_MSR         0x5C
#define HV_TR_SYNICP_EXTERNAL_INT           0x5D
#define HV_TR_SYNICP_APIC_IPI               0x5E
#define HV_TR_SYNICP_SIGNAL_EVENT_PORT      0x5F
#define HV_TR_SYNICP_POST_MESSAGE           0x60

//
// Internal Synic Timer Trace Types (0x1E 66-6F).
//

#define HV_TR_SYNICP_PERIODIC_TIMER_UPDATE  0x66
#define HV_TR_SYNICP_PERIODIC_TIMER_RESET   0x67
#define HV_TR_SYNICP_TIMER_SEND_MESSAGE     0x68
#define HV_TR_SYNICP_TIMER_SCAN_MESSAGE     0x69
#define HV_TR_SYNICP_TIMER_ASSIST_EXPIRE    0x6A

//
// Internal Am GVA Trace Types (0x1E 70-97).
//

#define HV_TR_AMP_GVA_PAGE_FAULT            0x70
#define HV_TR_AMP_GVA_VTLB_WRITABILITY_CHANGE 0x71
#define HV_TR_AMP_GVA_SWITCH_SPACE          0x72
#define HV_TR_AMP_GVA_FLUSH_VA_LOCAL        0x73
#define HV_TR_AMP_GVA_FLUSH_VA_GLOBAL       0x74
#define HV_TR_AMP_GVA_FLUSH_VTLB_RANGE      0x75
#define HV_TR_AMP_GVA_FLUSH_SPACE           0x76
#define HV_TR_AMP_GVA_FLUSH_DOMAIN          0x77
#define HV_TR_AMP_GVA_RESET_DOMAIN          0x78
#define HV_TR_AMP_GVA_TRANSLATE_VA          0x79
#define HV_TR_AMP_GVA_READ_VM               0x7A
#define HV_TR_AMP_GVA_WRITE_VM              0x7B
#define HV_TR_AMP_GVA_RESET_PT              0x7C
#define HV_TR_AMP_GVA_UNLINK_PT             0x7D
#define HV_TR_AMP_GVA_UNLINK_PT_VALIDATE    0x7E
#define HV_TR_AMP_GVA_UNLINK_PT_FILL        0x7F
#define HV_TR_AMP_GVA_UNLINK_PT_LINK        0x80
#define HV_TR_AMP_GVA_UNLINK_PT_RESET       0x81
#define HV_TR_AMP_GVA_UNLINK_PT_EVICT       0x82
#define HV_TR_AMP_GVA_UNLINK_PT_CLEAN       0x83
#define HV_TR_AMP_GVA_CONSTRUCT_PT          0x84
#define HV_TR_AMP_GVA_DESTRUCT_PT           0x85
#define HV_TR_AMP_GVA_WALK_PT               0x86
#define HV_TR_AMP_GVA_WAIT_FOR_PT_FILL      0x87
#define HV_TR_AMP_GVA_CLEAN_SAS             0x88
#define HV_TR_AMP_GVA_CLEAN_SAS_OVERFLOW    0x89
#define HV_TR_AMP_GVA_EVICT_PTS             0x8A
#define HV_TR_AMP_GVA_RECLAIM_PTS           0x8B
#define HV_TR_AMP_GVA_FREE_RECLAIMED_PTS    0x8C
#define HV_TR_AMP_GVA_HASH_PROCESSED        0x8D

//
// Internal Am Trace Types (0x1E 98-9F).
//

#define HV_TR_AMP_MAP_GPA                   0x98
#define HV_TR_AMP_UNMAP_GPA                 0x99

//
// Internal Val Trace Types (0x1E A0-A7).
//
// None.
//

#define HV_TR_VALP_PAUSE_LOOP_EXIT          0xA0

//
// Internal Vm Trace Types (0x1E A8-AF).
//
// None.
//

//
// Internal Sch Trace Types (0x1E B0-CD).
//

#define HV_TR_SCHP_NEXT_THREAD              0xB0
#define HV_TR_SCHP_ADD_LOCAL                0xB1
#define HV_TR_SCHP_EVAL_PRI                 0xB2
#define HV_TR_SCHP_TIMESLICE_MIN            0xB3
#define HV_TR_SCHP_AFFINITY_CHANGE          0xB4
#define HV_TR_SCHP_ADD_DEFERRED             0xB6
#define HV_TR_SCHP_DEFERRED_READY_THREAD    0xB7
#define HV_TR_SCHP_TIMESLICE_END            0xB8
#define HV_TR_SCHP_EVAL_SEND                0xB9
#define HV_TR_SCHP_EVAL_RECV                0xBA
#define HV_TR_SCHP_YIELD                    0xBB
#define HV_TR_SCHP_SET_PRI                  0xBC
#define HV_TR_SCHP_COMPUTE_TIMESLICE        0xBD
#define HV_TR_SCHP_BLOCK_ON_EVENT           0xBE
#define HV_TR_SCHP_UNBLOCK_FROM_EVENT       0xBF
#define HV_TR_SCHP_SIGNAL_EVENT             0xC0
#define HV_TR_SCHP_WATCHDOG                 0xC1
#define HV_TR_SCHP_LOAD_BALANCER            0xC2
#define HV_TR_SCHP_EVAL                     0xC3
#define HV_TR_SCHP_CPU_IDLE                 0xC4
#define HV_TR_SCHP_READY_UNBLOCKED_THREAD   0xC5
#define HV_TR_SCHP_EXPRESS_THREAD           0xC6
#define HV_TR_SCHP_EXPRESS_PROCESS          0xC7
#define HV_TR_SCHP_EVALUATE_CAPS            0xC8
#define HV_TR_SCHP_SET_CAPS_TIMER           0xC9

//
// Internal Th Trace Types (0x1E CE-CF).
//

#define HV_TR_THP_SEND_WORK                 0xCE

//
// Internal Ti Trace Types (0x1E D0-DF).
//

#define HV_TR_TIP_SET_APIC                  0xD0
#define HV_TR_TIP_INT                       0xD1
#define HV_TR_TIP_NEW_TIMER                 0xD2
#define HV_TR_TIP_INSERT_TIMER              0xD3
#define HV_TR_TIP_CALLBACK                  0xD4
#define HV_TR_TIP_REMOTE_REMOVE_TIMER       0xD5

//
// Internal Ke Trace Types (0x1E E0-E9).
//

#define HV_TR_KEP_FLUSH_ENTIRE_HW_TLB       0xE0
#define HV_TR_KEP_FLUSH_HV_HW_TLB           0xE1
#define HV_TR_KEP_FLUSH_MULTIPLE_HW_TLB     0xE2
#define HV_TR_KEP_SIGNAL_PROCESSORS         0xE3
#define HV_TR_KEP_RUN_GUEST                 0xE4
#define HV_TR_KEP_SEND_IPI                  0xE5
#define HV_TR_KEP_SEND_IPI_NO_IPI           0xE6
#define HV_TR_KEP_WAIT_FOR_IPI_BARRIER      0xE7
#define HV_TR_KEP_FLUSH_ENTIRE_HW_CACHE     0xE8

//
// Internal Mm Trace Types (0x1E EA-EF).
//
// None.
//

//
// Internal Tf Trace Types (0x1E FA-FF).
//

#define HV_TR_TF_INTERCEPT                  0xFA

#endif // defined(_HV_TEST_FEATURES_ENABLED_) || defined(_PERF_FEATURES_ENABLED_) || 
       // defined(_HV_COVERAGE_ENABLED_)


#if defined(_HV_ICECAP_ENABLED_)

//
// Internal IceCAP Trace Types (0x1E F0-F9).
//

#define HV_TR_ICE_CALL                      0xF0    // fixed (tffastcap.asm)
#define HV_TR_ICE_RETURN                    0xF1    // fixed (tffastcap.asm)
#define HV_TR_ICE_ACQUIRE                   0xF2
#define HV_TR_ICE_RELEASE                   0xF3

//
// Internal Custom Probe Type.
//

#define HV_TR_ICE_COMMENT                   0xF8

#endif // defined(_HV_ICECAP_ENABLED_)


//
// Thread ID for idle thread.
// HV_TR_THREAD_ID_TEST is a generic ID for all TFE-only threads.
//

#define HV_TR_THREAD_ID_IDLE                0
#define HV_TR_THREAD_ID_TEST                9


//
// Physical nodes are defined by a 32-bit index.
//

typedef unsigned long HV_PHYSICAL_NODE_INDEX, *PHV_PHYSICAL_NODE_INDEX;
#define HV_PHYSICAL_NODE_INDEX_UNSPECIFIED 0xFFFFFFFF

#define HV_X64_MSR_TIME_REF_COUNT      (0x40000020)
#define HV_X64_MSR_STIMER0_CONFIG      (0x400000b0)
#define HV_X64_MSR_STIMER0_COUNT       (0x400000b1)
#define HV_X64_MSR_STIMER1_CONFIG      (0x400000b2)
#define HV_X64_MSR_STIMER1_COUNT       (0x400000b3)
#define HV_X64_MSR_STIMER2_CONFIG      (0x400000b4)
#define HV_X64_MSR_STIMER2_COUNT       (0x400000b5)
#define HV_X64_MSR_STIMER3_CONFIG      (0x400000b6)
#define HV_X64_MSR_STIMER3_COUNT       (0x400000b7)

//
// Define the synthetic timer configuration structure
//
typedef struct _HV_X64_MSR_STIMER_CONFIG_CONTENTS
{
    union
    {
        unsigned long long AsUINT64;
        struct
        {
            unsigned long long Enable     : 1;
            unsigned long long Periodic   : 1;
            unsigned long long Lazy       : 1;
            unsigned long long AutoEnable : 1;
            unsigned long long ApicVector : 8;
            unsigned long long DirectMode : 1;
            unsigned long long ReservedZ1 : 1;
            unsigned long long SINTx      : 4;
            unsigned long long ReservedZ2 :44;
        };
    };
} HV_X64_MSR_STIMER_CONFIG_CONTENTS, *PHV_X64_MSR_STIMER_CONFIG_CONTENTS;

typedef enum _HV_SAVE_RESTORE_STATE_RESULT
{
    HvStateComplete                                    = 0, 
    HvStateIncomplete                                  = 1, 
    HvStateRestorable                                  = 2, 
    HvStateCorruptData                                 = 3, 
    HvStateUnsupportedVersion                          = 4, 
    HvStateProcessorFeatureMismatch                    = 5, 
    HvStateHardwareFeatureMismatch                     = 6, 
    HvStateProcessorCountMismatch                      = 7, 
    HvStateProcessorFlagsMismatch                      = 8, 
    HvStateProcessorIndexMismatch                      = 9, 
    HvStateProcessorInsufficientMemory                 = 10,
    HvStateIncompatibleProcessor                       = 11,
    HvStateProcessorFeatureSse3Mismatch                = 12,
    HvStateProcessorFeatureLahfSahfMismatch            = 13,
    HvStateProcessorFeaturSsse3eMismatch               = 14,
    HvStateProcessorFeatureSse41Mismatch               = 15,
    HvStateProcessorFeatureSse42Mismatch               = 16,
    HvStateProcessorFeatureSse4aMismatch               = 17,
    HvStateProcessorFeatureSse5Mismatch                = 18,
    HvStateProcessorFeaturePopcntMismatch              = 19,
    HvStateProcessorFeatureCmpxchg16bMismatch          = 20,
    HvStateProcessorFeatureAltmovcr8Mismatch           = 21,
    HvStateProcessorFeatureLzcntMismatch               = 22,
    HvStateProcessorFeatureMisalignedSseMismatch       = 23,
    HvStateProcessorFeatureMmxExtMismatch              = 24,
    HvStateProcessorFeature3DNowMismatch               = 25,
    HvStateProcessorFeatureExtended3DNowMismatch       = 26,
    HvStateProcessorFeaturePage1GBMismatch             = 27,
    HvStateProcessorCacheLineFlushSizeMismatch         = 28,
    HvStateProcessorFeatureXsaveMismatch               = 29,
    HvStateProcessorFeatureXsaveoptMismatch            = 30,
    HvStateProcessorFeatureXsaveLegacySseMismatch      = 31,
    HvStateProcessorFeatureXsaveAvxMismatch            = 32,
    HvStateProcessorFeatureXsaveUnknownFeatureMismatch = 33,
    HvStateProcessorXsaveSaveAreaMismatch              = 34
} HV_SAVE_RESTORE_STATE_RESULT, *PHV_SAVE_RESTORE_STATE_RESULT;

typedef unsigned long HV_SAVE_RESTORE_STATE_FLAGS, *PHV_SAVE_RESTORE_STATE_FLAGS;

#define HV_SAVE_RESTORE_STATE_START   0x00000001
#define HV_SAVE_RESTORE_STATE_SUMMARY 0x00000002

//
// Define index of the reference TSC page MSR.
//

#define HV_X64_MSR_REFERENCE_TSC            (0x40000021)

//
// Define contents of the reference TSC MSR.
//

typedef union _HV_X64_MSR_REFERENCE_TSC_CONTENTS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Enable                   : 1;
        unsigned long long ReservedP                : 11;
        unsigned long long GpaPageNumber            : 52;
    };
} HV_X64_MSR_REFERENCE_TSC_CONTENTS, *PHV_X64_MSR_REFERENCE_TSC_CONTENTS;


//
// Define invalid and maximum values of the reference TSC sequence.
//

#define HV_REFERENCE_TSC_SEQUENCE_INVALID   (0x00000000)

//
// Define structure of the reference TSC page.
//
typedef struct _HV_REFERENCE_TSC_PAGE
{
    volatile unsigned long TscSequence;
    unsigned long Reserved1;
    volatile unsigned long long TscScale;
    volatile unsigned long long TscOffset;
    volatile unsigned long long TimelineBias;
    unsigned long long Reserved2[508];
} HV_REFERENCE_TSC_PAGE, *PHV_REFERENCE_TSC_PAGE;

typedef union _HV_PARTITION_PRIVILEGE_MASK
{
    unsigned long long AsUINT64;
    struct
    {
        //
        // Access to virtual MSRs
        //
        unsigned long long  AccessVpRunTimeReg:1;
        unsigned long long  AccessPartitionReferenceCounter:1;
        unsigned long long  AccessSynicRegs:1;
        unsigned long long  AccessSyntheticTimerRegs:1;
        unsigned long long  AccessApicRegs:1;
        unsigned long long  AccessHypercallMsrs:1;
        unsigned long long  AccessVpIndex:1;
// 4.2.2 Partition Privilege Flags
        unsigned long long  AccessResetReg : 1;
        unsigned long long  AccessStatsReg : 1;
        unsigned long long  AccessPartitionReferenceTsc : 1;
        unsigned long long  AccessGuestIdleReg : 1;
        unsigned long long  AccessFrequencyRegs : 1;
        unsigned long long  AccessDebugRegs : 1;
        unsigned long long  AccessReenlightenmentControls : 1;
// Symbol Files
        unsigned long long  AccessRootSchedulerReg : 1;
        unsigned long long  Reserved1:17;

        //
        // Access to hypercalls
        //
        unsigned long long  CreatePartitions:1;
        unsigned long long  AccessPartitionId:1;
        unsigned long long  AccessMemoryPool:1;
        unsigned long long  AdjustMessageBuffers:1;
        unsigned long long  PostMessages:1;
        unsigned long long  SignalEvents:1;
        unsigned long long  CreatePort:1;
        unsigned long long  ConnectPort:1;
 // 4.2.2 Partition Privilege Flags
        unsigned long long  AccessStats : 1;
        unsigned long long  Reserved2 : 2;
        unsigned long long  Debugging : 1;
        unsigned long long  CpuManagement : 1;
        unsigned long long  ConfigureProfiler : 1;
// Symbol Files
        unsigned long long  AccessVpExitTracing : 1;
        unsigned long long  EnableExtendedGvaRangesForFlushVirtualAddressList : 1;
// 4.2.2 Partition Privilege Flags
        unsigned long long  AccessVsm : 1;
        unsigned long long  AccessVpRegisters : 1;
// Symbol Files
        unsigned long long  UnusedBit : 1;
        unsigned long long  FastHypercallOutput : 1;
        // 4.2.2 Partition Privilege Flags
        unsigned long long  EnableExtendedHypercalls : 1;
        unsigned long long  StartVirtualProcessor : 1;
// Symbol Files
        unsigned long long  Isolation : 1;
        unsigned long long  Reserved3 : 9;

    };

} HV_PARTITION_PRIVILEGE_MASK, *PHV_PARTITION_PRIVILEGE_MASK;

typedef enum _HV_PROCESSOR_VENDOR
{
    HvProcessorVendorAmd = 0x0000,
    HvProcessorVendorIntel = 0x0001

} HV_PROCESSOR_VENDOR, *PHV_PROCESSOR_VENDOR;

//
// Define the structure defining the processor related features
// that may be de-featured.
// 

typedef union _HV_PARTITION_PROCESSOR_FEATURES
{
    struct
    {
        unsigned long long Sse3Support:1;
        unsigned long long LahfSahfSupport:1;
        unsigned long long Ssse3Support:1;
        unsigned long long Sse4_1Support:1;
        unsigned long long Sse4_2Support:1;
        unsigned long long Sse4aSupport:1;
        unsigned long long Sse5Support:1;
        unsigned long long PopCntSupport:1;
        unsigned long long Cmpxchg16bSupport:1;
        unsigned long long Altmovcr8Support:1;
        unsigned long long LzcntSupport:1;
        unsigned long long MisAlignSseSupport:1;
        unsigned long long MmxExtSupport:1;
        unsigned long long Amd3DNowSupport:1;
        unsigned long long ExtendedAmd3DNowSupport:1;
        unsigned long long Page1GBSupport:1;
        unsigned long long Reserved1:48;
    };
    unsigned long long AsUINT64;

} HV_PARTITION_PROCESSOR_FEATURES, *PHV_PARTITION_PROCESSOR_FEATURES;

//
// Define the processor features avaialble in Intel and AMD compatibility mode.
//

#define HV_PARTITION_PROCESSOR_FEATURES_INTEL_COMPATIBILITY_MODE \
{   1,   /* Sse3Support */ \
    1,   /* LahfSahfSupport */ \
    0,   /* Ssse3Support */ \
    0,   /* Sse4_1Support */ \
    0,   /* Sse4_2Support */ \
    0,   /* Sse4aSupport */ \
    0,   /* Sse5Support */ \
    0,   /* PopCntSupport */ \
    1,   /* Cmpxchg16bSupport */ \
    0,   /* Altmovcr8Support */ \
    0,   /* LzcntSupport */ \
    0,   /* MisAlignSseSupport */ \
    0,   /* MmxExtSupport */ \
    0,   /* Amd3DNowSupport */ \
    0,   /* ExtendedAmd3DNowSupport */ \
    0,   /* Page1GBSupport */ \
    0    /* Reserved1 */ \
}

#define HV_PARTITION_PROCESSOR_FEATURES_AMD_COMPATIBILITY_MODE \
{ \
    1,   /* Sse3Support */ \
    1,   /* LahfSahfSupport */ \
    0,   /* Ssse3Support */ \
    0,   /* Sse4_1Support */ \
    0,   /* Sse4_2Support */ \
    0,   /* Sse4aSupport */ \
    0,   /* Sse5Support */ \
    0,   /* PopCntSupport */ \
    1,   /* Cmpxchg16bSupport */ \
    1,   /* Altmovcr8Support */ \
    0,   /* LzcntSupport */ \
    0,   /* MisAlignSseSupport */ \
    1,   /* MmxExtSupport */ \
    0,   /* Amd3DNowSupport */ \
    0,   /* ExtendedAmd3DNowSupport */ \
    0,   /* Page1GBSupport */ \
    0    /* Reserved1 */ \
}

//
// Define the structure defining the processor XSAVE related features
// that may be de-featured.
// 

typedef union _HV_PARTITION_PROCESSOR_XSAVE_FEATURES
{
    struct
    {
        unsigned long long XsaveSupport:1;
        unsigned long long XsaveoptSupport:1;
        unsigned long long AvxSupport:1;
        unsigned long long Reserved1:61;
    };
    unsigned long long AsUINT64;

} HV_PARTITION_PROCESSOR_XSAVE_FEATURES, *PHV_PARTITION_PROCESSOR_XSAVE_FEATURES;

//
// Define the processor features avaialble in Intel and AMD compatibility mode.
//

#define HV_PARTITION_PROCESSOR_XSAVE_FEATURES_INTEL_COMPATIBILITY_MODE \
{ \
    0,   /* XsaveSupport */ \
    0,   /* XsaveoptSupport */ \
    0,   /* AvxSupport */ \
    0    /* Reserved1 */ \
}

#define HV_PARTITION_PROCESSOR_XSAVE_FEATURES_AMD_COMPATIBILITY_MODE \
{ \
    0,   /* XsaveSupport */ \
    0,   /* XsaveoptSupport */ \
    0,   /* AvxSupport */ \
    0    /* Reserved1 */ \
}

//
// Define the processor cache line flush size Intel and AMD compatibility mode.
//

#define HV_PARTITION_PROCESSOR_CL_FLUSHSIZE_INTEL_COMPATIBILITY_MODE (8)
#define HV_PARTITION_PROCESSOR_CL_FLUSHSIZE_AMD_COMPATIBILITY_MODE (8)

typedef union _HV_EXPLICIT_SUSPEND_REGISTER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Suspended:1;
        unsigned long long Reserved:63;
    };
} HV_EXPLICIT_SUSPEND_REGISTER, *PHV_EXPLICIT_SUSPEND_REGISTER;

typedef union _HV_INTERCEPT_SUSPEND_REGISTER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Suspended:1;
        unsigned long long TlbLocked:1;
        unsigned long long Reserved:62;
    };
} HV_INTERCEPT_SUSPEND_REGISTER, *PHV_INTERCEPT_SUSPEND_REGISTER;

typedef union _HV_DISPATCH_SUSPEND_REGISTER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Suspended    : 1;
        unsigned long long Reserved     : 63;
    };
} HV_DISPATCH_SUSPEND_REGISTER, *PHV_DISPATCH_SUSPEND_REGISTER;

typedef union _HV_X64_INTERRUPT_STATE_REGISTER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long InterruptShadow:1;
        unsigned long long NmiMasked:1;
        unsigned long long Reserved:62;
    };
} HV_X64_INTERRUPT_STATE_REGISTER, *PHV_X64_INTERRUPT_STATE_REGISTER;

typedef union _HV_X64_MSR_NPIEP_CONFIG_CONTENTS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long PreventSgdt  : 1;
        unsigned long long PreventSidt  : 1;
        unsigned long long PreventSldt  : 1;
        unsigned long long PreventStr   : 1;
        unsigned long long Reserved     : 60;
    };
} HV_X64_MSR_NPIEP_CONFIG_CONTENTS, *PHV_X64_MSR_NPIEP_CONFIG_CONTENTS;

typedef enum _HV_X64_PENDING_INTERRUPTION_TYPE
{
    HvX64PendingInterrupt                   = 0,
    HvX64PendingNmi                         = 2,
    HvX64PendingException                   = 3,
    HvX64PendingSoftwareInterrupt           = 4,
    HvX64PendingPrivilegedSoftwareException = 5,
    HvX64PendingSoftwareException           = 6
} HV_X64_PENDING_INTERRUPTION_TYPE, *PHV_X64_PENDING_INTERRUPTION_TYPE;

typedef union _HV_X64_PENDING_INTERRUPTION_REGISTER
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long InterruptionPending:1;
        unsigned long InterruptionType:3;
        unsigned long DeliverErrorCode : 1;
        unsigned long InstructionLength : 4;
        unsigned long NestedEvent : 1;
        unsigned long Reserved:6;
        unsigned long InterruptionVector:16;
        unsigned long ErrorCode;
    };
} HV_X64_PENDING_INTERRUPTION_REGISTER, *PHV_X64_PENDING_INTERRUPTION_REGISTER;

typedef enum _HV_X64_PENDING_EVENT_TYPE
{
    HvX64PendingEventException              = 0,
    HvX64PendingEventMemoryIntercept        = 1,
    HvX64PendingEventNestedMemoryIntercept  = 2,
    HvX64PendingEventVirtualizationFault    = 3,
    HvX64PendingEventHypercallOutput        = 4,
    HvX64PendingExtInt                      = 5,
    HvX64PendingEventShadowIpt              = 6
} HV_X64_PENDING_EVENT_TYPE, * PHV_X64_PENDING_EVENT_TYPE;

typedef union _HV_X64_PENDING_EXCEPTION_EVENT
{
    unsigned long long AsUINT64[2];
    struct
    {
        struct
        {
            unsigned long EventPending     : 1;
            unsigned long EventType        : 3;
            unsigned long Reserved0        : 4;
            unsigned long DeliverErrorCode : 1;
            unsigned long Reserved1        : 7;
            unsigned long Vector           : 16;
        };
        unsigned long ErrorCode;
        unsigned long long ExceptionParameter;
    };
} HV_X64_PENDING_EXCEPTION_EVENT, *PHV_X64_PENDING_EXCEPTION_EVENT;

typedef union _HV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT
{
    unsigned long long AsUINT64[2];
    struct
    {
        struct
        {
            unsigned long EventPending     : 1;
            unsigned long EventType        : 3;
            unsigned long Reserved0        : 4;
            unsigned long Reserved1        : 8;
            unsigned long Parameter0       : 16;
        };
        unsigned long Code;
        unsigned long long Parameter1;
    };
} HV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT, *PHV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT;

typedef union _HV_REGISTER_VALUE
{
    HV_UINT128                                  Reg128;
    unsigned long long                                      Reg64;
    unsigned long                                      Reg32;
    unsigned short                                      Reg16;
    unsigned char                                       Reg8;
    HV_X64_FP_REGISTER                          Fp;
    HV_X64_FP_CONTROL_STATUS_REGISTER           FpControlStatus;
    HV_X64_XMM_CONTROL_STATUS_REGISTER          XmmControlStatus;
    HV_X64_SEGMENT_REGISTER                     Segment;
    HV_X64_TABLE_REGISTER                       Table;
    HV_EXPLICIT_SUSPEND_REGISTER                ExplicitSuspend;
    HV_INTERCEPT_SUSPEND_REGISTER               InterceptSuspend;
    HV_DISPATCH_SUSPEND_REGISTER                DispatchSuspend;
    HV_X64_INTERRUPT_STATE_REGISTER             InterruptState;
    HV_X64_PENDING_INTERRUPTION_REGISTER        PendingInterruption;
    HV_X64_MSR_NPIEP_CONFIG_CONTENTS            NpiepConfig;
    HV_X64_PENDING_EXCEPTION_EVENT              PendingExceptionEvent;
    HV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT   PendingVirtualizationFaultEvent;
} HV_REGISTER_VALUE, *PHV_REGISTER_VALUE;
typedef const HV_REGISTER_VALUE *PCHV_REGISTER_VALUE;

//
// Define the intercept access types.
//

typedef unsigned char HV_INTERCEPT_ACCESS_TYPE;

#define HV_INTERCEPT_ACCESS_READ    0
#define HV_INTERCEPT_ACCESS_WRITE   1
#define HV_INTERCEPT_ACCESS_EXECUTE 2

typedef unsigned long HV_INTERCEPT_ACCESS_TYPE_MASK;

#define HV_INTERCEPT_ACCESS_MASK_NONE       0x00
#define HV_INTERCEPT_ACCESS_MASK_READ       0X01
#define HV_INTERCEPT_ACCESS_MASK_WRITE      0x02
#define HV_INTERCEPT_ACCESS_MASK_EXECUTE    0x04


//
// Define intercept types.
//
typedef enum _HV_INTERCEPT_TYPE
{
    //
    // Platform-specific intercept types.
    //
    HvInterceptTypeX64IoPort = 0x00000000,
    HvInterceptTypeX64Msr = 0x00000001,
    HvInterceptTypeX64Cpuid = 0x00000002,
    HvInterceptTypeX64Exception = 0x00000003,

} HV_INTERCEPT_TYPE, *PHV_INTERCEPT_TYPE;


//
// Define IO port type.
//
typedef unsigned short HV_X64_IO_PORT, *PHV_X64_IO_PORT;


//
// Define intercept parameters.
//
typedef union _HV_INTERCEPT_PARAMETERS
{
    //
    // HV_INTERCEPT_PARAMETERS is defined to be an 8-byte field.
    //
    unsigned long long AsUINT64;

    //
    // HvInterceptTypeX64IoPort.
    //
    HV_X64_IO_PORT IoPort;

    //
    // HvInterceptTypeX64Cpuid.
    //
    unsigned long CpuidIndex;

    //
    // HvInterceptTypeX64Exception.
    //
    unsigned short ExceptionVector;

    //
    // N.B. Other intercept types do not have any paramaters.
    //

} HV_INTERCEPT_PARAMETERS, *PHV_INTERCEPT_PARAMETERS;


//
// Define intercept descriptor structure.
//
typedef struct  _HV_INTERCEPT_DESCRIPTOR
{
    HV_INTERCEPT_TYPE Type;
    HV_INTERCEPT_PARAMETERS Parameters;
} HV_INTERCEPT_DESCRIPTOR, *PHV_INTERCEPT_DESCRIPTOR;
typedef const HV_INTERCEPT_DESCRIPTOR *PCHV_INTERCEPT_DESCRIPTOR;

//
// Virtual Processor Indices
//
typedef unsigned long HV_VP_INDEX, *PHV_VP_INDEX;

#define HV_MAX_VP_INDEX (63)

// 7.8.1 Virtual Processor Index
#define HV_ANY_VP ((HV_VP_INDEX)-1)
#define HV_VP_INDEX_SELF ((HV_VP_INDEX)-2) 

//
// Declare the MSR for determining the current VP index.
//
#define HV_X64_MSR_VP_INDEX     0x40000002

//
// Declare the VP run time MSR.
//
#define HV_X64_MSR_VP_RUNTIME   0x40000010


// 15.15.1 Type Definitions
// VTL definition
typedef unsigned char HV_VTL;

// Input for targeting a specific VTL.

typedef union
{
    unsigned char AsUINT8;
    struct
    {
        unsigned char TargetVtl : 4;
        unsigned char UseTargetVtl : 1;
        unsigned char ReservedZ : 3;
    };
} HV_INPUT_VTL;

//
// Scheduling control
//
typedef union _HV_SCHEDULING_CONTROL
{
    unsigned long long AsUINT64;

    struct
    {
        unsigned long long  DeterministicTsc:1;
        unsigned long long  Reserved:63;
    };

} HV_SCHEDULING_CONTROL, *PHV_SCHEDULING_CONTROL;

//
// Typedefs for CPUID leaves on HvMicrosoftHypercallInterface-supporting
// hypervisors.
// =====================================================================
//

//
// Microsoft hypervisor interface signature.
//
typedef enum _HV_HYPERVISOR_INTERFACE
{
    HvMicrosoftHypervisorInterface = '1#vH',
    HvMicrosoftXboxNanovisor = 'vnbX'
} HV_HYPERVISOR_INTERFACE, *PHV_HYPERVISOR_INTERFACE;


//
// Version info reported by both guest OS's and hypervisors
//
typedef enum _HV_SERVICE_BRANCH
{
    //
    // [General Distribution Release (GDR) Branch]
    //
    // This branch extends main releases and service pack releases with
    // patches that are generally distributed and recommended to all customers,
    // such as critical fixes.
    //
    // Unmodified main releases and service pack releases are members of this
    // branch.
    //
    HvServiceBranchGdr = 0x00000000,

    //
    // [Quality Fix Engineering (QFE) Branch]
    //
    // This branch extends main releases and service pack releases with
    // patches that are not generally distributed to all customers, such as
    // feature enhancements.
    //
    HvServiceBranchQfe = 0x00000001

} HV_SERVICE_BRANCH, *PHV_SERVICE_BRANCH;

//
// Version info reported by hypervisors
//
typedef struct _HV_HYPERVISOR_VERSION_INFO
{
    unsigned long BuildNumber;

    unsigned long MinorVersion:16;
    unsigned long MajorVersion:16;

    unsigned long ServicePack;

    unsigned long ServiceNumber:24;
    unsigned long ServiceBranch:8; // Type is HV_SERVICE_BRANCH

} HV_HYPERVISOR_VERSION_INFO, *PHV_HYPERVISOR_VERSION_INFO;

//
// The below CPUID leaves are present if VersionAndFeatures.HypervisorPresent
// is set by CPUID(HvCpuIdFunctionVersionAndFeatures).
// ==========================================================================
//

typedef enum _HV_CPUID_FUNCTION
{
    HvCpuIdFunctionVersionAndFeatures           = 0x00000001,
    HvCpuIdFunctionHvVendorAndMaxFunction       = 0x40000000,
    HvCpuIdFunctionHvInterface                  = 0x40000001,

    //
    // The remaining functions depend on the value of HvCpuIdFunctionInterface
    //
    HvCpuIdFunctionMsHvVersion                  = 0x40000002,
    HvCpuIdFunctionMsHvFeatures                 = 0x40000003,
    HvCpuIdFunctionMsHvEnlightenmentInformation = 0x40000004,
    HvCpuIdFunctionMsHvImplementationLimits     = 0x40000005,
    HvCpuIdFunctionMsHvHardwareFeatures         = 0x40000006,
    HvCpuIdFunctionMsHvCpuManagementFeatures    = 0x40000007,
    HvCpuIdFunctionMsHvSvmFeatures              = 0x40000008,
    HvCpuIdFunctionMsHvSkipLevelFeatures        = 0x40000009,
    HvCpuidFunctionMsHvNestedVirtFeatures       = 0x4000000a,
    HvCpuidFunctionMsHvIptFeatures              = 0x4000000b,

    HvCpuIdFunctionMaxReserved                  = 0x4000000b

} HV_CPUID_FUNCTION, *PHV_CPUID_FUNCTION;

typedef union _HV_X64_PLATFORM_CAPABILITIES
{
    unsigned long long AsUINT64[2];
    struct
    {
        //
        // Eax
        //
        struct
        {
            unsigned long AllowRedSignedCode : 1;
            unsigned long AllowKernelModeDebugging : 1;
            unsigned long AllowUserModeDebugging : 1;
            unsigned long AllowTelnetServer : 1;
            unsigned long AllowIOPorts : 1;
            unsigned long AllowFullMsrSpace : 1;
            unsigned long AllowPerfCounters : 1;
            unsigned long AllowHost512MB : 1;
            unsigned long AllowNextGenerationSupport : 1;
            unsigned long AllowRemoteRecovery : 1;
            unsigned long AllowStreaming : 1;
            unsigned long AllowPushDeployment : 1;
            unsigned long AllowPullDeployment : 1;
            unsigned long AllowProfiling : 1;
            unsigned long AllowJsProfiling : 1;
            unsigned long AllowCrashDump : 1;
            unsigned long AllowVsCrashDump : 1;
            unsigned long AllowToolFileIO : 1;
            unsigned long AllowConsoleMgmt : 1;
            unsigned long AllowTracing : 1;
            unsigned long AllowXStudio : 1;
            unsigned long AllowGestureBuilder : 1;
            unsigned long AllowSpeechLab : 1;
            unsigned long AllowSmartglassStudio : 1;
            unsigned long AllowNetworkTools : 1;
            unsigned long AllowTcrTool : 1;
            unsigned long AllowHostNetworkStack : 1;
            unsigned long AllowSystemUpdateTest : 1;
            unsigned long AllowOffChipPerfCtrStreaming : 1;
            unsigned long AllowToolingMemory : 1;
            unsigned long AllowSystemDowngrade : 1;
            unsigned long AllowGreenDiskLicenses : 1;
        };

        //
        // Ebx
        //
        struct
        {
            unsigned long IsLiveConnected : 1;
            unsigned long IsMteBoosted : 1;
            unsigned long IsQaSlt : 1;
            unsigned long IsStockImage : 1;
            unsigned long IsMsTestLab : 1;
            unsigned long IsRetailDebugger : 1;
            unsigned long IsXvdSrt : 1;
            unsigned long IsGreenDebug : 1;
            unsigned long IsHwDevTest : 1;
            unsigned long AllowDiskLicenses : 1;
            unsigned long AllowInstrumentation : 1;
            unsigned long AllowWifiTester : 1;
            unsigned long AllowWifiTesterDFS : 1;
            unsigned long IsHwTest : 1;
            unsigned long AllowHostOddTest : 1;
            unsigned long IsLiveUnrestricted : 1;
            unsigned long AllowDiscLicensesWithoutMediaAuth : 1;
            unsigned long ReservedEbx : 15;
        };

        //
        // Ecx
        //
        unsigned long ReservedEcx;

        //
        // Edx
        //
        struct
        {
            unsigned long ReservedEdx : 31;
            unsigned long UseAlternateXvd : 1;
        };
    };
} HV_X64_PLATFORM_CAPABILITIES, * PHV_X64_PLATFORM_CAPABILITIES;

typedef union _HV_HYPERVISOR_NESTED_VIRT_FEATURES
{
    unsigned long long AsUINT64[2];
    struct
    {
        //
        // Eax
        //
        struct
        {
            unsigned long EnlightenedVmcsVersionLow : 8;
            unsigned long EnlightenedVmcsVersionHigh : 8;
            unsigned long FlushGuestPhysicalHypercall_Deprecated : 1;
            unsigned long NestedFlushVirtualHypercall : 1;
            unsigned long FlushGuestPhysicalHypercall : 1;
            unsigned long MsrBitmap : 1;
            unsigned long VirtualizationException : 1;
            unsigned long Reserved0 : 11;
        };

        //
        // Ebx
        //
        unsigned long ReservedEbx;

        //
        // Ecx
        //
        unsigned long ReservedEcx;

        //
        // Edx
        //
        unsigned long ReservedEdx;
    };
} HV_HYPERVISOR_NESTED_VIRT_FEATURES, *PHV_HYPERVISOR_NESTED_VIRT_FEATURES;

typedef struct _HV_VENDOR_AND_MAX_FUNCTION
{
    //
    // Eax
    //
    unsigned long MaxFunction;

    //
    // Ebx, Ecx, Edx
    //
    unsigned char VendorName[12];
} HV_VENDOR_AND_MAX_FUNCTION, *PHV_VENDOR_AND_MAX_FUNCTION;

typedef struct _HV_IMPLEMENTATION_LIMITS
{
    //
    // Eax
    //
    unsigned long MaxVirtualProcessorCount;

    //
    // Ebx
    //
    unsigned long MaxLogicalProcessorCount;

    //
    // Ecx
    //
    unsigned long MaxInterruptMappingCount;

    //
    // Edx
    //
    unsigned long Reserved;
} HV_IMPLEMENTATION_LIMITS, *PHV_IMPLEMENTATION_LIMITS;

typedef struct _HV_HYPERVISOR_INTERFACE_INFO
{
    //
    // Eax
    //
    unsigned long Interface;

    //
    // Ebx
    //
    unsigned long Reserved1;

    //
    // Ecx
    //
    unsigned long Reserved2;

    //
    // Edx
    //
    unsigned long Reserved3;
} HV_HYPERVISOR_INTERFACE_INFO, *PHV_HYPERVISOR_INTERFACE_INFO;

typedef struct _HV_X64_HYPERVISOR_FEATURES
{
    //
    // Eax, Ebx
    //
    HV_PARTITION_PRIVILEGE_MASK PartitionPrivileges;

    //
    // Ecx
    //
    struct
    {
        unsigned long MaxSupportedCState : 4;
        unsigned long HpetNeededForC3PowerState_Deprecated : 1;
        unsigned long Reserved : 27;
    };

    //
    // Edx
    //
    struct
    {
        unsigned long MwaitAvailable_Deprecated : 1;
        unsigned long GuestDebuggingAvailable : 1;
        unsigned long PerformanceMonitorsAvailable : 1;
        unsigned long CpuDynamicPartitioningAvailable : 1;
        unsigned long XmmRegistersForFastHypercallAvailable : 1;
        unsigned long GuestIdleAvailable : 1;
        unsigned long HypervisorSleepStateSupportAvailable : 1;
        unsigned long NumaDistanceQueryAvailable : 1;
        unsigned long FrequencyRegsAvailable : 1;
        unsigned long SyntheticMachineCheckAvailable : 1;
        unsigned long GuestCrashRegsAvailable : 1;
        unsigned long DebugRegsAvailable : 1;
        unsigned long Npiep1Available : 1;
        unsigned long DisableHypervisorAvailable : 1;
        unsigned long ExtendedGvaRangesForFlushVirtualAddressListAvailable : 1;
        unsigned long FastHypercallOutputAvailable : 1;
        unsigned long SvmFeaturesAvailable : 1;
        unsigned long SintPollingModeAvailable : 1;
        unsigned long HypercallMsrLockAvailable : 1;
        unsigned long DirectSyntheticTimers : 1;
        unsigned long RegisterPatAvailable : 1;
        unsigned long RegisterBndcfgsAvailable : 1;
        unsigned long WatchdogTimerAvailable : 1;
        unsigned long SyntheticTimeUnhaltedTimerAvailable : 1;
        unsigned long DeviceDomainsAvailable : 1;
        unsigned long S1DeviceDomainsAvailable : 1;
        unsigned long LbrAvailable : 1;
        unsigned long IptAvailable : 1;
        unsigned long CrossVtlFlushAvailable : 1;
        unsigned long Reserved1 : 3;
    };
} HV_X64_HYPERVISOR_FEATURES, *PHV_X64_HYPERVISOR_FEATURES;

typedef struct _HV_X64_HYPERVISOR_HARDWARE_FEATURES
{
    //
    // Eax
    //
    struct
    {
        unsigned long ApicOverlayAssistInUse : 1;
        unsigned long MsrBitmapsInUse : 1;
        unsigned long ArchitecturalPerformanceCountersInUse : 1;
        unsigned long SecondLevelAddressTranslationInUse : 1;
        unsigned long DmaRemappingInUse : 1;
        unsigned long InterruptRemappingInUse : 1;
        unsigned long MemoryPatrolScrubberPresent : 1;
        unsigned long DmaProtectionInUse : 1;
        unsigned long HpetRequested : 1;
        unsigned long SyntheticTimersVolatile : 1;
        unsigned long HypervisorLevel : 4;
        unsigned long PhysicalDestinationModeRequired : 1;
        unsigned long UseVmfuncForAliasMapSwitch : 1;
        unsigned long HvRegisterForMemoryZeroingSupported : 1;
        unsigned long UnrestrictedGuestSupported : 1;
        unsigned long RdtAFeaturesSupported : 1;
        unsigned long RdtMFeaturesSupported : 1;
        unsigned long ChildPerfmonPmuSupported : 1;
        unsigned long ChildPerfmonLbrSupported : 1;
        unsigned long ChildPerfmonIptSupported : 1;
        unsigned long Reserved : 9;
    };

    //
    // Ebx
    //
    unsigned long ReservedEbx;

    //
    // Ecx
    //
    unsigned long ReservedEcx;

    //
    // Edx
    //
    unsigned long ReservedEdx;
} HV_X64_HYPERVISOR_HARDWARE_FEATURES, *PHV_X64_HYPERVISOR_HARDWARE_FEATURES;

typedef struct _HV_X64_ENLIGHTENMENT_INFORMATION
{
    struct
    {
        unsigned long UseHypercallForAddressSpaceSwitch : 1;
        unsigned long UseHypercallForLocalFlush : 1;
        unsigned long UseHypercallForRemoteFlushAndLocalFlushEntire : 1;
        unsigned long UseApicMsrs : 1;
        unsigned long UseHvRegisterForReset : 1;
        unsigned long UseRelaxedTiming : 1;
        unsigned long UseDmaRemapping_Deprecated : 1;
        unsigned long UseInterruptRemapping_Deprecated : 1;
        unsigned long UseX2ApicMsrs : 1;
        unsigned long DeprecateAutoEoi : 1;
        unsigned long UseSyntheticClusterIpi : 1;
        unsigned long UseExProcessorMasks : 1;
        unsigned long Nested : 1;
        unsigned long UseIntForMbecSystemCalls : 1;
        unsigned long UseVmcsEnlightenments : 1;
        unsigned long UseSyncedTimeline : 1;
        unsigned long Available : 1;
        unsigned long UseDirectLocalFlushEntire : 1;
        unsigned long NoNonArchitecturalCoreSharing : 1;
        unsigned long Reserved : 13;
    };

    //
    // Ebx
    //
    unsigned long LongSpinWaitCount;

    //
    // Ecx
    //
    struct
    {
        unsigned long ImplementedPhysicalAddressBits : 7;
        unsigned long ReservedEcx : 25;
    };

    //
    // Edx
    //
    unsigned long ReservedEdx;
} HV_X64_ENLIGHTENMENT_INFORMATION, *PHV_X64_ENLIGHTENMENT_INFORMATION;

typedef struct _HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES
{
    //
    // Eax
    //
    struct
    {
        unsigned long StartLogicalProcessor : 1;
        unsigned long CreateRootVirtualProcessor : 1;
        unsigned long PerformanceCounterSync : 1;
        unsigned long Reserved0 : 28;
        unsigned long ReservedIdentityBit : 1;
    };

    //
    // Ebx
    //
    struct
    {
            unsigned long ProcessorPowerManagement : 1;
            unsigned long MwaitIdleStates : 1;
            unsigned long LogicalProcessorIdling : 1;
            unsigned long Reserved1 : 29;
    };

    //
    // Ecx
    //
    struct
    {
        unsigned long RemapGuestUncached : 1;
        unsigned long ReservedZ2 : 31;
    };

    //
    // Edx
    //
    unsigned long ReservedEdx;
} HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES, *PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES;

typedef struct _HV_HYPERVISOR_SVM_FEATURES
{
    //
    // Eax
    //
    struct
    {
        unsigned long SvmSupported : 1;
        unsigned long Reserved0 : 10;
        unsigned long MaxPasidSpacePasidCount : 21;
    };

    //
    // Ebx
    //
    unsigned long MaxPasidSpaceCount;

    //
    // Ecx
    //
    unsigned long MaxDevicePrqSize;

    //
    // Edx
    //
    unsigned long Reserved1;
} HV_HYPERVISOR_SVM_FEATURES, *PHV_HYPERVISOR_SVM_FEATURES;

typedef struct _HV_HYPERVISOR_IPT_FEATURES
{
    //
    // Eax
    //
    struct
    {
        unsigned long ChainedToPA : 1;
        unsigned long Enlightened : 1;
        unsigned long Reserved0 : 10;
        unsigned long MaxTraceBufferSizePerVtl : 20;
    };

    //
    // Ebx
    //
    unsigned long Reserved1;

    //
    // Ecx
    //
    unsigned long Reserved2;

    //
    // Edx
    //
    struct
    {
        unsigned long HypervisorIpt : 1;
        unsigned long Reserved3 : 31;
    };
} HV_HYPERVISOR_IPT_FEATURES, *PHV_HYPERVISOR_IPT_FEATURES;

typedef union _HV_CPUID_RESULT
{
    struct
    {
        unsigned long Eax;
        unsigned long Ebx;
        unsigned long Ecx;
        unsigned long Edx;
    };

    unsigned long AsUINT32[4];

    struct
    {
        //
        // Eax
        //
        unsigned long ReservedEax;

        //
        // Ebx
        //
        unsigned long ReservedEbx:24;
        unsigned long InitialApicId:8;

        //
        // Ecx
        //
        unsigned long ReservedEcx:31;
        unsigned long HypervisorPresent:1;

        //
        // Edx
        //
        unsigned long ReservedEdx;

    } VersionAndFeatures;

    HV_X64_PLATFORM_CAPABILITIES MsHvPlatformCapabilities;
    HV_HYPERVISOR_NESTED_VIRT_FEATURES MsHvNestedVirtFeatures;
    HV_VENDOR_AND_MAX_FUNCTION HvVendorAndMaxFunction;
    HV_HYPERVISOR_INTERFACE_INFO HvInterface;
    HV_HYPERVISOR_VERSION_INFO MsHvVersion;
    HV_X64_HYPERVISOR_FEATURES MsHvFeatures;
    HV_X64_ENLIGHTENMENT_INFORMATION MsHvEnlightenmentInformation;
    HV_IMPLEMENTATION_LIMITS MsHvImplementationLimits;
    HV_X64_HYPERVISOR_HARDWARE_FEATURES MsHvHardwareFeatures;
    HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES MsHvCpuManagementFeatures;
    HV_HYPERVISOR_SVM_FEATURES MsHvSvmFeatures;
    HV_HYPERVISOR_IPT_FEATURES MsHvIptFeatures;

} HV_CPUID_RESULT, *PHV_CPUID_RESULT;

#define HV_CPUID_HV_VENDOR_MICROSOFT_EBX 'rciM'
#define HV_CPUID_HV_VENDOR_MICROSOFT_ECX 'foso'
#define HV_CPUID_HV_VENDOR_MICROSOFT_EDX 'vH t'

//
// Address spaces presented by the guest.
//
typedef unsigned long long HV_ADDRESS_SPACE_ID, *PHV_ADDRESS_SPACE_ID;

//
// Address space flush flags.
//
typedef unsigned long long HV_FLUSH_FLAGS, *PHV_FLUSH_FLAGS;

#define HV_FLUSH_ALL_PROCESSORS              (0x00000001)
#define HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES  (0x00000002)
#define HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY    (0x00000004)
#define HV_FLUSH_USE_EXTENDED_RANGE_FORMAT   (0x00000008)
#define HV_FLUSH_MASK                        (HV_FLUSH_ALL_PROCESSORS | \
                                              HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES | \
                                              HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY | \
                                              HV_FLUSH_USE_EXTENDED_RANGE_FORMAT)

//
// Address translation flags.
//
typedef unsigned long long HV_TRANSLATE_GVA_CONTROL_FLAGS;

#define HV_TRANSLATE_GVA_VALIDATE_READ       (0x0001)
#define HV_TRANSLATE_GVA_VALIDATE_WRITE      (0x0002)
#define HV_TRANSLATE_GVA_VALIDATE_EXECUTE    (0x0004)
#define HV_TRANSLATE_GVA_PRIVILEGE_EXEMPT    (0x0008)
#define HV_TRANSLATE_GVA_SET_PAGE_TABLE_BITS (0x0010)
#define HV_TRANSLATE_GVA_TLB_FLUSH_INHIBIT   (0x0020)
#define HV_TRANSLATE_GVA_CONTROL_MASK        (0x003F)
#define HV_TRANSLATE_GVA_INPUT_VTL_MASK      (0xFF00000000000000UI64)

typedef unsigned long long HV_TRANSLATE_GVA_CONTROL_FLAGS, *PHV_TRANSLATE_GVA_CONTROL_FLAGS;

typedef enum _HV_TRANSLATE_GVA_RESULT_CODE
{
    HvTranslateGvaSuccess                 = 0,

    // Translation Failures
    HvTranslateGvaPageNotPresent          = 1,
    HvTranslateGvaPrivilegeViolation      = 2,
    HvTranslateGvaInvalidPageTableFlags   = 3,

    // GPA access failures
    HvTranslateGvaGpaUnmapped             = 4,
    HvTranslateGvaGpaNoReadAccess         = 5,
    HvTranslateGvaGpaNoWriteAccess        = 6,
    HvTranslateGvaGpaIllegalOverlayAccess = 7,
    HvTranslateGvaIntercept               = 8

} HV_TRANSLATE_GVA_RESULT_CODE, *PHV_TRANSLATE_GVA_RESULT_CODE;

typedef union _HV_TRANSLATE_GVA_RESULT
{
    unsigned long long AsUINT64;
    struct
    {
        HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
        unsigned long CacheType : 8;
        unsigned long OverlayPage : 1;
        unsigned long Reserved : 23;
    };
} HV_TRANSLATE_GVA_RESULT, *PHV_TRANSLATE_GVA_RESULT;

typedef struct
{
    HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
    unsigned long CacheType : 8;
    unsigned long OverlayPage : 1;
    unsigned long Reserved : 23;
    /* not in spec HV_X64_PENDING_EVENT EventInfo; */
} HV_TRANSLATE_GVA_RESULT_EX;

//
// Read and write GPA access flags.
//

typedef union _HV_ACCESS_GPA_CONTROL_FLAGS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long CacheType : 8;  // Cache type for access
        unsigned long long Reserved  : 56;
    };
} HV_ACCESS_GPA_CONTROL_FLAGS, *PHV_ACCESS_GPA_CONTROL_FLAGS;

typedef enum _HV_ACCESS_GPA_RESULT_CODE
{
    HvAccessGpaSuccess              = 0,

    // GPA access failures
    HvAccessGpaUnmapped             = 1,
    HvAccessGpaReadIntercept        = 2,
    HvAccessGpaWriteIntercept       = 3,
    HvAccessGpaIllegalOverlayAccess = 4

} HV_ACCESS_GPA_RESULT_CODE, *PHV_ACCESS_GPA_RESULT_CODE;

typedef union _HV_ACCESS_GPA_RESULT
{
    unsigned long long AsUINT64;
    struct
    {
        HV_ACCESS_GPA_RESULT_CODE ResultCode;
        unsigned long                    Reserved;
    };
} HV_ACCESS_GPA_RESULT, *PHV_ACCESS_GPA_RESULT;

//
// Cache types.
//
typedef enum _HV_CACHE_TYPE
{
    HvCacheTypeX64Uncached       = 0,
    HvCacheTypeX64WriteCombining = 1,
    HvCacheTypeX64WriteThrough   = 4,
    HvCacheTypeX64WriteProtected = 5,
    HvCacheTypeX64WriteBack      = 6
} HV_CACHE_TYPE, *PHV_CACHE_TYPE;

//
// Flags to describe the access a partition has to a GPA page.
//
typedef unsigned long HV_MAP_GPA_FLAGS;

#define HV_MAP_GPA_READABLE     (0x00000001)
#define HV_MAP_GPA_WRITABLE     (0x00000002)
#define HV_MAP_GPA_EXECUTABLE   (0x00000004)

//
// Gva Range
//
// The GVA range is a compressed range of GVA used by the TLB flush
// routines.
//

typedef union _HV_GVA_RANGE
{
    unsigned long long AsUINT64;

    struct
    {
        //
        // Additional pages supplies the number of pages beyond one.
        //

        unsigned long long AdditionalPages : 12;

        //
        // GvaPageNumber supplies the top 54 most significant bits of the
        // guest virtual address space.
        //

        unsigned long long GvaPageNumber   : 52;
    };
} HV_GVA_RANGE, *PHV_GVA_RANGE;

typedef enum _HV_X64_SYNTHETIC_MSR
{
    HvSyntheticMsrGuestOsId = 0x40000000,
    HvSyntheticMsrHypercall = 0x40000001,
    HvSyntheticMsrVpIndex = 0x40000002,
    HvSyntheticMsrReset = 0x40000003,
    HvSyntheticMsrCpuMgmtVersion = 0x40000004,
    XbSyntheticMsrTbFlushHost = 0x40000006,
    XbSyntheticMsrTbFlush = 0x40000007,
    XbSyntheticMsrCrash = 0x40000008,
    XbSyntheticMsrGuestOsType = 0x40000009,
    HvSyntheticMsrVpRuntime = 0x40000010,
    XbSyntheticMsrRefTimeOffset = 0x40000011,
    XbSyntheticMsrRefTscScale = 0x40000012,
    XbSyntheticMsrVpCount = 0x40000013,
    XbSyntheticMsrWbinvd = 0x40000014,
    XbSyntheticMsrFlushWb = 0x40000015,
    XbSyntheticMsrFlushTbCurrent = 0x40000016,
    XbSyntheticMsrKcfgDone = 0x40000017,
    XbSyntheticMsrClearSignaturePage = 0x40000018,
    HvSyntheticMsrTimeRefCount = 0x40000020,
    HvSyntheticMsrReferenceTsc = 0x40000021,
    HvSyntheticMsrTscFrequency = 0x40000022,
    HvSyntheticMsrApicFrequency = 0x40000023,
    HvSyntheticMsrNpiepConfig = 0x40000040,
    HvSyntheticMsrEoi = 0x40000070,
    HvSyntheticMsrIcr = 0x40000071,
    HvSyntheticMsrTpr = 0x40000072,
    HvSyntheticMsrVpAssistPage = 0x40000073,
    HvSyntheticMsrSControl = 0x40000080,
    HvSyntheticMsrSVersion = 0x40000081,
    HvSyntheticMsrSiefp = 0x40000082,
    HvSyntheticMsrSimp = 0x40000083,
    HvSyntheticMsrEom = 0x40000084,
    HvSyntheticMsrSirb = 0x40000085,
    HvSyntheticMsrSint0 = 0x40000090,
    HvSyntheticMsrSint1 = 0x40000091,
    HvSyntheticMsrSint2 = 0x40000092,
    HvSyntheticMsrSint3 = 0x40000093,
    HvSyntheticMsrSint4 = 0x40000094,
    HvSyntheticMsrSint5 = 0x40000095,
    HvSyntheticMsrSint6 = 0x40000096,
    HvSyntheticMsrSint7 = 0x40000097,
    HvSyntheticMsrSint8 = 0x40000098,
    HvSyntheticMsrSint9 = 0x40000099,
    HvSyntheticMsrSint10 = 0x4000009a,
    HvSyntheticMsrSint11 = 0x4000009b,
    HvSyntheticMsrSint12 = 0x4000009c,
    HvSyntheticMsrSint13 = 0x4000009d,
    HvSyntheticMsrSint14 = 0x4000009e,
    HvSyntheticMsrSint15 = 0x4000009f,
    HvSyntheticMsrSTimer0Config = 0x400000b0,
    HvSyntheticMsrSTimer0Count = 0x400000b1,
    HvSyntheticMsrSTimer1Config = 0x400000b2,
    HvSyntheticMsrSTimer1Count = 0x400000b3,
    HvSyntheticMsrSTimer2Config = 0x400000b4,
    HvSyntheticMsrSTimer2Count = 0x400000b5,
    HvSyntheticMsrSTimer3Config = 0x400000b6,
    HvSyntheticMsrSTimer3Count = 0x400000b7,
    HvSyntheticMsrPerfFeedbackTrigger = 0x400000c1,
    HvSyntheticMsrGuestSchedulerEvent = 0x400000c2,
    HvSyntheticMsrGuestIdle = 0x400000f0,
    HvSyntheticMsrSynthDebugControl = 0x400000f1,
    HvSyntheticMsrSynthDebugStatus = 0x400000f2,
    HvSyntheticMsrSynthDebugSendBuffer = 0x400000f3,
    HvSyntheticMsrSynthDebugReceiveBuffer = 0x400000f4,
    HvSyntheticMsrSynthDebugPendingBuffer = 0x400000f5,
    XbSyntheticMsrSynthDebugTransition = 0x400000f6,
    HvSyntheticMsrDebugDeviceOptions = 0x400000ff,
    HvSyntheticMsrCrashP0 = 0x40000100,
    HvSyntheticMsrCrashP1 = 0x40000101,
    HvSyntheticMsrCrashP2 = 0x40000102,
    HvSyntheticMsrCrashP3 = 0x40000103,
    HvSyntheticMsrCrashP4 = 0x40000104,
    HvSyntheticMsrCrashCtl = 0x40000105,
    HvSyntheticMsrReenlightenmentControl = 0x40000106,
    HvSyntheticMsrTscEmulationControl = 0x40000107,
    HvSyntheticMsrTscEmulationStatus = 0x40000108,
    HvSyntheticMsrSWatchdogConfig = 0x40000110,
    HvSyntheticMsrSWatchdogCount = 0x40000111,
    HvSyntheticMsrSWatchdogStatus = 0x40000112,
    HvSyntheticMsrSTimeUnhaltedTimerConfig = 0x40000114,
    HvSyntheticMsrSTimeUnhaltedTimerCount = 0x40000115,
    HvSyntheticMsrMemoryZeroingControl = 0x40000116,
    XbSyntheticMsrFsBase = 0x40000122,
    XbSyntheticMsrXOnly = 0x40000123,
    HvSyntheticMsrBelow1MbPage = 0x40000200,
    HvSyntheticMsrNestedVpIndex = 0x40001002,
    HvSyntheticMsrNestedSControl = 0x40001080,
    HvSyntheticMsrNestedSVersion = 0x40001081,
    HvSyntheticMsrNestedSiefp = 0x40001082,
    HvSyntheticMsrNestedSimp = 0x40001083,
    HvSyntheticMsrNestedEom = 0x40001084,
    HvSyntheticMsrNestedSirb = 0x40001085,
    HvSyntheticMsrNestedSint0 = 0x40001090,
    HvSyntheticMsrNestedSint1 = 0x40001091,
    HvSyntheticMsrNestedSint2 = 0x40001092,
    HvSyntheticMsrNestedSint3 = 0x40001093,
    HvSyntheticMsrNestedSint4 = 0x40001094,
    HvSyntheticMsrNestedSint5 = 0x40001095,
    HvSyntheticMsrNestedSint6 = 0x40001096,
    HvSyntheticMsrNestedSint7 = 0x40001097,
    HvSyntheticMsrNestedSint8 = 0x40001098,
    HvSyntheticMsrNestedSint9 = 0x40001099,
    HvSyntheticMsrNestedSint10 = 0x4000109a,
    HvSyntheticMsrNestedSint11 = 0x4000109b,
    HvSyntheticMsrNestedSint12 = 0x4000109c,
    HvSyntheticMsrNestedSint13 = 0x4000109d,
    HvSyntheticMsrNestedSint14 = 0x4000109e,
    HvSyntheticMsrNestedSint15 = 0x4000109f,
} HV_X64_SYNTHETIC_MSR, *PHV_X64_SYNTHETIC_MSR;

//
// Define index of synthetic interrupt source that receives intercept messages.
//
#define HV_SYNIC_INTERCEPTION_SINT_INDEX ((HV_SYNIC_SINT_INDEX)0)


//
// Define the virtual APIC registers
//
#define HV_X64_MSR_EOI                  (0x40000070)
#define HV_X64_MSR_ICR                  (0x40000071)
#define HV_X64_MSR_TPR                  (0x40000072)
#define HV_X64_MSR_APIC_ASSIST_PAGE     (0x40000073)

//
// Define bit that enables the APIC assist page.
//
#define HV_X64_APIC_ASSIST_PAGE_ENABLE  0x1

//
// Define version of the synthetic interrupt controller.
//

#define HV_SYNIC_VERSION        (1)


//
// Define synthetic interrupt controller model specific registers.
//

#define HV_X64_MSR_SCONTROL   (0x40000080)
#define HV_X64_MSR_SVERSION   (0x40000081)
#define HV_X64_MSR_SIEFP      (0x40000082)
#define HV_X64_MSR_SIMP       (0x40000083)
#define HV_X64_MSR_EOM        (0x40000084)
#define HV_X64_MSR_SINT0      (0x40000090)
#define HV_X64_MSR_SINT1      (0x40000091)
#define HV_X64_MSR_SINT2      (0x40000092)
#define HV_X64_MSR_SINT3      (0x40000093)
#define HV_X64_MSR_SINT4      (0x40000094)
#define HV_X64_MSR_SINT5      (0x40000095)
#define HV_X64_MSR_SINT6      (0x40000096)
#define HV_X64_MSR_SINT7      (0x40000097)
#define HV_X64_MSR_SINT8      (0x40000098)
#define HV_X64_MSR_SINT9      (0x40000099)
#define HV_X64_MSR_SINT10     (0x4000009A)
#define HV_X64_MSR_SINT11     (0x4000009B)
#define HV_X64_MSR_SINT12     (0x4000009C)
#define HV_X64_MSR_SINT13     (0x4000009D)
#define HV_X64_MSR_SINT14     (0x4000009E)
#define HV_X64_MSR_SINT15     (0x4000009F)

//
// Define the expected SynIC version.
//
#define HV_SYNIC_VERSION_1 (0x1)

//
// Define synthetic interrupt controller message constants.
//

#define HV_MESSAGE_SIZE                 (256)
#define HV_MESSAGE_PAYLOAD_BYTE_COUNT   (240)
#define HV_MESSAGE_PAYLOAD_QWORD_COUNT  (30)

//
// Define synthetic interrupt controller flag constants.
//

#define HV_EVENT_FLAGS_COUNT        (256 * 8)
#define HV_EVENT_FLAGS_BYTE_COUNT   (256)
#define HV_EVENT_FLAGS_DWORD_COUNT  (256 / sizeof(unsigned long))

//
// Define hypervisor message types.
//
typedef enum _HV_MESSAGE_TYPE
{
    HvMessageTypeNone = 0x00000000,

    //
    // Memory access messages.
    //
    HvMessageTypeUnmappedGpa = 0x80000000,
    HvMessageTypeGpaIntercept = 0x80000001,

    //
    // Timer notification messages.
    //
    HvMessageTimerExpired = 0x80000010,

    //
    // Error messages.
    //
    HvMessageTypeInvalidVpRegisterValue = 0x80000020,
    HvMessageTypeUnrecoverableException = 0x80000021,
    HvMessageTypeUnsupportedFeature = 0x80000022,
    HvMessageTypeTlbPageSizeMismatch = 0x80000023,
    HvMessageTypeIommuFault = 0x80000024,

    //
    // Trace buffer complete messages.
    //
    HvMessageTypeEventLogBufferComplete = 0x80000040,

    // 11.10.2 SynIC Message Types
    // Hypercall intercept
    HvMessageTypeHypercallIntercept = 0x80000050,

    HvMessageTypeSynicEventIntercept = 0x80000060,

    HvMessageTypeSchedulerIdRangeStart = 0x80000100,
    HvMessageTypeSchedulerVpSignalBitset = 0x80000100,
    HvMessageTypeSchedulerVpSignalPair = 0x80000101,
    HvMessageTypeSchedulerIdRangeEnd = 0x800001FF,

    //
    // Platform-specific processor intercept messages.
    //
    HvMessageTypeX64IoPortIntercept = 0x80010000,
    HvMessageTypeMsrIntercept = 0x80010001,
    HvMessageTypeX64CpuidIntercept = 0x80010002,
    HvMessageTypeExceptionIntercept = 0x80010003,
    HvMessageTypeX64ApicEoi = 0x80010004,
    HvMessageTypeX64LegacyFpError = 0x80010005,
    HvMessageTypeX64IommuPrq = 0x80010006,
    HvMessageTypeX64Halt = 0x80010007,
    HvMessageTypeX64InterruptionDeliverable = 0x80010008,
    HvMessageTypeX64SipiIntercept = 0x80010009,

    // 11.10.2 SynIC Message Types
    HvMessageTypeRegisterIntercept = 0x80010006,

} HV_MESSAGE_TYPE, *PHV_MESSAGE_TYPE;


#define HV_MESSAGE_TYPE_HYPERVISOR_MASK (0x80000000)


//
// Define APIC EOI message.
//
typedef struct _HV_X64_APIC_EOI_MESSAGE
{
    unsigned long VpIndex;
    unsigned long InterruptVector;
} HV_X64_APIC_EOI_MESSAGE, *PHV_X64_APIC_EOI_MESSAGE;


//
// Define the number of synthetic interrupt sources.
//

#define HV_SYNIC_SINT_COUNT (16)
#define HV_SYNIC_STIMER_COUNT (4)

//
// Define the synthetic interrupt source index type.
//

typedef unsigned long HV_SYNIC_SINT_INDEX, *PHV_SYNIC_SINT_INDEX;

//
// Define partition identifier type.
//

typedef unsigned long long HV_PARTITION_ID, *PHV_PARTITION_ID;

//
// Define invalid partition identifier.
//
#define HV_PARTITION_ID_INVALID ((HV_PARTITION_ID) 0x0)

// 4.2.1
#define HV_PARTITION_ID_SELF ((HV_PARTITION_ID) -1)

//
// Define connection identifier type.
//

typedef union _HV_CONNECTION_ID
{
    unsigned long AsUINT32;

    struct
    {
        unsigned long Id:24;
        unsigned long Reserved:8;
    };

} HV_CONNECTION_ID, *PHV_CONNECTION_ID;

//
// Define port identifier type.
//

typedef union _HV_PORT_ID
{
    unsigned long AsUINT32;

    struct
    {
        unsigned long Id:24;
        unsigned long Reserved:8;
    };

} HV_PORT_ID, *PHV_PORT_ID;

//
// Define port type.
//

typedef enum _HV_PORT_TYPE
{
    HvPortTypeMessage   = 1,
    HvPortTypeEvent     = 2,
    HvPortTypeMonitor   = 3
} HV_PORT_TYPE, *PHV_PORT_TYPE;

//
// Define port information structure.
//

typedef struct _HV_PORT_INFO
{
    HV_PORT_TYPE PortType;
    unsigned long Padding;

    union
    {
        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            unsigned long long RsvdZ;
        } MessagePortInfo;

        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            unsigned short BaseFlagNumber;
            unsigned short FlagCount;
            unsigned long RsvdZ;
        } EventPortInfo;

        struct
        {
            HV_GPA MonitorAddress;
            unsigned long long RsvdZ;
        } MonitorPortInfo;
    };
} HV_PORT_INFO, *PHV_PORT_INFO;

typedef const HV_PORT_INFO *PCHV_PORT_INFO;

typedef struct _HV_CONNECTION_INFO
{
    HV_PORT_TYPE PortType;
    unsigned long Padding;

    union
    {
        struct
        {
            unsigned long long RsvdZ;
        } MessageConnectionInfo;

        struct
        {
            unsigned long long RsvdZ;
        } EventConnectionInfo;

        struct
        {
            HV_GPA MonitorAddress;
        } MonitorConnectionInfo;
    };
} HV_CONNECTION_INFO, *PHV_CONNECTION_INFO;

typedef const HV_CONNECTION_INFO *PCHV_CONNECTION_INFO;

//
// Define type of port property.
//

typedef unsigned long long HV_PORT_PROPERTY, *PHV_PORT_PROPERTY;

//
// Define enumeration of port property codes.
//

typedef enum _HV_PORT_PROPERTY_CODE
{
    HvPortPropertyPostCount = 0x00000000,
    HvPortPropertyPreferredTargetVp = 0x00000001,
} HV_PORT_PROPERTY_CODE, *PHV_PORT_PROPERTY_CODE;


//
// Define synthetic interrupt controller message flags.
//

typedef union _HV_MESSAGE_FLAGS
{
    unsigned char AsUINT8;
    struct
    {
        unsigned char MessagePending:1;
        unsigned char Reserved:7;
    };
} HV_MESSAGE_FLAGS, *PHV_MESSAGE_FLAGS;


//
// Define synthetic interrupt controller message header.
//

typedef struct _HV_MESSAGE_HEADER
{
    HV_MESSAGE_TYPE     MessageType;
    unsigned char               PayloadSize;
    HV_MESSAGE_FLAGS    MessageFlags;
    unsigned char               Reserved[2];
    union
    {
        HV_PARTITION_ID Sender;
        HV_PORT_ID      Port;
    };

} HV_MESSAGE_HEADER, *PHV_MESSAGE_HEADER;

//
// Define timer message payload structure.
//
typedef struct _HV_TIMER_MESSAGE_PAYLOAD
{
    unsigned long          TimerIndex;
    unsigned long          Reserved;
    HV_NANO100_TIME ExpirationTime;     // When the timer expired
    HV_NANO100_TIME DeliveryTime;       // When the message was delivered
} HV_TIMER_MESSAGE_PAYLOAD, *PHV_TIMER_MESSAGE_PAYLOAD;

typedef enum _HV_IOMMU_FAULT_TYPE
{
    HvIommuTranslationFault = 0,
    HvIommuTranslationBlocked = 1,
    HvIommuInterruptFault = 2,
} HV_IOMMU_FAULT_TYPE, * PHV_IOMMU_FAULT_TYPE;

//
// Define IOMMU fault message payload structure.
//

typedef struct _HV_IOMMU_FAULT_MESSAGE_PAYLOAD
{
    HV_IOMMU_FAULT_TYPE Type;
    unsigned char AccessType;
    struct
    {
        unsigned long FaultAddressValid : 1;
        unsigned long DeviceIdValid : 1;
    } Flags;
    unsigned long long LogicalDeviceId;
    unsigned long long FaultAddress;
} HV_IOMMU_FAULT_MESSAGE_PAYLOAD, *PHV_IOMMU_FAULT_MESSAGE_PAYLOAD;

//
// Define IOMMU PRQ message payload structure.
//

typedef struct _HV_IOMMU_PRQ_MESSAGE_PAYLOAD
{
    unsigned long IommuId;
} HV_IOMMU_PRQ_MESSAGE_PAYLOAD, *PHV_IOMMU_PRQ_MESSAGE_PAYLOAD;

//
// Define synthetic interrupt controller message format.
//

typedef struct _HV_MESSAGE
{
    HV_MESSAGE_HEADER Header;
    union
    {
        unsigned long long Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
        HV_TIMER_MESSAGE_PAYLOAD TimerPayload;
        HV_EVENTLOG_MESSAGE_PAYLOAD TracePayload;
        HV_IOMMU_PRQ_MESSAGE_PAYLOAD IommuPrqPayload;
        HV_IOMMU_FAULT_MESSAGE_PAYLOAD IommuFaultPayload;
    };
} HV_MESSAGE, *PHV_MESSAGE;

//
// Define the number of message buffers associated with each port.
//

#define HV_PORT_MESSAGE_BUFFER_COUNT (16)

//
// Define the synthetic interrupt message page layout.
//

typedef struct _HV_MESSAGE_PAGE
{
    volatile HV_MESSAGE SintMessage[HV_SYNIC_SINT_COUNT];
} HV_MESSAGE_PAGE, *PHV_MESSAGE_PAGE;


//
// Define the synthetic interrupt controller event flags format.
//

typedef union _HV_SYNIC_EVENT_FLAGS
{
    unsigned char Flags8[HV_EVENT_FLAGS_BYTE_COUNT];
    unsigned long Flags32[HV_EVENT_FLAGS_DWORD_COUNT];
} HV_SYNIC_EVENT_FLAGS, *PHV_SYNIC_EVENT_FLAGS;


//
// Define the synthetic interrupt flags page layout.
//

typedef struct _HV_SYNIC_EVENT_FLAGS_PAGE
{
    volatile HV_SYNIC_EVENT_FLAGS SintEventFlags[HV_SYNIC_SINT_COUNT];
} HV_SYNIC_EVENT_FLAGS_PAGE, *PHV_SYNIC_EVENT_FLAGS_PAGE;


//
// Define SynIC control register.
//
typedef union _HV_SYNIC_SCONTROL
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Enable:1;
        unsigned long long Reserved:63;
    };
} HV_SYNIC_SCONTROL, *PHV_SYNIC_SCONTROL;

//
// Define synthetic interrupt source.
//

typedef union _HV_SYNIC_SINT
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Vector    :8;
        unsigned long long Reserved1 :8;
        unsigned long long Masked    :1;
        unsigned long long AutoEoi   :1;
        unsigned long long Reserved2 :46;
    };
} HV_SYNIC_SINT, *PHV_SYNIC_SINT;

//
// Define the format of the SIMP register
//

typedef union _HV_SYNIC_SIMP
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long SimpEnabled : 1;
        unsigned long long Preserved   : 11;
        unsigned long long BaseSimpGpa : 52;
    };
} HV_SYNIC_SIMP, *PHV_SYNIC_SIMP;

//
// Define the format of the SIEFP register
//

typedef union _HV_SYNIC_SIEFP
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long SiefpEnabled : 1;
        unsigned long long Preserved   : 11;
        unsigned long long BaseSiefpGpa : 52;
    };
} HV_SYNIC_SIEFP, *PHV_SYNIC_SIEFP;

//
// Define the format of the APIC_ASSIST register
//
typedef union _HV_X64_MSR_APIC_ASSIST_CONTENTS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Enable                   : 1;
        unsigned long long ReservedP                : 11;
        unsigned long long GpaPageNumber            : 52;
    };
} HV_X64_MSR_APIC_ASSIST_CONTENTS, *PHV_X64_MSR_APIC_ASSIST_CONTENTS;

//
// Format of the APIC assist page.
//
#define HV_VIRTUAL_APIC_NO_EOI_REQUIRED 0x0

typedef union _HV_VIRTUAL_APIC_ASSIST
{
    unsigned long ApicFlags;
    struct
    {
        unsigned long NoEOIRequired : 1;
    };
} HV_VIRTUAL_APIC_ASSIST, *PHV_VIRTUAL_APIC_ASSIST;

//
// Define virtual interrupt control structure.
//
typedef union _HV_INTERRUPT_CONTROL
{
    unsigned long long AsUINT64;
    struct
    {
        HV_INTERRUPT_TYPE InterruptType;
        unsigned long LevelTriggered:1;
        unsigned long LogicalDestinationMode:1;
        unsigned long Reserved:30;
    };
} HV_INTERRUPT_CONTROL, *PHV_INTERRUPT_CONTROL;


//
// Emulated timer period
//
typedef union _HV_EMULATED_TIMER_PERIOD
{
    unsigned long long              AsUINT64;
    HV_NANO100_DURATION Period;

} HV_EMULATED_TIMER_PERIOD, *PHV_EMULATED_TIMER_PERIOD;

//
// Periodic Timer route
//
typedef union _HV_EMULATED_TIMER_CONTROL
{
    unsigned long long  AsUINT64;

    struct
    {
        unsigned long  Vector                  :  8;
        unsigned long  DeliveryMode            :  3;
        unsigned long  LogicalDestinationMode  :  1;
        unsigned long  Enabled                 :  1;
        unsigned long  Reserved1               : 19;
        unsigned long  Reserved2               : 24;
        unsigned long  Mda                     :  8;
    };

} HV_EMULATED_TIMER_CONTROL, *PHV_EMULATED_TIMER_CONTROL;

//
// ACPI PM timer
//
typedef union _HV_PM_TIMER_INFO
{
    unsigned long long  AsUINT64;

    struct
    {
        unsigned long  Port                : 16;
        unsigned long  Width24             :  1;
        unsigned long  Enabled             :  1;
        unsigned long  Reserved1           : 14;
        unsigned long  Reserved2           : 32;
    };

} HV_PM_TIMER_INFO, *PHV_PM_TIMER_INFO;

//
// Definitions for the monitored notification facility
//

typedef union _HV_MONITOR_TRIGGER_GROUP
{
    unsigned long long AsUINT64;

    struct
    {
        unsigned long Pending;
        unsigned long Armed;
    };
    
} HV_MONITOR_TRIGGER_GROUP, *PHV_MONITOR_TRIGGER_GROUP;

typedef struct _HV_MONITOR_PARAMETER
{
    HV_CONNECTION_ID    ConnectionId;
    unsigned short              FlagNumber;
    unsigned short              RsvdZ;
} HV_MONITOR_PARAMETER, *PHV_MONITOR_PARAMETER;

typedef union _HV_MONITOR_TRIGGER_STATE
{
    unsigned long AsUINT32;
        
    struct
    {
        unsigned long GroupEnable : 4;
        unsigned long RsvdZ       : 28;
    };

} HV_MONITOR_TRIGGER_STATE, *PHV_MONITOR_TRIGGER_STATE;

//
// HV_MONITOR_PAGE Layout
// ------------------------------------------------------
// | 0   | TriggerState (4 bytes) | Rsvd1 (4 bytes)     |
// | 8   | TriggerGroup[0]                              |
// | 10  | TriggerGroup[1]                              |
// | 18  | TriggerGroup[2]                              |
// | 20  | TriggerGroup[3]                              |
// | 28  | Rsvd2[0]                                     |
// | 30  | Rsvd2[1]                                     |
// | 38  | Rsvd2[2]                                     |
// | 40  | NextCheckTime[0][0]    | NextCheckTime[0][1] |
// | ...                                                |
// | 240 | Latency[0][0..3]                             |
// | 340 | Rsvz3[0]                                     |
// | 440 | Parameter[0][0]                              |
// | 448 | Parameter[0][1]                              |
// | ...                                                |
// | 840 | Rsvd4[0]                                     |
// ------------------------------------------------------

typedef struct _HV_MONITOR_PAGE
{
    HV_MONITOR_TRIGGER_STATE TriggerState;
    unsigned long                   RsvdZ1;

    HV_MONITOR_TRIGGER_GROUP TriggerGroup[4];
    unsigned long long                   RsvdZ2[3]; // 64

    unsigned short                   NextCheckTime[4][32]; // 256
    unsigned long long                   RsvdZ3[32]; // 256

    unsigned short                   Latency[4][32]; // 256
    unsigned long long                   RsvdZ4[32]; // 256

    HV_MONITOR_PARAMETER     Parameter[4][32]; // 1024

    unsigned char                    RsvdZ5[1984];

} HV_MONITOR_PAGE, *PHV_MONITOR_PAGE;

typedef volatile HV_MONITOR_PAGE* PVHV_MONITOR_PAGE;


//
// Debug channel identifier
//
typedef unsigned short HV_DEBUG_CHANNEL_IDENTIFIER;

//
// Maximum size of the payload
//
#define HV_DEBUG_MAXIMUM_DATA_SIZE 4088

//
// Debug options for all calls
//
typedef unsigned long HV_DEBUG_OPTIONS;

//
// Options flags for HvPostDebugData
//
#define HV_DEBUG_POST_LOOP                  0x00000001

//
// Options flags for HvRetrieveDebugData
//
#define HV_DEBUG_RETRIEVE_LOOP              0x00000001
#define HV_DEBUG_RETRIEVE_TEST_ACTIVITY     0x00000002

//
// Options flags for HvResetDebugSession
//
#define HV_DEBUG_PURGE_INCOMING_DATA        0x00000001
#define HV_DEBUG_PURGE_OUTGOING_DATA        0x00000002

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_POST_DEBUG_DATA
{
    unsigned long Count;
    HV_DEBUG_OPTIONS Options;
    unsigned char Data[HV_DEBUG_MAXIMUM_DATA_SIZE];
} HV_INPUT_POST_DEBUG_DATA, *PHV_INPUT_POST_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_POST_DEBUG_DATA
{
    unsigned long PendingCount;
} HV_OUTPUT_POST_DEBUG_DATA, *PHV_OUTPUT_POST_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RETRIEVE_DEBUG_DATA
{
    unsigned long Count;
    HV_DEBUG_OPTIONS Options;
    HV_NANO100_DURATION Timeout;
} HV_INPUT_RETRIEVE_DEBUG_DATA, *PHV_INPUT_RETRIEVE_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RETRIEVE_DEBUG_DATA
{
    unsigned long RetrievedCount;
    unsigned long RemainingCount;
    unsigned char Data[HV_DEBUG_MAXIMUM_DATA_SIZE];
} HV_OUTPUT_RETRIEVE_DEBUG_DATA, *PHV_OUTPUT_RETRIEVE_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESET_DEBUG_SESSION
{
    HV_DEBUG_OPTIONS Options;
} HV_INPUT_RESET_DEBUG_SESSION, *PHV_INPUT_RESET_DEBUG_SESSION;

#define HV_DEBUG_INVOKE_REASON_CLOCK_WATCHDOG   0x01
#define HV_DEBUG_INVOKE_REASON_DPC_WATCHDOG     0x02
#define HV_DEBUG_INVOKE_REASON_DPC_TIMEOUT      0x03

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INVOKE_HYPERVISOR_DEBUGGER
{
    unsigned long long Reason;
    unsigned long long SupplementalCode;
} HV_INPUT_INVOKE_HYPERVISOR_DEBUGGER, *PHV_INPUT_INVOKE_HYPERVISOR_DEBUGGER;

//
// Mux Protocol Defines
//
#define HV_MUX_PACKET_LEADER            0x11223344

#define HV_MUX_PACKET_TYPE_DATA             0x0001
#define HV_MUX_PACKET_TYPE_BREAKIN          0x0002
#define HV_MUX_PACKET_TYPE_QUERY_CHANNELS   0x0003

#define HV_MUX_PACKET_TYPE_MAXIMUM          HV_MUX_PACKET_TYPE_QUERY_CHANNELS

#define HV_MUX_PACKET_DUMMY_BYTE        0xEE

#pragma pack(1)
typedef struct _HV_MUX_PACKET_HEADER
{
    unsigned long Leader;
    unsigned short Type;
    unsigned short Length;
    unsigned long CRC;
    HV_DEBUG_CHANNEL_IDENTIFIER Channel;
    unsigned short Reserved;

} HV_MUX_PACKET_HEADER, *PHV_MUX_PACKET_HEADER;

//
// Channel data returned in a HV_MUX_PACKET_TYPE_QUERY_CHANNELS
// respone. The channelIds arrays is variable length array
// 

typedef struct {
    
    unsigned long Count;
    HV_DEBUG_CHANNEL_IDENTIFIER ChannelIds[1];

} MUX_CHANNEL_DATA, *PMUX_CHANNEL_DATA;

#pragma pack()

//
// Debug Channel Id
//
#define HV_DEBUG_CHANNEL_ID_HYPERVISOR      0x00000000
#define HV_DEBUG_CHANNEL_ID_ROOT            0x00000001
#define HV_DEBUG_CHANNEL_ID_DEFAULT         0x0000BADA
#define HV_DEBUG_CHANNEL_ID_ASSIGN_START    0x00000002
#define HV_DEBUG_CHANNEL_ID_FW_MAX          0x0000003E

//
// This structure is used to transfer crashdump information between the
// Hypervisor and the HvBoot.sys driver in the root Windows instance at the
// time of a Hypervisor BugCheck.  It is allocated by HvBoot.sys during the
// Hypervisor launch process, and its SPA is handed in to the Hypervisor via
// the loader block.
//

#define HV_CRASHDUMP_AREA_VERSION   2
#define HV_IMAGE_NAME_MAX_LENGTH    32
#define HV_DEFAULT_CRASHDUMP_SPA_PAGES 5

typedef struct _HV_CRASHDUMP_AREA_V1
{
    //
    // Version of the Crashdump Area structure
    //

    unsigned long Version;

    //
    // Flags indicating content validity and other attributes of the
    // Crashdump Area
    //

    union
    {
        unsigned long FlagsAsUINT32;
        struct
        {
            //
            // Indicates the contents of the Crashdump Area are valid
            //

            unsigned long  Valid:1;
            unsigned long  Reserved:31;

        };

    };

    //
    // Loaded Module Information
    //

    unsigned long long HypervisorBase;
    unsigned long SizeOfImage;
    unsigned short ImageNameLength;
    unsigned short ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    //
    // Bugcheck error code fields
    //

    unsigned long long BugCheckData[5];
    void  *BugCheckErrorReturnAddress;

    //
    // The root of the page table needed to lookup virtual addresses
    // and the debugger data block. The debugger data block contains
    // all the information necc. for the debugger to interpret the 
    // dump file. Of particular interest within it is the prcb address 
    // that contain the processor state.
    //

    unsigned long long PageTableBase;
    unsigned long long PfnDataBase;
    unsigned long long DebuggerDataBlock;
    unsigned long NumberProcessors;

    //
    // Context of the crashing thread
    //

    unsigned long ProcessorStateOffset;
    unsigned long ProcessorStateSize;

    //
    // The stack of crashing thread.
    // 

    unsigned long CrashStackSize;
    unsigned long CrashStackOffset;
    unsigned long long CrashStackAddress;

} HV_CRASHDUMP_AREA_V1, *PHV_CRASHDUMP_AREA_V1;


typedef struct _HV_CRASHDUMP_PROCESSOR_STATE
{
    //
    // Context of the crashing thread.
    //

    unsigned long RegisterStateOffset;
    unsigned long RegisterStateSize;

    //
    // The stack of the crashing thread.
    // 

    unsigned long CrashStackSize;
    unsigned long CrashStackOffset;
    unsigned long long CrashStackAddress;

    //
    // Platform specific data.
    //

    unsigned long PlatformStateSize;
    unsigned long PlatformStateOffset;

} HV_CRASHDUMP_PROCESSOR_STATE, *PHV_CRASHDUMP_PROCESSOR_STATE;

//
//  Size of code page to save during a crash.
// 

#define CODE_CHUNK_SIZE     0x200

typedef struct _HV_CRASHDUMP_AREA
{
    //
    // Version of the Crashdump Area structure
    //

    unsigned long Version;

    //
    // Flags indicating content validity and other attributes of the
    // Crashdump Area
    //

    union
    {
        unsigned long FlagsAsUINT32;
        struct
        {
            //
            // Indicates the contents of the Crashdump Area are valid
            //

            unsigned long  Valid:1;
            unsigned long  Reserved:31;

        };

    };

    //
    // Loaded Module Information.
    //

    unsigned long long HypervisorBase;
    unsigned long SizeOfImage;
    unsigned long CheckSum;

    //
    // Partition State.
    // 

    unsigned long long CurrentPartition;
    unsigned long long PartitionsCreated;
    unsigned long PartitionsRunning;
    unsigned long long CompartmentFreePfns;

    unsigned short ImageNameLength;
    unsigned short ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    //
    // Bugcheck error code fields.
    //

    unsigned long long BugCheckData[5];
    unsigned long long BugCheckErrorReturnAddress;

    //
    // The root of the page table needed to lookup virtual addresses
    // and the debugger data block. The debugger data block contains
    // all the information necc. for the debugger to interpret the 
    // dump file. Of particular interest within it is the prcb address 
    // that contain the processor state.
    //

    unsigned long long PageTableBase;
    unsigned long long PfnDataBase;
    unsigned long long DebuggerDataBlock;
    unsigned long NumberProcessors;
    unsigned long CurrentProcessor;
    
    //
    // Code page data. If we know the source of the fault this
    // will have the in memory copy of the code and its spa.
    //

    unsigned long long CodeSpa;
    unsigned char CodeChunk[CODE_CHUNK_SIZE];

    //
    // Processor contexts. This is the offset to a set of
    // HV_CRASHDUMP_PROCESSOR_STATE structs. The crashing processor
    // should always be included.
    // 

    unsigned long ContextCount;
    unsigned long ContextOffset;
    unsigned long ContextSize;

} HV_CRASHDUMP_AREA, *PHV_CRASHDUMP_AREA;

//
// Define virtual processor execution state bitfield.
//
typedef union _HV_X64_VP_EXECUTION_STATE
{
    unsigned short AsUINT16;
    struct
    {
        unsigned short Cpl:2;
        unsigned short Cr0Pe:1;
        unsigned short Cr0Am:1;
        unsigned short EferLma:1;
        unsigned short DebugActive:1;
        unsigned short InterruptionPending:1;
        unsigned short Reserved:9;
    };
} HV_X64_VP_EXECUTION_STATE, *PHV_X64_VP_EXECUTION_STATE;


//
// Define intercept message header structure.
//
typedef struct _HV_X64_INTERCEPT_MESSAGE_HEADER
{
    HV_VP_INDEX VpIndex;
    unsigned char InstructionLength;
    HV_INTERCEPT_ACCESS_TYPE InterceptAccessType;
    HV_X64_VP_EXECUTION_STATE ExecutionState;
    HV_X64_SEGMENT_REGISTER CsSegment;
    unsigned long long Rip;
    unsigned long long Rflags;
} HV_X64_INTERCEPT_MESSAGE_HEADER, *PHV_X64_INTERCEPT_MESSAGE_HEADER;


//
// Define memory access information structure.
//
typedef union _HV_X64_MEMORY_ACCESS_INFO
{
    unsigned char AsUINT8;
    struct
    {
        unsigned char GvaValid:1;
        unsigned char Reserved:7;
    };
} HV_X64_MEMORY_ACCESS_INFO, *PHV_X64_MEMORY_ACCESS_INFO;


//
// Define IO port access information structure.
//
typedef union _HV_X64_IO_PORT_ACCESS_INFO
{
    unsigned char AsUINT8;
    struct
    {
        unsigned char AccessSize:3;
        unsigned char StringOp:1;
        unsigned char RepPrefix:1;
        unsigned char Reserved:3;
    };
} HV_X64_IO_PORT_ACCESS_INFO, *PHV_X64_IO_PORT_ACCESS_INFO;


//
// Define exception information structure.
//
typedef union _HV_X64_EXCEPTION_INFO
{
    unsigned char AsUINT8;
    struct
    {
        unsigned char ErrorCodeValid:1;
        unsigned char Reserved:7;
    };
} HV_X64_EXCEPTION_INFO, *PHV_X64_EXCEPTION_INFO;


//
// Define memory access message structure. This message structure is used
// for memory intercepts, GPA not present intercepts and SPA access violation
// intercepts.
//
typedef struct _HV_X64_MEMORY_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_CACHE_TYPE CacheType;
    unsigned char InstructionByteCount;
    HV_X64_MEMORY_ACCESS_INFO MemoryAccessInfo;
    unsigned short Reserved1;
    unsigned long long GuestVirtualAddress;
    unsigned long long GuestPhysicalAddress;
    unsigned char InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    unsigned long long Rax;
    unsigned long long Rcx;
    unsigned long long Rdx;
    unsigned long long Rbx;
    unsigned long long Rsp;
    unsigned long long Rbp;
    unsigned long long Rsi;
    unsigned long long Rdi;
    unsigned long long R8;
    unsigned long long R9;
    unsigned long long R10;
    unsigned long long R11;
    unsigned long long R12;
    unsigned long long R13;
    unsigned long long R14;
    unsigned long long R15;
} HV_X64_MEMORY_INTERCEPT_MESSAGE, *PHV_X64_MEMORY_INTERCEPT_MESSAGE;


//
// Define CPUID intercept message structure.
//
typedef struct _HV_X64_CPUID_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    unsigned long long Rax;
    unsigned long long Rcx;
    unsigned long long Rdx;
    unsigned long long Rbx;
    unsigned long long DefaultResultRax;
    unsigned long long DefaultResultRcx;
    unsigned long long DefaultResultRdx;
    unsigned long long DefaultResultRbx;
} HV_X64_CPUID_INTERCEPT_MESSAGE, *PHV_X64_CPUID_INTERCEPT_MESSAGE;


//
// Define MSR intercept message structure.
//
typedef struct _HV_X64_MSR_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    unsigned long MsrNumber;
    unsigned long Reserved;
    unsigned long long Rdx;
    unsigned long long Rax;
} HV_X64_MSR_INTERCEPT_MESSAGE, *PHV_X64_MSR_INTERCEPT_MESSAGE;


//
// Define IO access intercept message structure.
//
typedef struct _HV_X64_IO_PORT_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    unsigned short PortNumber;
    HV_X64_IO_PORT_ACCESS_INFO AccessInfo;
    unsigned char InstructionByteCount;
    unsigned long Reserved;
    unsigned long long Rax;
    unsigned char InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER EsSegment;
    unsigned long long Rcx;
    unsigned long long Rsi;
    unsigned long long Rdi;
} HV_X64_IO_PORT_INTERCEPT_MESSAGE, *PHV_X64_IO_PORT_INTERCEPT_MESSAGE;


//
// Define exception intercept message.
//
typedef struct _HV_X64_EXCEPTION_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    unsigned short ExceptionVector;
    HV_X64_EXCEPTION_INFO ExceptionInfo;
    unsigned char InstructionByteCount;
    unsigned long ErrorCode;
    unsigned long long ExceptionParameter;
    unsigned long long Reserved;
    unsigned char InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    unsigned long long Rax;
    unsigned long long Rcx;
    unsigned long long Rdx;
    unsigned long long Rbx;
    unsigned long long Rsp;
    unsigned long long Rbp;
    unsigned long long Rsi;
    unsigned long long Rdi;
    unsigned long long R8;
    unsigned long long R9;
    unsigned long long R10;
    unsigned long long R11;
    unsigned long long R12;
    unsigned long long R13;
    unsigned long long R14;
    unsigned long long R15;
} HV_X64_EXCEPTION_INTERCEPT_MESSAGE, *PHV_X64_EXCEPTION_INTERCEPT_MESSAGE;


//
// Define legacy floating point error message.
//
typedef struct _HV_X64_LEGACY_FP_ERROR_MESSAGE
{
    unsigned long VpIndex;
    unsigned long Reserved;
} HV_X64_LEGACY_FP_ERROR_MESSAGE, *PHV_X64_LEGACY_FP_ERROR_MESSAGE;


//
// Define invalid virtual processor register message.
//
typedef struct _HV_X64_INVALID_VP_REGISTER_MESSAGE
{
    unsigned long VpIndex;
    unsigned long Reserved;
} HV_X64_INVALID_VP_REGISTER_MESSAGE, *PHV_X64_INVALID_VP_REGISTER_MESSAGE;


//
// Define virtual processor unrecoverable error message.
//
typedef struct _HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
} HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE, *PHV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE;


//
// Define the unsupported feature codes.
//
typedef enum _HV_X64_UNSUPPORTED_FEATURE_CODE
{
    HvUnsupportedFeatureIntercept = 1,
    HvUnsupportedFeatureTaskSwitchTss = 2
}HV_X64_UNSUPPORTED_FEATURE_CODE, *PHV_X64_UNSUPPORTED_FEATURE_CODE;


//
// Define unsupported feature message.
//
typedef struct _HV_X64_UNSUPPORTED_FEATURE_MESSAGE
{
    unsigned long VpIndex;
    HV_X64_UNSUPPORTED_FEATURE_CODE FeatureCode;
    unsigned long long FeatureParameter;
} HV_X64_UNSUPPORTED_FEATURE_MESSAGE, *PHV_X64_UNSUPPORTED_FEATURE_MESSAGE;

//
// Versioning definitions used for guests reporting themselves to the
// hypervisor, and visa versa.
// ==================================================================
//

//
// Version info reported by guest OS's
//
typedef enum _HV_GUEST_OS_VENDOR
{
    HvGuestOsVendorMicrosoft        = 0x0001

} HV_GUEST_OS_VENDOR, *PHV_GUEST_OS_VENDOR;

typedef enum _HV_GUEST_OS_MICROSOFT_IDS
{
    HvGuestOsMicrosoftUndefined     = 0x00,
    HvGuestOsMicrosoftMSDOS         = 0x01,
    HvGuestOsMicrosoftWindows3x     = 0x02,
    HvGuestOsMicrosoftWindows9x     = 0x03,
    HvGuestOsMicrosoftWindowsNT     = 0x04,
    HvGuestOsMicrosoftWindowsCE     = 0x05

} HV_GUEST_OS_MICROSOFT_IDS, *PHV_GUEST_OS_MICROSOFT_IDS;

typedef enum _HV_GUEST_OS_OPENSOURCE_IDS
{
    HvGuestOsOpenSourceLinux        = 0x0001

} HV_GUEST_OS_OPENSOURCE_IDS, *PHV_GUEST_OS_OPENSOURCE_IDS;

//
// Declare the MSR used to identify the guest OS.
//
#define HV_X64_MSR_GUEST_OS_ID 0x40000000

typedef union _HV_X64_MSR_GUEST_OS_ID_CONTENTS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long BuildNumber    : 16;
        unsigned long long ServiceVersion : 8; // Service Pack, etc.
        unsigned long long MinorVersion   : 8;
        unsigned long long MajorVersion   : 8;
        unsigned long long OsId           : 8; // HV_GUEST_OS_MICROSOFT_IDS (If Vendor=MS)
        unsigned long long VendorId       : 16; // HV_GUEST_OS_VENDOR
    };
} HV_X64_MSR_GUEST_OS_ID_CONTENTS, *PHV_X64_MSR_GUEST_OS_ID_CONTENTS;

//
// Declare the MSR used to setup pages used to communicate with the hypervisor.
//
#define HV_X64_MSR_HYPERCALL 0x40000001

typedef union _HV_X64_MSR_HYPERCALL_CONTENTS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Enable               : 1;
        unsigned long long Locked               : 1;
        unsigned long long ReservedP            : 10;
        unsigned long long GpaPageNumber        : 52;
    };
} HV_X64_MSR_HYPERCALL_CONTENTS, *PHV_X64_MSR_HYPERCALL_CONTENTS;

//
// Declare the MSR used to reset partition
//
#define HV_X64_MSR_RESET 0x40000003

typedef union _HV_X64_MSR_RESET_CONTENTS
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Reset        :1;
        unsigned long long ReservedZ    :63;
    };
} HV_X64_MSR_RESET_CONTENTS, *PHV_X64_MSR_RESET_CONTENTS;

//
// Hypercall structures, enumerations, and constants.
// ==================================================
//

//
// Partition Properties
//
typedef unsigned long long HV_PARTITION_PROPERTY, *PHV_PARTITION_PROPERTY;

typedef enum
{
    //
    // Privilege properties
    //
    HvPartitionPropertyPrivilegeFlags              = 0x00010000,

    //
    // Scheduling properties
    //
    HvPartitionPropertyCpuReserve                  = 0x00020001,
    HvPartitionPropertyCpuCap                      = 0x00020002,
    HvPartitionPropertyCpuWeight                   = 0x00020003,

    //
    // Timer assist properties
    //
    HvPartitionPropertyEmulatedTimerPeriod         = 0x00030000,
    HvPartitionPropertyEmulatedTimerControl        = 0x00030001,
    HvPartitionPropertyPmTimerAssist               = 0x00030002,

    //
    // Debugging properties
    //
    HvPartitionPropertyDebugChannelId              = 0x00040000,

    //
    // Resource properties
    //
    HvPartitionPropertyVirtualTlbPageCount         = 0x00050000,

    // Compatibility properties
    HvPartitionPropertyProcessorVendor             = 0x00060000,
    HvPartitionPropertyProcessorFeatures           = 0x00060001,
    HvPartitionPropertyProcessorXsaveFeatures      = 0x00060002,
    HvPartitionPropertyProcessorCLFlushSize        = 0x00060003,
} HV_PARTITION_PROPERTY_CODE, *PHV_PARTITION_PROPERTY_CODE;

//
// Partition scheduling property ranges
//
#define HvPartitionPropertyMinimumCpuReserve    (0 << 16)
#define HvPartitionPropertyMaximumCpuReserve    (1 << 16)
#define HvPartitionPropertyMinimumCpuCap        (0 << 16)
#define HvPartitionPropertyMaximumCpuCap        (1 << 16)
#define HvPartitionPropertyMinimumCpuWeight     1
#define HvPartitionPropertyMaximumCpuWeight     10000

//
// Declare the input and output structures for the HvCreatePartition hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PARTITION
{
    unsigned long long Flags;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INPUT_CREATE_PARTITION, *PHV_INPUT_CREATE_PARTITION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_CREATE_PARTITION
{
    HV_PARTITION_ID NewPartitionId;
} HV_OUTPUT_CREATE_PARTITION, *PHV_OUTPUT_CREATE_PARTITION;

//
// Declare the input structure for the HvDeletePartition hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_DELETE_PARTITION, *PHV_INPUT_DELETE_PARTITION;

//
// Declare the input structure for the HvFinalizePartition hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FINALIZE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_FINALIZE_PARTITION, *PHV_INPUT_FINALIZE_PARTITION;

//
// Declare the input structure for the HvInitializePartition hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INITIALIZE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_INITIALIZE_PARTITION, *PHV_INPUT_INITIALIZE_PARTITION;

//
// Declare the input and output structures for the HvGetPartitionProperty
// hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PARTITION_PROPERTY
{
    HV_PARTITION_ID             PartitionId;
    HV_PARTITION_PROPERTY_CODE  PropertyCode;

} HV_INPUT_GET_PARTITION_PROPERTY, *PHV_INPUT_GET_PARTITION_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PARTITION_PROPERTY
{
    HV_PARTITION_PROPERTY       PropertyValue;

} HV_OUTPUT_GET_PARTITION_PROPERTY, *PHV_OUTPUT_GET_PARTITION_PROPERTY;

//
// Declare the input structure for the HvSetPartitionProperty hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PARTITION_PROPERTY
{
    HV_PARTITION_ID             PartitionId;
    HV_PARTITION_PROPERTY_CODE  PropertyCode;
    HV_PARTITION_PROPERTY       PropertyValue;

} HV_INPUT_SET_PARTITION_PROPERTY, *PHV_INPUT_SET_PARTITION_PROPERTY;

//
// Declare the output structure for the HvGetPartitionId hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PARTITION_ID
{
    HV_PARTITION_ID             PartitionId;

} HV_OUTPUT_GET_PARTITION_ID, *PHV_OUTPUT_GET_PARTITION_ID;

//
// Declare the input and output structures for the
// HvGetNextChildPartition hypercall.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_NEXT_CHILD_PARTITION
{
    HV_PARTITION_ID ParentId;
    HV_PARTITION_ID PreviousChildId;
} HV_INPUT_GET_NEXT_CHILD_PARTITION, *PHV_INPUT_GET_NEXT_CHILD_PARTITION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_NEXT_CHILD_PARTITION
{
    HV_PARTITION_ID NextChildId;
} HV_OUTPUT_GET_NEXT_CHILD_PARTITION, *PHV_OUTPUT_GET_NEXT_CHILD_PARTITION;

//
// Declare constants and structures for submitting hypercalls.
//
#define HV_X64_MAX_HYPERCALL_ELEMENTS ((1<<12) - 1)

typedef union _HV_X64_HYPERCALL_INPUT
{
    //
    // Input: The call code, argument sizes and calling convention
    //
    struct
    {
        unsigned long CallCode        : 16; // Least significant bits
        unsigned long IsFast          : 1;  // Uses the register based form
        unsigned long Reserved1       : 15;
        unsigned long CountOfElements : 12;
        unsigned long Reserved2       : 4;
        unsigned long RepStartIndex   : 12;
        unsigned long Reserved3       : 4;  // Most significant bits
    };
    unsigned long long AsUINT64;

} HV_X64_HYPERCALL_INPUT, *PHV_X64_HYPERCALL_INPUT;

typedef union _HV_X64_HYPERCALL_OUTPUT
{
    //
    // Output: The result and returned data size
    //
    struct
    {
        HV_STATUS CallStatus;             // Least significant bits
        unsigned short    Reserved1;
        unsigned long    ElementsProcessed : 12;
        unsigned long    Reserved2         : 20; // Most significant bits
    };
    unsigned long long AsUINT64;

} HV_X64_HYPERCALL_OUTPUT, *PHV_X64_HYPERCALL_OUTPUT;

//
// Declare the various hypercall operations.
//
typedef enum _HV_CALL_CODE
{
    //
    // Reserved Feature Code
    //

    HvCallReserved0000                          = 0x0000,

    //
    // V1 Address space enlightment IDs
    //

    HvCallSwitchVirtualAddressSpace             = 0x0001,
    HvCallFlushVirtualAddressSpace              = 0x0002,
    HvCallFlushVirtualAddressList               = 0x0003,

    //
    // V1 Power Management and Run time metrics IDs
    //

    HvCallGetLogicalProcessorRunTime            = 0x0004,
    
    //
    // V? Additional Calls
    // Symbols
    //
    
    HvCallUpdateHvProcessorFeatures             = 0x0005,
    HvCallSwitchAliasMap                        = 0x0006,
    HvCallUpdateMicrocode                       = 0x0007,

    //
    // V1 Spinwait enlightenment IDs
    //

    HvCallNotifyLongSpinWait                    = 0x0008,

    //
    // V2 Core parking IDs
    //

    HvCallParkedVirtualProcessors               = 0x0009,

    //
    // V2 Invoke Hypervisor debugger
    //

    HvCallInvokeHypervisorDebugger              = 0x000a,

    //
    // V? VTL Calls
    // 17 Appendix A
    //
    
    HvCallSendSyntheticClusterIpi               = 0x000b,
    HvCallModifyVtlProtectionMask               = 0x000c,
    HvCallEnablePartitionVtl                    = 0x000d,
    HvCallDisablePartitionVtl                   = 0x000e,
    HvCallEnableVpVtl                           = 0x000f,
    HvCallDisableVpVtl                          = 0x0010,
    HvCallVtlCall                               = 0x0011,
    HvCallVtlReturn                             = 0x0012,

    HvCallFlushVirtualAddressSpaceEx            = 0x0013,
    HvCallFlushVirtualAddressListEx             = 0x0014,
    HvCallSendSyntheticClusterIpiEx             = 0x0015,

    //
    // V? secure hot patch support
    // Symbols
    //
    
    HvCallQueryImageInfo                        = 0x0016,
    HvCallMapImagePages                         = 0x0017,
    HvCallCommitPatch                           = 0x0018,
    HvCallSyncContext                           = 0x0019,
    HvCallSyncContextEx                         = 0x001a,

    //
    // V? CPU performance support
    // Symbols
    //
    
    HvCallSetPerfRegister                       = 0x001b,
    HvCallGetPerfRegister                       = 0x001c,
    
    //
    // Expansion support
    //
    
    HvCallReserved001d                          = 0x001d,
    HvCallReserved001e                          = 0x001e,
    HvCallReserved001f                          = 0x001f,
    HvCallReserved0020                          = 0x0020,
    HvCallReserved0021                          = 0x0021,
    HvCallReserved0022                          = 0x0022,
    HvCallReserved0023                          = 0x0023,
    HvCallReserved0024                          = 0x0024,
    HvCallReserved0025                          = 0x0025,
    HvCallReserved0026                          = 0x0026,
    HvCallReserved0027                          = 0x0027,
    HvCallReserved0028                          = 0x0028,
    HvCallReserved0029                          = 0x0029,
    HvCallReserved002a                          = 0x002a,
    HvCallReserved002b                          = 0x002b,
    HvCallReserved002c                          = 0x002c,
    HvCallReserved002d                          = 0x002d,
    HvCallReserved002e                          = 0x002e,
    HvCallReserved002f                          = 0x002f,
    HvCallReserved0030                          = 0x0030,
    HvCallReserved0031                          = 0x0031,
    HvCallReserved0032                          = 0x0032,
    HvCallReserved0033                          = 0x0033,
    HvCallReserved0034                          = 0x0034,
    HvCallReserved0035                          = 0x0035,
    HvCallReserved0036                          = 0x0036,
    HvCallReserved0037                          = 0x0037,
    HvCallReserved0038                          = 0x0038,
    HvCallReserved0039                          = 0x0039,
    HvCallReserved003a                          = 0x003a,
    HvCallReserved003b                          = 0x003b,
    HvCallReserved003c                          = 0x003c,
    HvCallReserved003d                          = 0x003d,
    HvCallReserved003e                          = 0x003e,
    HvCallReserved003f                          = 0x003f,

    //
    // V1 Partition Management IDs
    //

    HvCallCreatePartition                       = 0x0040,
    HvCallInitializePartition                   = 0x0041,
    HvCallFinalizePartition                     = 0x0042,
    HvCallDeletePartition                       = 0x0043,
    HvCallGetPartitionProperty                  = 0x0044,
    HvCallSetPartitionProperty                  = 0x0045,
    HvCallGetPartitionId                        = 0x0046,
    HvCallGetNextChildPartition                 = 0x0047,

    //
    // V1 Resource Management IDs
    //

    HvCallDepositMemory                         = 0x0048,
    HvCallWithdrawMemory                        = 0x0049,
    HvCallGetMemoryBalance                      = 0x004a,

    //
    // V1 Guest Physical Address Space Management IDs
    //

    HvCallMapGpaPages                           = 0x004b,
    HvCallUnmapGpaPages                         = 0x004c,

    //
    // V1 Intercept Management IDs
    //

    HvCallInstallIntercept                      = 0x004d,

    //
    // V1 Virtual Processor Management IDs
    //

    HvCallCreateVp                              = 0x004e,
    HvCallDeleteVp                              = 0x004f,
    HvCallGetVpRegisters                        = 0x0050,
    HvCallSetVpRegisters                        = 0x0051,

    //
    // V1 Virtual TLB IDs
    //

    HvCallTranslateVirtualAddress               = 0x0052,
    HvCallReadGpa                               = 0x0053,
    HvCallWriteGpa                              = 0x0054,

    //
    // V1 Interrupt Management IDs
    //

    HvCallAssertVirtualInterruptDeprecated      = 0x0055,
    HvCallClearVirtualInterrupt                 = 0x0056,

    //
    // V1 Port IDs
    //

    HvCallCreatePortDeprecated                  = 0x0057,
    HvCallDeletePort                            = 0x0058,
    HvCallConnectPortDeprecated                 = 0x0059,
    HvCallGetPortProperty                       = 0x005a,
    HvCallDisconnectPort                        = 0x005b,
    HvCallPostMessage                           = 0x005c,
    HvCallSignalEvent                           = 0x005d,

    //
    // V1 Partition State IDs
    //

    HvCallSavePartitionState                    = 0x005e,
    HvCallRestorePartitionState                 = 0x005f,

    //
    // V1 Trace IDs
    //

    HvCallInitializeEventLogBufferGroup         = 0x0060,
    HvCallFinalizeEventLogBufferGroup           = 0x0061,
    HvCallCreateEventLogBuffer                  = 0x0062,
    HvCallDeleteEventLogBuffer                  = 0x0063,
    HvCallMapEventLogBuffer                     = 0x0064,
    HvCallUnmapEventLogBuffer                   = 0x0065,
    HvCallSetEventLogGroupSources               = 0x0066,
    HvCallReleaseEventLogBuffer                 = 0x0067,
    HvCallFlushEventLogBuffer                   = 0x0068,

    //
    // V1 Dbg Call IDs
    //

    HvCallPostDebugData                         = 0x0069,
    HvCallRetrieveDebugData                     = 0x006a,
    HvCallResetDebugSession                     = 0x006b,

    //
    // V1 Stats IDs
    //

    HvCallMapStatsPage                          = 0x006c,
    HvCallUnmapStatsPage                        = 0x006d,

    //
    // V2 Guest Physical Address Space Management IDs
    // 

    HvCallMapSparseGpaPages                     = 0x006e,

    //
    // V2 Set System Property
    //
    
    HvCallSetSystemProperty                     = 0x006f,

    //
    // V2 Port Ids.
    //

    HvCallSetPortProperty                       = 0x0070,

    //
    // V2 Test IDs
    //

    HvCallOutputDebugCharacter                  = 0x0071,
    HvCallEchoIncrement                         = 0x0072,
    HvCallPerfNop                               = 0x0073,
    HvCallPerfNopInput                          = 0x0074,
    HvCallPerfNopOutput                         = 0x0075,

    //
    // 17 Appendix A
    //
    
    HvCallAddLogicalProcessor                   = 0x0076,
    HvCallRemoveLogicalProcessor                = 0x0077,
    HvCallQueryNumaDistance                     = 0x0078,
    HvCallSetLogicalProcessorProperty           = 0x0079,
    HvCallGetLogicalProcessorProperty           = 0x007a,

    HvCallGetSystemProperty                     = 0x007b,

    HvCallMapDeviceInterrupt                    = 0x007c,
    HvCallUnmapDeviceInterrupt                  = 0x007d,
    HvCallRetargetDeviceInterrupt               = 0x007e,
    HvCallRetargetRootDeviceInterrupt           = 0x007f,

    HvCallAssertDeviceInterrupt                 = 0x0080,
    HvCallReserved0081                          = 0x0081,

    HvCallAttachDevice                          = 0x0082,
    HvCallDetachDevice                          = 0x0083,

    HvCallEnterSleepState                       = 0x0084,
    HvCallNotifyStandbyTransition               = 0x0085,
    HvCallPrepareForHibernate                   = 0x0086,

    HvCallNotifyPartitionEvent                  = 0x0087,

    HvCallGetLogicalProcessorRegisters          = 0x0088,
    HvCallSetLogicalProcessorRegisters          = 0x0089,
    HvCallQueryAssociatedLpsForMca              = 0x008a,

    HvCallNotifyPortRingEmpty                   = 0x008b,

    HvCallInjectSyntheticMachineCheck           = 0x008c,

    HvCallScrubPartition                        = 0x008d,

    HvCallCollectLivedump                       = 0x008e,

    HvCallDisableHypervisor                     = 0x008f,

    HvCallModifySparseGpaPages                  = 0x0090,

    HvCallRegisterInterceptResult               = 0x0091,
    HvCallUnregisterInterceptResult             = 0x0092,

    HvCallGetCoverageData                       = 0x0093,

    HvCallAssertVirtualInterrupt                = 0x0094,

    HvCallCreatePort                            = 0x0095,
    HvCallConnectPort                           = 0x0096,

    HvCallGetSpaPageList                        = 0x0097,
    HvCallReserved0098                          = 0x0098,

    HvCallStartVirtualProcessor                 = 0x0099,
    HvCallGetVpIndexFromApicId                  = 0x009a,

    HvCallGetPowerProperty                      = 0x009b,
    HvCallSetPowerProperty                      = 0x009c,
    HvCallCreatePasidSpace                      = 0x009d,
    HvCallDeletePasidSpace                      = 0x009e,
    HvCallSetPasidAddressSpace                  = 0x009f,
    HvCallFlushPasidAddressSpace                = 0x00a0,
    HvCallFlushPasidAddressList                 = 0x00a1,
    HvCallAttachPasidSpace                      = 0x00a2,
    HvCallDetachPasidSpace                      = 0x00a3,
    HvCallEnablePasid                           = 0x00a4,
    HvCallDisablePasid                          = 0x00a5,
    HvCallAcknowledgeDevicePageRequest          = 0x00a6,

    HvCallCreateDevicePrQueue                   = 0x00a7,
    HvCallDeleteDevicePrQueue                   = 0x00a8,
    HvCallSetDevicePrqProperty                  = 0x00a9,
    HvCallGetPhysicalDeviceProperty             = 0x00aa,
    HvCallSetPhysicalDeviceProperty             = 0x00ab,

    HvCallTranslateVirtualAddressEx             = 0x00ac,

    HvCallCheckForIoIntercept                   = 0x00ad,

    HvCallSetGpaPageAttributes                  = 0x00ae,

    HvCallFlushGuestPhysicalAddressSpace        = 0x00af,
    HvCallFlushGuestPhysicalAddressList         = 0x00b0,

    HvCallCreateDeviceDomain                    = 0x00b1,
    HvCallAttachDeviceDomain                    = 0x00b2,
    HvCallMapDeviceGpaPages                     = 0x00b3,
    HvCallUnmapDeviceGpaPages                   = 0x00b4,

    //
    // V? CPU Group Support
    //
    
    HvCallCreateCpuGroup                        = 0x00b5,
    HvCallDeleteCpuGroup                        = 0x00b6,
    HvCallGetCpuGroupProperty                   = 0x00b7,
    HvCallSetCpuGroupProperty                   = 0x00b8,
    HvCallGetCpuGroupAffinity                   = 0x00b9,
    HvCallGetNextCpuGroup                       = 0x00ba,
    HvCallGetNextCpuGroupPartition              = 0x00bb,

    HvCallAddPhysicalMemory                     = 0x00bc,

    HvCallCompleteIntercept                     = 0x00bd,

    HvCallPrecommitGpaPages                     = 0x00be,
    HvCallUncommitGpaPages                      = 0x00bf,

    HvCallSignalEventDirect                     = 0x00c0,
    HvCallPostMessageDirect                     = 0x00c1,

    HvCallDispatchVp                            = 0x00c2,

    //
    // V? IOMMU Support
    // Symbols
    //

    HvCallProcessIommuPrq                       = 0x00c3,
    HvCallDetachDeviceDomain                    = 0x00c4,
    HvCallDeleteDeviceDomain                    = 0x00c5,
    HvCallQueryDeviceDomain                     = 0x00c6,

    //
    // V? Sparse Page Support
    // Symbols
    //

    HvCallMapSparseDeviceGpaPages               = 0x00c7,
    HvCallUnmapSparseDeviceGpaPages             = 0x00c8,
    HvCallGetGpaPagesAccessState                = 0x00c9,
    HvCallGetSparseGpaPagesAccessState          = 0x00ca,
    HvCallInvokeTestFramework                   = 0x00cb,
    HvCallQueryVtlProtectionMaskRange           = 0x00cc,
    HvCallModifyVtlProtectionMaskRange          = 0x00cd,
    HvCallConfigureDeviceDomain                 = 0x00ce,
    HvCallQueryDeviceDomainProperties           = 0x00cf,
    HvCallFlushDeviceDomain                     = 0x00d0,
    HvCallFlushDeviceDomainList                 = 0x00d1,
    HvCallAcquireSparseGpaPageHostAccess        = 0x00d2,
    HvCallReleaseSparseGpaPageHostAccess        = 0x00d3,
    HvCallCheckSparseGpaPageVtlAccess           = 0x00d4,
    HvCallEnableDeviceInterrupt                 = 0x00d5,
    HvCallFlushTlb                              = 0x00d6,
    HvCallAcquireSparseSpaPageHostAccess        = 0x00d7,
    HvCallReleaseSparseSpaPageHostAccess        = 0x00d8,
    HvCallAcceptGpaPages                        = 0x00d9,
    HvCallUnacceptGpaPages                      = 0x00da,
    HvCallModifySparseGpaPageHostVisibility     = 0x00db,
    HvCallLockSparseGpaPageMapping              = 0x00dc,
    HvCallUnlockSparseGpaPageMapping            = 0x00dd,

    HvCallRequestProcessorHalt                  = 0x00de,

    HvCallGetInterceptData                      = 0x00df,

    HvCallQueryDeviceInterruptTarget            = 0x00e0,

    HvCallMapVpStatePage                        = 0x00e1,
    HvCallUnmapVpStatePage                      = 0x00e2,

    //
    // V? XSAVE Support
    // Symbols
    //

    HvCallGetVpState                            = 0x00e3,
    HvCallSetVpState                            = 0x00e4,

    //
    // V? LAPIC Support
    // Symbols
    //

    HvCallGetVpSetFromMda                       = 0x00e5,
    HvCallReserved00E6                          = 0x00e6,

    //
    // V? IPT Support
    // Symbols
    //

    HvCallCreateIptBuffers                      = 0x00e7,
    HvCallDeleteIptBuffers                      = 0x00e8,
    HvCallControlHypervisorIptTrace             = 0x00e9,

    //
    // V? Persisted Device Support
    // Symbols
    //

    HvCallReserveDeviceInterrupt                = 0x00ea,
    HvCallPersistDevice                         = 0x00eb,
    HvCallUnpersistDevice                       = 0x00ec,
    HvCallPersistDeviceInterrupt                = 0x00ed,

    //
    // V? Perf Processor Support
    // Symbols
    //

    HvCallRefreshPerformanceCounters            = 0x00ee,
    HvCallImportIsolatedPages                   = 0x00ef,
    HvCallCompletePendingIsolatedPagesImport    = 0x00f0,
    HvCallCompleteIsolatedImport                = 0x00f1,
    HvCallIssueSnpPspGuestRequest               = 0x00f2,
    HvCallRootSignalEvent                       = 0x00f3,
    HvCallGetVpCpuidValues                      = 0x00f4,
    HvCallReadSystemMemory                      = 0x00f5,
    HvCallSetHwWatchdogConfig                   = 0x00f6,
    HvCallRemovePhysicalMemory                  = 0x00f7,
    HvCallLogHypervisorSystemConfig             = 0x00f8,
    HvCallIssueNestedSnpPspRequests             = 0x00f9,
    HvCallCompleteSnpPspRequests                = 0x00fa,
    HvCallSubsumeInitializedMemory              = 0x00fb,
    HvCallSubsumeVp                             = 0x00fc,
    HvCallDestroySubsumedContext                = 0x00fd,

    //
    // Total of all hypercalls
    //
            
    HvCallCount

} HV_CALL_CODE, *PHV_CALL_CODE;

//
// Partition save&restore definitions.
//

//
// Definition of the HvCallDepositMemory hypercall input structure.
// This call deposits memory into a child partition's memory pool.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DEPOSIT_MEMORY
{
    //
    // Supplies the partition ID of the child partition to deposit the
    // memory into.
    //
    HV_PARTITION_ID PartitionId;

    //
    // Supplies the GPAs of the pages to be deposited.
    //
    HV_GPA_PAGE_NUMBER GpaPageList[];

} HV_INPUT_DEPOSIT_MEMORY, *PHV_INPUT_DEPOSIT_MEMORY;

//
// Definition of the HvCallWithdrawMemory hypercall input and output
// structures.  This call withdraws memory from a child partition's
// memory pool.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_WITHDRAW_MEMORY
{
    //
    // Supplies the partition ID of the child partition from which the
    // memory should be withdrawn.
    //
    HV_PARTITION_ID PartitionId;

    //
    // Supplies the proximity domain from which the memory should be
    // allocated.
    //
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;

} HV_INPUT_WITHDRAW_MEMORY, *PHV_INPUT_WITHDRAW_MEMORY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_WITHDRAW_MEMORY
{
    //
    // Returns the GPA of the memory withdrawn.
    //
    HV_GPA_PAGE_NUMBER GpaPageList[];

} HV_OUTPUT_WITHDRAW_MEMORY, *PHV_OUTPUT_WITHDRAW_MEMORY;

//
// Definition of the HvCallGetMemoryBalance hypercall input and output
// structures.  This call determines the hypervisor memory resource
// usage of a child partition's memory pool.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_MEMORY_BALANCE
{
    //
    // Supplies the partition ID of the child partition whose memory
    // pool should be queried.
    //
    HV_PARTITION_ID PartitionId;

    //
    // Supplies the proximity domain to query.
    //
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;

} HV_INPUT_GET_MEMORY_BALANCE, *PHV_INPUT_GET_MEMORY_BALANCE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_MEMORY_BALANCE
{
    //
    // Returns the number of pages available.
    //
    unsigned long long PagesAvailable;

    //
    // Returns the number of pages actively being used for hypercall
    // datastructures.
    //
    unsigned long long PagesInUse;

} HV_OUTPUT_GET_MEMORY_BALANCE, *PHV_OUTPUT_GET_MEMORY_BALANCE;

//
// Definition of the HvCallMapGpaPages hypercall input structure.
// This call maps a range of GPA to a supplied range of SPA.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_GPA_PAGES
{
    //
    // Supplies the partition ID of the partition that this request is for.
    //

    HV_PARTITION_ID TargetPartitionId;

    //
    // Supplies the base guest physical page number where the mapping
    // will begin.
    //

    HV_GPA_PAGE_NUMBER TargetGpaBase;

    //
    // Supplies the flags to use for the mapping.
    //

    HV_MAP_GPA_FLAGS MapFlags;

    //
    // Supplies an array of guest physical page numbers in the calling
    // partition that the range of GPA will be mapped to.
    //

    HV_GPA_PAGE_NUMBER SourceGpaPageList[];

} HV_INPUT_MAP_GPA_PAGES, *PHV_INPUT_MAP_GPA_PAGES;

//
// Definition of the HvCallMapSparseGpaPages hypercall input structure.
// This call maps a range of GPA to a supplied range of SPA.
//

typedef struct _HV_GPA_MAPPING
{
    HV_GPA_PAGE_NUMBER TargetGpaPageNumber;
    HV_GPA_PAGE_NUMBER SourceGpaPageNumber;
} HV_GPA_MAPPING, *PHV_GPA_MAPPING;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_SPARSE_GPA_PAGES
{
    //
    // Supplies the partition ID of the partition that this request is for.
    //

    HV_PARTITION_ID TargetPartitionId;

    //
    // Supplies the flags to use for the mapping.
    //

    HV_MAP_GPA_FLAGS MapFlags;

    //
    // Supplies an array of pairs of physical page numbers.
    //

    HV_GPA_MAPPING PageList[];

} HV_INPUT_MAP_SPARSE_GPA_PAGES, *PHV_INPUT_MAP_SPARSE_GPA_PAGES;

//
// Definition of the HvCallUnmapGpaPages hypercall input structure.
// This call unmaps a range of GPA.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_GPA_PAGES
{

    //
    // Supplies the partition ID of the partition that this request is for.
    //

    HV_PARTITION_ID TargetPartitionId;

    //
    // Supplies the base guest physical page number where the GPA
    // space will be removed.
    //

    HV_GPA_PAGE_NUMBER TargetGpaBase;

} HV_INPUT_UNMAP_GPA_PAGES, *PHV_INPUT_UNMAP_GPA_PAGES;

//
// Definition of the HvCallTranslateVirtualAddress hypercall input and
// output structures.  This call translates a GVA to a GPA.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_TRANSLATE_VIRTUAL_ADDRESS
{
    //
    // Supplies the partition ID of the partition in which the
    // translation should take place.
    //

    HV_PARTITION_ID PartitionId;

    //
    // Supplies the virtual processor whose GVA space is to be
    // accessed.
    //

    HV_VP_INDEX VpIndex;

    //
    // Supplies the control flags governing the access.
    //

    HV_TRANSLATE_GVA_CONTROL_FLAGS ControlFlags;

    //
    // Supplies the GVA page number to translate.
    //

    HV_GVA_PAGE_NUMBER GvaPage;

} HV_INPUT_TRANSLATE_VIRTUAL_ADDRESS, *PHV_INPUT_TRANSLATE_VIRTUAL_ADDRESS;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS
{
    //
    // Flags to indicate the disposition of the translation.
    //

    HV_TRANSLATE_GVA_RESULT TranslationResult;

    //
    // The GPA to which the GVA translated.
    //

    HV_GPA_PAGE_NUMBER GpaPage;

} HV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS, *PHV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS;

//
// Definition of the HvCallReadGpa hypercall input and output
// structures.  This call reads from the indicated GPA.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_READ_GPA
{
    //
    // Supplies the partition ID of the partition whose GPA space is
    // to be read.
    //

    HV_PARTITION_ID PartitionId;

    //
    // Supplies the virtual processor whose GPA space is to be read
    // (virtual processor GPA spaces may differ, due to overlays).
    //

    HV_VP_INDEX VpIndex;

    //
    // Supplies the number of bytes to read.
    //

    unsigned long ByteCount;

    //
    // Supplies the start of the GPA range to read.
    //

    HV_GPA BaseGpa;

    //
    // Supplies the control flags governing the read.
    //

    HV_ACCESS_GPA_CONTROL_FLAGS ControlFlags;

} HV_INPUT_READ_GPA, *PHV_INPUT_READ_GPA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_READ_GPA
{
    //
    // Flags to indicate the disposition of the read.
    //

    HV_ACCESS_GPA_RESULT AccessResult;

    //
    // The data which was read.
    //

    unsigned char Data[16];

} HV_OUTPUT_READ_GPA, *PHV_OUTPUT_READ_GPA;

//
// Definition of the HvCallWriteGpa hypercall input and output
// structures.  This call writes from the indicated GPA.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_WRITE_GPA
{
    //
    // Supplies the partition ID of the partition whose GPA space is
    // to be written.
    //

    HV_PARTITION_ID PartitionId;

    //
    // Supplies the virtual processor whose GPA space is to be written
    // (virtual processor GPA spaces may differ, due to overlays).
    //

    HV_VP_INDEX VpIndex;

    //
    // Supplies the number of bytes to write.
    //

    unsigned long ByteCount;

    //
    // Supplies the start of the GPA range to write.
    //

    HV_GPA BaseGpa;

    //
    // Supplies the control flags governing the write.
    //

    HV_ACCESS_GPA_CONTROL_FLAGS ControlFlags;

    //
    // Supplies the data to write.
    //

    unsigned char Data[16];

} HV_INPUT_WRITE_GPA, *PHV_INPUT_WRITE_GPA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_WRITE_GPA
{
    //
    // Flags to indicate the disposition of the write.
    //

    HV_ACCESS_GPA_RESULT AccessResult;

} HV_OUTPUT_WRITE_GPA, *PHV_OUTPUT_WRITE_GPA;

//
// Definition of the HvCallInstallIntercept hypercall input
// structure.  This call sets an intercept.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INSTALL_INTERCEPT
{
    HV_PARTITION_ID PartitionId;
    HV_INTERCEPT_ACCESS_TYPE_MASK AccessType;
    HV_INTERCEPT_TYPE InterceptType;
    HV_INTERCEPT_PARAMETERS InterceptParameter;
} HV_INPUT_INSTALL_INTERCEPT, *PHV_INPUT_INSTALL_INTERCEPT;


//
// Definition of the HvCallCreateVp hypercall input structure.
// This call creates a virtual processor.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_VP
{
    HV_PARTITION_ID          PartitionId;
    HV_VP_INDEX              VpIndex;
    unsigned long                   Padding;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    unsigned long long                   Flags;
} HV_INPUT_CREATE_VP, *PHV_INPUT_CREATE_VP;

//
// Definition of the HvCallDeleteVp hypercall input structure.
// This call deletes a virtual processor.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX     VpIndex;
} HV_INPUT_DELETE_VP, *PHV_INPUT_DELETE_VP;

//
// External names used to manupulate registers
//

// 7.8.2 Virtual Processor Register Names
typedef enum _HV_REGISTER_NAME
{
    // Suspend Registers
    HvRegisterExplicitSuspend           = 0x00000000,
    HvRegisterInterceptSuspend          = 0x00000001,
    HvRegisterInstructionEmulationHints = 0x00000002,
    HvRegisterDispatchSuspend           = 0x00000003,
    HvRegisterInternalActivityState     = 0x00000004,

    // Version
    HvRegisterHypervisorVersion = 0x00000100,

    // Feature Access (registers are 128 bits)
    // 128-bit result same as CPUID 0x40000003
    HvRegisterPrivilegesAndFeaturesInfo = 0x00000200,

    // 128-bit result same as CPUID 0x40000004
    HvRegisterFeaturesInfo              = 0x00000201,

    // 128-bit result same as CPUID 0x40000005
    HvRegisterImplementationLimitsInfo  = 0x00000202,

    // 128-bit result same as CPUID 0x40000006
    HvRegisterHardwareFeaturesInfo      = 0x00000203,

    // 128-bit result same as CPUID 0x40000007
    HvRegisterCpuManagementFeaturesInfo = 0x00000204,

    // 128-bit result same as CPUID 0x40000008
    HvRegisterSvmFeaturesInfo           = 0x00000205,

    // 128-bit result same as CPUID 0x40000009
    HvRegisterSkipLevelFeaturesInfo     = 0x00000206,

    // 128-bit result same as CPUID 0x4000000a
    HvRegisterNestedVirtFeaturesInfo    = 0x00000207,

    // 128-bit result same as CPUID 0x4000000b
    HvRegisterIptFeaturesInfo           = 0x00000208,

    // Guest Crash Registers
    HvRegisterGuestCrashP0  = 0x00000210,
    HvRegisterGuestCrashP1  = 0x00000211,
    HvRegisterGuestCrashP2  = 0x00000212,
    HvRegisterGuestCrashP3  = 0x00000213,
    HvRegisterGuestCrashP4  = 0x00000214,
    HvRegisterGuestCrashCtl = 0x00000215,

    // Power State Configuration
    HvRegisterPowerStateConfigC1    = 0x00000220,
    HvRegisterPowerStateTriggerC1   = 0x00000221,
    HvRegisterPowerStateConfigC2    = 0x00000222,
    HvRegisterPowerStateTriggerC2   = 0x00000223,
    HvRegisterPowerStateConfigC3    = 0x00000224,
    HvRegisterPowerStateTriggerC3   = 0x00000225,

    // System Reset
    HvRegisterSystemReset = 0x00000230,

    // Frequency Registers
    HvRegisterProcessorClockFrequency = 0x00000240,
    HvRegisterInterruptClockFrequency = 0x00000241,

    // Idle Register
    HvRegisterGuestIdle = 0x00000250,

    // Guest Debug
    HvRegisterDebugDeviceOptions = 0x00000260,

    // Memory Zeroing
    HvRegisterMemoryZeroingControl = 0x00000270,

    // Pending Interruption Register
    HvRegisterPendingInterruption = 0x00010002,

    // Interrupt State register
    HvRegisterInterruptState = 0x00010003,

    // Pending Event Register
    HvRegisterPendingEvent0     = 0x00010004,
    HvRegisterPendingEvent1     = 0x00010005,

    // Notification Register
    HvX64RegisterDeliverabilityNotifications = 0x00010006,

    // User-Mode Registers
    HvX64RegisterRax                = 0x00020000,
    HvX64RegisterRcx                = 0x00020001,
    HvX64RegisterRdx                = 0x00020002,
    HvX64RegisterRbx                = 0x00020003,
    HvX64RegisterRsp                = 0x00020004,
    HvX64RegisterRbp                = 0x00020005,
    HvX64RegisterRsi                = 0x00020006,
    HvX64RegisterRdi                = 0x00020007,
    HvX64RegisterR8                 = 0x00020008,
    HvX64RegisterR9                 = 0x00020009,
    HvX64RegisterR10                = 0x0002000A,
    HvX64RegisterR11                = 0x0002000B,
    HvX64RegisterR12                = 0x0002000C,
    HvX64RegisterR13                = 0x0002000D,
    HvX64RegisterR14                = 0x0002000E,
    HvX64RegisterR15                = 0x0002000F,
    HvX64RegisterRip                = 0x00020010,
    HvX64RegisterRflags             = 0x00020011,

    // Floating Point and Vector Registers
    HvX64RegisterXmm0               = 0x00030000,
    HvX64RegisterXmm1               = 0x00030001,
    HvX64RegisterXmm2               = 0x00030002,
    HvX64RegisterXmm3               = 0x00030003,
    HvX64RegisterXmm4               = 0x00030004,
    HvX64RegisterXmm5               = 0x00030005,
    HvX64RegisterXmm6               = 0x00030006,
    HvX64RegisterXmm7               = 0x00030007,
    HvX64RegisterXmm8               = 0x00030008,
    HvX64RegisterXmm9               = 0x00030009,
    HvX64RegisterXmm10              = 0x0003000A,
    HvX64RegisterXmm11              = 0x0003000B,
    HvX64RegisterXmm12              = 0x0003000C,
    HvX64RegisterXmm13              = 0x0003000D,
    HvX64RegisterXmm14              = 0x0003000E,
    HvX64RegisterXmm15              = 0x0003000F,
    HvX64RegisterFpMmx0             = 0x00030010,
    HvX64RegisterFpMmx1             = 0x00030011,
    HvX64RegisterFpMmx2             = 0x00030012,
    HvX64RegisterFpMmx3             = 0x00030013,
    HvX64RegisterFpMmx4             = 0x00030014,
    HvX64RegisterFpMmx5             = 0x00030015,
    HvX64RegisterFpMmx6             = 0x00030016,
    HvX64RegisterFpMmx7             = 0x00030017,
    HvX64RegisterFpControlStatus    = 0x00030018,
    HvX64RegisterXmmControlStatus   = 0x00030019,

    // Control Registers
    HvX64RegisterCr0                = 0x00040000,
    HvX64RegisterCr2                = 0x00040001,
    HvX64RegisterCr3                = 0x00040002,
    HvX64RegisterCr4                = 0x00040003,
    HvX64RegisterCr8                = 0x00040004,
    HvX64RegisterXfem               = 0x00040005,

    // X64 Intermediate Control Registers
    HvX64RegisterIntermediateCr0    = 0x00041000,
    HvX64RegisterIntermediateCr4    = 0x00041003,
    HvX64RegisterIntermediateCr8    = 0x00041004,

    // Debug Registers
    HvX64RegisterDr0                = 0x00050000,
    HvX64RegisterDr1                = 0x00050001,
    HvX64RegisterDr2                = 0x00050002,
    HvX64RegisterDr3                = 0x00050003,
    HvX64RegisterDr6                = 0x00050004,
    HvX64RegisterDr7                = 0x00050005,

    // Segment Registers
    HvX64RegisterEs                 = 0x00060000,
    HvX64RegisterCs                 = 0x00060001,
    HvX64RegisterSs                 = 0x00060002,
    HvX64RegisterDs                 = 0x00060003,
    HvX64RegisterFs                 = 0x00060004,
    HvX64RegisterGs                 = 0x00060005,
    HvX64RegisterLdtr               = 0x00060006,
    HvX64RegisterTr                 = 0x00060007,

    // Table Registers
    HvX64RegisterIdtr               = 0x00070000,
    HvX64RegisterGdtr               = 0x00070001,

    // Virtualized MSRs
    HvX64RegisterTsc                = 0x00080000,
    HvX64RegisterEfer               = 0x00080001,
    HvX64RegisterKernelGsBase       = 0x00080002,
    HvX64RegisterApicBase           = 0x00080003,
    HvX64RegisterPat                = 0x00080004,
    HvX64RegisterSysenterCs         = 0x00080005,
    HvX64RegisterSysenterEip        = 0x00080006,
    HvX64RegisterSysenterEsp        = 0x00080007,
    HvX64RegisterStar               = 0x00080008,
    HvX64RegisterLstar              = 0x00080009,
    HvX64RegisterCstar              = 0x0008000A,
    HvX64RegisterSfmask             = 0x0008000B,
    HvX64RegisterInitialApicId      = 0x0008000C,

    //
    // Cache control MSRs
    //
    HvX64RegisterMtrrCap        = 0x0008000D,
    HvX64RegisterMtrrDefType    = 0x0008000E,
    HvX64RegisterMtrrPhysBase0  = 0x00080010,
    HvX64RegisterMtrrPhysBase1  = 0x00080011,
    HvX64RegisterMtrrPhysBase2  = 0x00080012,
    HvX64RegisterMtrrPhysBase3  = 0x00080013,
    HvX64RegisterMtrrPhysBase4  = 0x00080014,
    HvX64RegisterMtrrPhysBase5  = 0x00080015,
    HvX64RegisterMtrrPhysBase6  = 0x00080016,
    HvX64RegisterMtrrPhysBase7  = 0x00080017,
    HvX64RegisterMtrrPhysBase8  = 0x00080018,
    HvX64RegisterMtrrPhysBase9  = 0x00080019,
    HvX64RegisterMtrrPhysBaseA  = 0x0008001A,
    HvX64RegisterMtrrPhysBaseB  = 0x0008001B,
    HvX64RegisterMtrrPhysBaseC  = 0x0008001C,
    HvX64RegisterMtrrPhysBaseD  = 0x0008001D,
    HvX64RegisterMtrrPhysBaseE  = 0x0008001E,
    HvX64RegisterMtrrPhysBaseF  = 0x0008001F,

    HvX64RegisterMtrrPhysMask0  = 0x00080040,
    HvX64RegisterMtrrPhysMask1  = 0x00080041,
    HvX64RegisterMtrrPhysMask2  = 0x00080042,
    HvX64RegisterMtrrPhysMask3  = 0x00080043,
    HvX64RegisterMtrrPhysMask4  = 0x00080044,
    HvX64RegisterMtrrPhysMask5  = 0x00080045,
    HvX64RegisterMtrrPhysMask6  = 0x00080046,
    HvX64RegisterMtrrPhysMask7  = 0x00080047,
    HvX64RegisterMtrrPhysMask8  = 0x00080048,
    HvX64RegisterMtrrPhysMask9  = 0x00080049,
    HvX64RegisterMtrrPhysMaskA  = 0x0008004A,
    HvX64RegisterMtrrPhysMaskB  = 0x0008004B,
    HvX64RegisterMtrrPhysMaskC  = 0x0008004C,
    HvX64RegisterMtrrPhysMaskD  = 0x0008004D,
    HvX64RegisterMtrrPhysMaskE  = 0x0008004E,
    HvX64RegisterMtrrPhysMaskF  = 0x0008004F,

    HvX64RegisterMtrrFix64k00000 = 0x00080070,
    HvX64RegisterMtrrFix16k80000 = 0x00080071,
    HvX64RegisterMtrrFix16kA0000 = 0x00080072,
    HvX64RegisterMtrrFix4kC0000  = 0x00080073,
    HvX64RegisterMtrrFix4kC8000  = 0x00080074,
    HvX64RegisterMtrrFix4kD0000  = 0x00080075,
    HvX64RegisterMtrrFix4kD8000  = 0x00080076,
    HvX64RegisterMtrrFix4kE0000  = 0x00080077,
    HvX64RegisterMtrrFix4kE8000  = 0x00080078,
    HvX64RegisterMtrrFix4kF0000  = 0x00080079,
    HvX64RegisterMtrrFix4kF8000  = 0x0008007A,

    // Misc x64 MSRs
    HvX64RegisterTscAux             = 0x0008007B,
    HvX64RegisterBndcfgs            = 0x0008007C,
    HvX64RegisterDebugCtl           = 0x0008007D,
    HvX64RegisterAvailable0008007E  = 0x0008007E,
    HvX64RegisterAvailable0008007F  = 0x0008007F,

    // SGX-LC MSRs
    HvX64RegisterSgxLaunchControl0 = 0x00080080,
    HvX64RegisterSgxLaunchControl1 = 0x00080081,
    HvX64RegisterSgxLaunchControl2 = 0x00080082,
    HvX64RegisterSgxLaunchControl3 = 0x00080083,

    // Speculation MSRs
    HvX64RegisterSpecCtrl       = 0x00080084,
    HvX64RegisterPredCmd        = 0x00080085,
    HvX64RegisterVirtSpecCtrl   = 0x00080086,

    // VMX MSRs
    HvX64RegisterMsrIa32MiscEnable          = 0x000800a0,
    HvX64RegisterIa32FeatureControl         = 0x000800a1,
    HvX64RegisterIa32VmxBasic               = 0x000800a2,
    HvX64RegisterIa32VmxPinbasedCtls        = 0x000800a3,
    HvX64RegisterIa32VmxProcbasedCtls       = 0x000800a4,
    HvX64RegisterIa32VmxExitCtls            = 0x000800a5,
    HvX64RegisterIa32VmxEntryCtls           = 0x000800a6,
    HvX64RegisterIa32VmxMisc                = 0x000800a7,
    HvX64RegisterIa32VmxCr0Fixed0           = 0x000800a8,
    HvX64RegisterIa32VmxCr0Fixed1           = 0x000800a9,
    HvX64RegisterIa32VmxCr4Fixed0           = 0x000800aa,
    HvX64RegisterIa32VmxCr4Fixed1           = 0x000800ab,
    HvX64RegisterIa32VmxVmcsEnum            = 0x000800ac,
    HvX64RegisterIa32VmxProcbasedCtls2      = 0x000800ad,
    HvX64RegisterIa32VmxEptVpidCap          = 0x000800ae,
    HvX64RegisterIa32VmxTruePinbasedCtls    = 0x000800af,
    HvX64RegisterIa32VmxTrueProcbasedCtls   = 0x000800b0,
    HvX64RegisterIa32VmxTrueExitCtls        = 0x000800b1,
    HvX64RegisterIa32VmxTrueEntryCtls       = 0x000800b2,

    // Tracing and PMU MSRs
    HvX64RegisterPerfGlobalCtrl     = 0x00081000,
    HvX64RegisterPerfGlobalStatus   = 0x00081001,
    HvX64RegisterPerfGlobalInUse    = 0x00081002,
    HvX64RegisterFixedCtrCtrl       = 0x00081003,
    HvX64RegisterDsArea             = 0x00081004,
    HvX64RegisterPebsEnable         = 0x00081005,
    HvX64RegisterPebsLdLat          = 0x00081006,
    HvX64RegisterPebsFrontend       = 0x00081007,
    HvX64RegisterRtitCtl            = 0x00081008,
    HvX64RegisterRtitStatus         = 0x00081009,
    HvX64RegisterRtitOutputBase     = 0x0008100a,
    HvX64RegisterRtitOutputMaskPtrs = 0x0008100b,
    HvX64RegisterRtitCr3Match       = 0x0008100c,

    // Perf MSRs
    HvX64RegisterPerfEvtSel0    = 0x00081100,

    // PMC MSRs
    HvX64RegisterPmc0           = 0x00081200,

    HvX64RegisterFixedCtr0      = 0x00081300,

    HvX64RegisterRtitAddr0A     = 0x00081400,

    // LBR MSRs
    HvX64RegisterLbrTos         = 0x00082000,
    HvX64RegisterLbrSelect      = 0x00082001,
    HvX64RegisterLerFromLip     = 0x00082002,
    HvX64RegisterLerToLip       = 0x00082003,

    HvX64RegisterLbrFrom0       = 0x00082100,

    HvX64RegisterLbrTo0         = 0x00082200,

    HvX64RegisterLbrInfo0       = 0x00083300,

    // X2APIC MSRs
    HvX64RegisterApicId         = 0x00084802,
    HvX64RegisterApicVersion    = 0x00084803,

    // Hypervisor-defined MSRs (Misc)
    HvRegisterVpRuntime                 = 0x00090000,
    HvX64RegisterHypercall              = 0x00090001,
    HvRegisterGuestOsId                 = 0x00090002,
    HvRegisterVpIndex                   = 0x00090003,
    HvRegisterTimeRefCount              = 0x00090004,
    HvRegisterCpuManagementVersion      = 0x00090007,

    // Virtual APIC registers MSRs
    HvX64RegisterSyntheticEoi   = 0x00090010,
    HvX64RegisterSyntheticIcr   = 0x00090011,
    HvX64RegisterSyntheticTpr   = 0x00090012,

    HvRegisterVpAssistPage      = 0x00090013,

    HvRegisterVpRootSignalCount = 0x00090014,

    HvRegisterReferenceTsc      = 0x00090017,

    // Performance statistics MSRs
    HvRegisterStatsPartitionRetail      = 0x00090020,
    HvRegisterStatsPartitionInternal    = 0x00090021,
    HvRegisterStatsVpRetail             = 0x00090022,
    HvRegisterStatsVpInternal           = 0x00090023,

    HvX64RegisterEmulatedTimerPeriod    = 0x00090030,
    HvX64RegisterEmulatedTimerControl   = 0x00090031,
    HvX64RegisterPmTimerAssist          = 0x00090032,

    // Hypervisor-defined MSRs (Nested Misc)
    HvRegisterNestedVpIndex             = 0x00091003,

    // Hypervisor-defined MSRs (Synic)
    HvRegisterSint0              = 0x000A0000,
    HvRegisterSint1              = 0x000A0001,
    HvRegisterSint2              = 0x000A0002,
    HvRegisterSint3              = 0x000A0003,
    HvRegisterSint4              = 0x000A0004,
    HvRegisterSint5              = 0x000A0005,
    HvRegisterSint6              = 0x000A0006,
    HvRegisterSint7              = 0x000A0007,
    HvRegisterSint8              = 0x000A0008,
    HvRegisterSint9              = 0x000A0009,
    HvRegisterSint10             = 0x000A000A,
    HvRegisterSint11             = 0x000A000B,
    HvRegisterSint12             = 0x000A000C,
    HvRegisterSint13             = 0x000A000D,
    HvRegisterSint14             = 0x000A000E,
    HvRegisterSint15             = 0x000A000F,
    HvRegisterScontrol           = 0x000A0010,
    HvRegisterSversion           = 0x000A0011,
    HvRegisterSifp               = 0x000A0012,
    HvRegisterSipp               = 0x000A0013,
    HvRegisterEom                = 0x000A0014,
    HvRegisterSirbp              = 0x000A0015,

    // Hypervisor-defined MSRs (Nested Synic)
    HvRegisterNestedSint0        = 0x000A1000,
    HvRegisterNestedSint1        = 0x000A1001,
    HvRegisterNestedSint2        = 0x000A1002,
    HvRegisterNestedSint3        = 0x000A1003,
    HvRegisterNestedSint4        = 0x000A1004,
    HvRegisterNestedSint5        = 0x000A1005,
    HvRegisterNestedSint6        = 0x000A1006,
    HvRegisterNestedSint7        = 0x000A1007,
    HvRegisterNestedSint8        = 0x000A1008,
    HvRegisterNestedSint9        = 0x000A1009,
    HvRegisterNestedSint10       = 0x000A100a,
    HvRegisterNestedSint11       = 0x000A100b,
    HvRegisterNestedSint12       = 0x000A100c,
    HvRegisterNestedSint13       = 0x000A100d,
    HvRegisterNestedSint14       = 0x000A100e,
    HvRegisterNestedSint15       = 0x000A100f,
    HvRegisterNestedScontrol     = 0x000A1010,
    HvRegisterNestedSversion     = 0x000A1011,
    HvRegisterNestedSifp         = 0x000A1012,
    HvRegisterNestedSipp         = 0x000A1013,
    HvRegisterNestedEom          = 0x000A1014,
    HvRegisterNestedSirbp        = 0x000A1015,

    // Hypervisor-defined MSRs (Synthetic Timers)
    HvRegisterStimer0Config      = 0x000B0000,
    HvRegisterStimer0Count       = 0x000B0001,
    HvRegisterStimer1Config      = 0x000B0002,
    HvRegisterStimer1Count       = 0x000B0003,
    HvRegisterStimer2Config      = 0x000B0004,
    HvRegisterStimer2Count       = 0x000B0005,
    HvRegisterStimer3Config      = 0x000B0006,
    HvRegisterStimer3Count       = 0x000B0007,

    // Hypervisor-defined MSRs (Synthetic Time)
    HvRegisterStimeUnhaltedTimerConfig  = 0x000B0100,
    HvRegisterStimeUnhaltedTimerCount   = 0x000B0101,

    //
    // XSAVE/XRSTOR register names.
    //

    // XSAVE AFX extended state registers. YMM registers are 256-bit.
    // However, only 128-bit access is currently supported.
    // N.B. The lower 128-bits of YMM registers are overlyaid with
    // the cooresponding XMM register.
    HvX64RegisterYmm0Low             = 0x000C0000,
    HvX64RegisterYmm1Low             = 0x000C0001,
    HvX64RegisterYmm2Low             = 0x000C0002,
    HvX64RegisterYmm3Low             = 0x000C0003,
    HvX64RegisterYmm4Low             = 0x000C0004,
    HvX64RegisterYmm5Low             = 0x000C0005,
    HvX64RegisterYmm6Low             = 0x000C0006,
    HvX64RegisterYmm7Low             = 0x000C0007,
    HvX64RegisterYmm8Low             = 0x000C0008,
    HvX64RegisterYmm9Low             = 0x000C0009,
    HvX64RegisterYmm10Low            = 0x000C000A,
    HvX64RegisterYmm11Low            = 0x000C000B,
    HvX64RegisterYmm12Low            = 0x000C000C,
    HvX64RegisterYmm13Low            = 0x000C000D,
    HvX64RegisterYmm14Low            = 0x000C000E,
    HvX64RegisterYmm15Low            = 0x000C000F,
    HvX64RegisterYmm0High            = 0x000C0010,
    HvX64RegisterYmm1High            = 0x000C0011,
    HvX64RegisterYmm2High            = 0x000C0012,
    HvX64RegisterYmm3High            = 0x000C0013,
    HvX64RegisterYmm4High            = 0x000C0014,
    HvX64RegisterYmm5High            = 0x000C0015,
    HvX64RegisterYmm6High            = 0x000C0016,
    HvX64RegisterYmm7High            = 0x000C0017,
    HvX64RegisterYmm8High            = 0x000C0018,
    HvX64RegisterYmm9High            = 0x000C0019,
    HvX64RegisterYmm10High           = 0x000C001A,
    HvX64RegisterYmm11High           = 0x000C001B,
    HvX64RegisterYmm12High           = 0x000C001C,
    HvX64RegisterYmm13High           = 0x000C001D,
    HvX64RegisterYmm14High           = 0x000C001E,
    HvX64RegisterYmm15High           = 0x000C001F,

    // Synthetic VSM registers
    HvRegisterVsmVpVtlControl           = 0x000D0000,
    HvRegisterVsmCodePageOffsets        = 0x000D0002,
    HvRegisterVsmVpStatus               = 0x000D0003,
    HvRegisterVsmPartitionStatus        = 0x000D0004,
    HvRegisterVsmVina                   = 0x000D0005,
    HvRegisterVsmCapabilities           = 0x000D0006,
    HvRegisterVsmPartitionConfig        = 0x000D0007,
    HvRegisterVsmVpSecureConfigVtl0     = 0x000D0010,
    HvRegisterVsmVpSecureConfigVtl1     = 0x000D0011,
    HvRegisterVsmVpSecureConfigVtl2     = 0x000D0012,
    HvRegisterVsmVpSecureConfigVtl3     = 0x000D0013,
    HvRegisterVsmVpSecureConfigVtl4     = 0x000D0014,
    HvRegisterVsmVpSecureConfigVtl5     = 0x000D0015,
    HvRegisterVsmVpSecureConfigVtl6     = 0x000D0016,
    HvRegisterVsmVpSecureConfigVtl7     = 0x000D0017,
    HvRegisterVsmVpSecureConfigVtl8     = 0x000D0018,
    HvRegisterVsmVpSecureConfigVtl9     = 0x000D0019,
    HvRegisterVsmVpSecureConfigVtl10    = 0x000D001A,
    HvRegisterVsmVpSecureConfigVtl11    = 0x000D001B,
    HvRegisterVsmVpSecureConfigVtl12    = 0x000D001C,
    HvRegisterVsmVpSecureConfigVtl13    = 0x000D001D,
    HvRegisterVsmVpSecureConfigVtl14    = 0x000D001E,
    HvRegisterVsmVpWaitForTlbLock       = 0x000D0020,

    // VM Isolation
    HvRegisterIsolationCapabilities = 0x000D0100,

    // 15.13.4.1 Mask Registers
    HvX64RegisterCrInterceptControl             = 0x000E0000,
    HvX64RegisterCrInterceptCr0Mask             = 0x000E0001,
    HvX64RegisterCrInterceptCr4Mask             = 0x000E0002,
    HvX64RegisterCrInterceptIa32MiscEnableMask  = 0x000E0003,

} HV_REGISTER_NAME, *PHV_REGISTER_NAME;
typedef const HV_REGISTER_NAME *PCHV_REGISTER_NAME;

//
// Definiton of the HvCallGetVpRegister hypercall input structure.
// This call retrieves a Vp's register state.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_REGISTERS
{
    HV_PARTITION_ID     PartitionId;
    HV_VP_INDEX         VpIndex;
    HV_INPUT_VTL        InputVtl;
    HV_REGISTER_NAME    Names[];
} HV_INPUT_GET_VP_REGISTERS, *PHV_INPUT_GET_VP_REGISTERS;

typedef struct _HV_REGISTER_ASSOC
{
    HV_REGISTER_NAME    Name;
    unsigned long              Pad;
    HV_REGISTER_VALUE   Value;
} HV_REGISTER_ASSOC, *PHV_REGISTER_ASSOC;

typedef struct HV_CALL_ATTRIBUTES_ALIGNED(16) _HV_INPUT_SET_VP_REGISTERS
{
    HV_PARTITION_ID     PartitionId;
    HV_VP_INDEX         VpIndex;
    HV_INPUT_VTL        InputVtl;
    HV_REGISTER_ASSOC   Elements[];
} HV_INPUT_SET_VP_REGISTERS, *PHV_INPUT_SET_VP_REGISTERS;

//
// Definition of the HvCallGetVpRegisterCode hypercall input
// structure.  This call retrieves the valid Vp register codes.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_REGISTER_CODE
{
    HV_PARTITION_ID PartitionId;
    unsigned long          RegisterIndex;
} HV_INPUT_GET_VP_REGISTER_CODE, *PHV_INPUT_GET_VP_REGISTER_CODE;


//
// Definition of the HvCallSwitchVirtualAddressSpace hypercall input
// structure.  This call switches the guest's virtual address space.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SWITCH_VIRTUAL_ADDRESS_SPACE
{
    HV_ADDRESS_SPACE_ID AddressSpace;
} HV_INPUT_SWITCH_VIRTUAL_ADDRESS_SPACE,
  *PHV_INPUT_SWITCH_VIRTUAL_ADDRESS_SPACE;


//
// Common header used by both list and space flush routines.
//

typedef struct _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER
{
    HV_ADDRESS_SPACE_ID AddressSpace;
    HV_FLUSH_FLAGS      Flags;
    unsigned long long              ProcessorMask;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER,
  *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER;

//
// Definition of the HvCallFlushVirtualAddressSpace hypercall input
// structure.  This call flushes the virtual TLB entries which belong
// to the indicated address space, on one or more processors.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE
{
    HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER Header;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE;

//
// Definition of the HvCallFlushVirtualAddressList hypercall input
// structure.  This call invalidates portions of the virtual TLB which
// belong to the indicates address space, on one more more processors.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST
{
    HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER Header;
    HV_GVA GvaList[];
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST;

//
// Definition of the HvAssertVirtualInterrupt hypercall input
// structure.  This call asserts an interrupt in a guest partition.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ASSERT_VIRTUAL_INTERRUPT
{
    HV_PARTITION_ID         TargetPartition;
    HV_INTERRUPT_CONTROL    InterruptControl;
    unsigned long long                  DestinationAddress;
    HV_INTERRUPT_VECTOR     RequestedVector;
    unsigned long                  Reserved;
} HV_INPUT_ASSERT_VIRTUAL_INTERRUPT, *PHV_INPUT_ASSERT_VIRTUAL_INTERRUPT;

//
// Definition of the HvClearVirtualInterrupt hypercall input
// structure. This call clears the acknowledged status of a previously
// acknowledged vector.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CLEAR_VIRTUAL_INTERRUPT
{
    HV_PARTITION_ID         TargetPartition;
} HV_INPUT_CLEAR_VIRTUAL_INTERRUPT, *PHV_INPUT_CLEAR_VIRTUAL_INTERRUPT;

//
// Definition of the HvCreatePort hypercall input structure.  This
// call allocates a port object.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PORT
{
    HV_PARTITION_ID     PortPartition;
    HV_PORT_ID          PortId;
    unsigned long              Padding;
    HV_PARTITION_ID     ConnectionPartition;
    HV_PORT_INFO        PortInfo;
} HV_INPUT_CREATE_PORT, *PHV_INPUT_CREATE_PORT;

//
// Definition of the HvDeletePort hypercall input structure.  This
// call deletes a port object.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PORT
{
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID      PortId;
    unsigned long          Reserved;
} HV_INPUT_DELETE_PORT, *PHV_INPUT_DELETE_PORT;

//
// Definition of the HvConnectPort hypercall input structure.  This
// call creates a connection to a previously-created port in another
// partition.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CONNECT_PORT
{
    HV_PARTITION_ID     ConnectionPartition;
    HV_CONNECTION_ID    ConnectionId;
    unsigned long              Reserved1;
    HV_PARTITION_ID     PortPartition;
    HV_PORT_ID          PortId;
    unsigned long              Reserved2;
    HV_CONNECTION_INFO  ConnectionInfo;
} HV_INPUT_CONNECT_PORT, *PHV_INPUT_CONNECT_PORT;

//
// Definition of the HvGetPortProperty hypercall input and output
// structures.  This call retrieves a property of a previously-created
// port in the current or another partition.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PORT_PROPERTY
{
    HV_PARTITION_ID       PortPartition;
    HV_PORT_ID            PortId;
    unsigned long                Reserved;
    HV_PORT_PROPERTY_CODE PropertyCode;
} HV_INPUT_GET_PORT_PROPERTY, *PHV_INPUT_GET_PORT_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PORT_PROPERTY
{
    HV_PORT_PROPERTY PropertyValue;
} HV_OUTPUT_GET_PORT_PROPERTY, *PHV_OUTPUT_GET_PORT_PROPERTY;

//
// Definition of the HvDisconnectPort hypercall input structure.  This
// call disconnects an existing connection.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISCONNECT_PORT
{
    HV_PARTITION_ID     ConnectionPartition;
    HV_CONNECTION_ID    ConnectionId;
    unsigned long              Reserved;
} HV_INPUT_DISCONNECT_PORT, *PHV_INPUT_DISCONNECT_PORT;

//
// Definition of the HvPostMessage hypercall input structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_POST_MESSAGE
{
    HV_CONNECTION_ID    ConnectionId;
    unsigned long              Reserved;
    HV_MESSAGE_TYPE     MessageType;
    unsigned long              PayloadSize;
    unsigned long long              Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
} HV_INPUT_POST_MESSAGE, *PHV_INPUT_POST_MESSAGE;


//
// Definition of the HvSignalEvent hypercall input structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SIGNAL_EVENT
{
    HV_CONNECTION_ID ConnectionId;
    unsigned short           FlagNumber;
    unsigned short           RsvdZ;
} HV_INPUT_SIGNAL_EVENT, *PHV_INPUT_SIGNAL_EVENT;

//
// Define the scheduler run time hypercall input/output structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME
{
    HV_NANO100_TIME GlobalTime;
    HV_NANO100_TIME LocalRunTime;
    unsigned long long          RsvdZ;
    HV_NANO100_TIME HypervisorTime;
} HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME,
  *PHV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME;

//
// Definition of the HvSavePartitionState hypercall input and output
// structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SAVE_PARTITION_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_SAVE_RESTORE_STATE_FLAGS Flags;
} HV_INPUT_SAVE_PARTITION_STATE, *PHV_INPUT_SAVE_PARTITION_STATE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_SAVE_PARTITION_STATE
{
    unsigned long SaveDataCount;
    HV_SAVE_RESTORE_STATE_RESULT SaveState;
    unsigned char SaveData[4080];
} HV_OUTPUT_SAVE_PARTITION_STATE, *PHV_OUTPUT_SAVE_PARTITION_STATE;

//
// Definition of the HvRestorePartitionState hypercall input and
// output structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESTORE_PARTITION_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_SAVE_RESTORE_STATE_FLAGS Flags;
    unsigned long RestoreDataCount;
    unsigned char RestoreData[4080];
} HV_INPUT_RESTORE_PARTITION_STATE, *PHV_INPUT_RESTORE_PARTITION_STATE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RESTORE_PARTITION_STATE
{
    HV_SAVE_RESTORE_STATE_RESULT RestoreState;
    unsigned long RestoreDataConsumed;
} HV_OUTPUT_RESTORE_PARTITION_STATE, *PHV_OUTPUT_RESTORE_PARTITION_STATE;

//
// Flags used for specifying the stats object when making mapping/unmapping
// stats page hypercall.
//

typedef unsigned short HV_STATS_OBJECT_FLAG;

#define HvStatsObjectSelfStats      0x0001

//
// Definitions for the stats hypercall structures.
//

typedef union _HV_STATS_OBJECT_IDENTITY
{
    //
    // HvStatsObjectHypervisor
    //

    struct
    {
        unsigned long long  ReservedZ0;
        unsigned long  ReservedZ1;
        unsigned short  ReservedZ2;
        unsigned char   ReservedZ3;
        unsigned char   ReservedZ4;
    } Hypervisor;

    //
    // HvStatsObjectLogicalProcessor
    //

    struct
    {
        HV_LOGICAL_PROCESSOR_INDEX      LogicalProcessorIndex;
        unsigned long                          ReservedZ0;
        unsigned long                          ReservedZ1;
        unsigned short                          ReservedZ2;
        unsigned char                           ReservedZ3;
        unsigned char                           ReservedZ4;
    } LogicalProcessor;

    //
    // HvStatsObjectPartition
    //

    struct
    {
        HV_PARTITION_ID         PartitionId;
        unsigned long                  ReservedZ1;
        HV_STATS_OBJECT_FLAG    Flags;
        unsigned char                   ReservedZ3;
        unsigned char                   ReservedZ4;
    } Partition;

    //
    // HvStatsObjectVp
    //

    struct
    {
        HV_PARTITION_ID         PartitionId;
        HV_VP_INDEX             VpIndex;
        HV_STATS_OBJECT_FLAG    Flags;
        unsigned char                   ReservedZ3;
        unsigned char                   ReservedZ4;
    } Vp;

} HV_STATS_OBJECT_IDENTITY, *PHV_STATS_OBJECT_IDENTITY;


typedef const HV_STATS_OBJECT_IDENTITY *PCHV_STATS_OBJECT_IDENTITY;

//
// Definition of the HvMapStatsPage hypercall input structure.  This
// call allows a partition to map the page with statistics into
// the caller's GPA space.for child partition or for itself.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_STATS_PAGE
{
    HV_STATS_OBJECT_TYPE       StatsType;
    HV_STATS_OBJECT_IDENTITY   ObjectIdentity;
    HV_GPA_PAGE_NUMBER         MapLocation;
} HV_INPUT_MAP_STATS_PAGE, *PHV_INPUT_MAP_STATS_PAGE;


//
// Definition of the HvUnmapStatsPage hypercall input structure.  This
// call allows a partition to unmap the page with statistics from
// the caller's GPA space.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_STATS_PAGE
{
    HV_STATS_OBJECT_TYPE       StatsType;
    HV_STATS_OBJECT_IDENTITY   ObjectIdentity;
    HV_GPA_PAGE_NUMBER         MapLocation;
} HV_INPUT_UNMAP_STATS_PAGE, *PHV_INPUT_UNMAP_STATS_PAGE;

//
// Definition of the HcpHvNotifySpinlockAcquireFailure hypercall input
// structure.  This call switches notifies the hypervisor of a long running
// spinlock acquisition failure.
//
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_NOTIFY_LONG_SPINWAIT
{
    unsigned long long InitialLongSpinWait;
} HV_INPUT_NOTIFY_LONG_SPINWAIT,
  *PHV_INPUT_NOTIFY_LONG_SPINWAIT;

//
// Definition of the HcpHvParkLogicalProcessors hypercall input structure.
// This call notifies the hypervisor of the set of logical processors that
// the root partition decides to park.
//
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PARK_LOGICAL_PROCESSORS
{
    unsigned long long ProcessorMask;
} HV_INPUT_PARK_LOGICAL_PROCESSORS, *PHV_INPUT_PARK_LOGICAL_PROCESSORS;

//
// Definition of the HcpHvSetSystemProperty hypercall input structure.
// This call sets a generic system wide property. 
//

typedef enum _HV_SYSTEM_PROPERTY
{
    HvSetPerfCounterProperty = 1,
    
    HvSystemPropertyMax = 2

} HV_SYSTEM_PROPERTY, *PHV_SYSTEM_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_SYSTEM_PROPERTY
{
    unsigned long PropertyId;
    union 
    {
        struct 
        {
            unsigned short EventType;
            unsigned short ReservedZ1;
            unsigned long ReservedZ2;
            unsigned long long Period;  
        } SetPerfCounter;
    } Property;

} HV_INPUT_SET_SYSTEM_PROPERTY, *PHV_INPUT_SET_SYSTEM_PROPERTY;

//
// Chapter 15 -- Virtual Secure Mode
//

// 15.2 Virtual Trust Levels (VTL)
#define HV_NUM_VTLS 2
#define HV_INVALID_VTL ((HV_VTL) -1)
#define HV_VTL_ALL 0xF

// 15.3.2.1 HvRegisterVsmPartitionStatus
typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long EnabledVtlSet        : 16;
        unsigned long long MaximumVtl           : 4;
        unsigned long long MbecEnabledVtlSet    : 16;
        unsigned long long ReservedZ            : 28;
    };
} HV_REGISTER_VSM_PARTITION_STATUS;

// 15.3.2.2 HvRegisterVsmVpStatus
typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long ActiveVtl            : 4;
        unsigned long long ActiveMbecEnabled    : 1;
        unsigned long long ReservedZ0           : 11;
        unsigned long long EnabledVtlSet        : 16;
        unsigned long long ReservedZ1           : 32;
    };
} HV_REGISTER_VSM_VP_STATUS;

// 15.5.1 Partition Configuration
typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long EnableVtlProtection          : 1;
        unsigned long long DefaultVtlProtectionMask     : 4;
        unsigned long long ZeroMemoryOnReset            : 1;
        unsigned long long DenyLowerVtlStartup          : 1;
        unsigned long long InterceptAcceptance          : 1;
        unsigned long long InterceptEnableVtlProtection : 1;
        unsigned long long InterceptVpStartup           : 1;
        unsigned long long InterceptCpuidUnimplemented  : 1;
        unsigned long long ReservedZ                    : 53;
    };
} HV_REGISTER_VSM_PARTITION_CONFIG;

// 15.5.2 Configuring Lower VTLs
typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long MbecEnabled      : 1;
        unsigned long long TlbLocked        : 1;
        unsigned long long ReservedZ        : 62;
    };
} HV_REGISTER_VSM_VP_SECURE_VTL_CONFIG;

// 15.6.1.2 Identifying VTL Entry Reason
typedef enum
{
    // This reason is reserved and is not used.
    HvVtlEntryReserved = 0,

    // Indicates entry due to a VTL call from a lower VTL.
    HvVtlEntryVtlCall = 1,

    // Indicates entry due to an interrupt targeted to the VTL.
    HvVtlEntryInterrupt = 2
} HV_VTL_ENTRY_REASON;

// 15.8 Hypercall Page Assists
typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long VtlCallOffset    : 12;
        unsigned long long VtlReturnOffset  : 12;
        unsigned long long ReservedZ        : 40;
    };
} HV_REGISTER_VSM_CODE_PAGE_OFFSETS;

// 15.8.2 Definition
typedef struct
{
    // The hypervisor updates the entry reason with an indication as to why
    // the VTL was entered on the virtual processor.
    HV_VTL_ENTRY_REASON     EntryReason;

    // This flag determines whether the VINA interrupt line is asserted.
    union
    {
        unsigned char               AsUINT8;
        struct
        {
            unsigned char           VinaAsserted    : 1;
            unsigned char           VinaReservedZ   : 7;
        };
    } VinaStatus;

    unsigned char                   ReservedZ00;
    unsigned short                  ReservedZ01;

    // A guest updates the VtlReturn* fields to provide the register values
    // to restore on VTL return. The specific register values that are
    // restored will vary based on whether the VTL is 32-bit or 64-bit.

    union
    {
        struct
        {
            unsigned long long          VtlReturnX64Rax;
            unsigned long long          VtlReturnX64Rcx;
        };
        struct
        {
            unsigned long          VtlReturnX86Eax;
            unsigned long          VtlReturnX86Ecx;
            unsigned long          VtlReturnX86Edx;
            unsigned long          ReservedZ1;
        };
    };

} HV_VP_VTL_CONTROL;

// 15.13.4 Secure Register Intercepts

typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Cr0Write                 : 1; // 0x0000000000000001
        unsigned long long Cr4Write                 : 1; // 0x0000000000000002
        unsigned long long XCr0Write                : 1; // 0x0000000000000004
        unsigned long long IA32MiscEnableRead       : 1; // 0x0000000000000008
        unsigned long long IA32MiscEnableWrite      : 1; // 0x0000000000000010
        unsigned long long MsrLstarRead             : 1; // 0x0000000000000020
        unsigned long long MsrLstarWrite            : 1; // 0x0000000000000040
        unsigned long long MsrStarRead              : 1; // 0x0000000000000080
        unsigned long long MsrStarWrite             : 1; // 0x0000000000000100
        unsigned long long MsrCstarRead             : 1; // 0x0000000000000200
        unsigned long long MsrCstarWrite            : 1; // 0x0000000000000400
        unsigned long long ApicBaseMsrRead          : 1; // 0x0000000000000800
        unsigned long long ApicBaseMsrWrite         : 1; // 0x0000000000001000
        unsigned long long MsrEferRead              : 1; // 0x0000000000002000
        unsigned long long MsrEferWrite             : 1; // 0x0000000000004000
        unsigned long long GdtrWrite                : 1; // 0x0000000000008000
        unsigned long long IdtrWrite                : 1; // 0x0000000000010000
        unsigned long long LdtrWrite                : 1; // 0x0000000000020000
        unsigned long long TrWrite                  : 1; // 0x0000000000040000
        unsigned long long MsrSysenterCsWrite       : 1; // 0x0000000000080000
        unsigned long long MsrSysenterEipWrite      : 1; // 0x0000000000100000
        unsigned long long MsrSysenterEspWrite      : 1; // 0x0000000000200000
        unsigned long long MsrSfmaskWrite           : 1; // 0x0000000000400000
        unsigned long long MsrTscAuxWrite           : 1; // 0x0000000000800000
        unsigned long long MsrSgxLaunchControlWrite : 1; // 0x0000000001000000
        unsigned long long RsvdZ                    : 39;
    };
} HV_REGISTER_CR_INTERCEPT_CONTROL;

// 15.12.4 Virtual Interrupt Notification Assist
typedef union
{
    unsigned long long AsUINT64;
    struct
    {
        unsigned long long Vector : 8;
        unsigned long long Enabled : 1;
        unsigned long long AutoReset : 1;
        unsigned long long AutoEoi : 1;
        unsigned long long ReservedP : 53;
    };
} HV_REGISTER_VSM_VINA;


#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4200)
#pragma warning(default:4201)
#pragma warning(default:4214)
#pragma warning(default:4324)
#endif

#endif //_HVGDK_
