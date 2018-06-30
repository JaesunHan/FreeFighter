#include "stdafx.h"
#include "d3dMainGame.h"
#include "camera.h"
#include "cube.h"
#include "grid.h"
#include "gameObject.h"
#include "objectNode.h"
#include "rabbitWomen.h"
#include "ray.h"
#include "heightMap.h"
#include "skinnedMesh.h"
#include "player.h"


d3dMainGame::d3dMainGame()
	: _camera(NULL)
	, _grid(NULL)
	, _rw(NULL)
	, _map(NULL)
	, _hMap(NULL)
	, _zealot(NULL)
	, _z(NULL)
	, _player(NULL)
{
	for (int i = 0; i < 3; ++i)
		_sphere[i] = NULL;
}


d3dMainGame::~d3dMainGame()
{
	TEXTUREMANAGER->release();
	TIMEMANAGER->release();
	FONTMANAGER->release();
	DEVICEMANAGER->destroy();
}

void d3dMainGame::init()
{
	// 빛을 처리하지 않게
	//D3DDEVICE->SetRenderState(D3DRS_LIGHTING, false);
	//D3DDEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//_map = OBJLOADER->loadMesh(_mtlTexData, L".\\obj\\Map.obj");
	//_surface = OBJLOADER->load(L".\\obj\\map_surface.obj");

	//for (int i = 0; i < _surface.size(); ++i)
	//	_surface[i].init();
	//
	//_rw = new rabbitWomen;
	//_rw->setRoot(ASELOADER->load(L".\\woman\\woman_01_all.ASE"));
	//_rw->init();
	//_rw->setFloor(&_surface);

	//_tennis = ASELOADER->load(L".\\Tannis\\Walk_F.ASE");

	ZeroMemory(&_light, sizeof(D3DLIGHT9));
	_light.Type = D3DLIGHT_DIRECTIONAL;
	_light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_light.Range = 1000.0f;
	_light.Position = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	_light.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&_light.Direction, (D3DXVECTOR3*)&_light.Direction);
	_light.Attenuation0 = 0.0f;
	_light.Attenuation1 = 0.0f;
	_light.Attenuation2 = 0.0f;
	D3DDEVICE->SetLight(0, &_light);
	D3DDEVICE->LightEnable(0, TRUE);
	_numOfLight++;

	//_materialKey.resize(3);
	//_materialKey[0] = L"red";
	//_materialKey[1] = L"green";
	//_materialKey[2] = L"blue";
	//
	//_currentMaterial.resize(3);
	//for (int i = 0; i < 3; ++i)
	//{
	//	_sphere[i] = new tagSphere;
	//	_sphere[i]->center = D3DXVECTOR3(-3.0f + 3 * i, 0.0f, 0.0f);
	//	D3DXCreateSphere(D3DDEVICE, _sphere[i]->radius, 20, 20, &_sphere[i]->sphere, 0);
	//	_currentMaterial[i] = i;
	//}

	//D3DMATERIAL9 temp;
	//ZeroMemory(&temp, sizeof(D3DMATERIAL9));
	//temp.Ambient.r = temp.Diffuse.r = temp.Specular.r = 1.0f;
	//temp.Ambient.g = temp.Diffuse.g = temp.Specular.g = 0.0f;
	//temp.Ambient.b = temp.Diffuse.b = temp.Specular.b = 0.0f;
	//MATERIALMANAGER->addMaterial(L"red", temp);
	//
	//temp.Ambient.r = temp.Diffuse.r = temp.Specular.r = 0.0f;
	//temp.Ambient.g = temp.Diffuse.g = temp.Specular.g = 1.0f;
	//temp.Ambient.b = temp.Diffuse.b = temp.Specular.b = 0.0f;
	//MATERIALMANAGER->addMaterial(L"green", temp);
	//
	//temp.Ambient.r = temp.Diffuse.r = temp.Specular.r = 0.0f;
	//temp.Ambient.g = temp.Diffuse.g = temp.Specular.g = 0.0f;
	//temp.Ambient.b = temp.Diffuse.b = temp.Specular.b = 1.0f;
	//MATERIALMANAGER->addMaterial(L"blue", temp);

	_camera = new camera;
	_camera->init();
	
	_grid = new grid;
	_grid->init();

	//ZeroMemory(&_light2, sizeof(D3DLIGHT9));
	//_light2.Type = D3DLIGHT_POINT;
	//_light2.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//_light2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//_light2.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//_light2.Range = 1000.0f;
	//_light2.Position = D3DXVECTOR3(7.0f, 0.0f, 7.0f);
	//_light2.Attenuation0 = 0.0f;
	//_light2.Attenuation1 = 1.0f;
	//_light2.Attenuation2 = 0.0f;
	//D3DDEVICE->SetLight(1, &_light2);
	//D3DDEVICE->LightEnable(1, TRUE);

	//D3DMATERIAL9 mtrl;
	//ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	//mtrl.Diffuse.r = mtrl.Specular.r = 1.0f;
	//mtrl.Diffuse.g = mtrl.Specular.g = 1.0f;
	//mtrl.Diffuse.b = mtrl.Specular.b = 1.0f;
	//mtrl.Diffuse.a = mtrl.Specular.a = 1.0f;
	//mtrl.Ambient.r = 0.5f;
	//mtrl.Ambient.g = 0.5f;
	//mtrl.Ambient.b = 0.5f;
	//mtrl.Ambient.a = 1.0f;
	//
	//D3DDEVICE->SetMaterial(&mtrl);

	//_font = FONTMANAGER->addFont(fontManager::FONT_DEFAULT);

	//_hMap = new heightMap;
	//_hMap->init();
	//
	//_rw->setHeightMapMemory(_hMap);
	//_hMap->setPlayerMemoryAddress(_rw);

	//_zealot = XLOADER->load(L".\\Zeolot\\zealot.X", _zealotMtls);

	//_z = new skinnedMesh;
	//_z->init(L".\\Zeolot", L"zealot.X");

	_player = new player;
	_player->init();
}

