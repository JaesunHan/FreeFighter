#pragma once
#include "fightEnemy.h"
class fightWoodGiant : public fightEnemy
{
private:
	bool _useSkill;

public:
	fightWoodGiant();
	~fightWoodGiant();

	virtual void Attack02();

	virtual void UseSkill01();
	virtual void UseSkill02();
	virtual void UseSkill03();
};

