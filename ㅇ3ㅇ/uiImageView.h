#pragma once
#include "uiObject.h"

class uiImageView : public uiObject
{
#ifdef UNICODE
protected:
	wstring		_imageName;

public:
	uiImageView();
	virtual ~uiImageView();

	virtual HRESULT init(wstring imageName, const WCHAR* fileName, int frameX = 1, int frameY = 2);
	virtual void render() override;
#else
#endif
};

