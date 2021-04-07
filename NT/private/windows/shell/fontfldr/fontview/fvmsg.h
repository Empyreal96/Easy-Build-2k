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
// MessageId: MSG_BADFILENAME
//
// MessageText:
//
//  The requested file %1 was not a valid font file.
//
#define MSG_BADFILENAME                  0x00000001L

//
// MessageId: MSG_APP_TITLE
//
// MessageText:
//
//  Font View Application
//
#define MSG_APP_TITLE                    0x00000002L

//
// MessageId: MSG_OUTOFMEM
//
// MessageText:
//
//  There is not enough free memory for this operation.
//
#define MSG_OUTOFMEM                     0x00000003L

//
// MessageId: MSG_PTRUETYPEP
//
// MessageText:
//
//  %1 (TrueType)
//
#define MSG_PTRUETYPEP                   0x00000004L

//
// MessageId: MSG_TYPEFACENAME
//
// MessageText:
//
//  Typeface name: %1
//
#define MSG_TYPEFACENAME                 0x00000005L

//
// MessageId: MSG_FILESIZE
//
// MessageText:
//
//  File size: %1!d! KB
//
#define MSG_FILESIZE                     0x00000006L

//
// MessageId: MSG_VERSION
//
// MessageText:
//
//  Version: %1
//
#define MSG_VERSION                      0x00000007L

//
// MessageId: MSG_COPYRIGHT
//
// MessageText:
//
//  %1
//
#define MSG_COPYRIGHT                    0x00000008L

//
// MessageId: MSG_SAMPLEALPH_0
//
// MessageText:
//
//  abcdefghijklmnopqrstuvwxyz
//
#define MSG_SAMPLEALPH_0                 0x00000009L

//
// MessageId: MSG_SAMPLEALPH_1
//
// MessageText:
//
//  ABCDEFGHIJKLMNOPQRSTUVWXYZ
//
#define MSG_SAMPLEALPH_1                 0x0000000AL

//
// MessageId: MSG_SAMPLEALPH_2
//
// MessageText:
//
//  123456789.:,;(:*!?')
//
#define MSG_SAMPLEALPH_2                 0x0000000BL

//
// MessageId: MSG_SAMPLETEXT
//
// MessageText:
//
//  The quick brown fox jumps over the lazy dog. 1234567890
//
#define MSG_SAMPLETEXT                   0x0000000CL

//
// MessageId: MSG_SAMPLETEXT_ALT
//
// MessageText:
//
//  Windows 1234567890
//
#define MSG_SAMPLETEXT_ALT               0x0000000DL

//
// MessageId: MSG_DONE
//
// MessageText:
//
//  &Done
//
#define MSG_DONE                         0x0000000EL

//
// MessageId: MSG_PRINT
//
// MessageText:
//
//  &Print
//
#define MSG_PRINT                        0x0000000FL

//
// MessageId: MSG_ALTSAMPLE
//
// MessageText:
//
//  Jackdaws love my big sphinx of quartz. 123456890
//
#define MSG_ALTSAMPLE                    0x00000010L

//
// MessageId: MSG_TTC_CONCAT
//
// MessageText:
//
//  %1 & %2
//
#define MSG_TTC_CONCAT                   0x00000011L

//
// MessageId: MSG_PREV_FONT
//
// MessageText:
//
//  &<<
//
#define MSG_PREV_FONT                    0x00000012L

//
// MessageId: MSG_NEXT_FONT
//
// MessageText:
//
//  &>>
//
#define MSG_NEXT_FONT                    0x00000013L

//
// MessageId: MSG_POPENTYPEP
//
// MessageText:
//
//  %1 (OpenType)
//
#define MSG_POPENTYPEP                   0x00000014L

//
// MessageId: MSG_PTYPE1
//
// MessageText:
//
//  %1 (Type1)
//
#define MSG_PTYPE1                       0x00000015L

//
// MessageId: MSG_POTF
//
// MessageText:
//
//  %1OpenType Font,
//
#define MSG_POTF                         0x00000016L

//
// MessageId: MSG_PDSIG
//
// MessageText:
//
//  %1Digitally Signed,
//
#define MSG_PDSIG                        0x00000017L

//
// MessageId: MSG_PTTGLYPHS
//
// MessageText:
//
//  %1TrueType
//
#define MSG_PTTGLYPHS                    0x00000018L

//
// MessageId: MSG_PPSGLYPHS
//
// MessageText:
//
//  %1PostScript
//
#define MSG_PPSGLYPHS                    0x00000019L

//
// MessageId: MSG_PINSTRUCTIONS
//
// MessageText:
//
//  %1Outlines
//
#define MSG_PINSTRUCTIONS                0x0000001AL

//
// MessageId: MSG_PSINGLEMASTER
//
// MessageText:
//
//  %1, Single Master
//
#define MSG_PSINGLEMASTER                0x0000001BL

//
// MessageId: MSG_PMULTIPLEMASTER
//
// MessageText:
//
//  %1, Multiple Master
//
#define MSG_PMULTIPLEMASTER              0x0000001CL

