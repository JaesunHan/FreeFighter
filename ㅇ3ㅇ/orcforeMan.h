#pragma once
#include "enemy.h"
class orcforeMan : public enemy
{
public:
	orcforeMan();
	~orcforeMan();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

};

