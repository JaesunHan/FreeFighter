#pragma once
#include "enemy.h"

class anubis : public enemy
{
public:
	anubis();
	~anubis();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

