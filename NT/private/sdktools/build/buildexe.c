//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1994
//
//  File:       buildexe.c
//
//  Contents:   Functions related to spawning processes and processing
//              their output, using pipes and multiple threads.
//
//  History:    22-May-89     SteveWo  Created
//                 ... see SLM logs
//              26-Jul-94     LyleC    Cleanup/Add Pass0 Support
//              05-Dec-00     sbonev   See SD changelist 2317
//
//----------------------------------------------------------------------------

#include "build.h"

#include <fcntl.h>

//+---------------------------------------------------------------------------
//
// Global Data
//
//----------------------------------------------------------------------------

#define DEFAULT_LPS     (fStatusTree? 5000 : 50)

#define LastRow(pts)    ((USHORT) ((pts)->cRowTotal - 1))
#define LastCol(pts)    ((USHORT) ((pts)->cColTotal - 1))

typedef struct _PARALLEL_CHILD {
    PTHREADSTATE ThreadState;
    HANDLE       Event;
    CHAR         ExecuteProgramCmdLine[1024];
} PARALLEL_CHILD, *PPARALLEL_CHILD;

ULONG StartCompileTime;

DWORD OldConsoleMode;
DWORD NewConsoleMode;

HANDLE *WorkerThreads;
HANDLE *WorkerEvents;
ULONG NumberProcesses;
ULONG ThreadsStarted;

BOOLEAN fConsoleInitialized = FALSE;
BYTE ScreenCell[2];
BYTE StatusCell[2];

#define STATE_UNKNOWN       0
#define STATE_COMPILING     1
#define STATE_ASSEMBLING    2
#define STATE_LIBING        3
#define STATE_LINKING       4
#define STATE_C_PREPROC     5
#define STATE_S_PREPROC     6
#define STATE_PRECOMP       7
#define STATE_MKTYPLIB      8
#define STATE_MIDL          9
#define STATE_MC            10
#define STATE_STATUS        11
#define STATE_BINPLACE      12
#define STATE_VSTOOL        13
#define STATE_ASN           14
#define STATE_BATCHCOMPILE  15
#define STATE_BSCMAKING     16
#define STATE_CTCOMPILING   17
#define STATE_AUTODOCING    18
#define STATE_DOCCHECKING   19

#define FLAGS_CXX_FILE              0x0001
#define FLAGS_WARNINGS_ARE_ERRORS   0x0002

LPSTR States[] = {
    "Unknown",                      // 0
    "Compiling",                    // 1
    "Assembling",                   // 2
    "Building Library",             // 3
    "Linking Executable",           // 4
    "Preprocessing",                // 5
    "Assembling",                   // 6
    "Precompiling",                 // 7
    "Building Type Library",        // 8
    "MIDL Compiling",               // 9
    "Compiling error file",         // 10
    "Build Status Line",            // 11
    "Binplacing",                   // 12
    "Processing",                   // 13
    "Running ASN Compiler on",      // 14
    "Compiling",                    // 15
    "Building Browse File",         // 16
    "CTC Compiling",                // 17
    "Generating Documentation",     // 18
    "Checking Doc Comments",        // 19
};

//----------------------------------------------------------------------------
//
// Function prototypes
//
//----------------------------------------------------------------------------

VOID
GetScreenSize(THREADSTATE *ThreadState);

VOID
GetCursorPosition(USHORT *pRow, USHORT *pCol, USHORT *pRowTop);

VOID
SetCursorPosition(USHORT Row, USHORT Col);

VOID
WriteConsoleCells(
    LPSTR String,
    USHORT StringLength,
    USHORT Row,
    USHORT Col,
    BYTE *Attribute);

VOID
MoveRectangleUp (
    USHORT Top,
    USHORT Left,
    USHORT Bottom,
    USHORT Right,
    USHORT NumRow,
    BYTE  *FillCell);

VOID
ReadConsoleCells(
    BYTE *pScreenCell,
    USHORT cb,
    USHORT Row,
    USHORT Column);

VOID
ClearRows(
    PTHREADSTATE ThreadState,
    USHORT Top,
    USHORT NumRows,
    PBYTE  Cell
    );

LPSTR
IsolateFirstToken(
    LPSTR *pp,
    CHAR delim
    );

LPSTR
IsolateLastToken(
    LPSTR p,
    CHAR delim
    );

DWORD
ParallelChildStart(
    PPARALLEL_CHILD Data
    );

DWORD
PipeSpawnClose (
    FILE *pstream
    );

FILE *
PipeSpawn (
    const CHAR *cmdstring
    );


VOID
FormatMsErrorMessage(
    PTHREADSTATE ThreadState,
    LPSTR FileName,
    LPSTR LineNumber,
    LPSTR Message,
    BOOL Warning
    );

//+---------------------------------------------------------------------------
//
//  Function:   RestoreConsoleMode
//
//----------------------------------------------------------------------------

VOID
RestoreConsoleMode(VOID)
{
    SetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), OldConsoleMode);
    NewConsoleMode = OldConsoleMode;
}

//+---------------------------------------------------------------------------
//
//  Function:   IsolateFirstToken
//
//  Synopsis:   Returns the first token in a string.
//
//  Arguments:  [pp]    -- String to parse
//              [delim] -- Token delimiter
//
//  Returns:    Pointer to first token
//
//  Notes:      Leading spaces are ignored.
//
//----------------------------------------------------------------------------

LPSTR
IsolateFirstToken(
    LPSTR *pp,
    CHAR delim
    )
{
    LPSTR p, Result;

    p = *pp;
    while (*p <= ' ') {
        if (!*p) {
            *pp = p;
            return( "" );
            }
        else
            p++;
        }

    Result = p;
    while (*p) {
        if (*p == delim) {
            *p++ = '\0';
            break;
            }
        else {
            p++;
            }
        }
    *pp = p;
    if (*Result == '\0')    // don't overrun the buffer
        return( Result );

    if (*Result == '.' && Result[1] == '\\') {
        return( Result+2 );
        }
    else {
        return( Result );
        }
}


//+---------------------------------------------------------------------------
//
//  Function:   IsolateLastToken
//
//  Synopsis:   Return the last token in a string.
//
//  Arguments:  [p]     -- String to parse
//              [delim] -- Token delimiter
//
//  Returns:    Pointer to last token
//
//  Notes:      Trailing spaces are skipped.
//
//----------------------------------------------------------------------------

LPSTR
IsolateLastToken(
    LPSTR p,
    CHAR delim
    )
{
    LPSTR Start;

    Start = p;
    while (*p) {
        p++;
        }

    while (--p > Start) {
        if (*p <= ' ' || *p == ':') {
            *p = '\0';
            }
        else
            break;
        }

    while (p > Start) {
        if (*--p == delim) {
            p++;
            break;
            }
        }

    if (*p == '.' && p[1] == '\\') {
        return( p+2 );
        }
    else {
        return( p );
        }
}


//+---------------------------------------------------------------------------
//
//  Function:   TestPrefix
//
//  Synopsis:   Returns TRUE if [Prefix] is the first part of [pp]
//
//----------------------------------------------------------------------------

BOOL
TestPrefix(
    LPSTR  *pp,
    LPSTR Prefix
    )
{
    LPSTR p = *pp;
    UINT cb;

    if (!_strnicmp( p, Prefix, cb = strlen( Prefix ) )) {
        *pp = p + cb;
        return( TRUE );
        }
    else {
        return( FALSE );
        }
}


//+---------------------------------------------------------------------------
//
//  Function:   TestCommandPrefix
//
//  Synopsis:   Returns TRUE if [Prefix] is in the first element of [pp]
//
//----------------------------------------------------------------------------

BOOL
TestCommandPrefix(
    LPSTR  *pp,
    LPSTR Prefix
    )
{
    BOOL fRet = FALSE;
    LPSTR p = *pp, p1, p2;
    LPSTR pDup = _strupr(_strdup(p));
    LPSTR PrefixDup = _strupr(_strdup(Prefix));

    if ((p1 = strstr(pDup, PrefixDup)) < (p2 = strstr( pDup, " ")) &&
        ((p1 == pDup) || ((p1 > pDup) && (*(p1-1) == '\\')))) {
        *pp = p + (p1 - pDup) + strlen(Prefix);
        fRet = TRUE;
        }
    else {
        fRet = FALSE;
        }

    free(pDup);
    free(PrefixDup);
    return fRet;
}


//+---------------------------------------------------------------------------
//
//  Function:   Substr
//
//----------------------------------------------------------------------------

BOOL
Substr(
    LPSTR s,
    LPSTR p
    )
{
    LPSTR x;

    while (*p) {
        x = s;
        while (*p++ == *x) {
            if (*x == '\0') {
                return( TRUE );
                }
            x++;
            }
        if (*x == '\0') {
            return( TRUE );
            }
        }
    return( FALSE );
}



//+---------------------------------------------------------------------------
//
//  Function:   WriteTTY
//
//  Synopsis:   Writes the given string to the output device.
//
//  Arguments:  [ThreadState]   -- Struct containing info about the output dev.
//              [p]             -- String to display
//              [fStatusOutput] -- If TRUE then put on the status line.
//
//----------------------------------------------------------------------------

VOID
WriteTTY (THREADSTATE *ThreadState, LPSTR p, BOOL fStatusOutput)
{
    USHORT SaveRow;
    USHORT SaveCol;
    USHORT SaveRowTop;
    USHORT cb, cbT;
    PBYTE Attribute;
    BOOL ForceNewline;

    //
    // If we're not writing to the screen then don't do anything fancy, just
    // output the string.
    //
    if (!fStatus || !ThreadState->IsStdErrTty) {
        while (TRUE) {
            int cch;

            cch = strcspn(p, "\r");
            if (cch != 0) {
                fwrite(p, 1, cch, stderr);
                p += cch;
            }
            if (*p == '\0') {
                break;
            }
            if (p[1] != '\n') {
                fwrite(p, 1, 1, stderr);
            }
            p++;
        }
        fflush(stderr);
        return;
    }
    assert(ThreadState->cColTotal != 0);
    assert(ThreadState->cRowTotal != 0);

    //
    // Scroll as necessary
    //
    GetCursorPosition(&SaveRow, &SaveCol, &SaveRowTop);

    //  During processing, there might be N threads that are displaying
    //  messages and a single thread displaying directory-level
    //  linking and building messages.  We need to make sure there's room for
    //  the single thread's message as well as ours.  Since that single
    //  thread displays one line at a time (including CRLF) we must make sure
    //  that his display (as well as ours) doesn't inadvertantly scroll
    //  the status line at the top.  We do this by guaranteeing that there is
    //  a blank line at the end.


    //  We are synchronized with the single top-level thread
    //  at a higher level than this routine via TTYCriticalSection.  We
    //  are, thus, assured that we control the cursor completely.


    //  Stay off the LastRow
    if (SaveRow == LastRow(ThreadState)) {
        USHORT RowTop = 2;

        if (fStatus) {
            RowTop += SaveRowTop + (USHORT) NumberProcesses + 1;
        }

        MoveRectangleUp (
            RowTop,                     // Top
            0,                          // Left
            LastRow(ThreadState),       // Bottom
            LastCol(ThreadState),       // Right
            2,                          // NumRow
            ScreenCell);                // FillCell

        SaveRow -= 2;
        SetCursorPosition(SaveRow, SaveCol);
    }

    //
    // Different color for the status line.
    //
    if (fStatusOutput) {
        Attribute = &StatusCell[1];
    }
    else {
        Attribute = &ScreenCell[1];
    }
    cb = (USHORT) strlen(p);

    //
    // Write out the string.
    //
    while (cb > 0) {
        ForceNewline = FALSE;

        if (cb > 1) {
            if (p[cb - 1] == '\n' && p[cb - 2] == '\r') {
                cb -= 2;
                ForceNewline = TRUE;
            }
        }

        if (cb >= ThreadState->cColTotal - SaveCol) {
            cbT = ThreadState->cColTotal - SaveCol;
            if (fFullErrors)
                ForceNewline = TRUE;
        }
        else {
            cbT = cb;
        }

        WriteConsoleCells(p, cbT, SaveRow, SaveCol, Attribute);
        SetCursorPosition(SaveRow, SaveCol);

        if (ForceNewline) {
            SaveCol = 0;
            SaveRow++;
        }
        else {
            SaveCol += cbT;
        }

        if (!fFullErrors) {
            break;
        }

        if (cb > cbT) {
            // we have more to go... do a newline

            //  If we're back at the beginning of the bottom line
            if (SaveRow == LastRow(ThreadState)) {
                USHORT RowTop = 1;

                if (fStatus) {
                    RowTop += SaveRowTop + (USHORT) NumberProcesses + 1;
                }

                // move window up one line (leaving two lines blank at bottom)
                MoveRectangleUp (
                    RowTop,                     // Top
                    0,                          // Left
                    LastRow(ThreadState),       // Bottom
                    LastCol(ThreadState),       // Right
                    1,                          // NumRow
                    ScreenCell);                // FillCell

                SaveRow--;
            }
            SetCursorPosition(SaveRow, SaveCol);
        }

        cb -= cbT;
        p += cbT;
    }

    SetCursorPosition(SaveRow, SaveCol);
}


