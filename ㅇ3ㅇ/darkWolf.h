#pragma once
#include "enemy.h"

class darkWolf : public enemy
{
public:
	darkWolf();
	virtual ~darkWolf();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName);

	virtual void EnemyAI() override;

};

