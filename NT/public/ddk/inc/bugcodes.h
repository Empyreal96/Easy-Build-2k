/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1991  Microsoft Corporation

Module Name:

    bugcodes.h

Abstract:

    This module contains the definition of the system bug check codes.

Author:

    David N. Cutler (davec) 2-May-1989

Revision History:

Notes:

    This file is generated by the MC tool from the ntos\nls\bugcodes.msg
    file.

--*/

#ifndef _BUGCODES_
#define _BUGCODES_


//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: APC_INDEX_MISMATCH
//
// MessageText:
//
//  APC_INDEX_MISMATCH
//
#define APC_INDEX_MISMATCH               ((ULONG)0x00000001L)

//
// MessageId: DEVICE_QUEUE_NOT_BUSY
//
// MessageText:
//
//  DEVICE_QUEUE_NOT_BUSY
//
#define DEVICE_QUEUE_NOT_BUSY            ((ULONG)0x00000002L)

//
// MessageId: INVALID_AFFINITY_SET
//
// MessageText:
//
//  INVALID_AFFINITY_SET
//
#define INVALID_AFFINITY_SET             ((ULONG)0x00000003L)

//
// MessageId: INVALID_DATA_ACCESS_TRAP
//
// MessageText:
//
//  INVALID_DATA_ACCESS_TRAP
//
#define INVALID_DATA_ACCESS_TRAP         ((ULONG)0x00000004L)

//
// MessageId: INVALID_PROCESS_ATTACH_ATTEMPT
//
// MessageText:
//
//  INVALID_PROCESS_ATTACH_ATTEMPT
//
#define INVALID_PROCESS_ATTACH_ATTEMPT   ((ULONG)0x00000005L)

//
// MessageId: INVALID_PROCESS_DETACH_ATTEMPT
//
// MessageText:
//
//  INVALID_PROCESS_DETACH_ATTEMPT
//
#define INVALID_PROCESS_DETACH_ATTEMPT   ((ULONG)0x00000006L)

//
// MessageId: INVALID_SOFTWARE_INTERRUPT
//
// MessageText:
//
//  INVALID_SOFTWARE_INTERRUPT
//
#define INVALID_SOFTWARE_INTERRUPT       ((ULONG)0x00000007L)

//
// MessageId: IRQL_NOT_DISPATCH_LEVEL
//
// MessageText:
//
//  IRQL_NOT_DISPATCH_LEVEL
//
#define IRQL_NOT_DISPATCH_LEVEL          ((ULONG)0x00000008L)

//
// MessageId: IRQL_NOT_GREATER_OR_EQUAL
//
// MessageText:
//
//  IRQL_NOT_GREATER_OR_EQUAL
//
#define IRQL_NOT_GREATER_OR_EQUAL        ((ULONG)0x00000009L)

//
// MessageId: IRQL_NOT_LESS_OR_EQUAL
//
// MessageText:
//
//  IRQL_NOT_LESS_OR_EQUAL
//
#define IRQL_NOT_LESS_OR_EQUAL           ((ULONG)0x0000000AL)

//
// MessageId: NO_EXCEPTION_HANDLING_SUPPORT
//
// MessageText:
//
//  NO_EXCEPTION_HANDLING_SUPPORT
//
#define NO_EXCEPTION_HANDLING_SUPPORT    ((ULONG)0x0000000BL)

//
// MessageId: MAXIMUM_WAIT_OBJECTS_EXCEEDED
//
// MessageText:
//
//  MAXIMUM_WAIT_OBJECTS_EXCEEDED
//
#define MAXIMUM_WAIT_OBJECTS_EXCEEDED    ((ULONG)0x0000000CL)

//
// MessageId: MUTEX_LEVEL_NUMBER_VIOLATION
//
// MessageText:
//
//  MUTEX_LEVEL_NUMBER_VIOLATION
//
#define MUTEX_LEVEL_NUMBER_VIOLATION     ((ULONG)0x0000000DL)

//
// MessageId: NO_USER_MODE_CONTEXT
//
// MessageText:
//
//  NO_USER_MODE_CONTEXT
//
#define NO_USER_MODE_CONTEXT             ((ULONG)0x0000000EL)

//
// MessageId: SPIN_LOCK_ALREADY_OWNED
//
// MessageText:
//
//  SPIN_LOCK_ALREADY_OWNED
//
#define SPIN_LOCK_ALREADY_OWNED          ((ULONG)0x0000000FL)

//
// MessageId: SPIN_LOCK_NOT_OWNED
//
// MessageText:
//
//  SPIN_LOCK_NOT_OWNED
//
#define SPIN_LOCK_NOT_OWNED              ((ULONG)0x00000010L)

//
// MessageId: THREAD_NOT_MUTEX_OWNER
//
// MessageText:
//
//  THREAD_NOT_MUTEX_OWNER
//
#define THREAD_NOT_MUTEX_OWNER           ((ULONG)0x00000011L)

