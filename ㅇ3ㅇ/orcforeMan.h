#pragma once
#include "enemy.h"
class orcforeMan : public enemy
{
public:
	orcforeMan();
	~orcforeMan();

	// enemy을(를) 통해 상속됨
	virtual void EnemyAI() override;
};

