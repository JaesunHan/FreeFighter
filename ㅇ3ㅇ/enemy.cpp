#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

void enemy::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
}

void enemy::Update()
{
	interfaceCharacter::Update();

	if (_targetPos)
		_act = ACT_RUN;
	else _act = ACT_IDLE;

	enemyController::Moving();
}

void enemy::Render()
{
	interfaceCharacter::Render();
}


bool enemy::YouAndIDistance(D3DXVECTOR3 playerPos, float num)
{
	return D3DXVec3Length(&(_worldPos - playerPos)) < num;
}

