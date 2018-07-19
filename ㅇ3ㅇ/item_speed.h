#pragma once
#include "item.h"

class item_speed : public item
{
public:
	item_speed();
	virtual ~item_speed();

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra);
};

