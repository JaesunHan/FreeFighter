#include "stdafx.h"
#include "background.h"


background::background()
{
}


background::~background()
{
}

#ifdef UNICODE
HRESULT background::init(WCHAR * skyFolder, WCHAR * skyFileName, WCHAR * mapFolder, WCHAR * mapFileName)
{
	return S_OK;
}
#else
HRESULT background::init(char * skyFolder, char * skyFileName, char * mapFolder, char * mapFileName)
{
	return S_OK;
}
#endif // UNICODE


HRESULT background::init()
{
	_meshMap = OBJLOADER->loadMesh(_vecMapMtlData, _T(".\\map\\map_forest.obj"));
	_meshSurface = OBJLOADER->loadMesh(_vecSurfaceMtlData, _T(".\\map\\map_forest_surface.obj"));

	setLigh();

	return S_OK;
}

void background::update()
{
	D3DXMATRIX  matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);

	_mapMatWorld = matS;
}

void background::render()
{
	if (_isDebug)
	{
		//디버그 모드일 때는 surface 출력
		for (int i = 0; i < _vecSurfaceMtlData.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecSurfaceMtlData[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecSurfaceMtlData[i].mtlName));
			_meshSurface->DrawSubset(i);
		}
	}

	else
	{
		//맵 출력
		for (int i = 0; i < _vecMapMtlData.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecMapMtlData[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecMapMtlData[i].mtlName));
			_meshMap->DrawSubset(i);
		}
	}
}

void background::release()
{
	SAFE_RELEASE(_meshMap);
	SAFE_RELEASE(_meshSurface);


}

void background::setLigh()
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
