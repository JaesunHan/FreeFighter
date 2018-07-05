#include "stdafx.h"
#include "selectScene.h"
#include "uiImageView.h"
#include "skinnedMesh.h"
#include "playerSelector.h"
#include "camera.h"


selectScene::selectScene()
	: _buttons(NULL)
	, _gameMode(GAME_NONE)
	, _playerMode(PMODE_NONE)
	, _portrait(NULL)
	, _camera(NULL)
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	// ��ư
	_buttons = new uiButton;
	_buttons->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), vp.Width - 120, vp.Height - 70, 3);
	_buttons->setDelegate(this);

	// �ʻ�ȭ
	_portrait = new uiImageView;
	_portrait->init(_T("portrait_zealot"), _T(".\\texture\\portraits\\zealot.png"), vp.Width / 2 - 165, vp.Height / 2 + 100);

	uiImageView* portrait = new uiImageView;
	portrait->init(_T("portrait_reaper"), _T(".\\texture\\portraits\\reaper.png"), vp.Width / 2 - 55, vp.Height / 2 + 100);

	_portrait->addChild(portrait);

	portrait = new uiImageView;
	portrait->init(_T("portrait_woodGiant"), _T(".\\texture\\portraits\\woodGiant.png"), vp.Width / 2 + 55, vp.Height / 2 + 100);

	_portrait->addChild(portrait);

	portrait = new uiImageView;
	portrait->init(_T("portrait_knight"), _T(".\\texture\\portraits\\knight.png"), vp.Width / 2 + 165, vp.Height / 2 + 100);

	_portrait->addChild(portrait);

	// �÷��̾ ������ �� �ִ� �𵨵�
	wstring name[CHAR_END] = 
	{
		_T("zealot"),
		_T("reaper"),
		_T("woodGiant"),
		_T("fepee")
	};

	_vMesh.resize(CHAR_END);
	for (int i = 0; i < _vMesh.size(); ++i)
	{
		skinnedMesh* mesh = new skinnedMesh;
		mesh->init(name[i], wstring(_T(".\\xFile\\") + name[i]).c_str(), (name[i] + wstring(_T(".X"))).c_str());
		_vMesh[i] = mesh;
	}

	// �÷��̾� ������
	_selectors.resize(_playerMode + 1);
	for (int i = 0; i < _selectors.size(); ++i)
	{
		playerSelector* selector = new playerSelector;
		selector->init((PLAYERS)i);
		_selectors[i] = selector;
	}
	if (_selectors.size() != 1)
	{
		_selectors[PLAYER_1P]->setCantSelectCharacter(_selectors[PLAYER_2P]);
		_selectors[PLAYER_2P]->setCantSelectCharacter(_selectors[PLAYER_1P]);
	}

	// ī�޶�
	_camera = new camera;
	_camera->init();

	return S_OK;
}

void selectScene::update()
{
	if (_camera)
		_camera->update();

	for (int i = 0; i < _selectors.size(); ++i)
	{
		_selectors[i]->update();
		_vMesh[_selectors[i]->getCurrentSelectedCharacter()]->setParentMatrix(_selectors[i]->getWorldAdress());
		_vMesh[_selectors[i]->getCurrentSelectedCharacter()]->update();
	}

	if (_portrait)
		_portrait->update();

	if (_buttons)
		_buttons->update();
}

void selectScene::release()
{
	SAFE_OBJRELEASE(_camera);
	SAFE_OBJRELEASE(_buttons);
	SAFE_OBJRELEASE(_portrait);

	for (int i = 0; i < _vMesh.size(); ++i)
		_vMesh[i]->destroy();
	_vMesh.clear();

	for (int i = 0; i < _selectors.size(); ++i)
		SAFE_OBJRELEASE(_selectors[i]);
	_selectors.clear();
}

void selectScene::render()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (_buttons)
		_buttons->render();

	if (_portrait)
		_portrait->render();

	for (int i = 0; i < _selectors.size(); ++i)
		_selectors[i]->render();

	for (int i = 0; i < _selectors.size(); ++i)
		_vMesh[_selectors[i]->getCurrentSelectedCharacter()]->render();

	FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("selectScene"), lstrlen(_T("selectScene")),
		&RectMake(100, 100, 100, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);

	if (_gameMode == GAME_FIGHT)
	{
		FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("next : fight"), lstrlen(_T("next : fight")),
			&RectMake(100, 150, 100, 100),
			DT_LEFT | DT_CENTER | DT_NOCLIP,
			BLACK);
	}
	else if (_gameMode == GAME_STORY)
	{
		FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("next : story"), lstrlen(_T("next : story")),
			&RectMake(100, 150, 100, 100),
			DT_LEFT | DT_CENTER | DT_NOCLIP,
			BLACK);
	}
}

void selectScene::OnClick(uiButton* d)
{
	if (d->getButtonName() == _T("Back"))
	{
		SCENEMANAGER->changeScene(_T("mainScene"));
		SCENEMANAGER->sceneInit();
	}
}
