#pragma once
#include "enemy.h"
class woodGiant : public enemy
{
public:
	woodGiant();
	~woodGiant();

	// enemy��(��) ���� ��ӵ�
	virtual void EnemyAI() override;
};

