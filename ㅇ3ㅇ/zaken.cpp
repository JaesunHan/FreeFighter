#include "stdafx.h"
#include "zaken.h"



zaken::zaken()
{
	_AniIndex[ACT_IDLE]			= 13;
	_AniIndex[ACT_RUN_FRONT]	= 14;
	_AniIndex[ACT_ATTACK00]		= 15;
	_AniIndex[ACT_ATTACK01]		= 5;
	_AniIndex[ACT_ATTACK02]		= 3;
	_AniIndex[ACT_DAMAGED]		= 12;
	_AniIndex[ACT_DEATH]		= 10;

	_aniRate[0]					= 0.6f;
	_aniRate[1]					= 0.7f;
	_aniRate[2]					= 0.7f;
}


zaken::~zaken()
{
}


void zaken::SetStatus(int stage)
{
	_status.maxHp		= 200.0f + (200.0f * (stage * 0.6f));
	_status.currentHp	= _status.maxHp;
	_status.mp			= 50.0f * stage;
	_status.atkDmg		= 20.0f + (20.0f * (stage * 0.4f));
	_status.def			= 6.0f + (6.0f * (stage * 0.4f));
	_status.speed		= 0.08f + stage * 0.001f;
}



void zaken::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = 0.0f;

	_kinds = ENEMY_ZAKEN;
}

