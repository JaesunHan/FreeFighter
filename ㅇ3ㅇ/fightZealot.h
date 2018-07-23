#pragma once
#include "fightEnemy.h"
class fightZealot : public fightEnemy
{

public:
	fightZealot();
	~fightZealot();

	virtual void SetStatus(int stage);

	virtual void UseSkill01();
	virtual void UseSkill02();
	virtual void UseSkill03();
};

