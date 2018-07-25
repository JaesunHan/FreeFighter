#include "stdafx.h"
#include "fightScene.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "grid.h"


fightScene::fightScene()
	: _pm(NULL)
	, _em(NULL)
	, _gameMode(GAME_NONE)
	, _playerMode(PMODE_NONE)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	, _camera(NULL)
	, _grid(NULL)
{
}


fightScene::~fightScene()
{
}

HRESULT fightScene::init()
{
	IMAGEMANAGER->addImage(_T("gameover"), _T(".\\texture\\ui\\gameover.png"));

	//���������� ����Ǵ� �� ����
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(false);

	D3DDEVICE->GetViewport(&_originViewport);

	_pm = new playerManager;
	_pm->init(_gameMode, _playerMode, _vPlayerSelect, &_cm, _material);

	_em = new enemyManager;
	_em->setPhysX(_cm, _material);
	_em->Init(1, _pm->getPlayersNum());

	_em->SetPlayerAdressLink(_pm);
	_pm->setEMMemory(_em);

	_camera = new camera;
	_camera->init();

	_grid = new grid;
	_grid->init(BLACK, 20, 0.0f);

	if (_playerMode == PMODE_PLAYER2)
		_pm->setOpponent();

	_gameoverAlpha = 0;
	_isGameOver = false;
	_gameoverTime = 0.0f;

	return S_OK;
}

void fightScene::release()
{
	SAFE_OBJRELEASE(_pm);
	SAFE_DELETE(_em);

	D3DDEVICE->SetViewport(&_originViewport);

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

	SAFE_OBJRELEASE(_camera);

	SAFE_OBJRELEASE(_grid);
}

void fightScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeChild(_T("returnScene"));
		SCENEMANAGER->currentSceneInit();
	}

	if (!_isGameOver)
	{
		if (_pm)
		{
			_pm->update();
			if (_pm->isAllDead())
				_isGameOver = true;
		}

		if (_em)
			_em->Update();

		if (_isDebug)
		{
			if (_camera)
				_camera->update(&(_pm->getVPlayers()[0]->p->GetPosition()));
		}
	}
	else
	{
		_gameoverAlpha += 5;
		if (_gameoverAlpha > 255)
			_gameoverAlpha = 255;

		_gameoverTime += TIMEMANAGER->getElapsedTime();

		if (_gameoverTime > 7.0f)
		{
			SCENEMANAGER->changeScene(_T("mainScene"));
			SCENEMANAGER->sceneInit();
		}
	}
}

void fightScene::render()
{
	if (_pm)
	{
		for (int i = 0; i < _pm->getPlayersNum(); ++i)
		{
			// ======================== ���⿡ �����Ϸ�^^ ========================
			_pm->render(i);

			if (_em)
				_em->Render(_pm->getPlayersNum());

			if (_grid)
				_grid->render();
			// ======================== ���⿡ �����Ϸ�^^ ========================

			_pm->renderParticle();
			_pm->renderUi(i);
			_em->RenderParticle(_pm->getPlayersNum());
		}
	}
	D3DDEVICE->SetViewport(&_originViewport);
}

void fightScene::cameraZoom(float zoom)
{
	if (_isDebug)
		_camera->cameraZoom(zoom);
}
