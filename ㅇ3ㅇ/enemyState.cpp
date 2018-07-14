#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"

//���̽�Ÿ���� ��Ǿƴ�
#include "jmAstar.h"
//���ʹ̸Ŵ���
#include "enemyManager.h"
//��������
#include "stateContext.h"

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
		_velocity.x = _worldDir.x * 0.05f;
		_velocity.z = _worldDir.z * 0.05f;

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

void enemy::Damage()
{
	if (_AniIndex[ACT_ATTACKED00] != -1)
		_nextAct = ACT_ATTACKED00;
}

void enemy::Death()
{
	if (_AniIndex[ACT_DEATH] != -1)
		_nextAct = ACT_DEATH;
}

void enemy::Attack01()
{
	if (_AniIndex[ACT_ATTACK00] != -1)
		_nextAct = ACT_ATTACK00;
}

void enemy::Attack02()
{
	if (_AniIndex[ACT_ATTACK01] != -1)
		_nextAct = ACT_ATTACK01;
}

void enemy::Attack03()
{
	if (_AniIndex[ACT_ATTACK02] != -1)
		_nextAct = ACT_ATTACK02;
}