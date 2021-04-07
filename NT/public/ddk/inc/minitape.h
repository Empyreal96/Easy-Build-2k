/*++

Copyright (c000294  Microsoft Corporation

Module Name:

    minitape.h

Abstract:

    Type definitions for minitape drivers.

Author:

    Norbert Kusters 20-December-1994

Revision History:

--*/

#ifndef _MINITAPE_
#define _MINITAPE_

#include "stddef.h"

#define ASSERT( exp )

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef NOTHING
#define NOTHING
#endif

#ifndef CRITICAL
#define CRITICAL
#endif

#ifndef ANYSIZE_ARRAY
#define ANYSIZE_ARRAY 1       // winnt
#endif

// begin_winnt

#if defined(_M_MRX000) && !(defined(MIDL_PASS) || defined(RC_INVOKED)) && defined(ENABLE_RESTRICTED)
#define RESTRICTED_POINTER __restrict
#else
#define RESTRICTED_POINTER
#endif

#if defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif

// end_winnt

#ifndef CONST
#define CONST               const
#endif

// begin_winnt

#if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
#define DECLSPEC_IMPORT __declspec(dllimport)
#else
#define DECLSPEC_IMPORT
#endif

// end_winnt

//
// Void
//

typedef void *PVOID;    // winnt


//
// Basics
//

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

//
// UNICODE (Wide Character) types
//

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character

typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;

typedef CONST WCHAR *LPCWSTR, *PCWSTR;

//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     // r_winnt

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TUCHAR, *PTUCHAR;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote      // r_winnt

#else   /* UNICODE */               // r_winnt

#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TUCHAR, *PTUCHAR;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;
#define __TEXT(quote) quote         // r_winnt

#endif /* UNICODE */                // r_winnt
#define TEXT(quote) __TEXT(quote)   // r_winnt


// end_winnt

typedef double DOUBLE;

typedef struct _QUAD {              // QUAD is for those times we want
    double  DoNotUseThisField;      // an 8 byte aligned 8 byte long structure
} QUAD;                             // which is NOT really a floating point
                                    // number.  Use DOUBLE if you want an FP
                                    // number.

//
// Pointer to Basics
//

typedef SHORT *PSHORT;  // winnt
typedef LONG *PLONG;    // winnt
typedef QUAD *PQUAD;

//
// Unsigned Basics
//

// Tell windef.h that some types are already defined.
#define BASETYPES

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef QUAD UQUAD;

//
// Pointer to Unsigned Basics
//

typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef ULONG *PULONG;
typedef UQUAD *PUQUAD;

//
// Signed characters
//

typedef signed char SCHAR;
typedef SCHAR *PSCHAR;

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif

//
// Handle to an Object
//

// begin_winnt

#ifdef STRICT
typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

//
// Flag (bit) fields
//

typedef UCHAR  FCHAR;
typedef USHORT FSHORT;
typedef ULONG  FLONG;

// end_winnt

//
// Low order two bits of a handle are ignored by the system and available
// for use by application code as tag bits.  The remaining bits are opaque
// and used to store a serial number and table index.
//

#define OBJ_HANDLE_TAGBITS  0x00000003L

//
// Cardinal Data Types [0 - 2**N-2)
//

typedef char CCHAR;          // winnt
typedef short CSHORT;
typedef ULONG CLONG;

typedef CCHAR *PCCHAR;
typedef CSHORT *PCSHORT;
typedef CLONG *PCLONG;


//
// __int64 is only supported by 2.0 and later midl.
// __midl is set by the 2.0 midl and not by 1.0 midl.
//

#define _ULONGLONG_
#if (!defined(MIDL_PASS) || defined(__midl)) && (!defined(_M_IX86) || (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64))
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define MAXLONGLONG                      (0x7fffffffffffffff)
#else
typedef double LONGLONG;
typedef double ULONGLONG;
#endif

typedef LONGLONG *PLONGLONG;
typedef ULONGLONG *PULONGLONG;

// Update Sequence Number

typedef LONGLONG USN;

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
    struct {
        ULONG LowPart;
        LONG HighPart;
    };
    struct {
        ULONG LowPart;
        LONG HighPart;
    } u;
#endif //MIDL_PASS
    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;


#if defined(MIDL_PASS)
typedef struct _ULARGE_INTEGER {
#else // MIDL_PASS
typedef union _ULARGE_INTEGER {
    struct {
        ULONG LowPart;
        ULONG HighPart;
    };
    struct {
        ULONG LowPart;
        ULONG HighPart;
    } u;
#endif //MIDL_PASS
    ULONGLONG QuadPart;
} ULARGE_INTEGER;

typedef ULARGE_INTEGER *PULARGE_INTEGER;


//
// Boolean
//

typedef UCHAR BOOLEAN;           // winnt
typedef BOOLEAN *PBOOLEAN;       // winnt


//
// Constants
//

#define FALSE   0
#define TRUE    1

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif // NULL


//
// Macros used to eliminate compiler warning generated when formal
// parameters or local variables are not declared.
//
// Use DBG_UNREFERENCED_PARAMETER() when a parameter is not yet
// referenced but will be once the module is completely developed.
//
// Use DBG_UNREFERENCED_LOCAL_VARIABLE() when a local variable is not yet
// referenced but will be once the module is completely developed.
//
// Use UNREFERENCED_PARAMETER() if a parameter will never be referenced.
//
// DBG_UNREFERENCED_PARAMETER and DBG_UNREFERENCED_LOCAL_VARIABLE will
// eventually be made into a null macro to help determine whether there
// is unfinished work.
//

#if ! (defined(lint) || defined(_lint))
#define UNREFERENCED_PARAMETER(P)          (P)
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)

#else // lint or _lint

// Note: lint -e530 says don't complain about uninitialized variables for
// this.  line +e530 turns that checking back on.  Error 527 has to do with
// unreachable code.

#define UNREFERENCED_PARAMETER(P)          \
    /*lint -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint +e527 +e530 */
#define DBG_UNREFERENCED_PARAMETER(P)      \
    /*lint -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint +e527 +e530 */
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) \
    /*lint -e527 -e530 */ \
    { \
        (V) = (V); \
    } \
    /*lint +e527 +e530 */

#endif // lint or _lint



//
// IOCTL_TAPE_ERASE definitions
//

#define TAPE_ERASE_SHORT            0L
#define TAPE_ERASE_LONG             1L

typedef struct _TAPE_ERASE {
    ULONG Type;
    BOOLEAN Immediate;
} TAPE_ERASE, *PTAPE_ERASE;

//
// IOCTL_TAPE_PREPARE definitions
//

#define TAPE_LOAD                   0L
#define TAPE_UNLOAD                 1L
#define TAPE_TENSION                2L
#define TAPE_LOCK                   3L
#define TAPE_UNLOCK                 4L
#define TAPE_FORMAT                 5L

typedef struct _TAPE_PREPARE {
    ULONG Operation;
    BOOLEAN Immediate;
} TAPE_PREPARE, *PTAPE_PREPARE;

//
// IOCTL_TAPE_WRITE_MARKS definitions
//

#define TAPE_SETMARKS               0L
#define TAPE_FILEMARKS              1L
#define TAPE_SHORT_FILEMARKS        2L
#define TAPE_LONG_FILEMARKS         3L

typedef struct _TAPE_WRITE_MARKS {
    ULONG Type;
    ULONG Count;
    BOOLEAN Immediate;
} TAPE_WRITE_MARKS, *PTAPE_WRITE_MARKS;

//
// IOCTL_TAPE_GET_POSITION definitions
//

#define TAPE_ABSOLUTE_POSITION       0L
#define TAPE_LOGICAL_POSITION        1L
#define TAPE_PSEUDO_LOGICAL_POSITION 2L

typedef struct _TAPE_GET_POSITION {
    ULONG Type;
    ULONG Partition;
    LARGE_INTEGER Offset;
} TAPE_GET_POSITION, *PTAPE_GET_POSITION;

//
// IOCTL_TAPE_SET_POSITION definitions
//

#define TAPE_REWIND                 0L
#define TAPE_ABSOLUTE_BLOCK         1L
#define TAPE_LOGICAL_BLOCK          2L
#define TAPE_PSEUDO_LOGICAL_BLOCK   3L
#define TAPE_SPACE_END_OF_DATA      4L
#define TAPE_SPACE_RELATIVE_BLOCKS  5L
#define TAPE_SPACE_FILEMARKS        6L
#define TAPE_SPACE_SEQUENTIAL_FMKS  7L
#define TAPE_SPACE_SETMARKS         8L
#define TAPE_SPACE_SEQUENTIAL_SMKS  9L

typedef struct _TAPE_SET_POSITION {
    ULONG Method;
    ULONG Partition;
    LARGE_INTEGER Offset;
    BOOLEAN Immediate;
} TAPE_SET_POSITION, *PTAPE_SET_POSITION;

//
// IOCTL_TAPE_GET_DRIVE_PARAMS definitions
//

//
// Definitions for FeaturesLow parameter
//

#define TAPE_DRIVE_FIXED            0x00000001
#define TAPE_DRIVE_SELECT           0x00000002
#define TAPE_DRIVE_INITIATOR        0x00000004

#define TAPE_DRIVE_ERASE_SHORT      0x00000010
#define TAPE_DRIVE_ERASE_LONG       0x00000020
#define TAPE_DRIVE_ERASE_BOP_ONLY   0x00000040
#define TAPE_DRIVE_ERASE_IMMEDIATE  0x00000080

