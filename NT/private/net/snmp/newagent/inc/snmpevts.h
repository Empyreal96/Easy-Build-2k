/*++

Copyright (c) 1992-1997  Microsoft Corporation

Module Name:

    snmpevts.h

Abstract:

    Eventlog message definitions for the SNMP Service.

Environment:

    User Mode - Win32

Revision History:


--*/

#ifndef _SNMPEVTS_
#define _SNMPEVTS_

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// Public procedures                                                   //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

VOID
SNMP_FUNC_TYPE
ReportSnmpEvent(
    DWORD   nMsgId, 
    DWORD   cSubStrings, 
    LPTSTR *ppSubStrings,
    DWORD   nErrorCode
    );

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// SNMP events 1-1100 are informational                                //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

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
// MessageId: SNMP_EVENT_SERVICE_STARTED
//
// MessageText:
//
//  The SNMP Service has started successfully.
//
#define SNMP_EVENT_SERVICE_STARTED       ((DWORD)0x40FF03E9L)

//
// MessageId: SNMP_EVENT_SERVICE_STOPPED
//
// MessageText:
//
//  The SNMP Service has stopped successfully.
//
#define SNMP_EVENT_SERVICE_STOPPED       ((DWORD)0x40FF03EBL)

//
// MessageId: SNMP_EVENT_CONFIGURATION_UPDATED
//
// MessageText:
//
//  The SNMP Service configuration has been updated successfully.
//
#define SNMP_EVENT_CONFIGURATION_UPDATED ((DWORD)0x40FF03ECL)


/////////////////////////////////////////////////////////////////////////
//                                                                     //
// SNMP events 1100-1499 are warnings                                  //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMP_EVENT_NAME_RESOLUTION_FAILURE
//
// MessageText:
//
//  The SNMP Service is ignoring the manager %1 because its name could not be resolved.
//
#define SNMP_EVENT_NAME_RESOLUTION_FAILURE ((DWORD)0x80FF044CL)

//
// MessageId: SNMP_EVENT_INVALID_EXTENSION_AGENT_KEY
//
// MessageText:
//
//  The SNMP Service is ignoring extension agent key %1 because it is missing or misconfigured.
//
#define SNMP_EVENT_INVALID_EXTENSION_AGENT_KEY ((DWORD)0x80FF044DL)

//
// MessageId: SNMP_EVENT_INVALID_EXTENSION_AGENT_DLL
//
// MessageText:
//
//  The SNMP Service is ignoring extension agent dll %1 because it is missing or misconfigured.
//
#define SNMP_EVENT_INVALID_EXTENSION_AGENT_DLL ((DWORD)0x80FF044EL)

//
// MessageId: SNMP_EVENT_INVALID_ENTERPRISEOID
//
// MessageText:
//
//  The SNMP Service has reset the registry parameter sysObjectID to a default value.
//  This is caused either by an invalid type or by an invalid string format of the registry value.
//
#define SNMP_EVENT_INVALID_ENTERPRISEOID ((DWORD)0x80FF044FL)

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// SNMP events 1500-1998 are warnings                                  //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMP_EVENT_INVALID_REGISTRY_KEY
//
// MessageText:
//
//  The SNMP Service encountered an error while accessing the registry key %1.
//
#define SNMP_EVENT_INVALID_REGISTRY_KEY  ((DWORD)0xC0FF05DCL)

//
// MessageId: SNMP_EVNT_INCOMING_TRANSPORT_CLOSED
//
// MessageText:
//
//  The SNMP Service encountered an error while setting up the incoming transports.\n
//  The %1 transport has been dropped out.
//
#define SNMP_EVNT_INCOMING_TRANSPORT_CLOSED ((DWORD)0xC0FF05DDL)

//
// MessageId: SNMP_EVENT_REGNOTIFY_THREAD_FAILED
//
// MessageText:
//
//  The SNMP Service encountered an error while registering for registry notifications.\n
//  Changes in the service's configuration will not be considered.
//
#define SNMP_EVENT_REGNOTIFY_THREAD_FAILED ((DWORD)0xC0FF05DEL)


/////////////////////////////////////////////////////////////////////////
//                                                                     //
// SNMP events 1999 is used to display debug messages (obsolete)       //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMP_EVENT_DEBUG_TRACE
//
// MessageText:
//
//  %1
//
#define SNMP_EVENT_DEBUG_TRACE           ((DWORD)0x40FF07CFL)


#endif // _SNMPEVTS_

