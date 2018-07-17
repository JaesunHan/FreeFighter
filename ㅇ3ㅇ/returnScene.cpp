#include "stdafx.h"
#include "returnScene.h"


returnScene::returnScene()
	: _buttons(NULL)
{
}


returnScene::~returnScene()
{
}

HRESULT returnScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	_buttons = new uiButton;
	_buttons->init(_T("Resume"), _T(".\\texture\\buttons\\Resume.png"), vp.Width / 2, vp.Height / 2 - 60, 3);
	_buttons->setDelegate(this);

	uiButton* button = new uiButton;
	button->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), vp.Width / 2, vp.Height / 2, 3);
	button->setDelegate(this);

	_buttons->addChild(button);

	button = new uiButton;
	button->init(_T("Quit"), _T(".\\texture\\buttons\\Quit.png"), vp.Width / 2, vp.Height / 2 + 60, 3);
	button->setDelegate(this);

	_buttons->addChild(button);

	return S_OK;
}

void returnScene::release()
{
	SAFE_OBJRELEASE(_buttons);
}

void returnScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		SCENEMANAGER->changeParent();

	if (_buttons)
		_buttons->update();
}

void returnScene::render()
{
	IMAGEMANAGER->alphaRender(_T("blackMask"), 150);
	if (_buttons)
		_buttons->render();
}

void returnScene::OnClick(uiButton* d)
{
	if (d->getButtonName() == _T("Quit"))
		PostQuitMessage(0);
	else if (d->getButtonName() == _T("Back"))
	{
		SCENEMANAGER->changeScene(_T("mainScene"));
		SCENEMANAGER->sceneInit();
	}
	else if (d->getButtonName() == _T("Resume"))
	{
		SCENEMANAGER->changeParent();
	}
}
