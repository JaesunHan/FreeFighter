#pragma once
#include "enemy.h"
class bloodyQueen : public enemy
{
public:
	bloodyQueen();
	~bloodyQueen();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