#define TAPE_DRIVE_TAPE_CAPACITY    0x00000100
#define TAPE_DRIVE_TAPE_REMAINING   0x00000200
#define TAPE_DRIVE_FIXED_BLOCK      0x00000400
#define TAPE_DRIVE_VARIABLE_BLOCK   0x00000800

#define TAPE_DRIVE_WRITE_PROTECT    0x00001000
#define TAPE_DRIVE_EOT_WZ_SIZE      0x00002000

#define TAPE_DRIVE_ECC              0x00010000
#define TAPE_DRIVE_COMPRESSION      0x00020000
#define TAPE_DRIVE_PADDING          0x00040000
#define TAPE_DRIVE_REPORT_SMKS      0x00080000

#define TAPE_DRIVE_GET_ABSOLUTE_BLK 0x00100000
#define TAPE_DRIVE_GET_LOGICAL_BLK  0x00200000
#define TAPE_DRIVE_SET_EOT_WZ_SIZE  0x00400000

#define TAPE_DRIVE_EJECT_MEDIA      0x01000000

#define TAPE_DRIVE_RESERVED_BIT     0x80000000  //don't use this bit!
//                                              //can't be a low features bit!
//                                              //reserved; high features only

//
// Definitions for FeaturesHigh parameter
//

#define TAPE_DRIVE_LOAD_UNLOAD      0x80000001
#define TAPE_DRIVE_TENSION          0x80000002
#define TAPE_DRIVE_LOCK_UNLOCK      0x80000004
#define TAPE_DRIVE_REWIND_IMMEDIATE 0x80000008

#define TAPE_DRIVE_SET_BLOCK_SIZE   0x80000010
#define TAPE_DRIVE_LOAD_UNLD_IMMED  0x80000020
#define TAPE_DRIVE_TENSION_IMMED    0x80000040
#define TAPE_DRIVE_LOCK_UNLK_IMMED  0x80000080

#define TAPE_DRIVE_SET_ECC          0x80000100
#define TAPE_DRIVE_SET_COMPRESSION  0x80000200
#define TAPE_DRIVE_SET_PADDING      0x80000400
#define TAPE_DRIVE_SET_REPORT_SMKS  0x80000800

#define TAPE_DRIVE_ABSOLUTE_BLK     0x80001000
#define TAPE_DRIVE_ABS_BLK_IMMED    0x80002000
#define TAPE_DRIVE_LOGICAL_BLK      0x80004000
#define TAPE_DRIVE_LOG_BLK_IMMED    0x80008000

#define TAPE_DRIVE_END_OF_DATA      0x80010000
#define TAPE_DRIVE_RELATIVE_BLKS    0x80020000
#define TAPE_DRIVE_FILEMARKS        0x80040000
#define TAPE_DRIVE_SEQUENTIAL_FMKS  0x80080000

#define TAPE_DRIVE_SETMARKS         0x80100000
#define TAPE_DRIVE_SEQUENTIAL_SMKS  0x80200000
#define TAPE_DRIVE_REVERSE_POSITION 0x80400000
#define TAPE_DRIVE_SPACE_IMMEDIATE  0x80800000

#define TAPE_DRIVE_WRITE_SETMARKS   0x81000000
#define TAPE_DRIVE_WRITE_FILEMARKS  0x82000000
#define TAPE_DRIVE_WRITE_SHORT_FMKS 0x84000000
#define TAPE_DRIVE_WRITE_LONG_FMKS  0x88000000

#define TAPE_DRIVE_WRITE_MARK_IMMED 0x90000000
#define TAPE_DRIVE_FORMAT           0xA0000000
#define TAPE_DRIVE_FORMAT_IMMEDIATE 0xC0000000
#define TAPE_DRIVE_HIGH_FEATURES    0x80000000  //mask for high features flag

typedef struct _TAPE_GET_DRIVE_PARAMETERS {
    BOOLEAN ECC;
    BOOLEAN Compression;
    BOOLEAN DataPadding;
    BOOLEAN ReportSetmarks;
    ULONG DefaultBlockSize;
    ULONG MaximumBlockSize;
    ULONG MinimumBlockSize;
    ULONG MaximumPartitionCount;
    ULONG FeaturesLow;
    ULONG FeaturesHigh;
    ULONG EOTWarningZoneSize;
} TAPE_GET_DRIVE_PARAMETERS, *PTAPE_GET_DRIVE_PARAMETERS;

//
// IOCTL_TAPE_SET_DRIVE_PARAMETERS definitions
//

typedef struct _TAPE_SET_DRIVE_PARAMETERS {
    BOOLEAN ECC;
    BOOLEAN Compression;
    BOOLEAN DataPadding;
    BOOLEAN ReportSetmarks;
    ULONG EOTWarningZoneSize;
} TAPE_SET_DRIVE_PARAMETERS, *PTAPE_SET_DRIVE_PARAMETERS;

//
// IOCTL_TAPE_GET_MEDIA_PARAMETERS definitions
//

typedef struct _TAPE_GET_MEDIA_PARAMETERS {
    LARGE_INTEGER Capacity;
    LARGE_INTEGER Remaining;
    ULONG BlockSize;
    ULONG PartitionCount;
    BOOLEAN WriteProtected;
} TAPE_GET_MEDIA_PARAMETERS, *PTAPE_GET_MEDIA_PARAMETERS;

//
// IOCTL_TAPE_SET_MEDIA_PARAMETERS definitions
//

typedef struct _TAPE_SET_MEDIA_PARAMETERS {
    ULONG BlockSize;
} TAPE_SET_MEDIA_PARAMETERS, *PTAPE_SET_MEDIA_PARAMETERS;

//
// IOCTL_TAPE_CREATE_PARTITION definitions
//

#define TAPE_FIXED_PARTITIONS       0L
#define TAPE_SELECT_PARTITIONS      1L
#define TAPE_INITIATOR_PARTITIONS   2L

typedef struct _TAPE_CREATE_PARTITION {
    ULONG Method;
    ULONG Count;
    ULONG Size;
} TAPE_CREATE_PARTITION, *PTAPE_CREATE_PARTITION;


#define MAXIMUM_CDB_SIZE 12


//
// SCSI I/O Request Block
//

typedef struct _SCSI_REQUEST_BLOCK {
    USHORT Length;                  // offset 0
    UCHAR Function;                 // offset 2
    UCHAR SrbStatus;                // offset 3
    UCHAR ScsiStatus;               // offset 4
    UCHAR PathId;                   // offset 5
    UCHAR TargetId;                 // offset 6
    UCHAR Lun;                      // offset 7
    UCHAR QueueTag;                 // offset 8
    UCHAR QueueAction;              // offset 9
    UCHAR CdbLength;                // offset a
    UCHAR SenseInfoBufferLength;    // offset b
    ULONG SrbFlags;                 // offset c
    ULONG DataTransferLength;       // offset 10
    ULONG TimeOutValue;             // offset 14
    PVOID DataBuffer;               // offset 18
    PVOID SenseInfoBuffer;          // offset 1c
    struct _SCSI_REQUEST_BLOCK *NextSrb; // offset 20
    PVOID OriginalRequest;          // offset 24
    PVOID SrbExtension;             // offset 28
    ULONG QueueSortKey;             // offset 2c
    UCHAR Cdb[16];                  // offset 30
} SCSI_REQUEST_BLOCK, *PSCSI_REQUEST_BLOCK;

#define SCSI_REQUEST_BLOCK_SIZE sizeof(SCSI_REQUEST_BLOCK)

//
// SRB Functions
//

#define SRB_FUNCTION_EXECUTE_SCSI           0x00
#define SRB_FUNCTION_CLAIM_DEVICE           0x01
#define SRB_FUNCTION_IO_CONTROL             0x02
#define SRB_FUNCTION_RECEIVE_EVENT          0x03
#define SRB_FUNCTION_RELEASE_QUEUE          0x04
#define SRB_FUNCTION_ATTACH_DEVICE          0x05
#define SRB_FUNCTION_RELEASE_DEVICE         0x06
#define SRB_FUNCTION_SHUTDOWN               0x07
#define SRB_FUNCTION_FLUSH                  0x08
#define SRB_FUNCTION_ABORT_COMMAND          0x10
#define SRB_FUNCTION_RELEASE_RECOVERY       0x11
#define SRB_FUNCTION_RESET_BUS              0x12
#define SRB_FUNCTION_RESET_DEVICE           0x13
#define SRB_FUNCTION_TERMINATE_IO           0x14
#define SRB_FUNCTION_FLUSH_QUEUE            0x15
#define SRB_FUNCTION_REMOVE_DEVICE          0x16

//
// SRB Status
//

#define SRB_STATUS_PENDING                  0x00
#define SRB_STATUS_SUCCESS                  0x01
#define SRB_STATUS_ABORTED                  0x02
#define SRB_STATUS_ABORT_FAILED             0x03
#define SRB_STATUS_ERROR                    0x04
#define SRB_STATUS_BUSY                     0x05
#define SRB_STATUS_INVALID_REQUEST          0x06
#define SRB_STATUS_INVALID_PATH_ID          0x07
#define SRB_STATUS_NO_DEVICE                0x08
#define SRB_STATUS_TIMEOUT                  0x09
#define SRB_STATUS_SELECTION_TIMEOUT        0x0A
#define SRB_STATUS_COMMAND_TIMEOUT          0x0B
#define SRB_STATUS_MESSAGE_REJECTED         0x0D
#define SRB_STATUS_BUS_RESET                0x0E
#define SRB_STATUS_PARITY_ERROR             0x0F
#define SRB_STATUS_REQUEST_SENSE_FAILED     0x10
#define SRB_STATUS_NO_HBA                   0x11
#define SRB_STATUS_DATA_OVERRUN             0x12
#define SRB_STATUS_UNEXPECTED_BUS_FREE      0x13
#define SRB_STATUS_PHASE_SEQUENCE_FAILURE   0x14
#define SRB_STATUS_BAD_SRB_BLOCK_LENGTH     0x15
#define SRB_STATUS_REQUEST_FLUSHED          0x16
#define SRB_STATUS_INVALID_LUN              0x20
#define SRB_STATUS_INVALID_TARGET_ID        0x21
#define SRB_STATUS_BAD_FUNCTION             0x22
#define SRB_STATUS_ERROR_RECOVERY           0x23

