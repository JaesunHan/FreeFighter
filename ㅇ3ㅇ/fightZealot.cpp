#include "stdafx.h"
#include "fightZealot.h"
#include "particleSystems.h"

fightZealot::fightZealot()
{
	_AniIndex[ACT_IDLE] = 4;
	_AniIndex[ACT_RUN_FRONT] = 3;
	_AniIndex[ACT_RUN_BACK] = 3;
	_AniIndex[ACT_ATTACK00] = 2;
	_AniIndex[ACT_ATTACK01] = 1;
	_AniIndex[ACT_ATTACK02] = 0;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 4;

	_AniIndex[ACT_SKILL01] = 3;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.3f;

	_correctionAngle = -D3DX_PI / 2;
}


fightZealot::~fightZealot()
{
}

void fightZealot::UseSkill01()
{
}

void fightZealot::UseSkill02()
{

}

void fightZealot::UseSkill03()
{

}
