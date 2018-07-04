#pragma once
#include "player.h"

class testMan :public player
{
public:
	testMan();
	testMan(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	~testMan();
};