//
// SRB Status Masks
//

#define SRB_STATUS_QUEUE_FROZEN             0x40
#define SRB_STATUS_AUTOSENSE_VALID          0x80

#define SRB_STATUS(Status) (Status & ~(SRB_STATUS_AUTOSENSE_VALID | SRB_STATUS_QUEUE_FROZEN))

//
// SRB Flag Bits
//

#define SRB_FLAGS_QUEUE_ACTION_ENABLE       0x00000002
#define SRB_FLAGS_DISABLE_DISCONNECT        0x00000004
#define SRB_FLAGS_DISABLE_SYNCH_TRANSFER    0x00000008
#define SRB_FLAGS_BYPASS_FROZEN_QUEUE       0x00000010
#define SRB_FLAGS_DISABLE_AUTOSENSE         0x00000020
#define SRB_FLAGS_DATA_IN                   0x00000040
#define SRB_FLAGS_DATA_OUT                  0x00000080
#define SRB_FLAGS_NO_DATA_TRANSFER          0x00000000
#define SRB_FLAGS_UNSPECIFIED_DIRECTION      (SRB_FLAGS_DATA_IN | SRB_FLAGS_DATA_OUT)
#define SRB_FLAGS_NO_QUEUE_FREEZE           0x00000100
#define SRB_FLAGS_ADAPTER_CACHE_ENABLE      0x00000200
#define SRB_FLAGS_IS_ACTIVE                 0x00010000
#define SRB_FLAGS_ALLOCATED_FROM_ZONE       0x00020000
#define SRB_FLAGS_SGLIST_FROM_POOL          0x00040000

//
// Queue Action
//

#define SRB_SIMPLE_TAG_REQUEST              0x20
#define SRB_HEAD_OF_QUEUE_TAG_REQUEST       0x21
#define SRB_ORDERED_QUEUE_TAG_REQUEST       0x22


#ifndef _NTDDK_
#define SCSIPORT_API DECLSPEC_IMPORT
#else
#define SCSIPORT_API
#endif


SCSIPORT_API
VOID
ScsiDebugPrint(
    ULONG DebugPrintLevel,
    PCCHAR DebugMessage,
    ...
    );


//
// Command Descriptor Block. Passed by SCSI controller chip over the SCSI bus
//

