#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"

//에이스타지만 사실아님
#include "jmAstar.h"
//에너미매니저
#include "enemyManager.h"
//상태패턴
#include "stateContext.h"

enemy::enemy()
	: _enemyState(ENEMY_STATE_DOING)
	, _RndCount(0)
	, _currentState(NULL)
	, _disappearCount(0)
	, _distance(0.0f)
{
	ZeroMemory(&_sphere, sizeof(tagSphere));
	D3DXMatrixIdentity(&_worldTM);
}

enemy::~enemy()
{
}

void enemy::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
	_currentState = new stateContext;
	_currentState->setState(new idle, this);

	_status.maxHp = 100.0f;
	_status.currentHp = _status.maxHp;
}

void enemy::Update()
{
	if (_status.currentHp <= 0) _isDead = true;
	if (KEYMANAGER->isOnceKeyDown(VK_F8)) _status.currentHp -= 100.0f;

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
		EnemyStoryAI();
	}

	_currentState->Update();

	CreateWorldMatrix();

	AnimationSetting();
	interfaceCharacter::Update();
}

void enemy::Render(float elapsedTime)
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

	//애니메이션 셋팅
	if (!GetIsDeadAnimationEnd())
		interfaceCharacter::Render();
	else 
		interfaceCharacter::Render(0.0f);
	
	if (_isDebug)
	{
		// === 디버깅용 원 =====
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, _worldPos.x + _sphere.center.x,
			_worldPos.y + _sphere.center.y,
			_worldPos.z + _sphere.center.z);
		D3DDEVICE->SetTransform(D3DTS_WORLD, &matT);
		_sphere.sphere->DrawSubset(0);
		D3DXMatrixIdentity(&matT);
		D3DDEVICE->SetTransform(D3DTS_WORLD, &matT);
		// ====================
	}
}

bool enemy::GetIsDeadAnimationEnd()
{
	return _currentAct == ACT_DEATH && _skinnedMesh->IsAnimationEnd();
}

bool enemy::YouAndIDistance()
{
	if (_targetPos)
	{
		D3DXVECTOR3 temp = _worldPos - *_targetPos;
		return D3DXVec3Length(&temp) <= _distance;
	}
	else
		return false;
}

void enemy::EnemyStoryAI()
{
	switch (_enemyState)
	{
	case ENEMY_STATE_WAIT:
	{
		_RndCount++;

		_currentState->setState(new idle, this);
	}
	break;
	case ENEMY_STATE_DOING:
	{
		//에니메이션이 도중에 바뀌면 안되는 것들 == isAbsoluteMotion가 true
		if (!isAbsoluteMotion())
		{
			if (!YouAndIDistance())
			{
				_RndCount++;
				_currentState->setState(new run, this);
			}

			//공격범위에 들어왔다 !
			else if (YouAndIDistance())
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
			}
				
		}
		else
		{
			if (_skinnedMesh->IsAnimationEnd())
			{
				_currentState->setState(new idle, this);
			}
		}
		
	}
	break;
	}

	if (_RndCount % 300 == 0)
	{
		if (_enemyState == ENEMY_STATE_WAIT)
		{
			_RndCount = 0;
			_enemyState = ENEMY_STATE_DOING;
		}
		else if (_enemyState == ENEMY_STATE_DOING)
		{
			_RndCount = 200;
			_enemyState = ENEMY_STATE_WAIT;
		}

	}
}

void enemy::EnemyFightAI()
{
}

