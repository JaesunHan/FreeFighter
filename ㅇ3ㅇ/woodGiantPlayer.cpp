#include "stdafx.h"
#include "woodGiantPlayer.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"
#include "leafAtk.h"


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
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.35f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.65f;

	player::Init(p, character, keyPath, keyName);
}

void woodGiantPlayer::Update()
{
	//if (_vParticle.size() != 0)
	//{
	//	hitSkillEnemy();
	//}

	if (_currentAct == ACT_ATTACK01 
		&& _skinnedMesh->getCurrentAnimationRate() > this->GetAttackAniRate() 
		&& _isOneHit)
	{
		this->SetOneHit();
		createLeafSkill();
	}


	player::Update();
}

void woodGiantPlayer::useSkill1()
{
	for (int i = 0; i < 4; ++i)
	{
		float angleY = getAngle(0, 0, _worldDir.x, _worldDir.z) + D3DX_PI / 2;
		float angleZ = D3DX_PI * 2 / 4 * i;
		leafAtk * temp = new leafAtk;
		temp->init(7.0f, 2.0f, angleZ, angleY, 256, _T("texture\\skill"), _T("fastBuff.png"), D3DXVECTOR3(_worldPos.x, _worldPos.y + 1.5f, _worldPos.z) + _worldDir * 2.0f);
		temp->setPlayer(this);

		_vParticle.push_back(temp);
	}
}

void woodGiantPlayer::useSkill2()
{

}

void woodGiantPlayer::useSkill3()
{
}

void woodGiantPlayer::createLeafSkill()
{
	for (int i = 0; i < 3; ++i)
	{
		float angleY = getAngle(0, 0, _worldDir.x, _worldDir.z) + D3DX_PI / 2;
		float angleZ = D3DX_PI * 2 / 3 * i;
		leafAtk * temp = new leafAtk;
		temp->init(6.0f, 1.0f, angleZ, angleY, 256, _T("texture\\skill"), _T("fastBuff.png"), D3DXVECTOR3(_worldPos.x, _worldPos.y + 1.5f, _worldPos.z) + _worldDir * 2.0f);
		temp->setPlayer(this);

		_vParticle.push_back(temp);
	}
}

bool woodGiantPlayer::hitSkillEnemy()
{
	if (!_isOneHit) return false;

	bool isHit = false;
	//�÷��̾ ���� �ִ� ���ʹ� �Ŵ������� ���ʹ̵��� Ž���ϸ鼭 �浹���θ� �˻��Ѵ�.
	vector<enemy*>		vecEnemy = _em->GetEnemy();
	for (int i = 0; i < vecEnemy.size(); ++i)
	{
		if (vecEnemy[i]->GetIsDead())
			continue;

		if (getDistance(_worldPos, vecEnemy[i]->GetPosition()) > 8.0f)
			continue;
		//skillHitCheck(vecEnemy[i]);
		//							  10.0f, 1.0f, 1.0f, _vEnemy[i]->GetAttackAniRate()
		HitCheck((interfaceCharacter*)vecEnemy[i], 10.0f, 3.5f, 3.5f, this->GetAttackAniRate());
		isHit = true;
	}

	this->SetOneHit();

	return isHit;
}

//void woodGiantPlayer::skillHitCheck(enemy* e)
//{
//	//if (getDistance(_worldPos, e->GetPosition()) <= 6.0f)
//	//{
//	//	if()
//	//}
//
//}





