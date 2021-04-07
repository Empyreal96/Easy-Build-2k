

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* Compiler settings for mstask.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __mstask_h__
#define __mstask_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITaskTrigger_FWD_DEFINED__
#define __ITaskTrigger_FWD_DEFINED__
typedef interface ITaskTrigger ITaskTrigger;
#endif 	/* __ITaskTrigger_FWD_DEFINED__ */


#ifndef __IScheduledWorkItem_FWD_DEFINED__
#define __IScheduledWorkItem_FWD_DEFINED__
typedef interface IScheduledWorkItem IScheduledWorkItem;
#endif 	/* __IScheduledWorkItem_FWD_DEFINED__ */


#ifndef __ITask_FWD_DEFINED__
#define __ITask_FWD_DEFINED__
typedef interface ITask ITask;
#endif 	/* __ITask_FWD_DEFINED__ */


#ifndef __IEnumWorkItems_FWD_DEFINED__
#define __IEnumWorkItems_FWD_DEFINED__
typedef interface IEnumWorkItems IEnumWorkItems;
#endif 	/* __IEnumWorkItems_FWD_DEFINED__ */


#ifndef __ITaskScheduler_FWD_DEFINED__
#define __ITaskScheduler_FWD_DEFINED__
typedef interface ITaskScheduler ITaskScheduler;
#endif 	/* __ITaskScheduler_FWD_DEFINED__ */


#ifndef __IProvideTaskPage_FWD_DEFINED__
#define __IProvideTaskPage_FWD_DEFINED__
typedef interface IProvideTaskPage IProvideTaskPage;
#endif 	/* __IProvideTaskPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "oleidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mstask_0000 */
/* [local] */ 

#define TASK_SUNDAY       (0x1)
#define TASK_MONDAY       (0x2)
#define TASK_TUESDAY      (0x4)
#define TASK_WEDNESDAY    (0x8)
#define TASK_THURSDAY     (0x10)
#define TASK_FRIDAY       (0x20)
#define TASK_SATURDAY     (0x40)
#define TASK_FIRST_WEEK   (1)
#define TASK_SECOND_WEEK  (2)
#define TASK_THIRD_WEEK   (3)
#define TASK_FOURTH_WEEK  (4)
#define TASK_LAST_WEEK    (5)
#define TASK_JANUARY      (0x1)
#define TASK_FEBRUARY     (0x2)
#define TASK_MARCH        (0x4)
#define TASK_APRIL        (0x8)
#define TASK_MAY          (0x10)
#define TASK_JUNE         (0x20)
#define TASK_JULY         (0x40)
#define TASK_AUGUST       (0x80)
#define TASK_SEPTEMBER    (0x100)
#define TASK_OCTOBER      (0x200)
#define TASK_NOVEMBER     (0x400)
#define TASK_DECEMBER     (0x800)
#define TASK_FLAG_INTERACTIVE                  (0x1)
#define TASK_FLAG_DELETE_WHEN_DONE             (0x2)
#define TASK_FLAG_DISABLED                     (0x4)
#define TASK_FLAG_START_ONLY_IF_IDLE           (0x10)
#define TASK_FLAG_KILL_ON_IDLE_END             (0x20)
#define TASK_FLAG_DONT_START_IF_ON_BATTERIES   (0x40)
#define TASK_FLAG_KILL_IF_GOING_ON_BATTERIES   (0x80)
#define TASK_FLAG_RUN_ONLY_IF_DOCKED           (0x100)
#define TASK_FLAG_HIDDEN                       (0x200)
#define TASK_FLAG_RUN_IF_CONNECTED_TO_INTERNET (0x400)
#define TASK_FLAG_RESTART_ON_IDLE_RESUME       (0x800)
#define TASK_FLAG_SYSTEM_REQUIRED              (0x1000)
#define TASK_FLAG_RUN_ONLY_IF_LOGGED_ON        (0x2000)
#define TASK_TRIGGER_FLAG_HAS_END_DATE         (0x1)
#define TASK_TRIGGER_FLAG_KILL_AT_DURATION_END (0x2)
#define TASK_TRIGGER_FLAG_DISABLED             (0x4)
#define	TASK_MAX_RUN_TIMES	( 1440 )

typedef 
enum _TASK_TRIGGER_TYPE
    {	TASK_TIME_TRIGGER_ONCE	= 0,
	TASK_TIME_TRIGGER_DAILY	= 1,
	TASK_TIME_TRIGGER_WEEKLY	= 2,
	TASK_TIME_TRIGGER_MONTHLYDATE	= 3,
	TASK_TIME_TRIGGER_MONTHLYDOW	= 4,
	TASK_EVENT_TRIGGER_ON_IDLE	= 5,
	TASK_EVENT_TRIGGER_AT_SYSTEMSTART	= 6,
	TASK_EVENT_TRIGGER_AT_LOGON	= 7
    } 	TASK_TRIGGER_TYPE;

typedef enum _TASK_TRIGGER_TYPE *PTASK_TRIGGER_TYPE;

typedef struct _DAILY
    {
    WORD DaysInterval;
    } 	DAILY;

typedef struct _WEEKLY
    {
    WORD WeeksInterval;
    WORD rgfDaysOfTheWeek;
    } 	WEEKLY;

typedef struct _MONTHLYDATE
    {
    DWORD rgfDays;
    WORD rgfMonths;
    } 	MONTHLYDATE;

typedef struct _MONTHLYDOW
    {
    WORD wWhichWeek;
    WORD rgfDaysOfTheWeek;
    WORD rgfMonths;
    } 	MONTHLYDOW;

typedef union _TRIGGER_TYPE_UNION
    {
    DAILY Daily;
    WEEKLY Weekly;
    MONTHLYDATE MonthlyDate;
    MONTHLYDOW MonthlyDOW;
    } 	TRIGGER_TYPE_UNION;

typedef struct _TASK_TRIGGER
    {
    WORD cbTriggerSize;
    WORD Reserved1;
    WORD wBeginYear;
    WORD wBeginMonth;
    WORD wBeginDay;
    WORD wEndYear;
    WORD wEndMonth;
    WORD wEndDay;
    WORD wStartHour;
    WORD wStartMinute;
    DWORD MinutesDuration;
    DWORD MinutesInterval;
    DWORD rgFlags;
    TASK_TRIGGER_TYPE TriggerType;
    TRIGGER_TYPE_UNION Type;
    WORD Reserved2;
    WORD wRandomMinutesInterval;
    } 	TASK_TRIGGER;

typedef struct _TASK_TRIGGER *PTASK_TRIGGER;

