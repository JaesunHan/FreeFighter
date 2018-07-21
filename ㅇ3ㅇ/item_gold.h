#pragma once
#include "item.h"
class item_gold : public item
{
public:
	item_gold();
	~item_gold();

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos);
};

