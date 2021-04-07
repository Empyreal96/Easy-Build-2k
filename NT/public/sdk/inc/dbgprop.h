

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* Compiler settings for dbgprop.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __dbgprop_h__
#define __dbgprop_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDebugProperty_FWD_DEFINED__
#define __IDebugProperty_FWD_DEFINED__
typedef interface IDebugProperty IDebugProperty;
#endif 	/* __IDebugProperty_FWD_DEFINED__ */


#ifndef __IEnumDebugPropertyInfo_FWD_DEFINED__
#define __IEnumDebugPropertyInfo_FWD_DEFINED__
typedef interface IEnumDebugPropertyInfo IEnumDebugPropertyInfo;
#endif 	/* __IEnumDebugPropertyInfo_FWD_DEFINED__ */


#ifndef __IDebugExtendedProperty_FWD_DEFINED__
#define __IDebugExtendedProperty_FWD_DEFINED__
typedef interface IDebugExtendedProperty IDebugExtendedProperty;
#endif 	/* __IDebugExtendedProperty_FWD_DEFINED__ */


#ifndef __IEnumDebugExtendedPropertyInfo_FWD_DEFINED__
#define __IEnumDebugExtendedPropertyInfo_FWD_DEFINED__
typedef interface IEnumDebugExtendedPropertyInfo IEnumDebugExtendedPropertyInfo;
#endif 	/* __IEnumDebugExtendedPropertyInfo_FWD_DEFINED__ */


#ifndef __IPerPropertyBrowsing2_FWD_DEFINED__
#define __IPerPropertyBrowsing2_FWD_DEFINED__
typedef interface IPerPropertyBrowsing2 IPerPropertyBrowsing2;
#endif 	/* __IPerPropertyBrowsing2_FWD_DEFINED__ */


#ifndef __IDebugPropertyEnumType_All_FWD_DEFINED__
#define __IDebugPropertyEnumType_All_FWD_DEFINED__
typedef interface IDebugPropertyEnumType_All IDebugPropertyEnumType_All;
#endif 	/* __IDebugPropertyEnumType_All_FWD_DEFINED__ */


#ifndef __IDebugPropertyEnumType_Locals_FWD_DEFINED__
#define __IDebugPropertyEnumType_Locals_FWD_DEFINED__
typedef interface IDebugPropertyEnumType_Locals IDebugPropertyEnumType_Locals;
#endif 	/* __IDebugPropertyEnumType_Locals_FWD_DEFINED__ */


#ifndef __IDebugPropertyEnumType_Arguments_FWD_DEFINED__
#define __IDebugPropertyEnumType_Arguments_FWD_DEFINED__
typedef interface IDebugPropertyEnumType_Arguments IDebugPropertyEnumType_Arguments;
#endif 	/* __IDebugPropertyEnumType_Arguments_FWD_DEFINED__ */


#ifndef __IDebugPropertyEnumType_LocalsPlusArgs_FWD_DEFINED__
#define __IDebugPropertyEnumType_LocalsPlusArgs_FWD_DEFINED__
typedef interface IDebugPropertyEnumType_LocalsPlusArgs IDebugPropertyEnumType_LocalsPlusArgs;
#endif 	/* __IDebugPropertyEnumType_LocalsPlusArgs_FWD_DEFINED__ */


#ifndef __IDebugPropertyEnumType_Registers_FWD_DEFINED__
#define __IDebugPropertyEnumType_Registers_FWD_DEFINED__
typedef interface IDebugPropertyEnumType_Registers IDebugPropertyEnumType_Registers;
#endif 	/* __IDebugPropertyEnumType_Registers_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_dbgprop_0000 */
/* [local] */ 






