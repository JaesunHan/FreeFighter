#pragma once
#include "player.h"

class lucius : public player
{
private:
	player * _playerCharacter;
public:
	lucius();
	lucius(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	~lucius();
};

