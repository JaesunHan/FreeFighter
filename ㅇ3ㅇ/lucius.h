#pragma once
#include "player.h"

class lucius : public player
{
private:
	player * _playerCharacter;
public:
	lucius();
	virtual 	~lucius();

	virtual void Init(wstring keyPath, wstring keyName);
};

