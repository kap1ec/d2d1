#pragma once

#include "Init.h" 

extern ID2D1HwndRenderTarget *pRenderTarget;

class CRenderObject
{
public:
	CRenderObject(LPCWSTR textureFilename);
	~CRenderObject();
	void draw();
	void setXY(float x, float y);
private:
	float m_x, m_y;
	ID2D1BitmapBrush *m_pBitmapBrush;
	ID2D1Bitmap *m_pBitmap;
	LPCWSTR m_textureFilename;
};

