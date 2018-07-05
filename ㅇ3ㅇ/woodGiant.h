#pragma once
#include "enemy.h"
class woodGiant : public enemy
{
public:
	woodGiant();
	~woodGiant();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName);

	virtual void EnemyAI() override;

};

