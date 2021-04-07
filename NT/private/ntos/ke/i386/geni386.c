/*++

Copyright (c) 1989  Microsoft Corporation

Module Name:

    genoff.c

Abstract:

    This module implements a program which generates structure offset
    definitions for kernel structures that are accessed in assembly code.

Author:

    Bryan M. Willman (bryanwi) 16-Oct-90


To build:

    in ke\up do a "nmake UMAPPL=geni386"
    watch out for precompiled headers


Revision History:

    Forrest Foltz (forrestf) 24-Jan-1998

        Modified format to use new obj-based procedure.

--*/


#include "ki.h"
#pragma hdrstop

#include "nturtl.h"
#include "vdmntos.h"
#include "abios.h"

/*++

Copyright (c) 1998  Microsoft Corporation

Module Name:

    genxx.h

Abstract:

    This file contains macros (some of them destined for the M4 preprocessor)
    to aid in the generation of ks & hal header files.  This is used by
    ke\xxx\genxxx.c, as well as sdktools\genxx.

Author:

    Forrest C. Foltz (forrestf) 23-Jan-1998

Revision History:

--*/



//
// Structure element definitions.  
//

#define MAX_ELEMENT_NAME_LEN 127    // big enough for comments too
typedef struct _STRUC_ELEMENT {

//
// Flags is one or more SEF_xxx, defined below.
//

    UINT64 Flags;

//
// Note that Equate is used to store a pointer in the case of bitfield
// processing.
//

    UINT64 Equate;

//
// Name should be quite long, as it is used to hold comments as well.
//

    CHAR Name[ MAX_ELEMENT_NAME_LEN + 1 ];
} STRUC_ELEMENT, *PSTRUC_ELEMENT;

#define SEF_ENABLE_MASK     0x0000FF00      
#define SEF_HAL             0x00000100
#define SEF_KERNEL          0x00000200

#define SEF_INC_FORMAT_MASK 0x00010000
#define SEF_H_FORMAT        0x00000000
#define SEF_INC_FORMAT      0x00010000

//
// Types.  Note that SETMASK, CLRMASK has no effect on te BITFLD types.  BITFLD
// types have SEF_HAL | SEF_KERNEL set in the type.
//

#define SEF_TYPE_MASK       0x000000FF
#define SEF_EQUATE          0x00000000
#define SEF_EQUATE64        0x00000001
#define SEF_COMMENT         0x00000002      
#define SEF_STRING          0x00000003      // Equate is vararg to printf
#define SEF_BITFLD          0x00000004
#define SEF_BITALIAS        0x00000005
#define SEF_STRUCTURE       0x00000006
#define SEF_SETMASK         0x00000010      // Equate is the mask
#define SEF_CLRMASK         0x00000011      // Equate is the mask
#define SEF_END             0x00000012
#define SEF_START           0x00000013
#define SEF_PATH            0x00000014

//
// Note that BITFLD entries have per-entry hal|kernel flags
//


//
// Define architecture specific generation macros.
//

#define SEF_FLAGS 0
#define HAL SEF_HAL
#define KERNEL SEF_KERNEL

#ifndef ULONG_MAX
#define ULONG_MAX 0xFFFFFFFF
#endif

#ifdef _WIN64_
#define SEF_UINT SEF_EQUATE64
#else
#define SEF_UINT SEF_EQUATE
#endif

//
// genDef(Pc, KPCR, MinorVersion)
//
// -> #define PcMinorVersion 0x0
//

