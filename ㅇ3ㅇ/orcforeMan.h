#pragma once
#include "enemy.h"
class orcforeMan : public enemy
{
public:
	orcforeMan();
	~orcforeMan();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName);

	virtual void EnemyAI() override;

};

