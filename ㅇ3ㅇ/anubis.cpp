#include "stdafx.h"
#include "anubis.h"


anubis::anubis()
{
	_AniIndex[ACT_IDLE]			= 2;
	_AniIndex[ACT_RUN_FRONT]	= 1;
	_AniIndex[ACT_ATTACK00]		= 5;
	_AniIndex[ACT_ATTACK01]		= 6;
	_AniIndex[ACT_ATTACKED00]	= 4;
	_AniIndex[ACT_DEATH]		= 3;
}


anubis::~anubis()
{
}

void anubis::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = -D3DX_PI / 2;

	_kinds = ENEMY_ANUBIS;
}
