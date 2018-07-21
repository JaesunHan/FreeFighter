#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"

//���̽�Ÿ���� ��Ǿƴ�
#include "jmAstar.h"
//���ʹ̸Ŵ���
#include "enemyManager.h"
//��������
#include "stateContext.h"
//��ƼŬ
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

		// ���� ���� �����̴� ����
		_worldDir = *_targetPos - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);

		//���� + ũ�� == �ӵ� 
		_velocity.x = _worldDir.x * _status.speed;
		_velocity.z = _worldDir.z * _status.speed;

		if (!isAbsoluteMotion())
		{
			// �����̱� �� ��ġ
			if (_controller)
				D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

			if (_controller)
				_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

			if (true || false);		// ���� �̻��ϸ� �������� ���� tempPos��

			//���� _worldPos�� �Űܼ� ���ص� ������ _worldPos�� ����ϴ°� �������� ���Ƽ�
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

	// ���� + ũ�� == �ӵ� 
	_velocity.x = _worldDir.x * _status.speed;
	_velocity.z = _worldDir.z * _status.speed;

	if (!isAbsoluteMotion())
	{
		// �����̱� �� ��ġ
		if (_controller)
			D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

		if (_controller)
			_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		if (true || false);		// ���� �̻��ϸ� �������� ���� tempPos��

		//���� _worldPos�� �Űܼ� ���ص� ������ _worldPos�� ����ϴ°� �������� ���Ƽ�					
		if (_controller)
			_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
	}

}

void enemy::GoHome()
{
	if (_AniIndex[ACT_RUN_FRONT] != -1)
		_nextAct = ACT_RUN_FRONT;

	// ���� ���� �����̴� ����
	_worldDir = _respawnPos - _worldPos;
	D3DXVec3Normalize(&_worldDir, &_worldDir);

	//���� + ũ�� == �ӵ� 
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
	_velocity.x = dir.x * 0.5f;
	_velocity.z = dir.z * 0.5f;

	if (_controller)
		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

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

		wind* temp = new wind;
		temp->init(2.0f, 10, L"");
		temp->SetEnemyAdressLink(this);

		_vParticle.push_back(temp);
	}
		
}

void enemy::Attack02()
{
	if (_AniIndex[ACT_ATTACK01] != -1)
	{
		_nextAct = ACT_ATTACK01;	

		wind* temp = new wind;
		temp->init(2.0f, 10, L"");
		temp->SetEnemyAdressLink(this);

		_vParticle.push_back(temp);
	}
		
}

void enemy::Attack03()
{
	if (_AniIndex[ACT_ATTACK02] != -1)
	{
		_nextAct = ACT_ATTACK02;

		wind* temp = new wind;
		temp->init(2.0f, 10, L"");
		temp->SetEnemyAdressLink(this);

		_vParticle.push_back(temp);
	}
		
}