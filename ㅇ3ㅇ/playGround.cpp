#include "stdafx.h"
#include "playGround.h"
#include "camera.h"
#include "playerKeySet.h"


playGround::playGround()
	: _player(NULL)
	, _camera(NULL)
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	SetLight();


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	_player = new player;
	_player->Init(PLAYER_1P, _T(".\\xFile\\gigas"), _T("gigas.X"));
	

	//else if (KEYMANAGER->isOnceKeyDown('B'))
	//{
	//	_player->Init(_T(".\\xFile\\knight"), _T("knight.X"));
	//}

	//else if (KEYMANAGER->isOnceKeyDown('N'))
	//{
	//	_player->Init(_T(".\\xFile\\gigas"), _T("gigas.X"));
	//}


	_camera = new camera;
	_camera->init();

	return S_OK;
}

void playGround::release()
{
	SAFE_DELETE(_player);
	SAFE_OBJRELEASE(_camera);
}

void playGround::update()
{
	_player->Update();
	_camera->update();
}



void playGround::render()
{
	_player->Render();
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