//
// MessageId: TRAP_CAUSE_UNKNOWN
//
// MessageText:
//
//  TRAP_CAUSE_UNKNOWN
//
#define TRAP_CAUSE_UNKNOWN               ((ULONG)0x00000012L)

//
// MessageId: EMPTY_THREAD_REAPER_LIST
//
// MessageText:
//
//  EMPTY_THREAD_REAPER_LIST
//
#define EMPTY_THREAD_REAPER_LIST         ((ULONG)0x00000013L)

//
// MessageId: CREATE_DELETE_LOCK_NOT_LOCKED
//
// MessageText:
//
//  The thread reaper was handed a thread to reap, but the thread's process'
//
#define CREATE_DELETE_LOCK_NOT_LOCKED    ((ULONG)0x00000014L)

//
// MessageId: LAST_CHANCE_CALLED_FROM_KMODE
//
// MessageText:
//
//  LAST_CHANCE_CALLED_FROM_KMODE
//
#define LAST_CHANCE_CALLED_FROM_KMODE    ((ULONG)0x00000015L)

//
// MessageId: CID_HANDLE_CREATION
//
// MessageText:
//
//  CID_HANDLE_CREATION
//
#define CID_HANDLE_CREATION              ((ULONG)0x00000016L)

//
// MessageId: CID_HANDLE_DELETION
//
// MessageText:
//
//  CID_HANDLE_DELETION
//
#define CID_HANDLE_DELETION              ((ULONG)0x00000017L)

//
// MessageId: REFERENCE_BY_POINTER
//
// MessageText:
//
//  REFERENCE_BY_POINTER
//
#define REFERENCE_BY_POINTER             ((ULONG)0x00000018L)

//
// MessageId: BAD_POOL_HEADER
//
// MessageText:
//
//  BAD_POOL_HEADER
//
#define BAD_POOL_HEADER                  ((ULONG)0x00000019L)

//
// MessageId: MEMORY_MANAGEMENT
//
// MessageText:
//
//  MEMORY_MANAGEMENT
//
#define MEMORY_MANAGEMENT                ((ULONG)0x0000001AL)

//
// MessageId: PFN_SHARE_COUNT
//
// MessageText:
//
//  PFN_SHARE_COUNT
//
#define PFN_SHARE_COUNT                  ((ULONG)0x0000001BL)

//
// MessageId: PFN_REFERENCE_COUNT
//
// MessageText:
//
//  PFN_REFERENCE_COUNT
//
#define PFN_REFERENCE_COUNT              ((ULONG)0x0000001CL)

//
// MessageId: NO_SPIN_LOCK_AVAILABLE
//
// MessageText:
//
//  NO_SPIN_LOCK_AVAILABLE
//
#define NO_SPIN_LOCK_AVAILABLE           ((ULONG)0x0000001DL)

//
// MessageId: KMODE_EXCEPTION_NOT_HANDLED
//
// MessageText:
//
//  KMODE_EXCEPTION_NOT_HANDLED
//
#define KMODE_EXCEPTION_NOT_HANDLED      ((ULONG)0x0000001EL)

//
// MessageId: SHARED_RESOURCE_CONV_ERROR
//
// MessageText:
//
//  SHARED_RESOURCE_CONV_ERROR
//
#define SHARED_RESOURCE_CONV_ERROR       ((ULONG)0x0000001FL)

//
// MessageId: KERNEL_APC_PENDING_DURING_EXIT
//
// MessageText:
//
//  KERNEL_APC_PENDING_DURING_EXIT
//
#define KERNEL_APC_PENDING_DURING_EXIT   ((ULONG)0x00000020L)

//
// MessageId: QUOTA_UNDERFLOW
//
// MessageText:
//
//  QUOTA_UNDERFLOW
//
#define QUOTA_UNDERFLOW                  ((ULONG)0x00000021L)

//
// MessageId: FILE_SYSTEM
//
// MessageText:
//
//  FILE_SYSTEM
//
#define FILE_SYSTEM                      ((ULONG)0x00000022L)

//
// MessageId: FAT_FILE_SYSTEM
//
// MessageText:
//
//  FAT_FILE_SYSTEM
//
#define FAT_FILE_SYSTEM                  ((ULONG)0x00000023L)

//
// MessageId: NTFS_FILE_SYSTEM
//
// MessageText:
//
//  NTFS_FILE_SYSTEM
//
#define NTFS_FILE_SYSTEM                 ((ULONG)0x00000024L)

//
// MessageId: NPFS_FILE_SYSTEM
//
// MessageText:
//
//  NPFS_FILE_SYSTEM
//
#define NPFS_FILE_SYSTEM                 ((ULONG)0x00000025L)

//
// MessageId: CDFS_FILE_SYSTEM
//
// MessageText:
//
//  CDFS_FILE_SYSTEM
//
#define CDFS_FILE_SYSTEM                 ((ULONG)0x00000026L)

