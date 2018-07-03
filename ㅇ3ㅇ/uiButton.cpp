#include "stdafx.h"
#include "uiButton.h"

#ifdef UNICODE
wstring uiButton::_buttonStateKey[BUTTON_END] = 
{
	_T("Up"),
	_T("Over"),
	_T("Down")
};

uiButton::uiButton()
	: _buttonName(_T(""))
	, _state(BUTTON_UP)
{
}


uiButton::~uiButton()
{
}

HRESULT uiButton::init(wstring buttonName, const WCHAR* folder, const WCHAR* fileFormat, int frameX, int frameY)
{
	for (int i = 0; i < BUTTON_END; ++i)
	{
		wstring buttonKey = buttonName + _buttonStateKey[i];
		wstring filePath = wstring(folder) + wstring(_T("\\")) + buttonKey + wstring(_T(".")) + fileFormat;
		IMAGEMANAGER->addImage(buttonKey, filePath.c_str());
	}

	_buttonName = buttonName;

	_size.width = IMAGEMANAGER->findImage(buttonName + _buttonStateKey[BUTTON_UP])->getFrameWidth();
	_size.height = IMAGEMANAGER->findImage(buttonName + _buttonStateKey[BUTTON_UP])->getFrameHeight();

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
	wstring buttonKey = _buttonName + _buttonStateKey[_state];
	IMAGEMANAGER->findImage(buttonKey)->render(_position.x, _position.y);

	uiObject::render();
}

#else
#endif
