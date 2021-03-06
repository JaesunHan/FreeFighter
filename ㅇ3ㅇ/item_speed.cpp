#include "stdafx.h"
#include "item_speed.h"


item_speed::item_speed()
{
}


item_speed::~item_speed()
{
}

void item_speed::init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_vPosition = pos;
	_vScale = sca;
	_vRotate = rot;
	//_vTrans = tra;

	int rndSuchi;

	//���� ��ġ
	_itemMesh = OBJLOADER->load(_T("obj"), _T("shoes.obj"));

	for (int i = 0; i < _itemMesh.size(); ++i)
	{
		D3DXCreateSphere(g_pD3DDevice, 0.15f, 20, 20, &_Mesh, NULL);
		_itemMesh[i].scaleWorld(sca.x, sca.y, sca.z);
		_itemMesh[i].positionWorld(pos);
		_itemMesh[i].rotateWorld(rot.x, rot.y, rot.z);
		_itemMesh[i].update();
	}

	_itemType = ITEM_SPEED;

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

	item::init(sca, rot, pos);
}
