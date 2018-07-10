#pragma once
#include "player.h"

class aranzebia : public player
{
private:
	//PLAYER_KEYSET	_keySet;
public:
	aranzebia();
	virtual ~aranzebia();

	virtual void Init(PLAYERS p, wstring keyPath, wstring keyName);
	virtual void movement();

};

