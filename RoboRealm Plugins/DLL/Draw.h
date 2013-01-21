#ifndef _DRAW
#define _DRAW 1

#include "stdafx.h"
#include "resource.h"
#include <Windows.h>
#include <vfw.h>
#include <Math.h>

class Draw
{
// Construction
public:
	static CDC *createDC(unsigned char *data, int width, int height, HBITMAP *bitmap);
	static void destroyDC(CDC *MemDC, HBITMAP bitmap, unsigned char *data, int width, int height);

	static void drawLine(CDC *hdc, int x, int y, int xx, int yy, HPEN pen);
	static void drawArrow(CDC *hdc, POINT *pt, int x, int y, int xx, int yy, HPEN pen);
	static void drawArrow(CDC *hdc, int x, int y, int xx, int yy, HPEN pen);
	static void drawLine(CDC *hdc, POINT *pt, int x, int y, int xx, int yy, HPEN pen);
	static void drawPoly(CDC *hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen);
	static void drawSquare(CDC *hdc, int x, int y, int xx, int yy, HPEN pen);
	static void drawSquare(CDC *hdc, POINT *pt, int x, int y, int xx, int yy, HPEN pen);
	static void drawText(CDC *hdc, CFont *font, int x, int y, int xx, int yy, COLORREF foreColor, COLORREF backColor, char *text);
};

#endif
