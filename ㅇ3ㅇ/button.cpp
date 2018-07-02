#include "stdafx.h"
#include "button.h"
#include "image.h"


button::button()
	: _isSelected(false)
	, _buttonName(_T(""))
	, _pos(0.0f, 0.0f, 0.0f)
	, _width(0.0f)
	, _height(0.0f)
	, _currentFrameY(0)
{
}


button::~button()
{
}

#ifdef UNICODE
HRESULT button::init(wstring buttonName, wstring fileName, float x, float y)
#else
HRESULT button::init(string buttonName, string fileName, float x, float y)
#endif
{
	//if (!TEXTUREMANAGER->addTexture(buttonName, fileName.c_str())) return E_FAIL;
	//
	//D3DXCreateSprite(D3DDEVICE, &_sprite);
	//
	//_width = TEXTUREMANAGER->find(buttonName)->textureInfo.Width;
	//_height = TEXTUREMANAGER->find(buttonName)->textureInfo.Height;
	//
	//_buttonName = buttonName;

	IMAGEMANAGER->addFrameImage(buttonName, fileName.c_str(), 1, 2);

	_isSelected = false;

	_width = IMAGEMANAGER->findImage(buttonName)->getFrameWidth();
	_height = IMAGEMANAGER->findImage(buttonName)->getFrameHeight();
	_pos.x = x - _width / 2;
	_pos.y = y - _height / 2;

	_buttonName = buttonName;

	_currentFrameY = 0;

	return S_OK;
}

void button::release()
{
}

void button::update()
{
	RECT clickRange = RectMake(_pos.x, _pos.y, _width, _height);
	if (PtInRect(&clickRange, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			_isSelected = true;
		else
			_isSelected = false;
	}
	else
		_isSelected = false;

	if (_isSelected)
		_currentFrameY = 1;
	else
		_currentFrameY = 0;
}

void button::render()
{
	IMAGEMANAGER->findImage(_buttonName)->alphaFrameRender(_pos.x, _pos.y, 0, _currentFrameY, 150);
}
