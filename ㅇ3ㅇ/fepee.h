#pragma once
#include "player.h"

class fepee : public player
{
public:
	fepee();
	virtual ~fepee();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;

	virtual void attack() override;

	virtual void useSkill1() override;
	virtual void useSkill2() override;
	virtual void useSkill3() override;

	void createPoisonArrow(D3DXVECTOR3 startPosition, D3DXVECTOR3 dir, float angle);
};

