#pragma once
#include "player.h"

class woodGiantPlayer : public player
{
public:
	woodGiantPlayer();
	~woodGiantPlayer();

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;
};

