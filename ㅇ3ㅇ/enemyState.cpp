#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"

//에이스타지만 사실아님
#include "jmAstar.h"
//에너미매니저
#include "enemyManager.h"
//상태패턴
#include "stateContext.h"
//파티클
#include "particleSystems.h"

void enemy::Appear()
{
	if (_AniIndex[ACT_APPEAR] != -1)
		_nextAct = ACT_APPEAR;
}

void enemy::Idle()
{
	if (_AniIndex[ACT_IDLE] != -1)
		_nextAct = ACT_IDLE;
}

void enemy::Moving()
{
	if (_AniIndex[ACT_RUN_FRONT] != -1)
		_nextAct = ACT_RUN_FRONT;

	if (_targetPos)
	{
		PxControllerState state;
		if (_controller)
			_controller->getState(state);

		// 적이 실제 움직이는 방향
		_worldDir = *_targetPos - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);

		//방향 + 크기 == 속도 
		_velocity.x = _worldDir.x * _status.speed;
		_velocity.z = _worldDir.z * _status.speed;

		if (!isAbsoluteMotion())
		{
			// 움직이기 전 위치
			if (_controller)
				D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

			if (_controller)
				_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

			if (true || false);		// 뭔가 이상하면 움직이지 말고 tempPos로

			//굳이 _worldPos에 옮겨서 안해도 되지만 _worldPos로 계산하는게 생각보다 많아서
			if (_controller)
				_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
		}
	}
}

void enemy::RNDMoving()
{
	if (_AniIndex[ACT_RUN_FRONT] != -1)
		_nextAct = ACT_RUN_FRONT;

	_RndCount++;

	if (_RndCount % 150 == 0)
	{
		float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, angle);
		D3DXVec3TransformNormal(&_worldDir, &_worldDir, &matR);
		D3DXVec3Normalize(&_worldDir, &_worldDir);
		_RndCount = 0;
	}

	// 방향 + 크기 == 속도 
	_velocity.x = _worldDir.x * _status.speed;
	_velocity.z = _worldDir.z * _status.speed;

	if (!isAbsoluteMotion())
	{
		// 움직이기 전 위치
		if (_controller)
			D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

		if (_controller)
			_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		if (true || false);		// 뭔가 이상하면 움직이지 말고 tempPos로

		//굳이 _worldPos에 옮겨서 안해도 되지만 _worldPos로 계산하는게 생각보다 많아서					
		if (_controller)
			_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
	}

}

void enemy::GoHome()
{
	if (_AniIndex[ACT_RUN_FRONT] != -1)
		_nextAct = ACT_RUN_FRONT;

	// 적이 실제 움직이는 방향
	_worldDir = _respawnPos - _worldPos;
	D3DXVec3Normalize(&_worldDir, &_worldDir);

	//방향 + 크기 == 속도 
	_velocity.x = _worldDir.x * _status.speed;
	_velocity.z = _worldDir.z * _status.speed;

	if (_controller)
		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

	if (_controller)
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
}

void enemy::Damage()
{
	if (_AniIndex[ACT_DAMAGED] != -1)
		_nextAct = ACT_DAMAGED;

	D3DXVECTOR3 dir = -_worldDir;
	D3DXVec3Normalize(&dir, &dir);
	_velocity.x = dir.x * _damagedSpeed;
	_velocity.z = dir.z * _damagedSpeed;

	if (_controller)
		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

	_damagedSpeed -= 0.001f;
	if (_damagedSpeed <= 0) _damagedSpeed = 0;

	if (_controller)
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

}

void enemy::Recovery()
{
	if (_AniIndex[ACT_RECOVERY] != -1)
		_nextAct = ACT_RECOVERY;
	else
		_nextAct = ACT_IDLE;

	_damagedCount = 0;
	_damagedSpeed = 0.05f;
}

void enemy::Death()
{
	if (_AniIndex[ACT_DEATH] != -1)
		_nextAct = ACT_DEATH;
}

void enemy::Attack01()
{
	if (_AniIndex[ACT_ATTACK00] != -1)
	{
		_nextAct = ACT_ATTACK00;

		//wind* temp = new wind;
		//temp->init(2.0f, 10, L"");
		//temp->SetEnemyAdressLink(this);
		//
		//_vParticle.push_back(temp);
	}
		
}

void enemy::Attack02()
{
	if (_AniIndex[ACT_ATTACK01] != -1)
	{
		_nextAct = ACT_ATTACK01;	

		//wind* temp = new wind;
		//temp->init(2.0f, 10, L"");
		//temp->SetEnemyAdressLink(this);
		//
		//_vParticle.push_back(temp);
	}
		
}

void enemy::Attack03()
{
	if (_AniIndex[ACT_ATTACK02] != -1)
	{
		_nextAct = ACT_ATTACK02;

		//wind* temp = new wind;
		//temp->init(2.0f, 10, L"");
		//temp->SetEnemyAdressLink(this);
		//
		//_vParticle.push_back(temp);
	}
		
}