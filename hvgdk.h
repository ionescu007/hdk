/*++

Copyright (c) Microsoft Corporation

Module Name:

    HvGdk.h

Abstract:

    Type definitions for the hypervisor guest interface.

Author:

    Hypervisor Engineering Team (hvet) 01-May-2005

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


//
// Define a 128bit type.
//
typedef struct DECLSPEC_ALIGN(16) _HV_UINT128 {

    UINT64  Low64;
    UINT64  High64;

} HV_UINT128, *PHV_UINT128;


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

typedef UINT64 HV_SPA, *PHV_SPA;
typedef UINT64 HV_GPA, *PHV_GPA;
typedef UINT64 HV_GVA, *PHV_GVA;

#define HV_X64_PAGE_SIZE (4096)
#define HV_PAGE_SIZE HV_X64_PAGE_SIZE

typedef UINT64 HV_SPA_PAGE_NUMBER, *PHV_SPA_PAGE_NUMBER;
typedef UINT64 HV_GPA_PAGE_NUMBER, *PHV_GPA_PAGE_NUMBER;
typedef UINT64 HV_GVA_PAGE_NUMBER, *PHV_GVA_PAGE_NUMBER;

typedef const HV_SPA_PAGE_NUMBER *PCHV_SPA_PAGE_NUMBER;
typedef const HV_GPA_PAGE_NUMBER *PCHV_GPA_PAGE_NUMBER;
typedef const HV_GVA_PAGE_NUMBER *PCHV_GVA_PAGE_NUMBER;

//
// Forward declare the loader block.
//
typedef struct _HV_LOADER_BLOCK *PHV_LOADER_BLOCK;
//
// Status codes for hypervisor operations.
//
typedef UINT16 HV_STATUS, *PHV_STATUS;

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
// The specified hypercall code is not supported.
//
#define HV_STATUS_INVALID_HYPERCALL_CODE ((HV_STATUS)0x0002)

//
// MessageId: HV_STATUS_INVALID_HYPERCALL_INPUT
//
// MessageText:
//
// The encoding for the hypercall input register was not supported.
//
#define HV_STATUS_INVALID_HYPERCALL_INPUT ((HV_STATUS)0x0003)

//
// MessageId: HV_STATUS_INVALID_ALIGNMENT
//
// MessageText:
//
// The operation cannot proceed as a parameter has an invalid alignment.
//
#define HV_STATUS_INVALID_ALIGNMENT      ((HV_STATUS)0x0004)

//
// MessageId: HV_STATUS_INVALID_PARAMETER
//
// MessageText:
//
// An invalid parameter was specified.
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
// The operation cannot proceed as the partition is entering or in an invalid state.
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
// The specified partition property is not recognized.
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
// There is not enough memory in the hypervisor pool to complete the call.
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
// The specified VP index is invalid.
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
// The port identifier is invalid.
//
#define HV_STATUS_INVALID_PORT_ID        ((HV_STATUS)0x0011)

//
// MessageId: HV_STATUS_INVALID_CONNECTION_ID
//
// MessageText:
//
// The connection identifier is invalid.
//
#define HV_STATUS_INVALID_CONNECTION_ID  ((HV_STATUS)0x0012)

//
// MessageId: HV_STATUS_INSUFFICIENT_BUFFERS
//
// MessageText:
//
// The caller does not have enough message buffers to send a message.
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
// The operation could not be completed because a required feature of the SynIC was disabled.
//
#define HV_STATUS_INVALID_SYNIC_STATE    ((HV_STATUS)0x0018)

//
// MessageId: HV_STATUS_OBJECT_IN_USE
//
// MessageText:
//
// The operation could not be performed because the object or value was either already in use or being used for a purpose that would not permit it.
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
// A hypervisor feature is not available to the caller.
//
#define HV_STATUS_FEATURE_UNAVAILABLE    ((HV_STATUS)0x001E)

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
// An architecture is a set of processor instruction sets and operating modes
//

typedef enum _HV_ARCHITECTURE
{
    HvArchitectureX64,
    HvArchitectureX86,
    HvArchitectureMaximum
} HV_ARCHITECTURE, *PHV_ARCHITECTURE;

typedef union _HV_X64_FP_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        UINT64 Mantissa;
        UINT64 BiasedExponent:15;
        UINT64 Sign:1;
        UINT64 Reserved:48;
    };
} HV_X64_FP_REGISTER, *PHV_X64_FP_REGISTER;

typedef union _HV_X64_FP_CONTROL_STATUS_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        UINT16 FpControl;
        UINT16 FpStatus;
        UINT8  FpTag;
        UINT8  IgnNe:1;
        UINT8  Reserved:7;
        UINT16 LastFpOp;
        union
        {
            // Long Mode
            UINT64 LastFpRip;
            // 32 Bit Mode
            struct
            {
                UINT32 LastFpEip;
                UINT16 LastFpCs;
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
            UINT64 LaftFpRdp;
            // 32 Bit Mode
            struct
            {
                UINT32 LastFpDp;
                UINT16 LastFpDs;
            };
        };
        UINT32 XmmStatusControl;
        UINT32 XmmStatusControlMask;
    };
} HV_X64_XMM_CONTROL_STATUS_REGISTER, *PHV_X64_XMM_CONTROL_STATUS_REGISTER;

typedef struct _HV_X64_SEGMENT_REGISTER
{
    UINT64 Base;
    UINT32 Limit;
    UINT16 Selector;
    union
    {
        struct
        {
            UINT16 SegmentType:4;
            UINT16 NonSystemSegment:1;
            UINT16 DescriptorPrivilegeLevel:2;
            UINT16 Present:1;
            UINT16 Reserved:4;
            UINT16 Available:1;
            UINT16 Long:1;
            UINT16 Default:1;
            UINT16 Granularity:1;
        };
        UINT16 Attributes;
    };

} HV_X64_SEGMENT_REGISTER, *PHV_X64_SEGMENT_REGISTER;

typedef struct _HV_X64_TABLE_REGISTER
{
    UINT16     Pad[3];
    UINT16     Limit;
    UINT64     Base;
} HV_X64_TABLE_REGISTER, *PHV_X64_TABLE_REGISTER;

typedef union _HV_X64_FP_MMX_REGISTER
{
    HV_UINT128          AsUINT128;
    HV_X64_FP_REGISTER  Fp;
    UINT64              Mmx;
} HV_X64_FP_MMX_REGISTER, *PHV_X64_FP_MMX_REGISTER;

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
    UINT8 FxSaveArea[512];

} HV_X64_FX_REGISTERS, *PHV_X64_FX_REGISTERS;

typedef struct _HV_X64_CONTEXT
{

    //
    // The Initial APIC ID pseudo register. This is the value returned
    // by CPUID.
    //
    UINT64 InitialApicId;

    //
    // 16 64 bit general purpose registers, instruction pointer and
    // flags
    //

    UINT64 Rax;
    UINT64 Rbx;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rsi;
    UINT64 Rdi;
    UINT64 Rbp;
    UINT64 Rsp;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;

    UINT64 Rip;
    UINT64 Rflags;

    //
    // Control Registers - on 32 bit platforms the upper 32 bits are
    // ignored. Efer is actually an Msr but it acts as an extension to
    // Cr4 and as such is treated as a processor register. Cr8 is only
    // valid on 64 bit systems.
    //

    UINT64 Cr0;
    UINT64 Cr2;
    UINT64 Cr3;
    UINT64 Cr4;
    UINT64 Cr8;
    UINT64 Efer;

    //
    // Debug Registers - on 32 bit platforms the upper 32 bits are
    // ignored
    //

    UINT64 Dr0;
    UINT64 Dr1;
    UINT64 Dr2;
    UINT64 Dr3;
    UINT64 Dr6;
    UINT64 Dr7;

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

    UINT64 KernelGsBase;
    UINT64 Star;
    UINT64 Lstar;
    UINT64 Cstar;
    UINT64 Sfmask;
    UINT64 SysenterCs;
    UINT64 SysenterEip;
    UINT64 SysenterEsp;

    UINT64 MsrCrPat;

    //
    // Local APIC state.
    //

    UINT32 LocalApicId;
    UINT32 LocalApicVersion;
    UINT32 LocalApicLdr;
    UINT32 LocalApicDfr;
    UINT32 LocalApicSpurious;
    UINT32 LocalApicIcrLow;
    UINT32 LocalApicIcrHigh;
    UINT32 LocalApicIsr[8];
    UINT32 LocalApicTmr[8];
    UINT32 LocalApicLvtTimer;
    UINT32 LocalApicLvtPerfmon;
    UINT32 LocalApicLvtLint0;
    UINT32 LocalApicLvtLint1;
    UINT32 LocalApicCurrentCount;
    UINT32 LocalApicInitialCount;
    UINT32 LocalApicDivider;
    UINT64 LocalApicBaseMsr;

    //
    // x87 Floating point, MMX and XMM registers formatted as by
    // fxsave/fxrstor
    //

    HV_X64_FX_REGISTERS FxRegisters;

} HV_X64_CONTEXT, *PHV_X64_CONTEXT;

#define HV_VIRTUAL_PROCESSOR_REGISTERS_VERSION 1

typedef struct _HV_VP_CONTEXT
{
    //
    // The version of the HV_VP_CONTEXT structure
    //

    UINT32 Version;

    //
    // The architecture of these registers
    //

    HV_ARCHITECTURE Architecture;

    union
    {
        HV_X64_CONTEXT x64;
    };

} HV_VP_CONTEXT, *PHV_VP_CONTEXT;

typedef UINT16  HV_STATISTICS_GROUP_TYPE;
typedef UINT16  HV_STATISTICS_GROUP_LENGTH;

typedef struct _HV_STATISTICS_GROUP_VERSION
{
    UINT16    Minor;
    UINT16    Major;

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
    ((HV_PAGE_SIZE - 2 * sizeof(HV_STATISTICS_GROUP_HEADER)) / sizeof(UINT64))

//
// Definition of the counters structure.
//

typedef struct _HV_STATS_PAGE
{
    UINT64      Data[HV_PAGE_SIZE / sizeof(UINT64)];

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
// Namespace definition helper macros.
//

#define ST_DECLARE_HV_COUNTER(x,id)     StHvCounter##x = id,
#define ST_DECLARE_LP_COUNTER(x,id)     StLpCounter##x = id,
#define ST_DECLARE_PT_COUNTER(x,id)     StPtCounter##x = id,
#define ST_DECLARE_VP_COUNTER(x,id)     StVpCounter##x = id,

//
// Conversion macros: from "human" to prefixed index names.
//

#define ST_HV_COUNTER_NAME(x)           StHvCounter##x
#define ST_LP_COUNTER_NAME(x)           StLpCounter##x
#define ST_PT_COUNTER_NAME(x)           StPtCounter##x
#define ST_VP_COUNTER_NAME(x)           StVpCounter##x

//
// Hypervisor global counter set
//
typedef enum _HV_HYPERVISOR_COUNTER 
{

    ST_DECLARE_HV_COUNTER(LogicalProcessors, 1)
    ST_DECLARE_HV_COUNTER(Partitions, 2)

    ST_HV_COUNTER_NAME(MAXIMUM)

} HV_HYPERVISOR_COUNTER;

#define HV_STATISTICS_GROUP_HVA_LENGTH 16
#define HV_STATISTICS_GROUP_HVV_LENGTH 0

//
// Hypervisor Logical Processor counter set
//
typedef enum _HV_CPU_COUNTER 
{

    ST_DECLARE_LP_COUNTER(TotalTime, 1)
    ST_DECLARE_LP_COUNTER(HypervisorTime, 2)
    ST_DECLARE_LP_COUNTER(HardwareInterrupts, 3)
    ST_DECLARE_LP_COUNTER(ContextSwitches, 4)

    ST_LP_COUNTER_NAME(MAXIMUM)

} HV_CPU_COUNTER;

#define HV_STATISTICS_GROUP_LPA_LENGTH 32
#define HV_STATISTICS_GROUP_LPV_LENGTH 0

//
// Partition counter set
//
typedef enum _HV_PROCESS_COUNTER 
{

    ST_DECLARE_PT_COUNTER(VirtualProcessors, 1)
    ST_DECLARE_PT_COUNTER(MappedGpaPages, 2)

    ST_DECLARE_PT_COUNTER(PageTables, 4)
    ST_DECLARE_PT_COUNTER(AddressSpaces, 5)
    ST_DECLARE_PT_COUNTER(PagesDeposited, 6)
    ST_PT_COUNTER_NAME(MAXIMUM)

} HV_PROCESS_COUNTER;

#define HV_STATISTICS_GROUP_PTA_LENGTH 16
#define HV_STATISTICS_GROUP_PTV_LENGTH 24

//
// Hypervisor Virtual Processor counter set
//
typedef enum _HV_THREAD_COUNTER 
{

    ST_DECLARE_VP_COUNTER(RunTime, 1)
    ST_DECLARE_VP_COUNTER(Intercepts, 2)
    ST_DECLARE_VP_COUNTER(InterceptsTime, 3)
    ST_DECLARE_VP_COUNTER(HypervisorRunTime, 4)

    ST_DECLARE_VP_COUNTER(GuestExceptions, 6)
    ST_DECLARE_VP_COUNTER(GuestExceptionsTime, 7)
    ST_DECLARE_VP_COUNTER(Hypercalls, 8)
    ST_DECLARE_VP_COUNTER(HypercallsTime, 9)
    ST_DECLARE_VP_COUNTER(PageInvalidations, 10)
    ST_DECLARE_VP_COUNTER(PageInvalidationsTime, 11)
    ST_DECLARE_VP_COUNTER(CrAccesses, 12)
    ST_DECLARE_VP_COUNTER(CrAccessesTime, 13)
    ST_DECLARE_VP_COUNTER(IoInstructions, 14)
    ST_DECLARE_VP_COUNTER(IoInstructionsTime, 15)
    ST_DECLARE_VP_COUNTER(HaltInstructions, 16)
    ST_DECLARE_VP_COUNTER(HaltInstructionsTime, 17)
    ST_DECLARE_VP_COUNTER(MwaitInstructions, 18)
    ST_DECLARE_VP_COUNTER(MwaitInstructionsTime, 19)
    ST_DECLARE_VP_COUNTER(CpuidInstructions, 20)
    ST_DECLARE_VP_COUNTER(CpuidInstructionsTime, 21)
    ST_DECLARE_VP_COUNTER(MsrAccesses, 22)
    ST_DECLARE_VP_COUNTER(MsrAccessesTime, 23)
    ST_DECLARE_VP_COUNTER(PauseInstructions, 24)
    ST_DECLARE_VP_COUNTER(PauseInstructionsTime, 25)
    ST_DECLARE_VP_COUNTER(TaskSwitches, 26)
    ST_DECLARE_VP_COUNTER(TaskSwitchesTime, 27)
    ST_DECLARE_VP_COUNTER(NmiInterrupts, 28)
    ST_DECLARE_VP_COUNTER(NmiInterruptsTime, 29)
    ST_DECLARE_VP_COUNTER(InitInterrupts, 30)
    ST_DECLARE_VP_COUNTER(InitInterruptsTime, 31)
    ST_DECLARE_VP_COUNTER(PendingInterrupts, 32)
    ST_DECLARE_VP_COUNTER(PendingInterruptsTime, 33)
    ST_DECLARE_VP_COUNTER(SipiInterrupts, 34)
    ST_DECLARE_VP_COUNTER(SipiInterruptsTime, 35)
    ST_DECLARE_VP_COUNTER(EmulatedInstructions, 36)
    ST_DECLARE_VP_COUNTER(EmulatedInstructionsTime, 37)
    ST_DECLARE_VP_COUNTER(EmulatedRealModeInterruptions, 38)
    ST_DECLARE_VP_COUNTER(EmulatedRealModeInterruptionsTime, 39)
    ST_DECLARE_VP_COUNTER(VirtualInterrupts, 40)
    ST_DECLARE_VP_COUNTER(VirtualInterruptsTime, 41)
    ST_DECLARE_VP_COUNTER(RsmInstructions, 42)
    ST_DECLARE_VP_COUNTER(RsmInstructionsTime, 43)
    ST_DECLARE_VP_COUNTER(Shutdowns, 44)
    ST_DECLARE_VP_COUNTER(ShutdownsTime, 45)
    ST_DECLARE_VP_COUNTER(IretdEmulations, 46)
    ST_DECLARE_VP_COUNTER(IretdEmulationsTime, 47)
    ST_DECLARE_VP_COUNTER(InvdInstructions, 48)
    ST_DECLARE_VP_COUNTER(InvdInstructionsTime, 49)
    ST_DECLARE_VP_COUNTER(DrAccesses, 50)
    ST_DECLARE_VP_COUNTER(DrAccessesTime, 51)
    ST_DECLARE_VP_COUNTER(MemoryIntercepts, 52)
    ST_DECLARE_VP_COUNTER(MemoryInterceptsTime, 53)
    ST_DECLARE_VP_COUNTER(OverlayIntercepts, 54)
    ST_DECLARE_VP_COUNTER(OverlayInterceptsTime, 55)
    ST_DECLARE_VP_COUNTER(ReflectedGuestExceptions, 56)
    ST_DECLARE_VP_COUNTER(ReflectedGuestExceptionsTime, 57)
    ST_DECLARE_VP_COUNTER(GuestExecutions, 58)
    ST_DECLARE_VP_COUNTER(GuestExecutionsTime, 59)
    ST_DECLARE_VP_COUNTER(Messages, 60)
    ST_DECLARE_VP_COUNTER(GuestPageTableMaps, 61)
    ST_DECLARE_VP_COUNTER(LargePageMaps, 62)
    ST_DECLARE_VP_COUNTER(PageMaps, 63)
    ST_DECLARE_VP_COUNTER(VirtualTlbCollisionTime, 64)
    ST_DECLARE_VP_COUNTER(PostedMessages, 65)
    ST_DECLARE_VP_COUNTER(PostedMessageBytes, 66)
    ST_DECLARE_VP_COUNTER(ReceivedMessages, 67)
    ST_DECLARE_VP_COUNTER(ReceivedMessageBytes, 68)
    ST_DECLARE_VP_COUNTER(PostedEvents, 69)
    ST_DECLARE_VP_COUNTER(ReflectedPageFaults, 70)
    ST_VP_COUNTER_NAME(MAXIMUM)

} HV_THREAD_COUNTER;

#define HV_STATISTICS_GROUP_VPA_LENGTH 32
#define HV_STATISTICS_GROUP_VPV_LENGTH 520



//
// Declare the timestamp type.
//
typedef UINT64 HV_TIME_STAMP, *PHV_TIME_STAMP;

//
// Logical processors are defined by a 32-bit index
//
typedef UINT32 HV_LOGICAL_PROCESSOR_INDEX, *PHV_LOGICAL_PROCESSOR_INDEX;

//
// Time in the hypervisor is measured in 100 nanosecond units
//
typedef UINT64 HV_NANO100_TIME,     *PHV_NANO100_TIME;
typedef UINT64 HV_NANO100_DURATION, *PHV_NANO100_DURATION;

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
    HvX64InterruptTypeNmi               = 0x0004,
    HvX64InterruptTypeInit              = 0x0005,
    HvX64InterruptTypeSipi              = 0x0006,
    HvX64InterruptTypeExtInt            = 0x0007,

    //
    // Maximum (exclusive) value of interrupt type.
    //
    HvX64InterruptTypeMaximum           = 0x008

} HV_INTERRUPT_TYPE, *PHV_INTERRUPT_TYPE;

//
// Define interrupt vector type.
//
typedef UINT32 HV_INTERRUPT_VECTOR, *PHV_INTERRUPT_VECTOR;

//
// Define special "no interrupt vector" value used by hypercalls that indicate
// whether the previous virtual interrupt was acknowledged.
//
#define HV_INTERRUPT_VECTOR_NONE 0xFFFFFFFF

//
// In a NUMA system processors, memory and devices may reside in different
// firmware described proximity domains.
//
// On a non-NUMA system everything resides in proximity domain 0.
//

typedef UINT32 HV_PROXIMITY_DOMAIN_ID, *PHV_PROXIMITY_DOMAIN_ID;

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
    UINT32 ProximityPreferred:1;

    UINT32 Reserved:30;

    //
    // This flag specifies that the specified proximity domain is valid. If
    // this flag is false then the memory allocation can come from any
    // proximity domain.
    //
    UINT32 ProximityInfoValid:1;

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
    UINT32 LocalApicId;

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
    UINT64 Length;

    //
    // The proximity domain this memory range resides in.
    //
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;

} HV_MEMORY_RANGE_INFO, *PHV_MEMORY_RANGE_INFO;

typedef const HV_MEMORY_RANGE_INFO* PCHV_MEMORY_RANGE_INFO;


//
// This structure is used to transfer crashdump information between the
// Hypervisor and the HvBoot.sys driver in the root Windows instance at the
// time of a Hypervisor BugCheck.  It is allocated by HvBoot.sys during the
// Hypervisor launch process, and its SPA is handed in to the Hypervisor via
// the loader block.
//

#define HV_CRASHDUMP_AREA_VERSION   1

typedef struct _HV_CRASHDUMP_AREA
{
    //
    // Version of the Crashdump Area structure
    //

    UINT32 Version;

    //
    // Flags indicating content validity and other attributes of the
    // Crashdump Area
    //

    union
    {
        UINT32 FlagsAsUINT32;
        struct
        {
            //
            // Indicates the contents of the Crashdump Area are valid
            //

            UINT32  Valid:1;
            UINT32  Reserved:31;

        };

    };

    //
    // Bugcheck error code fields
    //

    UINT64 BugCheckData[5];
    void  *BugCheckErrorReturnAddress;

    //
    // Count and array reference to per-proc (nt) KPROCESSOR_STATE /
    // (hv) KD_PROCESSOR_STATE structures where state of each processor is
    // put during crashdump.
    //

    UINT32 ProcessorContextCount;
    UINT32 ProcessorContextOffset;

} HV_CRASHDUMP_AREA, *PHV_CRASHDUMP_AREA;



//
// Define the trace buffer index type.
//

typedef UINT32 HV_EVENTLOG_BUFFER_INDEX, *PHV_EVENTLOG_BUFFER_INDEX;

#define HV_EVENTLOG_BUFFER_INDEX_NONE 0xffffffff

//
// Define all the trace buffer types.
//

typedef enum
{
    HvEventLogTypeGlobalSystemEvents = 0x00000000,
    HvEventLogTypeLocalDiagnostics   = 0x00000001,
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
    UINT64          TimeStamp;

} HV_EVENTLOG_ENTRY_TIME;


//
// Define trace buffer header.
//

typedef struct _HV_EVENTLOG_BUFFER_HEADER
{
    UINT32                         BufferSize;        // BufferSize
    HV_EVENTLOG_BUFFER_INDEX       BufferIndex;       // SavedOffset   
    UINT32                         EventsLost;        // CurrentOffset
    volatile UINT32                ReferenceCounter;  // ReferenceCount

    union
    {
        UINT64                     TimeStamp;
        HV_NANO100_TIME            ReferenceTime;
    };
    UINT64                         Reserved1;

    UINT64                         Reserved2;    
    struct                                            // ClientContext
    {
        UINT8                      LogicalProcessor;  // ProcessorNumber
        UINT8                      Alignment;
        UINT16                     LoggerId;
    };
    volatile HV_EVENTLOG_BUFFER_STATE BufferState;    // (Free/GeneralLogging/Flush)
    
    UINT32                         NextBufferOffset;  // Offset
    HV_EVENTLOG_TYPE               Type;              // BufferFlag and BufferType
    HV_EVENTLOG_BUFFER_INDEX       NextBufferIndex;   // Padding1
    UINT32                         Reserved3;         // Padding1

    UINT32                         Reserved4[2];      // Padding1 
    
} HV_EVENTLOG_BUFFER_HEADER, *PHV_EVENTLOG_BUFFER_HEADER;


//
// Define trace entry header.
//
typedef struct _HV_EVENTLOG_ENTRY_HEADER
{
    UINT32              Context;    // Marker    
    UINT16              Size;       // Size in WMI_TRACE_PACKET
    UINT16              Type;       // HookId in WMI_TRACE_PACKET
    
    union 
    {
        UINT64          TimeStamp;
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
    UINT32 MaximumBufferCount;
    UINT32 BufferSizeInPages;
    UINT32 Threshold;
    HV_EVENTLOG_ENTRY_TIME_BASIS TimeBasis;

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
    UINT64           EnableFlags;

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
// Performance Trace Groups (starting at 0x0000000000000100)
//
#define HV_TR_GROUP_KE              0x0000000000000100
#define HV_TR_GROUP_SCH             0x0000000000000200
#define HV_TR_GROUP_MM              0x0000000000000400
#define HV_TR_GROUP_VAL             0x0000000000000800
#define HV_TR_GROUP_VP              0x0000000000001000
#define HV_TR_GROUP_AM              0x0000000000002000
#define HV_TR_GROUP_PT              0x0000000000004000
#define HV_TR_GROUP_HC              0x0000000000008000
#define HV_TR_GROUP_IM              0x0000000000010000
#define HV_TR_GROUP_DM              0x0000000000020000
#define HV_TR_GROUP_BM              0x0000000000040000
#define HV_TR_GROUP_TI              0x0000000000080000
#define HV_TR_GROUP_SYNIC           0x0000000000100000

//
// Performance Trace Sub-Groups (starting at 0x0000000100000000)
//
#define HV_TR_GROUP_AM_GPA          0x0000000100000000
#define HV_TR_GROUP_AM_GVA          0x0000000200000000

//
// Internal Debugging Trace Groups (starting at 0x0001000000000000)
//
#define HV_TR_GROUP_SCH_INTERNAL        0x0001000000000000
#define HV_TR_GROUP_TI_INTERNAL         0x0002000000000000
#define HV_TR_GROUP_SYNIC_INTERNAL      0x0004000000000000
#define HV_TR_GROUP_KE_INTERNAL         0x0008000000000000
#define HV_TR_GROUP_TISYNIC_INTERNAL    0x0010000000000000

//
// Internal Synic Trace Types.
//
#define HV_TR_SYNIC_ASSERT          0x01
#define HV_TR_SYNIC_EVALUATE        0x02
#define HV_TR_SYNIC_VIP             0x03
#define HV_TR_SYNIC_EOI             0x04
#define HV_TR_SYNIC_LATENCY         0x05
#define HV_TR_SYNIC_MARK_PENDING    0x06
#define HV_TR_SYNIC_MARK_PENDING2   0x07
#define HV_TR_SYNIC_EVAL_APIC_INTS  0x08


#if defined(_HV_TEST_FEATURES_ENABLED_) || defined(_PERF_FEATURES_ENABLED_)

//
// Tf, simulate full buffers and cyclic buffers are currently only
// supported for TEST_FEATURES_ENABLED builds.
//
#define HV_TR_GROUP_TF              0x0800000000000000
#define HV_TR_GROUP_SIMULATE_FULL   0x1000000000000000
#define HV_TR_GROUP_CYCLIC          0x2000000000000000

#endif

#if defined(_HV_ICECAP_ENABLED_)

//
// NMI and ICECAP Trace Groups.
//
#define HV_TR_GROUP_ICE             0x8000000000000000

#endif // defined(_HV_ICECAP_ENABLED_)

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
// N.B. The group mask's bit position (starting with 1) should be left
// shifted 8 bits and ORd with the increasing type Id
//

//
// Sch Trace Types.
//
#define HV_TR_SCH_SWITCH            0x11


//
// Dm Trace Types.
//
#define HV_TR_DM_INTERCEPT          0x21


//
// AM GVA Trace Types.
//
#define HV_TR_GVA_PAGE_FAULT        0x31
#define HV_TR_GVA_CR_WRITE          0x32
#define HV_TR_GVA_UPDATE_SPACE      0x33
#define HV_TR_GVA_FLUSH_LOCAL       0x34
#define HV_TR_GVA_FLUSH_GLOBAL      0x35
#define HV_TR_GVA_FLUSH_SPACE       0x36
#define HV_TR_GVA_FLUSH_DOMAIN      0x37
#define HV_TR_GVA_RESET_DOMAIN      0x38
#define HV_TR_GVA_TRANSLATE_VA      0x39
#define HV_TR_GVA_READ_VM           0x3A
#define HV_TR_GVA_WRITE_VM          0x3B

//
// Reserve one more group for AM GVA Trace Types
//

//
// Internal Ke Trace Types.
//
#define HV_TR_KE_OVERRUN            0x51


#if defined(_HV_TEST_FEATURES_ENABLED_) || defined(_PERF_FEATURES_ENABLED_)

//
// Internal Sch Trace Types.
//
#define HV_TR_SCH_PREEMPTION        0x61
#define HV_TR_SCH_NEWTIMESLICE      0x62
#define HV_TR_SCH_PRIORITY_EVAL     0x63
#define HV_TR_SCH_OVERRUN           0x64
#define HV_TR_SCH_AFFINTY_CHANGE    0x65
#define HV_TR_SCH_KEEP_INTERIM      0x66
#define HV_TR_SCH_PULL_INTERIM      0x67
#define HV_TR_SCH_PUSH_INTERIM      0x68
#define HV_TR_SCH_TIMESLICE_END     0x69
#define HV_TR_SCH_RUN_CURRENT       0x6A
#define HV_TR_SCH_EVAL_SEND         0x6B
#define HV_TR_SCH_EVAL_RECV         0x6C
#define HV_TR_SCH_YIELD             0x6D
#define HV_TR_SCH_SET_PRIO          0x6E
#define HV_TR_SCH_EVAL_AFFINTY      0x6F
#define HV_TR_SCH_EVAL_TIMESLICE    0x60
#define HV_TR_SCH_SIGNAL_EVENT      0x71
#define HV_TR_SCH_BLOCK_ON_WAIT     0x72
#define HV_TR_SCH_UNBLOCK_ON_WAIT   0x73
#define HV_TR_SCH_EVENT_TIMER_END   0x74
#define HV_TR_SCH_ADD_INTERMEDIATE  0x75
#define HV_TR_SCH_GET_INTERMEDIATE  0x76
#define HV_TR_SCH_LOAD_BALANCER     0x77
#define HV_TR_SCH_EVALUATE          0x78


//
// Internal Ti Trace Types.
//
#define HV_TR_TI_CALIBRATION        0x81
#define HV_TR_TI_SETAPIC            0x82
#define HV_TR_TI_INTERRUPT          0x83
#define HV_TR_TI_NEWTIMER           0x84
#define HV_TR_TI_CALLBACK           0x85
#define HV_TR_TI_CHANGE_AFFINITY    0x86


//
// Internal Synic Ti Trace Types.
//
#define HV_TR_TI_SYNIC_PERIODIC     0x86
#define HV_TR_TI_SYNIC_SEND_MESSAGE 0x87
#define HV_TR_TI_SYNIC_SCAN_MESSAGE 0x88


//
// Internal TfTrace Types.
//
#define HV_TR_TF_INTERCEPT          0x91

#endif // defined(_HV_TEST_FEATURES_ENABLED_) || defined(_PERF_FEATURES_ENABLED_)


#if defined(_HV_ICECAP_ENABLED_)

//
// Internal IceCAP Trace Types.
//
#define HV_TR_ICE_CALL              0xA1      // fixed (tffastcap.asm)
#define HV_TR_ICE_RET               0xA2      // fixed (tffastcap.asm)
#define HV_TR_ICE_ACQUIRE           0xA3      // fixed (rtlspinlocks.h)
#define HV_TR_ICE_RELEASE           0xA4      // fixed (rtlspinlocks.h)
#define HV_TR_ICE_COMMENT           0xA5


//
// Internal Profiler Types.
//
#define HV_TR_ICE_PROFILE           0xA6

#endif // defined(_HV_ICECAP_ENABLED_)


//
// Physical nodes are defined by a 32-bit index.
//

typedef UINT32 HV_PHYSICAL_NODE_INDEX, *PHV_PHYSICAL_NODE_INDEX;

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
        UINT64 AsUINT64;
        struct
        {
            UINT64 Enable     : 1;
            UINT64 Periodic   : 1;
            UINT64 Lazy       : 1;
            UINT64 AutoEnable : 1;
            UINT64 Reserved1  :12;
            UINT64 SINTx      : 4;
            UINT64 Reserved2  :14;
        };
    };
} HV_X64_MSR_STIMER_CONFIG_CONTENTS, *PHV_X64_MSR_STIMER_CONFIG_CONTENTS;

typedef enum _HV_SAVE_RESTORE_STATE_RESULT
{
    HvStateComplete                 = 0,
    HvStateIncomplete               = 1,
    HvStateRestorable               = 2,
    HvStateCorruptData              = 3,
    HvStateUnsupportedVersion       = 4,
    HvStateProcessorFeatureMismatch = 5,
    HvStateHardwareFeatureMismatch  = 6,
    HvStateProcessorCountMismatch   = 7,
    HvStateProcessorFlagsMismatch   = 8,
    HvStateProcessorIndexMismatch   = 9
} HV_SAVE_RESTORE_STATE_RESULT, *PHV_SAVE_RESTORE_STATE_RESULT;

typedef UINT32 HV_SAVE_RESTORE_STATE_FLAGS, *PHV_SAVE_RESTORE_STATE_FLAGS;

#define HV_SAVE_RESTORE_STATE_START   0x00000001
#define HV_SAVE_RESTORE_STATE_SUMMARY 0x00000002

typedef union _HV_PARTITION_PRIVILEGE_MASK
{
    UINT64 AsUINT64;
    struct
    {
        //
        // Access to virtual MSRs
        //
        UINT64  AccessVpRunTimeMsr:1;
        UINT64  AccessPartitionReferenceCounter:1;
        UINT64  AccessSynicMsrs:1;
        UINT64  AccessSyntheticTimerMsrs:1;
        UINT64  AccessApicMsrs:1;
        UINT64  AccessHypercallMsrs:1;
        UINT64  AccessVpIndex:1;
        UINT64  Reserved1:25;

        //
        // Access to hypercalls
        //
        UINT64  CreatePartitions:1;
        UINT64  AccessPartitionId:1;
        UINT64  AccessMemoryPool:1;
        UINT64  AdjustMessageBuffers:1;
        UINT64  PostMessages:1;
        UINT64  SignalEvents:1;
        UINT64  CreatePort:1;
        UINT64  ConnectPort:1;
        UINT64  AccessStats:1;
        UINT64  IteratePhysicalHardware:1;
        UINT64  ExposeHyperthreads:1;
        UINT64  Debugging:1;
        UINT64  CpuPowerManagement:1;
        UINT64  Reserved2:19;
    };

} HV_PARTITION_PRIVILEGE_MASK, *PHV_PARTITION_PRIVILEGE_MASK;

typedef union _HV_EXPLICIT_SUSPEND_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Suspended:1;
        UINT64 Reserved:63;
    };
} HV_EXPLICIT_SUSPEND_REGISTER, *PHV_EXPLICIT_SUSPEND_REGISTER;

typedef union _HV_INTERCEPT_SUSPEND_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Suspended:1;
        UINT64 TlbLocked:1;
        UINT64 Reserved:62;
    };
} HV_INTERCEPT_SUSPEND_REGISTER, *PHV_INTERCEPT_SUSPEND_REGISTER;

typedef union _HV_X64_INTERRUPT_STATE_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 InterruptShadow:1;
        UINT64 NmiMasked:1;
        UINT64 Reserved:62;
    };
} HV_X64_INTERRUPT_STATE_REGISTER, *PHV_X64_INTERRUPT_STATE_REGISTER;

typedef enum _HV_X64_PENDING_INTERRUPTION_TYPE
{
    HvX64PendingInterrupt           = 0,
    HvX64PendingNmi                 = 2,
    HvX64PendingException           = 3,
    HvX64PendingSoftwareInterrupt   = 4
} HV_X64_PENDING_INTERRUPTION_TYPE, *PHV_X64_PENDING_INTERRUPTION_TYPE;

typedef union _HV_X64_PENDING_INTERRUPTION_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT32 InterruptionPending:1;
        UINT32 InterruptionType:3;
        UINT32 DeliverErrorCode:1;
        UINT32 Reserved:11;
        UINT32 InterruptionVector:16;
        UINT32 ErrorCode;
    };
} HV_X64_PENDING_INTERRUPTION_REGISTER, *PHV_X64_PENDING_INTERRUPTION_REGISTER;

typedef union _HV_REGISTER_VALUE
{
    HV_UINT128                              Reg128;
    UINT64                                  Reg64;
    UINT32                                  Reg32;
    UINT16                                  Reg16;
    UINT8                                   Reg8;
    HV_X64_FP_REGISTER                      Fp;
    HV_X64_FP_CONTROL_STATUS_REGISTER       FpControlStatus;
    HV_X64_XMM_CONTROL_STATUS_REGISTER      XmmControlStatus;
    HV_X64_SEGMENT_REGISTER                 Segment;
    HV_X64_TABLE_REGISTER                   Table;
    HV_EXPLICIT_SUSPEND_REGISTER            ExplicitSuspend;
    HV_INTERCEPT_SUSPEND_REGISTER           InterceptSuspend;
    HV_X64_INTERRUPT_STATE_REGISTER         InterruptState;
    HV_X64_PENDING_INTERRUPTION_REGISTER    PendingInterruption;
} HV_REGISTER_VALUE, *PHV_REGISTER_VALUE;
typedef const HV_REGISTER_VALUE *PCHV_REGISTER_VALUE;

//
// Define the intercept access types.
//

typedef UINT8 HV_INTERCEPT_ACCESS_TYPE;

#define HV_INTERCEPT_ACCESS_READ    0
#define HV_INTERCEPT_ACCESS_WRITE   1
#define HV_INTERCEPT_ACCESS_EXECUTE 2

typedef UINT32 HV_INTERCEPT_ACCESS_TYPE_MASK;

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
typedef UINT16 HV_X64_IO_PORT, *PHV_X64_IO_PORT;


//
// Define intercept parameters.
//
typedef union _HV_INTERCEPT_PARAMETERS
{
    //
    // HV_INTERCEPT_PARAMETERS is defined to be an 8-byte field.
    //
    UINT64 AsUINT64;

    //
    // HvInterceptTypeX64IoPort.
    //
    HV_X64_IO_PORT IoPort;

    //
    // HvInterceptTypeX64Cpuid.
    //
    UINT32 CpuidIndex;

    //
    // HvInterceptTypeX64Exception.
    //
    UINT16 ExceptionVector;

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
typedef UINT32 HV_VP_INDEX, *PHV_VP_INDEX;

#define HV_MAX_VP_INDEX (63)

//
// Declare the MSR for determining the current VP index.
//
#define HV_X64_MSR_VP_INDEX     0x40000002
#define HV_X64_MSR_RESET        0x40000003

//
// Declare the VP run time MSR.
//
#define HV_X64_MSR_VP_RUNTIME   0x40000010

//
// Scheduling control
//
typedef union _HV_SCHEDULING_CONTROL
{
    UINT64 AsUINT64;

    struct
    {
        UINT64  DeterministicTsc:1;
        UINT64  Reserved:63;
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
    HvMicrosoftHypervisorInterface = '1#vH'

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
    UINT32 BuildNumber;

    UINT32 MinorVersion:16;
    UINT32 MajorVersion:16;

    UINT32 ServicePack;

    UINT32 ServiceNumber:24;
    UINT32 ServiceBranch:8; // Type is HV_SERVICE_BRANCH

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
    HvCpuIdFunctionMsHvImplementationLimits     = 0x40000005

} HV_CPUID_FUNCTION, *PHV_CPUID_FUNCTION;

typedef union _HV_CPUID_RESULT
{
    struct
    {
        UINT32 Eax;
        UINT32 Ebx;
        UINT32 Ecx;
        UINT32 Edx;
    };

    UINT32 AsUINT32[4];

    struct
    {
        //
        // Eax
        //
        UINT32 ReservedEax;

        //
        // Ebx
        //
        UINT32 ReservedEbx:24;
        UINT32 InitialApicId:8;

        //
        // Ecx
        //
        UINT32 ReservedEcx:31;
        UINT32 HypervisorPresent:1;

        //
        // Edx
        //
        UINT32 ReservedEdx;

    } VersionAndFeatures;

    struct
    {
        //
        // Eax
        //
        UINT32 MaxFunction;

        //
        // Ebx-Edx
        //
        UINT8 VendorName[12];

    } HvVendorAndMaxFunction;

    struct
    {
        //
        // Eax
        //
        UINT32 Interface; // HV_HYPERVISOR_INTERFACE

        //
        // Ebx
        //
        UINT32 ReservedEbx;

        //
        // Ecx
        //
        UINT32 ReservedEcx;

        //
        // Edx
        //
        UINT32 ReservedEdx;

    } HvInterface;

    //
    // Eax-Edx.
    //
    HV_HYPERVISOR_VERSION_INFO MsHvVersion;

    struct
    {
        //
        // Eax-Ebx
        //
        HV_PARTITION_PRIVILEGE_MASK PartitionPrivileges;

        //
        // Ecx
        //
        UINT32 ReservedEcx;

        //
        // Edx
        //
        UINT32 MwaitAvailalbe:1;
        UINT32 GuestDebuggingAvailable:1;
        UINT32 PerformanceMonitorsAvailable:1;
        UINT32 Reserved:29;

    } MsHvFeatures;

    struct
    {
        //
        // Eax
        //
        UINT32 UseHypercallForAddressSpaceSwitch:1;
        UINT32 UseHypercallForLocalFlush:1;
        UINT32 UseHypercallForRemoteFlush:1;
        UINT32 UseApicMsrs:1;
        UINT32 UseMsrForReset:1;
        UINT32 Reserved:27;

        //
        // Ebx
        //
        UINT32 ReservedEbx;

        //
        // Ecx
        //
        UINT32 ReservedEcx;

        //
        // Edx
        //
        UINT32 ReservedEdx;

    } MsHvEnlightenmentInformation;

    struct
    {
        //
        // Eax
        //
        UINT32 MaxVirtualProcessorCount;

        //
        // Ebx
        //
        UINT32 MaxLogicalProcessorCount;

        //
        // Ecx
        //
        UINT32 ReservedEcx;

        //
        // Edx
        //
        UINT32 ReservedEdx;

    } MsHvImplementationLimits;

} HV_CPUID_RESULT, *PHV_CPUID_RESULT;

#define HV_CPUID_HV_VENDOR_MICROSOFT_EBX 'rciM'
#define HV_CPUID_HV_VENDOR_MICROSOFT_ECX 'foso'
#define HV_CPUID_HV_VENDOR_MICROSOFT_EDX 'vH t'

//
// Address spaces presented by the guest.
//
typedef UINT64 HV_ADDRESS_SPACE_ID, *PHV_ADDRESS_SPACE_ID;

//
// Address space flush flags.
//
typedef UINT64 HV_FLUSH_FLAGS, *PHV_FLUSH_FLAGS;

#define HV_FLUSH_ALL_PROCESSORS              (0x00000001)
#define HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES  (0x00000002)
#define HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY    (0x00000004)
#define HV_FLUSH_MASK                        (HV_FLUSH_ALL_PROCESSORS | \
                                              HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES | \
                                              HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY)

//
// Address translation flags.
//

#define HV_TRANSLATE_GVA_VALIDATE_READ       (0x0001)
#define HV_TRANSLATE_GVA_VALIDATE_WRITE      (0x0002)
#define HV_TRANSLATE_GVA_VALIDATE_EXECUTE    (0x0004)
#define HV_TRANSLATE_GVA_PRIVILEGE_EXEMPT    (0x0008)
#define HV_TRANSLATE_GVA_SET_PAGE_TABLE_BITS (0x0010)
#define HV_TRANSLATE_GVA_TLB_FLUSH_INHIBIT   (0x0020)
#define HV_TRANSLATE_GVA_CONTROL_MASK        (0x003F)

typedef UINT64 HV_TRANSLATE_GVA_CONTROL_FLAGS, *PHV_TRANSLATE_GVA_CONTROL_FLAGS;

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
    HvTranslateGvaGpaIllegalOverlayAccess = 7

} HV_TRANSLATE_GVA_RESULT_CODE, *PHV_TRANSLATE_GVA_RESULT_CODE;

typedef union _HV_TRANSLATE_GVA_RESULT
{
    UINT64 AsUINT64;
    struct
    {
        HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
        UINT32 CacheType : 8;
        UINT32 OverlayPage : 1;
        UINT32 Reserved : 23;
    };
} HV_TRANSLATE_GVA_RESULT, *PHV_TRANSLATE_GVA_RESULT;

//
// Read and write GPA access flags.
//

typedef union _HV_ACCESS_GPA_CONTROL_FLAGS
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 CacheType : 8;  // Cache type for access
        UINT64 Reserved  : 56;
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
    UINT64 AsUINT64;
    struct
    {
        HV_ACCESS_GPA_RESULT_CODE ResultCode;
        UINT32                    Reserved;
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
typedef UINT32 HV_MAP_GPA_FLAGS;

#define HV_MAP_GPA_READABLE	(0x00000001)
#define HV_MAP_GPA_WRITABLE	(0x00000002)
#define HV_MAP_GPA_EXECUTABLE	(0x00000004)

//
// Gva Range
//
// The GVA range is a compressed range of GVA used by the TLB flush
// routines.
//

typedef union _HV_GVA_RANGE
{
    UINT64 AsUINT64;

    struct
    {
        //
        // Additional pages supplies the number of pages beyond one.
        //

        UINT64 AdditionalPages : 12;

        //
        // GvaPageNumber supplies the top 54 most significant bits of the
        // guest virtual address space.
        //

        UINT64 GvaPageNumber   : 52;
    };
} HV_GVA_RANGE, *PHV_GVA_RANGE;


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
#define HV_ANY_VP                       (0xFFFFFFFF)

//
// Define synthetic interrupt controller flag constants.
//

#define HV_EVENT_FLAGS_COUNT        (256 * 8)
#define HV_EVENT_FLAGS_BYTE_COUNT   (256)
#define HV_EVENT_FLAGS_DWORD_COUNT  (256 / sizeof(UINT32))

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

    //
    // Trace buffer complete messages.
    //
    HvMessageTypeEventLogBufferComplete = 0x80000040,

    //
    // Platform-specific processor intercept messages.
    //
    HvMessageTypeX64IoPortIntercept = 0x80010000,
    HvMessageTypeX64MsrIntercept = 0x80010001,
    HvMessageTypeX64CpuidIntercept = 0x80010002,
    HvMessageTypeX64ExceptionIntercept = 0x80010003,
    HvMessageTypeX64ApicEoi = 0x80010004,
    HvMessageTypeX64LegacyFpError = 0x80010005

} HV_MESSAGE_TYPE, *PHV_MESSAGE_TYPE;


#define HV_MESSAGE_TYPE_HYPERVISOR_MASK (0x80000000)


//
// Define APIC EOI message.
//
typedef struct _HV_X64_APIC_EOI_MESSAGE
{
    UINT32 VpIndex;
    UINT32 InterruptVector;
} HV_X64_APIC_EOI_MESSAGE, *PHV_X64_APIC_EOI_MESSAGE;


//
// Define the number of synthetic interrupt sources.
//

#define HV_SYNIC_SINT_COUNT (16)
#define HV_SYNIC_STIMER_COUNT (4)

//
// Define the synthetic interrupt source index type.
//

typedef UINT32 HV_SYNIC_SINT_INDEX, *PHV_SYNIC_SINT_INDEX;

//
// Define partition identifier type.
//

typedef UINT64 HV_PARTITION_ID, *PHV_PARTITION_ID;

//
// Define invalid partition identifier.
//
#define HV_PARTITION_ID_INVALID ((HV_PARTITION_ID) 0x0)

//
// Define connection identifier type.
//

typedef UINT32 HV_CONNECTION_ID, *PHV_CONNECTION_ID;

//
// Define port identifier type.
//

typedef UINT32 HV_PORT_ID, *PHV_PORT_ID;

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
    UINT32 Padding;

    union
    {
        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            UINT64 RsvdZ;
        } MessagePortInfo;

        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            UINT16 BaseFlagNumber;
            UINT16 FlagCount;
            UINT32 RsvdZ;
        } EventPortInfo;

        struct
        {
            HV_GPA MonitorAddress;
            UINT64 RsvdZ;
        } MonitorPortInfo;
    };
} HV_PORT_INFO, *PHV_PORT_INFO;

typedef const HV_PORT_INFO *PCHV_PORT_INFO;

typedef struct _HV_CONNECTION_INFO
{
    HV_PORT_TYPE PortType;
    UINT32 Padding;

    union
    {
        struct
        {
            UINT64 RsvdZ;
        } MessageConnectionInfo;

        struct
        {
            UINT64 RsvdZ;
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

typedef UINT64 HV_PORT_PROPERTY, *PHV_PORT_PROPERTY;

//
// Define enumeration of port property codes.
//

typedef enum _HV_PORT_PROPERTY_CODE
{
    HvPortPropertyPostCount = 0x00000000
} HV_PORT_PROPERTY_CODE, *PHV_PORT_PROPERTY_CODE;


//
// Define synthetic interrupt controller message flags.
//

typedef union _HV_MESSAGE_FLAGS
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 MessagePending:1;
        UINT8 Reserved:7;
    };
} HV_MESSAGE_FLAGS, *PHV_MESSAGE_FLAGS;


//
// Define synthetic interrupt controller message header.
//

typedef struct _HV_MESSAGE_HEADER
{
    HV_MESSAGE_TYPE     MessageType;
    UINT8               PayloadSize;
    HV_MESSAGE_FLAGS    MessageFlags;
    UINT8               Reserved[2];
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
    UINT32          TimerIndex;
    UINT32          Reserved;
    HV_NANO100_TIME ExpirationTime;     // When the timer expired
    HV_NANO100_TIME DeliveryTime;       // When the message was delivered
} HV_TIMER_MESSAGE_PAYLOAD, *PHV_TIMER_MESSAGE_PAYLOAD;

//
// Define synthetic interrupt controller message format.
//

typedef struct _HV_MESSAGE
{
    HV_MESSAGE_HEADER Header;
    union
    {
        UINT64 Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
        HV_TIMER_MESSAGE_PAYLOAD TimerPayload;
        HV_EVENTLOG_MESSAGE_PAYLOAD TracePayload;
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
    UINT8 Flags8[HV_EVENT_FLAGS_BYTE_COUNT];
    UINT32 Flags32[HV_EVENT_FLAGS_DWORD_COUNT];
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
    UINT64 AsUINT64;
    struct
    {
        UINT64 Enable:1;
        UINT64 Reserved:63;
    };
} HV_SYNIC_SCONTROL, *PHV_SYNIC_SCONTROL;

//
// Define synthetic interrupt source.
//

typedef union _HV_SYNIC_SINT
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Vector    :8;
        UINT64 Reserved1 :8;
        UINT64 Masked    :1;
        UINT64 AutoEoi   :1;
        UINT64 Reserved2 :46;
    };
} HV_SYNIC_SINT, *PHV_SYNIC_SINT;

//
// Define the format of the SIMP register
//

typedef union _HV_SYNIC_SIMP
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 SimpEnabled : 1;
        UINT64 Preserved   : 11;
        UINT64 BaseSimpGpa : 52;
    };
} HV_SYNIC_SIMP, *PHV_SYNIC_SIMP;

//
// Define the format of the SIEFP register
//

typedef union _HV_SYNIC_SIEFP
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 SiefpEnabled : 1;
        UINT64 Preserved   : 11;
        UINT64 BaseSiefpGpa : 52;
    };
} HV_SYNIC_SIEFP, *PHV_SYNIC_SIEFP;

//
// Define virtual interrupt control structure.
//
typedef union _HV_INTERRUPT_CONTROL
{
    UINT64 AsUINT64;
    struct
    {
        HV_INTERRUPT_TYPE InterruptType;
        UINT32 LevelTriggered:1;
        UINT32 LogicalDestinationMode:1;
        UINT32 Reserved:30;
    };
} HV_INTERRUPT_CONTROL, *PHV_INTERRUPT_CONTROL;


//
// Emulated timer period
//
typedef union _HV_EMULATED_TIMER_PERIOD
{
    UINT64              AsUINT64;
    HV_NANO100_DURATION Period;

} HV_EMULATED_TIMER_PERIOD, *PHV_EMULATED_TIMER_PERIOD;

//
// Periodic Timer route
//
typedef union _HV_EMULATED_TIMER_CONTROL
{
    UINT64  AsUINT64;

    struct
    {
        UINT32  Vector                  :  8;
        UINT32  DeliveryMode            :  3;
        UINT32  LogicalDestinationMode  :  1;
        UINT32  Enabled                 :  1;
        UINT32  Reserved                : 19;
        UINT32  Mda                     : 32;
    };

} HV_EMULATED_TIMER_CONTROL, *PHV_EMULATED_TIMER_CONTROL;

//
// ACPI PM timer
//
typedef union _HV_PM_TIMER_INFO
{
    UINT64  AsUINT64;

    struct
    {
        UINT32  Port                : 16;
        UINT32  Width24             :  1;
        UINT32  Enabled             :  1;
        UINT32  Reserved1           : 14;
        UINT32  Reserved2           : 32;
    };

} HV_PM_TIMER_INFO, *PHV_PM_TIMER_INFO;

//
// Definitions for the monitored notification facility
//

typedef union _HV_MONITOR_TRIGGER_GROUP
{
    UINT64 AsUINT64;

    struct
    {
        UINT32 Pending;
        UINT32 Armed;
    };
    
} HV_MONITOR_TRIGGER_GROUP, *PHV_MONITOR_TRIGGER_GROUP;

typedef struct _HV_MONITOR_PARAMETER
{
    HV_CONNECTION_ID    ConnectionId;
    UINT16              FlagNumber;
    UINT16              RsvdZ;
} HV_MONITOR_PARAMETER, *PHV_MONITOR_PARAMETER;

typedef union _HV_MONITOR_TRIGGER_STATE
{
    UINT32 AsUINT32;
        
    struct
    {
        UINT32 GroupEnable : 4;
        UINT32 RsvdZ       : 28;
    };

} HV_MONITOR_TRIGGER_STATE, *PHV_MONITOR_TRIGGER_STATE;

typedef struct _HV_MONITOR_PAGE
{
    HV_MONITOR_TRIGGER_STATE TriggerState;
    UINT32                   RsvdZ1;

    HV_MONITOR_TRIGGER_GROUP TriggerGroup[4];
    UINT64                   RsvdZ2[3]; // 64

    UINT16                   NextCheckTime[4][32]; // 256
    UINT64                   RsvdZ3[32]; // 256

    UINT16                   Latency[4][32]; // 256
    UINT64                   RsvdZ4[32]; // 256

    HV_MONITOR_PARAMETER     Parameter[4][32]; // 1024

    UINT8                    RsvdZ5[1984];

} HV_MONITOR_PAGE, *PHV_MONITOR_PAGE;

typedef volatile HV_MONITOR_PAGE* PVHV_MONITOR_PAGE;


//
// Debug channel identifier
//
typedef UINT16 HV_DEBUG_CHANNEL_IDENTIFIER;

//
// Maximum size of the payload
//
#define HV_DEBUG_MAXIMUM_DATA_SIZE 4088

//
// Debug options for all calls
//
typedef UINT32 HV_DEBUG_OPTIONS;

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
    UINT32 Count;
    HV_DEBUG_OPTIONS Options;
    UINT8 Data[HV_DEBUG_MAXIMUM_DATA_SIZE];
} HV_INPUT_POST_DEBUG_DATA, *PHV_INPUT_POST_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_POST_DEBUG_DATA
{
    UINT32 PendingCount;
} HV_OUTPUT_POST_DEBUG_DATA, *PHV_OUTPUT_POST_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RETRIEVE_DEBUG_DATA
{
    UINT32 Count;
    HV_DEBUG_OPTIONS Options;
    HV_NANO100_DURATION Timeout;
} HV_INPUT_RETRIEVE_DEBUG_DATA, *PHV_INPUT_RETRIEVE_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RETRIEVE_DEBUG_DATA
{
    UINT32 RetrievedCount;
    UINT32 RemainingCount;
    UINT8 Data[HV_DEBUG_MAXIMUM_DATA_SIZE];
} HV_OUTPUT_RETRIEVE_DEBUG_DATA, *PHV_OUTPUT_RETRIEVE_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESET_DEBUG_SESSION
{
    HV_DEBUG_OPTIONS Options;
} HV_INPUT_RESET_DEBUG_SESSION, *PHV_INPUT_RESET_DEBUG_SESSION;

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
    UINT32 Leader;
    UINT16 Type;
    UINT16 Length;
    UINT32 CRC;
    HV_DEBUG_CHANNEL_IDENTIFIER Channel;
    UINT16 Reserved;

} HV_MUX_PACKET_HEADER, *PHV_MUX_PACKET_HEADER;

//
// Channel data returned in a HV_MUX_PACKET_TYPE_QUERY_CHANNELS
// respone. The channelIds arrays is variable length array
// 

typedef struct {
    
    UINT32 Count;
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
// Define virtual processor execution state bitfield.
//
typedef union _HV_X64_VP_EXECUTION_STATE
{
    UINT16 AsUINT16;
    struct
    {
        UINT16 Cpl:2;
        UINT16 Cr0Pe:1;
        UINT16 Cr0Am:1;
        UINT16 EferLma:1;
        UINT16 DebugActive:1;
        UINT16 InterruptionPending:1;
        UINT16 Reserved:9;
    };
} HV_X64_VP_EXECUTION_STATE, *PHV_X64_VP_EXECUTION_STATE;


//
// Define intercept message header structure.
//
typedef struct _HV_X64_INTERCEPT_MESSAGE_HEADER
{
    HV_VP_INDEX VpIndex;
    UINT8 InstructionLength;
    HV_INTERCEPT_ACCESS_TYPE InterceptAccessType;
    HV_X64_VP_EXECUTION_STATE ExecutionState;
    HV_X64_SEGMENT_REGISTER CsSegment;
    UINT64 Rip;
    UINT64 Rflags;
} HV_X64_INTERCEPT_MESSAGE_HEADER, *PHV_X64_INTERCEPT_MESSAGE_HEADER;


//
// Define memory access information structure.
//
typedef union _HV_X64_MEMORY_ACCESS_INFO
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 GvaValid:1;
        UINT8 Reserved:7;
    };
} HV_X64_MEMORY_ACCESS_INFO, *PHV_X64_MEMORY_ACCESS_INFO;


//
// Define IO port access information structure.
//
typedef union _HV_X64_IO_PORT_ACCESS_INFO
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 AccessSize:3;
        UINT8 StringOp:1;
        UINT8 RepPrefix:1;
        UINT8 Reserved:3;
    };
} HV_X64_IO_PORT_ACCESS_INFO, *PHV_X64_IO_PORT_ACCESS_INFO;


//
// Define exception information structure.
//
typedef union _HV_X64_EXCEPTION_INFO
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 ErrorCodeValid:1;
        UINT8 Reserved:7;
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
    UINT8 InstructionByteCount;
    HV_X64_MEMORY_ACCESS_INFO MemoryAccessInfo;
    UINT16 Reserved1;
    UINT64 GuestVirtualAddress;
    UINT64 GuestPhysicalAddress;
    UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rbx;
    UINT64 Rsp;
    UINT64 Rbp;
    UINT64 Rsi;
    UINT64 Rdi;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;
} HV_X64_MEMORY_INTERCEPT_MESSAGE, *PHV_X64_MEMORY_INTERCEPT_MESSAGE;


//
// Define CPUID intercept message structure.
//
typedef struct _HV_X64_CPUID_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rbx;
    UINT64 DefaultResultRax;
    UINT64 DefaultResultRcx;
    UINT64 DefaultResultRdx;
    UINT64 DefaultResultRbx;
} HV_X64_CPUID_INTERCEPT_MESSAGE, *PHV_X64_CPUID_INTERCEPT_MESSAGE;


//
// Define MSR intercept message structure.
//
typedef struct _HV_X64_MSR_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT32 MsrNumber;
    UINT32 Reserved;
    UINT64 Rdx;
    UINT64 Rax;
} HV_X64_MSR_INTERCEPT_MESSAGE, *PHV_X64_MSR_INTERCEPT_MESSAGE;


//
// Define IO access intercept message structure.
//
typedef struct _HV_X64_IO_PORT_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT16 PortNumber;
    HV_X64_IO_PORT_ACCESS_INFO AccessInfo;
    UINT8 InstructionByteCount;
    UINT32 Reserved;
    UINT64 Rax;
    UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER EsSegment;
    UINT64 Rcx;
    UINT64 Rsi;
    UINT64 Rdi;
} HV_X64_IO_PORT_INTERCEPT_MESSAGE, *PHV_X64_IO_PORT_INTERCEPT_MESSAGE;


//
// Define exception intercept message.
//
typedef struct _HV_X64_EXCEPTION_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT16 ExceptionVector;
    HV_X64_EXCEPTION_INFO ExceptionInfo;
    UINT8 InstructionByteCount;
    UINT32 ErrorCode;
    UINT64 ExceptionParameter;
    UINT64 Reserved;
    UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rbx;
    UINT64 Rsp;
    UINT64 Rbp;
    UINT64 Rsi;
    UINT64 Rdi;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;
} HV_X64_EXCEPTION_INTERCEPT_MESSAGE, *PHV_X64_EXCEPTION_INTERCEPT_MESSAGE;


//
// Define legacy floating point error message.
//
typedef struct _HV_X64_LEGACY_FP_ERROR_MESSAGE
{
    UINT32 VpIndex;
    UINT32 Reserved;
} HV_X64_LEGACY_FP_ERROR_MESSAGE, *PHV_X64_LEGACY_FP_ERROR_MESSAGE;


//
// Define invalid virtual processor register message.
//
typedef struct _HV_X64_INVALID_VP_REGISTER_MESSAGE
{
    UINT32 VpIndex;
    UINT32 Reserved;
} HV_X64_INVALID_VP_REGISTER_MESSAGE, *PHV_X64_INVALID_VP_REGISTER_MESSAGE;


//
// Define virtual processor unrecoverable error message.
//
typedef struct _HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
} HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE, *PHV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE;


//
// Define unsupported feature message.
//
typedef struct _HV_X64_UNSUPPORTED_FEATURE_MESSAGE
{
    UINT32 VpIndex;
    UINT32 FeatureCode;
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

//
// Declare the MSR used to identify the guest OS.
//
#define HV_X64_MSR_GUEST_OS_ID 0x40000000

typedef union _HV_X64_MSR_GUEST_OS_ID_CONTENTS
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 BuildNumber    : 16;
        UINT64 ServiceVersion : 8; // Service Pack, etc.
        UINT64 MinorVersion   : 8;
        UINT64 MajorVersion   : 8;
        UINT64 OsId           : 8; // HV_GUEST_OS_MICROSOFT_IDS (If Vendor=MS)
        UINT64 VendorId       : 16; // HV_GUEST_OS_VENDOR
    };
} HV_X64_MSR_GUEST_OS_ID_CONTENTS, *PHV_X64_MSR_GUEST_OS_ID_CONTENTS;

//
// Declare the MSR used to setup pages used to communicate with the hypervisor.
//
#define HV_X64_MSR_HYPERCALL 0x40000001

typedef union _HV_X64_MSR_HYPERCALL_CONTENTS
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Enable               : 1;
        UINT64 Reserved             : 11;
        UINT64 GuestPhysicalAddress : 52;
    };
} HV_X64_MSR_HYPERCALL_CONTENTS, *PHV_X64_MSR_HYPERCALL_CONTENTS;


//
// Hypercall structures, enumerations, and constants.
// ==================================================
//

//
// Partition Properties
//
typedef UINT64 HV_PARTITION_PROPERTY, *PHV_PARTITION_PROPERTY;

typedef enum
{
    //
    // Privilege properties
    //
    HvPartitionPropertyPrivilegeFlags       = 0x00010000,

    //
    // Scheduling properties
    //
    HvPartitionPropertySchedulingControl    = 0x00020000,
    HvPartitionPropertyCpuReserve           = 0x00020001,
    HvPartitionPropertyCpuCap               = 0x00020002,
    HvPartitionPropertyCpuWeight            = 0x00020003,

    //
    // Timer assist properties
    //
    HvPartitionPropertyEmulatedTimerPeriod  = 0x00030000,
    HvPartitionPropertyEmulatedTimerControl = 0x00030001,
    HvPartitionPropertyPmTimerAssist        = 0x00030002,

    //
    // Debugging properties
    //
    HvPartitionPropertyDebugChannelId       = 0x00040000,

    //
    // Resource properties
    //
    HvPartitionPropertyVirtualTlbPageCount  = 0x00050000

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
    UINT64 Flags;
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
        UINT32 CallCode        : 16; // Least significant bits
        UINT32 IsFast          : 1;  // Uses the register based form
        UINT32 Reserved1       : 15;
        UINT32 CountOfElements : 12;
        UINT32 Reserved2       : 4;
        UINT32 RepStartIndex   : 12;
        UINT32 Reserved3       : 4;  // Most significant bits
    };
    UINT64 AsUINT64;

} HV_X64_HYPERCALL_INPUT, *PHV_X64_HYPERCALL_INPUT;

typedef union _HV_X64_HYPERCALL_OUTPUT
{
    //
    // Output: The result and returned data size
    //
    struct
    {
        HV_STATUS CallStatus;             // Least significant bits
        UINT16    Reserved1;
        UINT32    ElementsProcessed : 12;
        UINT32    Reserved2         : 20; // Most significant bits
    };
    UINT64 AsUINT64;

} HV_X64_HYPERCALL_OUTPUT, *PHV_X64_HYPERCALL_OUTPUT;

//
// Declare the various hypercall operations.
//
typedef enum _HV_CALL_CODE
{
    //
    // Reserved Feature Code
    //

    HvCallReserved0000                  = 0x0000,

    //
    // V1 Address space enlightment IDs
    //

    HvCallSwitchVirtualAddressSpace     = 0x0001,
    HvCallFlushVirtualAddressSpace      = 0x0002,
    HvCallFlushVirtualAddressList       = 0x0003,

    //
    // V1 Power Management and Run time metrics IDs
    //

    HvCallGetLogicalProcessorRunTime        = 0x0004,
    HvCallSetLogicalProcessorRunTimeGroup   = 0x0005,
    HvCallClearLogicalProcessorRunTimeGroup = 0x0006,
    HvCallNotifyLogicalProcessorPowerState  = 0x0007,

    //
    // V1 enlightenment name space reservation.
    //

    HvCallReserved0008                  = 0x0008,
    HvCallReserved0009                  = 0x0009,
    HvCallReserved000a                  = 0x000a,
    HvCallReserved000b                  = 0x000b,
    HvCallReserved000c                  = 0x000c,
    HvCallReserved000d                  = 0x000d,
    HvCallReserved000e                  = 0x000e,
    HvCallReserved000f                  = 0x000f,
    HvCallReserved0010                  = 0x0010,
    HvCallReserved0011                  = 0x0011,
    HvCallReserved0012                  = 0x0012,
    HvCallReserved0013                  = 0x0013,
    HvCallReserved0014                  = 0x0014,
    HvCallReserved0015                  = 0x0015,
    HvCallReserved0016                  = 0x0016,
    HvCallReserved0017                  = 0x0017,
    HvCallReserved0018                  = 0x0018,
    HvCallReserved0019                  = 0x0019,
    HvCallReserved001a                  = 0x001a,
    HvCallReserved001b                  = 0x001b,
    HvCallReserved001c                  = 0x001c,
    HvCallReserved001d                  = 0x001d,
    HvCallReserved001e                  = 0x001e,
    HvCallReserved001f                  = 0x001f,
    HvCallReserved0020                  = 0x0020,
    HvCallReserved0021                  = 0x0021,
    HvCallReserved0022                  = 0x0022,
    HvCallReserved0023                  = 0x0023,
    HvCallReserved0024                  = 0x0024,
    HvCallReserved0025                  = 0x0025,
    HvCallReserved0026                  = 0x0026,
    HvCallReserved0027                  = 0x0027,
    HvCallReserved0028                  = 0x0028,
    HvCallReserved0029                  = 0x0029,
    HvCallReserved002a                  = 0x002a,
    HvCallReserved002b                  = 0x002b,
    HvCallReserved002c                  = 0x002c,
    HvCallReserved002d                  = 0x002d,
    HvCallReserved002e                  = 0x002e,
    HvCallReserved002f                  = 0x002f,
    HvCallReserved0030                  = 0x0030,
    HvCallReserved0031                  = 0x0031,
    HvCallReserved0032                  = 0x0032,
    HvCallReserved0033                  = 0x0033,
    HvCallReserved0034                  = 0x0034,
    HvCallReserved0035                  = 0x0035,
    HvCallReserved0036                  = 0x0036,
    HvCallReserved0037                  = 0x0037,
    HvCallReserved0038                  = 0x0038,
    HvCallReserved0039                  = 0x0039,
    HvCallReserved003a                  = 0x003a,
    HvCallReserved003b                  = 0x003b,
    HvCallReserved003c                  = 0x003c,
    HvCallReserved003d                  = 0x003d,
    HvCallReserved003e                  = 0x003e,
    HvCallReserved003f                  = 0x003f,

    //
    // V1 Partition Management IDs
    //

    HvCallCreatePartition               = 0x0040,
    HvCallInitializePartition           = 0x0041,
    HvCallFinalizePartition             = 0x0042,
    HvCallDeletePartition               = 0x0043,
    HvCallGetPartitionProperty          = 0x0044,
    HvCallSetPartitionProperty          = 0x0045,
    HvCallGetPartitionId                = 0x0046,
    HvCallGetNextChildPartition         = 0x0047,

    //
    // V1 Resource Management IDs
    //

    HvCallDepositMemory                 = 0x0048,
    HvCallWithdrawMemory                = 0x0049,
    HvCallGetMemoryBalance              = 0x004a,

    //
    // V1 Guest Physical Address Space Management IDs
    //

    HvCallMapGpaPages                   = 0x004b,
    HvCallUnmapGpaPages                 = 0x004c,

    //
    // V1 Intercept Management IDs
    //

    HvCallInstallIntercept              = 0x004d,

    //
    // V1 Virtual Processor Management IDs
    //

    HvCallCreateVp                      = 0x004e,
    HvCallDeleteVp                      = 0x004f,
    HvCallGetVpRegisters                = 0x0050,
    HvCallSetVpRegisters                = 0x0051,

    //
    // V1 Virtual TLB IDs
    //

    HvCallTranslateVirtualAddress       = 0x0052,
    HvCallReadGpa                       = 0x0053,
    HvCallWriteGpa                      = 0x0054,

    //
    // V1 Interrupt Management IDs
    //

    HvCallAssertVirtualInterrupt        = 0x0055,
    HvCallClearVirtualInterrupt         = 0x0056,

    //
    // V1 Port IDs
    //

    HvCallCreatePort                    = 0x0057,
    HvCallDeletePort                    = 0x0058,
    HvCallConnectPort                   = 0x0059,
    HvCallGetPortProperty               = 0x005a,
    HvCallDisconnectPort                = 0x005b,
    HvCallPostMessage                   = 0x005c,
    HvCallSignalEvent                   = 0x005d,

    //
    // V1 Partition State IDs
    //

    HvCallSavePartitionState            = 0x005e,
    HvCallRestorePartitionState         = 0x005f,

    //
    // V1 Trace IDs
    //

    HvCallInitializeEventLogBufferGroup  = 0x0060,
    HvCallFinalizeEventLogBufferGroup   = 0x0061,
    HvCallCreateEventLogBuffer          = 0x0062,
    HvCallDeleteEventLogBuffer          = 0x0063,
    HvCallMapEventLogBuffer             = 0x0064,
    HvCallUnmapEventLogBuffer           = 0x0065,
    HvCallSetEventLogGroupSources       = 0x0066,
    HvCallReleaseEventLogBuffer         = 0x0067,
    HvCallRequestEventLogGroupFlush     = 0x0068,

    //
    // V1 Dbg Call IDs
    //

    HvCallPostDebugData                 = 0x0069,
    HvCallRetrieveDebugData             = 0x006a,
    HvCallResetDebugSession             = 0x006b,

    //
    // V1 Stats IDs
    //

    HvCallMapStatsPage                  = 0x006c,
    HvCallUnmapStatsPage                = 0x006d,

    //
    // V1 Test IDs
    //

    HvCallOutputDebugCharacter,
    HvCallEchoIncrement,
    HvCallPerfNop,
    HvCallPerfNopInput,
    HvCallPerfNopOutput,

    //
    // Total of all V1 hypercalls
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
    UINT64 PagesAvailable;

    //
    // Returns the number of pages actively being used for hypercall
    // datastructures.
    //
    UINT64 PagesInUse;

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

    UINT32 ByteCount;

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

    UINT8 Data[16];

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

    UINT32 ByteCount;

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

    UINT8 Data[16];

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
    UINT32                   Padding;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    UINT64                   Flags;
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

typedef enum _HV_REGISTER_NAME
{
    // Suspend Registers
    HvRegisterExplicitSuspend   = 0x00000000,
    HvRegisterInterceptSuspend  = 0x00000001,

    // Pending Interruption Register
    HvX64RegisterPendingInterruption    = 0x00010002,

    // Interrupt State register
    HvX64RegisterInterruptState         = 0x00010003,

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
    HvX64RegisterMsrMtrrCap         = 0x0008000D,
    HvX64RegisterMsrMtrrDefType     = 0x0008000E,
    HvX64RegisterMsrMtrrPhysBase0   = 0x00080010,
    HvX64RegisterMsrMtrrPhysBase1   = 0x00080011,
    HvX64RegisterMsrMtrrPhysBase2   = 0x00080012,
    HvX64RegisterMsrMtrrPhysBase3   = 0x00080013,
    HvX64RegisterMsrMtrrPhysBase4   = 0x00080014,
    HvX64RegisterMsrMtrrPhysBase5   = 0x00080015,
    HvX64RegisterMsrMtrrPhysBase6   = 0x00080016,
    HvX64RegisterMsrMtrrPhysBase7   = 0x00080017,
    HvX64RegisterMsrMtrrPhysMask0   = 0x00080040,
    HvX64RegisterMsrMtrrPhysMask1   = 0x00080041,
    HvX64RegisterMsrMtrrPhysMask2   = 0x00080042,
    HvX64RegisterMsrMtrrPhysMask3   = 0x00080043,
    HvX64RegisterMsrMtrrPhysMask4   = 0x00080044,
    HvX64RegisterMsrMtrrPhysMask5   = 0x00080045,
    HvX64RegisterMsrMtrrPhysMask6   = 0x00080046,
    HvX64RegisterMsrMtrrPhysMask7   = 0x00080047,
    HvX64RegisterMsrMtrrFix64k00000 = 0x00080070,
    HvX64RegisterMsrMtrrFix16k80000 = 0x00080071,
    HvX64RegisterMsrMtrrFix16kA0000 = 0x00080072,
    HvX64RegisterMsrMtrrFix4kC0000  = 0x00080073,
    HvX64RegisterMsrMtrrFix4kC8000  = 0x00080074,
    HvX64RegisterMsrMtrrFix4kD0000  = 0x00080075,
    HvX64RegisterMsrMtrrFix4kD8000  = 0x00080076,
    HvX64RegisterMsrMtrrFix4kE0000  = 0x00080077,
    HvX64RegisterMsrMtrrFix4kE8000  = 0x00080078,
    HvX64RegisterMsrMtrrFix4kF0000  = 0x00080079,
    HvX64RegisterMsrMtrrFix4kF8000  = 0x0008007A,

    // Hypervisor-defined MSRs (Misc)
    HvX64RegisterHypervisorPresent  = 0x00090000,
    HvX64RegisterHypercall          = 0x00090001,
    HvX64RegisterGuestOsId          = 0x00090002,
    HvX64RegisterVpIndex            = 0x00090003,
    HvX64RegisterVpRuntime          = 0x00090004,

    // Hypervisor-defined MSRs (Synic)
    HvX64RegisterSint0              = 0x000A0000,
    HvX64RegisterSint1              = 0x000A0001,
    HvX64RegisterSint2              = 0x000A0002,
    HvX64RegisterSint3              = 0x000A0003,
    HvX64RegisterSint4              = 0x000A0004,
    HvX64RegisterSint5              = 0x000A0005,
    HvX64RegisterSint6              = 0x000A0006,
    HvX64RegisterSint7              = 0x000A0007,
    HvX64RegisterSint8              = 0x000A0008,
    HvX64RegisterSint9              = 0x000A0009,
    HvX64RegisterSint10             = 0x000A000A,
    HvX64RegisterSint11             = 0x000A000B,
    HvX64RegisterSint12             = 0x000A000C,
    HvX64RegisterSint13             = 0x000A000D,
    HvX64RegisterSint14             = 0x000A000E,
    HvX64RegisterSint15             = 0x000A000F,
    HvX64RegisterSynicBase          = 0x000A0010,
    HvX64RegisterSversion           = 0x000A0011,
    HvX64RegisterSifp               = 0x000A0012,
    HvX64RegisterSipp               = 0x000A0013,
    HvX64RegisterEom                = 0x000A0014,

    // Hypervisor-defined MSRs (Synthetic Timers)
    HvX64RegisterStimer0Config      = 0x000B0000,
    HvX64RegisterStimer0Count       = 0x000B0001,
    HvX64RegisterStimer1Config      = 0x000B0002,
    HvX64RegisterStimer1Count       = 0x000B0003,
    HvX64RegisterStimer2Config      = 0x000B0004,
    HvX64RegisterStimer2Count       = 0x000B0005,
    HvX64RegisterStimer3Config      = 0x000B0006,
    HvX64RegisterStimer3Count       = 0x000B0007

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
    HV_REGISTER_NAME    Names[];
} HV_INPUT_GET_VP_REGISTERS, *PHV_INPUT_GET_VP_REGISTERS;

typedef struct _HV_REGISTER_ASSOC
{
    HV_REGISTER_NAME    Name;
    UINT32              Pad;
    HV_REGISTER_VALUE   Value;
} HV_REGISTER_ASSOC, *PHV_REGISTER_ASSOC;

typedef struct HV_CALL_ATTRIBUTES_ALIGNED(16) _HV_INPUT_SET_VP_REGISTERS
{
    HV_PARTITION_ID      PartitionId;
    HV_VP_INDEX          VpIndex;
    UINT32               RsvdZ;
    HV_REGISTER_ASSOC    Elements[];
} HV_INPUT_SET_VP_REGISTERS, *PHV_INPUT_SET_VP_REGISTERS;

//
// Definition of the HvCallGetVpRegisterCode hypercall input
// structure.  This call retrieves the valid Vp register codes.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_REGISTER_CODE
{
    HV_PARTITION_ID PartitionId;
    UINT32          RegisterIndex;
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
    UINT64              ProcessorMask;
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
    UINT64                  DestinationAddress;
    HV_INTERRUPT_VECTOR     RequestedVector;
    UINT32                  Reserved;
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
    UINT32              Padding;
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
    UINT32          Reserved;
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
    UINT32              Reserved1;
    HV_PARTITION_ID     PortPartition;
    HV_PORT_ID          PortId;
    UINT32              Reserved2;
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
    UINT32                Reserved;
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
    UINT32              Reserved;
} HV_INPUT_DISCONNECT_PORT, *PHV_INPUT_DISCONNECT_PORT;

//
// Definition of the HvPostMessage hypercall input structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_POST_MESSAGE
{
    HV_CONNECTION_ID    ConnectionId;
    UINT32              Reserved;
    HV_MESSAGE_TYPE     MessageType;
    UINT32              PayloadSize;
    UINT64              Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
} HV_INPUT_POST_MESSAGE, *PHV_INPUT_POST_MESSAGE;


//
// Definition of the HvSignalEvent hypercall input structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SIGNAL_EVENT
{
    HV_CONNECTION_ID ConnectionId;
    UINT16           FlagNumber;
    UINT16           RsvdZ;
} HV_INPUT_SIGNAL_EVENT, *PHV_INPUT_SIGNAL_EVENT;

//
// Define the scheduler run time hypercall input/output structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME
{
    HV_NANO100_TIME GlobalTime;
    HV_NANO100_TIME LocalRunTime;
    HV_NANO100_TIME GroupRunTime;
    HV_NANO100_TIME HypervisorTime;
} HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME,
  *PHV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME;


typedef struct HV_CALL_ATTRIBUTES
_HV_INPUT_SET_LOGICAL_PROCESSOR_RUN_TIME_GROUP
{
    UINT64 Flags;      // Reserved Zeroes.
    UINT64 ProcessorMask;
} HV_INPUT_SET_LOGICAL_PROCESSOR_RUN_TIME_GROUP,
  *PHV_INPUT_SET_LOGICAL_PROCESSOR_RUN_TIME_GROUP;


typedef struct HV_CALL_ATTRIBUTES
_HV_INPUT_CLEAR_LOGICAL_PROCESSOR_RUN_TIME_GROUP
{
    HV_VP_INDEX VpIndex;
} HV_INPUT_CLEAR_LOGICAL_PROCESSOR_RUN_TIME_GROUP,
  *PHV_INPUT_CLEAR_LOGICAL_PROCESSOR_RUN_TIME_GROUP;


//
// External logical processor power states
//
typedef enum _HV_LOGICAL_PROCESSOR_POWER_STATE
{
    HvPowerStateRunning  = 0x00000000,
    HvPowerStateLowPower = 0x00000001,
    HvPowerStateOffline  = 0xFFFFFFFF

} HV_LOGICAL_PROCESSOR_POWER_STATE, *PHV_LOGICAL_PROCESSOR_POWER_STATE;

typedef struct HV_CALL_ATTRIBUTES
_HV_INPUT_NOTIFY_LOGICAL_PROCESSOR_POWER_STATE
{
    UINT32 PowerState;
    UINT32 Pad;
} HV_INPUT_NOTIFY_LOGICAL_PROCESSOR_POWER_STATE,
  *PHV_INPUT_NOTIFY_LOGICAL_PROCESSOR_POWER_STATE;

//
// Definition of the HvGetNextLogicalProcessor hypercall input and
// output structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_NEXT_LOGICAL_PROCESSOR
{
    HV_LOGICAL_PROCESSOR_INDEX SearchStartIndex;
} HV_INPUT_GET_NEXT_LOGICAL_PROCESSOR, *PHV_INPUT_GET_NEXT_LOGICAL_PROCESSOR;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_NEXT_LOGICAL_PROCESSOR
{
    HV_LOGICAL_PROCESSOR_INDEX LogicalProcessorIndex;
    HV_PHYSICAL_NODE_INDEX PhysicalNode;
} HV_OUTPUT_GET_NEXT_LOGICAL_PROCESSOR, *PHV_OUTPUT_GET_NEXT_LOGICAL_PROCESSOR;

//
// Definition of the HvGetNextRamPageRange hypercall input and output
// structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_NEXT_RAM_PAGE_RANGE
{
    HV_SPA_PAGE_NUMBER SearchStart;
} HV_INPUT_GET_NEXT_RAM_PAGE_RANGE, *PHV_INPUT_GET_NEXT_RAM_PAGE_RANGE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_NEXT_RAM_PAGE_RANGE
{
    HV_SPA_PAGE_NUMBER RangeStart;
    UINT64 PageCount;
    HV_PHYSICAL_NODE_INDEX PhysicalNode;
} HV_OUTPUT_GET_NEXT_RAM_PAGE_RANGE, *PHV_OUTPUT_GET_NEXT_RAM_PAGE_RANGE;

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
    UINT32 SaveDataCount;
    HV_SAVE_RESTORE_STATE_RESULT SaveState;
    UINT8 SaveData[4080];
} HV_OUTPUT_SAVE_PARTITION_STATE, *PHV_OUTPUT_SAVE_PARTITION_STATE;

//
// Definition of the HvRestorePartitionState hypercall input and
// output structures.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESTORE_PARTITION_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_SAVE_RESTORE_STATE_FLAGS Flags;
    UINT32 RestoreDataCount;
    UINT8 RestoreData[4080];
} HV_INPUT_RESTORE_PARTITION_STATE, *PHV_INPUT_RESTORE_PARTITION_STATE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RESTORE_PARTITION_STATE
{
    HV_SAVE_RESTORE_STATE_RESULT RestoreState;
    UINT32 RestoreDataConsumed;
} HV_OUTPUT_RESTORE_PARTITION_STATE, *PHV_OUTPUT_RESTORE_PARTITION_STATE;

//
// Definition of the HvSpecifyPreferredAffinity hypercall input
// structure.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SPECIFY_PREFERRED_AFFINITY
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_LOGICAL_PROCESSOR_INDEX PreferredAffinity;
} HV_INPUT_SPECIFY_PREFERRED_AFFINITY, *PHV_INPUT_SPECIFY_PREFERRED_AFFINITY;

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
        UINT64  ReservedZ1[2];
    } Hypervisor;

    //
    // HvStatsObjectLogicalProcessor
    //

    struct
    {
        HV_LOGICAL_PROCESSOR_INDEX      LogicalProcessorIndex;
        UINT32                          ReservedZ2;
        UINT64                          ReservedZ3;
    } LogicalProcessor;

    //
    // HvStatsObjectPartition
    //

    struct
    {
        HV_PARTITION_ID PartitionId;
        UINT64          ReservedZ4;
    } Partition;

    //
    // HvStatsObjectVp
    //

    struct
    {
        HV_PARTITION_ID PartitionId;
        HV_VP_INDEX     VpIndex;
        UINT32          ReservedZ5;
    } Vp;

} HV_STATS_OBJECT_IDENTITY;

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
} HV_INPUT_UNMAP_STATS_PAGE, *PHV_INPUT_UNMAP_STATS_PAGE;
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4200)
#pragma warning(default:4201)
#pragma warning(default:4214)
#pragma warning(default:4324)
#endif

#endif //_HVGDK_
