// API_Wrapper.h: Definition of the API_Wrapper class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_API_WRAPPER_H__8FF22E4B_A633_4F0E_A1E8_1E22DAF3B879__INCLUDED_)
#define AFX_API_WRAPPER_H__8FF22E4B_A633_4F0E_A1E8_1E22DAF3B879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include "..\C++\MS Visual Studio\API\RR_API.h"

/////////////////////////////////////////////////////////////////////////////
// API_Wrapper

class API_Wrapper :
	public IDispatchImpl<IAPI_Wrapper, &IID_IAPI_Wrapper, &LIBID_RR_COM_APILib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<API_Wrapper,&CLSID_API_Wrapper>
{
public:
	API_Wrapper() { pixels = NULL; }
BEGIN_COM_MAP(API_Wrapper)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAPI_Wrapper)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(API_Wrapper)
// Remove the comment from the line above if you don't want your object to
// support aggregation.

DECLARE_REGISTRY_RESOURCEID(IDR_API_Wrapper)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	RR_API rr;
	unsigned char *pixels;
	VARIANT null;
	VARIANT array;

	void SetVariant(VARIANT *var, int val);
	int GetIntVariant(VARIANT *var);
	void SetImageVariant(VARIANT *image, unsigned char *pixels, int w, int h);
	int GetImageVariant(VARIANT *image, unsigned char *pixels);

// IAPI_Wrapper
public:

	STDMETHODIMP API_Wrapper::Connect(BSTR hostname, long *res);
	STDMETHODIMP API_Wrapper::Disconnect(long *res);
	STDMETHODIMP API_Wrapper::GetDimension(VARIANT *width, VARIANT *height, long *res);
	STDMETHODIMP API_Wrapper::GetImage(BSTR name, VARIANT *image, VARIANT *width, VARIANT *height, long *res);
	STDMETHODIMP API_Wrapper::SetImage(BSTR name, VARIANT *image, VARIANT *width, VARIANT *height);
	STDMETHODIMP API_Wrapper::SetExImage(BSTR name, VARIANT *image, VARIANT *width, VARIANT *height, bool wait, BSTR format);
	STDMETHODIMP API_Wrapper::GetVariable(BSTR name, BSTR *res);
	STDMETHODIMP API_Wrapper::SetVariable(BSTR name, BSTR value, long *res);
	STDMETHODIMP API_Wrapper::DeleteVariable(BSTR name, long *res);
	STDMETHODIMP API_Wrapper::Execute(BSTR str, long *res);
	STDMETHODIMP API_Wrapper::LoadProgram(BSTR value, long *res);
	STDMETHODIMP API_Wrapper::SaveProgram(BSTR value, long *res);
	STDMETHODIMP API_Wrapper::LoadImage(BSTR name, BSTR value, long *res);
	STDMETHODIMP API_Wrapper::SaveImage(BSTR name, BSTR value, long *res);
	STDMETHODIMP API_Wrapper::SetCamera(BSTR name, long *res);
	STDMETHODIMP API_Wrapper::Run(BSTR name, long *res);
	STDMETHODIMP API_Wrapper::WaitVariable(BSTR name, BSTR value, long timeout, long *res);
	STDMETHODIMP API_Wrapper::WaitImage(long *res);
	STDMETHODIMP API_Wrapper::Open(BSTR filename, VARIANT *port, long *res);
	STDMETHODIMP API_Wrapper::Close(long *res);
	STDMETHODIMP API_Wrapper::LoadPPM(BSTR filename, VARIANT *image, VARIANT *width, VARIANT *height, long *res);
	STDMETHODIMP API_Wrapper::SavePPM(BSTR filename, VARIANT *image, VARIANT *width, VARIANT *height, long *res);
	STDMETHODIMP API_Wrapper::GetVariables(BSTR name, VARIANT *res);
	STDMETHODIMP API_Wrapper::SetVariables(VARIANT *names, VARIANT *values, long *res);
	STDMETHODIMP API_Wrapper::SetParameter(BSTR module, VARIANT *count, BSTR name, BSTR value, long *res);
	STDMETHODIMP API_Wrapper::GetParameter(BSTR module, VARIANT *count, BSTR name, BSTR *res);
	STDMETHODIMP API_Wrapper::MinimizeWindow(long *res);
	STDMETHODIMP API_Wrapper::MaximizeWindow(long *res);
	STDMETHODIMP API_Wrapper::MoveWindow(VARIANT *x, VARIANT *y, long *res);
	STDMETHODIMP API_Wrapper::ResizeWindow(VARIANT *width, VARIANT *height, long *res);
	STDMETHODIMP API_Wrapper::PositionWindow(VARIANT *x, VARIANT *y, VARIANT *width, VARIANT *height, long *res);
	STDMETHODIMP API_Wrapper::Pause(long *res);
	STDMETHODIMP API_Wrapper::Resume(long *res);
};

#endif // !defined(AFX_API_WRAPPER_H__8FF22E4B_A633_4F0E_A1E8_1E22DAF3B879__INCLUDED_)
