/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Apr 24 14:51:39 2011
 */
/* Compiler settings for C:\www\RoboRealm\API\COM\RR_COM_API.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


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

#ifndef __RR_COM_API_h__
#define __RR_COM_API_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAPI_Wrapper_FWD_DEFINED__
#define __IAPI_Wrapper_FWD_DEFINED__
typedef interface IAPI_Wrapper IAPI_Wrapper;
#endif 	/* __IAPI_Wrapper_FWD_DEFINED__ */


#ifndef __API_Wrapper_FWD_DEFINED__
#define __API_Wrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class API_Wrapper API_Wrapper;
#else
typedef struct API_Wrapper API_Wrapper;
#endif /* __cplusplus */

#endif 	/* __API_Wrapper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAPI_Wrapper_INTERFACE_DEFINED__
#define __IAPI_Wrapper_INTERFACE_DEFINED__

/* interface IAPI_Wrapper */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAPI_Wrapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3B82392-E613-4711-B619-E04555549903")
    IAPI_Wrapper : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ BSTR hostname,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDimension( 
            /* [out] */ VARIANT __RPC_FAR *width,
            /* [out] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ BSTR name,
            /* [out] */ VARIANT __RPC_FAR *image,
            /* [out] */ VARIANT __RPC_FAR *width,
            /* [out] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetImage( 
            /* [in] */ BSTR name,
            /* [in] */ VARIANT __RPC_FAR *image,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVariable( 
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVariable( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteVariable( 
            /* [in] */ BSTR name,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ BSTR str,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadProgram( 
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadImage( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveImage( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCamera( 
            /* [in] */ BSTR name,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ BSTR name,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitVariable( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            /* [in] */ long timeout,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitImage( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPPM( 
            /* [in] */ BSTR filename,
            /* [in] */ VARIANT __RPC_FAR *image,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SavePPM( 
            /* [in] */ BSTR filename,
            /* [in] */ VARIANT __RPC_FAR *image,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR hostname,
            /* [in] */ VARIANT __RPC_FAR *port,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVariables( 
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVariables( 
            /* [in] */ VARIANT __RPC_FAR *names,
            /* [in] */ VARIANT __RPC_FAR *values,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetParameter( 
            /* [in] */ BSTR mod,
            /* [in] */ VARIANT __RPC_FAR *count,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParameter( 
            /* [in] */ BSTR mod,
            /* [in] */ VARIANT __RPC_FAR *count,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MinimizeWindow( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MaximizeWindow( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveWindow( 
            /* [in] */ VARIANT __RPC_FAR *x,
            /* [in] */ VARIANT __RPC_FAR *y,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResizeWindow( 
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PositionWindow( 
            /* [in] */ VARIANT __RPC_FAR *x,
            /* [in] */ VARIANT __RPC_FAR *y,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveProgram( 
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Resume( 
            /* [retval][out] */ long __RPC_FAR *res) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAPI_WrapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAPI_Wrapper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAPI_Wrapper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR hostname,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDimension )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *width,
            /* [out] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImage )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [out] */ VARIANT __RPC_FAR *image,
            /* [out] */ VARIANT __RPC_FAR *width,
            /* [out] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImage )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ VARIANT __RPC_FAR *image,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVariable )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVariable )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteVariable )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR str,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadProgram )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadImage )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveImage )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCamera )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitVariable )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            /* [in] */ long timeout,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitImage )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadPPM )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR filename,
            /* [in] */ VARIANT __RPC_FAR *image,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SavePPM )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR filename,
            /* [in] */ VARIANT __RPC_FAR *image,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR hostname,
            /* [in] */ VARIANT __RPC_FAR *port,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVariables )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVariables )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *names,
            /* [in] */ VARIANT __RPC_FAR *values,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParameter )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR mod,
            /* [in] */ VARIANT __RPC_FAR *count,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParameter )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR mod,
            /* [in] */ VARIANT __RPC_FAR *count,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MinimizeWindow )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MaximizeWindow )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveWindow )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *x,
            /* [in] */ VARIANT __RPC_FAR *y,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResizeWindow )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PositionWindow )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *x,
            /* [in] */ VARIANT __RPC_FAR *y,
            /* [in] */ VARIANT __RPC_FAR *width,
            /* [in] */ VARIANT __RPC_FAR *height,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveProgram )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            IAPI_Wrapper __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *res);
        
        END_INTERFACE
    } IAPI_WrapperVtbl;

    interface IAPI_Wrapper
    {
        CONST_VTBL struct IAPI_WrapperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAPI_Wrapper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAPI_Wrapper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAPI_Wrapper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAPI_Wrapper_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAPI_Wrapper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAPI_Wrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAPI_Wrapper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAPI_Wrapper_Connect(This,hostname,res)	\
    (This)->lpVtbl -> Connect(This,hostname,res)

#define IAPI_Wrapper_Disconnect(This,res)	\
    (This)->lpVtbl -> Disconnect(This,res)

#define IAPI_Wrapper_GetDimension(This,width,height,res)	\
    (This)->lpVtbl -> GetDimension(This,width,height,res)

#define IAPI_Wrapper_GetImage(This,name,image,width,height,res)	\
    (This)->lpVtbl -> GetImage(This,name,image,width,height,res)

#define IAPI_Wrapper_SetImage(This,name,image,width,height)	\
    (This)->lpVtbl -> SetImage(This,name,image,width,height)

#define IAPI_Wrapper_GetVariable(This,name,value)	\
    (This)->lpVtbl -> GetVariable(This,name,value)

#define IAPI_Wrapper_SetVariable(This,name,value,res)	\
    (This)->lpVtbl -> SetVariable(This,name,value,res)

#define IAPI_Wrapper_DeleteVariable(This,name,res)	\
    (This)->lpVtbl -> DeleteVariable(This,name,res)

#define IAPI_Wrapper_Execute(This,str,res)	\
    (This)->lpVtbl -> Execute(This,str,res)

#define IAPI_Wrapper_LoadProgram(This,filename,res)	\
    (This)->lpVtbl -> LoadProgram(This,filename,res)

#define IAPI_Wrapper_LoadImage(This,name,filename,res)	\
    (This)->lpVtbl -> LoadImage(This,name,filename,res)

#define IAPI_Wrapper_SaveImage(This,name,filename,res)	\
    (This)->lpVtbl -> SaveImage(This,name,filename,res)

#define IAPI_Wrapper_SetCamera(This,name,res)	\
    (This)->lpVtbl -> SetCamera(This,name,res)

#define IAPI_Wrapper_Run(This,name,res)	\
    (This)->lpVtbl -> Run(This,name,res)

#define IAPI_Wrapper_WaitVariable(This,name,value,timeout,res)	\
    (This)->lpVtbl -> WaitVariable(This,name,value,timeout,res)

#define IAPI_Wrapper_WaitImage(This,res)	\
    (This)->lpVtbl -> WaitImage(This,res)

#define IAPI_Wrapper_LoadPPM(This,filename,image,width,height,res)	\
    (This)->lpVtbl -> LoadPPM(This,filename,image,width,height,res)

#define IAPI_Wrapper_SavePPM(This,filename,image,width,height,res)	\
    (This)->lpVtbl -> SavePPM(This,filename,image,width,height,res)

#define IAPI_Wrapper_Open(This,hostname,port,res)	\
    (This)->lpVtbl -> Open(This,hostname,port,res)

#define IAPI_Wrapper_Close(This,res)	\
    (This)->lpVtbl -> Close(This,res)

#define IAPI_Wrapper_GetVariables(This,name,value)	\
    (This)->lpVtbl -> GetVariables(This,name,value)

#define IAPI_Wrapper_SetVariables(This,names,values,res)	\
    (This)->lpVtbl -> SetVariables(This,names,values,res)

#define IAPI_Wrapper_SetParameter(This,mod,count,name,value,res)	\
    (This)->lpVtbl -> SetParameter(This,mod,count,name,value,res)

#define IAPI_Wrapper_GetParameter(This,mod,count,name,res)	\
    (This)->lpVtbl -> GetParameter(This,mod,count,name,res)

#define IAPI_Wrapper_MinimizeWindow(This,res)	\
    (This)->lpVtbl -> MinimizeWindow(This,res)

#define IAPI_Wrapper_MaximizeWindow(This,res)	\
    (This)->lpVtbl -> MaximizeWindow(This,res)

#define IAPI_Wrapper_MoveWindow(This,x,y,res)	\
    (This)->lpVtbl -> MoveWindow(This,x,y,res)

#define IAPI_Wrapper_ResizeWindow(This,width,height,res)	\
    (This)->lpVtbl -> ResizeWindow(This,width,height,res)

#define IAPI_Wrapper_PositionWindow(This,x,y,width,height,res)	\
    (This)->lpVtbl -> PositionWindow(This,x,y,width,height,res)

#define IAPI_Wrapper_SaveProgram(This,filename,res)	\
    (This)->lpVtbl -> SaveProgram(This,filename,res)

#define IAPI_Wrapper_Pause(This,res)	\
    (This)->lpVtbl -> Pause(This,res)

#define IAPI_Wrapper_Resume(This,res)	\
    (This)->lpVtbl -> Resume(This,res)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Connect_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR hostname,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Disconnect_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_GetDimension_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *width,
    /* [out] */ VARIANT __RPC_FAR *height,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_GetDimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_GetImage_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [out] */ VARIANT __RPC_FAR *image,
    /* [out] */ VARIANT __RPC_FAR *width,
    /* [out] */ VARIANT __RPC_FAR *height,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_GetImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SetImage_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ VARIANT __RPC_FAR *image,
    /* [in] */ VARIANT __RPC_FAR *width,
    /* [in] */ VARIANT __RPC_FAR *height);


void __RPC_STUB IAPI_Wrapper_SetImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_GetVariable_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ BSTR __RPC_FAR *value);


void __RPC_STUB IAPI_Wrapper_GetVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SetVariable_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR value,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SetVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_DeleteVariable_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_DeleteVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Execute_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR str,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_LoadProgram_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR filename,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_LoadProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_LoadImage_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR filename,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_LoadImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SaveImage_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR filename,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SaveImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SetCamera_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SetCamera_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Run_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_WaitVariable_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR value,
    /* [in] */ long timeout,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_WaitVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_WaitImage_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_WaitImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_LoadPPM_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR filename,
    /* [in] */ VARIANT __RPC_FAR *image,
    /* [in] */ VARIANT __RPC_FAR *width,
    /* [in] */ VARIANT __RPC_FAR *height,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_LoadPPM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SavePPM_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR filename,
    /* [in] */ VARIANT __RPC_FAR *image,
    /* [in] */ VARIANT __RPC_FAR *width,
    /* [in] */ VARIANT __RPC_FAR *height,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SavePPM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Open_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR hostname,
    /* [in] */ VARIANT __RPC_FAR *port,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Close_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_GetVariables_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT __RPC_FAR *value);


void __RPC_STUB IAPI_Wrapper_GetVariables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SetVariables_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *names,
    /* [in] */ VARIANT __RPC_FAR *values,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SetVariables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SetParameter_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR mod,
    /* [in] */ VARIANT __RPC_FAR *count,
    /* [in] */ BSTR name,
    /* [in] */ BSTR value,
    long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SetParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_GetParameter_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR mod,
    /* [in] */ VARIANT __RPC_FAR *count,
    /* [in] */ BSTR name,
    /* [retval][out] */ BSTR __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_GetParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_MinimizeWindow_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_MinimizeWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_MaximizeWindow_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_MaximizeWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_MoveWindow_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *x,
    /* [in] */ VARIANT __RPC_FAR *y,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_MoveWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_ResizeWindow_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *width,
    /* [in] */ VARIANT __RPC_FAR *height,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_ResizeWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_PositionWindow_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *x,
    /* [in] */ VARIANT __RPC_FAR *y,
    /* [in] */ VARIANT __RPC_FAR *width,
    /* [in] */ VARIANT __RPC_FAR *height,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_PositionWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_SaveProgram_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [in] */ BSTR filename,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_SaveProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Pause_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAPI_Wrapper_Resume_Proxy( 
    IAPI_Wrapper __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *res);


void __RPC_STUB IAPI_Wrapper_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAPI_Wrapper_INTERFACE_DEFINED__ */



#ifndef __RR_COM_APILib_LIBRARY_DEFINED__
#define __RR_COM_APILib_LIBRARY_DEFINED__

/* library RR_COM_APILib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RR_COM_APILib;

EXTERN_C const CLSID CLSID_API_Wrapper;

#ifdef __cplusplus

class DECLSPEC_UUID("5379A53A-B254-483B-9DA0-AF6BA0970BE3")
API_Wrapper;
#endif
#endif /* __RR_COM_APILib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