typedef 
enum tagOBJECT_ATTRIB_FLAG
    {	OBJECT_ATTRIB_NO_ATTRIB	= 0,
	OBJECT_ATTRIB_NO_NAME	= 0x1,
	OBJECT_ATTRIB_NO_TYPE	= 0x2,
	OBJECT_ATTRIB_NO_VALUE	= 0x4,
	OBJECT_ATTRIB_VALUE_IS_INVALID	= 0x8,
	OBJECT_ATTRIB_VALUE_IS_OBJECT	= 0x10,
	OBJECT_ATTRIB_VALUE_IS_ENUM	= 0x20,
	OBJECT_ATTRIB_VALUE_IS_CUSTOM	= 0x40,
	OBJECT_ATTRIB_OBJECT_IS_EXPANDABLE	= 0x70,
	OBJECT_ATTRIB_VALUE_HAS_CODE	= 0x80,
	OBJECT_ATTRIB_TYPE_IS_OBJECT	= 0x100,
	OBJECT_ATTRIB_TYPE_HAS_CODE	= 0x200,
	OBJECT_ATTRIB_TYPE_IS_EXPANDABLE	= 0x100,
	OBJECT_ATTRIB_SLOT_IS_CATEGORY	= 0x400,
	OBJECT_ATTRIB_VALUE_READONLY	= 0x800,
	OBJECT_ATTRIB_ACCESS_PUBLIC	= 0x1000,
	OBJECT_ATTRIB_ACCESS_PRIVATE	= 0x2000,
	OBJECT_ATTRIB_ACCESS_PROTECTED	= 0x4000,
	OBJECT_ATTRIB_ACCESS_FINAL	= 0x8000,
	OBJECT_ATTRIB_STORAGE_GLOBAL	= 0x10000,
	OBJECT_ATTRIB_STORAGE_STATIC	= 0x20000,
	OBJECT_ATTRIB_STORAGE_FIELD	= 0x40000,
	OBJECT_ATTRIB_STORAGE_VIRTUAL	= 0x80000,
	OBJECT_ATTRIB_TYPE_IS_CONSTANT	= 0x100000,
	OBJECT_ATTRIB_TYPE_IS_SYNCHRONIZED	= 0x200000,
	OBJECT_ATTRIB_TYPE_IS_VOLATILE	= 0x400000,
	OBJECT_ATTRIB_HAS_EXTENDED_ATTRIBS	= 0x800000,
	OBJECT_ATTRIB_IS_CLASS	= 0x1000000,
	OBJECT_ATTRIB_IS_FUNCTION	= 0x2000000,
	OBJECT_ATTRIB_IS_VARIABLE	= 0x4000000,
	OBJECT_ATTRIB_IS_PROPERTY	= 0x8000000,
	OBJECT_ATTRIB_IS_MACRO	= 0x10000000,
	OBJECT_ATTRIB_IS_TYPE	= 0x20000000,
	OBJECT_ATTRIB_IS_INHERITED	= 0x40000000,
	OBJECT_ATTRIB_IS_INTERFACE	= 0x80000000
    } 	OBJECT_ATTRIB_FLAGS;

typedef 
enum tagPROP_INFO_FLAGS
    {	PROP_INFO_NAME	= 0x1,
	PROP_INFO_TYPE	= 0x2,
	PROP_INFO_VALUE	= 0x4,
	PROP_INFO_FULLNAME	= 0x20,
	PROP_INFO_ATTRIBUTES	= 0x8,
	PROP_INFO_DEBUGPROP	= 0x10,
	PROP_INFO_AUTOEXPAND	= 0x8000000
    } 	PROP_INFO_FLAGS;

#define	PROP_INFO_STANDARD	( PROP_INFO_NAME | PROP_INFO_TYPE | PROP_INFO_VALUE | PROP_INFO_ATTRIBUTES )

#define	PROP_INFO_ALL	( PROP_INFO_NAME | PROP_INFO_TYPE | PROP_INFO_VALUE | PROP_INFO_FULLNAME | PROP_INFO_ATTRIBUTES | PROP_INFO_DEBUGPROP )

typedef struct tagDebugPropertyInfo
    {
    DWORD m_dwValidFields;
    BSTR m_bstrName;
    BSTR m_bstrType;
    BSTR m_bstrValue;
    BSTR m_bstrFullName;
    DWORD m_dwAttrib;
    IDebugProperty *m_pDebugProp;
    } 	DebugPropertyInfo;

typedef 
enum tagEX_PROP_INFO_FLAGS
    {	EX_PROP_INFO_ID	= 0x100,
	EX_PROP_INFO_NTYPE	= 0x200,
	EX_PROP_INFO_NVALUE	= 0x400,
	EX_PROP_INFO_LOCKBYTES	= 0x800,
	EX_PROP_INFO_DEBUGEXTPROP	= 0x1000
    } 	EX_PROP_INFO_FLAGS;

typedef struct tagExtendedDebugPropertyInfo
    {
    DWORD dwValidFields;
    LPOLESTR pszName;
    LPOLESTR pszType;
    LPOLESTR pszValue;
    LPOLESTR pszFullName;
    DWORD dwAttrib;
    IDebugProperty *pDebugProp;
    DWORD nDISPID;
    DWORD nType;
    VARIANT varValue;
    ILockBytes *plbValue;
    IDebugExtendedProperty *pDebugExtProp;
    } 	ExtendedDebugPropertyInfo;



extern RPC_IF_HANDLE __MIDL_itf_dbgprop_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dbgprop_0000_v0_0_s_ifspec;

