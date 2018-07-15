#include "stdafx.h"
#include "storyScene.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "background.h"
#include "camera.h"
#include "player.h"


storyScene::storyScene()
	: _pm(NULL)
	, _em(NULL)
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
	//물리엔진이 적용되는 신 생성
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(true);

	D3DDEVICE->GetViewport(&_originViewport);

	_pm = new playerManager;
	_pm->init(_gameMode, _playerMode, _vPlayerSelect, &_cm, _material);

	_pBG = new background;
	_pBG->init();
	_pBG->setLigh();
	_pBG->setSky();
	_pBG->createController(&_cm, _material, D3DXVECTOR3(100, 6, 100));
	_pBG->update();

	D3DXCreateBox(D3DDEVICE, 100, 6, 100, &_testGround, NULL);

	_camera = new camera;
	_camera->init();
	
	return S_OK;
}

void storyScene::release()
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

	if (_pBG)
		_pBG->release();

	SAFE_RELEASE(_testGround);

	SAFE_OBJRELEASE(_camera);
}

void storyScene::update()
{
	if (_pm)
		_pm->update();

	if (_isDebug)
	{
		if (_camera)
			_camera->update(&(_pm->getVPlayers()[0]->p->GetPosition()));
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

			D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);

			if (_pBG)
				_pBG->render();

			if (KEYMANAGER->isStayKeyDown(VK_TAB))
				_testGround->DrawSubset(0);
			// ======================== 여기에 랜더하렴^^ ========================
		}
	}
	D3DDEVICE->SetViewport(&_originViewport);
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

	D3DXVECTOR3	vDir(1.0f, -1.0f, 1.0f);
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
