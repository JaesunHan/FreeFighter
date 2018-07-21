#pragma once
#include "item.h"

class item_damage : public item
{
public:
	item_damage();
	virtual ~item_damage();

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos);
};