//
// MessageId: RDR_FILE_SYSTEM
//
// MessageText:
//
//  RDR_FILE_SYSTEM
//
#define RDR_FILE_SYSTEM                  ((ULONG)0x00000027L)

//
// MessageId: CORRUPT_ACCESS_TOKEN
//
// MessageText:
//
//  CORRUPT_ACCESS_TOKEN
//
#define CORRUPT_ACCESS_TOKEN             ((ULONG)0x00000028L)

//
// MessageId: SECURITY_SYSTEM
//
// MessageText:
//
//  SECURITY_SYSTEM
//
#define SECURITY_SYSTEM                  ((ULONG)0x00000029L)

//
// MessageId: INCONSISTENT_IRP
//
// MessageText:
//
//  INCONSISTENT_IRP
//
#define INCONSISTENT_IRP                 ((ULONG)0x0000002AL)

//
// MessageId: PANIC_STACK_SWITCH
//
// MessageText:
//
//  PANIC_STACK_SWITCH
//
#define PANIC_STACK_SWITCH               ((ULONG)0x0000002BL)

//
// MessageId: PORT_DRIVER_INTERNAL
//
// MessageText:
//
//  PORT_DRIVER_INTERNAL
//
#define PORT_DRIVER_INTERNAL             ((ULONG)0x0000002CL)

//
// MessageId: SCSI_DISK_DRIVER_INTERNAL
//
// MessageText:
//
//  SCSI_DISK_DRIVER_INTERNAL
//
#define SCSI_DISK_DRIVER_INTERNAL        ((ULONG)0x0000002DL)

//
// MessageId: DATA_BUS_ERROR
//
// MessageText:
//
//  DATA_BUS_ERROR
//
#define DATA_BUS_ERROR                   ((ULONG)0x0000002EL)

//
// MessageId: INSTRUCTION_BUS_ERROR
//
// MessageText:
//
//  INSTRUCTION_BUS_ERROR
//
#define INSTRUCTION_BUS_ERROR            ((ULONG)0x0000002FL)

//
// MessageId: SET_OF_INVALID_CONTEXT
//
// MessageText:
//
//  SET_OF_INVALID_CONTEXT
//
#define SET_OF_INVALID_CONTEXT           ((ULONG)0x00000030L)

//
// MessageId: PHASE0_INITIALIZATION_FAILED
//
// MessageText:
//
//  PHASE0_INITIALIZATION_FAILED
//
#define PHASE0_INITIALIZATION_FAILED     ((ULONG)0x00000031L)

//
// MessageId: PHASE1_INITIALIZATION_FAILED
//
// MessageText:
//
//  PHASE1_INITIALIZATION_FAILED
//
#define PHASE1_INITIALIZATION_FAILED     ((ULONG)0x00000032L)

//
// MessageId: UNEXPECTED_INITIALIZATION_CALL
//
// MessageText:
//
//  UNEXPECTED_INITIALIZATION_CALL
//
#define UNEXPECTED_INITIALIZATION_CALL   ((ULONG)0x00000033L)

//
// MessageId: CACHE_MANAGER
//
// MessageText:
//
//  CACHE_MANAGER
//
#define CACHE_MANAGER                    ((ULONG)0x00000034L)

//
// MessageId: NO_MORE_IRP_STACK_LOCATIONS
//
// MessageText:
//
//  NO_MORE_IRP_STACK_LOCATIONS
//
#define NO_MORE_IRP_STACK_LOCATIONS      ((ULONG)0x00000035L)

//
// MessageId: DEVICE_REFERENCE_COUNT_NOT_ZERO
//
// MessageText:
//
//  DEVICE_REFERENCE_COUNT_NOT_ZERO
//
#define DEVICE_REFERENCE_COUNT_NOT_ZERO  ((ULONG)0x00000036L)

//
// MessageId: FLOPPY_INTERNAL_ERROR
//
// MessageText:
//
//  FLOPPY_INTERNAL_ERROR
//
#define FLOPPY_INTERNAL_ERROR            ((ULONG)0x00000037L)

//
// MessageId: SERIAL_DRIVER_INTERNAL
//
// MessageText:
//
//  SERIAL_DRIVER_INTERNAL
//
#define SERIAL_DRIVER_INTERNAL           ((ULONG)0x00000038L)

//
// MessageId: SYSTEM_EXIT_OWNED_MUTEX
//
// MessageText:
//
//  SYSTEM_EXIT_OWNED_MUTEX
//
#define SYSTEM_EXIT_OWNED_MUTEX          ((ULONG)0x00000039L)

//
// MessageId: SYSTEM_UNWIND_PREVIOUS_USER
//
// MessageText:
//
//  SYSTEM_UNWIND_PREVIOUS_USER
//
#define SYSTEM_UNWIND_PREVIOUS_USER      ((ULONG)0x0000003AL)

