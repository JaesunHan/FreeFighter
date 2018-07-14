#include "stdafx.h"
#include "itemScene.h"
#include "camera.h"

#include "grid.h"
#include "cube.h"


itemScene::itemScene()
	: _camera(NULL)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	//, _grid(NULL)
	//, _cube(NULL)
{
}


itemScene::~itemScene()
{
	release();
	//_grid->release();
	//_cube->release();
}

HRESULT itemScene::init()
{
	SetLight();

	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(true);


	//테스트하기위한 공간
	//_grid = new grid;
	//_grid->init();
	//
	//_cube = new cube;
	//_cube->init();



	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);




	_camera = new camera;
	_camera->init();

	return S_OK;
}

void itemScene::release()
{
	//SAFE_DELETE(_PM);
	SAFE_OBJRELEASE(_camera);
}

void itemScene::update()
{
	_camera->update();

	//_cube->update();

}



void itemScene::render()
{
	//_grid->render();
	//_cube->render();
}

void itemScene::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);

	g_pD3DDevice->LightEnable(0, true);
}

