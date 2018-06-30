#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

void enemy::Update()
{
	EnemyAI();
}

void enemy::Render()
{
}

void enemy::EnemyAI()
{
	
}

bool enemy::YouAndMeDistance(D3DXVECTOR3 playerPos, float num)
{
	return D3DXVec3Length(&(_worldPos - playerPos)) < num;
}

