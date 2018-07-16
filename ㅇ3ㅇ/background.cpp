#include "stdafx.h"
#include "background.h"
#include "cube.h"

background::background()
	: _sky(NULL)
	, _cntWallsController(0)
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

	//if (_isDebug)
	//{
	//	D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);
	//	//����� ����� ���� surface ���
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
		D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);
		D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
		D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		//�� ���
		for (int i = 0; i < _vecMapMtlData.size(); ++i)
		{
			D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecMapMtlData[i].textureName));
			D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecMapMtlData[i].mtlName));
			_meshMap->DrawSubset(i);
		}
		D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//}

	
}

void background::release()
{
	SAFE_RELEASE(_meshMap);
	SAFE_RELEASE(_meshSurface);


}

void background::setLigh()
{
	//�¾�
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

void background::createGroundController(PxControllerManager ** cm, PxMaterial * m, D3DXVECTOR3 sizeVector)
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

	createWallsController();

	//��Ʈ�ѷ� �� ȸ�� ��Ű�� ���
	//D3DXVECTOR3  dir = D3DXVECTOR3(-1, 0, 1);
	//D3DXVec3Normalize(&dir, &dir);
	//PxVec3 tmpDir;
	//tmpDir.x = dir.x, tmpDir.y = dir.y, tmpDir.z = dir.z;
	//_pController->setUpDirection(tmpDir);



}

void background::createWallsController()
{
	//�⺻������ 8������ ���� �̸� ����� ���� �� ������ �ݺ��� ���鼭 �˸��� ���� �����Ͽ� �˸��� ��ġ�� ��ġ�Ѵ�.
	vector<PxController*> baseWalls;
	D3DXVECTOR3 szV = D3DXVECTOR3(10, 4, 10);
	float		PI4 = D3DX_PI / 4.0f;
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(-10, 3, 0), PxVec3(-1, 0, 0), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(-10*cosf(PI4), 3, 10 *-sinf(PI4)), PxVec3(-1,	0,	1), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(0,3,10), PxVec3(0,	0,	1), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(10 *cosf(PI4), 3, 10 * -sinf(PI4)), PxVec3(1,	0,	1), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(10, 3,0), PxVec3(1,	0,	0), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(10 *cosf(PI4), 3, -10 * -sinf(PI4)), PxVec3(1,	0,	-1), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(0,3,-10), PxVec3(0,	0,	-1), szV));
	baseWalls.push_back(createWallBaseController(PxExtendedVec3(-10 *cosf(PI4), 3, -10 * -sinf(PI4)), PxVec3(-1,	0,	-1), szV));

	//���� ���� ������ �����ʿ� �ξ��� ���� �������� �Ѵ�
	//���� ���
	_vecWallsController.push_back(baseWalls[0]);
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[2]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(-40, 0, 40), 6, 0);


	//���� �ϴ�
	_vecWallsController.push_back(baseWalls[0]);
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[6]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(-40, 0, -40), 6, 6);
	
	//������ �ϴ�
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[4]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[6]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(40, 0, -40), 6, 12);
	
	//������ ���
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[2]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[4]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(40, 0, 40), 6, 18);
	
	//���� �߾�
	_vecWallsController.push_back(baseWalls[0]);
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(-40, 0, 0), 5, 24);
	
	//�߾� ����
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[2]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[6]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(0, 0, 40), 6, 29);
	
	//�߾� �߾�
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[2]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[6]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(0, 0, 0), 6, 35);
	
	//�߾� �Ʒ���
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[2]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[6]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(0, 0, -40), 6, 41);
	
	//������ �߾�
	_vecWallsController.push_back(baseWalls[1]);
	_vecWallsController.push_back(baseWalls[3]);
	_vecWallsController.push_back(baseWalls[5]);
	_vecWallsController.push_back(baseWalls[7]);
	setWallsControllerPos(D3DXVECTOR3(0, 0, 0), 4, 47);

}
//														�� ��ġ,				������,			�� ������
PxController * background::createWallBaseController(PxExtendedVec3 pos, PxVec3 upDir, D3DXVECTOR3 sizeVector)
{

	PxController* con; 

	PxBoxControllerDesc	desc;
	desc.position = pos;
	desc.halfSideExtent = sizeVector.x / 2;
	desc.halfForwardExtent = sizeVector.z / 2;
	desc.halfHeight = sizeVector.y / 2;
	desc.stepOffset = 0.1f;
	//desc.volumeGrowth = 1.0;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = _pMaterial;

	con = (*_pCM)->createController(desc);
	con->setFootPosition(pos);
	con->setUserData(this);
	char strName[1024];
	sprintf_s(strName, "mapWallsController%d", _cntWallsController++);

	con->getActor()->setName(strName);

	//��Ʈ�ѷ� �� ȸ�� ��Ű�� ���
	D3DXVECTOR3  dir = D3DXVECTOR3(upDir.x, upDir.y, upDir.z);
	D3DXVec3Normalize(&dir, &dir);
	PxVec3 tmpDir;
	tmpDir.x = dir.x, tmpDir.y = dir.y, tmpDir.z = dir.z;
	con->setUpDirection(tmpDir);
	con->setFootPosition(pos);


	return con;
}

void background::setWallsControllerPos(D3DXVECTOR3 vCenter, int wallsNum, int startIdx)
{

	for (int i = startIdx; i < startIdx + wallsNum; ++i)
	{
		PxExtendedVec3 vPrevPos;
		vPrevPos.x = _vecWallsController[i]->getPosition().x, 
			vPrevPos.y = _vecWallsController[i]->getPosition().y, 
			vPrevPos.z = _vecWallsController[i]->getPosition().z;
		PxExtendedVec3			vChngPos;
		vChngPos.x = vPrevPos.x + vCenter.x;
		vChngPos.y = vPrevPos.y + vCenter.y;
		vChngPos.z = vPrevPos.z + vCenter.z;
		
		_vecWallsController[i]->setFootPosition(vChngPos);
	}

}

void background::setSky()
{
	_sky = new cube;
	_sky->init();
	//�ϴ��� �������� 1000���� ���δ�.
	_sky->scaleLocal(1000.0f, 1000.0f, 1000.0f);
	_sky->SetMtlTexName(_T("storeSkyMaterial"), _T("storeSkyTexture"));
	LPDIRECT3DTEXTURE9 skyTexture;
	TEXTUREMANAGER->addTexture(_sky->GetTexName(), _T(".\\texture\\sky\\sky2.jpg"));
	D3DMATERIAL9		skyMaterial;
	ZeroMemory(&skyMaterial, sizeof(skyMaterial));
	skyMaterial.Ambient = D3DXCOLOR(255, 255, 255, 255);

	MATERIALMANAGER->addMaterial(_sky->GetMtlName(), skyMaterial);

}

