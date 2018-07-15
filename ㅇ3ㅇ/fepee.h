#pragma once
#include "player.h"

class fepee : public player
{
public:
	fepee();
	virtual ~fepee();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;
};