// {148BD52B-A2AB-11CE-B11F-00AA00530503}
DEFINE_GUID(IID_ITaskTrigger, 0x148BD52BL, 0xA2AB, 0x11CE, 0xB1, 0x1F, 0x00, 0xAA, 0x00, 0x53, 0x05, 0x03);



extern RPC_IF_HANDLE __MIDL_itf_mstask_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0000_v0_0_s_ifspec;

#ifndef __ITaskTrigger_INTERFACE_DEFINED__
#define __ITaskTrigger_INTERFACE_DEFINED__

/* interface ITaskTrigger */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_ITaskTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("148BD52B-A2AB-11CE-B11F-00AA00530503")
    ITaskTrigger : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTrigger( 
            /* [in] */ const PTASK_TRIGGER pTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTrigger( 
            /* [out] */ PTASK_TRIGGER pTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTriggerString( 
            /* [out] */ LPWSTR *ppwszTrigger) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITaskTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITaskTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITaskTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITaskTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTrigger )( 
            ITaskTrigger * This,
            /* [in] */ const PTASK_TRIGGER pTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrigger )( 
            ITaskTrigger * This,
            /* [out] */ PTASK_TRIGGER pTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetTriggerString )( 
            ITaskTrigger * This,
            /* [out] */ LPWSTR *ppwszTrigger);
        
        END_INTERFACE
    } ITaskTriggerVtbl;

    interface ITaskTrigger
    {
        CONST_VTBL struct ITaskTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITaskTrigger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITaskTrigger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITaskTrigger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITaskTrigger_SetTrigger(This,pTrigger)	\
    (This)->lpVtbl -> SetTrigger(This,pTrigger)

#define ITaskTrigger_GetTrigger(This,pTrigger)	\
    (This)->lpVtbl -> GetTrigger(This,pTrigger)

#define ITaskTrigger_GetTriggerString(This,ppwszTrigger)	\
    (This)->lpVtbl -> GetTriggerString(This,ppwszTrigger)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITaskTrigger_SetTrigger_Proxy( 
    ITaskTrigger * This,
    /* [in] */ const PTASK_TRIGGER pTrigger);


void __RPC_STUB ITaskTrigger_SetTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskTrigger_GetTrigger_Proxy( 
    ITaskTrigger * This,
    /* [out] */ PTASK_TRIGGER pTrigger);


void __RPC_STUB ITaskTrigger_GetTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskTrigger_GetTriggerString_Proxy( 
    ITaskTrigger * This,
    /* [out] */ LPWSTR *ppwszTrigger);


void __RPC_STUB ITaskTrigger_GetTriggerString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITaskTrigger_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstask_0140 */
/* [local] */ 

// {a6b952f0-a4b1-11d0-997d-00aa006887ec}
DEFINE_GUID(IID_IScheduledWorkItem, 0xa6b952f0L, 0xa4b1, 0x11d0, 0x99, 0x7d, 0x00, 0xaa, 0x00, 0x68, 0x87, 0xec);



extern RPC_IF_HANDLE __MIDL_itf_mstask_0140_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0140_v0_0_s_ifspec;

#ifndef __IScheduledWorkItem_INTERFACE_DEFINED__
#define __IScheduledWorkItem_INTERFACE_DEFINED__

/* interface IScheduledWorkItem */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IScheduledWorkItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a6b952f0-a4b1-11d0-997d-00aa006887ec")
    IScheduledWorkItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateTrigger( 
            /* [out] */ WORD *piNewTrigger,
            /* [out] */ ITaskTrigger **ppTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteTrigger( 
            /* [in] */ WORD iTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTriggerCount( 
            /* [out] */ WORD *pwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTrigger( 
            /* [in] */ WORD iTrigger,
            /* [out] */ ITaskTrigger **ppTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTriggerString( 
            /* [in] */ WORD iTrigger,
            /* [out] */ LPWSTR *ppwszTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRunTimes( 
            /* [in] */ const LPSYSTEMTIME pstBegin,
            /* [in] */ const LPSYSTEMTIME pstEnd,
            /* [out][in] */ WORD *pCount,
            /* [out] */ LPSYSTEMTIME *rgstTaskTimes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextRunTime( 
            /* [out][in] */ SYSTEMTIME *pstNextRun) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIdleWait( 
            /* [in] */ WORD wIdleMinutes,
            /* [in] */ WORD wDeadlineMinutes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIdleWait( 
            /* [out] */ WORD *pwIdleMinutes,
            /* [out] */ WORD *pwDeadlineMinutes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Terminate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EditWorkItem( 
            /* [in] */ HWND hParent,
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMostRecentRunTime( 
            /* [out] */ SYSTEMTIME *pstLastRun) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out] */ HRESULT *phrStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExitCode( 
            /* [out] */ DWORD *pdwExitCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetComment( 
            /* [in] */ LPCWSTR pwszComment) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetComment( 
            /* [out] */ LPWSTR *ppwszComment) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCreator( 
            /* [in] */ LPCWSTR pwszCreator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCreator( 
            /* [out] */ LPWSTR *ppwszCreator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWorkItemData( 
            /* [in] */ WORD cbData,
            /* [in] */ BYTE rgbData[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkItemData( 
            /* [out] */ WORD *pcbData,
            /* [out] */ BYTE **prgbData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetErrorRetryCount( 
            /* [in] */ WORD wRetryCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetErrorRetryCount( 
            /* [out] */ WORD *pwRetryCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetErrorRetryInterval( 
            /* [in] */ WORD wRetryInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetErrorRetryInterval( 
            /* [out] */ WORD *pwRetryInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAccountInformation( 
            /* [in] */ LPCWSTR pwszAccountName,
            /* [in] */ LPCWSTR pwszPassword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAccountInformation( 
            /* [out] */ LPWSTR *ppwszAccountName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScheduledWorkItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScheduledWorkItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScheduledWorkItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScheduledWorkItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateTrigger )( 
            IScheduledWorkItem * This,
            /* [out] */ WORD *piNewTrigger,
            /* [out] */ ITaskTrigger **ppTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteTrigger )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD iTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetTriggerCount )( 
            IScheduledWorkItem * This,
            /* [out] */ WORD *pwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrigger )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD iTrigger,
            /* [out] */ ITaskTrigger **ppTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetTriggerString )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD iTrigger,
            /* [out] */ LPWSTR *ppwszTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetRunTimes )( 
            IScheduledWorkItem * This,
            /* [in] */ const LPSYSTEMTIME pstBegin,
            /* [in] */ const LPSYSTEMTIME pstEnd,
            /* [out][in] */ WORD *pCount,
            /* [out] */ LPSYSTEMTIME *rgstTaskTimes);
        
        HRESULT ( STDMETHODCALLTYPE *GetNextRunTime )( 
            IScheduledWorkItem * This,
            /* [out][in] */ SYSTEMTIME *pstNextRun);
        
        HRESULT ( STDMETHODCALLTYPE *SetIdleWait )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD wIdleMinutes,
            /* [in] */ WORD wDeadlineMinutes);
        
        HRESULT ( STDMETHODCALLTYPE *GetIdleWait )( 
            IScheduledWorkItem * This,
            /* [out] */ WORD *pwIdleMinutes,
            /* [out] */ WORD *pwDeadlineMinutes);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            IScheduledWorkItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *Terminate )( 
            IScheduledWorkItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *EditWorkItem )( 
            IScheduledWorkItem * This,
            /* [in] */ HWND hParent,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *GetMostRecentRunTime )( 
            IScheduledWorkItem * This,
            /* [out] */ SYSTEMTIME *pstLastRun);
        
        HRESULT ( STDMETHODCALLTYPE *GetStatus )( 
            IScheduledWorkItem * This,
            /* [out] */ HRESULT *phrStatus);
        
        HRESULT ( STDMETHODCALLTYPE *GetExitCode )( 
            IScheduledWorkItem * This,
            /* [out] */ DWORD *pdwExitCode);
        
        HRESULT ( STDMETHODCALLTYPE *SetComment )( 
            IScheduledWorkItem * This,
            /* [in] */ LPCWSTR pwszComment);
        
        HRESULT ( STDMETHODCALLTYPE *GetComment )( 
            IScheduledWorkItem * This,
            /* [out] */ LPWSTR *ppwszComment);
        
        HRESULT ( STDMETHODCALLTYPE *SetCreator )( 
            IScheduledWorkItem * This,
            /* [in] */ LPCWSTR pwszCreator);
        
        HRESULT ( STDMETHODCALLTYPE *GetCreator )( 
            IScheduledWorkItem * This,
            /* [out] */ LPWSTR *ppwszCreator);
        
        HRESULT ( STDMETHODCALLTYPE *SetWorkItemData )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD cbData,
            /* [in] */ BYTE rgbData[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *GetWorkItemData )( 
            IScheduledWorkItem * This,
            /* [out] */ WORD *pcbData,
            /* [out] */ BYTE **prgbData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorRetryCount )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD wRetryCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorRetryCount )( 
            IScheduledWorkItem * This,
            /* [out] */ WORD *pwRetryCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorRetryInterval )( 
            IScheduledWorkItem * This,
            /* [in] */ WORD wRetryInterval);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorRetryInterval )( 
            IScheduledWorkItem * This,
            /* [out] */ WORD *pwRetryInterval);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlags )( 
            IScheduledWorkItem * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlags )( 
            IScheduledWorkItem * This,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetAccountInformation )( 
            IScheduledWorkItem * This,
            /* [in] */ LPCWSTR pwszAccountName,
            /* [in] */ LPCWSTR pwszPassword);
        
        HRESULT ( STDMETHODCALLTYPE *GetAccountInformation )( 
            IScheduledWorkItem * This,
            /* [out] */ LPWSTR *ppwszAccountName);
        
        END_INTERFACE
    } IScheduledWorkItemVtbl;

    interface IScheduledWorkItem
    {
        CONST_VTBL struct IScheduledWorkItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScheduledWorkItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScheduledWorkItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScheduledWorkItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScheduledWorkItem_CreateTrigger(This,piNewTrigger,ppTrigger)	\
    (This)->lpVtbl -> CreateTrigger(This,piNewTrigger,ppTrigger)

#define IScheduledWorkItem_DeleteTrigger(This,iTrigger)	\
    (This)->lpVtbl -> DeleteTrigger(This,iTrigger)

#define IScheduledWorkItem_GetTriggerCount(This,pwCount)	\
    (This)->lpVtbl -> GetTriggerCount(This,pwCount)

#define IScheduledWorkItem_GetTrigger(This,iTrigger,ppTrigger)	\
    (This)->lpVtbl -> GetTrigger(This,iTrigger,ppTrigger)

#define IScheduledWorkItem_GetTriggerString(This,iTrigger,ppwszTrigger)	\
    (This)->lpVtbl -> GetTriggerString(This,iTrigger,ppwszTrigger)

#define IScheduledWorkItem_GetRunTimes(This,pstBegin,pstEnd,pCount,rgstTaskTimes)	\
    (This)->lpVtbl -> GetRunTimes(This,pstBegin,pstEnd,pCount,rgstTaskTimes)

#define IScheduledWorkItem_GetNextRunTime(This,pstNextRun)	\
    (This)->lpVtbl -> GetNextRunTime(This,pstNextRun)

#define IScheduledWorkItem_SetIdleWait(This,wIdleMinutes,wDeadlineMinutes)	\
    (This)->lpVtbl -> SetIdleWait(This,wIdleMinutes,wDeadlineMinutes)

#define IScheduledWorkItem_GetIdleWait(This,pwIdleMinutes,pwDeadlineMinutes)	\
    (This)->lpVtbl -> GetIdleWait(This,pwIdleMinutes,pwDeadlineMinutes)

#define IScheduledWorkItem_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IScheduledWorkItem_Terminate(This)	\
    (This)->lpVtbl -> Terminate(This)

#define IScheduledWorkItem_EditWorkItem(This,hParent,dwReserved)	\
    (This)->lpVtbl -> EditWorkItem(This,hParent,dwReserved)

#define IScheduledWorkItem_GetMostRecentRunTime(This,pstLastRun)	\
    (This)->lpVtbl -> GetMostRecentRunTime(This,pstLastRun)

#define IScheduledWorkItem_GetStatus(This,phrStatus)	\
    (This)->lpVtbl -> GetStatus(This,phrStatus)

#define IScheduledWorkItem_GetExitCode(This,pdwExitCode)	\
    (This)->lpVtbl -> GetExitCode(This,pdwExitCode)

#define IScheduledWorkItem_SetComment(This,pwszComment)	\
    (This)->lpVtbl -> SetComment(This,pwszComment)

#define IScheduledWorkItem_GetComment(This,ppwszComment)	\
    (This)->lpVtbl -> GetComment(This,ppwszComment)

#define IScheduledWorkItem_SetCreator(This,pwszCreator)	\
    (This)->lpVtbl -> SetCreator(This,pwszCreator)

#define IScheduledWorkItem_GetCreator(This,ppwszCreator)	\
    (This)->lpVtbl -> GetCreator(This,ppwszCreator)

#define IScheduledWorkItem_SetWorkItemData(This,cbData,rgbData)	\
    (This)->lpVtbl -> SetWorkItemData(This,cbData,rgbData)

#define IScheduledWorkItem_GetWorkItemData(This,pcbData,prgbData)	\
    (This)->lpVtbl -> GetWorkItemData(This,pcbData,prgbData)

#define IScheduledWorkItem_SetErrorRetryCount(This,wRetryCount)	\
    (This)->lpVtbl -> SetErrorRetryCount(This,wRetryCount)

#define IScheduledWorkItem_GetErrorRetryCount(This,pwRetryCount)	\
    (This)->lpVtbl -> GetErrorRetryCount(This,pwRetryCount)

#define IScheduledWorkItem_SetErrorRetryInterval(This,wRetryInterval)	\
    (This)->lpVtbl -> SetErrorRetryInterval(This,wRetryInterval)

#define IScheduledWorkItem_GetErrorRetryInterval(This,pwRetryInterval)	\
    (This)->lpVtbl -> GetErrorRetryInterval(This,pwRetryInterval)

#define IScheduledWorkItem_SetFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,dwFlags)

#define IScheduledWorkItem_GetFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,pdwFlags)

#define IScheduledWorkItem_SetAccountInformation(This,pwszAccountName,pwszPassword)	\
    (This)->lpVtbl -> SetAccountInformation(This,pwszAccountName,pwszPassword)

#define IScheduledWorkItem_GetAccountInformation(This,ppwszAccountName)	\
    (This)->lpVtbl -> GetAccountInformation(This,ppwszAccountName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IScheduledWorkItem_CreateTrigger_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ WORD *piNewTrigger,
    /* [out] */ ITaskTrigger **ppTrigger);


void __RPC_STUB IScheduledWorkItem_CreateTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_DeleteTrigger_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD iTrigger);


void __RPC_STUB IScheduledWorkItem_DeleteTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetTriggerCount_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ WORD *pwCount);


void __RPC_STUB IScheduledWorkItem_GetTriggerCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetTrigger_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD iTrigger,
    /* [out] */ ITaskTrigger **ppTrigger);


void __RPC_STUB IScheduledWorkItem_GetTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetTriggerString_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD iTrigger,
    /* [out] */ LPWSTR *ppwszTrigger);


void __RPC_STUB IScheduledWorkItem_GetTriggerString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetRunTimes_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ const LPSYSTEMTIME pstBegin,
    /* [in] */ const LPSYSTEMTIME pstEnd,
    /* [out][in] */ WORD *pCount,
    /* [out] */ LPSYSTEMTIME *rgstTaskTimes);


void __RPC_STUB IScheduledWorkItem_GetRunTimes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetNextRunTime_Proxy( 
    IScheduledWorkItem * This,
    /* [out][in] */ SYSTEMTIME *pstNextRun);


void __RPC_STUB IScheduledWorkItem_GetNextRunTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetIdleWait_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD wIdleMinutes,
    /* [in] */ WORD wDeadlineMinutes);


void __RPC_STUB IScheduledWorkItem_SetIdleWait_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetIdleWait_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ WORD *pwIdleMinutes,
    /* [out] */ WORD *pwDeadlineMinutes);


void __RPC_STUB IScheduledWorkItem_GetIdleWait_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_Run_Proxy( 
    IScheduledWorkItem * This);


void __RPC_STUB IScheduledWorkItem_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_Terminate_Proxy( 
    IScheduledWorkItem * This);


void __RPC_STUB IScheduledWorkItem_Terminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_EditWorkItem_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ HWND hParent,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB IScheduledWorkItem_EditWorkItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetMostRecentRunTime_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ SYSTEMTIME *pstLastRun);


void __RPC_STUB IScheduledWorkItem_GetMostRecentRunTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetStatus_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ HRESULT *phrStatus);


void __RPC_STUB IScheduledWorkItem_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetExitCode_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ DWORD *pdwExitCode);


void __RPC_STUB IScheduledWorkItem_GetExitCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetComment_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ LPCWSTR pwszComment);


void __RPC_STUB IScheduledWorkItem_SetComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetComment_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ LPWSTR *ppwszComment);


