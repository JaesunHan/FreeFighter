#pragma once
#include "player.h"

class lucius : public player
{
private:
	//PLAYER_KEYSET	_keySet;
public:
	lucius();
	virtual 	~lucius();

	virtual void Init(PLAYERS p, wstring keyPath, wstring keyName);
	virtual void movement();

};

