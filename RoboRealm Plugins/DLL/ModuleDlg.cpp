////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2007, RoboRealm, all rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are NOT permitted.
//
// Refer to http://www.roborealm.com/registration/Source_Code_Agreement.html
// for license information.
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ModuleDlg dialog
//
// Function:
// Provides utility routines for loading and saving configuration information
// and for some additional communication routines with RoboRealm. You should
// not modify this file.
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "resource.h"
#include "NameValueBuffer.h"
#include "ModuleDlg.h"
#include "Types.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_UPDATE_IMAGE 1868
#define IDC_ON_HELP 1869

#define DELETE_VALUE 255

ModuleDlg::ModuleDlg(int id, CWnd* pParent /*=NULL*/)
	: CDialog(id, pParent)
{
	//{{AFX_DATA_INIT(ModuleDlg)
	//}}AFX_DATA_INIT
  hasDialog=true;
	left=0;
	top=0;
  name[0]=0;
  display[0]=0;
	isActive=true;
	isInsert=true;
	width=320;
	height=240;
	returnFlags=0;
	resizeFunc=NULL;
}

void ModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ModuleDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ModuleDlg, CDialog)
	//{{AFX_MSG_MAP(ModuleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ModuleDlg message handlers

/*********************** State ***********************/

void ModuleDlg::ResetState()
{
	currentState.clear();
}

void ModuleDlg::SetStateTable(char *value, int len)
{
	currentState.set((unsigned char *)value, len);
	returnState.set((unsigned char *)value, len);
}

char *ModuleDlg::GetStateTable(int *len)
{
	*len = returnState.size();
	return returnState.getBuffer();
}

int ModuleDlg::GetInt(char *name, int def)
{
  char *txt = (char *)currentState.seek(name);
  if (txt==NULL)
  	return def;
  else
	  return (int)atoi(txt);
}

void ModuleDlg::SetInt(char *name, int value)
{
	returnState.append(name, value);
}

float ModuleDlg::GetFloat(char *name, float def)
{
  char *txt = (char *)currentState.seek(name);
  if (txt==NULL)
	  return def;
  else
	  return (float)atof(txt);
}

void ModuleDlg::SetFloat(char *name, float value)
{
  char buffer[16];
  sprintf(buffer, "%5.2f", value);
	returnState.append(name, buffer);
}

void ModuleDlg::GetString(char *name, char *res, char *def)
{
  char *txt = (char *)currentState.seek(name);
  if (txt!=NULL)
		strncpy(res, txt, 256);
	else
	{
		if (def!=NULL)
			strncpy(res, def, 256);
		else
			res[0]=0;
	}
}

char *ModuleDlg::GetString(char *name)
{
  return (char *)currentState.seek(name);
}

void ModuleDlg::GetString(char *name, CString *res, char *def)
{
  char *txt = (char *)currentState.seek(name);
  if (txt!=NULL)
		*res = txt;
	else
	{
		if (def)
			*res = def;
		else
			*res = "";
	}
}

void ModuleDlg::SetString(char *name, CString *buffer)
{
	if (!buffer->IsEmpty())
	  returnState.append(name, (char *)((LPCTSTR)*buffer));
}

void ModuleDlg::SetString(char *name, char *buffer)
{
	if (buffer[0])
		returnState.append(name, buffer);
}

void ModuleDlg::SetString(char *name, CComboBox *list, char *value)
{
	int ind;
	char text[64];

  if ((ind=list->GetCurSel())>=0)
  {
		if (value)
	    list->GetLBText(ind, value);
		else
		{
			value=text;
	    list->GetLBText(ind, text);
		}
	  returnState.append(name, value);
	}
}

