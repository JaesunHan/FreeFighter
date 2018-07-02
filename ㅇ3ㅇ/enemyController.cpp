#include "stdafx.h"
#include "enemyController.h"


enemyController::enemyController()
	: _worldPos(0, 0, 0)
	, _worldDir(0, 0, 1)
	, _targetPos(NULL)
	, _speed(0)
{
	D3DXMatrixIdentity(&_worldTM);
}


enemyController::~enemyController()
{

}

void enemyController::Moving()
{
	if (_targetPos)
	{
		_worldDir = (*_targetPos) - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);

		_worldPos += _worldDir * _speed;

		D3DXMATRIX matT;
		D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

		_worldTM = matT;
	}

	
}
