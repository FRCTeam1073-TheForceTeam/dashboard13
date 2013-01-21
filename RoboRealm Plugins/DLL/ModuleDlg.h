////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2007, RoboRealm, all rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are NOT permitted.
//
// Refer to http://www.roborealm.com/registration/Source_Code_Agreement.html
// for license information.
////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ModuleDlg_H__C5647123_DDBE_404B_BD0B_95441968697E__INCLUDED_)
#define AFX_ModuleDlg_H__C5647123_DDBE_404B_BD0B_95441968697E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModuleDlg.h : header file
//

typedef void (*LPResizeFunc)(int w, int h, unsigned char **d, short int **t, unsigned char **m);


/////////////////////////////////////////////////////////////////////////////
// ModuleDlg dialog

#define IDD_DEFAULT 0
#define P_EXTENSION 10000

class ModuleDlg : public CDialog
{
	int returnFlags;
	HWND parentWnd;
	NameValueBuffer currentVariable;
	NameValueBuffer currentState;
	NameValueBuffer returnVariable;
	NameValueBuffer returnState;

// Construction
public:
	char urlBuffer[256];
	int imageNumber;
	bool hasDialog;
	char name[64];
	bool isActive;
	bool isInsert;
	char display[256];
	int width, height, left, top;
	LPResizeFunc resizeFunc;

  virtual enum { IDD = IDD_DEFAULT };

	ModuleDlg(int id, CWnd* pParent = NULL);   // standard constructor

	/*********************** State ***********************/

	void ResetState();
	void SetStateTable(char *value, int len);
	char *GetStateTable(int *len);
	int GetInt(char *name, int def=NULL);
	void SetInt(char *name, int value);
	float GetFloat(char *name, float def=NULL);
	void SetFloat(char *name, float value);
	void GetString(char *name, char *res, char *def=NULL);
	char *GetString(char *name);
	void GetString(char *name, CString *res, char *def=NULL);
	void SetString(char *name, CString *buffer);
	void SetString(char *name, char *buffer);
	void SetString(char *name, CComboBox *list, char *value);
	bool GetBool(char *name, bool def=NULL);
	void SetBool(char *name, bool value);
	void SetBool(char *name, BOOL value);
	void RemoveVariable(char *name);
	void SetArray(char *name, int *vals, int num);
	int GetArray(char *name, int *vals, int max);
	void SetResizeCallback(void *func);

	/*********************** API ***********************/

	virtual int GetProgramId();
	virtual char *GetDisplay();
	virtual char *GetName();
	virtual int GetIDD();
	virtual void SetSize(int w, int h);
	virtual void SetDimension(int x, int y, int w, int h);
	virtual void RefreshValues();
	virtual void SaveValues();
	virtual void LoadValues();
	virtual int Process(unsigned char *data, short int *tmpImage, unsigned char *tmpImage2, int left, int top, int width, int height);
	virtual void Annotate(unsigned char *data, short int *tmpImage, unsigned char *tmpImage2, int left, int top, int width, int height);
	virtual bool Initialize();
	virtual void Destroy();
	int getImageNumber();
	virtual void UpdateData(bool mode);
	virtual void UpdateImage();

	/*********************** Variables ***********************/

	void SetVariableTable(char *value, int len);
	char *GetVariableTable(int *len);
	void SetVariable(char *name, int *arr);
	void SetVariable(char *name, float *arr);
	void SetVariable(char *name, int i);
	void SetVariable(char *name, float f);
	void SetVariable(char *name, char *val);
	void SetVariable(char *name, CString *val);
	void SetVariable(char *name, char **val, int count);
	void SetVariable(char *name, int *arr, int size);
	void SetVariable(char *name, float *arr, int size);
	char *GetVariable(char *name);

	/*********************** Dialog Buttons ***********************/

  void SetNotify(HWND parent);
	void OnHelp(char *name);
	virtual void OnOK();
	virtual void OnCancel();

	/*********************** Utility ***********************/

	BSTR AsciiToBSTR(const char* pszFName);
	void AddVariable(CComboBox *list, char *s);
	int SetVariableSelect(CComboBox *list, char *tmp);
	void Resize(int w, int h, unsigned char **d, short int **t, unsigned char **m);

// Dialog Data
	//{{AFX_DATA(ModuleDlg)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(ModuleDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ModuleDlg_H__C5647123_DDBE_404B_BD0B_95441968697E__INCLUDED_)
