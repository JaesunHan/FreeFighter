#pragma once
#include "item.h"

class item_potion : public item
{
public:
	item_potion();
	~item_potion();

	virtual void init(const WCHAR* folder, const WCHAR* file, D3DXVECTOR3 Position);
	virtual void render();
};

