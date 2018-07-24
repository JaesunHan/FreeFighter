#include "stdafx.h"
#include "item.h"
#include "skinnedMesh.h"
#include "gameObject.h"




item::item()
	: _itemEffect(0.0f)
	, _itemMesh(NULL)
	, _isAir(TRUE)
	, _isNotGravity(FALSE)
	, _Mesh(NULL)
	, _angleX(0)
	, _angleY(0.1f)
	, _angleZ(0)
	, _radius(1.0f)
	//, _itemController(NULL)
{
	D3DXMatrixIdentity(&_matWorld);
	_vPosition = D3DXVECTOR3(0, 0, 0);
	_vTrans = D3DXVECTOR3(0, 0.5f, 0);
	_vScale = D3DXVECTOR3(1, 1, 1);
	_vRotate = D3DXVECTOR3(0, 0, 0);
}


item::~item()
{
	SAFE_RELEASE(_Mesh);
}

#ifdef UNICODE

//파일만 읽는 이닛함수
void item::init()
{
}

//파일이랑 포지션도 포함인 이닛함수
void item::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_startHeight = pos.y- 0.85f;
}

//파일이랑 포지션이랑 골드량
void item::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos, float gold)
{

}

#else
void item::init(const char * folder, const char * file)
{
}
#endif // UNICODE

void item::update()
{
	if (_isAir)
	{
		for (int i = 0; i < _itemMesh.size(); ++i)
		{
			//_itemMesh[i].rotateWorld(0,0.3f,0);
			_itemMesh[i].translateWorld(D3DXVECTOR3(0, _vTrans.y, 0));
			_vPosition += _vTrans;
			_vTrans += D3DXVECTOR3(0.0f, -0.03f, 0.0f);
			_itemMesh[i].update();
		}
	}

	if (_vPosition.y < _startHeight)
	{
		_vPosition.y = _startHeight;
		_isAir = FALSE;
	}
	
	if(_isAir==FALSE)
	{
		for (int i = 0; i < _itemMesh.size(); ++i)
		{
			_itemMesh[i].rotateWorld(_vRotate.x, _vRotate.y, _vRotate.z);
			_vRotate.y = 0.1f;
			_itemMesh[i].update();
		}
	}

	//if (_isNotGravity == true)
	//{
	//	for (int i = 0; i < _itemMesh.size(); ++i)
	//	{
	//		_itemMesh[i].translateWorld(D3DXVECTOR3(0, _vTrans.y, 0));
	//		_vPosition += _vTrans;
	//		_itemMesh[i].update();
	//	}
	//}
	//if (_vPosition.y >= _curveHeight)
	//{
	//	_vPosition.y -= _vTrans.y;
	//}

	D3DXMATRIX matT, matR, matS;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);

	D3DXMatrixScaling(&matS,2,2,2);
	D3DXMatrixTranslation(&matT, _vPosition.x, _vPosition.y, _vPosition.z);
	D3DXMatrixRotationYawPitchRoll(&matR, _vRotate.y, _vRotate.x, _vRotate.z);

	_matWorld = matS * matR * matT;
	//upDown();

	//D3DXMATRIX matS, matR, matT;
	//
	//D3DXMatrixTranslation(&matT, _vTrans.x, _vTrans.y, _vTrans.z);
	//D3DXMatrixScaling(&matS, _vScale.x, _vScale.y, _vScale.z);
	//D3DXMatrixRotationYawPitchRoll(&matR, _vRotate.y, _vRotate.x, _vRotate.z);
	//
	//_matWorld = matS * matR * matT;
}

void item::render()
{
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_matWorld);

	//for (int i = 0; i < _itemMesh.size(); ++i)
	//{
	//	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_itemMesh[i].textureName));
	//	D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_itemMesh[i].mtlName));
	//	_itemMesh->DrawSubset(i);
	//}


	//아이템 렌더
	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_Mesh->DrawSubset(i);
		_itemMesh[i].render();
		//_itemMesh[i].rotateLocal(0, 5, 0);
		//_itemMesh[i].rotateWorld(0, 5, 0);
	}
	//_Mesh->DrawSubset(0);



	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);


	//아이템 원
}

void item::release()
{
	for (int i = 0; i < _itemMesh.size(); ++i)
		_itemMesh[i].release();
	_itemMesh.clear();
}

void item::upDown()
{

}



//만약, 아이템 위에 있는게 플레이어라면
void item::onTriggerItem()
{
	
	//{
	//	아이템의 정보를 플레이어에게 보내줄 코드쓰기
	//	아이템 디스트로이
	//}



	//그 외에는 안됨
}

void item::getItem()
{
	//switch (_itemType)
	//{
	//case NONE:
	//	break;
	//case POTION:
	//	//캐릭터 HP 증가
	//
	//	break;
	//case GOLD:
	//	//캐릭터 골드 증가
	//
	//	break;
	//case END:
	//	break;
	//default:
	//	break;
	//}
}