#pragma once
#include "enemy.h"
class mudGolem : public enemy
{
public:
	mudGolem();
	~mudGolem();

	virtual void SetStatus(int stage) override;

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

