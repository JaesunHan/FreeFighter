#pragma once
#include "enemy.h"
class zaken : public enemy
{
public:
	zaken();
	~zaken();

	virtual void SetStatus(int stage) override;

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

