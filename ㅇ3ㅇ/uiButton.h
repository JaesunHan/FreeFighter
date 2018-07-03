#pragma once
#include "uiObject.h"

class uiButton;

typedef class _buttonDelegate
{
public:
	virtual void OnClick(uiButton* d) = 0;
}iButtonDelegate;

class uiButton : public uiObject
{
private:
	enum BUTTON_STATE
	{
		BUTTON_NONE = -1,
		BUTTON_UP,
		BUTTON_OVER,
		BUTTON_DOWN,
		BUTTON_END
	};

#ifdef UNICODE
protected:
	static wstring		_buttonStateKey[BUTTON_END];
	wstring				_buttonName;

	iButtonDelegate*	_delegate;

	BUTTON_STATE		_state;

public:
	uiButton();
	virtual ~uiButton();

	virtual HRESULT init(wstring buttonName, const WCHAR* folder, const WCHAR* fileFormat, int frameX = 1, int frameY = 2);
	virtual void update();
	virtual void render() override;
#else
#endif
};

