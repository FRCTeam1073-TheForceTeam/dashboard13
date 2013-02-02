#pragma once

//Adapted from http://www.go4expert.com/forums/showthread.php?t=350

// CPictureBox
class CPictureBox : public CStatic
{
  DECLARE_DYNAMIC(CPictureBox)

public:
  CPictureBox();
  virtual ~CPictureBox();
  void SetBitmap(HBITMAP hBitmap);

protected:
  DECLARE_MESSAGE_MAP()
  void ShowBitmap(CPaintDC *pDC);

  CBitmap m_bmpBitmap;
  BITMAP bm;
public:

 afx_msg void OnPaint();
};