typedef union _CDB {

    //
    // Generic 6-Byte CDB
    //

    struct _CDB6GENERIC {
       UCHAR  OperationCode;
       UCHAR  Immediate : 1;
       UCHAR  CommandUniqueBits : 4;
       UCHAR  LogicalUnitNumber : 3;
       UCHAR  CommandUniqueBytes[3];
       UCHAR  Link : 1;
       UCHAR  Flag : 1;
       UCHAR  Reserved : 4;
       UCHAR  VendorUnique : 2;
    } CDB6GENERIC, *PCDB6GENERIC;

    //
    // Standard 6-byte CDB
    //

    struct _CDB6READWRITE {
        UCHAR OperationCode;
        UCHAR LogicalBlockMsb1 : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR LogicalBlockMsb0;
        UCHAR LogicalBlockLsb;
        UCHAR TransferBlocks;
        UCHAR Control;
    } CDB6READWRITE, *PCDB6READWRITE;


    //
    // SCSI Inquiry CDB
    //

    struct _CDB6INQUIRY {
        UCHAR OperationCode;
        UCHAR Reserved1 : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR PageCode;
        UCHAR IReserved;
        UCHAR AllocationLength;
        UCHAR Control;
    } CDB6INQUIRY, *PCDB6INQUIRY;

    //
    // SCSI Format CDB
    //

    struct _CDB6FORMAT {
        UCHAR OperationCode;
        UCHAR FormatControl : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR FReserved1;
        UCHAR InterleaveMsb;
        UCHAR InterleaveLsb;
        UCHAR FReserved2;
    } CDB6FORMAT, *PCDB6FORMAT;

    //
    // Standard 10-byte CDB

    struct _CDB10 {
        UCHAR OperationCode;
        UCHAR RelativeAddress : 1;
        UCHAR Reserved1 : 2;
        UCHAR ForceUnitAccess : 1;
        UCHAR DisablePageOut : 1;
        UCHAR LogicalUnitNumber : 3;
        UCHAR LogicalBlockByte0;
        UCHAR LogicalBlockByte1;
        UCHAR LogicalBlockByte2;
        UCHAR LogicalBlockByte3;
        UCHAR Reserved2;
        UCHAR TransferBlocksMsb;
        UCHAR TransferBlocksLsb;
        UCHAR Control;
    } CDB10, *PCDB10;

    //
    // CD Rom Audio CDBs
    //

    struct _PAUSE_RESUME {
        UCHAR OperationCode;
        UCHAR Reserved1 : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[6];
        UCHAR Action;
        UCHAR Control;
    } PAUSE_RESUME, *PPAUSE_RESUME;

    //
    // Read Table of Contents
    //

    struct _READ_TOC {
        UCHAR OperationCode;
        UCHAR Reserved0 : 1;
        UCHAR Msf : 1;
        UCHAR Reserved1 : 3;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[4];
        UCHAR StartingTrack;
        UCHAR AllocationLength[2];
        UCHAR Control : 6;
        UCHAR Format : 2;
    } READ_TOC, *PREAD_TOC;

    struct _PLAY_AUDIO_MSF {
        UCHAR OperationCode;
        UCHAR Reserved1 : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2;
        UCHAR StartingM;
        UCHAR StartingS;
        UCHAR StartingF;
        UCHAR EndingM;
        UCHAR EndingS;
        UCHAR EndingF;
        UCHAR Control;
    } PLAY_AUDIO_MSF, *PPLAY_AUDIO_MSF;

    //
    // Read SubChannel Data
    //

    struct _SUBCHANNEL {
        UCHAR OperationCode;
        UCHAR Reserved0 : 1;
        UCHAR Msf : 1;
        UCHAR Reserved1 : 3;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2 : 6;
        UCHAR SubQ : 1;
        UCHAR Reserved3 : 1;
        UCHAR Format;
        UCHAR Reserved4[2];
        UCHAR TrackNumber;
        UCHAR AllocationLength[2];
        UCHAR Control;
    } SUBCHANNEL, *PSUBCHANNEL;

    //
    // Read CD. Used by Atapi for raw sector reads.
    //

    struct _READ_CD {
        UCHAR OperationCode;
        UCHAR Reserved0 : 2;
        UCHAR ExpectedSectorType : 3;
        UCHAR Reserved1 : 3;
        UCHAR StartingLBA[4];
        UCHAR TransferBlocks[3];
        UCHAR Reserved2 : 1;
        UCHAR ErrorFlags : 2;
        UCHAR IncludeEDC : 1;
        UCHAR IncludeUserData : 1;
        UCHAR HeaderCode : 2;
        UCHAR IncludeSyncData : 1;
        UCHAR SubChannelSelection : 3;
        UCHAR Reserved3 : 5;
        UCHAR Reserved4;
    } READ_CD, *PREAD_CD;

    //
    // Plextor Read CD-DA
    //

    struct _PLXTR_READ_CDDA {
        UCHAR OperationCode;
        UCHAR Reserved0 : 5;
        UCHAR LogicalUnitNumber :3;
        UCHAR LogicalBlockByte0;
        UCHAR LogicalBlockByte1;
        UCHAR LogicalBlockByte2;
        UCHAR LogicalBlockByte3;
        UCHAR TransferBlockByte0;
        UCHAR TransferBlockByte1;
        UCHAR TransferBlockByte2;
        UCHAR TransferBlockByte3;
        UCHAR SubCode;
        UCHAR Control;
    } PLXTR_READ_CDDA, *PPLXTR_READ_CDDA;

    //
    // NEC Read CD-DA
    //

    struct _NEC_READ_CDDA {
        UCHAR OperationCode;
        UCHAR Reserved0;
        UCHAR LogicalBlockByte0;
        UCHAR LogicalBlockByte1;
        UCHAR LogicalBlockByte2;
        UCHAR LogicalBlockByte3;
        UCHAR Reserved1;
        UCHAR TransferBlockByte0;
        UCHAR TransferBlockByte1;
        UCHAR Control;
    } NEC_READ_CDDA, *PNEC_READ_CDDA;

    //
    // Mode sense
    //

    struct _MODE_SENSE {
        UCHAR OperationCode;
        UCHAR Reserved1 : 3;
        UCHAR Dbd : 1;
        UCHAR Reserved2 : 1;
        UCHAR LogicalUnitNumber : 3;
        UCHAR PageCode : 6;
        UCHAR Pc : 2;
        UCHAR Reserved3;
        UCHAR AllocationLength;
        UCHAR Control;
    } MODE_SENSE, *PMODE_SENSE;

    struct _MODE_SENSE10 {
        UCHAR OperationCode;
        UCHAR Reserved1 : 3;
        UCHAR Dbd : 1;
        UCHAR Reserved2 : 1;
        UCHAR LogicalUnitNumber : 3;
        UCHAR PageCode : 6;
        UCHAR Pc : 2;
        UCHAR Reserved3[4];
        UCHAR AllocationLength[2];
        UCHAR Control;
    } MODE_SENSE10, *PMODE_SENSE10;

    //
    // Mode select
    //

    struct _MODE_SELECT {
        UCHAR OperationCode;
        UCHAR SPBit : 1;
        UCHAR Reserved1 : 3;
        UCHAR PFBit : 1;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[2];
        UCHAR ParameterListLength;
        UCHAR Control;
    } MODE_SELECT, *PMODE_SELECT;

    struct _MODE_SELECT10 {
        UCHAR OperationCode;
        UCHAR SPBit : 1;
        UCHAR Reserved1 : 3;
        UCHAR PFBit : 1;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[5];
        UCHAR ParameterListLength[2];
        UCHAR Control;
    } MODE_SELECT10, *PMODE_SELECT10;

    struct _LOCATE {
        UCHAR OperationCode;
        UCHAR Immediate : 1;
        UCHAR CPBit : 1;
        UCHAR BTBit : 1;
        UCHAR Reserved1 : 2;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved3;
        UCHAR LogicalBlockAddress[4];
        UCHAR Reserved4;
        UCHAR Partition;
        UCHAR Control;
    } LOCATE, *PLOCATE;

    struct _LOGSENSE {
        UCHAR OperationCode;
        UCHAR SPBit : 1;
        UCHAR PPCBit : 1;
        UCHAR Reserved1 : 3;
        UCHAR LogicalUnitNumber : 3;
        UCHAR PageCode : 6;
        UCHAR PCBit : 2;
        UCHAR Reserved2;
        UCHAR Reserved3;
        UCHAR ParameterPointer[2];  // [0]=MSB, [1]=LSB
        UCHAR AllocationLength[2];  // [0]=MSB, [1]=LSB
        UCHAR Control;
    } LOGSENSE, *PLOGSENSE;

    struct _PRINT {
        UCHAR OperationCode;
        UCHAR Reserved : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR TransferLength[3];
        UCHAR Control;
    } PRINT, *PPRINT;

    struct _SEEK {
        UCHAR OperationCode;
        UCHAR Reserved1 : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR LogicalBlockAddress[4];
        UCHAR Reserved2[3];
        UCHAR Control;
    } SEEK, *PSEEK;

    struct _ERASE {
        UCHAR OperationCode;
        UCHAR Long : 1;
        UCHAR Immediate : 1;
        UCHAR Reserved1 : 3;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[3];
        UCHAR Control;
    } ERASE, *PERASE;

    struct _START_STOP {
        UCHAR OperationCode;
        UCHAR Immediate: 1;
        UCHAR Reserved1 : 4;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[2];
        UCHAR Start : 1;
        UCHAR LoadEject : 1;
        UCHAR Reserved3 : 6;
        UCHAR Control;
    } START_STOP, *PSTART_STOP;

    struct _MEDIA_REMOVAL {
        UCHAR OperationCode;
        UCHAR Reserved1 : 5;
        UCHAR LogicalUnitNumber : 3;
        UCHAR Reserved2[2];
        UCHAR Prevent;
        UCHAR Control;
    } MEDIA_REMOVAL, *PMEDIA_REMOVAL;

    //
    // Tape CDBs
    //

    struct _SEEK_BLOCK {
        UCHAR OperationCode;
        UCHAR Immediate : 1;
        UCHAR Reserved1 : 7;
        UCHAR BlockAddress[3];
        UCHAR Link : 1;
        UCHAR Flag : 1;
        UCHAR Reserved2 : 4;
        UCHAR VendorUnique : 2;
    } SEEK_BLOCK, *PSEEK_BLOCK;

    struct _REQUEST_BLOCK_ADDRESS {
        UCHAR OperationCode;
        UCHAR Reserved1[3];
        UCHAR AllocationLength;
        UCHAR Link : 1;
        UCHAR Flag : 1;
        UCHAR Reserved2 : 4;
        UCHAR VendorUnique : 2;
    } REQUEST_BLOCK_ADDRESS, *PREQUEST_BLOCK_ADDRESS;

    struct _PARTITION {
        UCHAR OperationCode;
        UCHAR Immediate : 1;
        UCHAR Sel: 1;
        UCHAR PartitionSelect : 6;
        UCHAR Reserved1[3];
        UCHAR Control;
    } PARTITION, *PPARTITION;

    struct _WRITE_TAPE_MARKS {
        UCHAR OperationCode;
        UCHAR Immediate : 1;
        UCHAR WriteSetMarks: 1;
        UCHAR Reserved : 3;
        UCHAR LogicalUnitNumber : 3;
        UCHAR TransferLength[3];
        UCHAR Control;
    } WRITE_TAPE_MARKS, *PWRITE_TAPE_MARKS;

    struct _SPACE_TAPE_MARKS {
        UCHAR OperationCode;
        UCHAR Code : 3;
        UCHAR Reserved : 2;
        UCHAR LogicalUnitNumber : 3;
        UCHAR NumMarksMSB ;
        UCHAR NumMarks;
        UCHAR NumMarksLSB;
        union {
            UCHAR value;
            struct {
                UCHAR Link : 1;
                UCHAR Flag : 1;
                UCHAR Reserved : 4;
                UCHAR VendorUnique : 2;
            } Fields;
        } Byte6;
    } SPACE_TAPE_MARKS, *PSPACE_TAPE_MARKS;

    //
    // Read tape position
    //

    struct _READ_POSITION {
        UCHAR Operation;
        UCHAR BlockType:1;
        UCHAR Reserved1:4;
        UCHAR Lun:3;
        UCHAR Reserved2[7];
        UCHAR Control;
    } READ_POSITION, *PREAD_POSITION;

    //
    // ReadWrite for Tape
    //

    struct _CDB6READWRITETAPE {
        UCHAR OperationCode;
        UCHAR VendorSpecific : 5;
        UCHAR Reserved : 3;
        UCHAR TransferLenMSB;
        UCHAR TransferLen;
        UCHAR TransferLenLSB;
        UCHAR Link : 1;
        UCHAR Flag : 1;
        UCHAR Reserved1 : 4;
        UCHAR VendorUnique : 2;
     } CDB6READWRITETAPE, *PCDB6READWRITETAPE;

    //
    // Atapi 2.5 Changer 12-byte CDBs
    //

    struct _LOAD_UNLOAD {
        UCHAR OperationCode;
        UCHAR Immediate : 1;
        UCHAR Reserved1 : 7;
        UCHAR Reserved2[2];
        UCHAR Start : 1;
        UCHAR LoadEject : 1;
        UCHAR Reserved3: 6;
        UCHAR Reserved4[3];
        UCHAR Slot;
        UCHAR Reserved5[3];
    } LOAD_UNLOAD, *PLOAD_UNLOAD;

    struct _MECH_STATUS {
        UCHAR OperationCode;
        UCHAR Reserved1[7];
        UCHAR AllocationLength[2];
        UCHAR Reserved2[2];
    } MECH_STATUS, *PMECH_STATUS;

} CDB, *PCDB;

//
// Command Descriptor Block constants.
//

#define CDB6GENERIC_LENGTH                   6
#define CDB10GENERIC_LENGTH                  10
#define CDB12GENERIC_LENGTH                  12

#define SETBITON                             1
#define SETBITOFF                            0
//
// Mode Sense/Select page constants.
//

#define MODE_PAGE_ERROR_RECOVERY        0x01
#define MODE_PAGE_DISCONNECT            0x02
#define MODE_PAGE_FORMAT_DEVICE         0x03
#define MODE_PAGE_RIGID_GEOMETRY        0x04
#define MODE_PAGE_FLEXIBILE             0x05
#define MODE_PAGE_VERIFY_ERROR          0x07
#define MODE_PAGE_CACHING               0x08
#define MODE_PAGE_PERIPHERAL            0x09
#define MODE_PAGE_CONTROL               0x0A
#define MODE_PAGE_MEDIUM_TYPES          0x0B
#define MODE_PAGE_NOTCH_PARTITION       0x0C
#define MODE_SENSE_RETURN_ALL           0x3f
#define MODE_SENSE_CURRENT_VALUES       0x00
#define MODE_SENSE_CHANGEABLE_VALUES    0x40
#define MODE_SENSE_DEFAULT_VAULES       0x80
#define MODE_SENSE_SAVED_VALUES         0xc0
#define MODE_PAGE_DEVICE_CONFIG         0x10
#define MODE_PAGE_MEDIUM_PARTITION      0x11
#define MODE_PAGE_DATA_COMPRESS         0x0f
#define MODE_PAGE_CAPABILITIES          0x2A

//
// SCSI CDB operation codes
//

