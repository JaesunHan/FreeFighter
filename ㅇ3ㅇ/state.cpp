#include "stdafx.h"
#include "state.h"
#include "enemy.h"

void appear::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_APPEAR);

		if (_enemy->GetAct() == ACT_APPEAR)
		{
			_enemy->SetIsAppear(true);

			if (_enemy->isAnimationEnd())
			{
				_enemy->SetIsAppear(false);
				_enemy->setState(new idle);
			}	
		}
		else
			_enemy->setState(new idle);
	}
		
}

// ===========================================================================================================================

void idle::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_IDLE);
	}
		
}

// ===========================================================================================================================

void run::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_RUN_FRONT);

		if (_enemy->GetTarget())
		{
			PxController* _controller = _enemy->getController();

			PxControllerState state;
			if (_controller)
				_controller->getState(state);

			D3DXVECTOR3 dir;
			dir = *(_enemy->GetTarget()) - _enemy->GetPosition();
			D3DXVec3Normalize(&dir, &dir);

			_enemy->SetDir(dir);

			PxVec3 velocity(0, 0, 0);

			//방향 + 크기 == 속도 
			velocity.x = dir.x * _enemy->GetStatus().speed;
			velocity.z = dir.z * _enemy->GetStatus().speed;

			if (!_enemy->isAbsoluteMotion())
			{
				// 움직이기 전 위치
				if (_controller)
					D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

				if (_controller)
					_controller->move(velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

				//굳이 _worldPos에 옮겨서 안해도 되지만 _worldPos로 계산하는게 생각보다 많아서
				if (_controller)
					_enemy->SetPosition(D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z));
			}
		}
	}

}

// ===========================================================================================================================

void rndRun::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_RUN_FRONT);

		PxController* _controller = _enemy->getController();

		_rndCount++;

		D3DXVECTOR3 dir = _enemy->GetDir();

		if (_rndCount >= 150)
		{
			float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
			D3DXMATRIX matR;
			D3DXMatrixRotationY(&matR, angle);
			D3DXVec3TransformNormal(&dir, &dir, &matR);
			D3DXVec3Normalize(&dir, &dir);
			_enemy->SetDir(dir);

			_rndCount = 0;
		}

		PxVec3 velocity(0, 0, 0);
		velocity.x = dir.x * _enemy->GetStatus().speed;
		velocity.z = dir.z * _enemy->GetStatus().speed;

		if (!_enemy->isAbsoluteMotion())
		{
			// 움직이기 전 위치
			if (_controller)
				D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

			if (_controller)
				_controller->move(velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

			//굳이 _worldPos에 옮겨서 안해도 되지만 _worldPos로 계산하는게 생각보다 많아서					
			if (_controller)
				_enemy->SetPosition(D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z));
		}
	}
}

// ===========================================================================================================================

void goHome::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_RUN_FRONT);

		PxController* _controller = _enemy->getController();

		D3DXVECTOR3 dir;
		dir = _enemy->GetRespawnPos() - _enemy->GetPosition();
		D3DXVec3Normalize(&dir, &dir);

		_enemy->SetDir(dir);

		PxVec3 velocity(0, 0, 0);

		//방향 + 크기 == 속도 
		velocity.x = dir.x * _enemy->GetStatus().speed;
		velocity.z = dir.z * _enemy->GetStatus().speed;

		if (_controller)
			_controller->move(velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		if (_controller)
			_enemy->SetPosition(D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z));
	}
}

// ===========================================================================================================================

void damaged::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_DAMAGED);

		if (!_enemy->isAnimationEnd())
		{
			PxController* _controller = _enemy->getController();
			PxVec3 velocity(0, 0, 0);

			D3DXVECTOR3 dir = -_enemy->GetPosition();
			D3DXVec3Normalize(&dir, &dir);
			velocity.x = dir.x * _speed;
			velocity.z = dir.z * _speed;

			if (_controller)
				_controller->move(velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

			_speed -= 0.001f;
			if (_speed <= 0) _speed = 0;

			if (_controller)
				_enemy->SetPosition(D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z));
		}
		else
			_enemy->setState(new idle);
	}

}

// ===========================================================================================================================

void recovery::Update()
{
	if (_enemy)
	{
		_enemy->ChangeAct(ACT_RECOVERY);

		if (_enemy->isAnimationEnd())
			_enemy->setState(new idle);
	}
		
}

// ===========================================================================================================================

void death::Update()
{
	if (_enemy)
		_enemy->ChangeAct(ACT_DEATH);
}

// ===========================================================================================================================

void attack01::Update()
{
	if (_enemy)
	{
		if (_enemy->GetKind() == ENEMY_DARKLORD && _enemy->GetAct() != ACT_ATTACK00)
			_enemy->createWind();

		_enemy->ChangeAct(ACT_ATTACK00);
	}
}
void attack02::Update()
{
	if (_enemy)
	{
		if (_enemy->GetKind() == ENEMY_DARKLORD && _enemy->GetAct() != ACT_ATTACK01)
			_enemy->createWind();

		_enemy->ChangeAct(ACT_ATTACK01);
	}
}
void attack03::Update()
{
	if (_enemy)
	{
		if (_enemy->GetKind() == ENEMY_DARKLORD && _enemy->GetAct() != ACT_ATTACK02)
			_enemy->createWind();

		_enemy->ChangeAct(ACT_ATTACK02);
	}
}

// ===========================================================================================================================

void skill01::Update()
{
	if (_enemy)
		_enemy->UseSkill01();
}
void skill02::Update()
{
	if (_enemy)
		_enemy->UseSkill02();
}
void skill03::Update()
{
	if (_enemy)
		_enemy->UseSkill03();
}

// ===========================================================================================================================