#define genDef(Prefix, Type, Member) \
    { SEF_EQUATE, OFFSET(Type, Member), #Prefix #Member },

//
// genAlt( PbAlignmentFixupCount, KPRCB, KeAlignmentFixupCount )
//
// -> #define PbAlignmentFixupCount 0x2f4
// 

#define genAlt(Name, Type, Member) \
    { SEF_EQUATE, OFFSET(Type, Member), #Name },

//
// genCom("This is a comment")
//
//    //
// -> // This is a comment
//    //
//

#define genCom(Comment) \
    { SEF_COMMENT, 0, Comment },

//
// genNam(PCR_MINOR_VERSION)
//
// -> #define PCR_MINOR_VERSION 0x1
//

#define genNam(Name) \
    { SEF_EQUATE, (ULONG)(Name), #Name },

//
// genNamUint(KSEG0_BASE)
//
// -> #define KSE0_BASE 0xffffffff80000000
//

#define genNamUint(Name) \
    { SEF_UINT, (UINT64)(Name), #Name },

//
// genVal(FirmwareFrameLength, FIRMWARE_FRAME_LENGTH)
//
// -> #define FirmwareFrameLength 0x250
//
// Note: if the value is 64-bit when _WIN64_ is enabled, use genValUint()
//

#define genVal(Name, Value) \
    { SEF_EQUATE, (ULONG)(Value), #Name },

//
// genValUint(KiPcr, KIPCR)
//
// -> #define KiPcr 0xe0000000ffffe000
//

#define genValUint(Name, Value) \
    { SEF_UINT, (UINT64)(Value), #Name },

//
// genSpc()
//
// ->
//

#define genSpc() \
    { SEF_STRING, 0, "\n" },

//
// genStr("    PCR equ ds:[0%lXH]\n", KIP0PCRADDRESS)
//
// ->     PCR equ ds:[0FFDFF000H]
//

#define genStr(String, Value) \
    { SEF_STRING, (ULONG_PTR)(Value), String },

//
// genTxt("ifdef NT_UP\n")
//
// -> ifdef NT_UP
//

#define genTxt(String) \
    { SEF_STRING, 0, String },

#define DisableInc( x ) \
    { SEF_CLRMASK, x, "" },

#define EnableInc( x ) \
    { SEF_SETMASK, x, "" },

#define MARKER_STRING "This is the genxx marker string."

//
// Source file can specify the _NTDRIVE\_NTROOT - relative output path.
// 'f' is the set of enable-flags that should be routed to this file.
// Use '0' if there is only a single output file.
//
// 'f' should also contain one of SEF_H_FORMAT or SEF_INC_FORMAT to
// indicate whether the generated file is in 'header file' or 'include file'
// format.
//

#define setPath( p, f ) \
    { SEF_PATH | f, 0, p },

//
// START_LIST defines the first element in ElementList.  This element contains
// a (possibly truncated) pointer to the ElementList array.  This is used to
// determine the fixup RA bias.
//

#define START_LIST \
    { SEF_START, (ULONG_PTR)ElementList, MARKER_STRING },

#define END_LIST \
    { SEF_END, 0, "" }

//
// Preprocessor assertion.  Do something here to make the compiler generate
// an error if x != y.
//

#define ASSERT_SAME( x, y )

//
// Macro to round Val up to the next Bnd boundary.  Bnd must be an integral
// power of two.
//

#define ROUND_UP( Val, Bnd ) \
    (((Val) + ((Bnd) - 1)) & ~((Bnd) - 1))

#ifndef OFFSET

//
// Define member offset computation macro.
//

#define OFFSET(type, field) ((ULONG_PTR)(&((type *)0)->field))

#endif

//
// Following are some M4 macros to help with bitfields.  
//

#ifndef SKIP_M4

//
// First, define the makezeros(n) macro that will generate a string with
// n pairs of ',0'.  This is a recursively defined macro.
//



//
// Define a concatenation macro.
//



//
// The following example bitfield declaration uses HARDWARE_PTE as an
// example, which is declared (for alpha) as follows:
//
// typedef struct _HARDWARE_PTE {
//     ULONG Valid: 1;
//     ULONG Owner: 1;
//     ULONG Dirty: 1;
//     ULONG reserved: 1;
//     ULONG Global: 1;
//     ULONG GranularityHint: 2;
//     ULONG Write: 1;
//     ULONG CopyOnWrite: 1;
//     ULONG PageFrameNumber: 23;
// } HARDWARE_PTE, *PHARDWARE_PTE;
//
//
// // First, startBitStruc() is invoked with the structure name.
//
// startBitStruc( HARDWARE_PTE, SEF_HAL | SEF_KERNEL )
//
// //
// // Now, suppose we wanted to expose seven of the fields in an assembly
// // include file:
// //
//
// genBitField( Valid, PTE_VALID )
// genBitField( Owner, PTE_OWNER )
// genBitField( Dirty, PTE_DIRTY )
// genBitField( reserved )
// genBitField( Global, PTE_GLOBAL )
// genBitField( GranularityHint )
// genBitField( Write, PTE_WRITE )
// genBitField( CopyOnWrite, PTE_COPYONWRITE )
// genBitField( PageFrameNumber, PTE_PFN )
//
// Note that fields that are not used (in this case 'reserved' and
// 'GranularityHint') must still appear in the list.
//
// The above will generate a bunch of static, initialized copies of HARDWARE_PTE
// like so:
//
// HARDWARE_PTE HARDWARE_PTE_Valid = {
//     0xFFFFFFFF };
//
// HARDWARE_PTE HARDWARE_PTE_Owner = {
//     0,   // Valid
//     0xFFFFFFFF };
//
// HARDWARE_PTE HARDWARE_PTE_Dirty = {
//     0,   // Valid
//     0,   // Owner
//     0xFFFFFFFF };
//
// HARDWARE_PTE HARDWARE_PTE_Global = {
//     0,   // Valid
//     0,   // Owner
//     0,   // Dirty
//     0,   // reserved
//     0xFFFFFFFF };
//
// HARDWARE_PTE HARDWARE_PTE_Write = {
//     0,   // Valid
//     0,   // Owner
//     0,   // Dirty
//     0,   // reserved (skipped)
//     0,   // Global
//     0xFFFFFFFF };
//
// HARDWARE_PTE HARDWARE_PTE_CopyOnWrite = {
//     0,   // Valid
//     0,   // Owner
//     0,   // Dirty
//     0,   // reserved (skipped)
//     0,   // Global
//     0,   // GranularityHint (skipped)
//     0xFFFFFFFF };
//
// HARDWARE_PTE HARDWARE_PTE_PageFrameNumber = {
//     0,   // Valid
//     0,   // Owner
//     0,   // Dirty
//     0,   // reserved (skipped)
//     0,   // Global
//     0,   // GranularityHint (skipped)
//     0,   // CopyOnWrite
//     0xFFFFFFFF };
//
// Then, as part of processing the END_LIST macro, these structures are
// generated:
//
// { SEF_BITFLD, &HARDWARE_PTE_Valid,           "PTE_VALID" },
// { SEF_BITFLD, &HARDWARE_PTE_Owner,           "PTE_OWNER" },
// { SEF_BITFLD, &HARDWARE_PTE_Dirty,           "PTE_DIRTY" },
// { SEF_BITFLD, &HARDWARE_PTE_Global,          "PTE_GLOBAL" },
// { SEF_BITFLD, &HARDWARE_PTE_Write,           "PTE_WRITE" },
// { SEF_BITFLD, &HARDWARE_PTE_CopyOnWrite,     "PTE_COPYONWRITE" },
// { SEF_BITFLD, &HARDWARE_PTE_PageFrameNumber, "PTE_PFN" },
// { SEF_END,    0,                             "" }
//
//
// ... and that's what gets compiled by the target compiler into the .obj.
// Now, the final stage: genxx.exe is run against this target .obj, and
// would generate the following:
//
// #define PTE_VALID_MASK 0x1
// #define PTE_VALID 0x0
// #define PTE_OWNER_MASK 0x2
// #define PTE_OWNER 0x1
// #define PTE_DIRTY_MASK 0x4
// #define PTE_DIRTY 0x2
// #define PTE_GLOBAL_MASK 0x10
// #define PTE_GLOBAL 0x4
// #define PTE_WRITE_MASK 0x80
// #define PTE_WRITE 0x7
// #define PTE_COPYONWRITE_MASK 0x100
// #define PTE_COPYONWRITE 0x8
// #define PTE_PFN_MASK 0xfffffe00
// #define PTE_PFN 0x9
//

//
// BITFIELD_STRUCS accumulates array element initializations.  END_LIST will
// dump these into the definition array.
// 



//
// startBitStruc( <strucname>, <whichfile> )
// sets BIT_STRUC_NAME = <strucname> and resets the ZERO_FIELDS count to 0.
// It also sets the WHICH_FILE macro.
//



//
// genBitField( <fldname>, <generatedname> ) declares a structure of type
// <strucname> and initializes the <fldname> bitfield within it.
//
// Note that I used "cma" instead of an actual comma, this gets changed to
// a comma by END_LIST, below.  If I were more proficient with M4 I would know
// how to get around this.
//





//
// END_LIST dumps the array initializers accumulated by , after
// replacing each 'cma' with an actual comma.
//



#endif  // SKIP_M4



#define KS386 KERNEL
#define HAL386 HAL

STRUC_ELEMENT ElementList[] = {

    START_LIST

  EnableInc(KS386)

    #include "genxx.inc"

    //
    // Generate architecture dependent definitions.
    //

    genCom("Apc Record Structure Offset Definitions")

    genDef(Ar, KAPC_RECORD, NormalRoutine)
    genDef(Ar, KAPC_RECORD, NormalContext)
    genDef(Ar, KAPC_RECORD, SystemArgument1)
    genDef(Ar, KAPC_RECORD, SystemArgument2)
    genVal(ApcRecordLength, sizeof(KAPC_RECORD))
    genSpc()

  EnableInc(HAL386)
    genCom("Processor Control Registers Structure Offset Definitions")

    genNam( KI_BEGIN_KERNEL_RESERVED )
    genTxt("ifdef NT_UP\n")
    genStr("    P0PCRADDRESS equ 0%lXH\n", KIP0PCRADDRESS)
    genStr("    PCR equ ds:[0%lXH]\n", KIP0PCRADDRESS)
    genTxt("else\n")
    genTxt("    PCR equ fs:\n")
    genTxt("endif\n\n")

    genAlt(PcExceptionList, KPCR,  NtTib.ExceptionList)
    genAlt(PcInitialStack, KPCR, NtTib.StackBase)
    genAlt(PcStackLimit, KPCR, NtTib.StackLimit)
    genDef(Pc, KPCR, SelfPcr)
    genDef(Pc, KPCR, Prcb)
    genAlt(PcTeb, KPCR, NtTib.Self)
    genDef(Pc, KPCR, Irql)
    genDef(Pc, KPCR, IRR)
    genDef(Pc, KPCR, IrrActive)
    genDef(Pc, KPCR, IDR)
    genAlt(PcIdt, KPCR, IDT)
    genAlt(PcGdt, KPCR, GDT)
    genAlt(PcTss, KPCR, TSS)
    genDef(Pc, KPCR, DebugActive)
    genDef(Pc, KPCR, Number)
    genDef(Pc, KPCR, VdmAlert)
    genDef(Pc, KPCR, SetMember)
    genDef(Pc, KPCR, StallScaleFactor)
    genAlt(PcHal, KPCR, HalReserved)
  DisableInc (HAL386)
    genDef(Pc, KPCR, PrcbData)
    genVal(ProcessorControlRegisterLength, sizeof(KPCR))
    genAlt(TebPeb, TEB, ProcessEnvironmentBlock)
    genDef(Peb, PEB, BeingDebugged)
    genDef(Peb, PEB, KernelCallbackTable)

  EnableInc (HAL386)
    genCom("Defines for user shared data")

    genVal(USER_SHARED_DATA, KI_USER_SHARED_DATA)
    genNam(MM_SHARED_USER_DATA_VA)
    genStr("USERDATA equ ds:[0%lXH]\n", KI_USER_SHARED_DATA)
    genDef(Us, KUSER_SHARED_DATA, TickCountLow)
    genDef(Us, KUSER_SHARED_DATA, TickCountMultiplier)
    genDef(Us, KUSER_SHARED_DATA, InterruptTime)
    genDef(Us, KUSER_SHARED_DATA, SystemTime)

    genCom("Tss Structure Offset Definitions")

    genDef(Tss, KTSS, Esp0)
    genDef(Tss, KTSS, CR3)
    genDef(Tss, KTSS, IoMapBase)
    genDef(Tss, KTSS, IoMaps)
    genVal(TssLength, sizeof(KTSS))
  DisableInc (HAL386)

  EnableInc (HAL386)
    genCom("Gdt Descriptor Offset Definitions")

    genNam(KGDT_R3_DATA)
    genNam(KGDT_R3_CODE)
    genNam(KGDT_R0_CODE)
    genNam(KGDT_R0_DATA)
    genNam(KGDT_R0_PCR)
    genNam(KGDT_STACK16)
    genNam(KGDT_CODE16)
    genNam(KGDT_TSS)
  DisableInc (HAL386)
    genNam(KGDT_R3_TEB)
    genNam(KGDT_DF_TSS)
    genNam(KGDT_NMI_TSS)
    genNam(KGDT_LDT)

  EnableInc (HAL386)
    genCom("GdtEntry Offset Definitions")

    genDef(Kgdt, KGDTENTRY, BaseLow)
    genAlt(KgdtBaseMid, KGDTENTRY, HighWord.Bytes.BaseMid)
    genAlt(KgdtBaseHi, KGDTENTRY, HighWord.Bytes.BaseHi)
    genAlt(KgdtLimitHi, KGDTENTRY, HighWord.Bytes.Flags2)
    genDef(Kgdt, KGDTENTRY, LimitLow)
    genSpc()

    //
    // Processor block structure definitions.
    //

    genCom("Processor Block Structure Offset Definitions")

    genDef(Pb, KPRCB, CurrentThread)
    genDef(Pb, KPRCB, NextThread)
    genDef(Pb, KPRCB, IdleThread)
    genDef(Pb, KPRCB, Number)
    genDef(Pb, KPRCB, SetMember)
    genDef(Pb, KPRCB, CpuID)
    genDef(Pb, KPRCB, CpuType)
    genDef(Pb, KPRCB, CpuStep)
    genDef(Pb, KPRCB, HalReserved)
    genDef(Pb, KPRCB, ProcessorState)
    genDef(Pb, KPRCB, LockQueue)

  DisableInc (HAL386)

    genDef(Pb, KPRCB, NpxThread)
    genDef(Pb, KPRCB, InterruptCount)
    genDef(Pb, KPRCB, KernelTime)
    genDef(Pb, KPRCB, UserTime)
    genDef(Pb, KPRCB, DpcTime)
    genDef(Pb, KPRCB, InterruptTime)
    genDef(Pb, KPRCB, ApcBypassCount)
    genDef(Pb, KPRCB, DpcBypassCount)
    genDef(Pb, KPRCB, AdjustDpcThreshold)
    genDef(Pb, KPRCB, DebugDpcTime)
    genDef(Pb, KPRCB, ThreadStartCount)
    genAlt(PbAlignmentFixupCount, KPRCB, KeAlignmentFixupCount)
    genAlt(PbContextSwitches, KPRCB, KeContextSwitches)
    genAlt(PbDcacheFlushCount, KPRCB, KeDcacheFlushCount)
    genAlt(PbExceptionDispatchCount, KPRCB, KeExceptionDispatchCount)
    genAlt(PbFirstLevelTbFills, KPRCB, KeFirstLevelTbFills)
    genAlt(PbFloatingEmulationCount, KPRCB, KeFloatingEmulationCount)
    genAlt(PbIcacheFlushCount, KPRCB, KeIcacheFlushCount)
    genAlt(PbSecondLevelTbFills, KPRCB, KeSecondLevelTbFills)
    genAlt(PbSystemCalls, KPRCB, KeSystemCalls)
    genDef(Pb, KPRCB, CurrentPacket)
    genDef(Pb, KPRCB, TargetSet)
    genDef(Pb, KPRCB, WorkerRoutine)
    genDef(Pb, KPRCB, IpiFrozen)
    genDef(Pb, KPRCB, RequestSummary)
    genDef(Pb, KPRCB, SignalDone)
    genDef(Pb, KPRCB, IpiFrame)
    genDef(Pb, KPRCB, DpcInterruptRequested)
    genDef(Pb, KPRCB, MaximumDpcQueueDepth)
    genDef(Pb, KPRCB, MinimumDpcRate)
    genDef(Pb, KPRCB, DpcListHead)
    genDef(Pb, KPRCB, DpcQueueDepth)
    genDef(Pb, KPRCB, DpcRoutineActive)
    genDef(Pb, KPRCB, DpcCount)
    genDef(Pb, KPRCB, DpcLastCount)
    genDef(Pb, KPRCB, DpcRequestRate)
    genDef(Pb, KPRCB, DpcStack)
    genDef(Pb, KPRCB, DpcLock)
    genDef(Pb, KPRCB, SkipTick)
    genDef(Pb, KPRCB, QuantumEnd)
    genDef(Pb, KPRCB, PowerState)
    genVal(ProcessorBlockLength, ((sizeof(KPRCB) + 15) & ~15))

    //
    // Prcb power state
    //

    genCom("Processor Power State Offset Definitions")
    genDef(Pp, PROCESSOR_POWER_STATE, IdleFunction)

    //
    // Interprocessor command definitions.
    //

    genCom("Immediate Interprocessor Command Definitions")

    genVal(IPI_APC, IPI_APC)
    genVal(IPI_DPC, IPI_DPC)
    genVal(IPI_FREEZE, IPI_FREEZE)
    genVal(IPI_PACKET_READY, IPI_PACKET_READY)
    genVal(IPI_SYNCH_REQUEST, IPI_SYNCH_REQUEST)

    genCom("Thread Environment Block Structure Offset Definitions")

    genAlt(TbExceptionList, TEB, NtTib.ExceptionList)
    genAlt(TbStackBase, TEB, NtTib.StackBase)
    genAlt(TbStackLimit, TEB, NtTib.StackLimit)
    genDef(Tb, TEB, EnvironmentPointer)
    genAlt(TbVersion, TEB, NtTib.Version)
    genAlt(TbFiberData, TEB, NtTib.FiberData)
    genAlt(TbArbitraryUserPointer, TEB, NtTib.ArbitraryUserPointer)
    genDef(Tb, TEB, ClientId)
    genDef(Tb, TEB, ThreadLocalStoragePointer)
    genDef(Tb, TEB, CountOfOwnedCriticalSections)
    genDef(Tb, TEB, SystemReserved1)
    genDef(Tb, TEB, Vdm)
    genDef(Tb, TEB, CsrClientThread)
    genDef(Tb, TEB, GdiThreadLocalInfo)
    genDef(Tb, TEB, glDispatchTable)
    genDef(Tb, TEB, glSectionInfo)
    genDef(Tb, TEB, glSection)
    genDef(Tb, TEB, glTable)
    genDef(Tb, TEB, glCurrentRC)
    genDef(Tb, TEB, glContext)
    genDef(Tb, TEB, WOW32Reserved)
    genDef(Tb, TEB, ExceptionCode)
    genDef(Tb, TEB, DeallocationStack)
    genDef(Tb, TEB, GdiBatchCount)

  EnableInc (HAL386)
    genCom("Time Fields (TIME_FIELDS) Structure Offset Definitions")
    genDef(Tf, TIME_FIELDS, Second)
    genDef(Tf, TIME_FIELDS, Minute)
    genDef(Tf, TIME_FIELDS, Hour)
    genDef(Tf, TIME_FIELDS, Weekday)
    genDef(Tf, TIME_FIELDS, Day)
    genDef(Tf, TIME_FIELDS, Month)
    genDef(Tf, TIME_FIELDS, Year)
    genDef(Tf, TIME_FIELDS, Milliseconds)
    genSpc()
  DisableInc (HAL386)

  EnableInc (HAL386)
    genCom("constants for system irql and IDT vector conversion")

    genNam(MAXIMUM_IDTVECTOR)
    genNam(MAXIMUM_PRIMARY_VECTOR)
    genNam(PRIMARY_VECTOR_BASE)
    genNam(RPL_MASK)
    genNam(MODE_MASK)

    genCom("Flags in the CR0 register")

    genNam(CR0_PG)
    genNam(CR0_ET)
    genNam(CR0_TS)
    genNam(CR0_EM)
    genNam(CR0_MP)
    genNam(CR0_PE)
    genNam(CR0_CD)
    genNam(CR0_NW)
    genNam(CR0_AM)
    genNam(CR0_WP)
    genNam(CR0_NE)

    genCom("Flags in the CR4 register")

    genNam(CR4_VME)
    genNam(CR4_PVI)
    genNam(CR4_TSD)
    genNam(CR4_DE)
    genNam(CR4_PSE)
    genNam(CR4_PAE)
    genNam(CR4_MCE)
    genNam(CR4_PGE)
    genNam(CR4_FXSR)
    genNam(CR4_XMMEXCPT)

    genCom("Miscellaneous Definitions")

    genNam(MAXIMUM_PROCESSORS)
    genNam(INITIAL_STALL_COUNT)
    genNam(IRQL_NOT_GREATER_OR_EQUAL)
    genNam(IRQL_NOT_LESS_OR_EQUAL)
    genNam(MUTEX_ALREADY_OWNED)
    genNam(THREAD_NOT_MUTEX_OWNER)
    genNam(SPIN_LOCK_ALREADY_OWNED)
    genNam(SPIN_LOCK_NOT_OWNED)
  DisableInc (HAL386)
    genNam(BASE_PRIORITY_THRESHOLD)
    genNam(EVENT_PAIR_INCREMENT)
    genNam(LOW_REALTIME_PRIORITY)
    genVal(BlackHole, 0xffffa000)
    genNam(KERNEL_LARGE_STACK_COMMIT)
    genNam(KERNEL_STACK_SIZE)
    genNam(DOUBLE_FAULT_STACK_SIZE)
    genNam(EFLAG_SELECT)
    genNam(BREAKPOINT_BREAK )
    genNam(IPI_FREEZE)
    genNam(CLOCK_QUANTUM_DECREMENT)
    genNam(READY_SKIP_QUANTUM)
    genNam(THREAD_QUANTUM)
    genNam(WAIT_QUANTUM_DECREMENT)
    genNam(ROUND_TRIP_DECREMENT_COUNT)

    //
    // Print trap frame offsets relative to sp.
    //

  EnableInc (HAL386)
    genCom("Trap Frame Offset Definitions and Length")

    genDef(Ts, KTRAP_FRAME, ExceptionList)
    genDef(Ts, KTRAP_FRAME, PreviousPreviousMode)
    genDef(Ts, KTRAP_FRAME, SegGs)
    genDef(Ts, KTRAP_FRAME, SegFs)
    genDef(Ts, KTRAP_FRAME, SegEs)
    genDef(Ts, KTRAP_FRAME, SegDs)
    genDef(Ts, KTRAP_FRAME, Edi)
    genDef(Ts, KTRAP_FRAME, Esi)
    genDef(Ts, KTRAP_FRAME, Ebp)
    genDef(Ts, KTRAP_FRAME, Ebx)
    genDef(Ts, KTRAP_FRAME, Edx)
    genDef(Ts, KTRAP_FRAME, Ecx)
    genDef(Ts, KTRAP_FRAME, Eax)
    genDef(Ts, KTRAP_FRAME, ErrCode)
    genDef(Ts, KTRAP_FRAME, Eip)
    genDef(Ts, KTRAP_FRAME, SegCs)
    genAlt(TsEflags, KTRAP_FRAME, EFlags)
    genDef(Ts, KTRAP_FRAME, HardwareEsp)
    genDef(Ts, KTRAP_FRAME, HardwareSegSs)
    genDef(Ts, KTRAP_FRAME, TempSegCs)
    genDef(Ts, KTRAP_FRAME, TempEsp)
    genDef(Ts, KTRAP_FRAME, DbgEbp)
    genDef(Ts, KTRAP_FRAME, DbgEip)
    genDef(Ts, KTRAP_FRAME, DbgArgMark)
    genDef(Ts, KTRAP_FRAME, DbgArgPointer)
    genDef(Ts, KTRAP_FRAME, Dr0)
    genDef(Ts, KTRAP_FRAME, Dr1)
    genDef(Ts, KTRAP_FRAME, Dr2)
    genDef(Ts, KTRAP_FRAME, Dr3)
    genDef(Ts, KTRAP_FRAME, Dr6)
    genDef(Ts, KTRAP_FRAME, Dr7)
    genDef(Ts, KTRAP_FRAME, V86Es)
    genDef(Ts, KTRAP_FRAME, V86Ds)
    genDef(Ts, KTRAP_FRAME, V86Fs)
    genDef(Ts, KTRAP_FRAME, V86Gs)
    genNam(KTRAP_FRAME_LENGTH)
    genNam(KTRAP_FRAME_ALIGN)
    genNam(FRAME_EDITED)
    genNam(EFLAGS_ALIGN_CHECK)
    genNam(EFLAGS_V86_MASK)
    genNam(EFLAGS_INTERRUPT_MASK)
    genNam(EFLAGS_VIF)
    genNam(EFLAGS_VIP)
    genNam(EFLAGS_USER_SANITIZE)

    genCom("Context Frame Offset and Flag Definitions")

    genNam(CONTEXT_FULL)
    genNam(CONTEXT_DEBUG_REGISTERS)
    genNam(CONTEXT_CONTROL)
    genNam(CONTEXT_FLOATING_POINT)
    genNam(CONTEXT_INTEGER)
    genNam(CONTEXT_SEGMENTS)
    genSpc()

    //
    // Print context frame offsets relative to sp.
    //

    genDef(Cs, CONTEXT, ContextFlags)
    genDef(Cs, CONTEXT, FloatSave)
    genDef(Cs, CONTEXT, SegGs)
    genDef(Cs, CONTEXT, SegFs)
    genDef(Cs, CONTEXT, SegEs)
    genDef(Cs, CONTEXT, SegDs)
    genDef(Cs, CONTEXT, Edi)
    genDef(Cs, CONTEXT, Esi)
    genDef(Cs, CONTEXT, Ebp)
    genDef(Cs, CONTEXT, Ebx)
    genDef(Cs, CONTEXT, Edx)
    genDef(Cs, CONTEXT, Ecx)
    genDef(Cs, CONTEXT, Eax)
    genDef(Cs, CONTEXT, Eip)
    genDef(Cs, CONTEXT, SegCs)
    genAlt(CsEflags, CONTEXT, EFlags)
    genDef(Cs, CONTEXT, Esp)
    genDef(Cs, CONTEXT, SegSs)
    genDef(Cs, CONTEXT, Dr0)
    genDef(Cs, CONTEXT, Dr1)
    genDef(Cs, CONTEXT, Dr2)
    genDef(Cs, CONTEXT, Dr3)
    genDef(Cs, CONTEXT, Dr6)
    genDef(Cs, CONTEXT, Dr7)
    genVal(ContextFrameLength, ROUND_UP(sizeof(CONTEXT), 16))
    genNam(DR6_LEGAL)
    genNam(DR7_LEGAL)
    genNam(DR7_ACTIVE)

    //
    // Print Registration Record Offsets relative to base
    //

    genDef(Err, EXCEPTION_REGISTRATION_RECORD, Handler)
    genDef(Err, EXCEPTION_REGISTRATION_RECORD, Next)

    //
    // Print floating point field offsets relative to Context.FloatSave
    //

    genCom("Floating save area field offset definitions")

    genDef(Fp, FLOATING_SAVE_AREA, ControlWord)
    genDef(Fp, FLOATING_SAVE_AREA, StatusWord)
    genDef(Fp, FLOATING_SAVE_AREA, TagWord)
    genDef(Fp, FLOATING_SAVE_AREA, ErrorOffset)
    genDef(Fp, FLOATING_SAVE_AREA, ErrorSelector)
    genDef(Fp, FLOATING_SAVE_AREA, DataOffset)
    genDef(Fp, FLOATING_SAVE_AREA, DataSelector)
    genDef(Fp, FLOATING_SAVE_AREA, RegisterArea)
    genDef(FpCtxt, FLOATING_SAVE_AREA, Cr0NpxState)

    //
    // Print floating point field offsets relative to Kernel Stack
    // The floating save area on kernel stack is bigger for FXSR mode
    //

    genCom("FX Floating save area field offset definitions")

    genDef(Fx, FXSAVE_FORMAT, ControlWord)
    genDef(Fx, FXSAVE_FORMAT, StatusWord)
    genDef(Fx, FXSAVE_FORMAT, TagWord)
    genDef(Fx, FXSAVE_FORMAT, ErrorOpcode)
    genDef(Fx, FXSAVE_FORMAT, ErrorOffset)
    genDef(Fx, FXSAVE_FORMAT, ErrorSelector)
    genDef(Fx, FXSAVE_FORMAT, DataOffset)
    genDef(Fx, FXSAVE_FORMAT, DataSelector)
    genDef(Fx, FXSAVE_FORMAT, MXCsr)
    genDef(FxFp, FXSAVE_FORMAT, RegisterArea)
    genDef(Fp, FX_SAVE_AREA,  NpxSavedCpu)
    genDef(Fp, FX_SAVE_AREA,  Cr0NpxState)

    genSpc()
    genVal(NPX_FRAME_LENGTH, sizeof(FX_SAVE_AREA))

    //
    // Processor State Frame offsets relative to base
    //

    genCom("Processor State Frame Offset Definitions\n")

    genDef(Ps, KPROCESSOR_STATE, ContextFrame)
    genDef(Ps, KPROCESSOR_STATE, SpecialRegisters)
    genDef(Sr, KSPECIAL_REGISTERS, Cr0)
    genDef(Sr, KSPECIAL_REGISTERS, Cr2)
    genDef(Sr, KSPECIAL_REGISTERS, Cr3)
    genDef(Sr, KSPECIAL_REGISTERS, Cr4)
    genDef(Sr, KSPECIAL_REGISTERS, KernelDr0)
    genDef(Sr, KSPECIAL_REGISTERS, KernelDr1)
    genDef(Sr, KSPECIAL_REGISTERS, KernelDr2)
    genDef(Sr, KSPECIAL_REGISTERS, KernelDr3)
    genDef(Sr, KSPECIAL_REGISTERS, KernelDr6)
    genDef(Sr, KSPECIAL_REGISTERS, KernelDr7)
    genAlt(SrGdtr, KSPECIAL_REGISTERS, Gdtr.Limit)

    genAlt(SrIdtr, KSPECIAL_REGISTERS, Idtr.Limit)
    genDef(Sr, KSPECIAL_REGISTERS, Tr)
    genDef(Sr, KSPECIAL_REGISTERS, Ldtr)
    genVal(ProcessorStateLength, ROUND_UP(sizeof(KPROCESSOR_STATE), 15))
  DisableInc (HAL386)

    //
    // E Process fields relative to base
    //

    genCom("EPROCESS")

    genDef(Ep, EPROCESS, DebugPort)
    genDef(Ep, EPROCESS, VdmObjects)

    //
    // E Resource fields relative to base
    //

    genCom("NTDDK Resource")

    genDef(Rs, NTDDK_ERESOURCE, OwnerThreads)
    genDef(Rs, NTDDK_ERESOURCE, OwnerCounts)
    genDef(Rs, NTDDK_ERESOURCE, TableSize)
    genDef(Rs, NTDDK_ERESOURCE, ActiveCount)
    genDef(Rs, NTDDK_ERESOURCE, Flag)
    genDef(Rs, NTDDK_ERESOURCE, InitialOwnerThreads)
    genVal(RsOwnedExclusive, ResourceOwnedExclusive)

    //
    // Define machine type (temporarily)
    //

  EnableInc (HAL386)

    genCom("Machine type definitions (Temporarily)")

    genNam(MACHINE_TYPE_ISA)
    genNam(MACHINE_TYPE_EISA)
    genNam(MACHINE_TYPE_MCA)

  DisableInc (HAL386)

    genCom("KeFeatureBits defines")

    genNam(KF_V86_VIS)
    genNam(KF_RDTSC)
    genNam(KF_CR4)
    genNam(KF_GLOBAL_PAGE)
    genNam(KF_LARGE_PAGE)
    genNam(KF_CMPXCHG8B)
    genNam(KF_FAST_SYSCALL)

  EnableInc (HAL386)
    genCom("LoaderParameterBlock offsets relative to base")

    genDef(Lpb, LOADER_PARAMETER_BLOCK, LoadOrderListHead)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, MemoryDescriptorListHead)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, KernelStack)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, Prcb)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, Process)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, Thread)
    genAlt(LpbI386, LOADER_PARAMETER_BLOCK, u.I386)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, RegistryLength)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, RegistryBase)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, ConfigurationRoot)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, ArcBootDeviceName)
    genDef(Lpb, LOADER_PARAMETER_BLOCK, ArcHalDeviceName)
  DisableInc (HAL386)

    genNam(PAGE_SIZE)

    //
    // Define the VDM instruction emulation count indexes
    //

    genCom("VDM equates.")

    genNam(VDM_INDEX_Invalid)
    genNam(VDM_INDEX_0F)
    genNam(VDM_INDEX_ESPrefix)
    genNam(VDM_INDEX_CSPrefix)
    genNam(VDM_INDEX_SSPrefix)
    genNam(VDM_INDEX_DSPrefix)
    genNam(VDM_INDEX_FSPrefix)
    genNam(VDM_INDEX_GSPrefix)
    genNam(VDM_INDEX_OPER32Prefix)
    genNam(VDM_INDEX_ADDR32Prefix)
    genNam(VDM_INDEX_INSB)
    genNam(VDM_INDEX_INSW)
    genNam(VDM_INDEX_OUTSB)
    genNam(VDM_INDEX_OUTSW)
    genNam(VDM_INDEX_PUSHF)
    genNam(VDM_INDEX_POPF)
    genNam(VDM_INDEX_INTnn)
    genNam(VDM_INDEX_INTO)
    genNam(VDM_INDEX_IRET)
    genNam(VDM_INDEX_NPX)
    genNam(VDM_INDEX_INBimm)
    genNam(VDM_INDEX_INWimm)
    genNam(VDM_INDEX_OUTBimm)
    genNam(VDM_INDEX_OUTWimm)
    genNam(VDM_INDEX_INB)
    genNam(VDM_INDEX_INW)
    genNam(VDM_INDEX_OUTB)
    genNam(VDM_INDEX_OUTW)
    genNam(VDM_INDEX_LOCKPrefix)
    genNam(VDM_INDEX_REPNEPrefix)
    genNam(VDM_INDEX_REPPrefix)
    genNam(VDM_INDEX_CLI)
    genNam(VDM_INDEX_STI)
    genNam(VDM_INDEX_HLT)
    genNam(MAX_VDM_INDEX)

    //
    // Vdm feature bits
    //

    genCom("VDM feature bits.")

    genNam(V86_VIRTUAL_INT_EXTENSIONS)
    genNam(PM_VIRTUAL_INT_EXTENSIONS)

    //
    // Selector type
    //

    genCom("Selector types.")

    genNam(SEL_TYPE_NP)

    //
    // Usermode callout frame
    //
  DisableInc (HAL386)
    genCom("Usermode callout frame definitions")
    genDef(Cu, KCALLOUT_FRAME, InStk)
    genDef(Cu, KCALLOUT_FRAME, TrFr)
    genDef(Cu, KCALLOUT_FRAME, CbStk)
    genDef(Cu, KCALLOUT_FRAME, Edi)
    genDef(Cu, KCALLOUT_FRAME, Esi)
    genDef(Cu, KCALLOUT_FRAME, Ebx)
    genDef(Cu, KCALLOUT_FRAME, Ebp)
    genDef(Cu, KCALLOUT_FRAME, Ret)
    genDef(Cu, KCALLOUT_FRAME, OutBf)
    genDef(Cu, KCALLOUT_FRAME, OutLn)

    //
    // VDM_PROCESS_OBJECTS
    //

    genCom("VDM_PROCESS_OBJECTS")

    genDef(Vp, VDM_PROCESS_OBJECTS, VdmTib)

  EnableInc (HAL386)

    END_LIST
};
