// API_Wrapper.cpp : Implementation of CRR_COM_APIApp and DLL registration.

#include "stdafx.h"
#include "RR_COM_API.h"
#include "API_Wrapper.h"
#include "..\..\src\Size.h"

/////////////////////////////////////////////////////////////////////////////
//
void logIt(char *s)
{
	FILE *fp;

	if ((fp=fopen("c:\\roborealm.log", "a+t"))!=NULL)
	{
		fprintf(fp, "%s\n", s);
		fclose(fp);
	}
}

void logInt(int i)
{
	FILE *fp;

	if ((fp=fopen("c:\\roborealm.log", "a+t"))!=NULL)
	{
		fprintf(fp, "%d\n", i);
		fclose(fp);
	}
}

void API_Wrapper::SetVariant(VARIANT *var, int val)
{
	if (var->vt & VT_BYREF)
		*var->piVal = val;
	else
	{
		VariantInit( var );
		var->vt = VT_I4;
		var->iVal = val;
	}
}

int API_Wrapper::GetIntVariant(VARIANT *var)
{
	if (var->vt & VT_BYREF)
		return *var->piVal;
	else
		return var->iVal;
}

STDMETHODIMP API_Wrapper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IAPI_Wrapper,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP API_Wrapper::Connect(BSTR hostname, long *res)
{
	char host[256];
	wcstombs(host, hostname, 256);
	if (!host[0]) strcpy(host, "localhost");

	VariantInit( &null );
	null.vt = 0;

	if (rr.connect(host))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

STDMETHODIMP API_Wrapper::Disconnect(long *res)
{
	*res = -1;
	rr.disconnect();

	if (pixels)
	{
		free(pixels);
		pixels = NULL;
	}

	return S_OK;
}

STDMETHODIMP API_Wrapper::GetDimension(VARIANT *width, VARIANT *height, long *res)
{
	int w, h;
	if (rr.getDimension((int *)&w, (int *)&h))
		*res = -1;
	else
		*res = 0;

	SetVariant(width, w);
	SetVariant(height, h);

	return S_OK;
}

void API_Wrapper::SetImageVariant(VARIANT *image, unsigned char *pixels, int w, int h)
{
	SAFEARRAYBOUND sabound[1];
	SAFEARRAY FAR* psa;

	int len = w*h*3;

	if (image->vt & (VT_ARRAY | VT_BYREF | VT_UI1))
	{
		psa = *image->pparray;

		unsigned char* VarArray;

		::SafeArrayAccessData( psa, (void **) &VarArray );
		memcpy(VarArray, pixels, len);
		SafeArrayUnaccessData( psa );
	}
	else
	{
		// Build and return a Safe Array of Variants
		VariantInit( image );

		image->vt = VT_ARRAY | VT_VARIANT;
		// Create safearray of unsigned char.

		sabound[0].cElements = len;
		sabound[0].lLbound = 0;
		psa = SafeArrayCreate(VT_VARIANT, 1, sabound);
		if (psa == NULL) return;

		VARIANT * VarArray;
		::SafeArrayAccessData( psa, (void **) &VarArray );

		int i;
		for (i=0;i<len;i++)
		{
			VarArray[i].vt = VT_UI1;
			VarArray[i].bVal = pixels[i];
		}

		SafeArrayUnaccessData( psa );
		image->parray = psa;
	}
}

HRESULT API_Wrapper::GetImage(BSTR name, VARIANT *image, VARIANT *width, VARIANT *height, long *res)
{
	char n[256];
	unsigned int max = IMAGE_WIDTH*IMAGE_HEIGHT*3;
	wcstombs(n, name, 256);
	int w, h;

	if (pixels==NULL)
		pixels = (unsigned char *)malloc(max);

	if (rr.getImage(n, pixels, (int *)&w, (int *)&h, &max, "RGB"))
	{
		SetVariant(width, w);
		SetVariant(height, h);

		SetImageVariant(image, pixels, w, h);
		*res = -1;
	}
	else
	{
		*res = 0;
		SetVariant(width, 0);
		SetVariant(height, 0);
	}
	return S_OK;
}

int API_Wrapper::GetImageVariant(VARIANT *image, unsigned char *pixels)
{
	int max = IMAGE_WIDTH*IMAGE_HEIGHT*3;

	SAFEARRAY FAR* psa;
	if (image->vt&VT_BYREF)
	  psa = *image->pparray;
	else
	  psa = image->parray;

  HRESULT hr;
  long lLBound, lUBound;

	// Check dimensions of array

  if (SafeArrayGetDim(psa) != 1) return 0;

  // Get array bounds.
  hr = SafeArrayGetLBound(psa, 1, &lLBound);
  if (FAILED(hr)) return ResultFromScode(E_INVALIDARG);

  hr = SafeArrayGetUBound(psa, 1, &lUBound);
  if (FAILED(hr)) return ResultFromScode(E_INVALIDARG);

	int len = (lUBound-lLBound)*3;
	if (lUBound-lLBound<=max)
	{
		if (image->vt & VT_VARIANT)
		{
			VARIANT * VarArray;
			::SafeArrayAccessData( psa, (void **) &VarArray );
	 		int i;
 			for (i=lLBound;i<=lUBound;i++)
			{
				pixels[i] = 	VarArray[i].bVal;
			}

			SafeArrayUnaccessData( psa );
		}
		else
		if (image->vt & VT_UI1)
		{
			unsigned char *VarArray;
			::SafeArrayAccessData( psa, (void **) &VarArray );
	 		memcpy(&pixels[lLBound], &VarArray[lLBound], lUBound-lLBound);
			SafeArrayUnaccessData( psa );
		}

		return 1;
	}

	return 0;
}


HRESULT API_Wrapper::SetImage(BSTR name, VARIANT *image, VARIANT *width, VARIANT *height)
{
	char n[256];

	wcstombs(n, name, 256);

	if (((width->vt &VT_I4)==0)||((height->vt &VT_I4)==0))
	{
		return E_INVALIDARG;
	}

	if ((image->vt&VT_ARRAY)==0)
	{
		return E_INVALIDARG;
	}

	int max = IMAGE_WIDTH*IMAGE_HEIGHT*3;

	if (pixels==NULL)
		pixels = (unsigned char *)malloc(max);

	if (GetImageVariant(image, pixels))
	{
		rr.setImage(n, pixels, GetIntVariant(width), GetIntVariant(height));
	}

	return S_OK;
}

HRESULT API_Wrapper::SetExImage(BSTR name, VARIANT *image, VARIANT *width, VARIANT *height, bool wait, BSTR format)
{
	char n[256];

	wcstombs(n, name, 256);

	if (((width->vt &VT_I4)==0)||((height->vt &VT_I4)==0))
	{
		return E_INVALIDARG;
	}

	if ((image->vt&VT_ARRAY)==0)
	{
		return E_INVALIDARG;
	}

	int max = IMAGE_WIDTH*IMAGE_HEIGHT*3;

	if (pixels==NULL)
		pixels = (unsigned char *)malloc(max);

	char f[32];

 	::WideCharToMultiByte(CP_ACP, 0, format, -1, f, 32, NULL, NULL);

	if (GetImageVariant(image, pixels))
	{
		rr.setImage(n, pixels, GetIntVariant(width), GetIntVariant(height), wait, f);
	}

	return S_OK;
}

HRESULT API_Wrapper::GetVariable(BSTR name, BSTR *res)
{
  char n[MAX_PATH];
	char result[4096];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);

	if (rr.getVariable(n, result, 4096))
	{
		CComBSTR bstrInstallDir;
		bstrInstallDir.Append(result);
		*res = bstrInstallDir.Detach();
	}
	else
		*res = NULL;

	return S_OK;
}