//
// MessageId: SYSTEM_SERVICE_EXCEPTION
//
// MessageText:
//
//  SYSTEM_SERVICE_EXCEPTION
//
#define SYSTEM_SERVICE_EXCEPTION         ((ULONG)0x0000003BL)

//
// MessageId: INTERRUPT_UNWIND_ATTEMPTED
//
// MessageText:
//
//  INTERRUPT_UNWIND_ATTEMPTED
//
#define INTERRUPT_UNWIND_ATTEMPTED       ((ULONG)0x0000003CL)

//
// MessageId: INTERRUPT_EXCEPTION_NOT_HANDLED
//
// MessageText:
//
//  INTERRUPT_EXCEPTION_NOT_HANDLED
//
#define INTERRUPT_EXCEPTION_NOT_HANDLED  ((ULONG)0x0000003DL)

//
// MessageId: MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED
//
// MessageText:
//
//  MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED
//
#define MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED ((ULONG)0x0000003EL)

//
// MessageId: NO_MORE_SYSTEM_PTES
//
// MessageText:
//
//  NO_MORE_SYSTEM_PTES
//
#define NO_MORE_SYSTEM_PTES              ((ULONG)0x0000003FL)

//
// MessageId: TARGET_MDL_TOO_SMALL
//
// MessageText:
//
//  TARGET_MDL_TOO_SMALL
//
#define TARGET_MDL_TOO_SMALL             ((ULONG)0x00000040L)

//
// MessageId: MUST_SUCCEED_POOL_EMPTY
//
// MessageText:
//
//  MUST_SUCCEED_POOL_EMPTY
//
#define MUST_SUCCEED_POOL_EMPTY          ((ULONG)0x00000041L)

//
// MessageId: ATDISK_DRIVER_INTERNAL
//
// MessageText:
//
//  ATDISK_DRIVER_INTERNAL
//
#define ATDISK_DRIVER_INTERNAL           ((ULONG)0x00000042L)

//
// MessageId: NO_SUCH_PARTITION
//
// MessageText:
//
//  NO_SUCH_PARTITION
//
#define NO_SUCH_PARTITION                ((ULONG)0x00000043L)

//
// MessageId: MULTIPLE_IRP_COMPLETE_REQUESTS
//
// MessageText:
//
//  MULTIPLE_IRP_COMPLETE_REQUESTS
//
#define MULTIPLE_IRP_COMPLETE_REQUESTS   ((ULONG)0x00000044L)

//
// MessageId: INSUFFICIENT_SYSTEM_MAP_REGS
//
// MessageText:
//
//  INSUFFICIENT_SYSTEM_MAP_REGS
//
#define INSUFFICIENT_SYSTEM_MAP_REGS     ((ULONG)0x00000045L)

//
// MessageId: DEREF_UNKNOWN_LOGON_SESSION
//
// MessageText:
//
//  DEREF_UNKNOWN_LOGON_SESSION
//
#define DEREF_UNKNOWN_LOGON_SESSION      ((ULONG)0x00000046L)

//
// MessageId: REF_UNKNOWN_LOGON_SESSION
//
// MessageText:
//
//  REF_UNKNOWN_LOGON_SESSION
//
#define REF_UNKNOWN_LOGON_SESSION        ((ULONG)0x00000047L)

//
// MessageId: CANCEL_STATE_IN_COMPLETED_IRP
//
// MessageText:
//
//  CANCEL_STATE_IN_COMPLETED_IRP
//
#define CANCEL_STATE_IN_COMPLETED_IRP    ((ULONG)0x00000048L)

//
// MessageId: PAGE_FAULT_WITH_INTERRUPTS_OFF
//
// MessageText:
//
//  PAGE_FAULT_WITH_INTERRUPTS_OFF
//
#define PAGE_FAULT_WITH_INTERRUPTS_OFF   ((ULONG)0x00000049L)

//
// MessageId: IRQL_GT_ZERO_AT_SYSTEM_SERVICE
//
// MessageText:
//
//  IRQL_GT_ZERO_AT_SYSTEM_SERVICE
//
#define IRQL_GT_ZERO_AT_SYSTEM_SERVICE   ((ULONG)0x0000004AL)

//
// MessageId: STREAMS_INTERNAL_ERROR
//
// MessageText:
//
//  STREAMS_INTERNAL_ERROR
//
#define STREAMS_INTERNAL_ERROR           ((ULONG)0x0000004BL)

//
// MessageId: FATAL_UNHANDLED_HARD_ERROR
//
// MessageText:
//
//  FATAL_UNHANDLED_HARD_ERROR
//
#define FATAL_UNHANDLED_HARD_ERROR       ((ULONG)0x0000004CL)

//
// MessageId: NO_PAGES_AVAILABLE
//
// MessageText:
//
//  NO_PAGES_AVAILABLE
//
#define NO_PAGES_AVAILABLE               ((ULONG)0x0000004DL)