#define SCSIOP_TEST_UNIT_READY     0x00
#define SCSIOP_REZERO_UNIT         0x01
#define SCSIOP_REWIND              0x01
#define SCSIOP_REQUEST_BLOCK_ADDR  0x02
#define SCSIOP_REQUEST_SENSE       0x03
#define SCSIOP_FORMAT_UNIT         0x04
#define SCSIOP_READ_BLOCK_LIMITS   0x05
#define SCSIOP_REASSIGN_BLOCKS     0x07
#define SCSIOP_READ6               0x08
#define SCSIOP_RECEIVE             0x08
#define SCSIOP_WRITE6              0x0A
#define SCSIOP_PRINT               0x0A
#define SCSIOP_SEND                0x0A
#define SCSIOP_SEEK6               0x0B
#define SCSIOP_TRACK_SELECT        0x0B
#define SCSIOP_SLEW_PRINT          0x0B
#define SCSIOP_SEEK_BLOCK          0x0C
#define SCSIOP_PARTITION           0x0D
#define SCSIOP_READ_REVERSE        0x0F
#define SCSIOP_WRITE_FILEMARKS     0x10
#define SCSIOP_FLUSH_BUFFER        0x10
#define SCSIOP_SPACE               0x11
#define SCSIOP_INQUIRY             0x12
#define SCSIOP_VERIFY6             0x13
#define SCSIOP_RECOVER_BUF_DATA    0x14
#define SCSIOP_MODE_SELECT         0x15
#define SCSIOP_RESERVE_UNIT        0x16
#define SCSIOP_RELEASE_UNIT        0x17
#define SCSIOP_COPY                0x18
#define SCSIOP_ERASE               0x19
#define SCSIOP_MODE_SENSE          0x1A
#define SCSIOP_START_STOP_UNIT     0x1B
#define SCSIOP_STOP_PRINT          0x1B
#define SCSIOP_LOAD_UNLOAD         0x1B
#define SCSIOP_RECEIVE_DIAGNOSTIC  0x1C
#define SCSIOP_SEND_DIAGNOSTIC     0x1D
#define SCSIOP_MEDIUM_REMOVAL      0x1E
#define SCSIOP_READ_CAPACITY       0x25
#define SCSIOP_READ                0x28
#define SCSIOP_WRITE               0x2A
#define SCSIOP_SEEK                0x2B
#define SCSIOP_LOCATE              0x2B
#define SCSIOP_WRITE_VERIFY        0x2E
#define SCSIOP_VERIFY              0x2F
#define SCSIOP_SEARCH_DATA_HIGH    0x30
#define SCSIOP_SEARCH_DATA_EQUAL   0x31
#define SCSIOP_SEARCH_DATA_LOW     0x32
#define SCSIOP_SET_LIMITS          0x33
#define SCSIOP_READ_POSITION       0x34
#define SCSIOP_SYNCHRONIZE_CACHE   0x35
#define SCSIOP_COMPARE             0x39
#define SCSIOP_COPY_COMPARE        0x3A
#define SCSIOP_WRITE_DATA_BUFF     0x3B
#define SCSIOP_READ_DATA_BUFF      0x3C
#define SCSIOP_CHANGE_DEFINITION   0x40
#define SCSIOP_READ_SUB_CHANNEL    0x42
#define SCSIOP_READ_TOC            0x43
#define SCSIOP_READ_HEADER         0x44
#define SCSIOP_PLAY_AUDIO          0x45
#define SCSIOP_PLAY_AUDIO_MSF      0x47
#define SCSIOP_PLAY_TRACK_INDEX    0x48
#define SCSIOP_PLAY_TRACK_RELATIVE 0x49
#define SCSIOP_PAUSE_RESUME        0x4B
#define SCSIOP_LOG_SELECT          0x4C
#define SCSIOP_LOG_SENSE           0x4D
#define SCSIOP_MODE_SELECT10       0x55
#define SCSIOP_MODE_SENSE10        0x5A
#define SCSIOP_LOAD_UNLOAD_SLOT    0xA6
#define SCSIOP_MECHANISM_STATUS    0xBD
#define SCSIOP_READ_CD             0xBE

//
// If the IMMED bit is 1, status is returned as soon
// as the operation is initiated. If the IMMED bit
// is 0, status is not returned until the operation
// is completed.
//

#define CDB_RETURN_ON_COMPLETION   0
#define CDB_RETURN_IMMEDIATE       1


//
// Inquiry buffer structure. This is the data returned from the target
// after it receives an inquiry.
//
// This structure may be extended by the number of bytes specified
// in the field AdditionalLength. The defined size constant only
// includes fields through ProductRevisionLevel.
//
// The NT SCSI drivers are only interested in the first 36 bytes of data.
//

#define INQUIRYDATABUFFERSIZE 36

typedef struct _INQUIRYDATA {
    UCHAR DeviceType : 5;
    UCHAR DeviceTypeQualifier : 3;
    UCHAR DeviceTypeModifier : 7;
    UCHAR RemovableMedia : 1;
    UCHAR Versions;
    UCHAR ResponseDataFormat;
    UCHAR AdditionalLength;
    UCHAR Reserved[2];
    UCHAR SoftReset : 1;
    UCHAR CommandQueue : 1;
    UCHAR Reserved2 : 1;
    UCHAR LinkedCommands : 1;
    UCHAR Synchronous : 1;
    UCHAR Wide16Bit : 1;
    UCHAR Wide32Bit : 1;
    UCHAR RelativeAddressing : 1;
    UCHAR VendorId[8];
    UCHAR ProductId[16];
    UCHAR ProductRevisionLevel[4];
    UCHAR VendorSpecific[20];
    UCHAR Reserved3[40];
} INQUIRYDATA, *PINQUIRYDATA;

//
// Inquiry defines. Used to interpret data returned from target as result
// of inquiry command.
//
// DeviceType field
//

#define DIRECT_ACCESS_DEVICE            0x00    // disks
#define SEQUENTIAL_ACCESS_DEVICE        0x01    // tapes
#define PRINTER_DEVICE                  0x02    // printers
#define PROCESSOR_DEVICE                0x03    // scanners, printers, etc
#define WRITE_ONCE_READ_MULTIPLE_DEVICE 0x04    // worms
#define READ_ONLY_DIRECT_ACCESS_DEVICE  0x05    // cdroms
#define SCANNER_DEVICE                  0x06    // scanners
#define OPTICAL_DEVICE                  0x07    // optical disks
#define MEDIUM_CHANGER                  0x08    // jukebox
#define COMMUNICATION_DEVICE            0x09    // network
#define LOGICAL_UNIT_NOT_PRESENT_DEVICE 0x7F
#define DEVICE_QUALIFIER_NOT_SUPPORTED  0x03

//
// DeviceTypeQualifier field
//

#define DEVICE_CONNECTED 0x00

//
// Sense Data Format
//

typedef struct _SENSE_DATA {
    UCHAR ErrorCode:7;
    UCHAR Valid:1;
    UCHAR SegmentNumber;
    UCHAR SenseKey:4;
    UCHAR Reserved:1;
    UCHAR IncorrectLength:1;
    UCHAR EndOfMedia:1;
    UCHAR FileMark:1;
    UCHAR Information[4];
    UCHAR AdditionalSenseLength;
    UCHAR CommandSpecificInformation[4];
    UCHAR AdditionalSenseCode;
    UCHAR AdditionalSenseCodeQualifier;
    UCHAR FieldReplaceableUnitCode;
    UCHAR SenseKeySpecific[3];
} SENSE_DATA, *PSENSE_DATA;

//
// Default request sense buffer size
//

#define SENSE_BUFFER_SIZE 18

//
// Sense codes
//

#define SCSI_SENSE_NO_SENSE         0x00
#define SCSI_SENSE_RECOVERED_ERROR  0x01
#define SCSI_SENSE_NOT_READY        0x02
#define SCSI_SENSE_MEDIUM_ERROR     0x03
#define SCSI_SENSE_HARDWARE_ERROR   0x04
#define SCSI_SENSE_ILLEGAL_REQUEST  0x05
#define SCSI_SENSE_UNIT_ATTENTION   0x06
#define SCSI_SENSE_DATA_PROTECT     0x07
#define SCSI_SENSE_BLANK_CHECK      0x08
#define SCSI_SENSE_UNIQUE           0x09
#define SCSI_SENSE_COPY_ABORTED     0x0A
#define SCSI_SENSE_ABORTED_COMMAND  0x0B
#define SCSI_SENSE_EQUAL            0x0C
#define SCSI_SENSE_VOL_OVERFLOW     0x0D
#define SCSI_SENSE_MISCOMPARE       0x0E
#define SCSI_SENSE_RESERVED         0x0F

//
// Additional tape bit
//

#define SCSI_ILLEGAL_LENGTH         0x20
#define SCSI_EOM                    0x40
#define SCSI_FILE_MARK              0x80

//
// Additional Sense codes
//

#define SCSI_ADSENSE_NO_SENSE       0x00
#define SCSI_ADSENSE_LUN_NOT_READY  0x04
#define SCSI_ADSENSE_ILLEGAL_COMMAND 0x20
#define SCSI_ADSENSE_ILLEGAL_BLOCK  0x21
#define SCSI_ADSENSE_INVALID_LUN    0x25
#define SCSI_ADSENSE_INVALID_CDB    0x24
#define SCSI_ADSENSE_MUSIC_AREA     0xA0
#define SCSI_ADSENSE_DATA_AREA      0xA1
#define SCSI_ADSENSE_VOLUME_OVERFLOW 0xA7

#define SCSI_ADSENSE_NO_MEDIA_IN_DEVICE 0x3a
#define SCSI_ADWRITE_PROTECT        0x27
#define SCSI_ADSENSE_MEDIUM_CHANGED 0x28
#define SCSI_ADSENSE_BUS_RESET      0x29
#define SCSI_ADSENSE_TRACK_ERROR    0x14
#define SCSI_ADSENSE_SEEK_ERROR     0x15
#define SCSI_ADSENSE_REC_DATA_NOECC 0x17
#define SCSI_ADSENSE_REC_DATA_ECC   0x18

//
// Additional sense code qualifier
//

