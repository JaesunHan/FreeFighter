#include "stdafx.h"
#include "gargoyle.h"

#include "particleSystems.h"


gargoyle::gargoyle()
{
	_AniIndex[ACT_IDLE]			= 2;
	_AniIndex[ACT_RUN_FRONT]	= 1;
	_AniIndex[ACT_ATTACK00]		= 5;
	_AniIndex[ACT_ATTACK01]		= 6;
	_AniIndex[ACT_ATTACK02]		= 7;
	_AniIndex[ACT_DAMAGED]		= 0;
	_AniIndex[ACT_DEATH]		= 3;

	_aniRate[0]					= 0.4f;
	_aniRate[1]					= 0.5f;
	_aniRate[2]					= 0.5f;
}


gargoyle::~gargoyle()
{
}

void gargoyle::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = -D3DX_PI / 2;

	_atkRange = 4.0f;
	_atkDistance = _atkRange;
	_hitRange = 4.0f;
	_actRange = 8.0f;

	_kinds = ENEMY_GARGOYLE;
}

void gargoyle::SetStatus(int stage)
{
	_status.maxHp = 150000.0f;
	_status.currentHp = _status.maxHp;
	_status.mp = FLT_MAX;
	_status.atkDmg = 1000.0f;
	_status.def = 500.0f;
	_status.speed = 0.06f;
}


void gargoyle::Attack01()
{
	if (_AniIndex[ACT_ATTACK00] != -1)
	{
		_nextAct = ACT_ATTACK00;

		wind* temp = new wind;
		temp->init(2.0f, 10, L"");
		temp->SetEnemyAdressLink(this);
		
		_vParticle.push_back(temp);
	}

}

void gargoyle::Attack02()
{
	if (_AniIndex[ACT_ATTACK01] != -1)
	{
		_nextAct = ACT_ATTACK01;

		wind* temp = new wind;
		temp->init(2.0f, 10, L"");
		temp->SetEnemyAdressLink(this);
		
		_vParticle.push_back(temp);
	}

}

void gargoyle::Attack03()
{
	if (_AniIndex[ACT_ATTACK02] != -1)
	{
		_nextAct = ACT_ATTACK02;

		wind* temp = new wind;
		temp->init(2.0f, 10, L"");
		temp->SetEnemyAdressLink(this);
		
		_vParticle.push_back(temp);
	}

}


