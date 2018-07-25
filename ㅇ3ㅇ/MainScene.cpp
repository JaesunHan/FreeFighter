#include "stdafx.h"
#include "MainScene.h"
#include "selectScene.h"


mainScene::mainScene()
	: _modeButtons(NULL)
	, _playerButtons(NULL)
	, _isModeSelect(false)
	, _isPlayersSelect(false)
	, _gameMode(GAME_NONE)
	, _playerMode(PMODE_NONE)
	, _titleScale(1.0f, 1.0f, 1.0f)
{
}


mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	IMAGEMANAGER->addImage(_T("title"), _T(".\\texture\\ui\\title.png"));

	FONTMANAGER->addFont(fontManager::FONT_DEFAULT);
	FONTMANAGER->addFont(fontManager::FONT_SMALLFONT);

	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	// 모드 선택
	_modeButtons = new uiButton;
	_modeButtons->init(_T("Story"), _T(".\\texture\\buttons\\Story.png"), vp.Width / 2, vp.Height / 2 + 10, 3);
	_modeButtons->setDelegate(this);
	
	uiButton* button = new uiButton;
	button->init(_T("Fight"), _T(".\\texture\\buttons\\Fight.png"), vp.Width / 2, vp.Height / 2 + 70, 3);
	button->setDelegate(this);

	_modeButtons->addChild(button);

	button = new uiButton;
	button->init(_T("Store"), _T(".\\texture\\buttons\\Store.png"), vp.Width / 2, vp.Height / 2 + 130, 3);
	button->setDelegate(this);

	_modeButtons->addChild(button);

	button = new uiButton;
	button->init(_T("Quit"), _T(".\\texture\\buttons\\Quit.png"), vp.Width / 2, vp.Height / 2 + 190, 3);
	button->setDelegate(this);

	_modeButtons->addChild(button);

	// 플레이어 선택
	_playerButtons = new uiButton;
	_playerButtons->init(_T("1P"), _T(".\\texture\\buttons\\1p.png"), vp.Width / 2, vp.Height / 2 - 50, 3);
	_playerButtons->setDelegate(this);

	button = new uiButton;
	button->init(_T("2P"), _T(".\\texture\\buttons\\2p.png"), vp.Width / 2, vp.Height / 2 + 10, 3);
	button->setDelegate(this);

	_playerButtons->addChild(button);

	button = new uiButton;
	button->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), vp.Width / 2, vp.Height / 2 + 70, 3);
	button->setDelegate(this);

	_playerButtons->addChild(button);

	this->modeReset();

	_titleScale = D3DXVECTOR3(10.0f, 2.0f, 1.0f);

	return S_OK;
}

void mainScene::update()
{
	if (!_isModeSelect)
	{
		if (_modeButtons)
			_modeButtons->update();

		_titleScale.x -= 0.1f;
		if (_titleScale.x < 2.0f)
			_titleScale.x = 2.0f;
	}
	else
	{
		if (!_isPlayersSelect)
		{
			if (_playerButtons)
				_playerButtons->update();
		}
	}
}

void mainScene::release()
{
	SAFE_OBJRELEASE(_modeButtons);
	SAFE_OBJRELEASE(_playerButtons);
}

void mainScene::render()
{
	if (!_isModeSelect)
	{
		D3DVIEWPORT9 vp;
		D3DDEVICE->GetViewport(&vp);

		float destX = vp.Width / 2 - IMAGEMANAGER->findImage(_T("title"))->getWidth() / 2 * _titleScale.x;
		float destY = vp.Height / 2 - IMAGEMANAGER->findImage(_T("title"))->getHeight() / 2 * _titleScale.y;

		IMAGEMANAGER->render(_T("title"), destX, destY, _titleScale);

		if (_modeButtons)
			_modeButtons->render();
	}
	else
	{
		if (!_isPlayersSelect)
		{
			if (_playerButtons)
				_playerButtons->render();
		}
		else
		{
			SCENEMANAGER->changeScene(_T("selectScene"));
			((selectScene*)SCENEMANAGER->findParent(_T("selectScene")))->setMode(_gameMode, _playerMode);
			SCENEMANAGER->sceneInit();
		}
	}
}

void mainScene::OnClick(uiButton* d)
{
	if (d->getButtonName() == _T("Quit"))
		PostQuitMessage(0);
	else if (d->getButtonName() == _T("Back"))
	{
		this->modeReset();
	}
	else if (d->getButtonName() == _T("Story"))
	{
		_isModeSelect = true;
		_gameMode = GAME_STORY;
	}
	else if (d->getButtonName() == _T("Fight"))
	{
		_isModeSelect = true;
		_gameMode = GAME_FIGHT;
	}
	else if (d->getButtonName() == _T("1P"))
	{
		_isPlayersSelect = true;
		_playerMode = PMODE_PLAYER1;
	}
	else if (d->getButtonName() == _T("2P"))
	{
		_isPlayersSelect = true;
		_playerMode = PMODE_PLAYER2;
	}
	else if (d->getButtonName() == _T("Store"))
	{
		SCENEMANAGER->changeScene(_T("storeScene"));
		SCENEMANAGER->sceneInit();
	}
}

void mainScene::modeReset()
{
	_isPlayersSelect = false;
	_isModeSelect = false;
	_gameMode = GAME_NONE;
	_playerMode = PMODE_NONE;
}
