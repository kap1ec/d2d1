#include "CDirect2D.h"


CDirect2D* CDirect2D::p_instance = 0;

template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
	)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


CDirect2D::CDirect2D()
{
	std::cout << "CDirect2D created \n";
}

CDirect2D::~CDirect2D()
{
}

CDirect2D * CDirect2D::getInstance(){
	if (!p_instance)
		p_instance = new CDirect2D();
	return p_instance;
}

void CDirect2D::setHWND(HWND hwnd) {
	m_hwnd = hwnd;
}

void CDirect2D::init(){

	std::cout << "Direct2D initialization: \n";
	assert(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory) == S_OK);
	std::cout << "d2d1 factory created \n";

	assert(m_hwnd);
	
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	HRESULT hr = m_pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&pRenderTarget);

	//pRenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Black),
	//	&m_pBlackBrush);

	//renderObj = new CRenderObject(L"test.png");

	//renderObjectsList = new std::vector<CRenderObject *>;
	//renderObjectsList.push_back(new CRenderObject(L"test.png"));
		
}

void CDirect2D::draw() {

	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	for (std::map<std::string, CRenderObject *>::iterator it = renderObjectsList.begin(); it != renderObjectsList.end(); ++it)
		it->second->draw();
	//renderObj->draw();
	//pRenderTarget->FillRectangle(D2D1::RectF(0, 0, 292, 282), m_pBitmapBrush);
	//pRenderTarget->DrawRectangle(
	//	D2D1::RectF(10, 10, 20, 20),
	//	m_pBlackBrush);

	pRenderTarget->EndDraw();
}

void CDirect2D::createRenderObject(std::string objectName, LPCWSTR fileName) {
	renderObjectsList.insert(std::pair<std::string, CRenderObject *>(objectName, new CRenderObject(fileName)));
	//renderObjectsList.push_back(new CRenderObject(fileName));
}

CRenderObject * CDirect2D::getRenderObject(std::string objectName)
{
	return renderObjectsList[objectName];
}
