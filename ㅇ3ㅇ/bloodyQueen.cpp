#include "stdafx.h"
#include "bloodyQueen.h"


bloodyQueen::bloodyQueen()
{
	_AniIndex[ACT_IDLE]			= 3;
	_AniIndex[ACT_RUN_FRONT]	= 12;
	_AniIndex[ACT_ATTACK00]		= 13;
	_AniIndex[ACT_ATTACK01]		= 14;
	_AniIndex[ACT_ATTACKED00]	= 10;
	_AniIndex[ACT_DEATH]		= 8;

	_aniRate[0]					= 0.5f;
	_aniRate[1]					= 0.5f;
	_aniRate[2]					= 0.5f;
}


bloodyQueen::~bloodyQueen()
{
}

void bloodyQueen::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = 0.0f;

	_kinds = ENEMY_BLOODYQUEEN;
}

