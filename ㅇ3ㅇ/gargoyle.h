#pragma once
#include "enemy.h"
class gargoyle : public enemy
{
public:
	gargoyle();
	~gargoyle();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

	virtual void Attack01() override;
	virtual void Attack02() override;
	virtual void Attack03() override;
};

