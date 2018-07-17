#pragma once
#include "enemy.h"

class durahan : public enemy
{
public:
	durahan();
	~durahan();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

