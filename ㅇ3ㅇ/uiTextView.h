#pragma once
#include "uiObject.h"

class uiTextView : public uiObject
{
protected:
	fontManager::FONT_TYPE		_fontType;
	wstring						_text;
	D3DXCOLOR					_color;

	// ���Ĺ�� ����?? �߰�

public:
	uiTextView();
	virtual ~uiTextView();

	virtual void render() override;
};

