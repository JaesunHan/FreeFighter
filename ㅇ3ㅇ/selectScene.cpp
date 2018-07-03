#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
	: _buttons(NULL)
	, _gameMode(GAME_NONE)
	, _playerMode(PMODE_NONE)
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	_buttons = new uiButton;
	_buttons->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), vp.Width - 120, vp.Height - 70, 3);
	_buttons->setDelegate(this);

	return S_OK;
}

void selectScene::update()
{
	if (_buttons)
		_buttons->update();
}

void selectScene::release()
{
	SAFE_OBJRELEASE(_buttons);
}

void selectScene::render()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (_buttons)
		_buttons->render();

	FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("selectScene"), lstrlen(_T("selectScene")),
		&RectMake(100, 100, 100, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
}

void selectScene::OnClick(uiButton* d)
{
	if (d->getButtonName() == _T("Back"))
	{
		SCENEMANAGER->changeScene(_T("mainScene"));
		SCENEMANAGER->sceneInit();
	}
}
