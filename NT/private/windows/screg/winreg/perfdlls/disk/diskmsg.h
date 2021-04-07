/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1996  Microsoft Corporation

Module Name:

    diskmsg.h
       (generated from diskmsg.mc)

Abstract:

   Event message definititions used by routines in PerfOS Perf DLL

Created:

    23-Oct-96 Bob Watson

Revision History:

--*/
#ifndef _DISKMSG_MC_H_
#define _DISKMSG_MC_H_

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
// MessageId: PERFDISK_UNABLE_OPEN
//
// MessageText:
//
//  Unable to open the Disk performance object. Status code returned is
//  data DWORD 0.
//
#define PERFDISK_UNABLE_OPEN             ((DWORD)0x800003E8L)

//
// MessageId: PERFDISK_NOT_OPEN
//
// MessageText:
//
//  The attempt to collect Disk Performance data failed beause the DLL did 
//  not open successfully.
//
#define PERFDISK_NOT_OPEN                ((DWORD)0xC00003E9L)

//
// MessageId: PERFDISK_UNABLE_ALLOC_BUFFER
//
// MessageText:
//
//  Unable to allocate a dynamic memory buffer
//
#define PERFDISK_UNABLE_ALLOC_BUFFER     ((DWORD)0xC00003EAL)

//
// MessageId: PERFDISK_BUSY
//
// MessageText:
//
//  The Disk Performance data collection function was called by one
//  thread while in use by another. No will be returned to the 2nd caller.
//
#define PERFDISK_BUSY                    ((DWORD)0xC00003EBL)

//
//     Module specific messages
//
//
// MessageId: PERFDISK_UNABLE_QUERY_VOLUME_INFO
//
// MessageText:
//
//  Unable to read the Logical Volume information from the system.
//  Status code returned is data DWORD 0.
//
#define PERFDISK_UNABLE_QUERY_VOLUME_INFO ((DWORD)0x800007D0L)

//
// MessageId: PERFDISK_UNABLE_QUERY_DISKPERF_INFO
//
// MessageText:
//
//  Unable to read the disk performance information from the system. 
//  Disk performance counters must be enabled for at least one 
//  physical disk or logical volume in order for these counters to appear.
//  Disk performance counters can be enabled by using the Hardware Device Manager property pages.
//  Status code returned is data DWORD 0.
//
#define PERFDISK_UNABLE_QUERY_DISKPERF_INFO ((DWORD)0x800007D1L)

//
#endif //_DISKMSG_MC_H_
