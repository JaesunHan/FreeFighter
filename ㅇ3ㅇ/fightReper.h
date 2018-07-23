#pragma once
#include "fightEnemy.h"
class fightReper : public fightEnemy
{
private:
	bool _useSkill;

public:
	fightReper();
	~fightReper();

	virtual void Attack01();
	virtual void Attack02();

	virtual void UseSkill01();
	virtual void UseSkill02();
	virtual void UseSkill03();
};

