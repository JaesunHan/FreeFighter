#include "stdafx.h"
#include "item_speed.h"


item_speed::item_speed()
{
}


item_speed::~item_speed()
{
}

void item_speed::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra)
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

	_itemType = SPEED;

	float speedBoostTime;
	speedBoostTime = 15.0f;

	if (speedBoostTime > 0)
	{
		_speedBoost = true;
		speedBoostTime--;
		if (speedBoostTime == 0)
		{
			_speedBoost = false;
		}
	}
}
