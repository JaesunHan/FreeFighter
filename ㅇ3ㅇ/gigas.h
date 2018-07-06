#pragma once
#include "player.h"

class gigas : public player
{
private:
	player * _playerCharacter;
public:
	gigas();
	gigas(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	~gigas();
};

