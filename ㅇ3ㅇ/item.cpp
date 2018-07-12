#include "stdafx.h"
#include "item.h"
#include "skinnedMesh.h"



item::item()
	: _applyData(0.0f)
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

void item::init(const WCHAR * folder, const WCHAR * file)
{
	WCHAR strFileName[1024];
	swprintf(strFileName, _T(".\\%s\\%s"), folder, file);

	_itemMesh = OBJLOADER->loadMesh(_vecItemMtlData, strFileName);

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
}


