//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1997 - 1999
//
//  File:       msg.mc
//
//--------------------------------------------------------------------------
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
// MessageId: MSG_I_SERVER_OFFLINE
//
// MessageText:
//
//  Server '%1' is now offline.%0
//
#define MSG_I_SERVER_OFFLINE             0x00000001L

//
// MessageId: MSG_I_SERVER_AVAILABLE
//
// MessageText:
//
//  Server '%1' is now available for synchronizing.%0
//
#define MSG_I_SERVER_AVAILABLE           0x00000002L

//
// MessageId: MSG_I_NET_STOPPED
//
// MessageText:
//
//  Network interface has been disconnected.%0
//
#define MSG_I_NET_STOPPED                0x00000003L

//
// MessageId: MSG_I_NET_STARTED
//
// MessageText:
//
//  Network interface has been reconnected.%0
//
#define MSG_I_NET_STARTED                0x00000004L

//
// MessageId: MSG_E_CACHE_CORRUPTED
//
// MessageText:
//
//  A portion of the Offline Files cache has become corrupted.  Restart the computer to clean up the cache.%0
//
#define MSG_E_CACHE_CORRUPTED            0x00000005L

//
// MessageId: MSG_I_SERVER_AUTORECONNECT
//
// MessageText:
//
//  Server '%1' automatically transitioned to online.%0
//
#define MSG_I_SERVER_AUTORECONNECT       0x00000006L

//
// MessageId: MSG_FMT_ACCESS_USER
//
// MessageText:
//
//  User %1%0
//
#define MSG_FMT_ACCESS_USER              0x00000007L

//
// MessageId: MSG_FMT_ACCESS_GUEST
//
// MessageText:
//
//  Guest %1%0
//
#define MSG_FMT_ACCESS_GUEST             0x00000008L

//
// MessageId: MSG_FMT_ACCESS_OTHER
//
// MessageText:
//
//  Other %1%0
//
#define MSG_FMT_ACCESS_OTHER             0x00000009L

//
// MessageId: MSG_FMT_ACCESS_USERGUEST
//
// MessageText:
//
//  User %1, Guest %2%0
//
#define MSG_FMT_ACCESS_USERGUEST         0x0000000AL

//
// MessageId: MSG_FMT_ACCESS_USEROTHER
//
// MessageText:
//
//  User %1, Other %2%0
//
#define MSG_FMT_ACCESS_USEROTHER         0x0000000BL

//
// MessageId: MSG_FMT_ACCESS_GUESTOTHER
//
// MessageText:
//
//  Guest %1, Other %2%0
//
#define MSG_FMT_ACCESS_GUESTOTHER        0x0000000CL

//
// MessageId: MSG_FMT_ACCESS_USERGUESTOTHER
//
// MessageText:
//
//  User %1, Guest %2, Other %3%0
//
#define MSG_FMT_ACCESS_USERGUESTOTHER    0x0000000DL

