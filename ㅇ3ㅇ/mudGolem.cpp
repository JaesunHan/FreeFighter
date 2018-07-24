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

void mudGolem::SetStatus(int stage)
{
	_status.maxHp		= 200.0f + (200.0f * (stage * 0.6f));
	_status.currentHp	= _status.maxHp;
	_status.mp			= 50.0f * stage;
	_status.atkDmg		= 20.0f + (20.0f * (stage * 0.4f));
	_status.def			= 6.0f + (6.0f * (stage * 0.4f));
	_status.speed		= 0.05f + stage * 0.001f;
}



void mudGolem::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = -D3DX_PI / 2;

	_kinds = ENEMY_DARKWOLF;
}


