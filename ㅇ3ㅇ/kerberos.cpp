#include "stdafx.h"
#include "kerberos.h"
#include "skinnedMesh.h"

//���̽�Ÿ���� ��Ǿƴ�
#include "jmAstar.h"
//���ʹ̸Ŵ���
#include "enemyManager.h"
//��������
#include "stateContext.h"
//�÷��̾� �Ŵ���
#include "playerManager.h"
#include "player.h"
//HP��
#include "hpBar.h"
//��ƼŬ
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
		// ���� ���͹ٸ��� ���Գ�
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
			// ������ ������ �ֳ�
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
		// �ൿ�� ���߿� �ٲ�� �ȵǴ� ����ΰ�
		if (!isAbsoluteMotion())
		{
			// ���� ������ �ֳ�
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
						// ���� ���� �����̴� ����
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
