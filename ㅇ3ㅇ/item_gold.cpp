#include "stdafx.h"
#include "item_gold.h"


item_gold::item_gold()
{
}


item_gold::~item_gold()
{
}

void item_gold::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_vPosition = pos;
	_vScale = sca;
	_vRotate = rot;
	//_vTrans = tra;

	//파일 위치
	_itemMesh = OBJLOADER->load(_T("obj"), _T("box.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(pos);
		_itemMesh[i].rotateWorld(rot.x, rot.y, rot.z);
		_itemMesh[i].update();
	}

	_itemType = ITEM_GOLD;

	_itemEffect = rand() % 101;

	item::init(sca, rot, pos);
}