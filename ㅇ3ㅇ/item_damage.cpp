#include "stdafx.h"
#include "item_damage.h"


item_damage::item_damage()
{
}


item_damage::~item_damage()
{
}

void item_damage::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra)
{
	_vScale = sca;
	_vRotate = rot;
	_vTrans = tra;

	int rndSuchi;

	//파일 위치
	_itemMesh = OBJLOADER->load(_T("obj"), _T("box.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(tra);
		//_itemMesh[i].rotateWorld(0,0,0);
		_itemMesh[i].update();
	}

	_itemType = ATTACK;

	float attackBoostTime;
	attackBoostTime = 10.0f;

	if (attackBoostTime > 0)
	{
		_attackBoost = true;
		attackBoostTime--;
		if (attackBoostTime == 0)
		{
			_attackBoost = false;
		}
	}
}