//
// MessageId: PFN_LIST_CORRUPT
//
// MessageText:
//
//  PFN_LIST_CORRUPT
//
#define PFN_LIST_CORRUPT                 ((ULONG)0x0000004EL)

//
// MessageId: NDIS_INTERNAL_ERROR
//
// MessageText:
//
//  NDIS_INTERNAL_ERROR
//
#define NDIS_INTERNAL_ERROR              ((ULONG)0x0000004FL)

//
// MessageId: PAGE_FAULT_IN_NONPAGED_AREA
//
// MessageText:
//
//  PAGE_FAULT_IN_NONPAGED_AREA
//
#define PAGE_FAULT_IN_NONPAGED_AREA      ((ULONG)0x00000050L)

//
// MessageId: REGISTRY_ERROR
//
// MessageText:
//
//  REGISTRY_ERROR
//
#define REGISTRY_ERROR                   ((ULONG)0x00000051L)

//
// MessageId: MAILSLOT_FILE_SYSTEM
//
// MessageText:
//
//  MAILSLOT_FILE_SYSTEM
//
#define MAILSLOT_FILE_SYSTEM             ((ULONG)0x00000052L)

//
// MessageId: NO_BOOT_DEVICE
//
// MessageText:
//
//  NO_BOOT_DEVICE
//
#define NO_BOOT_DEVICE                   ((ULONG)0x00000053L)

//
// MessageId: LM_SERVER_INTERNAL_ERROR
//
// MessageText:
//
//  LM_SERVER_INTERNAL_ERROR
//
#define LM_SERVER_INTERNAL_ERROR         ((ULONG)0x00000054L)

//
// MessageId: DATA_COHERENCY_EXCEPTION
//
// MessageText:
//
//  DATA_COHERENCY_EXCEPTION
//
#define DATA_COHERENCY_EXCEPTION         ((ULONG)0x00000055L)

//
// MessageId: INSTRUCTION_COHERENCY_EXCEPTION
//
// MessageText:
//
//  INSTRUCTION_COHERENCY_EXCEPTION
//
#define INSTRUCTION_COHERENCY_EXCEPTION  ((ULONG)0x00000056L)

//
// MessageId: XNS_INTERNAL_ERROR
//
// MessageText:
//
//  XNS_INTERNAL_ERROR
//
#define XNS_INTERNAL_ERROR               ((ULONG)0x00000057L)

//
// MessageId: FTDISK_INTERNAL_ERROR
//
// MessageText:
//
//  FTDISK_INTERNAL_ERROR
//
#define FTDISK_INTERNAL_ERROR            ((ULONG)0x00000058L)

//
// MessageId: PINBALL_FILE_SYSTEM
//
// MessageText:
//
//  PINBALL_FILE_SYSTEM
//
#define PINBALL_FILE_SYSTEM              ((ULONG)0x00000059L)

//
// MessageId: CRITICAL_SERVICE_FAILED
//
// MessageText:
//
//  CRITICAL_SERVICE_FAILED
//
#define CRITICAL_SERVICE_FAILED          ((ULONG)0x0000005AL)

//
// MessageId: SET_ENV_VAR_FAILED
//
// MessageText:
//
//  SET_ENV_VAR_FAILED
//
#define SET_ENV_VAR_FAILED               ((ULONG)0x0000005BL)

//
// MessageId: HAL_INITIALIZATION_FAILED
//
// MessageText:
//
//  HAL_INITIALIZATION_FAILED
//
#define HAL_INITIALIZATION_FAILED        ((ULONG)0x0000005CL)

//
// MessageId: UNSUPPORTED_PROCESSOR
//
// MessageText:
//
//  UNSUPPORTED_PROCESSOR
//
#define UNSUPPORTED_PROCESSOR            ((ULONG)0x0000005DL)

//
// MessageId: OBJECT_INITIALIZATION_FAILED
//
// MessageText:
//
//  OBJECT_INITIALIZATION_FAILED
//
#define OBJECT_INITIALIZATION_FAILED     ((ULONG)0x0000005EL)

//
// MessageId: SECURITY_INITIALIZATION_FAILED
//
// MessageText:
//
//  SECURITY_INITIALIZATION_FAILED
//
#define SECURITY_INITIALIZATION_FAILED   ((ULONG)0x0000005FL)

//
// MessageId: PROCESS_INITIALIZATION_FAILED
//
// MessageText:
//
//  PROCESS_INITIALIZATION_FAILED
//
#define PROCESS_INITIALIZATION_FAILED    ((ULONG)0x00000060L)

//
// MessageId: HAL1_INITIALIZATION_FAILED
//
// MessageText:
//
//  HAL1_INITIALIZATION_FAILED
//
#define HAL1_INITIALIZATION_FAILED       ((ULONG)0x00000061L)

