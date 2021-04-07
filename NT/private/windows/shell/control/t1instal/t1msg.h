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
// MessageId: MSG_BADESC
//
// MessageText:
//
//  Bad 'Escape' operator.
//
#define MSG_BADESC                       0x000003E8L

//
// MessageId: MSG_BADOP
//
// MessageText:
//
//  Unsupported operator: '%1'.
//
#define MSG_BADOP                        0x000003E9L

//
// MessageId: MSG_NOCOPYRIGHT
//
// MessageText:
//
//  Copyright notice was not found in the typeface.
//
#define MSG_NOCOPYRIGHT                  0x000003EAL

//
// MessageId: MSG_BADFMT
//
// MessageText:
//
//  Unsupported Adobe Type 1 file format.
//
#define MSG_BADFMT                       0x000003EBL

//
// MessageId: MSG_DB
//
// MessageText:
//
//  Simon says: %1
//
#define MSG_DB                           0x000003ECL

//
// MessageId: MSG_NOMEM
//
// MessageText:
//
//  Out of memory.
//
#define MSG_NOMEM                        0x000003EDL

//
// MessageId: MSG_RECURSION
//
// MessageText:
//
//  Too many recursion calls.
//
#define MSG_RECURSION                    0x000003EEL

//
// MessageId: MSG_PLATFORM
//
// MessageText:
//
//  Bad platform ID in NAME table.
//
#define MSG_PLATFORM                     0x000003EFL

//
// MessageId: MSG_FLEX
//
// MessageText:
//
//  Lost flex hint.
//
#define MSG_FLEX                         0x000003F0L

//
// MessageId: MSG_EXTREME1
//
// MessageText:
//
//  IP stack overflow.
//
#define MSG_EXTREME1                     0x000003F1L

//
// MessageId: MSG_REPLC
//
// MessageText:
//
//  Section stack overflow.
//
#define MSG_REPLC                        0x000003F2L

//
// MessageId: MSG_DBLIDX
//
// MessageText:
//
//  Conflicting sub-routine entries.
//
#define MSG_DBLIDX                       0x000003F3L

//
// MessageId: MSG_INVBLUES
//
// MessageText:
//
//  Inverted alignment zones.
//
#define MSG_INVBLUES                     0x000003F4L

//
// MessageId: MSG_BADAW
//
// MessageText:
//
//  Vertical advance width of characters is not supported.
//
#define MSG_BADAW                        0x000003F5L

//
// MessageId: MSG_DIAG
//
// MessageText:
//
//  Outline thinning stack overflow.
//
#define MSG_DIAG                         0x000003F6L

//
// MessageId: MSG_ALIGN
//
// MessageText:
//
//  Internal error (bad alignement).
//
#define MSG_ALIGN                        0x000003F7L

//
// MessageId: MSG_BADENC
//
// MessageText:
//
//  Ignoring glyph: %1
//
#define MSG_BADENC                       0x000003F8L

//
// MessageId: MSG_COPYRIGHT
//
// MessageText:
//
//  Copyright by: %1
//
#define MSG_COPYRIGHT                    0x000003F9L

//
// MessageId: MSG_STARTING
//
// MessageText:
//
//  Converting typeface: %1
//
#define MSG_STARTING                     0x000003FAL

//
// MessageId: MSG_NODB
//
// MessageText:
//
//  Could not access registry database.
//
#define MSG_NODB                         0x000003FBL

//
// MessageId: MSG_BADFORMAT
//
// MessageText:
//
//  Unknown copyright format: "%1"
//
#define MSG_BADFORMAT                    0x000003FCL

//
// MessageId: MSG_BADCOPYRIGHT
//
// MessageText:
//
//  Can not install typeface due to copyright.
//  Copyright holder: 
//      %1
//
#define MSG_BADCOPYRIGHT                 0x000003FDL

