#pragma once
#include "enemy.h"
class gargoyle : public enemy
{
public:
	gargoyle();
	~gargoyle();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;

	virtual void SetStatus(int stage) override;
};

