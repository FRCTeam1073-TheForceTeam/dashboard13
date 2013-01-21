// Sample_API_App.h : main header file for the SAMPLE_API_APP application
//

#if !defined(AFX_SAMPLE_API_APP_H__8F0DF15B_D508_46DF_AD33_2307989712BA__INCLUDED_)
#define AFX_SAMPLE_API_APP_H__8F0DF15B_D508_46DF_AD33_2307989712BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSample_API_AppApp:
// See Sample_API_App.cpp for the implementation of this class
//

class CSample_API_AppApp : public CWinApp
{
public:
	CSample_API_AppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample_API_AppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSample_API_AppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE_API_APP_H__8F0DF15B_D508_46DF_AD33_2307989712BA__INCLUDED_)
