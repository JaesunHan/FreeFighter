#pragma once
#include "item.h"
class item_gold : public item
{
public:
	item_gold();
	~item_gold();

	virtual void init(const WCHAR* folder, const WCHAR* file, D3DXVECTOR3 Position, float gold);
	virtual void render();
};

