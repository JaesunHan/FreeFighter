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

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.65f;

	player::Init(p, character, keyPath, keyName);
}

void woodGiantPlayer::Update()
{
	if (_currentAct == ACT_ATTACK01 && _skinnedMesh->getCurrentAnimationRate() > this->GetAttackAniRate() && _isOneHit)
	{
		createLeafSkill();
		this->SetOneHit();
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
	for (int i = 0; i < 5; ++i)
	{
		float angleY = getAngle(0, 0, _worldDir.x, _worldDir.z) + D3DX_PI / 2;
		float angleZ = D3DX_PI * 2 / 5 * i;
		leafAtk * temp = new leafAtk;
		temp->init(5.0f, angleZ, angleY, 500, _T("texture\\skill"), _T("fastBuff.png"), D3DXVECTOR3(_worldPos.x, _worldPos.y + 1.0f, _worldPos.z) + _worldDir * 1.5f);
		temp->setPlayer(this);

		_vParticle.push_back(temp);
	}
}
