#include "stdafx.h"
#include "enemyController.h"


enemyController::enemyController()
	: _worldPos(0, 0, 0)
	, _worldDir(0, 0, 1)
{
	D3DXMatrixIdentity(&_worldTM);
}


enemyController::~enemyController()
{

}