//+---------------------------------------------------------------------------
//
//  Function:   WriteTTYLoggingErrors
//
//  Synopsis:   Writes a message to the appropriate log file and also the
//              screen if specified.
//
//  Arguments:  [Warning]     -- TRUE if the message is a warning
//              [ThreadState] -- Info about output device
//              [p]           -- String
//
//----------------------------------------------------------------------------

VOID
WriteTTYLoggingErrors(
    BOOL Warning,
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    UINT cb;
    cb = strlen( p );

    // ignore empty strings
    if (0 == cb)
        return;

    if (fErrorLog) {
        fwrite( p, 1, cb, Warning ? WrnFile : ErrFile );
    }
    if (fShowWarningsOnScreen && Warning)
    {
        WriteTTY(ThreadState, p, FALSE);
        return;
    }
    if (!fErrorLog || !Warning) {
        WriteTTY(ThreadState, p, FALSE);
    }

    if (!Warning && fErrorBaseline && !bBaselineFailure) {
        // don't check for a new failure if there is already one

        if (NULL == pvBaselineContent || NULL == memfind(pvBaselineContent, cbBaselineContentSize, p, cb)) {
            // if there is no baseline file, or if the error is not found, we have new failure
            bBaselineFailure = TRUE;
        } 
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   RuntimeErrorFilter
//
//  Synopsis:   Filters output from the compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//                               (compiling, linking, etc...)
//              [p]           -- Message we're trying to parse.
//              [FileName]    -- [out] Filename in message
//              [LineNumber]  -- [out] Line number in message
//              [Message]     -- [out] Message number (for post processing)
//              [Warning]     -- [out] TRUE if message is a warning.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    26-Jul-94     sbonev    Created
//
//  Notes:
//
//      This routine filters strings that are not standard tool output.
//      Any unexpected error checking should go here
//
//----------------------------------------------------------------------------

BOOL
RuntimeErrorFilter(
    PTHREADSTATE ThreadState,
    LPSTR p,
    LPSTR *FileName,
    LPSTR *LineNumber,
    LPSTR *Message,
    BOOL *Warning
    )
{
    if (strstr(p, "Exception occured:"))
    {
        *FileName = NULL;
        *LineNumber = NULL;
        *Message = p;
        *Warning = FALSE;

        return TRUE;
    }

    return FALSE;
}

//+---------------------------------------------------------------------------
//
//  Function:   MsCompilerFilter
//
//  Synopsis:   Filters output from the compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//                               (compiling, linking, etc...)
//              [p]           -- Message we're trying to parse.
//              [FileName]    -- [out] Filename in message
//              [LineNumber]  -- [out] Line number in message
//              [Message]     -- [out] Message number (for post processing)
//              [Warning]     -- [out] TRUE if message is a warning.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    26-Jul-94     LyleC    Created
//
//  Notes:
//
//    This routine filters strings in the MS compiler format.  That is:
//
//       {toolname} : {number}: {text}
//
//    where:
//
//        toolname    If possible, the container and specific module that has
//                    the error.  For instance, the compiler uses
//                    filename(linenum), the linker uses library(objname), etc.
//                    If unable to provide a container, use the tool name.
//        number      A number, prefixed with some tool identifier (C for
//                    compiler, LNK for linker, LIB for librarian, N for nmake,
//                    etc).
//        test        The descriptive text of the message/error.
//
//        Accepted String formats are:
//
//        container(module): error/warning NUM ...
//        container(module) : error/warning NUM ...
//        container (module): error/warning NUM ...
//        container (module) : error/warning NUM ...
//
//----------------------------------------------------------------------------

BOOL
MsCompilerFilter(
    PTHREADSTATE ThreadState,
    LPSTR p,
    LPSTR *FileName,
    LPSTR *LineNumber,
    LPSTR *Message,
    BOOL *Warning
    )
{
    LPSTR p1;

    *Message = NULL;

    p1 = p;

    if (strstr(p, "see declaration of"))
        goto notRecognized;

    if (strstr(p, "see previous definition of"))
        goto notRecognized;

    if (strstr(p, "while compiling class-template member function"))
        goto notRecognized;

    if (strstr(p, "see reference to function template instantiation"))
        goto notRecognized;

    if (!strncmp(p, "Compiler error (", 16)) {
        *Message = p;
        *Warning = FALSE;
        if ((p1 = strstr( p, "source=" )))
            *LineNumber = p1+7;
        else
            *LineNumber = "1";
        *FileName = ThreadState->ChildCurrentFile;
        return TRUE;
    }

    // First look for the " : " or "): " sequence.

    while (*p1) {
        if ((p1[0] == ')') && (p1[1] == ' ')) p1++;

        if ((p1[0] == ' ') || (p1[0] == ')')) {
            if (p1[1] == ':') {
                if (p1[2] == ' ') {
                    *Message = p1 + 3;
                    *p1 = '\0';

                    break;
                }
                else
                    break;   // No sense going any further
            }
            else if ((p1[0] == ' ') && (p1[1] == '('))
                p1++;
            else
                break;   // No sense going any further
        }
        else
            p1++;
    }

    if (*Message != NULL) {
        // then figure out if this is an error or warning.

        *Warning = TRUE;        // Assume the best.

        if (TestPrefix( Message, "error " ) ||
            TestPrefix( Message, "fatal error " ) ||
            TestPrefix( Message, "Compiler error " )) 
            *Warning = FALSE;
        else
        if (TestPrefix( Message, "warning " )) { // This will advance Message
                                                 // past the warning message.           
            *Warning = TRUE;
        }

        if ((ThreadState->ChildFlags & FLAGS_WARNINGS_ARE_ERRORS) != 0) {
            if (Substr( "X0000", *Message )) {
                *Warning = TRUE;   // Special case this one. Never an error
            } else {
                *Warning = FALSE;       // Warnings treated as errors for this compile

            }
        }

        // Set the container name and look for the module paren's

        *FileName = p;
        *LineNumber = NULL;

        p1 = p;

        while (*p1) {
            if (*p1 == '(' && p1[1] != ')') {
                *p1 = '\0';
                p1++;
                *LineNumber = p1;
                while (*p1) {
                    if (*p1 == ')') {
                        *p1 = '\0';
                        break;
                    }
                    p1++;
                }

                break;
            }

            p1++;
        }

        return(TRUE);
    }

notRecognized:
    return RuntimeErrorFilter(ThreadState, p, FileName, LineNumber, Message, Warning);

}

//+---------------------------------------------------------------------------
//
//  Function:   PassThrough
//
//  Synopsis:   Keep track of and print the given message without any
//              filtering.
//
//  Arguments:  [ThreadState] --
//              [p]           -- Message
//              [Warning]     -- TRUE if warning
//
//  Returns:    FALSE
//
//----------------------------------------------------------------------------

BOOL
PassThrough(
    PTHREADSTATE ThreadState,
    LPSTR p,
    BOOL Warning
    )
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
    if (fColorConsole) {
        if (Warning)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    }

    if (ThreadState->ChildState == STATE_VSTOOL) {
        if (Warning) {
            RunningTotals.NumberVSToolWarnings++;
            ThreadState->BuildMetrics.NumberVSToolWarnings++;
            }
        else {
            RunningTotals.NumberVSToolErrors++;
            ThreadState->BuildMetrics.NumberVSToolErrors++;
            }
        }
    else
    if (ThreadState->ChildState == STATE_LIBING) {
        if (Warning) {
            RunningTotals.NumberLibraryWarnings++;
            ThreadState->BuildMetrics.NumberLibraryWarnings++;
            }
        else {
            RunningTotals.NumberLibraryErrors++;
            ThreadState->BuildMetrics.NumberLibraryErrors++;
            }
        }
    else
    if ((ThreadState->ChildState == STATE_LINKING) ||
        (ThreadState->ChildState == STATE_BINPLACE)) {
        if (Warning) {
            RunningTotals.NumberLinkWarnings++;
            ThreadState->BuildMetrics.NumberLinkWarnings++;
            }
        else {
            RunningTotals.NumberLinkErrors++;
            ThreadState->BuildMetrics.NumberLinkErrors++;
            }
        }
    else {
        if (Warning) {
            RunningTotals.NumberCompileWarnings++;
            ThreadState->BuildMetrics.NumberCompileWarnings++;
            }
        else {
            RunningTotals.NumberCompileErrors++;
            ThreadState->BuildMetrics.NumberCompileErrors++;
            if (ThreadState->CompileDirDB) {
                ThreadState->CompileDirDB->DirFlags |= DIRDB_COMPILEERRORS;
                }
                }
            }

    // safe to use. it is protected by the TTY critical section
    szXMLBuffer[0] = 0;

    if (fParallel && fThreadIndex) {
        sprintf(szXMLBuffer, "%d>", ThreadState->ThreadIndex);
        }

    strcat(szXMLBuffer, p);

    if (Warning) {
        ThreadState->BuildMetrics.NumberActWarnings++;
    }
    else {
        ThreadState->BuildMetrics.NumberActErrors++;
    }

    if (fXMLOutput) {
        XMLThreadWrite(ThreadState, "<%s MESSAGE=\"%s\"/>", Warning ? "WARNING" : "ERROR", XMLEncodeBuiltInEntities(szXMLBuffer, sizeof(szXMLBuffer)));
    }

    WriteTTYLoggingErrors( Warning, ThreadState, szXMLBuffer );
    WriteTTYLoggingErrors( Warning, ThreadState, "\r\n" );

    if (fColorConsole)
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), csbi.wAttributes);

    return( FALSE );
}


//+---------------------------------------------------------------------------
//
//  Function:   PassThroughFilter
//
//  Synopsis:   Straight pass-through filter for compiler messages
//
//----------------------------------------------------------------------------

BOOL
PassThroughFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    return PassThrough( ThreadState, p, FALSE );
}

//+---------------------------------------------------------------------------
//
//  Function:   NMakeFilter
//
//  Synopsis:   Filters output from NMAKE so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the build
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    10-Jun-99     patbr  Created
//
//----------------------------------------------------------------------------

BOOL
NMakeFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning)) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, FALSE );
        return( TRUE );
    }
    else {
        return( FALSE );
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   BisonFilter
//
//  Synopsis:   Filters output from the bison compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//                               (compiling, linking, etc...)
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    04-Oct-99     TomSe    Created
//
//  Notes:
//
//    This routine filters strings in the bison compiler format.  That is:
//
//        Accepted String formats are:
//
//        ("myfile.y", line 3) error: unknown character: #
//        "myfile.y", line 83: no input grammar
//        vapi.y contains 1 useless nonterminal and 1 useless rule
//
//----------------------------------------------------------------------------

BOOL
BisonFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName = NULL;
    LPSTR LineNumber = NULL;
    LPSTR Message = NULL;
    BOOL Warning = TRUE;

    // First colon marks beginnning of message.
    LPSTR p1 = strchr(p,':');

    if (p1)
    {
        Message = p1 + 1;
        *p1 = '\0';

        // Get filename, line number.
        p1 = p;

        do
        {
            Warning = FALSE;

            // Skip (.
            if ( '(' == *p1 )
            {
                p1++;
            }

            // Skip over leading quote in filename.
            if ( '"' != *p1 )
            {
                // Unexpected format.
                break;
            }
            p1++;

            FileName = p1;

            // Look for trailing quote in filename.
            p1 = strchr( p1, '"');
            if (NULL==p1)
            {
                // Unexpected format.
                FileName = NULL;
                break;
            }

            *p1 = '\0';

            p1++;

            if (0 !=strncmp( p1, ", line ", 7))
            {
                // Unexpected format.
                FileName = NULL;
                break;
            }
            p1 += 7;

            LineNumber = p1;

            while (isdigit(*p1))
            {
                p1++;
            }

            *p1 = '\0';
        }
        while (0);
    }
    else
    {
        // Take whole string as message if no colon is found.
        Message = p;
    }

    if (NULL==FileName)
    {
        FileName = ThreadState->ChildCurrentFile;
    }

    FormatMsErrorMessage( ThreadState,
                          FileName, LineNumber, Message, Warning );

    // This was a warning or error.
    return TRUE ;
}



//+---------------------------------------------------------------------------
//
//  Function:   C510Filter
//
//  Synopsis:   Compiler filter which strips out unwanted warnings.
//
//  Arguments:  [ThreadState] --
//              [p]           --
//
//----------------------------------------------------------------------------

BOOL
C510Filter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning
                        )
       ) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
        }
    else {
        return( FALSE );
        }
}

//+---------------------------------------------------------------------------
//
//  Function:   MSBCFilter
//
//  Synopsis:   Filters output from the Basic compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    08-Dec-09     marioch  Created
//
//----------------------------------------------------------------------------

