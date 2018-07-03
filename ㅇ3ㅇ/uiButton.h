#pragma once
#include "uiObject.h"

class uiButton;

typedef class _buttonDelegate
{
public:
	virtual void OnClick(uiButton* d) = 0;
} iButtonDelegate;

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
	wstring				_buttonName;

	iButtonDelegate*	_delegate;

	BUTTON_STATE		_state;

public:
	uiButton();
	virtual ~uiButton();

	virtual HRESULT init(wstring buttonName, const WCHAR* fileName, float destX, float destY, int frameY = 2);
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	inline void setButtonName(wstring n) { _buttonName = n; }
	inline wstring getButtonName() { return _buttonName; }

	inline void setDelegate(iButtonDelegate* d) { _delegate = d; }
	inline iButtonDelegate* getDelegate() { return _delegate; }
#else
protected:
	string				_buttonName;

	iButtonDelegate*	_delegate;

	BUTTON_STATE		_state;

public:
	uiButton();
	virtual ~uiButton();

	virtual HRESULT init(string buttonName, const CHAR* fileName, float destX, float destY, int frameY = 2);
	virtual void release() override;
	virtual void update();
	virtual void render() override;

	inline void setButtonName(string n) { _buttonName = n; }
	inline wstring getButtonName() { return _buttonName; }

	inline void setDelegate(iButtonDelegate* d) { _delegate = d; }
	inline iButtonDelegate* getDelegate() { return _delegate; }
#endif
};

