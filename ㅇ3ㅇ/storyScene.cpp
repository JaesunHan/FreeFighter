#include "stdafx.h"
#include "storyScene.h"
#include "camera.h"
#include "background.h"

storyScene::storyScene()
	: _pBG(NULL)
	,_camera(NULL)
	//: _meshMap(NULL)
	//, _meshSurface(NULL)	
	//, _camera(NULL)
{
	D3DXMatrixIdentity(&_mapMatWorld);
}


storyScene::~storyScene()
{
	
}

HRESULT storyScene::init()
{
	_pBG = new background;
	_pBG->init();
	//_meshMap = OBJLOADER->loadMesh(_vecMapMtlData, _T(".\\map\\map_forest.obj"));
	//_meshSurface = OBJLOADER->loadMesh(_vecSurfaceMtlData, _T(".\\map\\map_forest_surface.obj"));
	_camera = new camera;
	_camera->init();

	//setLight();
	return S_OK;
}

void storyScene::update()
{
	if (_pBG)
		_pBG->update();
	//D3DXMATRIX  matS, matR, matT;
	//D3DXMatrixIdentity(&matS);
	//D3DXMatrixIdentity(&matR);
	//D3DXMatrixIdentity(&matT);
	//
	//D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	//D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	//
	//_mapMatWorld = matS;

	if (_camera)
		_camera->update();
}

void storyScene::release()
{
	//SAFE_RELEASE(_meshMap);
	//SAFE_RELEASE(_meshSurface);
	//
	if (_pBG)
		_pBG->release();

	SAFE_DELETE(_camera);
}

void storyScene::render()
{
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
	D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	if (_pBG)
		_pBG->render();
	//if (_isDebug)
	//{
	//	//디버그 모드일 때는 surface 출력
	//	for (int i = 0; i < _vecSurfaceMtlData.size(); ++i)
	//	{
	//		D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecSurfaceMtlData[i].textureName));
	//		D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecSurfaceMtlData[i].mtlName));
	//		_meshSurface->DrawSubset(i);
	//	}
	//}
	//
	//else
	//{
	//	//맵 출력
	//	for (int i = 0; i < _vecMapMtlData.size(); ++i)
	//	{
	//		D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecMapMtlData[i].textureName));
	//		D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecMapMtlData[i].mtlName));
	//		_meshMap->DrawSubset(i);
	//	}
	//}
	D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void storyScene::cameraZoom(float zoom)
{
	_camera->cameraZoom(zoom);
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