BOOL
MSBCFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (!strncmp(p, "BC Compiler error", 17)) {
        FormatMsErrorMessage( ThreadState,
                              ThreadState->ChildCurrentFile, NULL, p, FALSE );
        return TRUE;
    }

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning)) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
    }
    else {
        char *pErrorMsg;
        if (NULL != (pErrorMsg = strstr(p, "error BC"))) {
            FormatMsErrorMessage( ThreadState,
                                  ThreadState->ChildCurrentFile, NULL, pErrorMsg+6, FALSE );
            return TRUE;
        }
        return( FALSE );
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   MSJVCFilter
//
//  Synopsis:   Filters output from the JVC compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    24-Mar-99     patbr  Created
//
//----------------------------------------------------------------------------

BOOL
MSJVCFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (!strncmp(p, "fatal error J", 13) || !strncmp(p, "error J", 7)) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
        if (fColorConsole)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        WriteTTYLoggingErrors( FALSE, ThreadState, p );
        WriteTTYLoggingErrors( FALSE, ThreadState, "\r\n" );
        if (fColorConsole)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), csbi.wAttributes);
        RunningTotals.NumberCompileErrors++;
        ThreadState->BuildMetrics.NumberCompileErrors++;
        return TRUE;
    }

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning)) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
    }
    else {
        return( FALSE );
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   MSCoolFilter
//
//  Synopsis:   Filters output from the COOL compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    2-Jun-99     patbr  Created
//
//----------------------------------------------------------------------------

BOOL
MSCoolFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (!strncmp(p, "fatal error SC", 14) || !strncmp(p, "error SC", 8)) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
        if (fColorConsole)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        WriteTTYLoggingErrors( FALSE, ThreadState, p );
        WriteTTYLoggingErrors( FALSE, ThreadState, "\r\n" );
        if (fColorConsole)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), csbi.wAttributes);
        RunningTotals.NumberCompileErrors++;
        ThreadState->BuildMetrics.NumberCompileErrors++;
        return TRUE;
    }

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning)) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
    }
    else {
        return( FALSE );
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   MSCSharpFilter
//
//  Synopsis:   Filters output from the CSharp compiler so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    6-Nov-00     sbonev  Copy of MSCoolFilter
//
//----------------------------------------------------------------------------

BOOL
MSCSharpFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (!strncmp(p, "fatal error CS", 14) || !strncmp(p, "error CS", 8)) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
        if (fColorConsole)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        WriteTTYLoggingErrors( FALSE, ThreadState, p );
        WriteTTYLoggingErrors( FALSE, ThreadState, "\r\n" );
        if (fColorConsole)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), csbi.wAttributes);
        RunningTotals.NumberCompileErrors++;
        ThreadState->BuildMetrics.NumberCompileErrors++;
        return TRUE;
    }

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning)) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
    }
    else {
        return( FALSE );
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   ResGenFilter
//
//  Synopsis:   Filters output from the .NET Resource Generator so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    22-Mar-01     sbonev
//
//----------------------------------------------------------------------------

BOOL
ResGenFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    if (!strncmp(p, "ResGen: Error: ", 15)) {
        LPSTR LineNumber = _strdup(p);
        LPSTR pch = LineNumber;
        LPCSTR Line = strstr(p, ". Line ");
        LPCSTR Pos = strstr(p, ", position ");
        LineNumber[0] = 0;

        // put line,pos info if available
        if (NULL != Line) {
            Line += 7;
            while (isdigit(*Line)) *pch++ = *Line++;

            if (NULL != Pos) {
                Pos += 11;
                *pch++ = ',';
                while (isdigit(*Pos)) *pch++ = *Pos++;
                }
            }

        FormatMsErrorMessage( 
            ThreadState, 
            ThreadState->ChildCurrentFile, 
            LineNumber, 
            strlen(ThreadState->ChildCurrentFile) > 0 ? p + 15 : p, // display full message if there is no filename
            FALSE);

        free(LineNumber);
        return TRUE;
    }

    return( FALSE );
}

//+---------------------------------------------------------------------------
//
//  Function:   CScriptFilter
//
//  Synopsis:   Filters output from Windows Script Host so we know what's happening
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    22-Mar-01     sbonev
//
//----------------------------------------------------------------------------
BOOL
CScriptFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    if (NULL != strstr(p, "Microsoft JScript runtime error:") ||
        NULL != strstr(p, "Microsoft JScript compilation error:") ||
        NULL != strstr(p, "Microsoft VBScript runtime error:") ||
        NULL != strstr(p, "Microsoft VBScript compilation error:")) {

        // just display the message
        PassThrough( ThreadState, p, FALSE );
        return TRUE;

    }

    return( FALSE );
}

//+---------------------------------------------------------------------------
//
//  Function:   ToolNotFoundFilter
//
//  Synopsis:   Filters output from the build looking for "name not recognized"
//
//  Arguments:  [ThreadState] -- State of thread watching the compiler
//              [p]           -- Message we're trying to parse.
//
//  Returns:    TRUE  - Message is an error or warning
//              FALSE - Message is not an error or a warning
//
//  History:    10-Dec-98     patbr  Created
//
//----------------------------------------------------------------------------

BOOL
ToolNotFoundFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    if ((!strncmp(p, "The name specified is not recognized", 36)) ||
        (!strncmp(p, "internal or external command", 28))) {
        FormatMsErrorMessage( ThreadState,
                              ThreadState->ChildCurrentFile, NULL, p, FALSE );
        return TRUE;
    }

    return (FALSE);
}


//+---------------------------------------------------------------------------
//
//  Function:   MSToolFilter
//
//----------------------------------------------------------------------------

BOOL
MSToolFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning
                        )
       ) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
        }
    else {
        return( FALSE );
        }
}


BOOL
LinkFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    );

//+---------------------------------------------------------------------------
//
//  Function:   LinkFilter1
//
//----------------------------------------------------------------------------

BOOL
LinkFilter1(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR p1;
    char buffer[ 256 ];

    if (p[ strlen( p ) - 1 ] == ':') {
        return( LinkFilter( ThreadState, p ) );
        }

    p1 = p;
    while (*p1) {
        if (*p1 == '(') {
            *p1++ = 0;
            if (*p1 == '.' && p1[1] == '\\') {
                p1 += 2;
                }
            FileName = p1;
            while (*p1) {
                if (*p1 == ')') {
                    *p1++ = 0;
                    strcpy( buffer, "L2029: Unresolved external reference to " );
                    strcat( buffer, ThreadState->UndefinedId );
                    FormatMsErrorMessage( ThreadState, FileName, "1",
                                          buffer, FALSE
                                        );
                    return( TRUE );
                    }
                else {
                    p1++;
                    }
                }
            }
        else {
            p1++;
            }
        }

    return( FALSE  );
}


//+---------------------------------------------------------------------------
//
//  Function:   LinkFilter
//
//----------------------------------------------------------------------------

BOOL
LinkFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;
    LPSTR p1;

    p1 = p;
    while (*p1) {
        if (*p1 == ':') {
            if (p1[-1] == ']') {
                return( FALSE );
                }

            if (p1[-1] == ' ' && p1[1] == ' ') {
                if (MsCompilerFilter( ThreadState, p,
                                      &FileName,
                                      &LineNumber,
                                      &Message,
                                      &Warning
                                    )
                   ) {

                    if (!Warning || !(_strnicmp(Message, "L4021", 5) || 
                          _strnicmp(Message, "L4038", 5) ||
                              _strnicmp(Message, "L4046", 5))) {
                        if (LineNumber)
                            FileName = LineNumber;
                        if (FileName[0] == '.' && FileName[1] == '\\') {
                            FileName += 2;
                            }
                        FormatMsErrorMessage( ThreadState, FileName, "1",
                                              Message, FALSE );
                        return( TRUE );
                        }
                    }

                   FormatMsErrorMessage( ThreadState, FileName, "1",
                                           Message, TRUE );                 

  
                return( TRUE );
                }

            if (p1[-1] == ')') {
                p1 -= 11;
                if (p1 > p && !strcmp( p1, " in file(s):" )) {
                    strcpy( ThreadState->UndefinedId,
                            IsolateFirstToken( &p, ' ' )
                          );
                    ThreadState->FilterProc = LinkFilter1;
                    return( TRUE );
                    }
                }

            return( FALSE );
            }
        else {
            p1++;
            }
        }

    return( FALSE );
}


BOOL
DetermineChildState(
    PTHREADSTATE ThreadState,
    LPSTR p
    );

//+---------------------------------------------------------------------------
//
//  Function:   CoffFilter
//
//----------------------------------------------------------------------------

BOOL
CoffFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;

    if (MsCompilerFilter( ThreadState, p,
                          &FileName,
                          &LineNumber,
                          &Message,
                          &Warning
                        )
       ) {
        FormatMsErrorMessage( ThreadState,
                              FileName, LineNumber, Message, Warning );
        return( TRUE );
        }
    else {
        return( FALSE );
        }
}

//+---------------------------------------------------------------------------
//
//  Function:   ClRiscFilter
//
//  Synopsis:   Risc compiler filter
//
//  BUGBUG -- It may be possible to remove this filter.
//
//----------------------------------------------------------------------------

BOOL
ClRiscFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR FileName;
    LPSTR LineNumber;
    LPSTR Message;
    BOOL Warning;
    LPSTR q;

    if (TestPrefix( &p, "cfe: " )) {
        if (strncmp(p, "Error: ", strlen("Error: ")) == 0) {
            p += strlen("Error: ");
            Warning = FALSE;

        } else if (strncmp(p, "Warning: ", strlen("Warning: ")) == 0) {
            p += strlen("Warning: ");
            Warning = TRUE;
        } else {
            return(FALSE);
        }

        q = p;
        if (p = strstr( p, ".\\\\" )) {
            p += 3;
        } else {
            p = q;
        }

        FileName = p;
        while (*p > ' ') {
            if (*p == ',' || (*p == ':' && *(p+1) == ' ')) {
                *p++ = '\0';
                break;
                }

            p++;
            }

        if (*p != ' ') {
            return( FALSE );
            }

        *p++ = '\0';

        if (strcmp(p, "line ") == 0) {
            p += strlen("line ");

        }

        LineNumber = p;
        while (*p != '\0' && *p != ':') {
            p++;
            }

        if (*p != ':') {
            return( FALSE );
            }

        *p++ = '\0';
        if (*p == ' ') {
            Message = p+1;
            ThreadState->LinesToIgnore = 2;

            FormatMsErrorMessage( ThreadState,
                                  FileName,
                                  LineNumber,
                                  Message,
                                  Warning
                                );
            return( TRUE );
            }
        }
    //
    // If we did not recognize the cfe compiler, pass it to the MS compiler
    // message filter
    //

    return( C510Filter( ThreadState, p ) );
}

//+---------------------------------------------------------------------------
//
//  Function:   MgClientFilter
//
//----------------------------------------------------------------------------

BOOL
MgClientFilter(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    return( PassThrough( ThreadState, p, TRUE ) );
}


//+---------------------------------------------------------------------------
//
//  Function:   FormatMsErrorMessage
//
//  Synopsis:   Take the information obtained from MsCompilerFilter,
//              reconstruct the error message, and print it to the screen.
//
//----------------------------------------------------------------------------

VOID
FormatMsErrorMessage(
    PTHREADSTATE ThreadState,
    LPSTR FileName,
    LPSTR LineNumber,
    LPSTR Message,
    BOOL Warning
    )
{
    char *DirectoryToUse;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
    if (fColorConsole) {
        if (Warning)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    }

    if (ThreadState->ChildState == STATE_LIBING) {
        if (Warning) {
            RunningTotals.NumberLibraryWarnings++;
            ThreadState->BuildMetrics.NumberLibraryWarnings++;
            }
        else {
            RunningTotals.NumberLibraryErrors++;
            ThreadState->BuildMetrics.NumberLibraryErrors++;
            }
        }

    else
    if ((ThreadState->ChildState == STATE_LINKING) ||
        (ThreadState->ChildState == STATE_BINPLACE)) {
        if (Warning) {
            RunningTotals.NumberLinkWarnings++;
            ThreadState->BuildMetrics.NumberLinkWarnings++;
            }
        else {
            RunningTotals.NumberLinkErrors++;
            ThreadState->BuildMetrics.NumberLinkErrors++;
            }
        }
    else {
        if (Warning) {
            RunningTotals.NumberCompileWarnings++;
            ThreadState->BuildMetrics.NumberCompileWarnings++;
            }
        else {
            RunningTotals.NumberCompileErrors++;
            ThreadState->BuildMetrics.NumberCompileErrors++;
            if (ThreadState->CompileDirDB) {
                ThreadState->CompileDirDB->DirFlags |= DIRDB_COMPILEERRORS;
                }
            }
        }

    // start filling up the buffer for the XML log file; 
    // however, we are going to use the same buffer even if no XML log is requested
    // safe to use - it is protected by the TTY critical section
    szXMLBuffer[0] = 0;

    if (fParallel && fThreadIndex ) {
        sprintf(szXMLBuffer, "%d>", ThreadState->ThreadIndex);
    }

    if (FileName) {
        DirectoryToUse = ThreadState->ChildCurrentDirectory;

        if (TestPrefix( &FileName, CurrentDirectory )) {
            DirectoryToUse = CurrentDirectory;
            if (*FileName == '\\') {
                FileName++;
                }
            }

        if (TestPrefix( &FileName, ThreadState->ChildCurrentDirectory )) {
            DirectoryToUse = ThreadState->ChildCurrentDirectory;
            if (*FileName == '\\') {
                FileName++;
                }
            }

        // check for some special cases when the FileName is actually the tool name
        // and should not be prepended with path

        if (ThreadState->FilterProc == CoffFilter && _stricmp(FileName, "link") == 0 ||
            ThreadState->FilterProc == CoffFilter && _stricmp(FileName, "lib") == 0) {
            strcat(szXMLBuffer, FileName);
            }
        else {
            strcat(szXMLBuffer, FormatPathName( DirectoryToUse, FileName));
            }
        }

    if (LineNumber && strlen(LineNumber) > 0) {
        strcat(szXMLBuffer, "(");
        strcat(szXMLBuffer, LineNumber);
        strcat(szXMLBuffer, ")");
        }
    if ((FileName && strlen(FileName) > 0) || (LineNumber && strlen(LineNumber) > 0)) {
        strcat(szXMLBuffer, " : ");
        }
    if (Warning) {
        strcat(szXMLBuffer, "warning ");
        }
    else {
        strcat(szXMLBuffer, "error ");
        }
    strcat(szXMLBuffer, Message);

    if (Warning) {
        ThreadState->BuildMetrics.NumberActWarnings++;
    }
    else {
        ThreadState->BuildMetrics.NumberActErrors++;
    }

    if (fXMLOutput) {
        XMLThreadWrite(ThreadState, "<%s MESSAGE=\"%s\"/>", Warning ? "WARNING" : "ERROR", XMLEncodeBuiltInEntities(szXMLBuffer, sizeof(szXMLBuffer)));
    }

    WriteTTYLoggingErrors( Warning, ThreadState, szXMLBuffer);
    WriteTTYLoggingErrors( Warning, ThreadState, "\r\n" );

    if (fColorConsole)
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), csbi.wAttributes);
}


