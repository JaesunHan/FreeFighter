#pragma once
#include "enemy.h"
class gargoyle : public enemy
{
public:
	gargoyle();
	~gargoyle();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;

	virtual void SetStatus(int stage) override;
};

