#include "Draw.h"

void Draw::destroyDC(CDC *MemDC, HBITMAP bitmap, unsigned char *data, int width, int height)
{
  struct
  {
	 BITMAPINFOHEADER bmiHeader;
	 RGBQUAD bmiColors[256];
  }
  bi;

	bi.bmiHeader.biWidth              = width;
	bi.bmiHeader.biHeight             = height;
	bi.bmiHeader.biSize               = sizeof(bi.bmiHeader);
	bi.bmiHeader.biPlanes             = 1;
	bi.bmiHeader.biBitCount           = 24;
	bi.bmiHeader.biCompression        = BI_RGB;
	bi.bmiHeader.biSizeImage          = width*height*3;
	bi.bmiHeader.biXPelsPerMeter      = 0;
	bi.bmiHeader.biYPelsPerMeter      = 0;
	bi.bmiHeader.biClrUsed            = 0;
	bi.bmiHeader.biClrImportant       = 0;

	GetDIBits(*MemDC, bitmap, 0, height, (LPVOID)data, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	MemDC->DeleteDC();
	//.res::ReleaseDC(NULL, *MemDC);
}

CDC *Draw::createDC(unsigned char *data, int width, int height, HBITMAP *bitmap)
{
	static CDC MemDC;
	HDC hDC = ::GetDC(NULL);
	CDC pDC;
	pDC.FromHandle(hDC);
	MemDC.CreateCompatibleDC(&pDC);

  struct
  {
	 BITMAPINFOHEADER bmiHeader;
	 RGBQUAD bmiColors[256];
  }
  bi;

	bi.bmiHeader.biWidth              = width;
	bi.bmiHeader.biHeight             = height;
	bi.bmiHeader.biSize               = sizeof(bi.bmiHeader);
	bi.bmiHeader.biPlanes             = 1;
	bi.bmiHeader.biBitCount           = 24;
	bi.bmiHeader.biCompression        = BI_RGB;
	bi.bmiHeader.biSizeImage          = width*height*3;
	bi.bmiHeader.biXPelsPerMeter      = 0;
	bi.bmiHeader.biYPelsPerMeter      = 0;
	bi.bmiHeader.biClrUsed            = 0;
	bi.bmiHeader.biClrImportant       = 0;

	*bitmap = CreateDIBSection(MemDC, (LPBITMAPINFO)&bi, DIB_RGB_COLORS, (void **)data, NULL, 0);
	HBITMAP oldHBitmap = (HBITMAP)SelectObject(MemDC, *bitmap);
	SetDIBits(MemDC, *bitmap, 0, height, (LPVOID)data, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	::ReleaseDC(NULL, hDC);

	return &MemDC;
}

void Draw::drawSquare(CDC *hdc, int x, int y, int xx, int yy, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(x, y);
  hdc->LineTo(xx, y);
  hdc->LineTo(xx, yy);
  hdc->LineTo(x, yy);
  hdc->LineTo(x, y);
}

void Draw::drawLine(CDC *hdc, int x, int y, int xx, int yy, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(x, y);
  hdc->LineTo(xx, yy);
}

void Draw::drawSquare(CDC *hdc, POINT *pt, int x, int y, int xx, int yy, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(pt->x+x, pt->y+y);
  hdc->LineTo(pt->x+xx, pt->y+y);
  hdc->LineTo(pt->x+xx, pt->y+yy);
  hdc->LineTo(pt->x+x, pt->y+yy);
  hdc->LineTo(pt->x+x, pt->y+y);
}

void Draw::drawLine(CDC *hdc, POINT *pt, int x, int y, int xx, int yy, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(pt->x+x, pt->y+y);
  hdc->LineTo(pt->x+xx, pt->y+yy);
}

void Draw::drawPoly(CDC *hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(x1, y1);
  hdc->LineTo(x2, y2);
  hdc->LineTo(x3, y3);
  hdc->LineTo(x4, y4);
  hdc->LineTo(x1, y1);
}

void Draw::drawArrow(CDC *hdc, POINT *pt, int x, int y, int xx, int yy, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(pt->x+x, pt->y+y);
  hdc->LineTo(pt->x+xx, pt->y+yy);

	// get angle
	float theta = (float)atan2((float)yy-y, (float)x-xx) + 0.7853975f;

	// rotate triangle around end point
	float tcos = (float)cos(theta);
	float tsin = (float)sin(theta);

	float atcos = (float)4.0f * tcos;
	float atsin = (float)4.0f * tsin;

	// determine other two coord
	int ax2 = (int)((float)xx+(atcos+0.5f));
	int ay2 = (int)((float)yy+(-atsin+0.5f));

	int ax3 = (int)((float)xx+(atsin+0.5f));
	int ay3 = (int)((float)yy+(atcos+0.5f));

  hdc->LineTo(pt->x+ax2, pt->y+ay2);
  hdc->LineTo(pt->x+ax3, pt->y+ay3);
  hdc->LineTo(pt->x+xx, pt->y+yy);
}

void Draw::drawArrow(CDC *hdc, int x, int y, int xx, int yy, HPEN pen)
{
	hdc->SelectObject(pen);
	hdc->MoveTo(x, y);
  hdc->LineTo(xx, yy);

	// get angle
	float theta = (float)atan2((float)yy-y, (float)x-xx) + 0.7853975f;

	// rotate triangle around end point
	float tcos = (float)cos(theta);
	float tsin = (float)sin(theta);

	float atcos = (float)4.0f * tcos;
	float atsin = (float)4.0f * tsin;

	// determine other two coord
	int ax2 = (int)((float)xx+(atcos+0.5f));
	int ay2 = (int)((float)yy+(-atsin+0.5f));

	int ax3 = (int)((float)xx+(atsin+0.5f));
	int ay3 = (int)((float)yy+(atcos+0.5f));

  hdc->LineTo(ax2, ay2);
  hdc->LineTo(ax3, ay3);
  hdc->LineTo(xx, yy);
}

void Draw::drawText(CDC *hdc, CFont *font, int x, int y, int xx, int yy, COLORREF foreColor, COLORREF backColor, char *text)
{
  hdc->SelectObject(font);
  hdc->SetTextColor(foreColor);
  hdc->SetBkColor(backColor);
	RECT sRect;
	sRect.top = y;
	sRect.right = x;
	sRect.bottom = yy;
	sRect.left = xx;
	hdc->DrawText(text, &sRect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);		// Draw out the caption
}
