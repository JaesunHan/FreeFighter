#pragma once
#include "enemy.h"

class darkWolf : public enemy
{
public:
	darkWolf();
	virtual ~darkWolf();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName);

	virtual void EnemyAI() override;

};

