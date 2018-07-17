#pragma once
#include "enemy.h"
class bloodyQueen : public enemy
{
public:
	bloodyQueen();
	~bloodyQueen();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

