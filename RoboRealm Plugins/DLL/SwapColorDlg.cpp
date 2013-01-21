// SwapColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <vfw.h>
#include "NameValueBuffer.h"
#include "ModuleDlg.h"
#include "SwapColorDlg.h"
#include "Draw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SwapColorDlg dialog
//
// Function:
// Provides an example module to swapping the color channels in an image
// being processed by RoboRealm.
//
// 1. You will need to update the RRModule.dll file each time you recompile
// this module. This file is already located in the RoboRealm.zip download.
// You can automate this process by changing the
//
//   Project->Settings->Debug->General->Executable for Debug Session
//
// path so that it overwrites the file in the RoboRealm folder.
// 2. To run this set the
//
//   Project->Settings->Debug->General->Working Directory
//
// to the RoboRealm folder and run this project.
// 3. RoboRealm show run and if you select
//
//   Extensions->SwapColor
//
// the interface to this module should appear. You can then set and breakpoints
// in this project to trap the execution.
/////////////////////////////////////////////////////////////////////////////

SwapColorDlg::SwapColorDlg(CWnd* pParent /*=NULL*/)
	: ModuleDlg(SwapColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SwapColorDlg)
	m_myText = _T("");
	//}}AFX_DATA_INIT
}

void SwapColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SwapColorDlg)
	DDX_Text(pDX, IDC_MYTEXT, m_myText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SwapColorDlg, CDialog)
	//{{AFX_MSG_MAP(SwapColorDlg)
	ON_BN_CLICKED(IDC_SHOW_HELP, OnHelp)
	ON_BN_CLICKED(IDC_SWAP_GB, OnSwapGb)
	ON_BN_CLICKED(IDC_SWAP_RB, OnSwapRb)
	ON_BN_CLICKED(IDC_SWAP_RG, OnSwapRg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SwapColorDlg message handlers

// Called on initialization of the dll
bool SwapColorDlg::Initialize()
{
  // tell RoboRealm that we have a GUI dialog
  hasDialog = true;

	// default to swapping R & B
	mode=1;
  ::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RB), BM_SETCHECK, 1, 0);

	redPen = CreatePen( PS_SOLID,	1, RGB(255,0,0));	// create pen
  font.CreateFont(24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Verdana");

	return true;
}

void SwapColorDlg::Destroy()
{
	// remove our global variable
	RemoveVariable("test");

	DeleteObject(redPen);
}

// used to indentify this plugin
char *SwapColorDlg::GetName()
{
  return "SwapColor";
}

// when the ok button is pressed this is called and used to indicate in the RoboRealm program pipeline
// what this module is. You can use this routine to include basic indicators that help the end user
// know what operation is being performed.
char *SwapColorDlg::GetDisplay()
{
	// configure our module text display in the pipeline
	_snprintf(display, 256, "SwapColor %s", (char *)((LPCSTR)m_myText));
  return display;
}

// The main image processing call.
// data - contains the current image data as BGR pixels
// tmp2Image - a temporary short int buffer than can be used for storage during image processing
// tmpImage - a temporary char buffer than can be used for storage during image processing
int SwapColorDlg::Process(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height)
{
  int i;
  int c;
	int len = width*height*3;

  // remember ... format is BGR (Blue, Green, Red) pixels
	if (mode==1)
	{
		// swap R and B
		for (i=0;i<len;i+=3)
		{
			c = data[i];
			data[i] = data[i+2];
			data[i+2] = c;
		}
	}
	else
	if (mode==2)
	{
		// swap R and G
		for (i=0;i<len;i+=3)
		{
			c = data[i+1];
			data[i+1] = data[i+2];
			data[i+2] = c;
		}
	}
	else
	{
		// swap G and B
		for (i=0;i<len;i+=3)
		{
			c = data[i];
			data[i] = data[i+1];
			data[i+1] = c;
		}
	}

	// set a global variable with myText's content
  SetVariable("test", &m_myText);

	// remove a global variable just for fun!
	RemoveVariable("IMAGE_WIDTH");

	// set a global variable array
  char *myArray[4];
	myArray[0]="string1";
	myArray[1]="string2";
	myArray[2]="string3";
	myArray[3]="string4";
	SetVariable("strings", myArray, 4);

	// set an integer array
	int myIntArray[4];
	myIntArray[0]=10;
	myIntArray[1]=20;
	myIntArray[2]=30;
	myIntArray[3]=40;
	SetVariable("ints", myIntArray, 4);

	// set a float array
	float myFloatArray[4];
	myFloatArray[0]=10;
	myFloatArray[1]=20;
	myFloatArray[2]=30;
	myFloatArray[3]=40;
	SetVariable("floats", myFloatArray, 4);

	//Resize the current image that is passed back to RoboRealm. Note data is preserved but not
	//realigned to new size. Note that tmp2Image and tmpImage may also be reallocated but will
	//NOT be preserved.
	//Resize(400,400,&data, &tmp2Image, &tmpImage);

  return 1;
}

