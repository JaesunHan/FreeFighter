#include "stdafx.h"
#include "physXScene.h"
#include "grid.h"
#include "camera.h"
#include "testPlayer.h"


physXScene::physXScene()
	: _grid(NULL)
	, _camera(NULL)
	, _physXScene(NULL)
	, _material(NULL)
	, _player(NULL)
	, _cm(NULL)
{
}


physXScene::~physXScene()
{
}

HRESULT physXScene::init()
{
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);

	_grid = new grid;
	_grid->init();

	_camera = new camera;
	_camera->init();

	_player = new testPlayer;
	_player->init();
	_player->createController(&_cm, _material);

	//_physXScene->addActor((*_player->getDynamic()));

	return S_OK;
}

void physXScene::release()
{
	SAFE_OBJRELEASE(_grid);
	SAFE_OBJRELEASE(_camera);

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
}

void physXScene::update()
{
	if (_player)
		_player->update();

	if (_camera)
		_camera->update();
}

void physXScene::render()
{
	if (_grid)
		_grid->render();

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (_player)
		_player->render();
}

void physXScene::cameraZoom(float zoom)
{
	_camera->cameraZoom(zoom);
}