void d3dMainGame::release()
{
	SAFE_DELETE(_camera);
	if (_grid)
	{
		_grid->release();
		SAFE_DELETE(_grid);
	}
	if (_rw)
	{
		_rw->release();
		SAFE_DELETE(_rw);
	}
	if (_map)
		_map->Release();
	for (int i = 0; i < _surface.size(); ++i)
	{
		_surface[i].release();
	}
	_surface.clear();

	for (int i = 0; i < 3; ++i)
	{
		if (_sphere[i])
		{
			if (_sphere[i]->sphere)
			{
				_sphere[i]->sphere->Release();
				_sphere[i]->sphere = NULL;
			}
			SAFE_DELETE(_sphere[i]);
		}
	}

	if (_hMap)
	{
		_hMap->release();
		SAFE_DELETE(_hMap);
	}

	if (_zealot)
		_zealot->Release();

	if (_z)
	{
		_z->release();
		SAFE_DELETE(_z);
	}
	SAFE_OBJRELEASE(_player);
}

void d3dMainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);

	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))
		_isDebug = !_isDebug;

	if (_hMap)
		_hMap->update();

	if (_rw)
		_rw->update();

	if (_rw)
		_camera->update(&_rw->getPosition());
	else
		_camera->update();

	if (_z)
		_z->update();

	if (_player)
		_player->update();

	//for (int i = 0; i < _surface.size(); ++i)
	//{
	//	_surface[i].update();
	//}
	//
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	ray r = ray::rayAtViewSpace(_ptMouse.x, _ptMouse.y);
	//
	//	D3DXMATRIX view, viewInv;
	//	D3DDEVICE->GetTransform(D3DTS_VIEW, &view);
	//	D3DXMatrixInverse(&viewInv, NULL, &view);
	//
	//	ray::TransformRay(&r, viewInv);
	//
	//	bool isPicked = false;
	//	D3DXVECTOR3 pickedPos;
	//	for (int i = 0; i < _surface.size() && !isPicked; ++i)
	//	{
	//		vector<D3DXVECTOR3> temp = _surface[i].getWorldVertex();
	//		for (int j = 0; j < temp.size(); j += 3)
	//		{
	//			if (r.IntersectTri(temp[j], temp[j + 1], temp[j + 2], pickedPos))
	//			{
	//				isPicked = true;
	//				_rw->moveTo(pickedPos);
	//				break;
	//			}
	//		}
	//	}
	//}
}

void d3dMainGame::render()
{
	// 도화지 미리 깔아두기
	D3DDEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		BLACK,						// 깔아둘 도화지 색
		1.0f,						// z버퍼 비율
		0);							// 스텐실 버퍼

	D3DDEVICE->BeginScene();
	// ========================== 랜더링 ==========================

	if (_grid)
		_grid->render();

	if (_rw)
		_rw->render();
	//
	//D3DXMATRIX temp;
	//D3DXMatrixIdentity(&temp);
	//D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);
	//for (int i = 0; i < _mtlTexData.size(); ++i)
	//{
	//	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_mtlTexData[i].textureName));
	//	D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_mtlTexData[i].mtlName));
	//	_map->DrawSubset(i);
	//}
	//
	for (int i = 0; i < _surface.size(); ++i)
	{
		_surface[i].render();
	}

	if (_hMap)
		_hMap->render();

	if (_zealot)
	{
		if (_isDebug)
			D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
		else
			D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

		D3DXMATRIX temp;
		D3DXMatrixIdentity(&temp);
		D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);
		for (int i = 0; i < _zealotMtls.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_zealotMtls[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_zealotMtls[i].mtlName));
			_zealot->DrawSubset(i);
		}
	}

	if (_z)
		_z->render();

	if (_player)
		_player->render();

	// ========================== 랜더링 ==========================
	D3DDEVICE->EndScene();

	D3DDEVICE->Present(NULL, NULL, NULL, NULL);

	//if (_isDebug)
	//{
	//	HDC hdc = GetDC(_hWnd);
	//
	//	TIMEMANAGER->render(hdc);
	//
	//	ReleaseDC(_hWnd, hdc);
	//}
	//
	//WCHAR tempStr[1024];
	//swprintf_s(tempStr, L"메롱");
	//RECT rc;
	//SetRect(&rc, 100, 100, 200, 100);
	//_font->DrawTextW(NULL, tempStr, wcslen(tempStr), &rc, 
	//	DT_LEFT | DT_CENTER | DT_NOCLIP,
	//	BLACK);
}

void d3dMainGame::cameraZoom(float zoom)
{
	if (_camera)
		_camera->cameraZoom(zoom);
}
