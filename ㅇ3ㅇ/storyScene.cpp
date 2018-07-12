#include "stdafx.h"
#include "storyScene.h"


storyScene::storyScene()
	: _meshMap(NULL)
	, _meshSurface(NULL)	
{
	D3DXMatrixIdentity(&_mapMatWorld);
}


storyScene::~storyScene()
{
	
}

HRESULT storyScene::init()
{
	_meshMap = OBJLOADER->loadMesh(_vecMapMtlData, _T(".\\obj\\map_forest.obj"));
	_meshSurface = OBJLOADER->loadMesh(_vecMapMtlData, _T(".\\obj\\map_forest_surface____4.obj"));

	return S_OK;
}

void storyScene::update()
{
}

void storyScene::release()
{
}

void storyScene::render()
{
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);
	if (_isDebug)
	{
		//����� ����� ���� surface ���
		for (int i = 0; i < _vecSurfaceMtlData.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecSurfaceMtlData[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecSurfaceMtlData[i].mtlName));
			_meshSurface->DrawSubset(i);
		}
	}

	else
	{
		//�� ���
		for (int i = 0; i < _vecMapMtlData.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecMapMtlData[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecMapMtlData[i].mtlName));
			_meshMap->DrawSubset(i);
		}
	}
}
