;++
;
; Copyright (c) 1989  Microsoft Corporation
;
; Module Name:
;
;    sysstubs.asm
;
; Abstract:
;
;    This module implements the system service dispatch stub procedures.
;
; Author:
;
;    Shie-Lin Tzong (shielint) 6-Feb-1990
;
; Environment:
;
;    User or kernel mode.
;
; Revision History:
;
;--

include ks386.inc
include callconv.inc

.386
STUBS_BEGIN1 macro t
    TITLE t
endm
STUBS_BEGIN2 macro t
endm
STUBS_BEGIN3 macro t
_TEXT	SEGMENT DWORD PUBLIC 'CODE'
endm
STUBS_BEGIN4 macro t
endm
STUBS_BEGIN5 macro t
    align 4
endm
STUBS_BEGIN6 macro t
endm
STUBS_BEGIN7 macro t
endm
STUBS_BEGIN8 macro t
endm

STUBS_END    macro t
_TEXT ENDS
      end
endm

SYSSTUBS_ENTRY1 macro ServiceNumber, Name, NumArgs
cPublicProc _Zw&Name,NumArgs
.FPO ( 0, NumArgs, 0, 0, 0, 0 )
IFIDN <Name>, <SetHighWaitLowThread>
        int 2Bh
ELSE
IFIDN <Name>, <SetLowWaitHighThread>
        int 2Ch
ELSE
        mov     eax, ServiceNumber      ; (eax) = service number
        lea     edx, [esp]+4            ; (edx) -> arguments
        call    dword ptr fs:[TeWow32Reserved]
ENDIF
ENDIF
        stdRET  _Zw&Name
stdENDP _Zw&Name
endm

SYSSTUBS_ENTRY2 macro ServiceNumber, Name, NumArgs
endm
SYSSTUBS_ENTRY3 macro ServiceNumber, Name, NumArgs
endm
SYSSTUBS_ENTRY4 macro ServiceNumber, Name, NumArgs
endm
SYSSTUBS_ENTRY5 macro ServiceNumber, Name, NumArgs
endm
SYSSTUBS_ENTRY6 macro ServiceNumber, Name, NumArgs
endm
SYSSTUBS_ENTRY7 macro ServiceNumber, Name, NumArgs
endm
SYSSTUBS_ENTRY8 macro ServiceNumber, Name, NumArgs
endm


USRSTUBS_ENTRY1 macro ServiceNumber, Name, NumArgs
local   c
cPublicProc     _Zw&Name, NumArgs
PUBLICP _Nt&Name, NumArgs
LABELP  _Nt&Name, NumArgs
.FPO ( 0, NumArgs, 0, 0, 0, 0 )
IFIDN <Name>, <SetHighWaitLowThread>
        int 2Bh
ELSE
IFIDN <Name>, <SetLowWaitHighThread>
        int 2Ch
ELSE
        mov     eax, ServiceNumber      ; (eax) = service number
        lea     edx, [esp]+4            ; (edx) -> arguments
        call    dword ptr [fs:TeWow32Reserved]
ENDIF
ENDIF
        stdRET  _Zw&Name
stdENDP _Zw&Name
endm

USRSTUBS_ENTRY2 macro ServiceNumber, Name, NumArgs
endm
USRSTUBS_ENTRY3 macro ServiceNumber, Name, NumArgs
endm
USRSTUBS_ENTRY4 macro ServiceNumber, Name, NumArgs
endm
USRSTUBS_ENTRY5 macro ServiceNumber, Name, NumArgs
endm
USRSTUBS_ENTRY6 macro ServiceNumber, Name, NumArgs
endm
USRSTUBS_ENTRY7 macro ServiceNumber, Name, NumArgs
endm
USRSTUBS_ENTRY8 macro ServiceNumber, Name, NumArgs
endm

        STUBS_BEGIN1 <"System Service Stub Procedures">
        STUBS_BEGIN2 <"System Service Stub Procedures">
        STUBS_BEGIN3 <"System Service Stub Procedures">
        STUBS_BEGIN4 <"System Service Stub Procedures">
        STUBS_BEGIN5 <"System Service Stub Procedures">
        STUBS_BEGIN6 <"System Service Stub Procedures">
        STUBS_BEGIN7 <"System Service Stub Procedures">
        STUBS_BEGIN8 <"System Service Stub Procedures">
USRSTUBS_ENTRY1  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY2  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY3  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY4  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY5  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY6  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY7  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY8  0, Wow64CsrClientConnectToServer, 6 
USRSTUBS_ENTRY1  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY2  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY3  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY4  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY5  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY6  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY7  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY8  1, Wow64CsrNewThread, 0 
USRSTUBS_ENTRY1  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY2  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY3  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY4  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY5  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY6  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY7  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY8  2, Wow64CsrIdentifyAlertableThread, 0 
USRSTUBS_ENTRY1  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY2  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY3  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY4  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY5  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY6  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY7  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY8  3, Wow64CsrClientCallServer, 4 
USRSTUBS_ENTRY1  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY2  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY3  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY4  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY5  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY6  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY7  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY8  4, Wow64CsrAllocateCaptureBuffer, 2 
USRSTUBS_ENTRY1  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY2  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY3  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY4  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY5  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY6  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY7  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY8  5, Wow64CsrFreeCaptureBuffer, 1 
USRSTUBS_ENTRY1  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY2  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY3  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY4  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY5  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY6  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY7  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY8  6, Wow64CsrAllocateMessagePointer, 3 
USRSTUBS_ENTRY1  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY2  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY3  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY4  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY5  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY6  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY7  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY8  7, Wow64CsrCaptureMessageBuffer, 4 
USRSTUBS_ENTRY1  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY2  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY3  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY4  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY5  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY6  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY7  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY8  8, Wow64CsrCaptureMessageString, 5 
USRSTUBS_ENTRY1  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY2  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY3  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY4  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY5  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY6  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY7  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY8  9, Wow64CsrSetPriorityClass, 2 
USRSTUBS_ENTRY1  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY2  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY3  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY4  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY5  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY6  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY7  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY8  10, DbgUiConnectToDbg, 0 
USRSTUBS_ENTRY1  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY2  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY3  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY4  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY5  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY6  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY7  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY8  11, DbgUiWaitStateChange, 2 
USRSTUBS_ENTRY1  12, DbgUiContinue, 2 
USRSTUBS_ENTRY2  12, DbgUiContinue, 2 
USRSTUBS_ENTRY3  12, DbgUiContinue, 2 
USRSTUBS_ENTRY4  12, DbgUiContinue, 2 
USRSTUBS_ENTRY5  12, DbgUiContinue, 2 
USRSTUBS_ENTRY6  12, DbgUiContinue, 2 
USRSTUBS_ENTRY7  12, DbgUiContinue, 2 
USRSTUBS_ENTRY8  12, DbgUiContinue, 2 
USRSTUBS_ENTRY1  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY2  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY3  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY4  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY5  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY6  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY7  13, Wow64DebuggerCall, 3 
USRSTUBS_ENTRY8  13, Wow64DebuggerCall, 3 

STUBS_END
