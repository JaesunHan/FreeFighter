#pragma once
#include "enemy.h"
class orcforeMan : public enemy
{
public:
	orcforeMan();
	~orcforeMan();

	// enemy��(��) ���� ��ӵ�
	virtual void EnemyAI() override;
};

