#include "stdafx.h"
#include "fightFepee.h"
#include "particleSystems.h"


fightFepee::fightFepee()
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 3;

	_AniIndex[ACT_SKILL01] = 5;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.65f;

	_correctionAngle = -D3DX_PI / 2;
}


fightFepee::~fightFepee()
{
}

void fightFepee::SetStatus(int stage)
{
	_status.maxHp		= 1000.0f;
	_status.currentHp	= _status.maxHp;
	_status.mp			= 300.0f;
	_status.atkDmg		= 500.0f;
	_status.def			= 50.0f;
	_status.speed		= 0.05f;

}

void fightFepee::UseSkill01()
{
	//_isFastSkillOn = true;
	//fastBuff* temp = new fastBuff;
	//temp->init(200, _T(".\\texture\\skill\\fastBuff.png"));
	//temp->setEnemy(this);
	//
	//_vParticle.push_back(temp);
}

void fightFepee::UseSkill02()
{
}

void fightFepee::UseSkill03()
{
}
