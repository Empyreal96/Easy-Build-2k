/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1992  Microsoft Corporation

Module Name:

    win31evt.h

Abstract:

    Definitions for Windows 3.1 Migration Events

Author:

    Portable Systems Group 6-May-1992

Revision History:

Notes:

    This file is generated by the MC tool from the win31evt.mc file.

--*/


#ifndef _WIN31EVT_
#define _WIN31EVT_


/////////////////////////////////////////////////////////////////////////
//
// Windows 3.1 Migration Events (1000 - 1999)
//
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
// MessageId: WIN31IO_EVENT_EXCEPTION
//
// MessageText:
//
//  An exception occurred while performing Windows 3.1 migration.  Some data
//  may not have been migrated.
//
#define WIN31IO_EVENT_EXCEPTION          0x400003E8L

//
// MessageId: WIN31IO_EVENT_MIGRATE_INI_FILE
//
// MessageText:
//
//  The entire contents of %1 was migrated into the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_INI_FILE   0x400003E9L

//
// MessageId: WIN31IO_EVENT_MIGRATE_INI_SECTION
//
// MessageText:
//
//  The entire contents of the %1 section of %2 was migrated into the
//  Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_INI_SECTION 0x400003EAL

//
// MessageId: WIN31IO_EVENT_MIGRATE_INI_VARIABLE
//
// MessageText:
//
//  The value of the %1 variable in the %2 section of %3 was migrated into
//  the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_INI_VARIABLE 0x400003EBL

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP
//
// MessageText:
//
//  The entire contents of the %1 Program Manager group was migrated into the
//  Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_GROUP      0x400003ECL

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP_EXISTS
//
// MessageText:
//
//  The contents of the Windows 3.X Program Manager group file %1 was not
//  migrated into the Windows NT registry, as a group of that name, %2,
//  already existed.
//
#define WIN31IO_EVENT_MIGRATE_GROUP_EXISTS 0x400003EDL

//
// MessageId: WIN31IO_EVENT_MIGRATE_INI_FILE_FAILED
//
// MessageText:
//
//  Unable to migrate all or part of the %1 file into the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_INI_FILE_FAILED 0x800003EEL

//
// MessageId: WIN31IO_EVENT_MIGRATE_INI_SECTION_FAILED
//
// MessageText:
//
//  Unable to migrate all or part of the %1 section of %2 into the Windows
//  NT registry.
//
#define WIN31IO_EVENT_MIGRATE_INI_SECTION_FAILED 0x800003EFL

//
// MessageId: WIN31IO_EVENT_MIGRATE_INI_VARIABLE_FAILED
//
// MessageText:
//
//  Unable to migrate the value of the %1 variable in the %2 section of %3
//  into the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_INI_VARIABLE_FAILED 0x800003F0L

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP_FAILED
//
// MessageText:
//
//  Unable to migrate the contents of the %1 Program Manager group into
//  the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_GROUP_FAILED 0x800003F1L

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP_FAILED1
//
// MessageText:
//
//  Unable to load the contents of the Windows 3.1 Program Manager group file %1.
//  Error Code was %2.  Group not migrated to the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_GROUP_FAILED1 0x800003F2L

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP_FAILED2
//
// MessageText:
//
//  Unable to read the value of %1 from the %2 file.  Group not migrated to
//  the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_GROUP_FAILED2 0x800003F3L

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP_FAILED3
//
// MessageText:
//
//  Unable to convert the contents of the Windows 3.1 Program Manager group
//  file %1.  into the Windows NT format.  Error Code was %2.  Group not
//  migrated to the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_GROUP_FAILED3 0x800003F4L

//
// MessageId: WIN31IO_EVENT_MIGRATE_REGDAT
//
// MessageText:
//
//  Contents of %1 migrated to the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_REGDAT     0x400003F5L

//
// MessageId: WIN31IO_EVENT_MIGRATE_REGDAT_FAILED
//
// MessageText:
//
//  Unable to migrate all or part of %1 to the Windows NT registry.
//
#define WIN31IO_EVENT_MIGRATE_REGDAT_FAILED 0x800003F6L

//
// MessageId: WIN31IO_EVENT_MIGRATE_GROUP_FAILED4
//
// MessageText:
//
//  Did not migrate the contents of the %1 Program Manager group into
//  the Windows NT registry.  It is incompatible with Windows NT.
//
#define WIN31IO_EVENT_MIGRATE_GROUP_FAILED4 0x800003F7L


#endif // _WIN31EVT_