#define SCSI_SENSEQ_FORMAT_IN_PROGRESS 0x04
#define SCSI_SENSEQ_INIT_COMMAND_REQUIRED 0x02
#define SCSI_SENSEQ_MANUAL_INTERVENTION_REQUIRED 0x03
#define SCSI_SENSEQ_BECOMING_READY 0x01
#define SCSI_SENSEQ_FILEMARK_DETECTED 0x01
#define SCSI_SENSEQ_SETMARK_DETECTED 0x03
#define SCSI_SENSEQ_END_OF_MEDIA_DETECTED 0x02
#define SCSI_SENSEQ_BEGINNING_OF_MEDIA_DETECTED 0x04


//
// Read Capacity Data - returned in Big Endian format
//

typedef struct _READ_CAPACITY_DATA {
    ULONG LogicalBlockAddress;
    ULONG BytesPerBlock;
} READ_CAPACITY_DATA, *PREAD_CAPACITY_DATA;


//
// Read Block Limits Data - returned in Big Endian format
// This structure returns the maximum and minimum block
// size for a TAPE device.
//

typedef struct _READ_BLOCK_LIMITS {
    UCHAR Reserved;
    UCHAR BlockMaximumSize[3];
    UCHAR BlockMinimumSize[2];
} READ_BLOCK_LIMITS_DATA, *PREAD_BLOCK_LIMITS_DATA;


//
// Mode data structures.
//

//
// Define Mode parameter header.
//

typedef struct _MODE_PARAMETER_HEADER {
    UCHAR ModeDataLength;
    UCHAR MediumType;
    UCHAR DeviceSpecificParameter;
    UCHAR BlockDescriptorLength;
}MODE_PARAMETER_HEADER, *PMODE_PARAMETER_HEADER;

typedef struct _MODE_PARAMETER_HEADER10 {
    UCHAR ModeDataLength[2];
    UCHAR MediumType;
    UCHAR DeviceSpecificParameter;
    UCHAR Reserved[2];
    UCHAR BlockDescriptorLength[2];
}MODE_PARAMETER_HEADER10, *PMODE_PARAMETER_HEADER10;

#define MODE_FD_SINGLE_SIDE     0x01
#define MODE_FD_DOUBLE_SIDE     0x02
#define MODE_FD_MAXIMUM_TYPE    0x1E
#define MODE_DSP_FUA_SUPPORTED  0x10
#define MODE_DSP_WRITE_PROTECT  0x80

//
// Define the mode parameter block.
//

typedef struct _MODE_PARAMETER_BLOCK {
    UCHAR DensityCode;
    UCHAR NumberOfBlocks[3];
    UCHAR Reserved;
    UCHAR BlockLength[3];
}MODE_PARAMETER_BLOCK, *PMODE_PARAMETER_BLOCK;

//
// Define Disconnect-Reconnect page.
//

typedef struct _MODE_DISCONNECT_PAGE {
    UCHAR PageCode : 6;
    UCHAR Reserved : 1;
    UCHAR PageSavable : 1;
    UCHAR PageLength;
    UCHAR BufferFullRatio;
    UCHAR BufferEmptyRatio;
    UCHAR BusInactivityLimit[2];
    UCHAR BusDisconnectTime[2];
    UCHAR BusConnectTime[2];
    UCHAR MaximumBurstSize[2];
    UCHAR DataTransferDisconnect : 2;
    UCHAR Reserved2[3];
}MODE_DISCONNECT_PAGE, *PMODE_DISCONNECT_PAGE;

//
// Define mode caching page.
//

typedef struct _MODE_CACHING_PAGE {
    UCHAR PageCode : 6;
    UCHAR Reserved : 1;
    UCHAR PageSavable : 1;
    UCHAR PageLength;
    UCHAR ReadDisableCache : 1;
    UCHAR MultiplicationFactor : 1;
    UCHAR WriteCacheEnable : 1;
    UCHAR Reserved2 : 5;
    UCHAR WriteRetensionPriority : 4;
    UCHAR ReadRetensionPriority : 4;
    UCHAR DisablePrefetchTransfer[2];
    UCHAR MinimumPrefetch[2];
    UCHAR MaximumPrefetch[2];
    UCHAR MaximumPrefetchCeiling[2];
}MODE_CACHING_PAGE, *PMODE_CACHING_PAGE;

//
// Define mode flexible disk page.
//

typedef struct _MODE_FLEXIBLE_DISK_PAGE {
    UCHAR PageCode : 6;
    UCHAR Reserved : 1;
    UCHAR PageSavable : 1;
    UCHAR PageLength;
    UCHAR TransferRate[2];
    UCHAR NumberOfHeads;
    UCHAR SectorsPerTrack;
    UCHAR BytesPerSector[2];
    UCHAR NumberOfCylinders[2];
    UCHAR StartWritePrecom[2];
    UCHAR StartReducedCurrent[2];
    UCHAR StepRate[2];
    UCHAR StepPluseWidth;
    UCHAR HeadSettleDelay[2];
    UCHAR MotorOnDelay;
    UCHAR MotorOffDelay;
    UCHAR Reserved2 : 5;
    UCHAR MotorOnAsserted : 1;
    UCHAR StartSectorNumber : 1;
    UCHAR TrueReadySignal : 1;
    UCHAR StepPlusePerCyclynder : 4;
    UCHAR Reserved3 : 4;
    UCHAR WriteCompenstation;
    UCHAR HeadLoadDelay;
    UCHAR HeadUnloadDelay;
    UCHAR Pin2Usage : 4;
    UCHAR Pin34Usage : 4;
    UCHAR Pin1Usage : 4;
    UCHAR Pin4Usage : 4;
    UCHAR MediumRotationRate[2];
    UCHAR Reserved4[2];
}MODE_FLEXIBLE_DISK_PAGE, *PMODE_FLEXIBLE_DISK_PAGE;

//
// Define mode format page.
//

typedef struct _MODE_FORMAT_PAGE {
    UCHAR PageCode : 6;
    UCHAR Reserved : 1;
    UCHAR PageSavable : 1;
    UCHAR PageLength;
    UCHAR TracksPerZone[2];
    UCHAR AlternateSectorsPerZone[2];
    UCHAR AlternateTracksPerZone[2];
    UCHAR AlternateTracksPerLogicalUnit[2];
    UCHAR SectorsPerTrack[2];
    UCHAR BytesPerPhysicalSector[2];
    UCHAR Interleave[2];
    UCHAR TrackSkewFactor[2];
    UCHAR CylinderSkewFactor[2];
    UCHAR Reserved2 : 4;
    UCHAR SurfaceFirst : 1;
    UCHAR RemovableMedia : 1;
    UCHAR HardSectorFormating : 1;
    UCHAR SoftSectorFormating : 1;
    UCHAR Reserved3[2];
}MODE_FORMAT_PAGE, *PMODE_FORMAT_PAGE;

//
// Define rigid disk driver geometry page.
//

typedef struct _MODE_RIGID_GEOMETRY_PAGE {
    UCHAR PageCode : 6;
    UCHAR Reserved : 1;
    UCHAR PageSavable : 1;
    UCHAR PageLength;
    UCHAR NumberOfCylinders[2];
    UCHAR NumberOfHeads;
    UCHAR StartWritePrecom[2];
    UCHAR StartReducedCurrent[2];
    UCHAR DriveStepRate[2];
    UCHAR LandZoneCyclinder[2];
    UCHAR RotationalPositionLock : 2;
    UCHAR Reserved2 : 6;
    UCHAR RotationOffset;
    UCHAR Reserved3;
    UCHAR RoataionRate[2];
    UCHAR Reserved4[2];
}MODE_RIGID_GEOMETRY_PAGE, *PMODE_RIGID_GEOMETRY_PAGE;

//
// Define read write recovery page
//

typedef struct _MODE_READ_WRITE_RECOVERY_PAGE {

    UCHAR PageCode : 6;
    UCHAR Reserved1 : 1;
    UCHAR PSBit : 1;
    UCHAR PageLength;
    UCHAR DCRBit : 1;
    UCHAR DTEBit : 1;
    UCHAR PERBit : 1;
    UCHAR EERBit : 1;
    UCHAR RCBit : 1;
    UCHAR TBBit : 1;
    UCHAR ARRE : 1;
    UCHAR AWRE : 1;
    UCHAR ReadRetryCount;
    UCHAR Reserved4[4];
    UCHAR WriteRetryCount;
    UCHAR Reserved5[3];

} MODE_READ_WRITE_RECOVERY_PAGE, *PMODE_READ_WRITE_RECOVERY_PAGE;

//
// Define read recovery page - cdrom
//

typedef struct _MODE_READ_RECOVERY_PAGE {

    UCHAR PageCode : 6;
    UCHAR Reserved1 : 1;
    UCHAR PSBit : 1;
    UCHAR PageLength;
    UCHAR DCRBit : 1;
    UCHAR DTEBit : 1;
    UCHAR PERBit : 1;
    UCHAR Reserved2 : 1;
    UCHAR RCBit : 1;
    UCHAR TBBit : 1;
    UCHAR Reserved3 : 2;
    UCHAR ReadRetryCount;
    UCHAR Reserved4[4];

} MODE_READ_RECOVERY_PAGE, *PMODE_READ_RECOVERY_PAGE;

//
// Define CD-ROM Capabilities and Mechanical Status Page.
//

typedef struct _MODE_CAPABILITIES_PAGE2 {
    UCHAR PageCode : 6;
    UCHAR Reserved1 : 1;
    UCHAR PSBit : 1;
    UCHAR PageLength;
    UCHAR Reserved2[2];
    UCHAR Capabilities[4];
    UCHAR MaximumSpeedSupported[2];
    UCHAR Reserved3;
    UCHAR NumberVolumeLevels;
    UCHAR BufferSize[2];
    UCHAR CurrentSpeed[2];
    UCHAR Reserved4;
    UCHAR Reserved5 : 1;
    UCHAR DigitalOutput : 4;
    UCHAR Reserved6 : 3;
    UCHAR Reserved7[2];
} MODE_CAPABILITIES_PAGE2, *PMODE_CAPABILITIES_PAGE2;

