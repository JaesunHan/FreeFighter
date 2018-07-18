#pragma once
#include "player.h"

class enemy;

class zealot : public player
{
private:
	enemy*  _target;

public:
	zealot();
	virtual ~zealot();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;

	virtual void Update() override;

	virtual void attackEnemy() override;

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;
};
