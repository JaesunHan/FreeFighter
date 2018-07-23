#include "stdafx.h"
#include "mudGolem.h"


mudGolem::mudGolem()
{
	_AniIndex[ACT_IDLE]			= 2;
	_AniIndex[ACT_RUN_FRONT]	= 1;
	_AniIndex[ACT_ATTACK00]		= 5;
	_AniIndex[ACT_ATTACK01]		= 6;
	_AniIndex[ACT_DEATH]		= 3;

	_aniRate[0] = 0.4f;
	_aniRate[1] = 0.5f;
	_aniRate[2] = 0.5f;
}


mudGolem::~mudGolem()
{
}


void mudGolem::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = -D3DX_PI / 2;

	_kinds = ENEMY_DARKWOLF;
}


