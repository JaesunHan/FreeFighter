#pragma once
#include "enemy.h"

class darkWolf : public enemy
{
public:
	darkWolf();
	darkWolf(D3DXVECTOR3 sca , D3DXVECTOR3 pos);
	virtual ~darkWolf();

	// enemy을(를) 통해 상속됨
	virtual void EnemyAI() override;
};