//
// MessageId: OBJECT1_INITIALIZATION_FAILED
//
// MessageText:
//
//  OBJECT1_INITIALIZATION_FAILED
//
#define OBJECT1_INITIALIZATION_FAILED    ((ULONG)0x00000062L)

//
// MessageId: SECURITY1_INITIALIZATION_FAILED
//
// MessageText:
//
//  SECURITY1_INITIALIZATION_FAILED
//
#define SECURITY1_INITIALIZATION_FAILED  ((ULONG)0x00000063L)

//
// MessageId: SYMBOLIC_INITIALIZATION_FAILED
//
// MessageText:
//
//  SYMBOLIC_INITIALIZATION_FAILED
//
#define SYMBOLIC_INITIALIZATION_FAILED   ((ULONG)0x00000064L)

//
// MessageId: MEMORY1_INITIALIZATION_FAILED
//
// MessageText:
//
//  MEMORY1_INITIALIZATION_FAILED
//
#define MEMORY1_INITIALIZATION_FAILED    ((ULONG)0x00000065L)

//
// MessageId: CACHE_INITIALIZATION_FAILED
//
// MessageText:
//
//  CACHE_INITIALIZATION_FAILED
//
#define CACHE_INITIALIZATION_FAILED      ((ULONG)0x00000066L)

//
// MessageId: CONFIG_INITIALIZATION_FAILED
//
// MessageText:
//
//  CONFIG_INITIALIZATION_FAILED
//
#define CONFIG_INITIALIZATION_FAILED     ((ULONG)0x00000067L)

//
// MessageId: FILE_INITIALIZATION_FAILED
//
// MessageText:
//
//  FILE_INITIALIZATION_FAILED
//
#define FILE_INITIALIZATION_FAILED       ((ULONG)0x00000068L)

//
// MessageId: IO1_INITIALIZATION_FAILED
//
// MessageText:
//
//  IO1_INITIALIZATION_FAILED
//
#define IO1_INITIALIZATION_FAILED        ((ULONG)0x00000069L)

//
// MessageId: LPC_INITIALIZATION_FAILED
//
// MessageText:
//
//  LPC_INITIALIZATION_FAILED
//
#define LPC_INITIALIZATION_FAILED        ((ULONG)0x0000006AL)

//
// MessageId: PROCESS1_INITIALIZATION_FAILED
//
// MessageText:
//
//  PROCESS1_INITIALIZATION_FAILED
//
#define PROCESS1_INITIALIZATION_FAILED   ((ULONG)0x0000006BL)

//
// MessageId: REFMON_INITIALIZATION_FAILED
//
// MessageText:
//
//  REFMON_INITIALIZATION_FAILED
//
#define REFMON_INITIALIZATION_FAILED     ((ULONG)0x0000006CL)

//
// MessageId: SESSION1_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION1_INITIALIZATION_FAILED
//
#define SESSION1_INITIALIZATION_FAILED   ((ULONG)0x0000006DL)

//
// MessageId: SESSION2_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION2_INITIALIZATION_FAILED
//
#define SESSION2_INITIALIZATION_FAILED   ((ULONG)0x0000006EL)

//
// MessageId: SESSION3_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION3_INITIALIZATION_FAILED
//
#define SESSION3_INITIALIZATION_FAILED   ((ULONG)0x0000006FL)

//
// MessageId: SESSION4_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION4_INITIALIZATION_FAILED
//
#define SESSION4_INITIALIZATION_FAILED   ((ULONG)0x00000070L)

//
// MessageId: SESSION5_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION5_INITIALIZATION_FAILED
//
#define SESSION5_INITIALIZATION_FAILED   ((ULONG)0x00000071L)

//
// MessageId: ASSIGN_DRIVE_LETTERS_FAILED
//
// MessageText:
//
//  ASSIGN_DRIVE_LETTERS_FAILED
//
#define ASSIGN_DRIVE_LETTERS_FAILED      ((ULONG)0x00000072L)

//
// MessageId: CONFIG_LIST_FAILED
//
// MessageText:
//
//  CONFIG_LIST_FAILED
//
#define CONFIG_LIST_FAILED               ((ULONG)0x00000073L)

//
// MessageId: BAD_SYSTEM_CONFIG_INFO
//
// MessageText:
//
//  BAD_SYSTEM_CONFIG_INFO
//
#define BAD_SYSTEM_CONFIG_INFO           ((ULONG)0x00000074L)

//
// MessageId: CANNOT_WRITE_CONFIGURATION
//
// MessageText:
//
//  CANNOT_WRITE_CONFIGURATION
//
#define CANNOT_WRITE_CONFIGURATION       ((ULONG)0x00000075L)

//
// MessageId: PROCESS_HAS_LOCKED_PAGES
//
// MessageText:
//
//  PROCESS_HAS_LOCKED_PAGES
//
#define PROCESS_HAS_LOCKED_PAGES         ((ULONG)0x00000076L)

