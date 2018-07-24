#include "stdafx.h"
#include "item_potion.h"


item_potion::item_potion()
{
}


item_potion::~item_potion()
{
}

void item_potion::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_vPosition = pos;
	_vScale = sca;
	_vRotate = rot;
	//_vTrans = tra;
	//
	//int rndSuchi;

	//���� ��ġ
	_itemMesh = OBJLOADER->load(_T("obj"), _T("potion.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		D3DXCreateSphere(g_pD3DDevice, 0.15f, 20, 20, &_Mesh, NULL);
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(pos);
		_itemMesh[i].rotateWorld(rot.x, rot.y, rot.z);
		_itemMesh[i].update();
	}

	_itemType = ITEM_POTION;

	_itemEffect = rand() % 101;

	
	item::init(sca, rot, pos);
}


