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
// MessageId: MSG_E_POLICY_OUTOFMEMORY
//
// MessageText:
//
//  Insufficient memory to apply quota policy.%0
//
#define MSG_E_POLICY_OUTOFMEMORY         0x00000001L

//
// MessageId: MSG_E_POLICY_EXCEPTION
//
// MessageText:
//
//  An exception occured while applying quota policy.%0
//
#define MSG_E_POLICY_EXCEPTION           0x00000002L

//
// MessageId: MSG_E_POLICY_GPEREGKEYROOT
//
// MessageText:
//
//  Error %1 querying for group policy registry root key.%n%2.%0
//
#define MSG_E_POLICY_GPEREGKEYROOT       0x00000003L

//
// MessageId: MSG_E_POLICY_GPEREGKEYOPEN
//
// MessageText:
//
//  Error %1 opening group policy registry key %2.%n%3.%0
//
#define MSG_E_POLICY_GPEREGKEYOPEN       0x00000004L

//
// MessageId: MSG_E_POLICY_CREATEQUOTACONTROL
//
// MessageText:
//
//  Error %1 instantiating IDiskQuotaControl in dskquota.dll.%n%2.%0
//
#define MSG_E_POLICY_CREATEQUOTACONTROL  0x00000005L

//
// MessageId: MSG_E_POLICY_CREATECLASSFACTORY
//
// MessageText:
//
//  Error %1 instantiating IClassFactory in dskquota.dll.%n%2.%0
//
#define MSG_E_POLICY_CREATECLASSFACTORY  0x00000006L

//
// MessageId: MSG_E_POLICY_GETDRIVELIST
//
// MessageText:
//
//  Error %1 getting list of disk volumes.%n%2.%0
//
#define MSG_E_POLICY_GETDRIVELIST        0x00000007L

//
// MessageId: MSG_E_POLICY_INITVOLUME
//
// MessageText:
//
//  Error %1 initializing volume %2%n%3.%0
//
#define MSG_E_POLICY_INITVOLUME          0x00000008L

//
// MessageId: MSG_E_POLICY_SETQUOTA
//
// MessageText:
//
//  Error %1 applying quota policy to volume %2%n%3.%0
//
#define MSG_E_POLICY_SETQUOTA            0x00000009L

//
// MessageId: MSG_I_POLICY_FINISHED
//
// MessageText:
//
//  Quota policy applied to volumes %1%nQuota enabled: %2%nDeny use over limit: %3%nWarning at: %4%nLimit at: %5%0
//
#define MSG_I_POLICY_FINISHED            0x0000000AL

//
// MessageId: MSG_I_POLICY_INFOLOADED
//
// MessageText:
//
//  Quota policy information loaded from registry.%0
//
#define MSG_I_POLICY_INFOLOADED          0x0000000BL

//
// MessageId: MSG_I_POLICY_ABORTED
//
// MessageText:
//
//  Quota policy processing aborted due to machine shutdown or logoff.%0
//
#define MSG_I_POLICY_ABORTED             0x0000000CL

