#pragma once
#include "interfaceCharacter.h"
#include "playerController.h"
#include "character.h"

class Enemy;


class player : public interfaceCharacter, public playerController
{
private:
	Enemy * _enemy;

public:
	player();
	~player();

	// interfaceCharacter에게 상속받은 함수
	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update() override;
	virtual void Render() override;



	void SetEnemyAdressLink(Enemy* pE) { _enemy = pE; }
};