HRESULT API_Wrapper::GetVariables(BSTR names, VARIANT *res)
{
  char n[MAX_PATH];
	char *result[32];
	int num;
	char resultBuffer[4096*32];
	int j;
	for (j=0;j<32;j++)
		result[j]=&resultBuffer[j*4096];

  ::WideCharToMultiByte(CP_ACP, 0, names, -1, n, MAX_PATH, NULL, NULL);

	if (num = rr.getVariables(n, result, 4096, 32))
	{
		SAFEARRAYBOUND sabound[1];
		SAFEARRAY FAR* psa;

		// Build and return a Safe Array of Variants
		VariantInit( &array );

		array.vt = VT_ARRAY | VT_VARIANT;

		// Create safearray of unsigned char.
		sabound[0].cElements = num;
		sabound[0].lLbound = 0;
		psa = SafeArrayCreate(VT_VARIANT, 1, sabound);
		if (psa == NULL)
		{
			*res = null;
			return S_OK;
		}

		VARIANT * VarArray;
		::SafeArrayAccessData( psa, (void **) &VarArray );

		int i;
		CComBSTR bstrInstallDir;
		for (i=0;i<num;i++)
		{
			VarArray[i].vt = VT_BSTR;
			bstrInstallDir = result[i];
			VarArray[i].bstrVal = bstrInstallDir.Detach();
		}

		SafeArrayUnaccessData( psa );
		array.parray = psa;
		*res = array;
	}
	else
		*res = null;

	return S_OK;
}

