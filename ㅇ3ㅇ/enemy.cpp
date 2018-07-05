#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"


enemy::enemy()
	: _distance(0.0f)
{
}


enemy::~enemy()
{
}

void enemy::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	enemyController::Init();
	_skinnedMesh->setParentMatrix(&_worldTM);
}

void enemy::Update()
{
	if (_targetPos && !YouAndIDistance())
		_act = ACT_RUN_FRONT;

	if (!YouAndIDistance())
	{
		enemyController::Moving();
	}
	else
	{
		_act = ACT_IDLE;
		EnemyAI();
	}

	interfaceCharacter::Update();
}

void enemy::Render()
{
	interfaceCharacter::Render();
}

void enemy::SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_worldSca = sca;
	_worldRot = rot;
	_worldPos = pos;

	enemyController::Init();
}

void enemy::SetDistance(float dis)
{
	_distance = dis;
}

bool enemy::YouAndIDistance()
{
	if (_targetPos)
	return D3DXVec3Length(&(_worldPos - *_targetPos)) < _distance;
}

float enemy::YouAndIDistance(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02)
{
	return D3DXVec3Length(&(pos01 - pos02));
}

