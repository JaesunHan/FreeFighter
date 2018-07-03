#include "stdafx.h"
#include "battleScene.h"

//에너미
#include "enemyManager.h"
//카메라
#include "camera.h"

battleScene::battleScene()
	: _em(NULL)
	, _test01(10.0f, 0.0f, 0.0f)
{
}

battleScene::~battleScene()
{
	SAFE_DELETE(_em);
}

HRESULT battleScene::init()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING , TRUE);

	SetLight();

	_em = new enemyManager;
	_em->ChangeStage(0);

	_camera = new camera;
	_camera->init();

	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		if (_em)
			_em->SetTarget(&_test01);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (_em)
			_em->SetTarget(NULL);
	}
	
	if (_em)
		_em->Update();

	if (_camera)
		_camera->update();
}

void battleScene::render()
{
	if (_em)
		_em->Render();

}

void battleScene::SetLight()
{
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vDir(0.0f, -1.0f, 0.0f);
	light.Direction = vDir;

	D3DDEVICE->SetLight(0, &light);
	D3DDEVICE->LightEnable(0 , true);


}
