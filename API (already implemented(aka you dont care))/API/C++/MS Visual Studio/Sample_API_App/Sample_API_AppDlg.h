// Sample_API_AppDlg.h : header file
//

#if !defined(AFX_SAMPLE_API_APPDLG_H__4F355D1C_AAC1_4D24_AE63_868AA4E4BA11__INCLUDED_)
#define AFX_SAMPLE_API_APPDLG_H__4F355D1C_AAC1_4D24_AE63_868AA4E4BA11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSample_API_AppDlg dialog

class CSample_API_AppDlg : public CDialog
{
	HBITMAP hBitmap;

// Construction
public:
	CSample_API_AppDlg(CWnd* pParent = NULL);	// standard constructor
	~CSample_API_AppDlg();	// standard destructor

// Dialog Data
	//{{AFX_DATA(CSample_API_AppDlg)
	enum { IDD = IDD_SAMPLE_API_APP_DIALOG };
	CPictureBox	imageCtl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample_API_AppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSample_API_AppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetImage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE_API_APPDLG_H__4F355D1C_AAC1_4D24_AE63_868AA4E4BA11__INCLUDED_)
