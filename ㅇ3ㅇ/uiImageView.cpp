#include "stdafx.h"
#include "uiImageView.h"


uiImageView::uiImageView()
	: _imageName(_T(""))
{
}


uiImageView::~uiImageView()
{
}

HRESULT uiImageView::init(wstring imageName, const WCHAR * fileName, int frameX, int frameY)
{
	return E_NOTIMPL;
}

void uiImageView::render()
{
}
