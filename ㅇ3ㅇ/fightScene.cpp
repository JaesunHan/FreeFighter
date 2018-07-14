#include "stdafx.h"
#include "fightScene.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "grid.h"
#include "background.h"

fightScene::fightScene()
	: _pm(NULL)
	, _em(NULL)
	, _gameMode(GAME_NONE)
	, _playerMode(PMODE_NONE)
	, _grid(NULL)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	, _bg(NULL)
{
}


fightScene::~fightScene()
{
}

HRESULT fightScene::init()
{
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(false);

	D3DDEVICE->GetViewport(&_originViewport);

	_pm = new playerManager;
	_pm->init(_gameMode, _playerMode, _vPlayerSelect, &_cm, _material);

	_grid = new grid;
	_grid->init(BLACK);

	_bg = new background;
	_bg->init();
	_bg->setLigh();
	_bg->setSky();
	_bg->createController(&_cm, _material, D3DXVECTOR3(100, 6, 100));
	return S_OK;
}

void fightScene::release()
{
	SAFE_OBJRELEASE(_pm);
	SAFE_DELETE(_em);

	D3DDEVICE->SetViewport(&_originViewport);

	SAFE_OBJRELEASE(_grid);

	if (_physXScene)
	{
		_physXScene->release();
		_physXScene = NULL;
	}

	if (_material)
	{
		_material->release();
		_material = NULL;
	}

	if (_cm)
		_cm->purgeControllers();

	if (_bg)
		_bg->release();
}

void fightScene::update()
{
	if (_pm)
		_pm->update();

	if (_bg)
		_bg->update();
}

void fightScene::render()
{
	if (_pm)
	{
		for (int i = 0; i < _pm->getPlayersNum(); ++i)
		{
			// ======================== 여기에 랜더하렴^^ ========================
			_pm->render(i);

			if (_grid)
				_grid->render();

			if (_bg)
				_bg->render();
			// ======================== 여기에 랜더하렴^^ ========================
		}
	}
	D3DDEVICE->SetViewport(&_originViewport);
}

void fightScene::addPlayers(PLAYABLE_CHARACTER p)
{
	_vPlayerSelect.push_back(p);
}
