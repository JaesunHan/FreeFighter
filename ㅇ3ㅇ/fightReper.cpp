#include "stdafx.h"
#include "fightReper.h"
#include "particleSystems.h"


fightReper::fightReper()
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 3;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.65f;

	_correctionAngle = -D3DX_PI / 2;

	_useSkill = false;
}


fightReper::~fightReper()
{
}

void fightReper::Attack01()
{
	if (_currentAct == ACT_ATTACK00)
		_useSkill = true;
	else
		_useSkill = false;

	if (_AniIndex[ACT_ATTACK00] != -1)
	{
		_nextAct = ACT_ATTACK00;

		if (!_useSkill)
		{
			wind* temp = new wind;
			temp->init(2.0f, 500, _T(".\\texture\\skill\\darkAura.png"));
			temp->SetEnemyAdressLink(this);

			_vParticle.push_back(temp);
		}

	}
}

void fightReper::Attack02()
{
	if (_currentAct == ACT_ATTACK01)
		_useSkill = true;
	else
		_useSkill = false;

	if (_AniIndex[ACT_ATTACK01] != -1)
	{
		_nextAct = ACT_ATTACK01;

		if (!_useSkill)
		{
			D3DXVECTOR3 pos = _worldPos + _worldDir * _atkDistance;

			enemyDarkAura* temp = new enemyDarkAura;
			temp->init(1.0f, 200, _T(".\\texture\\skill\\darkAura.png"), pos);
			temp->setPlayer(this);

			_vParticle.push_back(temp);
		}
		
	}
}

void fightReper::UseSkill01()
{
	
}

void fightReper::UseSkill02()
{
}

void fightReper::UseSkill03()
{
}
