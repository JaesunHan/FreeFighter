#pragma once
#include "item.h"

class item_defence : public item
{
public:
	item_defence();
	virtual ~item_defence();

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos);
};