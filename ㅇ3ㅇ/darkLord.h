#pragma once
#include "enemy.h"
class darkLord : public enemy
{
public:
	darkLord();
	~darkLord();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

