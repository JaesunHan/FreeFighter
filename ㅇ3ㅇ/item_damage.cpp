#include "stdafx.h"
#include "item_damage.h"


item_damage::item_damage()
{
}


item_damage::~item_damage()
{
}

void item_damage::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_vPosition = pos;
	_vScale = sca;
	_vRotate = rot;
	_radius = 0;
	//_vTrans = tra;

	int rndSuchi;

	//파일 위치
	_itemMesh = OBJLOADER->load(_T("obj"), _T("attack.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		D3DXCreateSphere(g_pD3DDevice, 0.15f, 20, 20, &_Mesh, NULL);
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(pos);
		_itemMesh[i].rotateWorld(rot.x, rot.y, rot.z);
		_itemMesh[i].update();
	}

	_itemType = ITEM_ATTACK;

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

	item::init(sca, rot, pos);
}
