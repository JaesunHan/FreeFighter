#pragma once
#include "fightEnemy.h"
class fightFepee : public fightEnemy
{
public:
	fightFepee();
	~fightFepee();

	virtual void SetStatus(int stage);

	virtual void UseSkill01();
	virtual void UseSkill02();
	virtual void UseSkill03();
};

