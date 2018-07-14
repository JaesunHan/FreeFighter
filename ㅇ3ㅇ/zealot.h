#pragma once
#include "player.h"

class zealot : public player
{
public:
	zealot();
	virtual ~zealot();

	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName) override;
};

