#pragma once
#include "player.h"

class knight : public player
{
private:
	PLAYER_KEYSET	_keySet;
public:
	knight();
	virtual ~knight();

	virtual void Init(wstring keyPath, wstring keyName);

	virtual void movement();

};

