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
	_AniIndex[ACT_SKILL03] = 5;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.65f;

	_coolTime[0].totalTime = _coolTime[0].currentTime = 3.0f;
	_coolTime[1].totalTime = _coolTime[1].currentTime = 6.0f;
	_coolTime[2].totalTime = _coolTime[2].currentTime = 10.0f;

	player::Init(p, character, keyPath, keyName);
}

void reaper::move()
{
	// �����̴°��� ��ȭ�� ������ �ȵǴ� ���(AbsoluteMotion)�� ��� �����̸� �ƴϵǿ�
	if (this->isAbsoluteMotion()) return;

	// Ű �Է��ϴ°Ϳ� ���� speed���� ����� �ٲ���
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

	// ȸ���� ����� angle�� ����
	float angle;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
		angle = -ANGLESPEED;
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
		angle = ANGLESPEED;
	else
		angle = 0.0f;

	// ������ angle����ŭ �÷��̾ �ٶ󺸴� ����(_worldDir)�� �ٲ���
	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, angle);
	D3DXVec3TransformNormal(&_worldDir, &_worldDir, &matR);
	D3DXVec3Normalize(&_worldDir, &_worldDir);

	// ���������� ������ �ӵ����� ����
	// ���� �츮 ������ ������ ���� ������ y���� �ӵ��� 0�� ����������
	// ���� ������ �ִ� ���ӿ����� y��ӵ��� ���⼭ ���ϴ°� �ƴ϶� �ٸ������� �����ϴ� ���� ����
	_velocity.x = _worldDir.x * speed;
	_velocity.z = _worldDir.z * speed;

	// ��������ǥ ��Ʈ�ѷ��� ������ ������ �ӵ���ŭ �̵�
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

	// �÷��̾��� ���� ��ġ�� �ٲ���
	if (_isGhostMode)
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _ghostStartHeight, _controller->getFootPosition().z);
	else
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
}

void reaper::attack()
{
	if (_isGhostMode) return;

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

	if (_coolTime[0].currentTime < _coolTime[0].totalTime) return;

	vector<int> index;
	for (int i = 0; i < _em->GetEnemy().size(); ++i)
	{
		if (_em->GetEnemy()[i]->GetIsDead()) continue;

		if (getDistance(_em->GetEnemy()[i]->GetPosition(), _worldPos) < 10.0f)
			index.push_back(i);
	}

	if (index.size() != 0)
	{
		_coolTime[0].currentTime = 0.0f;
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

	if (_coolTime[1].currentTime < _coolTime[1].totalTime) return;
	_coolTime[1].currentTime = 0.0f;

	_isGhostMode = true;
	_ghostStartHeight = _controller->getFootPosition().y;
	_controller->setFootPosition(_controller->getFootPosition() + PxExtendedVec3(0.0f, 100.0f, 0.0f));
	this->createGhostMode();
}

void reaper::useSkill3()
{
	if (_isGhostMode) return;

	if (_coolTime[2].currentTime < _coolTime[2].totalTime) return;
	_coolTime[2].currentTime = 0.0f;

	this->changeAct(ACT_SKILL03);

	this->createGravityShot();
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

void reaper::createGravityShot()
{
	float radius = 0.25f;
	gravityShot* temp = new gravityShot;
	D3DXVec3Normalize(&_worldDir, &_worldDir);
	D3DXVECTOR3 startPosition = _worldPos + _worldDir * 1.5f;
	temp->init(radius, 1000, _T(".\\texture\\skill\\darkAura.png"), startPosition, PxVec3(_worldDir.x, _worldDir.y, _worldDir.z));
	temp->createController(_cm, _material);
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

bool reaper::isGravityStart()
{
	return (_currentAct == ACT_SKILL03 && _skinnedMesh->getCurrentAnimationRate() > this->GetAttackAniRate());
}

// Ÿ�ݰ�
// 1. ī�޶� ����
// 2. ����Ʈ
// 3. ����
