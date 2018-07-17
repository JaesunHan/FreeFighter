#include "stdafx.h"
#include "fepee.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "poisonArrow.h"


fepee::fepee()
{
}


fepee::~fepee()
{
}

void fepee::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_ATTACKED00] = 4;
	_AniIndex[ACT_DEATH] = 3;

	player::Init(p, character, keyPath, keyName);
}

void fepee::attack()
{
	// ī��Ʈ�� ������ ���̴�. �׷��� ���̴�.
	_comboCount++;

	// ����Ű�� ���� �� ���� ī��Ʈ�� 0���� �ٲٸ鼭 �޺��� �̾�� ���ɼ��� �������
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
		_comboCount = 0;

	// ī��Ʈ�� 30�� �Ǳ� �� �ִϸ��̼��� �����ٸ� �޺��� �̾�����
	if (_comboCount < 30)
	{
		// �ϴ� ���� ������ ������ ����(AbsoluteMotion�� �ƴ� ���)�̸� attack00���� �ٲ���
		if (!this->isAbsoluteMotion())
		{
			this->changeAct(ACT_ATTACK00);

			for (int i = 0; i < _em->GetEnemy().size(); ++i)
			{
				if (getDistance(_em->GetEnemy()[i]->GetPosition(), _worldPos) < 10.0f)
				{
					_worldDir = _em->GetEnemy()[i]->GetPosition() - _worldPos;
					D3DXVec3Normalize(&_worldDir, &_worldDir);
				}
			}

			D3DXVECTOR3 startPosition = _worldPos + _worldDir;
			float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) - D3DX_PI / 2;
			this->createPoisonArrow(startPosition, _worldDir, angle);
		}
		// ���� attack00�ε� �޺��� �̾�� ���ɼ��� ������ attack01���·� �ٲ���
		// �� �ؿ��� ��������
		else if (_currentAct == ACT_ATTACK00 && _skinnedMesh->IsAnimationEnd())
		{
			this->changeAct(ACT_ATTACK01);

			for (int i = 0; i < 8; ++i)
			{
				D3DXVECTOR3 dir;
				D3DXMATRIX matR;
				D3DXMatrixRotationY(&matR, D3DX_PI / 4 * i);
				D3DXVec3TransformNormal(&dir, &_worldDir, &matR);
				float angle = getAngle(0, 0, dir.x, dir.z) - D3DX_PI / 2;
				D3DXVECTOR3 startPosition = _worldPos + dir;
				this->createPoisonArrow(startPosition, dir, angle);
			}
		}
	}
}

void fepee::useSkill1()
{
}

void fepee::useSkill2()
{
}

void fepee::useSkill3()
{
}

void fepee::createPoisonArrow(D3DXVECTOR3 startPosition, D3DXVECTOR3 dir, float angle)
{
	poisonArrow* temp = new poisonArrow;
	temp->init(0.5f, 200, _T(".\\texture\\skill\\poisonArrow.png"), startPosition, PxVec3(dir.x, dir.y, dir.z), angle);
	temp->createController(_cm, _material);
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}
