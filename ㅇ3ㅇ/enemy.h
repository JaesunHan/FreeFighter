#pragma once
#include "interfaceCharacter.h"
#include "enemyController.h"

class player;

class enemy : public interfaceCharacter, public enemyController
{
private:
	player* _player;

public:
	enemy();
	~enemy();

	// interfaceCharacter을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	// enemyController을(를) 통해 상속됨
	virtual void EnemyAI() override;
	virtual bool YouAndMeDistance(D3DXVECTOR3 playerPos, float num) override;

	void SetPlayerMemAdressLink(player* pP) { _player = pP; }

};

