#include "stdafx.h"
#include "knight.h"


knight::knight()
{
}

knight::knight(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	_worldScale = scale;
	_worldPos = position;
}


knight::~knight()
{
}
