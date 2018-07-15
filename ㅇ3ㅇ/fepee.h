#pragma once
#include "player.h"

class fepee : public player
{
public:
	fepee();
	virtual ~fepee();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;
};

