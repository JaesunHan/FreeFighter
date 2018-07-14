#include "stdafx.h"
#include "background.h"
#include "cube.h"

background::background()
	: _sky(NULL)
{
}


background::~background()
{
	SAFE_DELETE(_sky);
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
	if (_sky)
		_sky->render();

	if (_isDebug)
	{
		D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);
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
		D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);
		D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
		D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		//맵 출력
		for (int i = 0; i < _vecMapMtlData.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecMapMtlData[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecMapMtlData[i].mtlName));
			_meshMap->DrawSubset(i);
		}
		D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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

void background::createController(PxControllerManager ** cm, PxMaterial * m, D3DXVECTOR3 sizeVector)
{
	PxBoxControllerDesc	desc;
	desc.position = PxExtendedVec3(0, 0, 0);
	desc.halfSideExtent = sizeVector.x/2;			
	desc.halfForwardExtent = sizeVector.z/2;		
	desc.halfHeight = sizeVector.y/2;
	desc.stepOffset = 0.1f;
	desc.volumeGrowth = 1.0;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_pMaterial = m;

	_pController = (*cm)->createController(desc);
	_pCM = cm;
	_pController->setFootPosition(PxExtendedVec3(0, 0, 0));
	_pController->setUserData(this);
	_pController->getActor()->setName("storyMapController");

}

void background::setSky()
{
	_sky = new cube;
	_sky->init();
	//하늘의 스케일을 1000정도 높인다.
	_sky->scaleLocal(1000.0f, 1000.0f, 1000.0f);
	_sky->SetMtlTexName(_T("storeSkyMaterial"), _T("storeSkyTexture"));
	LPDIRECT3DTEXTURE9 skyTexture;
	TEXTUREMANAGER->addTexture(_sky->GetTexName(), _T(".\\texture\\sky\\sky2.jpg"));
	D3DMATERIAL9		skyMaterial;
	ZeroMemory(&skyMaterial, sizeof(skyMaterial));
	skyMaterial.Ambient = D3DXCOLOR(255, 255, 255, 255);

	MATERIALMANAGER->addMaterial(_sky->GetMtlName(), skyMaterial);

}