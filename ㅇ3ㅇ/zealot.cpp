#include "stdafx.h"
#include "zealot.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"


zealot::zealot()
	: _target(NULL)
{
}


zealot::~zealot()
{
}

void zealot::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_AniIndex[ACT_IDLE] = 4;
	_AniIndex[ACT_RUN_FRONT] = 3;
	_AniIndex[ACT_RUN_BACK] = 3;
	_AniIndex[ACT_ATTACK00] = 2;
	_AniIndex[ACT_ATTACK01] = 1;
	_AniIndex[ACT_ATTACK02] = 0;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 4;

	_AniIndex[ACT_SKILL01] = 0;
	_AniIndex[ACT_SKILL03] = 3;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.3f;

	_coolTime[0].totalTime = _coolTime[0].currentTime = 3.0f;
	_coolTime[1].totalTime = _coolTime[1].currentTime = 6.0f;
	_coolTime[2].totalTime = _coolTime[2].currentTime = 10.0f;

	player::Init(p, character, keyPath, keyName);
}

void zealot::Update()
{
	if (_target)
	{
		this->changeAct(ACT_SKILL03);

		// 키 입력하는것에 따라 speed값과 모션을 바꿔줌
		float speed = 0.3f;

		if (_isFastSkillOn)
			speed *= 2;

		_worldDir = _target->GetPosition() - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);

		// 물리엔진에 적용할 속도값을 설정
		// 현재 우리 게임은 점프가 없기 때문에 y축의 속도는 0로 설정했으나
		// 만약 점프가 있는 게임에서는 y축속도는 여기서 정하는게 아니라 다른곳에서 설정하는 것이 좋음
		_velocity.x = _worldDir.x * speed;
		_velocity.z = _worldDir.z * speed;

		// 물리엔진표 컨트롤러로 위에서 설정한 속도만큼 이동
		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		PxControllerState state;
		_controller->getState(state);
		if (state.collisionFlags & PxControllerCollisionFlag::eCOLLISION_SIDES)
		{
			if (_em)
			{
				for (int i = 0; i < _em->GetEnemy().size(); ++i)
				{
					if (_em->GetEnemy()[i]->GetIsDead()) continue;

					D3DXVECTOR3 temp = AttackRange(1.0f);
					D3DXVECTOR3 pos = _em->GetEnemy()[i]->GetPosition();
					if (temp.x - 5.0f < pos.x && temp.x + 5.0f > pos.x &&
						temp.y - 5.0f < pos.y && temp.y + 5.0f > pos.y &&
						temp.z - 5.0f < pos.z && temp.z + 5.0f > pos.z)
					{
						_em->GetEnemy()[i]->HitDamage(_status.atkDmg - _em->GetEnemy()[i]->GetStatus().def);
						_em->GetEnemy()[i]->createHitEffect(0.5f);
					}
				}
			}

			if (_opponent)
			{
				if (!_opponent->GetIsDead())
				{
					D3DXVECTOR3 temp = AttackRange(1.0f);
					D3DXVECTOR3 pos = _opponent->GetPosition();
					if (temp.x - 5.0f < pos.x && temp.x + 5.0f > pos.x &&
						temp.y - 5.0f < pos.y && temp.y + 5.0f > pos.y &&
						temp.z - 5.0f < pos.z && temp.z + 5.0f > pos.z)
					{
						_opponent->HitDamage(_status.atkDmg - _opponent->GetStatus().def);
						_opponent->createHitEffect(0.5f);
					}
				}
			}
			_target = NULL;

			_isOneHit = false;
			this->changeAct(ACT_IDLE);
		}

		// 플레이어의 월드 위치를 바꿔줌
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
	}

	player::Update();
}

void zealot::attackEnemy()
{
	if (!_isOneHit) return;

	if (_em)
	{
		for (int i = 0; i < _em->GetEnemy().size(); ++i)
		{
			if (_em->GetEnemy()[i]->GetIsDead()) continue;

			float damage;
			if (_currentAct == ACT_SKILL01)
			{
				float rate = 1.0f;
				for (int i = 0; i < _status.skillLV1; ++i)
					rate += 0.1f;
				damage = _status.atkDmg * rate;
			}
			else
				damage = _status.atkDmg;

			this->HitCheck(_em->GetEnemy()[i], damage - _em->GetEnemy()[i]->GetStatus().def, 1.0f, 2.0f, this->GetAttackAniRate());
		}
	}

	if (_opponent)
	{
		if (!_opponent->GetIsDead())
		{
			float damage;
			if (_currentAct == ACT_SKILL01)
			{
				float rate = 1.0f;
				for (int i = 0; i < _status.skillLV1; ++i)
					rate += 0.1f;
				damage = _status.atkDmg * rate;
			}
			else
				damage = _status.atkDmg;

			this->HitCheck(_opponent, damage - _opponent->GetStatus().def, 1.0f, 2.0f, this->GetAttackAniRate());
		}
	}
	
	this->SetOneHit();
}

void zealot::useSkill1()
{
	if (_coolTime[0].currentTime < _coolTime[0].totalTime) return;
	_coolTime[0].currentTime = 0.0f;

	this->changeAct(ACT_SKILL01);
}

void zealot::useSkill2()
{
	if (_coolTime[1].currentTime < _coolTime[1].totalTime) return;
	_coolTime[1].currentTime = 0.0f;

	_isFastSkillOn = true;
	fastBuff* temp = new fastBuff;
	temp->init(200, _T(".\\texture\\skill\\fastBuff.png"));
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}

void zealot::useSkill3()
{
	if (_coolTime[2].currentTime < _coolTime[2].totalTime) return;

	float minDis = FLT_MAX;
	int minIdx = INT_MAX;

	if (_em)
	{
		for (int i = 0; i < _em->GetEnemy().size(); ++i)
		{
			if (_em->GetEnemy()[i]->GetIsDead()) continue;

			float dis = getDistance(_worldPos, _em->GetEnemy()[i]->GetPosition());
			if (dis < minDis)
			{
				minDis = dis;
				minIdx = i;
			}
		}

		if (minDis < 10.0f)
		{
			_coolTime[2].currentTime = 0.0f;

			_target = _em->GetEnemy()[minIdx];
			this->changeAct(ACT_SKILL03);
		}
	}

	if (_opponent)
	{
		if (!_opponent->GetIsDead())
		{
			float dis = getDistance(_worldPos, _opponent->GetPosition());

			if (dis < 10.0f)
			{
				_coolTime[2].currentTime = 0.0f;

				_target = _opponent;
				this->changeAct(ACT_SKILL03);
			}
		}
	}
}