#ifndef __IDebugProperty_INTERFACE_DEFINED__
#define __IDebugProperty_INTERFACE_DEFINED__

/* interface IDebugProperty */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C50-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugProperty : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetPropertyInfo( 
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ DebugPropertyInfo *pPropertyInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExtendedInfo( 
            /* [in] */ ULONG cInfos,
            /* [size_is][in] */ GUID *rgguidExtendedInfo,
            /* [size_is][out] */ VARIANT *rgvar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValueAsString( 
            /* [in] */ LPCOLESTR pszValue,
            /* [in] */ UINT nRadix) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMembers( 
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [in] */ REFIID refiid,
            /* [out] */ IEnumDebugPropertyInfo **ppepi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParent( 
            /* [out] */ IDebugProperty **ppDebugProp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDebugPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugProperty * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyInfo )( 
            IDebugProperty * This,
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ DebugPropertyInfo *pPropertyInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetExtendedInfo )( 
            IDebugProperty * This,
            /* [in] */ ULONG cInfos,
            /* [size_is][in] */ GUID *rgguidExtendedInfo,
            /* [size_is][out] */ VARIANT *rgvar);
        
        HRESULT ( STDMETHODCALLTYPE *SetValueAsString )( 
            IDebugProperty * This,
            /* [in] */ LPCOLESTR pszValue,
            /* [in] */ UINT nRadix);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMembers )( 
            IDebugProperty * This,
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [in] */ REFIID refiid,
            /* [out] */ IEnumDebugPropertyInfo **ppepi);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDebugProperty * This,
            /* [out] */ IDebugProperty **ppDebugProp);
        
        END_INTERFACE
    } IDebugPropertyVtbl;

    interface IDebugProperty
    {
        CONST_VTBL struct IDebugPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugProperty_GetPropertyInfo(This,dwFieldSpec,nRadix,pPropertyInfo)	\
    (This)->lpVtbl -> GetPropertyInfo(This,dwFieldSpec,nRadix,pPropertyInfo)

#define IDebugProperty_GetExtendedInfo(This,cInfos,rgguidExtendedInfo,rgvar)	\
    (This)->lpVtbl -> GetExtendedInfo(This,cInfos,rgguidExtendedInfo,rgvar)

#define IDebugProperty_SetValueAsString(This,pszValue,nRadix)	\
    (This)->lpVtbl -> SetValueAsString(This,pszValue,nRadix)

#define IDebugProperty_EnumMembers(This,dwFieldSpec,nRadix,refiid,ppepi)	\
    (This)->lpVtbl -> EnumMembers(This,dwFieldSpec,nRadix,refiid,ppepi)

#define IDebugProperty_GetParent(This,ppDebugProp)	\
    (This)->lpVtbl -> GetParent(This,ppDebugProp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDebugProperty_RemoteGetPropertyInfo_Proxy( 
    IDebugProperty * This,
    /* [in] */ DWORD dwFieldSpec,
    /* [in] */ UINT nRadix,
    /* [out] */ DWORD *dwValidFields,
    /* [out] */ BSTR *pbstrName,
    /* [out] */ BSTR *pbstrType,
    /* [out] */ BSTR *pbstrValue,
    /* [out] */ BSTR *pbstrFullName,
    /* [out] */ DWORD *pdwAttrib,
    /* [unique][out][in] */ IDebugProperty **ppDebugProperty);


void __RPC_STUB IDebugProperty_RemoteGetPropertyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDebugProperty_GetExtendedInfo_Proxy( 
    IDebugProperty * This,
    /* [in] */ ULONG cInfos,
    /* [size_is][in] */ GUID *rgguidExtendedInfo,
    /* [size_is][out] */ VARIANT *rgvar);


void __RPC_STUB IDebugProperty_GetExtendedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDebugProperty_SetValueAsString_Proxy( 
    IDebugProperty * This,
    /* [in] */ LPCOLESTR pszValue,
    /* [in] */ UINT nRadix);


void __RPC_STUB IDebugProperty_SetValueAsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDebugProperty_EnumMembers_Proxy( 
    IDebugProperty * This,
    /* [in] */ DWORD dwFieldSpec,
    /* [in] */ UINT nRadix,
    /* [in] */ REFIID refiid,
    /* [out] */ IEnumDebugPropertyInfo **ppepi);


void __RPC_STUB IDebugProperty_EnumMembers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDebugProperty_GetParent_Proxy( 
    IDebugProperty * This,
    /* [out] */ IDebugProperty **ppDebugProp);


void __RPC_STUB IDebugProperty_GetParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDebugProperty_INTERFACE_DEFINED__ */


#ifndef __IEnumDebugPropertyInfo_INTERFACE_DEFINED__
#define __IEnumDebugPropertyInfo_INTERFACE_DEFINED__

/* interface IEnumDebugPropertyInfo */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumDebugPropertyInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C51-CB0C-11d0-B5C9-00A0244A0E7A")
    IEnumDebugPropertyInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ DebugPropertyInfo *pi,
            /* [out] */ ULONG *pcEltsfetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDebugPropertyInfo **ppepi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *pcelt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumDebugPropertyInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDebugPropertyInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDebugPropertyInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDebugPropertyInfo * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDebugPropertyInfo * This,
            /* [in] */ ULONG celt,
            /* [out] */ DebugPropertyInfo *pi,
            /* [out] */ ULONG *pcEltsfetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDebugPropertyInfo * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDebugPropertyInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDebugPropertyInfo * This,
            /* [out] */ IEnumDebugPropertyInfo **ppepi);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumDebugPropertyInfo * This,
            /* [out] */ ULONG *pcelt);
        
        END_INTERFACE
    } IEnumDebugPropertyInfoVtbl;

    interface IEnumDebugPropertyInfo
    {
        CONST_VTBL struct IEnumDebugPropertyInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDebugPropertyInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumDebugPropertyInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumDebugPropertyInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumDebugPropertyInfo_Next(This,celt,pi,pcEltsfetched)	\
    (This)->lpVtbl -> Next(This,celt,pi,pcEltsfetched)

#define IEnumDebugPropertyInfo_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumDebugPropertyInfo_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumDebugPropertyInfo_Clone(This,ppepi)	\
    (This)->lpVtbl -> Clone(This,ppepi)

#define IEnumDebugPropertyInfo_GetCount(This,pcelt)	\
    (This)->lpVtbl -> GetCount(This,pcelt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT __stdcall IEnumDebugPropertyInfo_RemoteNext_Proxy( 
    IEnumDebugPropertyInfo * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][unique][out][in] */ DebugPropertyInfo *pinfo,
    /* [out] */ ULONG *pcEltsfetched);


void __RPC_STUB IEnumDebugPropertyInfo_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugPropertyInfo_Skip_Proxy( 
    IEnumDebugPropertyInfo * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumDebugPropertyInfo_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugPropertyInfo_Reset_Proxy( 
    IEnumDebugPropertyInfo * This);


void __RPC_STUB IEnumDebugPropertyInfo_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugPropertyInfo_Clone_Proxy( 
    IEnumDebugPropertyInfo * This,
    /* [out] */ IEnumDebugPropertyInfo **ppepi);


void __RPC_STUB IEnumDebugPropertyInfo_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugPropertyInfo_GetCount_Proxy( 
    IEnumDebugPropertyInfo * This,
    /* [out] */ ULONG *pcelt);


void __RPC_STUB IEnumDebugPropertyInfo_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumDebugPropertyInfo_INTERFACE_DEFINED__ */


#ifndef __IDebugExtendedProperty_INTERFACE_DEFINED__
#define __IDebugExtendedProperty_INTERFACE_DEFINED__

/* interface IDebugExtendedProperty */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugExtendedProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C52-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugExtendedProperty : public IDebugProperty
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetExtendedPropertyInfo( 
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ ExtendedDebugPropertyInfo *pExtendedPropertyInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumExtendedMembers( 
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ IEnumDebugExtendedPropertyInfo **ppeepi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDebugExtendedPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugExtendedProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugExtendedProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugExtendedProperty * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyInfo )( 
            IDebugExtendedProperty * This,
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ DebugPropertyInfo *pPropertyInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetExtendedInfo )( 
            IDebugExtendedProperty * This,
            /* [in] */ ULONG cInfos,
            /* [size_is][in] */ GUID *rgguidExtendedInfo,
            /* [size_is][out] */ VARIANT *rgvar);
        
        HRESULT ( STDMETHODCALLTYPE *SetValueAsString )( 
            IDebugExtendedProperty * This,
            /* [in] */ LPCOLESTR pszValue,
            /* [in] */ UINT nRadix);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMembers )( 
            IDebugExtendedProperty * This,
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [in] */ REFIID refiid,
            /* [out] */ IEnumDebugPropertyInfo **ppepi);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDebugExtendedProperty * This,
            /* [out] */ IDebugProperty **ppDebugProp);
        
        HRESULT ( STDMETHODCALLTYPE *GetExtendedPropertyInfo )( 
            IDebugExtendedProperty * This,
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ ExtendedDebugPropertyInfo *pExtendedPropertyInfo);
        
        HRESULT ( STDMETHODCALLTYPE *EnumExtendedMembers )( 
            IDebugExtendedProperty * This,
            /* [in] */ DWORD dwFieldSpec,
            /* [in] */ UINT nRadix,
            /* [out] */ IEnumDebugExtendedPropertyInfo **ppeepi);
        
        END_INTERFACE
    } IDebugExtendedPropertyVtbl;

    interface IDebugExtendedProperty
    {
        CONST_VTBL struct IDebugExtendedPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugExtendedProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugExtendedProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugExtendedProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugExtendedProperty_GetPropertyInfo(This,dwFieldSpec,nRadix,pPropertyInfo)	\
    (This)->lpVtbl -> GetPropertyInfo(This,dwFieldSpec,nRadix,pPropertyInfo)

#define IDebugExtendedProperty_GetExtendedInfo(This,cInfos,rgguidExtendedInfo,rgvar)	\
    (This)->lpVtbl -> GetExtendedInfo(This,cInfos,rgguidExtendedInfo,rgvar)

#define IDebugExtendedProperty_SetValueAsString(This,pszValue,nRadix)	\
    (This)->lpVtbl -> SetValueAsString(This,pszValue,nRadix)

#define IDebugExtendedProperty_EnumMembers(This,dwFieldSpec,nRadix,refiid,ppepi)	\
    (This)->lpVtbl -> EnumMembers(This,dwFieldSpec,nRadix,refiid,ppepi)

#define IDebugExtendedProperty_GetParent(This,ppDebugProp)	\
    (This)->lpVtbl -> GetParent(This,ppDebugProp)


#define IDebugExtendedProperty_GetExtendedPropertyInfo(This,dwFieldSpec,nRadix,pExtendedPropertyInfo)	\
    (This)->lpVtbl -> GetExtendedPropertyInfo(This,dwFieldSpec,nRadix,pExtendedPropertyInfo)

#define IDebugExtendedProperty_EnumExtendedMembers(This,dwFieldSpec,nRadix,ppeepi)	\
    (This)->lpVtbl -> EnumExtendedMembers(This,dwFieldSpec,nRadix,ppeepi)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDebugExtendedProperty_GetExtendedPropertyInfo_Proxy( 
    IDebugExtendedProperty * This,
    /* [in] */ DWORD dwFieldSpec,
    /* [in] */ UINT nRadix,
    /* [out] */ ExtendedDebugPropertyInfo *pExtendedPropertyInfo);


void __RPC_STUB IDebugExtendedProperty_GetExtendedPropertyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDebugExtendedProperty_EnumExtendedMembers_Proxy( 
    IDebugExtendedProperty * This,
    /* [in] */ DWORD dwFieldSpec,
    /* [in] */ UINT nRadix,
    /* [out] */ IEnumDebugExtendedPropertyInfo **ppeepi);


void __RPC_STUB IDebugExtendedProperty_EnumExtendedMembers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDebugExtendedProperty_INTERFACE_DEFINED__ */


#ifndef __IEnumDebugExtendedPropertyInfo_INTERFACE_DEFINED__
#define __IEnumDebugExtendedPropertyInfo_INTERFACE_DEFINED__

/* interface IEnumDebugExtendedPropertyInfo */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumDebugExtendedPropertyInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C53-CB0C-11d0-B5C9-00A0244A0E7A")
    IEnumDebugExtendedPropertyInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ExtendedDebugPropertyInfo *rgExtendedPropertyInfo,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDebugExtendedPropertyInfo **pedpe) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *pcelt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumDebugExtendedPropertyInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDebugExtendedPropertyInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDebugExtendedPropertyInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDebugExtendedPropertyInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDebugExtendedPropertyInfo * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ExtendedDebugPropertyInfo *rgExtendedPropertyInfo,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDebugExtendedPropertyInfo * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDebugExtendedPropertyInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDebugExtendedPropertyInfo * This,
            /* [out] */ IEnumDebugExtendedPropertyInfo **pedpe);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumDebugExtendedPropertyInfo * This,
            /* [out] */ ULONG *pcelt);
        
        END_INTERFACE
    } IEnumDebugExtendedPropertyInfoVtbl;

    interface IEnumDebugExtendedPropertyInfo
    {
        CONST_VTBL struct IEnumDebugExtendedPropertyInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDebugExtendedPropertyInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumDebugExtendedPropertyInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumDebugExtendedPropertyInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumDebugExtendedPropertyInfo_Next(This,celt,rgExtendedPropertyInfo,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgExtendedPropertyInfo,pceltFetched)

#define IEnumDebugExtendedPropertyInfo_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumDebugExtendedPropertyInfo_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumDebugExtendedPropertyInfo_Clone(This,pedpe)	\
    (This)->lpVtbl -> Clone(This,pedpe)

#define IEnumDebugExtendedPropertyInfo_GetCount(This,pcelt)	\
    (This)->lpVtbl -> GetCount(This,pcelt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumDebugExtendedPropertyInfo_Next_Proxy( 
    IEnumDebugExtendedPropertyInfo * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ ExtendedDebugPropertyInfo *rgExtendedPropertyInfo,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumDebugExtendedPropertyInfo_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugExtendedPropertyInfo_Skip_Proxy( 
    IEnumDebugExtendedPropertyInfo * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumDebugExtendedPropertyInfo_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugExtendedPropertyInfo_Reset_Proxy( 
    IEnumDebugExtendedPropertyInfo * This);


void __RPC_STUB IEnumDebugExtendedPropertyInfo_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugExtendedPropertyInfo_Clone_Proxy( 
    IEnumDebugExtendedPropertyInfo * This,
    /* [out] */ IEnumDebugExtendedPropertyInfo **pedpe);


void __RPC_STUB IEnumDebugExtendedPropertyInfo_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumDebugExtendedPropertyInfo_GetCount_Proxy( 
    IEnumDebugExtendedPropertyInfo * This,
    /* [out] */ ULONG *pcelt);


void __RPC_STUB IEnumDebugExtendedPropertyInfo_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumDebugExtendedPropertyInfo_INTERFACE_DEFINED__ */


#ifndef __IPerPropertyBrowsing2_INTERFACE_DEFINED__
#define __IPerPropertyBrowsing2_INTERFACE_DEFINED__

/* interface IPerPropertyBrowsing2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPerPropertyBrowsing2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C54-CB0C-11d0-B5C9-00A0244A0E7A")
    IPerPropertyBrowsing2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDisplayString( 
            /* [in] */ DISPID dispid,
            /* [out] */ BSTR *pBstr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapPropertyToPage( 
            /* [in] */ DISPID dispid,
            /* [out] */ CLSID *pClsidPropPage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPredefinedStrings( 
            /* [in] */ DISPID dispid,
            /* [out] */ CALPOLESTR *pCaStrings,
            /* [out] */ CADWORD *pCaCookies) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPredefinedValue( 
            /* [in] */ DISPID dispid,
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPerPropertyBrowsing2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPerPropertyBrowsing2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPerPropertyBrowsing2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPerPropertyBrowsing2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayString )( 
            IPerPropertyBrowsing2 * This,
            /* [in] */ DISPID dispid,
            /* [out] */ BSTR *pBstr);
        
        HRESULT ( STDMETHODCALLTYPE *MapPropertyToPage )( 
            IPerPropertyBrowsing2 * This,
            /* [in] */ DISPID dispid,
            /* [out] */ CLSID *pClsidPropPage);
        
        HRESULT ( STDMETHODCALLTYPE *GetPredefinedStrings )( 
            IPerPropertyBrowsing2 * This,
            /* [in] */ DISPID dispid,
            /* [out] */ CALPOLESTR *pCaStrings,
            /* [out] */ CADWORD *pCaCookies);
        
        HRESULT ( STDMETHODCALLTYPE *SetPredefinedValue )( 
            IPerPropertyBrowsing2 * This,
            /* [in] */ DISPID dispid,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IPerPropertyBrowsing2Vtbl;

    interface IPerPropertyBrowsing2
    {
        CONST_VTBL struct IPerPropertyBrowsing2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPerPropertyBrowsing2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPerPropertyBrowsing2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPerPropertyBrowsing2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPerPropertyBrowsing2_GetDisplayString(This,dispid,pBstr)	\
    (This)->lpVtbl -> GetDisplayString(This,dispid,pBstr)

#define IPerPropertyBrowsing2_MapPropertyToPage(This,dispid,pClsidPropPage)	\
    (This)->lpVtbl -> MapPropertyToPage(This,dispid,pClsidPropPage)

#define IPerPropertyBrowsing2_GetPredefinedStrings(This,dispid,pCaStrings,pCaCookies)	\
    (This)->lpVtbl -> GetPredefinedStrings(This,dispid,pCaStrings,pCaCookies)

#define IPerPropertyBrowsing2_SetPredefinedValue(This,dispid,dwCookie)	\
    (This)->lpVtbl -> SetPredefinedValue(This,dispid,dwCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPerPropertyBrowsing2_GetDisplayString_Proxy( 
    IPerPropertyBrowsing2 * This,
    /* [in] */ DISPID dispid,
    /* [out] */ BSTR *pBstr);


void __RPC_STUB IPerPropertyBrowsing2_GetDisplayString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPerPropertyBrowsing2_MapPropertyToPage_Proxy( 
    IPerPropertyBrowsing2 * This,
    /* [in] */ DISPID dispid,
    /* [out] */ CLSID *pClsidPropPage);


void __RPC_STUB IPerPropertyBrowsing2_MapPropertyToPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPerPropertyBrowsing2_GetPredefinedStrings_Proxy( 
    IPerPropertyBrowsing2 * This,
    /* [in] */ DISPID dispid,
    /* [out] */ CALPOLESTR *pCaStrings,
    /* [out] */ CADWORD *pCaCookies);


void __RPC_STUB IPerPropertyBrowsing2_GetPredefinedStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPerPropertyBrowsing2_SetPredefinedValue_Proxy( 
    IPerPropertyBrowsing2 * This,
    /* [in] */ DISPID dispid,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IPerPropertyBrowsing2_SetPredefinedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPerPropertyBrowsing2_INTERFACE_DEFINED__ */


#ifndef __IDebugPropertyEnumType_All_INTERFACE_DEFINED__
#define __IDebugPropertyEnumType_All_INTERFACE_DEFINED__

/* interface IDebugPropertyEnumType_All */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugPropertyEnumType_All;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C55-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugPropertyEnumType_All : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ BSTR *__MIDL_0011) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDebugPropertyEnumType_AllVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugPropertyEnumType_All * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugPropertyEnumType_All * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugPropertyEnumType_All * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IDebugPropertyEnumType_All * This,
            /* [out] */ BSTR *__MIDL_0011);
        
        END_INTERFACE
    } IDebugPropertyEnumType_AllVtbl;

    interface IDebugPropertyEnumType_All
    {
        CONST_VTBL struct IDebugPropertyEnumType_AllVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugPropertyEnumType_All_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugPropertyEnumType_All_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugPropertyEnumType_All_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugPropertyEnumType_All_GetName(This,__MIDL_0011)	\
    (This)->lpVtbl -> GetName(This,__MIDL_0011)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDebugPropertyEnumType_All_GetName_Proxy( 
    IDebugPropertyEnumType_All * This,
    /* [out] */ BSTR *__MIDL_0011);


void __RPC_STUB IDebugPropertyEnumType_All_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDebugPropertyEnumType_All_INTERFACE_DEFINED__ */


#ifndef __IDebugPropertyEnumType_Locals_INTERFACE_DEFINED__
#define __IDebugPropertyEnumType_Locals_INTERFACE_DEFINED__

/* interface IDebugPropertyEnumType_Locals */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugPropertyEnumType_Locals;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C56-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugPropertyEnumType_Locals : public IDebugPropertyEnumType_All
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDebugPropertyEnumType_LocalsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugPropertyEnumType_Locals * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugPropertyEnumType_Locals * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugPropertyEnumType_Locals * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IDebugPropertyEnumType_Locals * This,
            /* [out] */ BSTR *__MIDL_0011);
        
        END_INTERFACE
    } IDebugPropertyEnumType_LocalsVtbl;

    interface IDebugPropertyEnumType_Locals
    {
        CONST_VTBL struct IDebugPropertyEnumType_LocalsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugPropertyEnumType_Locals_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugPropertyEnumType_Locals_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugPropertyEnumType_Locals_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugPropertyEnumType_Locals_GetName(This,__MIDL_0011)	\
    (This)->lpVtbl -> GetName(This,__MIDL_0011)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDebugPropertyEnumType_Locals_INTERFACE_DEFINED__ */


#ifndef __IDebugPropertyEnumType_Arguments_INTERFACE_DEFINED__
#define __IDebugPropertyEnumType_Arguments_INTERFACE_DEFINED__

/* interface IDebugPropertyEnumType_Arguments */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugPropertyEnumType_Arguments;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C57-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugPropertyEnumType_Arguments : public IDebugPropertyEnumType_All
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDebugPropertyEnumType_ArgumentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugPropertyEnumType_Arguments * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugPropertyEnumType_Arguments * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugPropertyEnumType_Arguments * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IDebugPropertyEnumType_Arguments * This,
            /* [out] */ BSTR *__MIDL_0011);
        
        END_INTERFACE
    } IDebugPropertyEnumType_ArgumentsVtbl;

    interface IDebugPropertyEnumType_Arguments
    {
        CONST_VTBL struct IDebugPropertyEnumType_ArgumentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugPropertyEnumType_Arguments_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugPropertyEnumType_Arguments_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugPropertyEnumType_Arguments_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugPropertyEnumType_Arguments_GetName(This,__MIDL_0011)	\
    (This)->lpVtbl -> GetName(This,__MIDL_0011)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDebugPropertyEnumType_Arguments_INTERFACE_DEFINED__ */


#ifndef __IDebugPropertyEnumType_LocalsPlusArgs_INTERFACE_DEFINED__
#define __IDebugPropertyEnumType_LocalsPlusArgs_INTERFACE_DEFINED__

/* interface IDebugPropertyEnumType_LocalsPlusArgs */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugPropertyEnumType_LocalsPlusArgs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C58-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugPropertyEnumType_LocalsPlusArgs : public IDebugPropertyEnumType_All
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDebugPropertyEnumType_LocalsPlusArgsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugPropertyEnumType_LocalsPlusArgs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugPropertyEnumType_LocalsPlusArgs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugPropertyEnumType_LocalsPlusArgs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IDebugPropertyEnumType_LocalsPlusArgs * This,
            /* [out] */ BSTR *__MIDL_0011);
        
        END_INTERFACE
    } IDebugPropertyEnumType_LocalsPlusArgsVtbl;

    interface IDebugPropertyEnumType_LocalsPlusArgs
    {
        CONST_VTBL struct IDebugPropertyEnumType_LocalsPlusArgsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugPropertyEnumType_LocalsPlusArgs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugPropertyEnumType_LocalsPlusArgs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugPropertyEnumType_LocalsPlusArgs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugPropertyEnumType_LocalsPlusArgs_GetName(This,__MIDL_0011)	\
    (This)->lpVtbl -> GetName(This,__MIDL_0011)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDebugPropertyEnumType_LocalsPlusArgs_INTERFACE_DEFINED__ */


#ifndef __IDebugPropertyEnumType_Registers_INTERFACE_DEFINED__
#define __IDebugPropertyEnumType_Registers_INTERFACE_DEFINED__

/* interface IDebugPropertyEnumType_Registers */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDebugPropertyEnumType_Registers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51973C59-CB0C-11d0-B5C9-00A0244A0E7A")
    IDebugPropertyEnumType_Registers : public IDebugPropertyEnumType_All
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDebugPropertyEnumType_RegistersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDebugPropertyEnumType_Registers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDebugPropertyEnumType_Registers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDebugPropertyEnumType_Registers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IDebugPropertyEnumType_Registers * This,
            /* [out] */ BSTR *__MIDL_0011);
        
        END_INTERFACE
    } IDebugPropertyEnumType_RegistersVtbl;

    interface IDebugPropertyEnumType_Registers
    {
        CONST_VTBL struct IDebugPropertyEnumType_RegistersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDebugPropertyEnumType_Registers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDebugPropertyEnumType_Registers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDebugPropertyEnumType_Registers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDebugPropertyEnumType_Registers_GetName(This,__MIDL_0011)	\
    (This)->lpVtbl -> GetName(This,__MIDL_0011)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDebugPropertyEnumType_Registers_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* [local] */ HRESULT STDMETHODCALLTYPE IDebugProperty_GetPropertyInfo_Proxy( 
    IDebugProperty * This,
    /* [in] */ DWORD dwFieldSpec,
    /* [in] */ UINT nRadix,
    /* [out] */ DebugPropertyInfo *pPropertyInfo);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDebugProperty_GetPropertyInfo_Stub( 
    IDebugProperty * This,
    /* [in] */ DWORD dwFieldSpec,
    /* [in] */ UINT nRadix,
    /* [out] */ DWORD *dwValidFields,
    /* [out] */ BSTR *pbstrName,
    /* [out] */ BSTR *pbstrType,
    /* [out] */ BSTR *pbstrValue,
    /* [out] */ BSTR *pbstrFullName,
    /* [out] */ DWORD *pdwAttrib,
    /* [unique][out][in] */ IDebugProperty **ppDebugProperty);

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumDebugPropertyInfo_Next_Proxy( 
    IEnumDebugPropertyInfo * This,
    /* [in] */ ULONG celt,
    /* [out] */ DebugPropertyInfo *pi,
    /* [out] */ ULONG *pcEltsfetched);


/* [call_as] */ HRESULT __stdcall IEnumDebugPropertyInfo_Next_Stub( 
    IEnumDebugPropertyInfo * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][unique][out][in] */ DebugPropertyInfo *pinfo,
    /* [out] */ ULONG *pcEltsfetched);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


