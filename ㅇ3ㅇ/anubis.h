#pragma once
#include "enemy.h"

class anubis : public enemy
{
public:
	anubis();
	~anubis();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

