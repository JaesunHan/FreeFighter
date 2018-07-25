#include "stdafx.h"
#include "storyScene.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "background.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "itemManager.h"
#include "appearEnemyScene.h"


storyScene::storyScene()
	: _pm(NULL)
	, _em(NULL)
	, _im(NULL)
	, _gameMode(GAME_NONE)
	, _playerMode(PMODE_NONE)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	, _pBG(NULL)
	, _testGround(NULL)
	, _camera(NULL)
{
	D3DXMatrixIdentity(&_mapMatWorld);
}


storyScene::~storyScene()
{
}

HRESULT storyScene::init()
{
	IMAGEMANAGER->addImage(_T("gameover"), _T(".\\texture\\ui\\gameover.png"));

	//물리엔진이 적용되는 신 생성
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(false);

	D3DDEVICE->GetViewport(&_originViewport);

	_pm = new playerManager;
	_pm->init(_gameMode, _playerMode, _vPlayerSelect, &_cm, _material);

	_pBG = new background;
	_pBG->init();
	_pBG->setLigh();
	_pBG->setSky();
	_pBG->createGroundController(&_cm, _material, D3DXVECTOR3(170, 3, 170));
	_pBG->update();

	D3DXCreateBox(D3DDEVICE, 100, 3, 100, &_testGround, NULL);

	_em = new enemyManager;
	_em->ChangeStage(0);
	_em->setPhysX(_cm, _material);
	_em->Init();

	_im = new itemManager;
	_im->Init();

	_em->SetPlayerAdressLink(_pm);
	_em->SetItemAdressLink(_im);
	_pm->setEMMemory(_em);
	_pm->setIMMemory(_im);
	_im->setPlayerAdressLink(_pm);
	_im->setEnemyAdressLink(_em);

	_camera = new camera;
	_camera->init();
	
	_appearScene = (appearEnemyScene*)SCENEMANAGER->findChild(_T("storyScene"), _T("appearScene"));
	_isBossAppear = false;

	_gameoverAlpha = 0;
	_isGameOver = false;
	_gameoverTime = 0.0f;

	return S_OK;
}

void storyScene::release()
{
	SAFE_OBJRELEASE(_pm);
	SAFE_DELETE(_em);
	SAFE_DELETE(_im);

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

	if (_pBG)
		_pBG->release();

	SAFE_RELEASE(_testGround);

	SAFE_OBJRELEASE(_camera);
}

void storyScene::update()
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

		if (_im)
			_im->Update();

		if (_isDebug)
		{
			if (_camera)
				_camera->update(&(_pm->getVPlayers()[0]->p->GetPosition()));
		}
		//if (KEYMANAGER->isOnceKeyDown('U'))
		if (_em->GetMiddleBoss())
		{
			if (_appearScene && !_isBossAppear)
			{

				_appearScene->setBackground(_pBG);
				_appearScene->setEnemyManager(_em);
				_appearScene->setMapMatWorld(_mapMatWorld);
				_appearScene->setCamWalkStartKeyFrame();
				_isBossAppear = true;
				SCENEMANAGER->changeChild(_T("appearScene"));
				SCENEMANAGER->findChild(_T("storyScene"), _T("appearScene"))->init();
				//D3DDEVICE->SetViewport(&_originViewport);

			}
		}
	}
	else
	{
		if (_pm)
			_pm->update();

		_gameoverAlpha++;
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

void storyScene::render()
{
	if (_pm)
	{
		for (int i = 0; i < _pm->getPlayersNum(); ++i)
		{
			// ======================== 여기에 랜더하렴^^ ========================
			_pm->render(i);

			if (_em)
				_em->Render(_pm->getPlayersNum());

			if (_im)
				_im->Render();

			D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);

			if (_pBG)
				_pBG->render();

			if (KEYMANAGER->isStayKeyDown(VK_TAB))
				_testGround->DrawSubset(0);
			// ======================== 여기에 랜더하렴^^ ========================

			_pm->renderParticle();
			_pm->renderUi(i);
			_em->RenderParticle(_pm->getPlayersNum());
		}
	}
	D3DDEVICE->SetViewport(&_originViewport);

	if (_isGameOver)
	{
		float widthRate = _originViewport.Width / IMAGEMANAGER->findImage(_T("gameover"))->getWidth();
		float heightRate = _originViewport.Height / IMAGEMANAGER->findImage(_T("gameover"))->getHeight();

		IMAGEMANAGER->alphaRender(_T("gameover"), 0, 0, D3DXVECTOR3(widthRate, heightRate, 1.0f), _gameoverAlpha);
	}
}

void storyScene::setLight()
{
	//태양
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3	vDir(-1.0f, -1.0f, -1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	D3DDEVICE->SetLight(_numOfLight, &stLight);
	D3DDEVICE->LightEnable(_numOfLight, TRUE);
	_numOfLight++;
}

void storyScene::cameraZoom(float zoom)
{
	if (_isDebug)
		_camera->cameraZoom(zoom);
}
