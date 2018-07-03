#include "stdafx.h"
#include "uiButton.h"

#ifdef UNICODE
uiButton::uiButton()
	: _buttonName(_T(""))
	, _state(BUTTON_UP)
{
}


uiButton::~uiButton()
{
}

HRESULT uiButton::init(wstring buttonName, const WCHAR* fileName, float destX, float destY, int frameY)
{
	IMAGEMANAGER->addFrameImage(buttonName, fileName, 1, frameY);

	_buttonName = buttonName;

	_size.width = IMAGEMANAGER->findImage(buttonName)->getFrameWidth();
	_size.height = IMAGEMANAGER->findImage(buttonName)->getFrameHeight();

	_position.x = destX - _size.width / 2;
	_position.y = destY - _size.height / 2;

	return S_OK;
}

void uiButton::update()
{
	if (PtInRect(&RectMake(_position.x, _position.y, _size.width, _size.height), _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			_state = BUTTON_DOWN;
		else
			_state = BUTTON_OVER;

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _state == BUTTON_DOWN)
		{
			_state = BUTTON_UP;

			if (_delegate)
				_delegate->OnClick(this);
		}
	}
	else
		_state = BUTTON_UP;

	uiObject::update();
}

void uiButton::render()
{
	IMAGEMANAGER->findImage(_buttonName)->frameRender(_position.x, _position.y, 0, _state);

	uiObject::render();
}

#else
uiButton::uiButton()
	: _buttonName(_T(""))
	, _state(BUTTON_UP)
{
}


uiButton::~uiButton()
{
}

HRESULT uiButton::init(string buttonName, const CHAR* fileName, float destX, float destY, int frameX, int frameY)
{
	IMAGEMANAGER->addFrameImage(buttonName, fileName, frameX, frameY);

	_buttonName = buttonName;

	_size.width = IMAGEMANAGER->findImage(buttonName)->getFrameWidth();
	_size.height = IMAGEMANAGER->findImage(buttonName)->getFrameHeight();

	return S_OK;
}

void uiButton::update()
{
	if (PtInRect(&RectMake(_position.x, _position.y, _size.width, _size.height), _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			_state = BUTTON_DOWN;
		else
			_state = BUTTON_OVER;

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _state == BUTTON_DOWN)
		{
			_state = BUTTON_UP;

			if (_delegate)
				_delegate->OnClick(this);
		}
	}
	else
		_state = BUTTON_UP;

	uiObject::update();
}

void uiButton::render()
{
	IMAGEMANAGER->findImage(_buttonName)->frameRender(_position.x, _position.y, 0, _state);

	uiObject::render();
}
#endif
