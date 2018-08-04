#include "stdafx.h"
#include "enemy.h"
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

enemy::enemy()
	: 
	_RndCount(0)
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
	, _damagedCount(0)
	, _damagedSpeed(0.05f)
	, _atkDistance(0)
	, _hitRange(0)
{

}

enemy::~enemy()
{
	SAFE_DELETE(_currentState);
	SAFE_DELETE(_hpBar);
}

void enemy::Init(wstring keyPath, wstring keyName, int stage)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);

	_currentState = new stateContext;
	_currentState->setState(new appear, this);
	_currentState->Update();

	//스텟설정
	SetStatus(stage);

	_atkRange = 2.0f;
	_atkDistance = _atkRange;
	_hitRange = 1.0f;
	_actRange = 8.0f;

	_hpBar = new hpBar;
	_hpBar->Init(_T("hpBar"), _T(".\\texture\\enemy"), _T(".\\hpBar01.bmp"), GREEN, RED);

	//_currentAct = ACT_NONE;
	//_nextAct = ACT_APPEAR;
	//
	//AnimationSetting();
}

void enemy::SetStatus(int stage)
{
	_status.maxHp		= 100.0f + (100.0f * (stage * 0.6f));
	_status.currentHp	= _status.maxHp;
	_status.mp			= 50.0f * stage;
	_status.atkDmg		= 10.0f + (10.0f * (stage * 0.4f));
	_status.def			= 3.0f + (3.0f * (stage * 0.4f));
	_status.speed		= 0.05f + stage * 0.001f;
}

void enemy::createWind()
{
	wind* temp = new wind;
	temp->init(2.0f, 400, _T(".\\texture\\skill\\darkAura.png"));
	temp->SetEnemyAdressLink(this);

	_vParticle.push_back(temp);
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
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		HitDamage(10.0f);
	}

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
	}
	else
		EnemyStoryAI();
	
	_currentState->Update();

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

void enemy::Render(float elapsedTime)
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//애니메이션 셋팅
	if (!GetIsDeadAnimationEnd())
		interfaceCharacter::Render(elapsedTime);
	else 
		interfaceCharacter::Render(0.0f);

	if (_hpBar)
	{
		float maxRange = 15.0f;

		if (_targetPos)
		{
			float range = D3DXVec3Length(&(*_targetPos - _worldPos));

			if (range <= maxRange)
			{
				//float temp = (maxRange - range) / maxRange;
				//if (temp > 0.9f) temp = 0.9f;
				D3DXVECTOR2 v2Temp = get3Dto2D(_worldPos);
				_hpBar->Render(v2Temp.x, v2Temp.y, D3DXVECTOR3(0.5f, 0.5f, 0.0f));
			}
		}
	}
	
}

void enemy::SetParticle()
{
	
}

void enemy::HitDamage(float damage)
{
	if (_isDead) return;

	_status.currentHp -= damage;

	if (_status.currentHp <= 0)
	{
		_isDead = true;
		_currentState->setState(new death, this);
		return;
	}

	int rndAvoid = RND->getFromIntTo(0, 3);

	if (rndAvoid != 0) return;

	if (_currentAct == ACT_DAMAGED || _currentAct == ACT_RECOVERY) return;

	ACT temp = ACT_DAMAGED;
	if (_AniIndex[temp] == -1) return;

	_currentState->setState(new damaged, this);

}

bool enemy::GetIsDeadAnimationEnd()
{
	return _currentAct == ACT_DEATH && _skinnedMesh->IsAnimationEnd();
}

bool enemy::RespawnRange(float range)
{
	return	(_respawnPos.x - range < _worldPos.x && _worldPos.x < _respawnPos.x + range) &&
			(_respawnPos.y - range < _worldPos.y && _worldPos.y < _respawnPos.y + range) &&
			(_respawnPos.z - range < _worldPos.z && _worldPos.z < _respawnPos.z + range);
}

bool enemy::AttackRange()
{
	if (_targetPos)
		return D3DXVec3Length(&(*_targetPos - _worldPos)) < _atkRange;

	return false;
}

bool enemy::ActionRange()
{
	if (_targetPos)
		return D3DXVec3Length(&(*_targetPos - _worldPos)) < _actRange;

	return false;
}

bool enemy::BetweenEnemyDistance(D3DXVECTOR3 cheakPos, D3DXVECTOR3 makingPos, float range)
{
	return	(cheakPos.x - range < makingPos.x && makingPos.x < cheakPos.x + range) &&
			(cheakPos.y - range < makingPos.y && makingPos.y< cheakPos.y + range) &&
			(cheakPos.z - range < makingPos.z && makingPos.z < cheakPos.z + range);
}

void enemy::EnemyStoryAI()
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
			if (RespawnRange())
			{
				_changeCount++;

				if (_changeCount >= 100)
				{
					int rnd = RND->getFromIntTo(0, 1);

					if (rnd == 0)
						_currentState->setState(new idle, this);
					else
						_currentState->setState(new rndRun, this);

					_changeCount = 0;
				}
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

void enemy::EnemyFightAI()
{


}

bool enemy::isAnimationEnd()
{
	return _skinnedMesh->IsAnimationEnd();
}

void enemy::setState(state * s)
{
	_currentState->setState(s, this);
}

