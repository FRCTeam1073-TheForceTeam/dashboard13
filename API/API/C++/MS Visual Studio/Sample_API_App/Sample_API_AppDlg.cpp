// Sample_API_AppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PictureBox.h"
#include "..\API\RR_API.h"
#include "Sample_API_App.h"
#include "Sample_API_AppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSample_API_AppDlg dialog

CSample_API_AppDlg::CSample_API_AppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSample_API_AppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSample_API_AppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hBitmap = NULL;
}

CSample_API_AppDlg::~CSample_API_AppDlg()
{
	if (hBitmap)	DeleteObject(hBitmap);
}

void CSample_API_AppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSample_API_AppDlg)
	DDX_Control(pDX, IDC_IMAGE, imageCtl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSample_API_AppDlg, CDialog)
	//{{AFX_MSG_MAP(CSample_API_AppDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET_IMAGE, OnGetImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSample_API_AppDlg message handlers

BOOL CSample_API_AppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSample_API_AppDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSample_API_AppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSample_API_AppDlg::OnGetImage() 
{
	int width, height;
	unsigned char *image = (unsigned char *)malloc(320*240*3);

	RR_API rr;

	// open up RoboRealm if it is not already running. Note you may need to change
	// the path on this.
	rr.open("c:\\www\\RoboRealm\\bin\\RoboRealm.exe", 6060);

	if (!rr.connect("localhost"))
	{
		printf("RoboRealm does not appear to be running.\nPlease run RoboRealm and try again.");
		exit(0);
	}

	if (hBitmap)	DeleteObject(hBitmap);

	hBitmap = rr.getBitmap("processed", image, &width, &height, 320*240*3);

	imageCtl.SetBitmap(hBitmap);

	rr.disconnect();

	free(image);
}