void __RPC_STUB IScheduledWorkItem_GetComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetCreator_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ LPCWSTR pwszCreator);


void __RPC_STUB IScheduledWorkItem_SetCreator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetCreator_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ LPWSTR *ppwszCreator);


void __RPC_STUB IScheduledWorkItem_GetCreator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetWorkItemData_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD cbData,
    /* [in] */ BYTE rgbData[  ]);


void __RPC_STUB IScheduledWorkItem_SetWorkItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetWorkItemData_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ WORD *pcbData,
    /* [out] */ BYTE **prgbData);


void __RPC_STUB IScheduledWorkItem_GetWorkItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetErrorRetryCount_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD wRetryCount);


void __RPC_STUB IScheduledWorkItem_SetErrorRetryCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetErrorRetryCount_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ WORD *pwRetryCount);


void __RPC_STUB IScheduledWorkItem_GetErrorRetryCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetErrorRetryInterval_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ WORD wRetryInterval);


void __RPC_STUB IScheduledWorkItem_SetErrorRetryInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetErrorRetryInterval_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ WORD *pwRetryInterval);


void __RPC_STUB IScheduledWorkItem_GetErrorRetryInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetFlags_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IScheduledWorkItem_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetFlags_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IScheduledWorkItem_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_SetAccountInformation_Proxy( 
    IScheduledWorkItem * This,
    /* [in] */ LPCWSTR pwszAccountName,
    /* [in] */ LPCWSTR pwszPassword);


