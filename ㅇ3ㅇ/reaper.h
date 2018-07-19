#pragma once
#include "player.h"

class reaper : public player
{
public:
	reaper();
	virtual ~reaper();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;

	virtual void attack() override;

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;

	void createDrakAura(D3DXVECTOR3 pos);
};

