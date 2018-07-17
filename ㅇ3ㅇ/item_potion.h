#pragma once
#include "item.h"

class item_potion : public item
{
public:
	item_potion();
	virtual ~item_potion();

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra);
};