HRESULT API_Wrapper::SetVariable(BSTR name, BSTR value, long *res)
{
  char n[MAX_PATH];
	char v[4096];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);
  ::WideCharToMultiByte(CP_ACP, 0, value, -1, v, 4096, NULL, NULL);

	if (rr.setVariable(n, v))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::SetVariables(VARIANT *n, VARIANT *v, long *res)
{
	if (n->vt!=(VT_ARRAY|VT_VARIANT|VT_BYREF))
	{
		*res = -1;
		return ResultFromScode(E_INVALIDARG);
	}
	if (v->vt!=(VT_ARRAY|VT_VARIANT|VT_BYREF))
	{
		*res = -1;
		return ResultFromScode(E_INVALIDARG);
	}

  SAFEARRAY FAR* pnames = *n->pparray;
  SAFEARRAY FAR* pvalues = *v->pparray;
  HRESULT hr;
  long nLBound, nUBound;
  long vLBound, vUBound;

	// Check dimensions of array
  if (SafeArrayGetDim(pnames) != 1) return S_OK;
  if (SafeArrayGetDim(pvalues) != 1) return S_OK;

  // Get array bounds.
  hr = SafeArrayGetLBound(pnames, 1, &nLBound);
  if (FAILED(hr)) return ResultFromScode(E_INVALIDARG);

  hr = SafeArrayGetUBound(pnames, 1, &nUBound);
  if (FAILED(hr)) return ResultFromScode(E_INVALIDARG);

  // Get array bounds.
  hr = SafeArrayGetLBound(pvalues, 1, &vLBound);
  if (FAILED(hr)) return ResultFromScode(E_INVALIDARG);

  hr = SafeArrayGetUBound(pvalues, 1, &vUBound);
  if (FAILED(hr)) return ResultFromScode(E_INVALIDARG);

	// check that they are the same size
	if ((nUBound-nLBound)!=(vUBound-vLBound))
	{
		return ResultFromScode(E_INVALIDARG);
	}

	VARIANT *vArray, *nArray;
	::SafeArrayAccessData( pnames, (void **) &nArray );
	::SafeArrayAccessData( pvalues, (void **) &vArray );

  char *names[32];
  char *values[32];

	char nameBuffer[MAX_PATH*32];
	char valueBuffer[MAX_PATH*32];

	// write name and values array to a string array
	int i,j,p;
	for (p=0, i=nLBound, j=vLBound;(i<nUBound)&&(p<32);i++, j++)
	{
		if (nArray[i].vt==VT_BSTR)
		{
			names[p]=&nameBuffer[p*MAX_PATH];
			values[p]=&valueBuffer[p*4096];

			::WideCharToMultiByte(CP_ACP, 0, nArray[i].bstrVal, -1, names[p], MAX_PATH, NULL, NULL);

			switch (vArray[j].vt)
			{
				case VT_UI1:
				case VT_I1:
				case VT_UI2:
				case VT_UI4:
				case VT_I2:
				case VT_I4:
				case VT_BOOL:
					sprintf(values[p], "%d", vArray[j].iVal);
				break;
				case VT_BSTR:
					::WideCharToMultiByte(CP_ACP, 0, vArray[j].bstrVal, -1, values[p], MAX_PATH, NULL, NULL);
				break;
			}
			p++;
		}
	}

	SafeArrayUnaccessData(pnames);
	SafeArrayUnaccessData(pvalues);

	// call the API wrapper
	if (rr.setVariables(names, values, p))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::DeleteVariable(BSTR name, long *res)
{
  char n[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);

	if (rr.deleteVariable(n))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::Execute(BSTR str, long *res)
{
  char s[32768];

  ::WideCharToMultiByte(CP_ACP, 0, str, -1, s, 32768, NULL, NULL);

	if (rr.execute(s))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::LoadProgram(BSTR filename, long *res)
{
  char f[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, filename, -1, f, MAX_PATH, NULL, NULL);

	if (rr.loadProgram(f))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::SaveProgram(BSTR filename, long *res)
{
  char f[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, filename, -1, f, MAX_PATH, NULL, NULL);

	if (rr.saveProgram(f))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::LoadImage(BSTR name, BSTR filename, long *res)
{
  char n[MAX_PATH];
  char f[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);
  ::WideCharToMultiByte(CP_ACP, 0, filename, -1, f, MAX_PATH, NULL, NULL);

	if (rr.loadImage(n, f))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::SaveImage(BSTR name, BSTR filename, long *res)
{
  char n[MAX_PATH];
  char f[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);
  ::WideCharToMultiByte(CP_ACP, 0, filename, -1, f, MAX_PATH, NULL, NULL);

	if (rr.saveImage(n, f))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::SetCamera(BSTR name, long *res)
{
  char n[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);

	if (rr.setCamera(n))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::Run(BSTR name, long *res)
{
  char n[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);

	if (rr.run(n))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::WaitVariable(BSTR name, BSTR value, long timeout, long *res)
{
  char n[MAX_PATH];
  char v[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, name, -1, n, MAX_PATH, NULL, NULL);
  ::WideCharToMultiByte(CP_ACP, 0, value, -1, v, MAX_PATH, NULL, NULL);

	if (rr.waitVariable(n, v, timeout))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::WaitImage(long *res)
{
	if (rr.waitImage())
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::Open(BSTR filename, VARIANT *port, long *res)
{
  char f[MAX_PATH];

  ::WideCharToMultiByte(CP_ACP, 0, filename, -1, f, MAX_PATH, NULL, NULL);

	if (rr.open(f, GetIntVariant(port)))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::Close(long *res)
{
	if (rr.close())
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::LoadPPM(BSTR filename, VARIANT *image, VARIANT *width, VARIANT *height, long *res)
{
	char f[MAX_PATH];
	int max = IMAGE_WIDTH*IMAGE_HEIGHT*3;
	int w, h;

	wcstombs(f, filename, 256);

	if (pixels==NULL)
		pixels = (unsigned char *)malloc(max);

	if (rr.loadPPM(f, pixels, (int *)&w, (int *)&h, max))
	{
		SetVariant(width, w);
		SetVariant(height, h);

		SetImageVariant(image, pixels, w, h);
		*res = -1;
	}
	else
	{
		SetVariant(width, 0);
		SetVariant(height, 0);
		*res = 0;
	}

	return S_OK;
}

HRESULT API_Wrapper::SavePPM(BSTR filename, VARIANT *image, VARIANT *width, VARIANT *height, long *res)
{
	char f[MAX_PATH];
	int max = IMAGE_WIDTH*IMAGE_HEIGHT*3;

	wcstombs(f, filename, 256);

	if (((width->vt &VT_I4)==0)||((height->vt &VT_I4)==0))
	{
		return E_INVALIDARG;
	}

	if ((image->vt&VT_ARRAY)==0)
	{
		return E_INVALIDARG;
	}

	if (pixels==NULL)
		pixels = (unsigned char *)malloc(max);

	if (GetImageVariant(image, pixels))
	{
		rr.savePPM(f, pixels, GetIntVariant(width), GetIntVariant(height));
	}

	return S_OK;
}

HRESULT API_Wrapper::SetParameter(BSTR module, VARIANT *count, BSTR name, BSTR value, long *res)
{
	char n[MAX_PATH];
	char v[MAX_PATH];
	char m[MAX_PATH];

	wcstombs(n, name, 256);
	wcstombs(v, value, 256);
	wcstombs(m, module, 256);

	if ((count->vt&VT_I4)==0)
	{
		return E_INVALIDARG;
	}

	rr.setParameter(m, GetIntVariant(count), n, v);

	return S_OK;
}

HRESULT API_Wrapper::GetParameter(BSTR module, VARIANT *count, BSTR name, BSTR *res)
{
	char n[MAX_PATH];
	char r[MAX_PATH];
	char m[MAX_PATH];

	wcstombs(n, name, 256);
	wcstombs(m, module, 256);

	if ((count->vt&VT_I4)==0)
	{
		return E_INVALIDARG;
	}

	rr.getParameter(m, GetIntVariant(count), n, r, MAX_PATH);

	CComBSTR bstrInstallDir;
	bstrInstallDir.Append(r);
	*res = bstrInstallDir.Detach();

	return S_OK;
}

HRESULT API_Wrapper::MinimizeWindow(long *res)
{
	if (rr.minimizeWindow())
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::MaximizeWindow(long *res)
{
	if (rr.maximizeWindow())
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::MoveWindow(VARIANT *x, VARIANT *y, long *res)
{
	if (rr.moveWindow(GetIntVariant(x), GetIntVariant(y)))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::ResizeWindow(VARIANT *width, VARIANT *height, long *res)
{
	if (rr.resizeWindow(GetIntVariant(width), GetIntVariant(height)))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::PositionWindow(VARIANT *x, VARIANT *y, VARIANT *width, VARIANT *height, long *res)
{
	if (rr.positionWindow(GetIntVariant(x), GetIntVariant(y), GetIntVariant(width), GetIntVariant(height)))
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::Pause(long *res)
{
	if (rr.pause())
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

HRESULT API_Wrapper::Resume(long *res)
{
	if (rr.resume())
		*res = -1;
	else
		*res = 0;

	return S_OK;
}

