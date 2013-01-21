// RRModule.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "NameValueBuffer.h"
#include "RRModule.h"
#include "ModuleDlg.h"
#include "SwapColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CRRModuleApp

BEGIN_MESSAGE_MAP(CRRModuleApp, CWinApp)
	//{{AFX_MSG_MAP(CRRModuleApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRRModuleApp construction

CRRModuleApp::CRRModuleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRRModuleApp object

CRRModuleApp theApp;

extern "C" __declspec(dllexport) ModuleDlg *CreateModule(LPCTSTR name, HWND parentWnd)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  // you could create different modules based on the name passed into this call
	SwapColorDlg *swap = new SwapColorDlg();
  swap->Create((const char *)swap->GetIDD());
	swap->SetNotify(parentWnd);

  return swap;//new SwapColorDlg();
}

extern "C" __declspec(dllexport) BOOL DisplayWindow(ModuleDlg *dlg, int cmd)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->ShowWindow(cmd);
}

extern "C" __declspec(dllexport) int GetIDD(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->GetIDD();
}

extern "C" __declspec(dllexport) void RefreshValues(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->RefreshValues();
}

extern "C" __declspec(dllexport) void SaveValues(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->SaveValues();
}

extern "C" __declspec(dllexport) void LoadValues(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->LoadValues();
}

extern "C" __declspec(dllexport) int Process(ModuleDlg *dlg, unsigned char *data, short int *tmp, unsigned char *tmp2, int left, int top, int width, int height, int imageNumber)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->imageNumber = imageNumber;

	return dlg->Process(data, tmp, tmp2, left, top, width, height);
}

extern "C" __declspec(dllexport) void Annotate(ModuleDlg *dlg, unsigned char *data, short int *tmp, unsigned char *tmp2, int left, int top, int width, int height)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->Annotate(data, tmp, tmp2, left, top, width, height);
}

extern "C" __declspec(dllexport) char *GetDisplay(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->GetDisplay();
}

extern "C" __declspec(dllexport) char *GetName(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->GetName();
}

extern "C" __declspec(dllexport) int GetProgramId(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->GetProgramId();
}

extern "C" __declspec(dllexport) void SetSize(ModuleDlg *dlg, int w, int h)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->SetSize(w, h);
}

extern "C" __declspec(dllexport) void SetDimension(ModuleDlg *dlg, int x, int y, int w, int h)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->SetDimension(x, y, w, h);
}

extern "C" __declspec(dllexport) bool Initialize(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->Initialize();
}

extern "C" __declspec(dllexport) void Destroy(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->Destroy();
}

extern "C" __declspec(dllexport) void SetVariableTable(ModuleDlg *dlg, char *values, int len)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->SetVariableTable(values, len);
}

extern "C" __declspec(dllexport) char *GetVariableTable(ModuleDlg *dlg, int *len)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->GetVariableTable(len);
}

extern "C" __declspec(dllexport) void SetStateTable(ModuleDlg *dlg, char *values, int len)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->SetStateTable(values, len);
}

extern "C" __declspec(dllexport) char *GetStateTable(ModuleDlg *dlg, int *len)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->GetStateTable(len);
}

extern "C" __declspec(dllexport) char *GetHelpUrl(ModuleDlg *dlg)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return dlg->urlBuffer;
}

extern "C" __declspec(dllexport) void SetResizeCallback(ModuleDlg *dlg, void *func)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	dlg->SetResizeCallback(func);
}

