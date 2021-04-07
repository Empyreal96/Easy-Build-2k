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
        INT     2Eh                     ; invoke system service
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
        INT     2Eh                     ; invoke system service
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

STUBS_END
