#pragma once
#include "enemy.h"
class kerberos : public enemy
{
private:
	D3DXVECTOR3 _tempDir;

public:
	kerberos();
	~kerberos();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;

	virtual void EnemyStoryAI() override;
};

