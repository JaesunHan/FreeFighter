#include "stdafx.h"
#include "fightEnemy.h"
#include "skinnedMesh.h"

//에이스타지만 사실아님
#include "jmAstar.h"
//에너미매니저
#include "enemyManager.h"
//상태패턴
#include "stateContext.h"
//플레이어 매니저
#include "playerManager.h"
#include "player.h"
//HP바
#include "hpBar.h"
//파티클
#include "particleSystems.h"


fightEnemy::fightEnemy()
{
	for (int i = 0; i < 3; i++)
	{
		_coolTime[i] = COOLTIME;
		_useSkill[i] = true;
	}

	_fastSkillCount = 200;
		
}


fightEnemy::~fightEnemy()
{
}

void fightEnemy::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_currentState = new stateContext;
	_currentState->setState(new idle, this);

	SetStatus(1);

	_hpBar = new hpBar;
	_hpBar->Init(_T("hpBar"), _T(".\\texture\\enemy"), _T(".\\hpBar01.bmp"), GREEN, RED);

	_currentAct = ACT_NONE;
	_nextAct = ACT_IDLE;

	AnimationSetting();
}

void fightEnemy::Update()
{
	if (_status.currentHp <= 0) _isDead = true;

	if (_hpBar)
		_hpBar->Update(_status.currentHp, _status.maxHp);

	if (_isDead)
	{
		if (_controller)
		{
			_controller->release();
			_controller = NULL;
		}

		_currentState->setState(new death, this);
	}
	else
	{
		EnemyFightAI();
	}

	float speed = _status.speed;

	if (_isFastSkillOn)
	{
		_status.speed *= 2;

		_fastSkillCount--;
		if (_fastSkillCount <= 0)
		{
			_isFastSkillOn = false;
			_fastSkillCount = 200;
		}
	}

	_currentState->Update();

	_status.speed = speed;

	CreateWorldMatrix(_correctionAngle);

	AnimationSetting();
	interfaceCharacter::Update();

	for (int i = 0; i < _vParticle.size();)
	{
		_vParticle[i]->update();

		if (_vParticle[i]->isDead())
		{
			SAFE_OBJRELEASE(_vParticle[i]);
			_vParticle.erase(_vParticle.begin() + i);
		}
		else i++;
	}
}

void fightEnemy::Render(float elapsedTime)
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//애니메이션 셋팅
	if (!GetIsDeadAnimationEnd())
		interfaceCharacter::Render(elapsedTime);
	else
		interfaceCharacter::Render(0.0f);

	for (int i = 0; i < _vParticle.size(); i++)
	{
		_vParticle[i]->render();
	}

	if (_hpBar)
	{
		float maxRange = 15.0f;

		//if (_targetPos)
		//{
		//	float range = D3DXVec3Length(&(*_targetPos - _worldPos));
		//
		//	if (range <= maxRange)
		//	{
		//		
		//	}
		//}

		D3DVIEWPORT9 vp;
		D3DDEVICE->GetViewport(&vp);
		_hpBar->Render(vp.X + vp.Width / 2, vp.Y + 20.0f, D3DXVECTOR3(2.0f, 1.5f, 0.0f));
	}
}

void fightEnemy::EnemyFightAI()
{
	for (int i = 0; i < 3; i++)
	{
		if (!_useSkill[i])
			_coolTime[i]--;
		
		if (_coolTime[i] <= 0)
		{
			_coolTime[i] = COOLTIME;
			_useSkill[i] = true;
		}
	}

	if (_currentAct == ACT_DAMAGED)
	{
		_damagedCount++;

		if (_skinnedMesh->IsAnimationEnd())
		{
			if (_damagedCount < 10)
			{
				_skinnedMesh->Pause();
				return;
			}

			_currentState->setState(new recovery, this);
			return;
		}
		else
		{
			_currentState->setState(new damaged, this);
			return;
		}
	}
	if (_currentAct == ACT_RECOVERY)
	{
		if (_skinnedMesh->IsAnimationEnd())
			_currentState->setState(new idle, this);

		return;
	}


	if (!AttackRange())
	{		
		if (!isAbsoluteMotion())
			_currentState->setState(new run, this);
		else
		{
			if (_skinnedMesh->IsAnimationEnd())
				_currentState->setState(new idle, this);
		}
	}
	else
	{
		_changeCount++;

		if (!isAbsoluteMotion())
		{
			if (_changeCount % 100 == 0)
			{
				int RndAttack;

				while (true)
				{
					RndAttack = RND->getFromIntTo(ACT_ATTACK00, ACT_SKILL03);

					if (_AniIndex[RndAttack] == -1) continue;
					if (_AniIndex[RndAttack] == ACT_SKILL01 && _coolTime[0] == false) continue;
					if (_AniIndex[RndAttack] == ACT_SKILL02 && _coolTime[1] == false) continue;
					if (_AniIndex[RndAttack] == ACT_SKILL03 && _coolTime[2] == false) continue;

					break;
				}

				if (RndAttack == ACT_ATTACK00)
					_currentState->setState(new attack01, this);
				if (RndAttack == ACT_ATTACK01)
					_currentState->setState(new attack02, this);
				if (RndAttack == ACT_ATTACK02)
					_currentState->setState(new attack03, this);
				if (RndAttack == ACT_SKILL01)
					_currentState->setState(new skill01, this);
				if (RndAttack == ACT_SKILL02)
					_currentState->setState(new skill02, this);
				if (RndAttack == ACT_SKILL03)
					_currentState->setState(new skill03, this);

				if (_targetPos)
				{
					// 적이 실제 움직이는 방향
					_worldDir = *_targetPos - _worldPos;
					D3DXVec3Normalize(&_worldDir, &_worldDir);
				}

				_changeCount = 0;
			}
			else
				_currentState->setState(new idle, this);
		}
		else
		{
			if (_skinnedMesh->IsAnimationEnd())
				_currentState->setState(new idle, this);
		}
	}
}

void fightEnemy::UseSkill01()
{
}

void fightEnemy::UseSkill02()
{
}

void fightEnemy::UseSkill03()
{
}
