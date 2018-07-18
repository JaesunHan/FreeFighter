#include "stdafx.h"
#include "item_gold.h"


item_gold::item_gold()
{
}


item_gold::~item_gold()
{
}

void item_gold::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra, float gold)
{
	_vScale = sca;
	_vRotate = rot;
	_vTrans = tra;

	//파일 위치
	_itemMesh = OBJLOADER->load(_T("obj"), _T("box.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(tra);
		//_itemMesh[i].rotateWorld(0.0f, D3DX_PI - 0.16f, 0.0f);
		_itemMesh[i].update();
	}

	_itemType = GOLD;

	_itemEffect = gold;



}

void item_gold::render()
{

}
