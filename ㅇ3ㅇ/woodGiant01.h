#pragma once
#include "enemy.h"
class woodGiant01 : public enemy
{
public:
	woodGiant01();
	~woodGiant01();

	// enemy��(��) ���� ��ӵ�
	virtual void EnemyAI() override;
};

