#pragma once
#include "player.h"

class aranzebia : public player
{
private:
	player * _playerCharacter;
public:
	aranzebia();
	aranzebia(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	~aranzebia();
};