//
// MessageId: KERNEL_STACK_INPAGE_ERROR
//
// MessageText:
//
//  KERNEL_STACK_INPAGE_ERROR
//
#define KERNEL_STACK_INPAGE_ERROR        ((ULONG)0x00000077L)

//
// MessageId: PHASE0_EXCEPTION
//
// MessageText:
//
//  PHASE0_EXCEPTION
//
#define PHASE0_EXCEPTION                 ((ULONG)0x00000078L)

//
// MessageId: MISMATCHED_HAL
//
// MessageText:
//
//  Mismatched kernel and hal image.
//
#define MISMATCHED_HAL                   ((ULONG)0x00000079L)

//
// MessageId: KERNEL_DATA_INPAGE_ERROR
//
// MessageText:
//
//  KERNEL_DATA_INPAGE_ERROR
//
#define KERNEL_DATA_INPAGE_ERROR         ((ULONG)0x0000007AL)

//
// MessageId: INACCESSIBLE_BOOT_DEVICE
//
// MessageText:
//
//  INACCESSIBLE_BOOT_DEVICE
//
#define INACCESSIBLE_BOOT_DEVICE         ((ULONG)0x0000007BL)

//
// MessageId: BUGCODE_PSS_MESSAGE
//
// MessageText:
//
//  Restart and set the recovery options in the system control panel
//  or the /CRASHDEBUG system start option. If this message reappears,
//  contact your system administrator or technical support group.
//
#define BUGCODE_PSS_MESSAGE              ((ULONG)0x0000007CL)

//
// MessageId: INSTALL_MORE_MEMORY
//
// MessageText:
//
//  INSTALL_MORE_MEMORY
//
#define INSTALL_MORE_MEMORY              ((ULONG)0x0000007DL)

//
// MessageId: WINDOWS_NT_BANNER
//
// MessageText:
//
//  Microsoft (R) Windows NT (TM) Version %s (Build %u%s)
//
#define WINDOWS_NT_BANNER                ((ULONG)0x4000007EL)

//
// MessageId: UNEXPECTED_KERNEL_MODE_TRAP
//
// MessageText:
//
//  UNEXPECTED_KERNEL_MODE_TRAP
//
#define UNEXPECTED_KERNEL_MODE_TRAP      ((ULONG)0x0000007FL)

//
// MessageId: NMI_HARDWARE_FAILURE
//
// MessageText:
//
//  Hardware malfunction.
//
#define NMI_HARDWARE_FAILURE             ((ULONG)0x00000080L)

//
// MessageId: SPIN_LOCK_INIT_FAILURE
//
// MessageText:
//
//  SPIN_LOCK_INIT_FAILURE
//
#define SPIN_LOCK_INIT_FAILURE           ((ULONG)0x00000081L)

//
// MessageId: DFS_FILE_SYSTEM
//
// MessageText:
//
//  DFS_FILE_SYSTEM
//
#define DFS_FILE_SYSTEM                  ((ULONG)0x00000082L)

//
// MessageId: OFS_FILE_SYSTEM
//
// MessageText:
//
//  OFS_FILE_SYSTEM
//
#define OFS_FILE_SYSTEM                  ((ULONG)0x00000083L)

//
// MessageId: RECOM_DRIVER
//
// MessageText:
//
//  RECOM_DRIVER
//
#define RECOM_DRIVER                     ((ULONG)0x00000084L)

//
// MessageId: SETUP_FAILURE
//
// MessageText:
//
//  SETUP_FAILURE
//
#define SETUP_FAILURE                    ((ULONG)0x00000085L)

//
// MessageId: AUDIT_FAILURE
//
// MessageText:
//
//  Audit attempt has failed.
//
#define AUDIT_FAILURE                    ((ULONG)0x00000086L)

//
// MessageId: WINDOWS_NT_CSD_STRING
//
// MessageText:
//
//  Service Pack
//
#define WINDOWS_NT_CSD_STRING            ((ULONG)0x40000087L)

//
// MessageId: WINDOWS_NT_INFO_STRING
//
// MessageText:
//
//  %u System Processor [%u MB Memory] %Z
//
#define WINDOWS_NT_INFO_STRING           ((ULONG)0x40000088L)

//
// MessageId: WINDOWS_NT_MP_STRING
//
// MessageText:
//
//  MultiProcessor Kernel
//
#define WINDOWS_NT_MP_STRING             ((ULONG)0x40000089L)

//
// MessageId: THREAD_TERMINATE_HELD_MUTEX
//
// MessageText:
//
//  A kernel thread terminated while holding a mutex
//
#define THREAD_TERMINATE_HELD_MUTEX      ((ULONG)0x4000008AL)