BOOL fAlreadyUnknown = FALSE;

//+---------------------------------------------------------------------------
//
//  Function:   DetermineChildState
//
//  Synopsis:   Parse the message given by the compiler (or whatever) and try
//              to figure out what it's doing.
//
//  Arguments:  [ThreadState] -- Current thread state
//              [p]           -- New message string
//
//  Returns:    TRUE if we figured it out, FALSE if we didn't recognize
//              anything.
//
//----------------------------------------------------------------------------

BOOL
DetermineChildState(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    PFILEREC FileDB;
    USHORT SaveRow;
    USHORT SaveCol;
    USHORT SaveRowTop;
    char buffer[ DB_MAX_PATH_LENGTH ];
    char CheckFileName[300];
    LPSTR FileName;
    LPSTR pCheckFileName;
    ULONG PercentDone;
    LONG FilesLeft;
    LONG LinesLeft;
    ULONG LinesPerSecond;
    ULONG SecondsLeft;
    BOOL fStatusOutput = FALSE;

    //
    // ************ Determine what state the child process is in.
    //               (Compiling, linking, running MIDL, etc.)
    //
    if ( TestCommandPrefix( &p, "rc ") || TestCommandPrefix( &p, "rc.exe ")) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildState = STATE_COMPILING;
        ThreadState->ChildFlags = 0;
        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestCommandPrefix( &p, "rc16 ") ) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildState = STATE_COMPILING;
        ThreadState->ChildFlags = 0;
        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if ( TestCommandPrefix( &p, "cl " )  || TestCommandPrefix( &p, "cl.exe " ) ||
         TestCommandPrefix( &p, "covc " )  || TestCommandPrefix( &p, "covc.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = C510Filter;
        ThreadState->ChildFlags = 0;
        if ( strstr( p, "/WX" ) != NULL || strstr( p, "-WX" ) != NULL) {
            ThreadState->ChildFlags |= FLAGS_WARNINGS_ARE_ERRORS;
        }
        if ((strstr( p, "/EP " ) != NULL) ||
            (strstr( p, "/E " ) != NULL) ||
            (strstr( p, "/P " ) != NULL) ||
            (strstr( p, "-EP " ) != NULL) ||
            (strstr( p, "-E " ) != NULL) ||
            (strstr( p, "-P " ) != NULL)
           ) {
            if (strstr( p, "i386") || strstr( p, "I386")) {
                ThreadState->ChildTarget = i386TargetMachine.Description;
            }
            else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
                ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
            else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
                ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
            else if (strstr( p, "ia64") || strstr( p, "IA64")) {
                ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
            else {
                ThreadState->ChildTarget = "unknown target";
            }

            strcpy( ThreadState->ChildCurrentFile,IsolateLastToken( p, ' ' ) );
            if ( strstr( p, ".s" ) != NULL )
                ThreadState->ChildState = STATE_S_PREPROC;
            else
                ThreadState->ChildState = STATE_C_PREPROC;
            }
        else
        if ( (pch = strstr( p, "/Yc" )) != NULL ) {
            size_t namelen = strcspn( pch+3, " \t" );
            if (strstr( p, "i386") || strstr( p, "I386")) {
                ThreadState->ChildTarget = i386TargetMachine.Description;
            }
            else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
                ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
            else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
                ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
            else if (strstr( p, "ia64") || strstr( p, "IA64")) {
                ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
            else {
                ThreadState->ChildTarget = "unknown target";
            }

            ThreadState->ChildState = STATE_PRECOMP;
            strncpy( ThreadState->ChildCurrentFile,
                     pch + 3, namelen
                  );
            ThreadState->ChildCurrentFile[namelen] = '\0';
            }
        else
        if (((pch = strstr( p, "*.c" )) != NULL ) || ((pch = strstr( p, "*.cxx" )) != NULL ) || ((pch = strstr( p, "*.cpp" )) != NULL ) ||
            (((pch = strstr( p, ".c " )) != NULL ) && ((pch2 = strstr( pch+1, ".c" )) != NULL )) ||
            (((pch = strstr( p, ".cxx " )) != NULL ) && ((pch2 = strstr( pch+1, ".cxx" )) != NULL )) ||
            (((pch = strstr( p, ".cpp " )) != NULL ) && ((pch2 = strstr( pch+1, ".cpp" )) != NULL ))) {
            if (strstr( p, "i386") || strstr( p, "I386")) {
                ThreadState->ChildTarget = i386TargetMachine.Description;
            }
            else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
                ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
            else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
                ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
            else if (strstr( p, "ia64") || strstr( p, "IA64")) {
                ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
            else {
                ThreadState->ChildTarget = "unknown target";
            }
            ThreadState->ChildState = STATE_BATCHCOMPILE;
            return FALSE;   // batch compiles will be counted by progress output
        }
        else {
            if (strstr( p, "i386") || strstr( p, "I386")) {
                ThreadState->ChildTarget = i386TargetMachine.Description;
            }
            else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
                ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
            else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
                ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
            else if (strstr( p, "ia64") || strstr( p, "IA64")) {
                ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
            else {
                ThreadState->ChildTarget = "unknown target";
            }
            ThreadState->ChildState = STATE_COMPILING;
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateLastToken( p, ' ' )
                  );
            }
        }
    else

    if ( TestCommandPrefix( &p, "cl16 " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = C510Filter;
        ThreadState->ChildFlags = 0;
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }

        ThreadState->ChildState = STATE_COMPILING;
        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' ));
        }
    else

    if (TestCommandPrefix( &p, "bc " ) || TestCommandPrefix( &p, "bc.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        if (IsolateFirstToken( &p, '-' )) {
            if (*p == '\0')
                return FALSE; // This is a warning/error string
            while(*p != 'i')
            {
                if (!IsolateFirstToken( &p, '-' ))
                {
                    break;
                }
            }

            p++;
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ' ' ));

            ThreadState->ChildFlags = 0;
            ThreadState->ChildTarget = "all platforms";
            ThreadState->FilterProc = MSBCFilter;

            ThreadState->ChildState = STATE_COMPILING;
            }
        }
    else

    if (TestCommandPrefix( &p, "vbc " ) || TestCommandPrefix( &p, "vbc.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSBCFilter;

        ThreadState->ChildState = STATE_COMPILING;
        strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
    else

    if (TestCommandPrefix( &p, "jvc " ) || TestCommandPrefix( &p, "jvc.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSJVCFilter;

        if (((pch = strstr( p, "*.java" )) != NULL ) || 
            (((pch = strstr( p, ".java" )) != NULL ) && ((pch2 = strstr( pch+1, ".java" )) != NULL ))) {
            ThreadState->ChildState = STATE_BATCHCOMPILE;
            // batch compiles will be counted by progress output
            if (getenv("JVC_TERSE") != NULL)
                strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, '\\' ) );
            else
                return FALSE;
        } else {
            ThreadState->ChildState = STATE_COMPILING;
            strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
        }
    else

    if (TestCommandPrefix( &p, "coolc " ) || TestCommandPrefix( &p, "coolc.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSCoolFilter;

        if (((pch = strstr( p, "*.cool" )) != NULL ) || 
            (((pch = strstr( p, ".cool" )) != NULL ) && ((pch2 = strstr( pch+1, ".cool" )) != NULL ))) {
            ThreadState->ChildState = STATE_BATCHCOMPILE;
            // batch compiles will be counted by progress output
            return FALSE;
        } else {
            ThreadState->ChildState = STATE_COMPILING;
            strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
        }
    else

    if (TestCommandPrefix( &p, "csc " ) || TestCommandPrefix( &p, "csc.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSCSharpFilter;

        if (((pch = strstr( p, "*.cs" )) != NULL ) || 
            (((pch = strstr( p, ".cs" )) != NULL ) && ((pch2 = strstr( pch+1, ".cs" )) != NULL ))) {
            ThreadState->ChildState = STATE_BATCHCOMPILE;
            // batch compiles will be counted by progress output
            return FALSE;
        } else {
            ThreadState->ChildState = STATE_COMPILING;
            strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
        }
    else

    if (TestCommandPrefix( &p, "resgen " ) || TestCommandPrefix( &p, "resgen.exe " ) || TestCommandPrefix( &p, "ResGen: Error:" )) {
        //
        // resgen usage:
        // ResGen inputFile.ext [outputFile.ext]
        //   no wildcards

        if (*(p-1) == ':') {
            // this is an error string
            if (ThreadState->FilterProc != ResGenFilter) {
                // switch the filter proc if we didn't know that ResGen was running
                ThreadState->FilterProc = ResGenFilter;
                strcpy( ThreadState->ChildCurrentFile, "" );
                }
            return FALSE;
            }

        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = ResGenFilter;

        ThreadState->ChildState = STATE_COMPILING;
        strcpy( ThreadState->ChildCurrentFile, IsolateFirstToken( &p, ' ' ) );
        }
    else

    if (TestCommandPrefix( &p, "cscript " ) || TestCommandPrefix( &p, "cscript.exe " )) {
        //
        // cscript usage:
        // CScript [option...] scriptname.extension [option...] [arguments...]
        // options are prefixed with / or -

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->ChildState = STATE_VSTOOL;
        ThreadState->FilterProc = CScriptFilter;
        strcpy( ThreadState->ChildCurrentFile, "" );    // don't care about the name; it would be displayed on error
        }
    else

    if (TestCommandPrefix( &p, "docchecker " ) || TestCommandPrefix( &p, "docchecker.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildState = STATE_DOCCHECKING;
        ThreadState->ChildTarget = "all platforms";
        strcpy( ThreadState->ChildCurrentFile, "" );
        }
    else

    if (TestCommandPrefix( &p, "scc " ) || TestCommandPrefix( &p, "scc.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSToolFilter;

        if (((pch = strstr( p, "*.sc" )) != NULL ) || 
            (((pch = strstr( p, ".sc" )) != NULL ) && ((pch2 = strstr( pch+1, ".sc" )) != NULL ))) {
            ThreadState->ChildState = STATE_BATCHCOMPILE;
            // batch compiles will be counted by progress output
            return FALSE;
        } else {
            ThreadState->ChildState = STATE_COMPILING;
            strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
        }
    else

    if (TestCommandPrefix( &p, "wfctosafec " ) || TestCommandPrefix( &p, "wfctosafec.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSToolFilter;

        if (((pch = strstr( p, "*.sc" )) != NULL ) || 
            (((pch = strstr( p, ".sc" )) != NULL ) && ((pch2 = strstr( pch+1, ".sc" )) != NULL ))) {
            ThreadState->ChildState = STATE_BATCHCOMPILE;
            // batch compiles will be counted by progress output
            return FALSE;
        } else {
            ThreadState->ChildState = STATE_COMPILING;
            strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
        }
    else

    if (TestCommandPrefix( &p, "ml " ) || TestCommandPrefix( &p, "ml.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildState = STATE_ASSEMBLING;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = i386TargetMachine.Description;
        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestCommandPrefix( &p, "masm ") || TestCommandPrefix( &p, "masm.exe ")) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildState = STATE_ASSEMBLING;
        ThreadState->ChildFlags = 0;
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }

        if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }

        if (strstr(p, ",")) {
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateLastToken(IsolateFirstToken(&p,','), ' '));
            }
        else {
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateLastToken(IsolateFirstToken(&p,';'), ' '));
            }

        }
    else

    if (TestCommandPrefix( &p, "lib " ) || TestCommandPrefix( &p, "lib.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }
        ThreadState->FilterProc = CoffFilter;
        ThreadState->ChildFlags = 0;
        if (TestPrefix( &p, "-out:" )) {
            ThreadState->LinesToIgnore = 1;
            ThreadState->ChildState = STATE_LIBING;
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ' ' )
                  );
            }
        else
        if (TestPrefix( &p, "-def:" )) {
            ThreadState->LinesToIgnore = 1;
            ThreadState->ChildState = STATE_LIBING;
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ' ' )
                  );
            if (TestPrefix( &p, "-out:" )) {
                strcpy( ThreadState->ChildCurrentFile,
                        IsolateFirstToken( &p, ' ' )
                      );
                }
            }
        else {
            return FALSE;
            }
        }
    else

    if (TestCommandPrefix( &p, "implib " ) || TestCommandPrefix( &p, "implib.exe " ) ) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }

        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildState = STATE_LIBING;
        if (strstr(p, ";")) {
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ';' ));
            }
        else {
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ' ' ));
            } 
        }
    else

    if (TestCommandPrefix( &p, "link " ) || TestCommandPrefix( &p, "link.exe " ) || 
        TestCommandPrefix( &p, "covlink ") || TestCommandPrefix( &p, "covlink.exe ")) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }
        ThreadState->FilterProc = CoffFilter;
        ThreadState->ChildFlags = 0;
        if (TestPrefix( &p, "-out:" )) {
            ThreadState->LinesToIgnore = 2;
            ThreadState->ChildState = STATE_LINKING;
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ' ' )
                  );
            }
        }
    else

    if (TestCommandPrefix( &p, "link16" ) ) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }
        if (strstr( p, "i386") || strstr( p, "I386")) {
            ThreadState->ChildTarget = i386TargetMachine.Description;
            }
        else if (strstr( p, "alpha64") || strstr( p, "ALPHA64")) {
            ThreadState->ChildTarget = Alpha64TargetMachine.Description;
            }
        else if (strstr( p, "alpha") || strstr( p, "ALPHA")) {
            ThreadState->ChildTarget = AlphaTargetMachine.Description;
            }
        else if (strstr( p, "ia64") || strstr( p, "IA64")) {
            ThreadState->ChildTarget = ia64TargetMachine.Description;
            }
        else {
            ThreadState->ChildTarget = "unknown target";
            }

        ThreadState->FilterProc = LinkFilter;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildState = STATE_LINKING;
        p = IsolateLastToken(p, ' ');
        if (strstr(p, ";")) {
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ';' ));
            }
        else {
            strcpy( ThreadState->ChildCurrentFile,
                    IsolateFirstToken( &p, ',' ));
            }

        }
    else

    if ( TestCommandPrefix( &p, "bscmake " ) || TestCommandPrefix( &p, "bscmake.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string

        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildState = STATE_BSCMAKING;
        ThreadState->ChildTarget = "all platforms";
        if ( (pch = strstr( p, "/o" )) != NULL ) {
            size_t namelen;
            pch2 = pch + 3;
            if ( *pch2 == '"' )
                pch2++;
            namelen = strcspn( pch2, " \t\"" );
            strncpy( ThreadState->ChildCurrentFile, pch2, namelen );
            ThreadState->ChildCurrentFile[namelen] = '\0';
            }
        }
    else

    if (TestCommandPrefix( &p, "asaxp " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildState = STATE_ASSEMBLING;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = AlphaTargetMachine.Description;
        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestCommandPrefix( &p, "icl ")) {
        while (*p == ' ') {
            p++;
            }
        ThreadState->ChildState = STATE_COMPILING;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = ia64TargetMachine.Description;
        ThreadState->FilterProc = C510Filter;

        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestCommandPrefix( &p, "mktyplib " ) || TestCommandPrefix( &p, "mktyplib.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildState = STATE_MKTYPLIB;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = C510Filter;

        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestPrefix( &p, "MC: Compiling " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildState = STATE_MC;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = C510Filter;

        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestCommandPrefix( &p, "midl " ) || TestCommandPrefix( &p, "midl.exe " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildState = STATE_MIDL;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = C510Filter;

        strcpy( ThreadState->ChildCurrentFile,
                IsolateLastToken( p, ' ' )
              );
        }
    else

    if (TestCommandPrefix( &p, "asn1 " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildState = STATE_ASN;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = C510Filter;

        strcpy(ThreadState->ChildCurrentFile, IsolateLastToken(p, ' '));
        }
    else

    if (TestPrefix( &p, "Build_Status " )) {
        while (*p == ' ') {
            p++;
            }

        ThreadState->ChildState = STATE_STATUS;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "";
        ThreadState->FilterProc = C510Filter;

        strcpy( ThreadState->ChildCurrentFile, "" );
        }

    else
    if (TestCommandPrefix( &p, "binplace " )) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
        }

        // If this is a standard link/binplace step, don't tell the
        // user what's going on, just pass any errors/warnings to
        // the output.  If this is a straight binplace, list the state.

        if (ThreadState->ChildState == STATE_LINKING) {
            ThreadState->ChildState = STATE_BINPLACE;
            ThreadState->ChildFlags = 0;
            ThreadState->FilterProc = MSToolFilter;
            return TRUE;
        } else {
            ThreadState->ChildState = STATE_BINPLACE;
            ThreadState->ChildFlags = 0;
            ThreadState->FilterProc = MSToolFilter;
            strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
        }
    }

    else
    if (TestCommandPrefix( &p, "ctc " ) || TestCommandPrefix( &p, "ctc.exe " )) {
        size_t namelen;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
        }

        ThreadState->ChildState = STATE_CTCOMPILING;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSToolFilter;
        while (*p == '-') {
            p = p + strcspn( p, " \t" );
            while (*p == ' ')
                p++;
        }
        namelen = strcspn( p, " \t" );
        strncpy( ThreadState->ChildCurrentFile, p, namelen );
        ThreadState->ChildCurrentFile[namelen] = '\0';
    }

    else
    if (TestCommandPrefix( &p, "idheader " )) {
        size_t namelen;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
        }

        ThreadState->ChildState = STATE_VSTOOL;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSToolFilter;
        namelen = strcspn( p, " \t" );
        strncpy( ThreadState->ChildCurrentFile, p, namelen );
        ThreadState->ChildCurrentFile[namelen] = '\0';
    }

    else
    if (TestCommandPrefix( &p, "bison ")) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
        }

        ThreadState->ChildState = STATE_VSTOOL;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = MSToolFilter;
        strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
    }

    else
    if (TestCommandPrefix( &p, "gnu_bison ")) {
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        while (*p == ' ') {
            p++;
        }

        ThreadState->ChildState = STATE_VSTOOL;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildTarget = "all platforms";
        ThreadState->FilterProc = BisonFilter;
        strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, ' ' ) );
    }

    else
    if ( TestCommandPrefix( &p, "vsautodoc " ) || TestCommandPrefix( &p, "vsautodoc.exe " )) {
        LPSTR pch, pch2;
        if (*p == ':')
            return FALSE;       // This is a warning/error string
        ThreadState->FilterProc = MSToolFilter;
        ThreadState->ChildFlags = 0;
        ThreadState->ChildState = STATE_AUTODOCING;
        ThreadState->ChildTarget = "all platforms";
        if ( (pch = strstr( p, "/o" )) != NULL ) {
            size_t namelen;
            pch2 = pch + 3;
            if ( *pch2 == '"' )
                pch2++;
            namelen = strcspn( pch2, " \t\"" );
            strncpy( ThreadState->ChildCurrentFile, pch2, namelen );
            ThreadState->ChildCurrentFile[namelen] = '\0';
            }
        }
    else

    if (ThreadState->ChildState == STATE_BATCHCOMPILE) {
        if (strstr( p, "integral type to pointer") ||
            strstr( p, "this conversion is possible") ||
            strstr( p, "void cannot be converted") ||
            strstr( p, "Compiling...") ||
            strstr( p, "Generating Code...") ||
            strstr( p, "Parsing ") ||
            strstr( p, "Loading class:") ||
            strstr( p, "Generating file "))
            return FALSE;       // This is a warning/error/info string
        if (strstr( p, ".c") && !strchr( p, ' ') && !strchr( p, ':'))
            strcpy( ThreadState->ChildCurrentFile, p ); // C/C++ compile
        else if (strstr( p, ".java") && strstr( p, "Compiling ")) {
            if (getenv("JVC_TERSE") != NULL) {
                RunningTotals.NumberCompiles++;
                ThreadState->BuildMetrics.NumberCompiles++;
                return FALSE;
            } else {
                strcpy( ThreadState->ChildCurrentFile, IsolateLastToken( p, '\\' ) ); // Java compile
            }
        }
        else
            return FALSE;
    }

    else {
        return FALSE;
        }

    //
    // ***************** Set the Thread State according to what we determined.
    //
    if ((strstr( ThreadState->ChildCurrentFile, "*.c" ) == NULL ) && (strstr( ThreadState->ChildCurrentFile, "*.cxx" ) == NULL ) &&
        (strstr( ThreadState->ChildCurrentFile, "*.cpp" ) == NULL ) && (strstr( ThreadState->ChildCurrentFile, "*.java" ) == NULL )) {
        FileName = ThreadState->ChildCurrentFile;

        // make sure directories match to trailing backslash
        strcpy(CheckFileName, FileName);
        pCheckFileName = CheckFileName;

        if (TestPrefix( &pCheckFileName, CurrentDirectory )) {
            if (*pCheckFileName == '\\') {
                FileName += (pCheckFileName - CheckFileName) + 1;
            }

            if (TestPrefix( &pCheckFileName, ThreadState->ChildCurrentDirectory )) {
                if (*pCheckFileName == '\\') {
                    FileName += (pCheckFileName - CheckFileName) + 1;
                }
            }

            strcpy( ThreadState->ChildCurrentFile, FileName );
        }
    }

    FileDB = NULL;

    if (ThreadState->ChildState == STATE_LIBING) {
        RunningTotals.NumberLibraries++;
        ThreadState->BuildMetrics.NumberLibraries++;
        }
    else
    if (ThreadState->ChildState == STATE_LINKING) {
        RunningTotals.NumberLinks++;
        ThreadState->BuildMetrics.NumberLinks++;
        }
    else
    if (ThreadState->ChildState == STATE_BSCMAKING) {
        RunningTotals.NumberBSCMakes++;
        ThreadState->BuildMetrics.NumberBSCMakes++;
        }
    else
    if ((ThreadState->ChildState == STATE_STATUS) ||
        (ThreadState->ChildState == STATE_BINPLACE) ||
        (ThreadState->ChildState == STATE_UNKNOWN)) {
        ;  // Do nothing.
        }
    else {
        if (ThreadState->CompileDirDB) {
            if ((strstr( ThreadState->ChildCurrentFile, "*.c" ) == NULL ) && (strstr( ThreadState->ChildCurrentFile, "*.cxx" ) == NULL ) &&
                (strstr( ThreadState->ChildCurrentFile, "*.cpp" ) == NULL ) && (strstr( ThreadState->ChildCurrentFile, "*.java" ) == NULL )) {
                RunningTotals.NumberCompiles++;
                ThreadState->BuildMetrics.NumberCompiles++;
                CopyString(ThreadState->ChildCurrentFile, ThreadState->ChildCurrentFile, TRUE);
            }

            if (!fQuicky) {
                FileDB = FindSourceFileDB(
                            ThreadState->CompileDirDB,
                            ThreadState->ChildCurrentFile,
                            NULL);
            }
        }
    }

    //
    // *********************** Print the thread state to the screen
    //
    if (ThreadState->IsStdErrTty) {
        GetScreenSize(ThreadState);
        assert(ThreadState->cColTotal != 0);
        assert(ThreadState->cRowTotal != 0);

        if (fStatus) {
            GetCursorPosition(&SaveRow, &SaveCol, &SaveRowTop);

            //  Clear row for process message
            ClearRows (ThreadState,
                       (USHORT) (SaveRowTop + ThreadState->ThreadIndex - 1),
                       1,
                       StatusCell);

            //  Clear row for status message
            ClearRows (ThreadState,
                       (USHORT) (SaveRowTop + NumberProcesses),
                       1,
                       StatusCell);

            //  Make sure there's still some room at the bottom
            if (SaveRow == LastRow(ThreadState)) {
                USHORT RowTop = 1 + SaveRowTop + (USHORT) NumberProcesses + 1;

                MoveRectangleUp (
                    RowTop,                     // Top
                    0,                          // Left
                    LastRow(ThreadState),       // Bottom
                    LastCol(ThreadState),       // Right
                    1,                          // NumRow
                    ScreenCell);                // FillCell

                SaveRow--;
            }

            SetCursorPosition(
                (USHORT) (SaveRowTop + ThreadState->ThreadIndex - 1),
                0);
            fStatusOutput = TRUE;
        }
    }

    if (strstr(ThreadState->ChildCurrentFile, ".cxx") ||
        strstr(ThreadState->ChildCurrentFile, ".cpp")) {
        ThreadState->ChildFlags |= FLAGS_CXX_FILE;
    }

    if (szBuildTag) {
        sprintf(buffer, "%s: ", szBuildTag);
        WriteTTY(ThreadState, buffer, fStatusOutput);
    }

    if (fParallel) {
        sprintf(buffer, "%d>", ThreadState->ThreadIndex);
        WriteTTY(ThreadState, buffer, fStatusOutput);
    }

    if (ThreadState->ChildState == STATE_UNKNOWN) {
        if (!fAlreadyUnknown) {
            WriteTTY(
                ThreadState,
                "Processing Unknown item(s)...\r\n",
                fStatusOutput);
            fAlreadyUnknown = TRUE;
        }
    }
    else
    if (ThreadState->ChildState == STATE_STATUS) {
        WriteTTY(ThreadState, p, fStatusOutput);
        WriteTTY(ThreadState, "\r\n", fStatusOutput);
    }
    else {
        fAlreadyUnknown = FALSE;
        WriteTTY(ThreadState, States[ThreadState->ChildState], fStatusOutput);
        WriteTTY(ThreadState, " - ", fStatusOutput);
        if ((strstr( ThreadState->ChildCurrentFile, "*.c" ) == NULL ) && (strstr( ThreadState->ChildCurrentFile, "*.cxx" ) == NULL ) &&
            (strstr( ThreadState->ChildCurrentFile, "*.cpp" ) == NULL ) && (strstr( ThreadState->ChildCurrentFile, "*.java" ) == NULL )) {
            WriteTTY(ThreadState, FormatPathName(ThreadState->ChildCurrentDirectory, ThreadState->ChildCurrentFile), fStatusOutput);
        } else {
            WriteTTY(ThreadState, ThreadState->ChildCurrentFile, fStatusOutput);
        }
        WriteTTY(ThreadState, " for ", fStatusOutput);
        WriteTTY(ThreadState, ThreadState->ChildTarget, fStatusOutput);
        WriteTTY(ThreadState, "\r\n", fStatusOutput);

        if (fXMLOutput) {
            XMLThreadInitBuffer(ThreadState);
            if (PXMLThreadStates[ThreadState->XMLThreadIndex]->fXMLInAction) {
                // check for action errors or warnings
                if (ThreadState->BuildMetrics.NumberActErrors || ThreadState->BuildMetrics.NumberActWarnings) {
                    sprintf(szXMLBuffer, "<ACTIONSUMMARY ");
                    if (ThreadState->BuildMetrics.NumberActErrors) {
                        sprintf(szXMLBuffer + strlen(szXMLBuffer), " ERRORS=\"%d\"", ThreadState->BuildMetrics.NumberActErrors);
                    }
                    if (ThreadState->BuildMetrics.NumberActWarnings) {
                        sprintf(szXMLBuffer + strlen(szXMLBuffer), " WARNINGS=\"%d\"", ThreadState->BuildMetrics.NumberActWarnings);
                    }
                    strcat(szXMLBuffer, "/>");
                    XMLThreadWrite(ThreadState, szXMLBuffer);
                }
                XMLThreadCloseTag(ThreadState, "ACTION");
                PXMLThreadStates[ThreadState->XMLThreadIndex]->fXMLInAction = FALSE;
            }
            XMLThreadOpenTag(ThreadState, "ACTION", "TYPE=\"%s\" FILE=\"%s\" TARGET=\"%s\"", States[ThreadState->ChildState], ThreadState->ChildCurrentFile, ThreadState->ChildTarget);
            PXMLThreadStates[ThreadState->XMLThreadIndex]->fXMLInAction = TRUE;
        }
        ThreadState->BuildMetrics.NumberDirActions++;
        ThreadState->BuildMetrics.NumberActErrors = 0;
        ThreadState->BuildMetrics.NumberActWarnings = 0;
    }

    if (StartCompileTime) {
        ElapsedCompileTime += time(NULL) - StartCompileTime;
    }

    if (FileDB != NULL) {
        StartCompileTime = time(NULL);
    }
    else {
        StartCompileTime = 0L;
    }

    //
    // ****************** Update the status line
    //
    if (fStatus) {
        if (FileDB != NULL) {
            FilesLeft = TotalFilesToCompile - TotalFilesCompiled;
            if (FilesLeft < 0) {
                FilesLeft = 0;
            }
            LinesLeft = TotalLinesToCompile - TotalLinesCompiled;
            if (LinesLeft < 0) {
                LinesLeft = 0;
                PercentDone = 99;
            }
            else if (TotalLinesToCompile != 0) {
                if (TotalLinesCompiled > 20000000L) {
                    int TLC = TotalLinesCompiled / 100;
                    int TLTC = TotalLinesToCompile / 100;

                    PercentDone = (TLC * 100L)/TLTC;
                }
                else
                    PercentDone = (TotalLinesCompiled * 100L)/TotalLinesToCompile;
            }
            else {
                PercentDone = 0;
            }

            if (ElapsedCompileTime != 0) {
                LinesPerSecond = TotalLinesCompiled / ElapsedCompileTime;
            }
            else {
                LinesPerSecond = 0;
            }

            if (LinesPerSecond != 0) {
                SecondsLeft = LinesLeft / LinesPerSecond;
            }
            else {
                SecondsLeft = LinesLeft / DEFAULT_LPS;
            }

            sprintf(
                buffer,
                "%2d%% done. %4ld %sLPS  Time Left:%s  Files: %d  %sLines: %s\r\n",
                PercentDone,
                LinesPerSecond,
                fStatusTree? "T" : "",
                FormatTime(SecondsLeft),
                FilesLeft,
                fStatusTree? "Total " : "",
                FormatNumber(LinesLeft));

            SetCursorPosition((USHORT) (SaveRowTop + NumberProcesses), 0);

            WriteTTY(ThreadState, buffer, fStatusOutput);
        }

        if (ThreadState->IsStdErrTty) {
            assert(ThreadState->cColTotal != 0);
            assert(ThreadState->cRowTotal != 0);
            SetCursorPosition(SaveRow, SaveCol);
        }
    }

    //
    // ***************** Keep track of how many files have been compiled.
    //
    if (ThreadState->ChildState == STATE_COMPILING  ||
        ThreadState->ChildState == STATE_ASSEMBLING ||
        ThreadState->ChildState == STATE_MKTYPLIB   ||
        ThreadState->ChildState == STATE_MIDL       ||
        ThreadState->ChildState == STATE_ASN        ||
        (FileDB != NULL && ThreadState->ChildState == STATE_PRECOMP)) {
        TotalFilesCompiled++;
    }
    if (FileDB != NULL) {
        TotalLinesCompiled += FileDB->TotalSourceLines;
    }

    return(TRUE);
}


