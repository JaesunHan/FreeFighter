#include "stdafx.h"
#include "kerberos.h"
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

kerberos::kerberos()
{
	_AniIndex[ACT_IDLE]			= 4;
	_AniIndex[ACT_RUN_FRONT]	= 1;
	_AniIndex[ACT_ATTACK00]		= 7;
	_AniIndex[ACT_ATTACK01]		= 9;
	_AniIndex[ACT_ATTACK02]		= 10;
	_AniIndex[ACT_DAMAGED]		= 0;
	_AniIndex[ACT_DEATH]		= 5;

	_aniRate[0]					= 0.5f;
	_aniRate[1]					= 0.5f;
	_aniRate[2]					= 0.57f;
}


kerberos::~kerberos()
{
}

void kerberos::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_correctionAngle = -D3DX_PI / 2;

	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, _correctionAngle);
	D3DXVec3TransformNormal(&_tempDir, &_tempDir, &matR);

	_kinds = ENEMY_KERBEROS;

	_atkRange = 4.0f;
	_atkDistance = _atkRange;
	_hitRange = 2.0f;
	_actRange = 10.0f;
}

void kerberos::SetStatus(int stage)
{
	_status.maxHp = 2500.0f;
	_status.currentHp = _status.maxHp;
	_status.mp = 500.0f;
	_status.atkDmg = 150.0f;
	_status.def = 50.0f;
	_status.speed = 0.07f;
}


void kerberos::EnemyStoryAI()
{
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
			_currentState->setState(new damage01, this);
			return;
		}
	}
	if (_currentAct == ACT_RECOVERY)
	{
		if (_skinnedMesh->IsAnimationEnd())
			_currentState->setState(new idle, this);

		return;
	}

	if (_enemyState != ENEMY_STATE_APPEAR)
	{
		// 몬스터 나와바리에 들어왔나
		if (ActionRange())
			_enemyState = ENEMY_STATE_DOING;
		else
		{
			if (!isAbsoluteMotion())
				_enemyState = ENEMY_STATE_WAIT;
		}
	}

	switch (_enemyState)
	{
	case ENEMY_STATE_APPEAR:
	{
		_isAppear = true;

		if (_AniIndex[_currentAct] == -1)
		{
			_isAppear = false;
			_enemyState = ENEMY_STATE_WAIT;
			_currentState->setState(new idle, this);
			return;
		}

		if (_skinnedMesh->IsAnimationEnd())
		{
			_isAppear = false;
			_enemyState = ENEMY_STATE_WAIT;
			_currentState->setState(new idle, this);
			return;
		}

		_currentState->setState(new appear, this);

		return;

	}
	break;
	case ENEMY_STATE_WAIT:
	{
		if (!isAbsoluteMotion())
		{
			// 리스폰 범위에 있나
			if (RespawnRange(1.0f))
			{
				_currentState->setState(new idle, this);
				_worldDir = _tempDir;
			}
			else
				_currentState->setState(new goHome, this);
		}
		else
		{
			if (_skinnedMesh->IsAnimationEnd())
				_currentState->setState(new idle, this);
		}

	}
	break;
	case ENEMY_STATE_DOING:
	{
		// 행동이 도중에 바뀌면 안되는 모션인가
		if (!isAbsoluteMotion())
		{
			// 공격 범위에 있나
			if (AttackRange())
			{
				_changeCount++;

				if (_changeCount % 50 == 0)
				{
					int RndAttack;
					do
					{
						RndAttack = RND->getFromIntTo(ACT_ATTACK00, ACT_ATTACK02);
					} while (_AniIndex[RndAttack] == -1);

					if (RndAttack == ACT_ATTACK00)
						_currentState->setState(new attack01, this);
					if (RndAttack == ACT_ATTACK01)
						_currentState->setState(new attack02, this);
					if (RndAttack == ACT_ATTACK02)
						_currentState->setState(new attack03, this);

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
				_currentState->setState(new run, this);
			}
		}
		else
		{
			if (_skinnedMesh->IsAnimationEnd())
				_currentState->setState(new idle, this);
		}

	}
	break;
	}
}
