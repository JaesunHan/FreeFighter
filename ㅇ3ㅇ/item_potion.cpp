#include "stdafx.h"
#include "item_potion.h"


item_potion::item_potion()
{
}


item_potion::~item_potion()
{
}

void item_potion::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra)
{
	_vScale = sca;
	_vRotate = rot;
	_vTrans = tra;

	//파일 위치
	_itemMesh = OBJLOADER->load(_T(".\\obj\\box.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(tra);
		//_itemMesh[i].rotateWorld(0,0,0);
		_itemMesh[i].update();
	}


	//D3DXVECTOR3 scaleV(0.16f, 0.16f, 0.16f);
	//_translationV = D3DXVECTOR3(-1.47f, -1.0f, 0.0f);
	//for (int i = 0; i < _vecGround.size(); ++i)
	//{
	//	_vecGround[i].scaleWorld(scaleV.x, scaleV.y, scaleV.z);
	//	_vecGround[i].positionWorld(_translationV);
	//	//_vecGround[i].rotateWorld(0.0f, D3DX_PI - 0.16f, 0.0f);
	//	_vecGround[i].update();
	//}

	_itemType = POTION;

	_itemEffect = 100;

}
