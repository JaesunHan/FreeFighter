#pragma once
#include "player.h"

class gigas : public player
{
private:
	PLAYER_KEYSET	_keySet;

public:
	gigas();
	virtual ~gigas();

	virtual void Init(wstring keyPath, wstring keyName);

	virtual void movement();
};