//
// Bit definitions of Capabilites and DigitalOutput
//

#define AUDIO_PLAY_SUPPORTED    0x01
#define MODE2_FORM1_SUPPORTED   0x10
#define MODE2_FORM2_SUPPORTED   0x20
#define MULTI_SESSION_SUPPORTED 0x40

#define READ_CD_SUPPORTED       0x01

#define MEDIA_LOCKING_SUPPORTED 0x01
#define CURRENT_LOCK_STATE      0x02
#define SOFTWARE_EJECT_SUPPORT  0x08

#define DISC_PRESENT_REPORTING 0x04

//
// Mode parameter list block descriptor -
// set the block length for reading/writing
//
//

#define MODE_BLOCK_DESC_LENGTH               8
#define MODE_HEADER_LENGTH                   4
#define MODE_HEADER_LENGTH10                 8

typedef struct _MODE_PARM_READ_WRITE {

   MODE_PARAMETER_HEADER  ParameterListHeader;  // List Header Format
   MODE_PARAMETER_BLOCK   ParameterListBlock;   // List Block Descriptor

} MODE_PARM_READ_WRITE_DATA, *PMODE_PARM_READ_WRITE_DATA;


//
// Tape definitions
//

typedef struct _TAPE_POSITION_DATA {
    UCHAR Reserved1:2;
    UCHAR BlockPositionUnsupported:1;
    UCHAR Reserved2:3;
    UCHAR EndOfPartition:1;
    UCHAR BeginningOfPartition:1;
    UCHAR PartitionNumber;
    USHORT Reserved3;
    UCHAR FirstBlock[4];
    UCHAR LastBlock[4];
    UCHAR Reserved4;
    UCHAR NumberOfBlocks[3];
    UCHAR NumberOfBytes[4];
} TAPE_POSITION_DATA, *PTAPE_POSITION_DATA;

//
// This structure is used to convert little endian
// ULONGs to SCSI CDB 4 byte big endians values.
//

typedef struct _FOUR_BYTE {
    UCHAR Byte0;
    UCHAR Byte1;
    UCHAR Byte2;
    UCHAR Byte3;
} FOUR_BYTE, *PFOUR_BYTE;

//
// Byte reversing macro for converting
// between big- and little-endian formats
//

#define REVERSE_BYTES(Destination, Source) {                \
    PFOUR_BYTE d = (PFOUR_BYTE)(Destination);               \
    PFOUR_BYTE s = (PFOUR_BYTE)(Source);                    \
    d->Byte3 = s->Byte0;                                    \
    d->Byte2 = s->Byte1;                                    \
    d->Byte1 = s->Byte2;                                    \
    d->Byte0 = s->Byte3;                                    \
}

//
// This macro has the effect of Bit = log2(Data)
//

#define WHICH_BIT(Data, Bit) {                      \
    for (Bit = 0; Bit < 32; Bit++) {                \
        if ((Data >> Bit) == 1) {                   \
            break;                                  \
        }                                           \
    }                                               \
}


#if DBG

#define DebugPrint(x) ScsiDebugPrint x

#else

#define DebugPrint(x)

#endif // DBG


//
// Define Device Configuration Page
//

typedef struct _MODE_DEVICE_CONFIGURATION_PAGE {

    UCHAR PageCode : 6;
    UCHAR Reserved1 : 1;
    UCHAR PS : 1;
    UCHAR PageLength;
    UCHAR ActiveFormat : 5;
    UCHAR CAFBit : 1;
    UCHAR CAPBit : 1;
    UCHAR Reserved2 : 1;
    UCHAR ActivePartition;
    UCHAR WriteBufferFullRatio;
    UCHAR ReadBufferEmptyRatio;
    UCHAR WriteDelayTime[2];
    UCHAR REW : 1;
    UCHAR RBO : 1;
    UCHAR SOCF : 2;
    UCHAR AVC : 1;
    UCHAR RSmk : 1;
    UCHAR BIS : 1;
    UCHAR DBR : 1;
    UCHAR GapSize;
    UCHAR Reserved3 : 3;
    UCHAR SEW : 1;
    UCHAR EEG : 1;
    UCHAR EODdefined : 3;
    UCHAR BufferSize[3];
    UCHAR DCAlgorithm;
    UCHAR Reserved4;

} MODE_DEVICE_CONFIGURATION_PAGE, *PMODE_DEVICE_CONFIGURATION_PAGE;

//
// Define Medium Partition Page
//

typedef struct _MODE_MEDIUM_PARTITION_PAGE {

    UCHAR PageCode : 6;
    UCHAR Reserved1 : 1;
    UCHAR PSBit : 1;
    UCHAR PageLength;
    UCHAR MaximumAdditionalPartitions;
    UCHAR AdditionalPartitionDefined;
    UCHAR Reserved2 : 3;
    UCHAR PSUMBit : 2;
    UCHAR IDPBit : 1;
    UCHAR SDPBit : 1;
    UCHAR FDPBit : 1;
    UCHAR MediumFormatRecognition;
    UCHAR Reserved3[2];
    UCHAR Partition0Size[2];
    UCHAR Partition1Size[2];

} MODE_MEDIUM_PARTITION_PAGE, *PMODE_MEDIUM_PARTITION_PAGE;

//
// Define Data Compression Page
//

typedef struct _MODE_DATA_COMPRESSION_PAGE {

    UCHAR PageCode : 6;
    UCHAR Reserved1 : 2;
    UCHAR PageLength;
    UCHAR Reserved2 : 6;
    UCHAR DCC : 1;
    UCHAR DCE : 1;
    UCHAR Reserved3 : 5;
    UCHAR RED : 2;
    UCHAR DDE : 1;
    UCHAR CompressionAlgorithm[4];
    UCHAR DecompressionAlgorithm[4];
    UCHAR Reserved4[4];

} MODE_DATA_COMPRESSION_PAGE, *PMODE_DATA_COMPRESSION_PAGE;

//
// Define capabilites and mechanical status page.
//

typedef struct _MODE_CAPABILITIES_PAGE {

    UCHAR PageCode : 6;
    UCHAR Reserved1 : 2;
    UCHAR PageLength;
    UCHAR Reserved2[2];
    UCHAR RO : 1;
    UCHAR Reserved3 : 4;
    UCHAR SPREV : 1;
    UCHAR Reserved4 : 2;
    UCHAR Reserved5 : 3;
    UCHAR EFMT : 1;
    UCHAR Reserved6 : 1;
    UCHAR QFA : 1;
    UCHAR Reserved7 : 2;
    UCHAR LOCK : 1;
    UCHAR LOCKED : 1;
    UCHAR PREVENT : 1;
    UCHAR UNLOAD : 1;
    UCHAR Reserved8 : 2;
    UCHAR ECC : 1;
    UCHAR CMPRS : 1;
    UCHAR Reserved9 : 1;
    UCHAR BLK512 : 1;
    UCHAR BLK1024 : 1;
    UCHAR Reserved10 : 4;
    UCHAR SLOWB : 1;
    UCHAR MaximumSpeedSupported[2];
    UCHAR MaximumStoredDefectedListEntries[2];
    UCHAR ContinuousTransferLimit[2];
    UCHAR CurrentSpeedSelected[2];
    UCHAR BufferSize[2];
    UCHAR Reserved11[2];

} MODE_CAPABILITIES_PAGE, *PMODE_CAPABILITIES_PAGE;

typedef struct _MODE_CAP_PAGE {

    MODE_PARAMETER_HEADER   ParameterListHeader;
    MODE_PARAMETER_BLOCK    ParameterListBlock;
    MODE_CAPABILITIES_PAGE  CapabilitiesPage;

} MODE_CAP_PAGE, *PMODE_CAP_PAGE;



//
// Mode parameter list header and medium partition page -
// used in creating partitions
//

typedef struct _MODE_MEDIUM_PART_PAGE {

   MODE_PARAMETER_HEADER       ParameterListHeader;
   MODE_MEDIUM_PARTITION_PAGE  MediumPartPage;

} MODE_MEDIUM_PART_PAGE, *PMODE_MEDIUM_PART_PAGE;

typedef struct _MODE_MEDIUM_PART_PAGE_PLUS {

    MODE_PARAMETER_HEADER       ParameterListHeader;
    MODE_PARAMETER_BLOCK        ParameterListBlock;
    MODE_MEDIUM_PARTITION_PAGE  MediumPartPage;

} MODE_MEDIUM_PART_PAGE_PLUS, *PMODE_MEDIUM_PART_PAGE_PLUS;



//
// Mode parameters for retrieving tape or media information
//

typedef struct _MODE_TAPE_MEDIA_INFORMATION {

   MODE_PARAMETER_HEADER       ParameterListHeader;
   MODE_PARAMETER_BLOCK        ParameterListBlock;
   MODE_MEDIUM_PARTITION_PAGE  MediumPartPage;

} MODE_TAPE_MEDIA_INFORMATION, *PMODE_TAPE_MEDIA_INFORMATION;

//
// Mode parameter list header and device configuration page -
// used in retrieving device configuration information
//

typedef struct _MODE_DEVICE_CONFIG_PAGE {

   MODE_PARAMETER_HEADER       ParameterListHeader;
   MODE_DEVICE_CONFIGURATION_PAGE  DeviceConfigPage;

} MODE_DEVICE_CONFIG_PAGE, *PMODE_DEVICE_CONFIG_PAGE;

