/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1996  Microsoft Corporation

Module Name:

    netsvcmc.h
       (generated from netsvcmc.mc)

Abstract:

   Event message definititions used by routines in PerfOS Perf DLL

Created:

    23-Oct-96 Bob Watson

Revision History:

--*/
#ifndef _NETSVC_MC_H_
#define _NETSVC_MC_H_

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
// MessageId: PERFNET_UNABLE_OPEN
//
// MessageText:
//
//  Unable to open the Network Services performance object. 
//  Status code returned is data DWORD 0.
//
#define PERFNET_UNABLE_OPEN              ((DWORD)0x800003E8L)

//
// MessageId: PERFNET_NOT_OPEN
//
// MessageText:
//
//  The attempt to collect Network Services Performance data failed 
//  beause the DLL did not open successfully.
//
#define PERFNET_NOT_OPEN                 ((DWORD)0xC00003E9L)

//
//     Module specific messages
//
//
// MessageId: PERFNET_UNABLE_OPEN_NETAPI32_DLL
//
// MessageText:
//
//  Unable to open the NETAPI32.DLL for the collection of Browser performance
//  data. Browser performance data will not be returned. Error code returned
//  is in data DWORD 0.
//
#define PERFNET_UNABLE_OPEN_NETAPI32_DLL ((DWORD)0xC00007D0L)

//
// MessageId: PERFNET_UNABLE_LOCATE_BROWSER_PERF_FN
//
// MessageText:
//
//  Unable to locate the Query function for the Browser Performance data in the 
//  NETAPI32.DLL for the collection of Browser performance data. Browser 
//  performance data will not be returned. Error code returned is in 
//  data DWORD 0.
//
#define PERFNET_UNABLE_LOCATE_BROWSER_PERF_FN ((DWORD)0xC00007D1L)

//
// MessageId: PERFNET_UNABLE_OPEN_REDIR
//
// MessageText:
//
//  Unable to open the Redirector service. Redirector performance data 
//  will not be returned. Error code returned is in data DWORD 0.
//
#define PERFNET_UNABLE_OPEN_REDIR        ((DWORD)0xC00007D2L)

//
// MessageId: PERFNET_UNABLE_READ_REDIR
//
// MessageText:
//
//  Unable to read performance data from the Redirector service. 
//  No Redirector performance data will be returned in this sample. 
//  Error code returned is in data DWORD 0.
//
#define PERFNET_UNABLE_READ_REDIR        ((DWORD)0xC00007D3L)

//
// MessageId: PERFNET_UNABLE_OPEN_SERVER
//
// MessageText:
//
//  Unable to open the Server service. Server performance data 
//  will not be returned. Error code returned is in data DWORD 0.
//
#define PERFNET_UNABLE_OPEN_SERVER       ((DWORD)0xC00007D4L)

//
// MessageId: PERFNET_UNABLE_READ_SERVER
//
// MessageText:
//
//  Unable to read performance data from the Server service. 
//  No Server performance data will be returned in this sample. 
//  Error code returned is in data DWORD 0, IOSB.Status is DWORD 1 and
//  the IOSB.Information is DWORD 2.
//
#define PERFNET_UNABLE_READ_SERVER       ((DWORD)0xC00007D5L)

//
// MessageId: PERFNET_UNABLE_READ_SERVER_QUEUE
//
// MessageText:
//
//  Unable to read Server Queue performance data from the Server service. 
//  No Server Queue performance data will be returned in this sample. 
//  Error code returned is in data DWORD 0, IOSB.Status is DWORD 1 and
//  the IOSB.Information is DWORD 2.
//
#define PERFNET_UNABLE_READ_SERVER_QUEUE ((DWORD)0xC00007D6L)

//
#endif //_NETSVC_MC_H_