//+---------------------------------------------------------------------------
//
//  Function:   ProcessLine
//
//  Synopsis:   Watch the lines coming from the thread for special strings.
//
//----------------------------------------------------------------------------

BOOL
ProcessLine(
    PTHREADSTATE ThreadState,
    LPSTR p
    )
{
    LPSTR p1;

    while (*p <= ' ') {
        if (!*p) {
            return( FALSE );
            }
        else {
            p++;
            }
        }

    p1 = p;
    while (*p1) {
        if (*p1 == '\r')
            break;
        else
            p1++;
        }
    *p1 = '\0';

    p1 = p;
    if (TestPrefix( &p1, "Stop." )) {
        return( TRUE );
        }

    //  Stop multithread access to shared:
    //      database
    //      window
    //      compilation stats

    EnterCriticalSection(&TTYCriticalSection);

    if (TestPrefix( &p1, "nmake :" )) {
        PassThrough( ThreadState, p, FALSE );
    }
    else
    if (ThreadState->LinesToIgnore) {
        ThreadState->LinesToIgnore--;
    }
    else {
        if ( !DetermineChildState( ThreadState, p ) ) {
            if (!ToolNotFoundFilter( ThreadState, p ))
                {
                if (ThreadState->FilterProc != NULL) {
                    (*ThreadState->FilterProc)( ThreadState, p );
                    }
                }
            }
        }

    if (fXMLVerboseOutput) {
        XMLThreadWrite(ThreadState, "<RAW MESSAGE=\"%s\"/>\r\n", XMLEncodeBuiltInEntitiesCopy(p, szXMLBuffer));
    }

    LeaveCriticalSection(&TTYCriticalSection);

    return( FALSE );
}


