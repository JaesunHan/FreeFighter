#include "stdafx.h"
#include "reaper.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"


reaper::reaper()
	: _isGhostMode(false)
	, _ghostStartHeight(3.0f)
{
}


reaper::~reaper()
{
}

void reaper::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 3;

	_AniIndex[ACT_SKILL01] = 5;
	_AniIndex[ACT_SKILL03] = 6;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.3f;

	player::Init(p, character, keyPath, keyName);
}

void reaper::move()
{
	// 움직이는것은 변화가 있으면 안되는 모션(AbsoluteMotion)일 경우 움직이면 아니되오
	if (this->isAbsoluteMotion()) return;

	// 키 입력하는것에 따라 speed값과 모션을 바꿔줌
	float speed;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
	{
		this->changeAct(ACT_RUN_FRONT);
		speed = _status.speed;
	}
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
	{
		this->changeAct(ACT_RUN_BACK);
		speed = -_status.speed;
	}
	else
	{
		this->changeAct(ACT_IDLE);
		speed = 0.0f;
	}

	if (_isFastSkillOn)
		speed *= 2;

	// 회전에 사용할 angle값 설정
	float angle;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
		angle = -ANGLESPEED;
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
		angle = ANGLESPEED;
	else
		angle = 0.0f;

	// 설정된 angle값만큼 플레이어가 바라보는 방향(_worldDir)을 바꿔줌
	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, angle);
	D3DXVec3TransformNormal(&_worldDir, &_worldDir, &matR);
	D3DXVec3Normalize(&_worldDir, &_worldDir);

	// 물리엔진에 적용할 속도값을 설정
	// 현재 우리 게임은 점프가 없기 때문에 y축의 속도는 0로 설정했으나
	// 만약 점프가 있는 게임에서는 y축속도는 여기서 정하는게 아니라 다른곳에서 설정하는 것이 좋음
	_velocity.x = _worldDir.x * speed;
	_velocity.z = _worldDir.z * speed;

	// 물리엔진표 컨트롤러로 위에서 설정한 속도만큼 이동
	_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());


	if (_isJump)
	{
		PxControllerState state;
		_controller->getState(state);
		if (state.collisionFlags == PxControllerCollisionFlag::eCOLLISION_DOWN ||
			state.collisionFlags == PxControllerCollisionFlag::eCOLLISION_UP)
		{
			_velocity.y = 0.0f;
		}
	}

	// 플레이어의 월드 위치를 바꿔줌
	if (_isGhostMode)
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _ghostStartHeight, _controller->getFootPosition().z);
	else
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
}

void reaper::attack()
{
	if (_isGhostMode) return;

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
			this->changeAct(ACT_ATTACK00);
		// 현재 attack00인데 콤보를 이어나갈 가능성이 있으면 attack01상태로 바꿔줌
		// 그 밑에도 마찬가지
		else if (_currentAct == ACT_ATTACK00 && _skinnedMesh->IsAnimationEnd())
		{
			this->changeAct(ACT_ATTACK01);

			D3DXVECTOR3 startPos;
			D3DXVec3Normalize(&_worldDir, &_worldDir);
			startPos = _worldPos + _worldDir * 3.0f;

			for (int i = 0; i < _em->GetEnemy().size(); ++i)
			{
				if (_em->GetEnemy()[i]->GetIsDead()) continue;

				if (getDistance(_em->GetEnemy()[i]->GetPosition(), _worldPos) < 10.0f)
				{
					_worldDir = _em->GetEnemy()[i]->GetPosition() - _worldPos;
					D3DXVec3Normalize(&_worldDir, &_worldDir);
					startPos = D3DXVECTOR3(_em->GetEnemy()[i]->getController()->getFootPosition().x,
						_em->GetEnemy()[i]->getController()->getFootPosition().y,
						_em->GetEnemy()[i]->getController()->getFootPosition().z);
					break;
				}
			}

			this->createDrakAura(startPos);
		}
	}
}

void reaper::useSkill1()
{
	if (_isGhostMode) return;

	vector<int> index;
	for (int i = 0; i < _em->GetEnemy().size(); ++i)
	{
		if (_em->GetEnemy()[i]->GetIsDead()) continue;

		if (getDistance(_em->GetEnemy()[i]->GetPosition(), _worldPos) < 10.0f)
			index.push_back(i);
	}

	if (index.size() != 0)
	{
		this->changeAct(ACT_SKILL01);

		for (int i = 0; i < 100; ++i)
			swap(index[RND->getInt(index.size())], index[RND->getInt(index.size())]);

		for (int i = 0; i < index.size() && i < 5; ++i)
			this->createDrakAura(_em->GetEnemy()[index[i]]->GetPosition());
	}
}

void reaper::useSkill2()
{
	if (_isGhostMode) return;

	_isGhostMode = true;
	_ghostStartHeight = _controller->getFootPosition().y;
	_controller->setFootPosition(_controller->getFootPosition() + PxExtendedVec3(0.0f, 100.0f, 0.0f));
	this->createGhostMode();
}

void reaper::useSkill3()
{
	if (_isGhostMode) return;

}

void reaper::createDrakAura(D3DXVECTOR3 pos)
{
	darkAura* temp = new darkAura;
	temp->init(1.0f, 200, _T(".\\texture\\skill\\darkAura.png"), pos);
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}

void reaper::createGhostMode()
{
	ghostMode* temp = new ghostMode;
	temp->init(2.0f, 200, _T(".\\texture\\skill\\darkAura.png"));
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}

void reaper::turnOffGhostMode()
{
	_isGhostMode = false;
	_controller->setFootPosition(PxExtendedVec3(_controller->getFootPosition().x, _ghostStartHeight, _controller->getFootPosition().z));

	if (_controller->getFootPosition().y < _ghostStartHeight)
	{
		_controller->setFootPosition(PxExtendedVec3(_controller->getFootPosition().x, _ghostStartHeight, _controller->getFootPosition().z));
	}
}

// 타격감
// 1. 카메라 연출
// 2. 이펙트
// 3. 사운드
