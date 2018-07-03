#pragma once
#include "uiObject.h"

class uiTextView : public uiObject
{
protected:
	fontManager::FONT_TYPE		_fontType;
	wstring						_text;
	D3DXCOLOR					_color;

	// 정렬방식 정도?? 추가

public:
	uiTextView();
	virtual ~uiTextView();

	virtual void release() override;
	virtual void render() override;
};