//+---------------------------------------------------------------------------
//
//  Function:   FilterThread
//
//  Synopsis:   Capture the output of the thread and process it.
//
//----------------------------------------------------------------------------

VOID
FilterThread(
    PTHREADSTATE ThreadState
    )
{
    UINT CountBytesRead;
    LPSTR StartPointer;
    LPSTR EndPointer;
    LPSTR NewPointer;
    ULONG BufSize = 512;
    UINT uThreadIdLen = 0;

    AllocMem(BufSize, &StartPointer, MT_THREADFILTER);
    while (TRUE) {
        EndPointer = StartPointer;
        do {
            if (BufSize - (EndPointer-StartPointer) < 512) {
                AllocMem(BufSize*2, &NewPointer, MT_THREADFILTER);
                RtlCopyMemory(
                    NewPointer,
                    StartPointer,
                    EndPointer - StartPointer + 1);     // copy null byte, too
                EndPointer += NewPointer - StartPointer;
                FreeMem(&StartPointer, MT_THREADFILTER);
                StartPointer = NewPointer;
                BufSize *= 2;
            }

            if (EndPointer==StartPointer && fParallel && fThreadIndex) {
                /*
                Add build thread index to beginning of message before raw thread output.
                */
                sprintf(EndPointer, "%d>", ThreadState->ThreadIndex);

                uThreadIdLen = strlen(EndPointer);
                if (!fgets(EndPointer+uThreadIdLen, 512-uThreadIdLen, ThreadState->ChildOutput)) {
                    if (errno != 0)
                        BuildError("Pipe read failed - errno = %d\n", errno);
                    FreeMem(&StartPointer, MT_THREADFILTER);
                    return;
                }
            }
            else
            {
                if (!fgets(EndPointer, 512, ThreadState->ChildOutput)) {
                    if (errno != 0)
                        BuildError("Pipe read failed - errno = %d\n", errno);
                    FreeMem(&StartPointer, MT_THREADFILTER);
                    return;
                }
            }
            CountBytesRead = strlen(EndPointer);
            EndPointer = EndPointer + CountBytesRead;
        } while (CountBytesRead == 511 && EndPointer[-1] != '\n');

        CountBytesRead = EndPointer - StartPointer;
        if (LogFile != NULL && CountBytesRead) {
            fwrite(StartPointer, 1, CountBytesRead, LogFile);
        }
        if (ProcessLine(ThreadState, StartPointer)) {
            FreeMem(&StartPointer, MT_THREADFILTER);
            return;
        }
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   ExecuteProgram
//
//  Synopsis:   Spawn a new thread to execute the given program and filter
//              its output.
//
//  Arguments:  [ProgramName]       --
//              [CommandLine]       --
//              [MoreCommandLine]   --
//              [MustBeSynchronous] -- For synchronous operation on a
//                                      multi-processor machine.
//              [XMLDir]            -- For XML output only - the name of 
//                                      the directory processed.
//              [XMLAction]         -- For XML output only - what we are
//                                      doing with the directory.
//
//  Returns:    ERROR_SUCCESS, ERROR_NOTENOUGHMEMORY, or return code from
//              PipeSpawnClose.
//
//  Notes:      On a multiprocessor machine, this will spawn a new thread
//              and then return, letting the thread run asynchronously.  Use
//              WaitForParallelThreads() to ensure all threads are finished.
//              By default, this routine will spawn as many threads as the
//              machine has processors.  This can be overridden with the -M
//              option.
//
//----------------------------------------------------------------------------

char ExecuteProgramCmdLine[ 1024 ];

UINT
ExecuteProgram(
    LPSTR ProgramName,
    LPSTR CommandLine,
    LPSTR MoreCommandLine,
    BOOL MustBeSynchronous,
    LPCSTR XMLDir,
    LPCSTR XMLAction)
{
    LPSTR p;
    UINT rc;
    THREADSTATE *ThreadState;
    UINT OldErrorMode;
    DWORD dwStartTime;

    AllocMem(sizeof(THREADSTATE), &ThreadState, MT_THREADSTATE);

    memset(ThreadState, 0, sizeof(*ThreadState));
    ThreadState->ChildState = STATE_UNKNOWN;
    ThreadState->ChildTarget = "Unknown Target";
    ThreadState->IsStdErrTty = (BOOL) _isatty(_fileno(stderr));
    ThreadState->CompileDirDB = CurrentCompileDirDB;
    ThreadState->FilterProc = NMakeFilter;

    if (ThreadState->IsStdErrTty) {
        GetScreenSize(ThreadState);
        assert(ThreadState->cColTotal != 0);
        assert(ThreadState->cRowTotal != 0);

        // We're displaying to the screen, so initialize the console.

        if (!fConsoleInitialized) {
            StatusCell[1] =
                        BACKGROUND_RED |
                        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN |
                        FOREGROUND_INTENSITY;

            ReadConsoleCells(ScreenCell, sizeof(ScreenCell), 2, 0);

            // If we stumbled upon an old Status line in row 2 of the window,
            // try the current row to avoid using the Status line background
            // colors for fill when scrolling.

            if (ScreenCell[1] == StatusCell[1]) {
                USHORT Row, Col;

                GetCursorPosition(&Row, &Col, NULL);
                ReadConsoleCells(ScreenCell, sizeof(ScreenCell), Row, 0);
            }
            ScreenCell[0] = StatusCell[0] = ' ';

            GetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), &OldConsoleMode);
            NewConsoleMode = OldConsoleMode;
            fConsoleInitialized = TRUE;
        }
        if (fStatus)
        {
            NewConsoleMode = OldConsoleMode & ~(ENABLE_WRAP_AT_EOL_OUTPUT);
        } else
        {
            NewConsoleMode = OldConsoleMode | ENABLE_WRAP_AT_EOL_OUTPUT;
        }
        SetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), NewConsoleMode);
    }
    else {
        ThreadState->cRowTotal = 0;
        ThreadState->cColTotal = 0;
    }

    p = ThreadState->ChildCurrentDirectory;
    GetCurrentDirectory(sizeof(ThreadState->ChildCurrentDirectory), p);

    if (TestPrefix(&p, CurrentDirectory)) {
        if (*p == '\\') {
            p++;
        }
        strcpy(ThreadState->ChildCurrentDirectory, p);
    }

    if (ThreadState->ChildCurrentDirectory[0]) {
        strcat(ThreadState->ChildCurrentDirectory, "\\");
    }

    sprintf(
        ExecuteProgramCmdLine,
        "%s %s%s",
        ProgramName,
        CommandLine,
        MoreCommandLine);
    LogMsg("'%s %s%s'\n", ProgramName, CommandLine, MoreCommandLine);

    if (fParallel && !MustBeSynchronous) {
        PPARALLEL_CHILD ChildData;
        DWORD i;
        DWORD ThreadId;

        AllocMem(sizeof(PARALLEL_CHILD), &ChildData, MT_CHILDDATA);
        strcpy(ChildData->ExecuteProgramCmdLine,ExecuteProgramCmdLine);
        ChildData->ThreadState = ThreadState;

        if (ThreadsStarted < NumberProcesses) {
            if (ThreadsStarted == 0) {
                AllocMem(
                    sizeof(HANDLE) * NumberProcesses,
                    (VOID **) &WorkerThreads,
                    MT_THREADHANDLES);
                AllocMem(
                    sizeof(HANDLE) * NumberProcesses,
                    (VOID **) &WorkerEvents,
                    MT_EVENTHANDLES);
            }
            WorkerEvents[ThreadsStarted] = CreateEvent(NULL,
                                                       FALSE,
                                                       FALSE,
                                                       NULL);
            ChildData->Event = WorkerEvents[ThreadsStarted];

            ThreadState->ThreadIndex = ThreadsStarted+1;
            if (fXMLOutput) {
                ThreadState->XMLThreadIndex = ThreadState->ThreadIndex;
            }

            /*
            Thread-specific directory message that associates directory to build thread.
            */
            if (fParallel && fThreadIndex && ThreadState->CompileDirDB) {
                char buffer[500];
                ThreadState->CompileDirDB;
                sprintf(buffer, "%d>BUILDMSG: Processing %s\n", ThreadState->ThreadIndex,
                    ThreadState->CompileDirDB->Name);
                fwrite(buffer, 1, strlen(buffer), LogFile);
            }

            if (fXMLOutput || fXMLFragment) {
                char buffer[1024];
                char* pszRelPath = (char*)XMLDir;
                if (TestPrefix(&pszRelPath, CurrentDirectory) && (*pszRelPath == '\\')) pszRelPath++;
                if (strlen(pszRelPath) == 0) {
                    pszRelPath = ".\\";
                }
                strcpy(buffer, "CMDLINE=\"");
                XMLEncodeBuiltInEntitiesCopy(ExecuteProgramCmdLine, buffer+strlen(buffer));
                sprintf(buffer + strlen(buffer), "\" ACTION=\"%s\" FULLPATH=\"%s\" RELPATH=\"%s\"", XMLAction, ThreadState->ChildCurrentDirectory, pszRelPath);
                if (fXMLOutput) {
                    XMLThreadInitBuffer(ThreadState);
                    XMLThreadOpenTag(ThreadState, "DIR", buffer);
                }
                if (fXMLFragment) {
                    XMLWriteDirFragmentFile(TRUE, pszRelPath, "<DIR %s/>", buffer);
                }
                dwStartTime = GetTickCount();
            }
            memset(&(ThreadState->BuildMetrics), 0, sizeof(BUILDMETRICS));

            WorkerThreads[ThreadsStarted] = CreateThread(NULL,
                                                         0,
                                (LPTHREAD_START_ROUTINE) ParallelChildStart,
                                                         ChildData,
                                                         0,
                                                         &ThreadId);
            if ((WorkerThreads[ThreadsStarted] == NULL) ||
                (WorkerEvents[ThreadsStarted] == NULL)) {
                FreeMem(&ChildData, MT_CHILDDATA);
                FreeMem(&ThreadState, MT_THREADSTATE);
                return(ERROR_NOT_ENOUGH_MEMORY);
            } else {
                WaitForSingleObject(WorkerEvents[ThreadsStarted],INFINITE);
                ++ThreadsStarted;
            }
        } else {
            //
            // Wait for a thread to complete before starting
            // the next one.
            //
            i = WaitForMultipleObjects(NumberProcesses,
                                       WorkerThreads,
                                       FALSE,
                                       INFINITE);
            CloseHandle(WorkerThreads[i]);
            ChildData->Event = WorkerEvents[i];
            ThreadState->ThreadIndex = i+1;
            if (fXMLOutput) {
                ThreadState->XMLThreadIndex = ThreadState->ThreadIndex;
            }

            /*
            Thread-specific directory message that associates directory to build thread.
            */
            if (fParallel && fThreadIndex && ThreadState->CompileDirDB) {
                char buffer[500];
                ThreadState->CompileDirDB;
                sprintf(buffer, "%d>BUILDMSG: Processing %s\n", ThreadState->ThreadIndex,
                    ThreadState->CompileDirDB->Name);
                fwrite(buffer, 1, strlen(buffer), LogFile);
            }

            if (fXMLOutput || fXMLFragment) {
                char buffer[1024];
                char* pszRelPath = (char*)XMLDir;
                if (TestPrefix(&pszRelPath, CurrentDirectory) && (*pszRelPath == '\\')) pszRelPath++;
                if (strlen(pszRelPath) == 0) {
                    pszRelPath = ".\\";
                }
                strcpy(buffer, "CMDLINE=\"");
                XMLEncodeBuiltInEntitiesCopy(ExecuteProgramCmdLine, buffer+strlen(buffer));
                sprintf(buffer + strlen(buffer), "\" ACTION=\"%s\" FULLPATH=\"%s\" RELPATH=\"%s\"", XMLAction, XMLDir, pszRelPath);
                if (fXMLOutput) {
                    XMLThreadInitBuffer(ThreadState);
                    XMLThreadOpenTag(ThreadState, "DIR", buffer);
                }
                if (fXMLFragment) {
                    XMLWriteDirFragmentFile(TRUE, pszRelPath, "<DIR %s/>", buffer);
                }
                dwStartTime = GetTickCount();
            }
            memset(&(ThreadState->BuildMetrics), 0, sizeof(BUILDMETRICS));

            WorkerThreads[i] = CreateThread(NULL,
                                            0,
                   (LPTHREAD_START_ROUTINE) ParallelChildStart,
                                            ChildData,
                                            0,
                                            &ThreadId);
            if (WorkerThreads[i] == NULL) {
                FreeMem(&ChildData, MT_CHILDDATA);
                FreeMem(&ThreadState, MT_THREADSTATE);
                return(ERROR_NOT_ENOUGH_MEMORY);
            } else {
                WaitForSingleObject(WorkerEvents[i],INFINITE);
            }
        }

        return(ERROR_SUCCESS);

    } else {

        //
        // Synchronous operation
        //
        StartCompileTime = 0L;
        ThreadState->ThreadIndex = 1;
        if (fXMLOutput) {
            // the synchronized directories are always processed by the main thread
            ThreadState->XMLThreadIndex = 0;
        }

        //
        // Disable child error popups in child processes.
        //

        if (fClean) {
            OldErrorMode = SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX );
            }

        /*
        Thread-specific directory message that associates directory to build thread.
        */
        if (fParallel && fThreadIndex && ThreadState->CompileDirDB) {
            char buffer[500];
            ThreadState->CompileDirDB;
            sprintf(buffer, "%d>BUILDMSG: Processing %s\n", ThreadState->ThreadIndex,
                ThreadState->CompileDirDB->Name);
            fwrite(buffer, 1, strlen(buffer), LogFile);
        }

        if (fXMLOutput || fXMLFragment) {
            char buffer[1024];
            char* pszRelPath = (char*)XMLDir;
            if (TestPrefix(&pszRelPath, CurrentDirectory) && (*pszRelPath == '\\')) pszRelPath++;
            if (strlen(pszRelPath) == 0) {
                pszRelPath = ".\\";
            }
            strcpy(buffer, "CMDLINE=\"");
            XMLEncodeBuiltInEntitiesCopy(ExecuteProgramCmdLine, buffer+strlen(buffer));
            sprintf(buffer + strlen(buffer), "\" ACTION=\"%s\" FULLPATH=\"%s\" RELPATH=\"%s\"", XMLAction, XMLDir, pszRelPath);
            if (fXMLOutput) {
                XMLThreadInitBuffer(ThreadState);
                XMLThreadOpenTag(ThreadState, "DIR", buffer);
            }
            if (fXMLFragment) {
                XMLWriteDirFragmentFile(TRUE, pszRelPath, "<DIR %s/>", buffer);
            }
            dwStartTime = GetTickCount();
        }
        memset(&(ThreadState->BuildMetrics), 0, sizeof(BUILDMETRICS));

        ThreadState->ChildOutput = PipeSpawn( ExecuteProgramCmdLine );
        if (fClean) {
            SetErrorMode( OldErrorMode );
            }

        rc = ERROR_SUCCESS;

        if (ThreadState->ChildOutput == NULL) {
            BuildError(
                "Exec of '%s' failed - errno = %d\n",
                ExecuteProgramCmdLine,
                errno);
            }
        else {
            FilterThread( ThreadState );

            if (StartCompileTime) {
                ElapsedCompileTime += time(NULL) - StartCompileTime;
                }

            rc = PipeSpawnClose( ThreadState->ChildOutput );
            if (rc == -1) {
                BuildError("Child Terminate failed - errno = %d\n", errno);
            }
            else
            if (rc) {
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
                if (fColorConsole)
                    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                BuildError("%s failed - rc = %d\n", ProgramName, rc);
                if (fColorConsole)
                    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), csbi.wAttributes);
                }
            }

        if (fXMLOutput || fXMLFragment) {
            XMLEnterCriticalSection();
            AddBuildMetrics(&PassMetrics, &ThreadState->BuildMetrics);

            if (fXMLOutput) {
                if (PXMLThreadStates[ThreadState->XMLThreadIndex]->fXMLInAction) {
                    // check for action errors or warnings
                    if (ThreadState->BuildMetrics.NumberActErrors || ThreadState->BuildMetrics.NumberActWarnings) {
                        sprintf(szXMLBuffer, "<ACTIONSUMMARY ");
                        if (ThreadState->BuildMetrics.NumberActErrors) {
                            sprintf(szXMLBuffer + strlen(szXMLBuffer), " ERRORS=\"%d\"", ThreadState->BuildMetrics.NumberActErrors);
                        }
                        if (ThreadState->BuildMetrics.NumberActWarnings) {
                            sprintf(szXMLBuffer + strlen(szXMLBuffer), " WARNINGS=\"%d\"", ThreadState->BuildMetrics.NumberActWarnings);
                        }
                        strcat(szXMLBuffer, "/>");
                        XMLThreadWrite(ThreadState, szXMLBuffer);
                    }
                    XMLThreadCloseTag(ThreadState, "ACTION");
                    PXMLThreadStates[ThreadState->XMLThreadIndex]->fXMLInAction = FALSE;
                }
            }
            sprintf(szXMLBuffer, "ELAPSED=\"%s\" ACTIONS=\"%d\" ", FormatElapsedTime(dwStartTime), ThreadState->BuildMetrics.NumberDirActions);
            strcat(szXMLBuffer, XMLBuildMetricsString(&(ThreadState->BuildMetrics)));

            if (fXMLOutput) {
                XMLThreadWrite(ThreadState, "<DIRSUMMARY %s/>", szXMLBuffer);
                XMLThreadCloseTag(ThreadState, "DIR");
                XMLThreadReleaseBuffer(ThreadState);
                XMLUpdateEndTag(FALSE);
            }
            if (fXMLFragment) {
                XMLWriteDirFragmentFile(
                    FALSE, 
                    strlen(ThreadState->ChildCurrentDirectory) == 0 ? ".\\" : ThreadState->ChildCurrentDirectory,
                    "<DIRSUMMARY %s/>", 
                    szXMLBuffer);
            }

            XMLLeaveCriticalSection();
        }

        if (ThreadState->IsStdErrTty) {
            RestoreConsoleMode();
        }

        FreeMem(&ThreadState, MT_THREADSTATE);
        return( rc );
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   WaitForParallelThreads
//
//  Synopsis:   Wait for all threads to finish before returning.
//
//----------------------------------------------------------------------------

