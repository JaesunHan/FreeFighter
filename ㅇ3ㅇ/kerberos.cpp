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
	D3DXMatrixRotationY(&matR, D3DX_PI / 4);
	D3DXVec3TransformNormal(&_tempDir, &_tempDir, &matR);

	_kinds = ENEMY_KERBEROS;

	_atkRange = 4.0f;
	_atkDistance = _atkRange;
	_hitRange = 2.0f;
	_actRange = 10.0f;
}

void kerberos::Attack02()
{
	if (_AniIndex[ACT_ATTACK01] != -1)
	{
		_nextAct = ACT_ATTACK01;

		wind* temp = new wind;
		temp->init(2.0f, 10, _T(".\\texture\\skill\\darkAura.png"));
		temp->SetEnemyAdressLink(this);

		_vParticle.push_back(temp);
	}
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
	if (_currentAct == ACT_APPEAR) return;

	if (!isAbsoluteMotion())
	{
		//몬스터 구역 안으로 플레이어가 들어오면
		if (ActionRange())
		{
			// 공격 범위 안에 들어오면
			if (AttackRange())
			{
				_changeCount++;

				if (_changeCount % 100 == 0)
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
			// 공격범위 밖이면
			else
				_currentState->setState(new run, this);

		}
		//몬스터 구역 안에 플레이어가 없으면
		else
		{
			// 자기 구역에 있을 때
			if (RespawnRange(0.1f))
			{
				_worldDir = _tempDir;
				_currentState->setState(new idle, this);
			}		
			//움직이다 자기 구역 밖으로 나갔을 때
			else if (!RespawnRange())
				_currentState->setState(new goHome, this);
		}
	}
	else
	{
		if (isAnimationEnd())
			_currentState->setState(new idle, this);
	}

}
