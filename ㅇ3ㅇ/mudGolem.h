#pragma once
#include "enemy.h"
class mudGolem : public enemy
{
public:
	mudGolem();
	~mudGolem();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