bool ModuleDlg::GetBool(char *name, bool def)
{
  char *txt = (char *)currentState.seek(name);
  if (txt==NULL)
  	return def;
  else
  {
	  if (isalpha(txt[0]))
    {
      if (_stricmp(txt, "true")==0) return TRUE;
      if (_stricmp(txt, "false")==0) return FALSE;
      if (_stricmp(txt, "on")==0) return TRUE;
      if (_stricmp(txt, "off")==0) return FALSE;
      if (_stricmp(txt, "enabled")==0) return TRUE;
      if (_stricmp(txt, "disabled")==0) return FALSE;
      if (_stricmp(txt, "active")==0) return TRUE;
      if (_stricmp(txt, "inactive")==0) return FALSE;
      return FALSE;
    }

    return (atoi(txt)>=1);
  }
}

void ModuleDlg::SetBool(char *name, bool value)
{
  if (value)
    returnState.append(name, "TRUE");
  else
    returnState.append(name, "FALSE");
}

void ModuleDlg::SetBool(char *name, BOOL value)
{
  if (value!=0)
    returnState.append(name, "TRUE");
  else
    returnState.append(name, "FALSE");
}

void ModuleDlg::SetArray(char *name, int *vals, int num)
{
	int i;
	CString buffer;
	if (vals==NULL) return;
	if (num)
	{
		char temp[16];
		for (i=0;i<num;i++)
		{
			if (i>0) buffer+=",";
			_itoa(vals[i], temp, 10);
			buffer+=temp;
		}
	  returnState.append(name, (char *)((LPCTSTR)buffer));
	}
}

int ModuleDlg::GetArray(char *name, int *vals, int max)
{
	if (vals==NULL) return 0;
  char *txt = (char *)currentState.seek(name);
	if (txt==NULL) return 0;

	int i,j;
	int last=0;
	for (j=i=0;txt[i];i++)
	{
		if ((txt[i]==',')&&(j<max))
		{
			vals[j++]=atoi(&txt[last]);
			last=i+1;
		}
	}
	if (j<max) vals[j++]=atoi(&txt[last]);
	return j;
}

/*********************** API ***********************/

int ModuleDlg::GetProgramId()
{
  return 0;
}

char *ModuleDlg::GetDisplay()
{
  _snprintf(display, 256, "Blank");
  return display;
}

char *ModuleDlg::GetName()
{
  return "Blank";
}

int ModuleDlg::GetIDD()
{
  return IDD;
}

void ModuleDlg::SetSize(int w, int h)
{
  width=w;
  height=h;
}

void ModuleDlg::SetResizeCallback(void *func)
{
	resizeFunc = (LPResizeFunc)func;
}

void ModuleDlg::Resize(int w, int h, unsigned char **d, short int **t, unsigned char **m)
{
	if (resizeFunc) resizeFunc(w, h, d, t, m);
}

void ModuleDlg::SetDimension(int x, int y, int w, int h)
{
  left=x;
	top=y;
	width=w;
  height=h;
}

void ModuleDlg::RefreshValues()
{
}

void ModuleDlg::SaveValues()
{
}

void ModuleDlg::LoadValues()
{
}

int ModuleDlg::Process(unsigned char *data, short int *tmpImage, unsigned char *tmpImage2, int left, int top, int width, int height)
{
  return 1;
}

void ModuleDlg::Annotate(unsigned char *data, short int *tmpImage, unsigned char *tmpImage2, int left, int top, int width, int height)
{
}

bool ModuleDlg::Initialize()
{
	return TRUE;
}

void ModuleDlg::Destroy()
{
}

int ModuleDlg::getImageNumber()
{
  return imageNumber;
}

void ModuleDlg::UpdateData(bool mode)
{
  CDialog::UpdateData(mode);
  ::SendMessage(parentWnd, WM_COMMAND, IDC_UPDATE_IMAGE, 0);
}

void ModuleDlg::UpdateImage()
{
  ::SendMessage(parentWnd, WM_COMMAND, IDC_UPDATE_IMAGE, 0);
}

/*********************** Variables ***********************/

void ModuleDlg::SetVariableTable(char *value, int len)
{
	currentVariable.set((unsigned char *)value, len);
	returnVariable.clear();
}

