#include "stdafx.h"
#include "darkLord.h"
#include "stateContext.h"


darkLord::darkLord()
{
	_AniIndex[ACT_APPEAR]		= 6;
	_AniIndex[ACT_IDLE]			= 4;
	_AniIndex[ACT_RUN_FRONT]	= 12;
	_AniIndex[ACT_ATTACK00]		= 0;
	_AniIndex[ACT_ATTACK01]		= 1;
	_AniIndex[ACT_ATTACK02]		= 2;
	_AniIndex[ACT_ATTACKED00]	= 7;
	_AniIndex[ACT_DEATH]		= 9;
}


darkLord::~darkLord()
{
}

void darkLord::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = 0.0f;

	_kinds = ENEMY_DARKLORD;
}
