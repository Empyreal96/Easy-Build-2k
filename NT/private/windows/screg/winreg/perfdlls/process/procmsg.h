/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1996  Microsoft Corporation

Module Name:

    PROCMSG.h
       (generated from PROCMSG.mc)

Abstract:

   Event message definititions used by routines in PerfOS Perf DLL

Created:

    23-Oct-96 Bob Watson

Revision History:

--*/
#ifndef _PROCMSG_MC_H_
#define _PROCMSG_MC_H_

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
// MessageId: PERFPROC_UNABLE_OPEN
//
// MessageText:
//
//  Unable to open the Disk performance object. Status code returned is
//  data DWORD 0.
//
#define PERFPROC_UNABLE_OPEN             ((DWORD)0x800003E8L)

//
// MessageId: PERFPROC_NOT_OPEN
//
// MessageText:
//
//  The attempt to collect Disk Performance data failed beause the DLL did 
//  not open successfully.
//
#define PERFPROC_NOT_OPEN                ((DWORD)0xC00003E9L)

//
//     Module specific messages
//
//
// MessageId: PERFPROC_UNABLE_QUERY_PROCESS_INFO
//
// MessageText:
//
//  Unable to collect system process performance information. Status code
//  returned is data DWORD 0.
//
#define PERFPROC_UNABLE_QUERY_PROCESS_INFO ((DWORD)0xC00007D0L)

//
// MessageId: PERFPROC_UNABLE_QUERY_VM_INFO
//
// MessageText:
//
//  Unable to collect process virtual memory information. Status code
//  returned is data DWORD 0.
//
#define PERFPROC_UNABLE_QUERY_VM_INFO    ((DWORD)0xC00007D1L)

//
//
// MessageId: PERFPROC_UNABLE_OPEN_JOB
//
// MessageText:
//
//  Unable to open the job object %1 for query access. 
//  The calling process may not have permission to open this Job. 
//  The status returned is data DWORD 0.
//
#define PERFPROC_UNABLE_OPEN_JOB         ((DWORD)0x800007D2L)

//
//
// MessageId: PERFPROC_UNABLE_QUERY_JOB_ACCT
//
// MessageText:
//
//  Unable to query the job object %1 for its accounting info. 
//  The calling process may not have permission to query this Job. 
//  The status returned is data DWORD 0.
//
#define PERFPROC_UNABLE_QUERY_JOB_ACCT   ((DWORD)0x800007D3L)

//
//
// MessageId: PERFPROC_UNABLE_QUERY_OBJECT_DIR
//
// MessageText:
//
//  Unable to query the %1 Object Directory to look for Job Objects.
//  The calling process may not have permission to perform this query.
//  The status returned is data DWORD 0.
//
#define PERFPROC_UNABLE_QUERY_OBJECT_DIR ((DWORD)0x800007D4L)

//
//
// MessageId: PERFPROC_UNABLE_QUERY_JOB_PIDS
//
// MessageText:
//
//  Unable to query the job object %1 for its Process IDs
//  The calling process may not have permission to query this Job. 
//  The status returned is data DWORD 0.
//
#define PERFPROC_UNABLE_QUERY_JOB_PIDS   ((DWORD)0x800007D5L)

//
#endif //_PROCMSG_MC_H_
