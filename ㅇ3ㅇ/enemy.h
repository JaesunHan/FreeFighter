#pragma once
#include "interfaceCharacter.h"
#include "enemyController.h"

class enemy : public interfaceCharacter, public enemyController
{
private:

public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render() override;

	virtual bool YouAndIDistance(D3DXVECTOR3 playerPos, float num);
	virtual void EnemyAI() = 0;

};