typedef struct _MODE_DEVICE_CONFIG_PAGE_PLUS {

   MODE_PARAMETER_HEADER       ParameterListHeader;
   MODE_PARAMETER_BLOCK        ParameterListBlock;
   MODE_DEVICE_CONFIGURATION_PAGE  DeviceConfigPage;

} MODE_DEVICE_CONFIG_PAGE_PLUS, *PMODE_DEVICE_CONFIG_PAGE_PLUS ;

//
// Mode parameter list header and data compression page -
// used in retrieving data compression information
//

typedef struct _MODE_DATA_COMPRESS_PAGE {

   MODE_PARAMETER_HEADER       ParameterListHeader;
   MODE_DATA_COMPRESSION_PAGE  DataCompressPage;

} MODE_DATA_COMPRESS_PAGE, *PMODE_DATA_COMPRESS_PAGE;

typedef struct _MODE_DATA_COMPRESS_PAGE_PLUS {

   MODE_PARAMETER_HEADER       ParameterListHeader;
   MODE_PARAMETER_BLOCK        ParameterListBlock;
   MODE_DATA_COMPRESSION_PAGE  DataCompressPage;

} MODE_DATA_COMPRESS_PAGE_PLUS, *PMODE_DATA_COMPRESS_PAGE_PLUS;


//
// Tape/Minitape definition.
//

typedef
BOOLEAN
(*TAPE_VERIFY_INQUIRY_ROUTINE)(
    IN  PINQUIRYDATA            InquiryData,
    IN  PMODE_CAPABILITIES_PAGE ModeCapabilitiesPage
    );

typedef
VOID
(*TAPE_EXTENSION_INIT_ROUTINE)(
    IN  PVOID                   MinitapeExtension,
    IN  PINQUIRYDATA            InquiryData,
    IN  PMODE_CAPABILITIES_PAGE ModeCapabilitiesPage
    );

typedef enum _TAPE_STATUS {
    TAPE_STATUS_SEND_SRB_AND_CALLBACK,
    TAPE_STATUS_CALLBACK,
    TAPE_STATUS_CHECK_TEST_UNIT_READY,

    TAPE_STATUS_SUCCESS,
    TAPE_STATUS_INSUFFICIENT_RESOURCES,
    TAPE_STATUS_NOT_IMPLEMENTED,
    TAPE_STATUS_INVALID_DEVICE_REQUEST,
    TAPE_STATUS_INVALID_PARAMETER,

    TAPE_STATUS_MEDIA_CHANGED,
    TAPE_STATUS_BUS_RESET,
    TAPE_STATUS_SETMARK_DETECTED,
    TAPE_STATUS_FILEMARK_DETECTED,
    TAPE_STATUS_BEGINNING_OF_MEDIA,
    TAPE_STATUS_END_OF_MEDIA,
    TAPE_STATUS_BUFFER_OVERFLOW,
    TAPE_STATUS_NO_DATA_DETECTED,
    TAPE_STATUS_EOM_OVERFLOW,
    TAPE_STATUS_NO_MEDIA,
    TAPE_STATUS_IO_DEVICE_ERROR,
    TAPE_STATUS_UNRECOGNIZED_MEDIA,

    TAPE_STATUS_DEVICE_NOT_READY,
    TAPE_STATUS_MEDIA_WRITE_PROTECTED,
    TAPE_STATUS_DEVICE_DATA_ERROR,
    TAPE_STATUS_NO_SUCH_DEVICE,
    TAPE_STATUS_INVALID_BLOCK_LENGTH,
    TAPE_STATUS_IO_TIMEOUT,
    TAPE_STATUS_DEVICE_NOT_CONNECTED,
    TAPE_STATUS_DATA_OVERRUN,
    TAPE_STATUS_DEVICE_BUSY

} TAPE_STATUS, *PTAPE_STATUS;

typedef
VOID
(*TAPE_ERROR_ROUTINE)(
    IN      PVOID               MinitapeExtension,
    IN      PSCSI_REQUEST_BLOCK Srb,
    IN OUT  PTAPE_STATUS        TapeStatus
    );

#define TAPE_RETRY_MASK 0x0000FFFF
#define IGNORE_ERRORS   0x00010000
#define RETURN_ERRORS   0x00020000

typedef
TAPE_STATUS
(*TAPE_PROCESS_COMMAND_ROUTINE)(
    IN OUT  PVOID               MinitapeExtension,
    IN OUT  PVOID               CommandExtension,
    IN OUT  PVOID               CommandParameters,
    IN OUT  PSCSI_REQUEST_BLOCK Srb,
    IN      ULONG               CallNumber,
    IN      TAPE_STATUS         StatusOfLastCommand,
    IN OUT  PULONG              RetryFlags
    );

typedef struct _TAPE_INIT_DATA {
    TAPE_VERIFY_INQUIRY_ROUTINE     VerifyInquiry;
    BOOLEAN                         QueryModeCapabilitiesPage ;
    ULONG                           MinitapeExtensionSize;
    TAPE_EXTENSION_INIT_ROUTINE     ExtensionInit;          /* OPTIONAL */
    ULONG                           DefaultTimeOutValue;    /* OPTIONAL */
    TAPE_ERROR_ROUTINE              TapeError;              /* OPTIONAL */
    ULONG                           CommandExtensionSize;
    TAPE_PROCESS_COMMAND_ROUTINE    CreatePartition;
    TAPE_PROCESS_COMMAND_ROUTINE    Erase;
    TAPE_PROCESS_COMMAND_ROUTINE    GetDriveParameters;
    TAPE_PROCESS_COMMAND_ROUTINE    GetMediaParameters;
    TAPE_PROCESS_COMMAND_ROUTINE    GetPosition;
    TAPE_PROCESS_COMMAND_ROUTINE    GetStatus;
    TAPE_PROCESS_COMMAND_ROUTINE    Prepare;
    TAPE_PROCESS_COMMAND_ROUTINE    SetDriveParameters;
    TAPE_PROCESS_COMMAND_ROUTINE    SetMediaParameters;
    TAPE_PROCESS_COMMAND_ROUTINE    SetPosition;
    TAPE_PROCESS_COMMAND_ROUTINE    WriteMarks;
    TAPE_PROCESS_COMMAND_ROUTINE    PreProcessReadWrite;
} TAPE_INIT_DATA, *PTAPE_INIT_DATA;


SCSIPORT_API
ULONG
TapeClassInitialize(
    IN  PVOID           Argument1,
    IN  PVOID           Argument2,
    IN  PTAPE_INIT_DATA TapeInitData
    );

SCSIPORT_API
BOOLEAN
TapeClassAllocateSrbBuffer(
    IN OUT  PSCSI_REQUEST_BLOCK Srb,
    IN      ULONG               SrbBufferSize
    );

SCSIPORT_API
VOID
TapeClassZeroMemory(
    IN OUT  PVOID   Buffer,
    IN      ULONG   BufferSize
    );

SCSIPORT_API
ULONG
TapeClassCompareMemory(
    IN OUT  PVOID   Source1,
    IN OUT  PVOID   Source2,
    IN      ULONG   Length
    );


//
// defines for QIC tape density codes
//

#define QIC_XX     0   // ????
#define QIC_24     5   // 0x05
#define QIC_120    15  // 0x0F
#define QIC_150    16  // 0x10
#define QIC_525    17  // 0x11
#define QIC_1350   18  // 0x12
#define QIC_1000   21  // 0x15
#define QIC_1000C  30  // 0x1E
#define QIC_2100   31  // 0x1F
#define QIC_2GB    34  // 0x22
#define QIC_5GB    40  // 0x28

//
// defines for QIC tape media codes
//

#define DCXXXX   0
#define DC300    1
#define DC300XLP 2
#define DC615    3
#define DC600    4
#define DC6037   5
#define DC6150   6
#define DC6250   7
#define DC6320   8
#define DC6525   9
#define DC9135SL 33  //0x21
#define DC9210   34  //0x22
#define DC9135   35  //0x23
#define DC9100   36  //0x24
#define DC9120   37  //0x25
#define DC9120SL 38  //0x26
#define DC9164   39  //0x27
#define DCXXXXFW 48  //0x30
#define DC9200SL 49  //0x31
#define DC9210XL 50  //0x32
#define DC10GB   51  //0x33
#define DC9200   52  //0x34
#define DC9120XL 53  //0x35
#define DC9210SL 54  //0x36
#define DC9164XL 55  //0x37
#define DC9200XL 64  //0x40
#define DC9400   65  //0x41
#define DC9500   66  //0x42
#define DC9500SL 70  //0x46

//
// defines for translation reference point
//

#define NOT_FROM_BOT 0
#define FROM_BOT 1

//
// info/structure returned by/from
// TapeLogicalBlockToPhysicalBlock( )
//

typedef struct _TAPE_PHYS_POSITION {
    ULONG SeekBlockAddress;
    ULONG SpaceBlockCount;
} TAPE_PHYS_POSITION, PTAPE_PHYS_POSITION;

//
// function prototypes
//

TAPE_PHYS_POSITION
TapeClassLogicalBlockToPhysicalBlock(
    IN UCHAR DensityCode,
    IN ULONG LogicalBlockAddress,
    IN ULONG BlockLength,
    IN BOOLEAN FromBOT
    );

ULONG
TapeClassPhysicalBlockToLogicalBlock(
    IN UCHAR DensityCode,
    IN ULONG PhysicalBlockAddress,
    IN ULONG BlockLength,
    IN BOOLEAN FromBOT
    );


#endif /* _MINITAPE_ */
