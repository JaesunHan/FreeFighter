#pragma once
#include "enemy.h"

class hpBar;

class darkLord : public enemy
{
private:


public:
	darkLord();
	~darkLord();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

	virtual void SetStatus(int stage) override;

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;
};

