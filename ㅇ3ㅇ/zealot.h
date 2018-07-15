#pragma once
#include "player.h"

class zealot : public player
{
private:

public:
	zealot();
	virtual ~zealot();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;

	virtual void Update() override;

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;
};
