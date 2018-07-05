#include "stdafx.h"
#include "lucius.h"


lucius::lucius()
{
}

lucius::lucius(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	_worldScale = scale;
	_worldPos = position;
}


lucius::~lucius()
{
}
