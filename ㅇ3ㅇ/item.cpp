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

//���ϸ� �д� �̴��Լ�
void item::init()
{
}

//�����̶� �����ǵ� ������ �̴��Լ�
void item::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra)
{

}

//�����̶� �������̶� ��差
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


	//������ ����
	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_itemMesh[i].render();
		//_itemMesh[i].rotateLocal(0, 5, 0);
		//_itemMesh[i].rotateWorld(0, 5, 0);
	}

	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);


	//������ ��
}

void item::release()
{
}


//����, ������ ���� �ִ°� �÷��̾���
void item::onTriggerItem()
{

	//{
	//	�������� ������ �÷��̾�� ������ �ڵ徲��
	//	������ ��Ʈ����
	//}



	//�� �ܿ��� �ȵ�
}

void item::getItem()
{
	//switch (_itemType)
	//{
	//case NONE:
	//	break;
	//case POTION:
	//	//ĳ���� HP ����
	//
	//	break;
	//case GOLD:
	//	//ĳ���� ��� ����
	//
	//	break;
	//case END:
	//	break;
	//default:
	//	break;
	//}
}

