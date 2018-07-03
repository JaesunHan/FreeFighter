#pragma once
#include "enemy.h"
class woodGiant01 : public enemy
{
public:
	woodGiant01();
	~woodGiant01();

	// enemy을(를) 통해 상속됨
	virtual void EnemyAI() override;
};

