#pragma once
#include "enemy.h"
class zaken : public enemy
{
public:
	zaken();
	~zaken();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

