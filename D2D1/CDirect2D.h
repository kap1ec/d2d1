#pragma once
#include "Init.h" 
#include "RenderObject.h"

extern ID2D1HwndRenderTarget *pRenderTarget;

class CDirect2D
{
public:
	static CDirect2D * getInstance();
	void draw();
	void setHWND(HWND hwnd);
	void init();
	void createRenderObject(std::string objectName, LPCWSTR fileName);
	CRenderObject * getRenderObject(std::string objectName);
private:
	static CDirect2D * p_instance;

	CDirect2D();
	~CDirect2D();

	CDirect2D(const CDirect2D&) = delete;
	CDirect2D& operator=(CDirect2D&) = delete;

	HWND m_hwnd;

	//ID2D1HwndRenderTarget *m_pRenderTarget;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1SolidColorBrush * m_pBlackBrush;
	std::map<std::string, CRenderObject *> renderObjectsList;
	//CRenderObject *renderObj;
};