void __RPC_STUB IScheduledWorkItem_SetAccountInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IScheduledWorkItem_GetAccountInformation_Proxy( 
    IScheduledWorkItem * This,
    /* [out] */ LPWSTR *ppwszAccountName);


void __RPC_STUB IScheduledWorkItem_GetAccountInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScheduledWorkItem_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstask_0141 */
/* [local] */ 

// {148BD524-A2AB-11CE-B11F-00AA00530503}
DEFINE_GUID(IID_ITask, 0x148BD524L, 0xA2AB, 0x11CE, 0xB1, 0x1F, 0x00, 0xAA, 0x00, 0x53, 0x05, 0x03);



extern RPC_IF_HANDLE __MIDL_itf_mstask_0141_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0141_v0_0_s_ifspec;

#ifndef __ITask_INTERFACE_DEFINED__
#define __ITask_INTERFACE_DEFINED__

/* interface ITask */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_ITask;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("148BD524-A2AB-11CE-B11F-00AA00530503")
    ITask : public IScheduledWorkItem
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetApplicationName( 
            /* [in] */ LPCWSTR pwszApplicationName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetApplicationName( 
            /* [out] */ LPWSTR *ppwszApplicationName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParameters( 
            /* [in] */ LPCWSTR pwszParameters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParameters( 
            /* [out] */ LPWSTR *ppwszParameters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWorkingDirectory( 
            /* [in] */ LPCWSTR pwszWorkingDirectory) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkingDirectory( 
            /* [out] */ LPWSTR *ppwszWorkingDirectory) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPriority( 
            /* [in] */ DWORD dwPriority) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPriority( 
            /* [out] */ DWORD *pdwPriority) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTaskFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTaskFlags( 
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxRunTime( 
            /* [in] */ DWORD dwMaxRunTimeMS) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxRunTime( 
            /* [out] */ DWORD *pdwMaxRunTimeMS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITaskVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITask * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITask * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITask * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateTrigger )( 
            ITask * This,
            /* [out] */ WORD *piNewTrigger,
            /* [out] */ ITaskTrigger **ppTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteTrigger )( 
            ITask * This,
            /* [in] */ WORD iTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetTriggerCount )( 
            ITask * This,
            /* [out] */ WORD *pwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrigger )( 
            ITask * This,
            /* [in] */ WORD iTrigger,
            /* [out] */ ITaskTrigger **ppTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetTriggerString )( 
            ITask * This,
            /* [in] */ WORD iTrigger,
            /* [out] */ LPWSTR *ppwszTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *GetRunTimes )( 
            ITask * This,
            /* [in] */ const LPSYSTEMTIME pstBegin,
            /* [in] */ const LPSYSTEMTIME pstEnd,
            /* [out][in] */ WORD *pCount,
            /* [out] */ LPSYSTEMTIME *rgstTaskTimes);
        
        HRESULT ( STDMETHODCALLTYPE *GetNextRunTime )( 
            ITask * This,
            /* [out][in] */ SYSTEMTIME *pstNextRun);
        
        HRESULT ( STDMETHODCALLTYPE *SetIdleWait )( 
            ITask * This,
            /* [in] */ WORD wIdleMinutes,
            /* [in] */ WORD wDeadlineMinutes);
        
        HRESULT ( STDMETHODCALLTYPE *GetIdleWait )( 
            ITask * This,
            /* [out] */ WORD *pwIdleMinutes,
            /* [out] */ WORD *pwDeadlineMinutes);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            ITask * This);
        
        HRESULT ( STDMETHODCALLTYPE *Terminate )( 
            ITask * This);
        
        HRESULT ( STDMETHODCALLTYPE *EditWorkItem )( 
            ITask * This,
            /* [in] */ HWND hParent,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *GetMostRecentRunTime )( 
            ITask * This,
            /* [out] */ SYSTEMTIME *pstLastRun);
        
        HRESULT ( STDMETHODCALLTYPE *GetStatus )( 
            ITask * This,
            /* [out] */ HRESULT *phrStatus);
        
        HRESULT ( STDMETHODCALLTYPE *GetExitCode )( 
            ITask * This,
            /* [out] */ DWORD *pdwExitCode);
        
        HRESULT ( STDMETHODCALLTYPE *SetComment )( 
            ITask * This,
            /* [in] */ LPCWSTR pwszComment);
        
        HRESULT ( STDMETHODCALLTYPE *GetComment )( 
            ITask * This,
            /* [out] */ LPWSTR *ppwszComment);
        
        HRESULT ( STDMETHODCALLTYPE *SetCreator )( 
            ITask * This,
            /* [in] */ LPCWSTR pwszCreator);
        
        HRESULT ( STDMETHODCALLTYPE *GetCreator )( 
            ITask * This,
            /* [out] */ LPWSTR *ppwszCreator);
        
        HRESULT ( STDMETHODCALLTYPE *SetWorkItemData )( 
            ITask * This,
            /* [in] */ WORD cbData,
            /* [in] */ BYTE rgbData[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *GetWorkItemData )( 
            ITask * This,
            /* [out] */ WORD *pcbData,
            /* [out] */ BYTE **prgbData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorRetryCount )( 
            ITask * This,
            /* [in] */ WORD wRetryCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorRetryCount )( 
            ITask * This,
            /* [out] */ WORD *pwRetryCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorRetryInterval )( 
            ITask * This,
            /* [in] */ WORD wRetryInterval);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorRetryInterval )( 
            ITask * This,
            /* [out] */ WORD *pwRetryInterval);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlags )( 
            ITask * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlags )( 
            ITask * This,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetAccountInformation )( 
            ITask * This,
            /* [in] */ LPCWSTR pwszAccountName,
            /* [in] */ LPCWSTR pwszPassword);
        
        HRESULT ( STDMETHODCALLTYPE *GetAccountInformation )( 
            ITask * This,
            /* [out] */ LPWSTR *ppwszAccountName);
        
        HRESULT ( STDMETHODCALLTYPE *SetApplicationName )( 
            ITask * This,
            /* [in] */ LPCWSTR pwszApplicationName);
        
        HRESULT ( STDMETHODCALLTYPE *GetApplicationName )( 
            ITask * This,
            /* [out] */ LPWSTR *ppwszApplicationName);
        
        HRESULT ( STDMETHODCALLTYPE *SetParameters )( 
            ITask * This,
            /* [in] */ LPCWSTR pwszParameters);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameters )( 
            ITask * This,
            /* [out] */ LPWSTR *ppwszParameters);
        
        HRESULT ( STDMETHODCALLTYPE *SetWorkingDirectory )( 
            ITask * This,
            /* [in] */ LPCWSTR pwszWorkingDirectory);
        
        HRESULT ( STDMETHODCALLTYPE *GetWorkingDirectory )( 
            ITask * This,
            /* [out] */ LPWSTR *ppwszWorkingDirectory);
        
        HRESULT ( STDMETHODCALLTYPE *SetPriority )( 
            ITask * This,
            /* [in] */ DWORD dwPriority);
        
        HRESULT ( STDMETHODCALLTYPE *GetPriority )( 
            ITask * This,
            /* [out] */ DWORD *pdwPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetTaskFlags )( 
            ITask * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetTaskFlags )( 
            ITask * This,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetMaxRunTime )( 
            ITask * This,
            /* [in] */ DWORD dwMaxRunTimeMS);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxRunTime )( 
            ITask * This,
            /* [out] */ DWORD *pdwMaxRunTimeMS);
        
        END_INTERFACE
    } ITaskVtbl;

    interface ITask
    {
        CONST_VTBL struct ITaskVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITask_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITask_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITask_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITask_CreateTrigger(This,piNewTrigger,ppTrigger)	\
    (This)->lpVtbl -> CreateTrigger(This,piNewTrigger,ppTrigger)

#define ITask_DeleteTrigger(This,iTrigger)	\
    (This)->lpVtbl -> DeleteTrigger(This,iTrigger)

#define ITask_GetTriggerCount(This,pwCount)	\
    (This)->lpVtbl -> GetTriggerCount(This,pwCount)

#define ITask_GetTrigger(This,iTrigger,ppTrigger)	\
    (This)->lpVtbl -> GetTrigger(This,iTrigger,ppTrigger)

#define ITask_GetTriggerString(This,iTrigger,ppwszTrigger)	\
    (This)->lpVtbl -> GetTriggerString(This,iTrigger,ppwszTrigger)

#define ITask_GetRunTimes(This,pstBegin,pstEnd,pCount,rgstTaskTimes)	\
    (This)->lpVtbl -> GetRunTimes(This,pstBegin,pstEnd,pCount,rgstTaskTimes)

#define ITask_GetNextRunTime(This,pstNextRun)	\
    (This)->lpVtbl -> GetNextRunTime(This,pstNextRun)

#define ITask_SetIdleWait(This,wIdleMinutes,wDeadlineMinutes)	\
    (This)->lpVtbl -> SetIdleWait(This,wIdleMinutes,wDeadlineMinutes)

#define ITask_GetIdleWait(This,pwIdleMinutes,pwDeadlineMinutes)	\
    (This)->lpVtbl -> GetIdleWait(This,pwIdleMinutes,pwDeadlineMinutes)

#define ITask_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define ITask_Terminate(This)	\
    (This)->lpVtbl -> Terminate(This)

#define ITask_EditWorkItem(This,hParent,dwReserved)	\
    (This)->lpVtbl -> EditWorkItem(This,hParent,dwReserved)

#define ITask_GetMostRecentRunTime(This,pstLastRun)	\
    (This)->lpVtbl -> GetMostRecentRunTime(This,pstLastRun)

#define ITask_GetStatus(This,phrStatus)	\
    (This)->lpVtbl -> GetStatus(This,phrStatus)

#define ITask_GetExitCode(This,pdwExitCode)	\
    (This)->lpVtbl -> GetExitCode(This,pdwExitCode)

#define ITask_SetComment(This,pwszComment)	\
    (This)->lpVtbl -> SetComment(This,pwszComment)

#define ITask_GetComment(This,ppwszComment)	\
    (This)->lpVtbl -> GetComment(This,ppwszComment)

#define ITask_SetCreator(This,pwszCreator)	\
    (This)->lpVtbl -> SetCreator(This,pwszCreator)

#define ITask_GetCreator(This,ppwszCreator)	\
    (This)->lpVtbl -> GetCreator(This,ppwszCreator)

#define ITask_SetWorkItemData(This,cbData,rgbData)	\
    (This)->lpVtbl -> SetWorkItemData(This,cbData,rgbData)

#define ITask_GetWorkItemData(This,pcbData,prgbData)	\
    (This)->lpVtbl -> GetWorkItemData(This,pcbData,prgbData)

#define ITask_SetErrorRetryCount(This,wRetryCount)	\
    (This)->lpVtbl -> SetErrorRetryCount(This,wRetryCount)

#define ITask_GetErrorRetryCount(This,pwRetryCount)	\
    (This)->lpVtbl -> GetErrorRetryCount(This,pwRetryCount)

#define ITask_SetErrorRetryInterval(This,wRetryInterval)	\
    (This)->lpVtbl -> SetErrorRetryInterval(This,wRetryInterval)

#define ITask_GetErrorRetryInterval(This,pwRetryInterval)	\
    (This)->lpVtbl -> GetErrorRetryInterval(This,pwRetryInterval)

#define ITask_SetFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,dwFlags)

#define ITask_GetFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,pdwFlags)

#define ITask_SetAccountInformation(This,pwszAccountName,pwszPassword)	\
    (This)->lpVtbl -> SetAccountInformation(This,pwszAccountName,pwszPassword)

#define ITask_GetAccountInformation(This,ppwszAccountName)	\
    (This)->lpVtbl -> GetAccountInformation(This,ppwszAccountName)


#define ITask_SetApplicationName(This,pwszApplicationName)	\
    (This)->lpVtbl -> SetApplicationName(This,pwszApplicationName)

#define ITask_GetApplicationName(This,ppwszApplicationName)	\
    (This)->lpVtbl -> GetApplicationName(This,ppwszApplicationName)

#define ITask_SetParameters(This,pwszParameters)	\
    (This)->lpVtbl -> SetParameters(This,pwszParameters)

#define ITask_GetParameters(This,ppwszParameters)	\
    (This)->lpVtbl -> GetParameters(This,ppwszParameters)

#define ITask_SetWorkingDirectory(This,pwszWorkingDirectory)	\
    (This)->lpVtbl -> SetWorkingDirectory(This,pwszWorkingDirectory)

#define ITask_GetWorkingDirectory(This,ppwszWorkingDirectory)	\
    (This)->lpVtbl -> GetWorkingDirectory(This,ppwszWorkingDirectory)

#define ITask_SetPriority(This,dwPriority)	\
    (This)->lpVtbl -> SetPriority(This,dwPriority)

#define ITask_GetPriority(This,pdwPriority)	\
    (This)->lpVtbl -> GetPriority(This,pdwPriority)

#define ITask_SetTaskFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetTaskFlags(This,dwFlags)

#define ITask_GetTaskFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetTaskFlags(This,pdwFlags)

#define ITask_SetMaxRunTime(This,dwMaxRunTimeMS)	\
    (This)->lpVtbl -> SetMaxRunTime(This,dwMaxRunTimeMS)

#define ITask_GetMaxRunTime(This,pdwMaxRunTimeMS)	\
    (This)->lpVtbl -> GetMaxRunTime(This,pdwMaxRunTimeMS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITask_SetApplicationName_Proxy( 
    ITask * This,
    /* [in] */ LPCWSTR pwszApplicationName);


void __RPC_STUB ITask_SetApplicationName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_GetApplicationName_Proxy( 
    ITask * This,
    /* [out] */ LPWSTR *ppwszApplicationName);


void __RPC_STUB ITask_GetApplicationName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_SetParameters_Proxy( 
    ITask * This,
    /* [in] */ LPCWSTR pwszParameters);


void __RPC_STUB ITask_SetParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_GetParameters_Proxy( 
    ITask * This,
    /* [out] */ LPWSTR *ppwszParameters);


void __RPC_STUB ITask_GetParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_SetWorkingDirectory_Proxy( 
    ITask * This,
    /* [in] */ LPCWSTR pwszWorkingDirectory);


void __RPC_STUB ITask_SetWorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_GetWorkingDirectory_Proxy( 
    ITask * This,
    /* [out] */ LPWSTR *ppwszWorkingDirectory);


void __RPC_STUB ITask_GetWorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_SetPriority_Proxy( 
    ITask * This,
    /* [in] */ DWORD dwPriority);


void __RPC_STUB ITask_SetPriority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_GetPriority_Proxy( 
    ITask * This,
    /* [out] */ DWORD *pdwPriority);


void __RPC_STUB ITask_GetPriority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_SetTaskFlags_Proxy( 
    ITask * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB ITask_SetTaskFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_GetTaskFlags_Proxy( 
    ITask * This,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB ITask_GetTaskFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_SetMaxRunTime_Proxy( 
    ITask * This,
    /* [in] */ DWORD dwMaxRunTimeMS);


void __RPC_STUB ITask_SetMaxRunTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITask_GetMaxRunTime_Proxy( 
    ITask * This,
    /* [out] */ DWORD *pdwMaxRunTimeMS);


void __RPC_STUB ITask_GetMaxRunTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITask_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstask_0142 */
/* [local] */ 

// {148BD528-A2AB-11CE-B11F-00AA00530503}
DEFINE_GUID(IID_IEnumWorkItems, 0x148BD528L, 0xA2AB, 0x11CE, 0xB1, 0x1F, 0x00, 0xAA, 0x00, 0x53, 0x05, 0x03);



extern RPC_IF_HANDLE __MIDL_itf_mstask_0142_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0142_v0_0_s_ifspec;

#ifndef __IEnumWorkItems_INTERFACE_DEFINED__
#define __IEnumWorkItems_INTERFACE_DEFINED__

/* interface IEnumWorkItems */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IEnumWorkItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("148BD528-A2AB-11CE-B11F-00AA00530503")
    IEnumWorkItems : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ LPWSTR **rgpwszNames,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWorkItems **ppEnumWorkItems) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumWorkItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWorkItems * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWorkItems * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWorkItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWorkItems * This,
            /* [in] */ ULONG celt,
            /* [out] */ LPWSTR **rgpwszNames,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWorkItems * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWorkItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWorkItems * This,
            /* [out] */ IEnumWorkItems **ppEnumWorkItems);
        
        END_INTERFACE
    } IEnumWorkItemsVtbl;

    interface IEnumWorkItems
    {
        CONST_VTBL struct IEnumWorkItemsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWorkItems_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumWorkItems_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumWorkItems_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumWorkItems_Next(This,celt,rgpwszNames,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgpwszNames,pceltFetched)

#define IEnumWorkItems_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumWorkItems_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumWorkItems_Clone(This,ppEnumWorkItems)	\
    (This)->lpVtbl -> Clone(This,ppEnumWorkItems)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumWorkItems_Next_Proxy( 
    IEnumWorkItems * This,
    /* [in] */ ULONG celt,
    /* [out] */ LPWSTR **rgpwszNames,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumWorkItems_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumWorkItems_Skip_Proxy( 
    IEnumWorkItems * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumWorkItems_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumWorkItems_Reset_Proxy( 
    IEnumWorkItems * This);


void __RPC_STUB IEnumWorkItems_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumWorkItems_Clone_Proxy( 
    IEnumWorkItems * This,
    /* [out] */ IEnumWorkItems **ppEnumWorkItems);


void __RPC_STUB IEnumWorkItems_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumWorkItems_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstask_0143 */
/* [local] */ 

// {148BD527-A2AB-11CE-B11F-00AA00530503}
DEFINE_GUID(IID_ITaskScheduler, 0x148BD527L, 0xA2AB, 0x11CE, 0xB1, 0x1F, 0x00, 0xAA, 0x00, 0x53, 0x05, 0x03);



extern RPC_IF_HANDLE __MIDL_itf_mstask_0143_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0143_v0_0_s_ifspec;

#ifndef __ITaskScheduler_INTERFACE_DEFINED__
#define __ITaskScheduler_INTERFACE_DEFINED__

/* interface ITaskScheduler */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_ITaskScheduler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("148BD527-A2AB-11CE-B11F-00AA00530503")
    ITaskScheduler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTargetComputer( 
            /* [in] */ LPCWSTR pwszComputer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTargetComputer( 
            /* [out] */ LPWSTR *ppwszComputer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Enum( 
            /* [out] */ IEnumWorkItems **ppEnumWorkItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Activate( 
            /* [in] */ LPCWSTR pwszName,
            /* [in] */ REFIID riid,
            /* [out] */ IUnknown **ppUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ LPCWSTR pwszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NewWorkItem( 
            /* [in] */ LPCWSTR pwszTaskName,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [out] */ IUnknown **ppUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddWorkItem( 
            /* [in] */ LPCWSTR pwszTaskName,
            /* [in] */ IScheduledWorkItem *pWorkItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsOfType( 
            /* [in] */ LPCWSTR pwszName,
            /* [in] */ REFIID riid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITaskSchedulerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITaskScheduler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITaskScheduler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITaskScheduler * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTargetComputer )( 
            ITaskScheduler * This,
            /* [in] */ LPCWSTR pwszComputer);
        
        HRESULT ( STDMETHODCALLTYPE *GetTargetComputer )( 
            ITaskScheduler * This,
            /* [out] */ LPWSTR *ppwszComputer);
        
        HRESULT ( STDMETHODCALLTYPE *Enum )( 
            ITaskScheduler * This,
            /* [out] */ IEnumWorkItems **ppEnumWorkItems);
        
        HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ITaskScheduler * This,
            /* [in] */ LPCWSTR pwszName,
            /* [in] */ REFIID riid,
            /* [out] */ IUnknown **ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE *Delete )( 
            ITaskScheduler * This,
            /* [in] */ LPCWSTR pwszName);
        
        HRESULT ( STDMETHODCALLTYPE *NewWorkItem )( 
            ITaskScheduler * This,
            /* [in] */ LPCWSTR pwszTaskName,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [out] */ IUnknown **ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE *AddWorkItem )( 
            ITaskScheduler * This,
            /* [in] */ LPCWSTR pwszTaskName,
            /* [in] */ IScheduledWorkItem *pWorkItem);
        
        HRESULT ( STDMETHODCALLTYPE *IsOfType )( 
            ITaskScheduler * This,
            /* [in] */ LPCWSTR pwszName,
            /* [in] */ REFIID riid);
        
        END_INTERFACE
    } ITaskSchedulerVtbl;

    interface ITaskScheduler
    {
        CONST_VTBL struct ITaskSchedulerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITaskScheduler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITaskScheduler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITaskScheduler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITaskScheduler_SetTargetComputer(This,pwszComputer)	\
    (This)->lpVtbl -> SetTargetComputer(This,pwszComputer)

#define ITaskScheduler_GetTargetComputer(This,ppwszComputer)	\
    (This)->lpVtbl -> GetTargetComputer(This,ppwszComputer)

#define ITaskScheduler_Enum(This,ppEnumWorkItems)	\
    (This)->lpVtbl -> Enum(This,ppEnumWorkItems)

#define ITaskScheduler_Activate(This,pwszName,riid,ppUnk)	\
    (This)->lpVtbl -> Activate(This,pwszName,riid,ppUnk)

#define ITaskScheduler_Delete(This,pwszName)	\
    (This)->lpVtbl -> Delete(This,pwszName)

#define ITaskScheduler_NewWorkItem(This,pwszTaskName,rclsid,riid,ppUnk)	\
    (This)->lpVtbl -> NewWorkItem(This,pwszTaskName,rclsid,riid,ppUnk)

#define ITaskScheduler_AddWorkItem(This,pwszTaskName,pWorkItem)	\
    (This)->lpVtbl -> AddWorkItem(This,pwszTaskName,pWorkItem)

#define ITaskScheduler_IsOfType(This,pwszName,riid)	\
    (This)->lpVtbl -> IsOfType(This,pwszName,riid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITaskScheduler_SetTargetComputer_Proxy( 
    ITaskScheduler * This,
    /* [in] */ LPCWSTR pwszComputer);


void __RPC_STUB ITaskScheduler_SetTargetComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_GetTargetComputer_Proxy( 
    ITaskScheduler * This,
    /* [out] */ LPWSTR *ppwszComputer);


void __RPC_STUB ITaskScheduler_GetTargetComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_Enum_Proxy( 
    ITaskScheduler * This,
    /* [out] */ IEnumWorkItems **ppEnumWorkItems);


void __RPC_STUB ITaskScheduler_Enum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_Activate_Proxy( 
    ITaskScheduler * This,
    /* [in] */ LPCWSTR pwszName,
    /* [in] */ REFIID riid,
    /* [out] */ IUnknown **ppUnk);


void __RPC_STUB ITaskScheduler_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_Delete_Proxy( 
    ITaskScheduler * This,
    /* [in] */ LPCWSTR pwszName);


void __RPC_STUB ITaskScheduler_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_NewWorkItem_Proxy( 
    ITaskScheduler * This,
    /* [in] */ LPCWSTR pwszTaskName,
    /* [in] */ REFCLSID rclsid,
    /* [in] */ REFIID riid,
    /* [out] */ IUnknown **ppUnk);


void __RPC_STUB ITaskScheduler_NewWorkItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_AddWorkItem_Proxy( 
    ITaskScheduler * This,
    /* [in] */ LPCWSTR pwszTaskName,
    /* [in] */ IScheduledWorkItem *pWorkItem);


void __RPC_STUB ITaskScheduler_AddWorkItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskScheduler_IsOfType_Proxy( 
    ITaskScheduler * This,
    /* [in] */ LPCWSTR pwszName,
    /* [in] */ REFIID riid);


void __RPC_STUB ITaskScheduler_IsOfType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITaskScheduler_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstask_0144 */
/* [local] */ 

EXTERN_C const CLSID CLSID_CTask;
EXTERN_C const CLSID CLSID_CTaskScheduler;
 
// {148BD520-A2AB-11CE-B11F-00AA00530503}
DEFINE_GUID(CLSID_CTask, 0x148BD520, 0xA2AB, 0x11CE, 0xB1, 0x1F, 0x00, 0xAA, 0x00, 0x53, 0x05, 0x03);
 
// {148BD52A-A2AB-11CE-B11F-00AA00530503}
DEFINE_GUID(CLSID_CTaskScheduler, 0x148BD52A, 0xA2AB, 0x11CE, 0xB1, 0x1F, 0x00, 0xAA, 0x00, 0x53, 0x05, 0x03);
 

typedef struct _PSP *HPROPSHEETPAGE;

typedef 
enum _TASKPAGE
    {	TASKPAGE_TASK	= 0,
	TASKPAGE_SCHEDULE	= 1,
	TASKPAGE_SETTINGS	= 2
    } 	TASKPAGE;

// {4086658a-cbbb-11cf-b604-00c04fd8d565}
DEFINE_GUID(IID_IProvideTaskPage, 0x4086658aL, 0xcbbb, 0x11cf, 0xb6, 0x04, 0x00, 0xc0, 0x4f, 0xd8, 0xd5, 0x65);



extern RPC_IF_HANDLE __MIDL_itf_mstask_0144_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0144_v0_0_s_ifspec;

#ifndef __IProvideTaskPage_INTERFACE_DEFINED__
#define __IProvideTaskPage_INTERFACE_DEFINED__

/* interface IProvideTaskPage */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IProvideTaskPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4086658a-cbbb-11cf-b604-00c04fd8d565")
    IProvideTaskPage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPage( 
            /* [in] */ TASKPAGE tpType,
            /* [in] */ BOOL fPersistChanges,
            /* [out] */ HPROPSHEETPAGE *phPage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProvideTaskPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProvideTaskPage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProvideTaskPage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProvideTaskPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPage )( 
            IProvideTaskPage * This,
            /* [in] */ TASKPAGE tpType,
            /* [in] */ BOOL fPersistChanges,
            /* [out] */ HPROPSHEETPAGE *phPage);
        
        END_INTERFACE
    } IProvideTaskPageVtbl;

    interface IProvideTaskPage
    {
        CONST_VTBL struct IProvideTaskPageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProvideTaskPage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProvideTaskPage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProvideTaskPage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProvideTaskPage_GetPage(This,tpType,fPersistChanges,phPage)	\
    (This)->lpVtbl -> GetPage(This,tpType,fPersistChanges,phPage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IProvideTaskPage_GetPage_Proxy( 
    IProvideTaskPage * This,
    /* [in] */ TASKPAGE tpType,
    /* [in] */ BOOL fPersistChanges,
    /* [out] */ HPROPSHEETPAGE *phPage);


void __RPC_STUB IProvideTaskPage_GetPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProvideTaskPage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mstask_0145 */
/* [local] */ 

#define ISchedulingAgent       ITaskScheduler
#define IEnumTasks             IEnumWorkItems
#define IID_ISchedulingAgent   IID_ITaskScheduler
#define CLSID_CSchedulingAgent CLSID_CTaskScheduler


extern RPC_IF_HANDLE __MIDL_itf_mstask_0145_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstask_0145_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


