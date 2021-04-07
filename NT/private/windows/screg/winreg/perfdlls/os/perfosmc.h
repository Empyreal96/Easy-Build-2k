/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1996  Microsoft Corporation

Module Name:

    perfosmc.h
       (generated from perfosmc.mc)

Abstract:

   Event message definititions used by routines in PerfOS Perf DLL

Created:

    23-Oct-96 Bob Watson

Revision History:

--*/
#ifndef _PERFOS_MC_H_
#define _PERFOS_MC_H_

//
//     Perflib ERRORS
//
//
// Common messages
//
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
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: PERFOS_UNABLE_OPEN
//
// MessageText:
//
//  Unable to open the object. Status code returned is data DWORD 0.
//
#define PERFOS_UNABLE_OPEN               ((DWORD)0xC00003E8L)

//
// MessageId: PERFOS_NOT_OPEN
//
// MessageText:
//
//  The attempt to collect OS Performance data failed beause the DLL did 
//  not open successfully.
//
#define PERFOS_NOT_OPEN                  ((DWORD)0xC00003E9L)

//
//     Module specific messages
//
//
// MessageId: PERFOS_UNABLE_QUERY_PROCSSOR_INFO
//
// MessageText:
//
//  Unable to get processor performance information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_PROCSSOR_INFO ((DWORD)0x800007D0L)

//
// MessageId: PERFOS_UNABLE_QUERY_INTERRUPT_INFO
//
// MessageText:
//
//  Unable to get interrupt performance information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_INTERRUPT_INFO ((DWORD)0x800007D1L)

//
// MessageId: PERFOS_UNABLE_QUERY_FILE_CACHE_INFO
//
// MessageText:
//
//  Unable to get file cache performance information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_FILE_CACHE_INFO ((DWORD)0x800007D2L)

//
// MessageId: PERFOS_UNABLE_QUERY_PROCESS_OBJECT_INFO
//
// MessageText:
//
//  Unable to get process object information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_PROCESS_OBJECT_INFO ((DWORD)0x800007D3L)

//
// MessageId: PERFOS_UNABLE_QUERY_THREAD_OBJECT_INFO
//
// MessageText:
//
//  Unable to get thread object information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_THREAD_OBJECT_INFO ((DWORD)0x800007D4L)

//
// MessageId: PERFOS_UNABLE_QUERY_EVENT_OBJECT_INFO
//
// MessageText:
//
//  Unable to get event object information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_EVENT_OBJECT_INFO ((DWORD)0x800007D5L)

//
// MessageId: PERFOS_UNABLE_QUERY_SEMAPHORE_OBJECT_INFO
//
// MessageText:
//
//  Unable to get semaphore object information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_SEMAPHORE_OBJECT_INFO ((DWORD)0x800007D6L)

//
// MessageId: PERFOS_UNABLE_QUERY_MUTEX_OBJECT_INFO
//
// MessageText:
//
//  Unable to get mutex object information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_MUTEX_OBJECT_INFO ((DWORD)0x800007D7L)

//
// MessageId: PERFOS_UNABLE_QUERY_SECTION_OBJECT_INFO
//
// MessageText:
//
//  Unable to get section object information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_SECTION_OBJECT_INFO ((DWORD)0x800007D8L)

//
// MessageId: PERFOS_UNABLE_QUERY_BASIC_INFO
//
// MessageText:
//
//  Unable to get basic system configuration information. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_BASIC_INFO   ((DWORD)0xC00007D9L)

//
// MessageId: PERFOS_UNABLE_QUERY_SYS_PERF_INFO
//
// MessageText:
//
//  Unable to get system performance information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_SYS_PERF_INFO ((DWORD)0x800007DAL)

//
// MessageId: PERFOS_UNABLE_QUERY_PAGEFILE_INFO
//
// MessageText:
//
//  Unable to get system pagefile information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_PAGEFILE_INFO ((DWORD)0x800007DBL)

//
// MessageId: PERFOS_UNABLE_QUERY_PROCESS_INFO
//
// MessageText:
//
//  Unable to get system process information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_PROCESS_INFO ((DWORD)0x800007DCL)

//
// MessageId: PERFOS_UNABLE_QUERY_EXCEPTION_INFO
//
// MessageText:
//
//  Unable to get system exception information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_EXCEPTION_INFO ((DWORD)0x800007DDL)

//
// MessageId: PERFOS_UNABLE_QUERY_REGISTRY_QUOTA_INFO
//
// MessageText:
//
//  Unable to get registry quota information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_REGISTRY_QUOTA_INFO ((DWORD)0x800007DEL)

//
// MessageId: PERFOS_UNABLE_QUERY_SYSTEM_TIME_INFO
//
// MessageText:
//
//  Unable to get system process information from system. Status
//  code returned is data DWORD 0.
//
#define PERFOS_UNABLE_QUERY_SYSTEM_TIME_INFO ((DWORD)0x800007DFL)


#endif //_PERFOS_MC_H_
