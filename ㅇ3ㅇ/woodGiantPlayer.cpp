#include "stdafx.h"
#include "woodGiantPlayer.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"


woodGiantPlayer::woodGiantPlayer()
{
}


woodGiantPlayer::~woodGiantPlayer()
{
}

void woodGiantPlayer::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 3;

	_AniIndex[ACT_SKILL01] = 6;
	_AniIndex[ACT_SKILL03] = 6;

	player::Init(p, character, keyPath, keyName);
}

void woodGiantPlayer::Update()
{
	if (_currentAct == ACT_ATTACK01 && _skinnedMesh->IsAnimationEnd())
	{
		this->changeAct(ACT_ATTACK01);
		createLeafSkill();
	}


	player::Update();
}

void woodGiantPlayer::useSkill1()
{
}

void woodGiantPlayer::useSkill2()
{
}

void woodGiantPlayer::useSkill3()
{
}

void woodGiantPlayer::createLeafSkill()
{
	leafAtk*  temp = new leafAtk;
	temp->init(360 * DEG2RAD, 0.0f, 500, _T("texture\\skill"), _T("fastBuff.png"), D3DXVECTOR3(0, 0, 0));
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}
