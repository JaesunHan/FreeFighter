#include "stdafx.h"
#include "knight.h"


knight::knight()
{
}

knight::knight(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	_worldScale = scale;
	_worldPos = position;

	_playerCharacter = new player;
	_playerCharacter->Init(PLAYER_1P, _T(".\\xFile\\knight"), _T("knight.X"));

}


knight::~knight()
{
}