//
// MessageId: MBR_CHECKSUM_MISMATCH
//
// MessageText:
//
//  This system may be infected with a virus.
//
#define MBR_CHECKSUM_MISMATCH            ((ULONG)0x0000008BL)

//
// MessageId: BUGCODE_PSS_CRASH_INIT
//
// MessageText:
//
//  Beginning dump of physical memory
//
#define BUGCODE_PSS_CRASH_INIT           ((ULONG)0x0000008CL)

//
// MessageId: BUGCODE_PSS_CRASH_PROGRESS
//
// MessageText:
//
//  Dumping physical memory to disk
//
#define BUGCODE_PSS_CRASH_PROGRESS       ((ULONG)0x0000008DL)

//
// MessageId: BUGCODE_PSS_CRASH_DONE
//
// MessageText:
//
//  Physical memory dump complete.  Contact your system administrator or
//  technical support group.
//
#define BUGCODE_PSS_CRASH_DONE           ((ULONG)0x0000008EL)

//
// MessageId: PP0_INITIALIZATION_FAILED
//
// MessageText:
//
//  PP0_INITIALIZATION_FAILED
//
#define PP0_INITIALIZATION_FAILED        ((ULONG)0x0000008FL)

//
// MessageId: PP1_INITIALIZATION_FAILED
//
// MessageText:
//
//  PP1_INITIALIZATION_FAILED
//
#define PP1_INITIALIZATION_FAILED        ((ULONG)0x00000090L)

//
// MessageId: WIN32K_INIT_OR_RIT_FAILURE
//
// MessageText:
//
//  WIN32K_INIT_OR_RIT_FAILURE
//
#define WIN32K_INIT_OR_RIT_FAILURE       ((ULONG)0x00000091L)

//
// MessageId: UP_DRIVER_ON_MP_SYSTEM
//
// MessageText:
//
//  UP_DRIVER_ON_MP_SYSTEM
//
#define UP_DRIVER_ON_MP_SYSTEM           ((ULONG)0x00000092L)

//
// MessageId: INVALID_KERNEL_HANDLE
//
// MessageText:
//
//  INVALID_KERNEL_HANDLE
//
#define INVALID_KERNEL_HANDLE            ((ULONG)0x00000093L)

//
// MessageId: KERNEL_STACK_LOCKED_AT_EXIT
//
// MessageText:
//
//  KERNEL_STACK_LOCKED_AT_EXIT
//
#define KERNEL_STACK_LOCKED_AT_EXIT      ((ULONG)0x00000094L)

//
// MessageId: PNP_INTERNAL_ERROR
//
// MessageText:
//
//  PNP_INTERNAL_ERROR
//
#define PNP_INTERNAL_ERROR               ((ULONG)0x00000095L)

//
// MessageId: INVALID_WORK_QUEUE_ITEM
//
// MessageText:
//
//  INVALID_WORK_QUEUE_ITEM
//
#define INVALID_WORK_QUEUE_ITEM          ((ULONG)0x00000096L)

//
// MessageId: BOUND_IMAGE_UNSUPPORTED
//
// MessageText:
//
//  BOUND_IMAGE_UNSUPPORTED
//
#define BOUND_IMAGE_UNSUPPORTED          ((ULONG)0x00000097L)

//
// MessageId: END_OF_NT_EVALUATION_PERIOD
//
// MessageText:
//
//  END_OF_NT_EVALUATION_PERIOD
//
#define END_OF_NT_EVALUATION_PERIOD      ((ULONG)0x00000098L)

//
// MessageId: INVALID_REGION_OR_SEGMENT
//
// MessageText:
//
//  INVALID_REGION_OR_SEGMENT
//
#define INVALID_REGION_OR_SEGMENT        ((ULONG)0x00000099L)

//
// MessageId: SYSTEM_LICENSE_VIOLATION
//
// MessageText:
//
//  SYSTEM_LICENSE_VIOLATION
//
#define SYSTEM_LICENSE_VIOLATION         ((ULONG)0x0000009AL)

//
// MessageId: UDFS_FILE_SYSTEM
//
// MessageText:
//
//  UDFS_FILE_SYSTEM
//
#define UDFS_FILE_SYSTEM                 ((ULONG)0x0000009BL)

//
// MessageId: MACHINE_CHECK_EXCEPTION
//
// MessageText:
//
//  MACHINE_CHECK_EXCEPTION
//
#define MACHINE_CHECK_EXCEPTION          ((ULONG)0x0000009CL)

//
// MessageId: WINDOWS_NT_INFO_STRING_PLURAL
//
// MessageText:
//
//  %u System Processors [%u MB Memory] %Z
//
#define WINDOWS_NT_INFO_STRING_PLURAL    ((ULONG)0x4000009DL)

//
// MessageId: WINDOWS_NT_RC_STRING
//
// MessageText:
//
//  RC
//
#define WINDOWS_NT_RC_STRING             ((ULONG)0x4000009EL)

#endif // _BUGCODES_