VOID
WaitForParallelThreads(
    VOID
    )
{
    if (fParallel) {
        WaitForMultipleObjects(ThreadsStarted,
                               WorkerThreads,
                               TRUE,
                               INFINITE);
        while (ThreadsStarted) {
            CloseHandle(WorkerThreads[--ThreadsStarted]);
            CloseHandle(WorkerEvents[ThreadsStarted]);
        }
        if (WorkerThreads != NULL) {
            FreeMem((VOID **) &WorkerThreads, MT_THREADHANDLES);
            FreeMem((VOID **) &WorkerEvents, MT_EVENTHANDLES);
        }
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   ParallelChildStart
//
//  Synopsis:   Function that is run once for each thread.
//
//  Arguments:  [Data] -- Data given to CreateThread.
//
//----------------------------------------------------------------------------

DWORD
ParallelChildStart(
    PPARALLEL_CHILD Data
    )
{
    UINT OldErrorMode;
    UINT rc;
    DWORD dwStartTime = GetTickCount();

    //
    // Disable child error popups
    //
    if (fClean) {
        OldErrorMode = SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX );
    }
    Data->ThreadState->ChildOutput = PipeSpawn(Data->ExecuteProgramCmdLine);

    if (fClean) {
        SetErrorMode(OldErrorMode);
    }

    //
    // Poke the event to indicate that the child process has
    // started and it is ok for the main thread to change
    // the current directory.
    //
    SetEvent(Data->Event);

    if (Data->ThreadState->ChildOutput==NULL) {
        BuildError(
            "Exec of '%s' failed - errno = %d\n",
            ExecuteProgramCmdLine,
            errno);
    } else {
        FilterThread(Data->ThreadState);
        rc = PipeSpawnClose(Data->ThreadState->ChildOutput);
        if (rc == -1) {
            BuildError("Child terminate failed - errno = %d\n", errno);
        } else {
            if (rc) {
                BuildError("%s failed - rc = %d\n", Data->ExecuteProgramCmdLine, rc);
            }
        }
    }

    if (Data->ThreadState->IsStdErrTty) {
        RestoreConsoleMode();
    }

    if (fXMLOutput || fXMLFragment) {
        XMLEnterCriticalSection();
        AddBuildMetrics(&PassMetrics, &Data->ThreadState->BuildMetrics);

        if (fXMLOutput) {
            if (PXMLThreadStates[Data->ThreadState->XMLThreadIndex]->fXMLInAction) {
                // check for action errors or warnings
                if (Data->ThreadState->BuildMetrics.NumberActErrors || Data->ThreadState->BuildMetrics.NumberActWarnings) {
                    sprintf(szXMLBuffer, "<ACTIONSUMMARY ");
                    if (Data->ThreadState->BuildMetrics.NumberActErrors) {
                        sprintf(szXMLBuffer + strlen(szXMLBuffer), " ERRORS=\"%d\"", Data->ThreadState->BuildMetrics.NumberActErrors);
                    }
                    if (Data->ThreadState->BuildMetrics.NumberActWarnings) {
                        sprintf(szXMLBuffer + strlen(szXMLBuffer), " WARNINGS=\"%d\"", Data->ThreadState->BuildMetrics.NumberActWarnings);
                    }
                    strcat(szXMLBuffer, "/>");
                    XMLThreadWrite(Data->ThreadState, szXMLBuffer);
                }
                XMLThreadCloseTag(Data->ThreadState, "ACTION");
                PXMLThreadStates[Data->ThreadState->XMLThreadIndex]->fXMLInAction = FALSE;
            }
        }
        sprintf(szXMLBuffer, "ELAPSED=\"%s\" ACTIONS=\"%d\" ", FormatElapsedTime(dwStartTime), Data->ThreadState->BuildMetrics.NumberDirActions);
        strcat(szXMLBuffer, XMLBuildMetricsString(&(Data->ThreadState->BuildMetrics)));

        if (fXMLOutput) {
            XMLThreadWrite(Data->ThreadState, "<DIRSUMMARY %s/>", szXMLBuffer);
            XMLThreadCloseTag(Data->ThreadState, "DIR");
            XMLThreadReleaseBuffer(Data->ThreadState);
            XMLUpdateEndTag(FALSE);
        }
        if (fXMLFragment) {
            XMLWriteDirFragmentFile(
                FALSE, 
                strlen(Data->ThreadState->ChildCurrentDirectory) == 0 ? ".\\" : Data->ThreadState->ChildCurrentDirectory,
                "<DIRSUMMARY %s/>", 
                szXMLBuffer);
        }
        XMLLeaveCriticalSection();
    }

    FreeMem(&Data->ThreadState, MT_THREADSTATE);
    FreeMem(&Data, MT_CHILDDATA);
    return(rc);

}


//+---------------------------------------------------------------------------
//
//  Function:   ClearRows
//
//----------------------------------------------------------------------------

VOID
ClearRows(
    THREADSTATE *ThreadState,
    USHORT Top,
    USHORT NumRows,
    BYTE *Cell)
{
    COORD Coord;
    DWORD NumWritten;

    Coord.X = 0;
    Coord.Y = Top;

    FillConsoleOutputCharacter(
        GetStdHandle(STD_ERROR_HANDLE),
        Cell[0],
        ThreadState->cColTotal * NumRows,
        Coord,
        &NumWritten);
    FillConsoleOutputAttribute(
        GetStdHandle(STD_ERROR_HANDLE),
        (WORD) Cell[1],
        ThreadState->cColTotal * NumRows,
        Coord,
        &NumWritten);
}


//+---------------------------------------------------------------------------
//
//  Function:   GetScreenSize
//
//----------------------------------------------------------------------------

VOID
GetScreenSize(THREADSTATE *ThreadState)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi)) {
        ThreadState->cRowTotal = 25;
        ThreadState->cColTotal = 80;
    }
    else {
        ThreadState->cRowTotal = csbi.srWindow.Bottom + 1;
        ThreadState->cColTotal = csbi.dwSize.X;
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   GetCursorPosition
//
//----------------------------------------------------------------------------

VOID
GetCursorPosition(
    USHORT *pRow,
    USHORT *pCol,
    USHORT *pRowTop)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
    *pRow = csbi.dwCursorPosition.Y;
    *pCol = csbi.dwCursorPosition.X;
    if (pRowTop != NULL) {
        *pRowTop = csbi.srWindow.Top;
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   SetCursorPosition
//
//----------------------------------------------------------------------------

VOID
SetCursorPosition(USHORT Row, USHORT Col)
{
    COORD Coord;

    Coord.X = Col;
    Coord.Y = Row;
    SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), Coord);
}


