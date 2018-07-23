#pragma once
#include "enemy.h"
class darkLord : public enemy
{
public:
	darkLord();
	~darkLord();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

	virtual void SetStatus(int stage) override;

	virtual void Attack01() override;
	virtual void Attack02() override;
	virtual void Attack03() override;

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;
};

