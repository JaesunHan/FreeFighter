#pragma once
#include "player.h"

class knight : public player
{
private:
	player * _playerCharacter;
public:
	knight();
	knight(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	~knight();
};