//+---------------------------------------------------------------------------
//
//  Function:   WriteConsoleCells
//
//----------------------------------------------------------------------------

VOID
WriteConsoleCells(
    LPSTR String,
    USHORT StringLength,
    USHORT Row,
    USHORT Col,
    BYTE *Attribute)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD NumWritten;
    WORD OldAttribute;
    COORD StartCoord;

    //
    // Get current default attribute and save it.
    //

    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);

    OldAttribute = csbi.wAttributes;

    //
    // Set the default attribute to the passed parameter, along with
    // the cursor position.
    //

    if ((BYTE) OldAttribute != *Attribute) {
        SetConsoleTextAttribute(
            GetStdHandle(STD_ERROR_HANDLE),
            (WORD) *Attribute);
    }

    StartCoord.X = Col;
    StartCoord.Y = Row;
    SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), StartCoord);

    //
    // Write the passed string at the current cursor position, using the
    // new default attribute.
    //

    WriteFile(
        (HANDLE) STD_ERROR_HANDLE,
        String,
        StringLength,
        &NumWritten,
        NULL);

    //
    // Restore previous default attribute.
    //

    if ((BYTE) OldAttribute != *Attribute) {
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), OldAttribute);
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   MoveRectangleUp
//
//----------------------------------------------------------------------------

VOID
MoveRectangleUp (
    USHORT Top,
    USHORT Left,
    USHORT Bottom,
    USHORT Right,
    USHORT NumRow,
    BYTE  *FillCell)
{
    SMALL_RECT ScrollRectangle;
    COORD DestinationOrigin;
    CHAR_INFO Fill;

    ScrollRectangle.Left = Left;
    ScrollRectangle.Top = Top;
    ScrollRectangle.Right = Right;
    ScrollRectangle.Bottom = Bottom;
    DestinationOrigin.X = Left;
    DestinationOrigin.Y = Top - NumRow;
    Fill.Char.AsciiChar = FillCell[0];
    Fill.Attributes = (WORD) FillCell[1];

    ScrollConsoleScreenBuffer(
        GetStdHandle(STD_ERROR_HANDLE),
        &ScrollRectangle,
        NULL,
        DestinationOrigin,
        &Fill);
}


//+---------------------------------------------------------------------------
//
//  Function:   ReadConsoleCells
//
//----------------------------------------------------------------------------

VOID
ReadConsoleCells(
    BYTE *ScreenCell,
    USHORT cb,
    USHORT Row,
    USHORT Column)
{
    COORD BufferSize, BufferCoord;
    SMALL_RECT ReadRegion;
    CHAR_INFO CharInfo[1], *p;
    USHORT CountCells;

    CountCells = cb >> 1;
    assert(CountCells * sizeof(CHAR_INFO) <= sizeof(CharInfo));
    ReadRegion.Top = Row;
    ReadRegion.Left = Column;
    ReadRegion.Bottom = Row;
    ReadRegion.Right = Column + CountCells - 1;
    BufferSize.X = 1;
    BufferSize.Y = CountCells;
    BufferCoord.X = 0;
    BufferCoord.Y = 0;
    ReadConsoleOutput(
        GetStdHandle(STD_ERROR_HANDLE),
        CharInfo,
        BufferSize,
        BufferCoord,
        &ReadRegion);

    p = CharInfo;
    while (CountCells--) {
        *ScreenCell++ = p->Char.AsciiChar;
        *ScreenCell++ = (BYTE) p->Attributes;
        p++;
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   ClearLine
//
//----------------------------------------------------------------------------

VOID
ClearLine(VOID)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD Coord;
    DWORD   NumWritten;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);

    Coord.Y = csbi.dwCursorPosition.Y;
    Coord.X = csbi.dwCursorPosition.X = 0;
    FillConsoleOutputCharacter(
            GetStdHandle(STD_ERROR_HANDLE),
            ' ',
            csbi.dwSize.X,
            csbi.dwCursorPosition,
            &NumWritten);

    SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), Coord);
    fLineCleared = TRUE;
}


// PipeSpawn variables.  We can get away with one copy per thread.

__declspec(thread) HANDLE ProcHandle;
__declspec(thread) FILE *pstream;

//+---------------------------------------------------------------------------
//
//  Function:   PipeSpawn (similar to _popen)
//
//----------------------------------------------------------------------------

FILE *
PipeSpawn (
    const CHAR *cmdstring
    )
{
    int PipeHandle[2];
    HANDLE WriteHandle, ErrorHandle;
    STARTUPINFO StartupInfo;
    PROCESS_INFORMATION ProcessInformation;
    BOOL Status;
    char CmdLine[1024];

    if (cmdstring == NULL)
        return (NULL);

    // Open the pipe where we'll collect the output.

    _pipe(PipeHandle, 1024, _O_BINARY|_O_NOINHERIT);

    DuplicateHandle(GetCurrentProcess(),
                    (HANDLE)_get_osfhandle((LONG)PipeHandle[1]),
                    GetCurrentProcess(),
                    &WriteHandle,
                    0L,
                    TRUE,
                    DUPLICATE_SAME_ACCESS);

    DuplicateHandle(GetCurrentProcess(),
                    (HANDLE)_get_osfhandle((LONG)PipeHandle[1]),
                    GetCurrentProcess(),
                    &ErrorHandle,
                    0L,
                    TRUE,
                    DUPLICATE_SAME_ACCESS);

    _close(PipeHandle[1]);

    pstream = _fdopen(PipeHandle[0], "rb" );
    if (!pstream) {
        CloseHandle(WriteHandle);
        CloseHandle(ErrorHandle);
        _close(PipeHandle[0]);
        return(NULL);
    }

    strcpy(CmdLine, cmdexe);
    strcat(CmdLine, " /c ");
    strcat(CmdLine, cmdstring);

    memset(&StartupInfo, 0, sizeof(STARTUPINFO));
    StartupInfo.cb = sizeof(STARTUPINFO);

    StartupInfo.hStdOutput = WriteHandle;
    StartupInfo.hStdError = ErrorHandle;
    StartupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    StartupInfo.dwFlags = STARTF_USESTDHANDLES;

    memset(&ProcessInformation, 0, sizeof(PROCESS_INFORMATION));

    // And start the process.

    Status = CreateProcess(cmdexe, CmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInformation);

    CloseHandle(WriteHandle);
    CloseHandle(ErrorHandle);
    CloseHandle(ProcessInformation.hThread);

    if (!Status) {
        fclose(pstream);        // This will close the read handle
        pstream = NULL;
        ProcHandle = NULL;
    } else {
        ProcHandle = ProcessInformation.hProcess;
    }

    return(pstream);
}


//+---------------------------------------------------------------------------
//
//  Function:   PipeSpawnClose (similar to _pclose)
//
//----------------------------------------------------------------------------

DWORD
PipeSpawnClose (
    FILE *pstream
    )
{
    DWORD retval = 0;   /* return value (to caller) */

    if ( pstream == NULL) {
        return retval;
    }

    (void)fclose(pstream);

    if ( WaitForSingleObject(ProcHandle, (DWORD) -1L) == 0) {
        GetExitCodeProcess(ProcHandle, &retval);
    }
    CloseHandle(ProcHandle);

    return(retval);
}
