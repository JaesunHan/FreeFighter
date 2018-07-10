#include "stdafx.h"
#include "playGround.h"
#include "camera.h"

#include "playerManager.h"
#include "grid.h"


playGround::playGround()
//: _player(NULL)
	: _camera(NULL)
	, _PM(NULL)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	, _grid(NULL)
{
}


playGround::~playGround()
{
	release();
	_grid->release();
}

HRESULT playGround::init()
{
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(true);

	SetLight();

	_grid = new grid;
	_grid->init();


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	//_player = new player;
	//_player->Init(PLAYER_1P, _T(".\\xFile\\knight"), _T("knight.X"));


	//else if (KEYMANAGER->isOnceKeyDown('B'))
	//{
	//	_player->Init(_T(".\\xFile\\knight"), _T("knight.X"));
	//}

	//else if (KEYMANAGER->isOnceKeyDown('N'))
	//{
	//	_player->Init(_T(".\\xFile\\gigas"), _T("gigas.X"));
	//}
	_PM = new playerManager;
	_PM->Init();
	_PM->setPhysX(_cm, _material);



	_camera = new camera;
	_camera->init();

	return S_OK;
}

void playGround::release()
{
	SAFE_DELETE(_PM);
	SAFE_OBJRELEASE(_camera);
}

void playGround::update()
{
	//_player->Update();
	_camera->update();
	_PM->Update();
}



void playGround::render()
{
	//_player->Render();
	_PM->Render();
	_grid->render();
}

void playGround::SetLight()
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

void playGround::createTestCube()
{

}
