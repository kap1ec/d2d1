#include "RenderObject.h"

CRenderObject::CRenderObject(LPCWSTR textureFilename) :
	m_textureFilename(textureFilename)
{	
	m_x = m_y = 0;

	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;
	IWICImagingFactory *pIWICFactory;

	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory
		);

	if (!SUCCEEDED(hr)) 
		std::cout << "CoCreateInstance Err \n";
	

	hr = pIWICFactory->CreateDecoderFromFilename(
		m_textureFilename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	if (!SUCCEEDED(hr))
		std::cout << "CreateDecoderFromFilename Err \n";

	hr = pDecoder->GetFrame(0, &pSource);

	if (!SUCCEEDED(hr))
		std::cout << "GetFrame Err \n";

	hr = pIWICFactory->CreateFormatConverter(&pConverter);

	if (!SUCCEEDED(hr))
		std::cout << "CreateDecoderFromFilename Err \n";

	hr = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
		);

	if (!SUCCEEDED(hr))
		std::cout << "Initialize Err \n";

	hr = pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&m_pBitmap
		);

	if (!SUCCEEDED(hr))
		std::cout << "CreateBitmapFromWicBitmap Err \n";

	hr = pRenderTarget->CreateBitmapBrush(
		m_pBitmap,
		&m_pBitmapBrush
		);

	if (!SUCCEEDED(hr))
		std::cout << "CreateBitmapBrush Err \n";
}


CRenderObject::~CRenderObject()
{
}

void CRenderObject::draw() {
	std::wcout << m_textureFilename << " draw \n";
	//pRenderTarget->FillRectangle(D2D1::RectF(0, 0, (float)m_pBitmap->GetSize().width, (float)m_pBitmap->GetSize().height), m_pBitmapBrush);
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(m_x, m_y)); 
	pRenderTarget->FillRectangle(D2D1::RectF(0, 0, (float)m_pBitmap->GetSize().width, (float)m_pBitmap->GetSize().height), m_pBitmapBrush);
}

void CRenderObject::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
}