#pragma once
#include "enemy.h"
class darkLord : public enemy
{
public:
	darkLord();
	~darkLord();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

