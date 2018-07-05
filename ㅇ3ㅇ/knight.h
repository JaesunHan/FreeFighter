#pragma once
#include "player.h"

class knight : public player
{
public:
	knight();
	knight(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	~knight();
};

