#include "stdafx.h"
#include "fepee.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"


fepee::fepee()
{
}


fepee::~fepee()
{
}

void fepee::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_ATTACKED00] = 4;
	_AniIndex[ACT_DEATH] = 3;
	_AniIndex[ACT_SKILL01] = 6;

	player::Init(p, character, keyPath, keyName);
}

void fepee::attack()
{
	// 카운트는 진리인 것이다. 그러한 것이다.
	_comboCount++;

	// 어택키를 누를 때 마다 카운트를 0으로 바꾸면서 콤보를 이어나갈 가능성을 만들어줌
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
		_comboCount = 0;

	// 카운트가 30이 되기 전 애니메이션이 끝난다면 콤보가 이어진다
	if (_comboCount < 30)
	{
		// 일단 지금 공격이 가능한 상태(AbsoluteMotion이 아닌 경우)이면 attack00으로 바꿔줌
		if (!this->isAbsoluteMotion())
		{
			this->changeAct(ACT_ATTACK00);

			for (int i = 0; i < _em->GetEnemy().size(); ++i)
			{
				if (getDistance(_em->GetEnemy()[i]->GetPosition(), _worldPos) < 10.0f)
				{
					_worldDir = _em->GetEnemy()[i]->GetPosition() - _worldPos;
					D3DXVec3Normalize(&_worldDir, &_worldDir);
				}
			}

			D3DXVECTOR3 startPosition = _worldPos + _worldDir;
			float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) - D3DX_PI / 2;
			this->createPoisonArrow(startPosition, _worldDir, angle);
		}
		// 현재 attack00인데 콤보를 이어나갈 가능성이 있으면 attack01상태로 바꿔줌
		// 그 밑에도 마찬가지
		else if (_currentAct == ACT_ATTACK00 && _skinnedMesh->IsAnimationEnd())
		{
			this->changeAct(ACT_ATTACK01);

			for (int i = 0; i < 8; ++i)
			{
				D3DXVECTOR3 dir;
				D3DXMATRIX matR;
				D3DXMatrixRotationY(&matR, D3DX_PI / 4 * i);
				D3DXVec3TransformNormal(&dir, &_worldDir, &matR);
				float angle = getAngle(0, 0, dir.x, dir.z) - D3DX_PI / 2;
				D3DXVECTOR3 startPosition = _worldPos + dir;
				this->createPoisonArrow(startPosition, dir, angle);
			}
		}
	}
}

void fepee::useSkill1()
{
	float numOfArrow = 5.0f;
	for (int i = 0; i < numOfArrow; ++i)
	{
		D3DXVECTOR3 dir;
		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, (-30.0f + 60.0f / numOfArrow * i) * DEG2RAD);
		D3DXVec3TransformNormal(&dir, &_worldDir, &matR);
		D3DXVECTOR3 startPosition = _worldPos + dir * 1.5f;
		float angle = getAngle(0, 0, dir.x, dir.z) - D3DX_PI / 2;
		this->createPoisonArrow(startPosition, dir, angle);
	}

	this->changeAct(ACT_SKILL01);
}

void fepee::useSkill2()
{
	_isFastSkillOn = true;
	fastBuff* temp = new fastBuff;
	temp->init(200, _T(".\\texture\\skill\\fastBuff.png"));
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}

void fepee::useSkill3()
{
}

void fepee::createPoisonArrow(D3DXVECTOR3 startPosition, D3DXVECTOR3 dir, float angle)
{
	poisonArrow* temp = new poisonArrow;
	temp->init(0.5f, 200, _T(".\\texture\\skill\\poisonArrow.png"), startPosition, PxVec3(dir.x, dir.y, dir.z), angle);
	temp->createController(_cm, _material);
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}
