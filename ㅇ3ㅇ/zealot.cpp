#include "stdafx.h"
#include "zealot.h"


zealot::zealot()
{
}


zealot::~zealot()
{
}

void zealot::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_AniIndex[ACT_IDLE] = 4;
	_AniIndex[ACT_RUN_FRONT] = 3;
	_AniIndex[ACT_RUN_BACK] = 3;
	_AniIndex[ACT_ATTACK00] = 2;
	_AniIndex[ACT_ATTACK01] = 1;
	_AniIndex[ACT_ATTACK02] = 0;
	_AniIndex[ACT_ATTACKED00] = 4;
	_AniIndex[ACT_DEATH] = 4;

	player::Init(p, character, keyPath, keyName);
}
