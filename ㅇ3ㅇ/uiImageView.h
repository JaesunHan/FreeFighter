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

	virtual HRESULT init(wstring imageName, const WCHAR* fileName, float destX, float destY, int frameX = 1, int frameY = 1);
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
#else
protected:
	string		_imageName;

public:
	uiImageView();
	virtual ~uiImageView();

	virtual HRESULT init(string imageName, const CHAR* fileName, int frameX = 1, int frameY = 2);
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
#endif
};

