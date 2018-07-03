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

	// interfaceCharacter���� ��ӹ��� �Լ�
	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update() override;
	virtual void Render() override;



	void SetEnemyAdressLink(Enemy* pE) { _enemy = pE; }
};

