#include "stdafx.h"
#include "item.h"
#include "skinnedMesh.h"
#include "gameObject.h"




item::item()
	: _itemEffect(0.0f)
	, _itemMesh(NULL)
	, _itemController(NULL)
{
	D3DXMatrixIdentity(&_matWorld);
	_vTrans = D3DXVECTOR3(0, 0, 0);
	_vScale = D3DXVECTOR3(1, 1, 1);
	_vRotate = D3DXVECTOR3(0, 0, 0);
}


item::~item()
{
}

#ifdef UNICODE

//파일만 읽는 이닛함수
void item::init()
{
}

//파일이랑 포지션도 포함인 이닛함수
void item::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra)
{

}

//파일이랑 포지션이랑 골드량
void item::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra, float gold)
{

}

#else
void item::init(const char * folder, const char * file)
{
}
#endif // UNICODE

void item::update()
{

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_itemMesh[i].update();
		//_itemMesh[i].rotateLocal(0, 1, 0);
		//_itemMesh[i].rotateWorld(0, 0, 0);
	}

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
		_itemMesh[i].render();
		//_itemMesh[i].rotateLocal(0, 5, 0);
		//_itemMesh[i].rotateWorld(0, 5, 0);
	}

	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);


	//아이템 원
}

void item::release()
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

