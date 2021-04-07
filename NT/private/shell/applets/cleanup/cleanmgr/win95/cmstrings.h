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
// MessageId: MSG_APP_TITLE
//
// MessageText:
//
//  Disk Cleanup for %1 (%2!c!:)%0
//
#define MSG_APP_TITLE                    0x00000064L

//
// MessageId: MSG_BAD_DRIVE_LETTER
//
// MessageText:
//
//  Disk Cleanup cannot clean up drive %1.
//  Make sure that there is a disk in the drive, and that the drive door is closed.%0
//
#define MSG_BAD_DRIVE_LETTER             0x00000065L

//
// MessageId: MSG_APP_SETTINGS_TITLE
//
// MessageText:
//
//  Disk Cleanup Settings%0
//
#define MSG_APP_SETTINGS_TITLE           0x00000066L

//
// MessageId: MSG_INTRO_SETTINGS_TEXT
//
// MessageText:
//
//  Check the items that you would like Disk Cleanup to automatically clean up during its scheduled run times.%0
//
#define MSG_INTRO_SETTINGS_TEXT          0x00000067L

//
// MessageId: MSG_INTRO_SETTINGS_TAB
//
// MessageText:
//
//  %1 (%2!c!:)%0
//
#define MSG_INTRO_SETTINGS_TAB           0x00000068L

//
// MessageId: MSG_SEL_DRIVE_TITLE
//
// MessageText:
//
//  Select Drive%0
//
#define MSG_SEL_DRIVE_TITLE              0x00000069L

//
// MessageId: MSG_VOL_NAME_DRIVE_LETTER
//
// MessageText:
//
//  %1 (%2!c!:)%0
//
#define MSG_VOL_NAME_DRIVE_LETTER        0x0000006AL

//
// MessageId: MSG_INTRO_TEXT
//
// MessageText:
//
//  You can use Disk Cleanup to free up to %2 of disk space on %1.%0
//
#define MSG_INTRO_TEXT                   0x0000006BL

//
// MessageId: MSG_SCAN_ABORT_TEXT
//
// MessageText:
//
//  Disk Cleanup is calculating how much space you will be able to free on %1 (%2!c!:).%0
//
#define MSG_SCAN_ABORT_TEXT              0x0000006CL

//
// MessageId: MSG_PURGE_ABORT_TEXT
//
// MessageText:
//
//  Cleaning up drive %1 (%2!c!:).%0
//
#define MSG_PURGE_ABORT_TEXT             0x0000006DL

//
// MessageId: MSG_GB
//
// MessageText:
//
//  %1 GB%0
//
#define MSG_GB                           0x0000006EL

//
// MessageId: MSG_MB
//
// MessageText:
//
//  %1 MB%0
//
#define MSG_MB                           0x0000006FL

//
// MessageId: MSG_KB
//
// MessageText:
//
//  %1 KB%0
//
#define MSG_KB                           0x00000070L

