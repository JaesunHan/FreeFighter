#include "stdafx.h"
#include "durahan.h"


durahan::durahan()
{
	_AniIndex[ACT_IDLE]			= 2;
	_AniIndex[ACT_RUN_FRONT]	= 1;
	_AniIndex[ACT_ATTACK00]		= 5;
	_AniIndex[ACT_ATTACK01]		= 6;
	_AniIndex[ACT_ATTACK02]		= 7;
	_AniIndex[ACT_DAMAGED]		= 0;
	_AniIndex[ACT_DEATH]		= 3;

	_aniRate[0]					= 0.7f;
	_aniRate[1]					= 0.45f;
	_aniRate[2]					= 0.4f;
}


durahan::~durahan()
{
}

void durahan::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = -D3DX_PI / 2;
	
	_kinds = ENEMY_DURAHAN;
}
