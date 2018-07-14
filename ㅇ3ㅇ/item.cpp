#include "stdafx.h"
#include "item.h"
#include "skinnedMesh.h"



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
void item::init(const WCHAR * folder, const WCHAR * file)
{
}

//�����̶� �����ǵ� ������ �̴��Լ�
void item::init(const WCHAR * folder, const WCHAR * file,D3DXVECTOR3 Position)
{
	
}

//�����̶� �������̶� ��差
void item::init(const WCHAR * folder, const WCHAR * file, D3DXVECTOR3 Position, float gold)
{
}

#else
void item::init(const char * folder, const char * file)
{
}
#endif // UNICODE

void item::update()
{
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixTranslation(&matT, _vTrans.x, _vTrans.y, _vTrans.z);
	D3DXMatrixScaling(&matS, _vScale.x, _vScale.y, _vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, _vRotate.y, _vRotate.x, _vRotate.z);

	_matWorld = matS * matR * matT;
}

void item::render()
{
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_matWorld);

	for (int i = 0; i < _vecItemMtlData.size(); ++i)
	{
		D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_vecItemMtlData[i].textureName));
		D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_vecItemMtlData[i].mtlName));
		_itemMesh->DrawSubset(i);
	}
}

void item::release()
{
}

void item::usingItem(float& data)	
{

}

void item::usingItem(int & data)
{
	if (_itemType == GOLD)
	{

	}
}

void item::onTriggerItem()
{
	//����, ������ ���� �ִ°� �÷��̾���
	//{
	//	�������� ������ �÷��̾�� ������ �ڵ徲��
	//	������ ��Ʈ����
	//}

	//�� �ܿ��� �ȵ�
}

void item::getItem()
{
	switch (_itemType)
	{
	case NONE:
		break;
	case POTION:
		//ĳ���� HP ����
		break;
	case GOLD:
		//ĳ���� ��� ����
		break;
	case END:
		break;
	default:
		break;
	}
}


