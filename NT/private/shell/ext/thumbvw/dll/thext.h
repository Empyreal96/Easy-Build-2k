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
// MessageId: MSG_STATUS_OBJECTS
//
// MessageText:
//
//  %1!d! object(s)%0
//
#define MSG_STATUS_OBJECTS               0x00000064L

//
// MessageId: MSG_STATUS_OBJECTS_SELECTED
//
// MessageText:
//
//  %1!d! object(s) selected%0
//
#define MSG_STATUS_OBJECTS_SELECTED      0x00000065L

//
// MessageId: MSG_HTML_TIMEOUT
//
// MessageText:
//
//  The page '%1' could not be loaded and rendered within the timeout period.
//
#define MSG_HTML_TIMEOUT                 0x00000068L

//
// MessageId: MSG_HTML_OUTOFMEMORY
//
// MessageText:
//
//  Item '%1'. The system is running low on available memory, please close some applications and try again.
//
#define MSG_HTML_OUTOFMEMORY             0x00000069L

//
// MessageId: MSG_HTML_OUTOFRESOURCES
//
// MessageText:
//
//  Item '%1'. The system is running low on available resources, please close some applications and try again.
//
#define MSG_HTML_OUTOFRESOURCES          0x0000006AL

//
// MessageId: MSG_THUMBNAIL_ERROR
//
// MessageText:
//
//  A thumbnail could not be created for this item.
//
#define MSG_THUMBNAIL_ERROR              0x00000077L

//
// MessageId: MSG_ERROR_TITLE
//
// MessageText:
//
//  Refresh Thumbnail
//
#define MSG_ERROR_TITLE                  0x00000078L

