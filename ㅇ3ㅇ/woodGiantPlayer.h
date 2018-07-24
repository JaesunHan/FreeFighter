#pragma once
#include "player.h"

class woodGiantPlayer : public player
{
public:
	woodGiantPlayer();
	virtual ~woodGiantPlayer();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;
	virtual void Update() override;

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;

	void createLeafSkill();
	bool hitSkillEnemy();

	//void skillHitCheck(enemy* e);
};

