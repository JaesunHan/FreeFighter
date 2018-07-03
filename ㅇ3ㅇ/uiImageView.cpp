#include "stdafx.h"
#include "uiImageView.h"

#ifdef UNICODE
uiImageView::uiImageView()
	: _imageName(_T(""))
{
}


uiImageView::~uiImageView()
{
}

HRESULT uiImageView::init(wstring imageName, const WCHAR* fileName, float destX, float destY, int frameX, int frameY)
{
	IMAGEMANAGER->addFrameImage(imageName, fileName, frameX, frameY);

	_imageName = imageName;

	_size.width = IMAGEMANAGER->findImage(imageName)->getFrameWidth();
	_size.height = IMAGEMANAGER->findImage(imageName)->getFrameHeight();

	_position.x = destX - _size.width / 2;
	_position.y = destY - _size.height / 2;

	return S_OK;
}

void uiImageView::release()
{
	IMAGEMANAGER->deleteImage(_imageName);

	uiObject::release();
}

void uiImageView::update()
{
	uiObject::update();
}

void uiImageView::render()
{
	IMAGEMANAGER->findImage(_imageName)->frameRender(_position.x, _position.y, 0, 0);

	uiObject::render();
}
#else
uiImageView::uiImageView()
	: _imageName(_T(""))
{
}


uiImageView::~uiImageView()
{
}

HRESULT uiImageView::init(string imageName, const CHAR* fileName, float destX, float destY, int frameX, int frameY)
{
	IMAGEMANAGER->addFrameImage(imageName, fileName, frameX, frameY);

	_imageName = imageName;

	_size.width = IMAGEMANAGER->findImage(imageName)->getFrameWidth();
	_size.height = IMAGEMANAGER->findImage(imageName)->getFrameHeight();

	_position.x = destX - _size.width / 2;
	_position.y = destY - _size.height / 2;

	return S_OK;
}

void uiImageView::release()
{
	IMAGEMANAGER->deleteImage(_imageName);

	uiObject::release();
}

void uiImageView::update()
{
	uiObject::update();
}

void uiImageView::render()
{
	IMAGEMANAGER->findImage(_imageName)->frameRender(_position.x, _position.y, 0, 0);

	uiObject::render();
}
#endif