char *ModuleDlg::GetVariableTable(int *len)
{
	*len = returnVariable.size();
	return returnVariable.getBuffer();
}

void ModuleDlg::SetVariable(char *name, int *arr)
{
	int len = (arr[0]+1)*sizeof(int);
	returnVariable.append(name, (char *)arr, len, INT_ARRAY_VALUE);
}

void ModuleDlg::SetVariable(char *name, float *arr)
{
	int len = (*((int *)&arr[0])+1)*sizeof(float);
	returnVariable.append(name, (char *)arr, len, FLOAT_ARRAY_VALUE);
}

void ModuleDlg::SetVariable(char *name, int *arr, int size)
{
	int len = (size+1)*sizeof(int);
	returnVariable.append(name, (char *)arr, len, INT_ARRAY_VALUE, size);
}

void ModuleDlg::SetVariable(char *name, float *arr, int size)
{
	int len = (size+1)*sizeof(float);
	returnVariable.append(name, (char *)arr, len, FLOAT_ARRAY_VALUE, size);
}

void ModuleDlg::SetVariable(char *name, int i)
{
	returnVariable.append(name, i);
}

void ModuleDlg::SetVariable(char *name, float f)
{
	returnVariable.append(name, f);
}

void ModuleDlg::SetVariable(char *name, char *val)
{
	returnVariable.append(name, val);
}

void ModuleDlg::SetVariable(char *name, char **val, int count)
{
	returnVariable.append(name, val, count);
}

void ModuleDlg::SetVariable(char *name, CString *val)
{
	returnVariable.append(name, (char *)(*(LPCTSTR *)val));
}

char *ModuleDlg::GetVariable(char *name)
{
	return currentVariable.seek(name);
}

void ModuleDlg::RemoveVariable(char *name)
{
  returnVariable.append(name, "", 0, DELETE_VALUE);
}

/*********************** Dialog Buttons ***********************/

void ModuleDlg::SetNotify(HWND p)
{
	parentWnd = p;
}

void ModuleDlg::OnHelp(char *name)
{
	strncpy(urlBuffer, name, 256);
  ::SendMessage(parentWnd, WM_COMMAND, IDC_ON_HELP, 0);
}

void ModuleDlg::OnOK()
{
	isActive = false;
  UpdateData(TRUE);

  SaveValues();

  CDialog::OnOK();
	isActive = true;

  ::SendMessage(parentWnd, WM_COMMAND, IDOK, 0);
}

void ModuleDlg::OnCancel()
{
	isActive = false;

	CDialog::OnCancel();

  if (!isInsert)
  {
    LoadValues();
		isActive = true;
		UpdateImage();
  }

  ::SendMessage(parentWnd, WM_COMMAND, IDCANCEL, 0);
}

/*********************** Utility ***********************/

BSTR ModuleDlg::AsciiToBSTR(const char* pszFName)
{
   WCHAR wszURL[4096];
   ::MultiByteToWideChar(CP_ACP, 0, pszFName, -1, wszURL, 4096);
   return SysAllocString(wszURL);
}

void ModuleDlg::AddVariable(CComboBox *list, char *s)
{
  int i;
  CString str;

  for (i=1;i<list->GetCount();i++)
  {
  	list->GetLBText(i, str);
	  if (strcmp((char *)((LPCTSTR)str), s)==0) i=1000;
  }
  if (i<=1000) list->AddString(s);
}

int ModuleDlg::SetVariableSelect(CComboBox *list, char *tmp)
{
  CString str;
  int i;

  if (tmp[0])
  {
    for (i=0;i<list->GetCount();i++)
    {
      list->GetLBText(i, str);
      if (strcmp((char *)((LPCTSTR)str), tmp)==0)
      {
        list->SetCurSel(i);
				return i;
      }
    }
    list->SetCurSel(list->AddString(tmp));
	  return list->GetCount()-1;
  }
	else
	{
		list->SetCurSel(0);
	}

  return 0;
}