// The annotation call. This is called after all processing routines are done to annotate the image .. i.e. draw lines, circles, etc.
// data - contains the current image data as BGR pixels
// tmp2Image - a temporary short int buffer than can be used for storage during image processing
// tmpImage - a temporary char buffer than can be used for storage during image processing
void SwapColorDlg::Annotate(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height)
{
	// example on how to use windows graphic api to draw a line into data (BGR pixel data)
	HBITMAP hBitmap;
	CDC *cdc = Draw::createDC(data, width, height, &hBitmap);

	// once we have the context based on the data array we can use any routine to draw to that buffer
	Draw::drawLine(cdc, 0, 0, 100, 100, redPen);

	// draw some text using Verdana font
	Draw::drawText(cdc, &font, 100, 100, 500, 150, RGB(255,255,255), RGB(0,0,0), "Hello from Example Plugin");

	// convert back from the cdc to data buffer.
	Draw::destroyDC(cdc, hBitmap, data, width, height);
}

// returns the IDD for this module. This is needed so that RoboRealm can correctly display the
// GUI dialog.
int SwapColorDlg::GetIDD()
{
  return IDD_SWAPCOLOR;
}

// Saves the current configuration values for this module. Note that you need to save all values every time
// in order for RoboRealm to correctly update the values. This is called when the RoboRealm needs to save
// your configuration information into a robofile.
void SwapColorDlg::SaveValues()
{
  // get current values from GUI
	UpdateData(TRUE);

	// reset state table to empty
	ResetState();

  // save the current text string to the state table
	SetString("my_text", &m_myText);

	SetInt("swap_mode", mode);
}

// Loads the configuration values back into your module.
void SwapColorDlg::LoadValues()
{
	GetString("my_text", &m_myText);
	mode = GetInt("swap_mode");

	// update values from GUI variables to GUI interface
  UpdateData(FALSE);

	// update radio button with appropriate value (they don't get auto updated by UpdateData)
	switch (mode)
	{
		case 1:
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RB), BM_SETCHECK, 1, 0);
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RG), BM_SETCHECK, 0, 0);
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_GB), BM_SETCHECK, 0, 0);
		break;
		case 2:
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RB), BM_SETCHECK, 0, 0);
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RG), BM_SETCHECK, 1, 0);
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_GB), BM_SETCHECK, 0, 0);
		break;
		case 3:
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RB), BM_SETCHECK, 0, 0);
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_RG), BM_SETCHECK, 0, 0);
			::SendMessage(::GetDlgItem(this->GetSafeHwnd(), IDC_SWAP_GB), BM_SETCHECK, 1, 0);
		break;
	}
}

// Specify a url that describes more about your module
void SwapColorDlg::OnHelp()
{
  ModuleDlg::OnHelp("http://www.roborealm.com/help/DLL_Program.php");
}

// called when the user clicks on Swap R B radio button
void SwapColorDlg::OnSwapRb()
{
	mode=1;
	// Tell RoboRealm to update the image if a static image is being processed
	UpdateImage();
}

void SwapColorDlg::OnSwapRg()
{
	mode=2;
	UpdateImage();
}

void SwapColorDlg::OnSwapGb()
{
	mode=3;
	UpdateImage();
}

