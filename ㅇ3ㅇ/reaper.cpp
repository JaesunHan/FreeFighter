#include "stdafx.h"
#include "reaper.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"


reaper::reaper()
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
	_AniIndex[ACT_ATTACKED00] = 4;
	_AniIndex[ACT_DEATH] = 3;

	player::Init(p, character, keyPath, keyName);
}

void reaper::attack()
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
			this->changeAct(ACT_ATTACK00);
		// ���� attack00�ε� �޺��� �̾�� ���ɼ��� ������ attack01���·� �ٲ���
		// �� �ؿ��� ��������
		else if (_currentAct == ACT_ATTACK00 && _skinnedMesh->IsAnimationEnd())
		{
			this->changeAct(ACT_ATTACK01);

			D3DXVECTOR3 startPos;
			D3DXVec3Normalize(&_worldDir, &_worldDir);
			startPos = _worldPos + _worldDir * 3.0f;

			for (int i = 0; i < _em->GetEnemy().size(); ++i)
			{
				if (!_em->GetEnemy()[i]->GetIsDead())
				{
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
			}

			this->createDrakAura(startPos);
		}
	}
}

void reaper::useSkill1()
{
}

void reaper::useSkill2()
{
}

void reaper::useSkill3()
{
}

void reaper::createDrakAura(D3DXVECTOR3 pos)
{
	darkAura* temp = new darkAura;
	temp->init(1.0f, 200, _T(".\\texture\\skill\\darkAura.png"), pos);
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}
