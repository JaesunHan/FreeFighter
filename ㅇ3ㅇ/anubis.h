#pragma once
#include "enemy.h"

class anubis : public enemy
{
public:
	anubis();
	~anubis();

	virtual void SetStatus(int stage) override;

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

