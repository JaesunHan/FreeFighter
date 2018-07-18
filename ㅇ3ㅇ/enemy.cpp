#include "stdafx.h"
#include "enemy.h"
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
#include "progressBar.h"

enemy::enemy()
	: _enemyState(ENEMY_STATE_APPEAR)
	, _RndCount(0)
	, _changeCount(0)
	, _currentState(NULL)
	, _disappearCount(0)
	, _atkRange(0.0f)
	, _actRange(0.0f)
	, _targetPos(NULL)
	, _respawnPos(0, 0, 0)
	, _correctionAngle(0.0f)
	, _isAppear(false)
	, _isOutOfRange(false)
	, _hpBar(NULL)
{

}

enemy::~enemy()
{
	SAFE_DELETE(_currentState);
}

void enemy::Init(wstring keyPath, wstring keyName, int stage)
{
	Init(keyPath, keyName);
	SetStatus(stage);
}

void enemy::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
	_currentState = new stateContext;
	_currentState->setState(new idle, this);

	//_hpBar = new progressBar;
	//_hpBar->Init();

	_currentAct = ACT_NONE;
	_nextAct = ACT_APPEAR;

	AnimationSetting();

	//�ӽ� // �� ���� �̸�??
	_status.maxHp = 100.0f;
	_status.currentHp = _status.maxHp;
	_atkRange = 2.0f;
	_actRange = 8.0f;
}

void enemy::SetStatus(int stage)
{
	_status.maxHp		= 100.0f;
	_status.currentHp	= _status.maxHp;
	_status.mp			= 50.0f;
	_status.atkDmg		= 10.0f;
	_status.def			= 3.0f;
	_status.speed		= 0.05f;
}

void enemy::SetTarget(playerManager * pm)
{
	player* target = NULL;
	float distance = FLT_MAX;
	for (int i = 0; i < pm->getPlayersNum(); ++i)
	{
		float tempDis = getDistance(pm->getVPlayers()[i]->p->GetPosition(), _worldPos);
		if (tempDis < distance)
		{
			target = pm->getVPlayers()[i]->p;
			distance = tempDis;
		}
	}
	if (target)
		_targetPos = &target->GetPosition();
	else
		_targetPos = NULL;
}


void enemy::Update()
{
	if (_status.currentHp <= 0) _isDead = true;

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
		if (_hpBar)
			_hpBar->Update(_status.currentHp, _status.maxHp);

		EnemyStoryAI();
	}
	_currentState->Update();

	CreateWorldMatrix(_correctionAngle);

	AnimationSetting();
	interfaceCharacter::Update();
}

void enemy::Render(float elapsedTime)
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�ִϸ��̼� ����
	if (!GetIsDeadAnimationEnd())
		interfaceCharacter::Render(elapsedTime);
	else 
		interfaceCharacter::Render(0.0f);

	//if (_hpBar)
	//	_hpBar->Render();
	
}



void enemy::HitDamage(float damage)
{
	_status.currentHp -= damage;

	if (_status.currentHp > 0)
		_currentState->setState(new damage01, this);
	else
		_isDead = true;
}

bool enemy::GetIsDeadAnimationEnd()
{
	return _currentAct == ACT_DEATH && _skinnedMesh->IsAnimationEnd();
}

bool enemy::WithinRespawnRange(float range)
{
	return	(_respawnPos.x - range < _worldPos.x && _worldPos.x < _respawnPos.x + range) &&
			(_respawnPos.y - range < _worldPos.y && _worldPos.y < _respawnPos.y + range) &&
			(_respawnPos.z - range < _worldPos.z && _worldPos.z < _respawnPos.z + range);
}

bool enemy::WithinAttackRange()
{
	if (_targetPos)
		return D3DXVec3Length(&(*_targetPos - _worldPos)) < _atkRange;

	return false;
}

bool enemy::WithinActionRange()
{
	if (_targetPos)
		return D3DXVec3Length(&(*_targetPos - _worldPos)) < _actRange;

	return false;
}

bool enemy::WithinEnemyRange(D3DXVECTOR3 cheakPos, D3DXVECTOR3 makingPos, float range)
{
	return	(cheakPos.x - range < makingPos.x && makingPos.x < cheakPos.x + range) &&
			(cheakPos.y - range < makingPos.y && makingPos.y< cheakPos.y + range) &&
			(cheakPos.z - range < makingPos.z && makingPos.z < cheakPos.z + range);
}

void enemy::EnemyStoryAI()
{

	if (_enemyState != ENEMY_STATE_APPEAR)
	{
		// ���� ���͹ٸ��� ���Գ�
		if (WithinActionRange())
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

			if ( _skinnedMesh->IsAnimationEnd())
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
			// ������ ������ �ֳ�
			if (WithinRespawnRange())
			{
				_changeCount++;

				if (_changeCount % 100 == 0)
				{
					int rnd = RND->getFromIntTo(0, 1);

					if (rnd == 0)
					{
						_currentState->setState(new idle, this);
					}					
					else
					{
						_currentState->setState(new rndRun, this);
					}
					
					_changeCount = 0;
				}
				
			}
			else
				_currentState->setState(new goHome, this);
		}
		break;
		case ENEMY_STATE_DOING:
		{
			// �ൿ�� ���߿� �ٲ�� �ȵǴ� ����ΰ�
			if (!isAbsoluteMotion())
			{
				// ���� ������ �ֳ�
				if (WithinAttackRange())
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

void enemy::EnemyFightAI()
{


}

