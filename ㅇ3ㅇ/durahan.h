#pragma once
#include "enemy.h"

class durahan : public enemy
{
public:
	durahan();
	~durahan();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

