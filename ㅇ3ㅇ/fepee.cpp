#include "stdafx.h"
#include "fepee.h"
#include "skinnedMesh.h"
#include "enemyManager.h"
#include "enemy.h"
#include "particleSystems.h"


fepee::fepee()
	: _skill03Count(-1)
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
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 3;

	_AniIndex[ACT_SKILL01] = 6;
	_AniIndex[ACT_SKILL03] = 6;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.45f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.0f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.0f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.0f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.0f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.0f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.0f;

	player::Init(p, character, keyPath, keyName);
}

void fepee::Update()
{
	if (_currentAct == ACT_SKILL03)
	{
		// Ű �Է��ϴ°Ϳ� ���� speed���� ����� �ٲ���
		float speed = _status.speed * 1.5f;

		if (_isFastSkillOn)
			speed *= 2;

		D3DXVec3Normalize(&_worldDir, &_worldDir);
		D3DXVECTOR3 dir = -_worldDir;

		// ���������� ������ �ӵ����� ����
		// ���� �츮 ������ ������ ���� ������ y���� �ӵ��� 0�� ����������
		// ���� ������ �ִ� ���ӿ����� y��ӵ��� ���⼭ ���ϴ°� �ƴ϶� �ٸ������� �����ϴ� ���� ����
		_velocity.x = dir.x * speed;
		_velocity.z = dir.z * speed;

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
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

		_skill03Count++;
		if (_skill03Count % (20 / (int)_aniPlaySpeed) == 0)
		{
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

			_skill03Count = 0;
		}
	}
	else _skill03Count = -1;

	player::Update();
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

	if (_currentAct == ACT_ATTACK00)
	{
		if (_skinnedMesh->getCurrentAnimationRate() > this->GetAttackAniRate() && _isOneHit)
		{
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

			this->SetOneHit();
		}
	}
}

void fepee::useSkill1()
{
	float numOfArrow = 5.0f;
	for (int i = 0; i < numOfArrow; ++i)
	{
		D3DXVECTOR3 dir;
		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, (-30.0f + 60.0f / numOfArrow * i) * DEG2RAD);
		D3DXVec3TransformNormal(&dir, &_worldDir, &matR);
		D3DXVECTOR3 startPosition = _worldPos + dir * 1.5f;
		float angle = getAngle(0, 0, dir.x, dir.z) - D3DX_PI / 2;
		this->createPoisonArrow(startPosition, dir, angle);
	}

	this->changeAct(ACT_SKILL01);
}

void fepee::useSkill2()
{
	_isFastSkillOn = true;
	fastBuff* temp = new fastBuff;
	temp->init(200, _T(".\\texture\\skill\\fastBuff.png"));
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}

void fepee::useSkill3()
{
	this->changeAct(ACT_SKILL03);
}

void fepee::createPoisonArrow(D3DXVECTOR3 startPosition, D3DXVECTOR3 dir, float angle)
{
	poisonArrow* temp = new poisonArrow;
	temp->init(0.5f, 200, _T(".\\texture\\skill\\poisonArrow.png"), startPosition, PxVec3(dir.x, dir.y, dir.z), angle);
	temp->createController(_cm, _material);
	temp->setPlayer(this);

	_vParticle.push_back(temp);
}
