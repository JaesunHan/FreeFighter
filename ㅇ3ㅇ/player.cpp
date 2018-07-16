#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"
#include "particleSystems.h"

player::player()
	: _keySet(NULL)
	, _currentCharacter(CHAR_NONE)
	, _opponent(NULL)
	, _comboCount(30)
	, _em(NULL)
	, _isJump(false)
{
}

player::~player()
{
}

void player::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_keySet = _playerKeySet[p];
	
	_currentCharacter = character;
	if (character == CHAR_ZEALOT)
		_worldSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	else
		_worldSca = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	_status.speed = 0.5f;

	interfaceCharacter::Init(keyPath, keyName);

	_currentAct = ACT_NONE;
	_nextAct = ACT_IDLE;

	_aniRate = 1.0f;
	_isFastSkillOn = false;

	this->AnimationSetting();
}

void player::release()
{
	for (int i = 0; i < _vParticle.size();)
		SAFE_OBJRELEASE(_vParticle[i]);
	_vParticle.clear();
}

void player::Update()
{
	// �÷��̾��� ���ݿ� ���õ� ��� ��(?)�� �ٲٴ� �Լ�
	this->attack();
	// �÷��̾��� ��ų ���
	this->useSkill();
	// �÷��̾��� �̵��� ���õ� ��� ��(?)�� �ٲٴ� �Լ�
	this->move();
	this->jump();

	// ���� ���°� AbsoluteMotion�� ���
	if (this->isAbsoluteMotion())
	{
		// �ִϸ��̼��� ������ �ϴ� ������ idle���·� �ٲ���
		if (_skinnedMesh->IsAnimationEnd())
			this->changeAct(ACT_IDLE);
	}

	// ������ �����Ʈ������ ���� �� �ʿ��� �������� �ٲ��ֱ⸸ �߰�
	// ������ �����Ʈ������ ����� �Լ��� �̰�
	this->CreateWorldMatrix();

	if (_isFastSkillOn)
		_aniRate = 2.0f;
	else
		_aniRate = 1.0f;
	// interfaceCharacter::Update() �� ��� �ᱹ skinnedMesh�� ���� �ִϸ��̼� ó���ۿ� ������
	// �׷��Ƿ� ������� ���� ���� ����� ��ġ�� �ִϸ��̼������� �ٲ��� �� ��ĳ�����ص� ������
	interfaceCharacter::Update();

	// ��ƼŬ(��ų) ������Ʈ
	for (int i = 0; i < _vParticle.size();)
	{
		_vParticle[i]->update();

		if (_vParticle[i]->isDead())
		{
			SAFE_OBJRELEASE(_vParticle[i]);
			_vParticle.erase(_vParticle.begin() + i);
		}
		else ++i;
	}
}

void player::move()
{
	// �����̴°��� ��ȭ�� ������ �ȵǴ� ���(AbsoluteMotion)�� ��� �����̸� �ƴϵǿ�
	if (this->isAbsoluteMotion()) return;

	// Ű �Է��ϴ°Ϳ� ���� speed���� ����� �ٲ���
	float speed;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
	{
		this->changeAct(ACT_RUN_FRONT);
		speed = SPEED;
	}
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
	{
		this->changeAct(ACT_RUN_BACK);
		speed = -SPEED;
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
			_isJump = false;
	}

	// �÷��̾��� ���� ��ġ�� �ٲ���
	_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
}

void player::jump()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_velocity.y = JUMPPOWER;
		_isJump = true;
	}

	if (_isJump)
	{
		_velocity.y -= GRAVITY;
	}
}

void player::attack()
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
			this->changeAct(ACT_ATTACK01);
		else if (_currentAct == ACT_ATTACK01 && _skinnedMesh->IsAnimationEnd())
			this->changeAct(ACT_ATTACK02);
	}
}

void player::useSkill()
{
	if (this->isAbsoluteMotion()) return;

	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_SKILL_0]))
		this->useSkill1();
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_SKILL_1]))
		this->useSkill2();
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_SKILL_2]))
		this->useSkill3();
}

void player::changeAct(ACT a)
{
	// �ٲٷ��ϴ� ����� �ε������� -1�̶�°��� �ش� ����� ���ٴ� ����
	if (_AniIndex[a] != -1)
		_nextAct = a;
	// �׷� ��� ������ idle���·� �ٲ����
	// �ֳ��ϸ� ���� attack01->attack02�� ������ ��� �ִϸ��̼��� �ٲ��� ������
	// ���� ¥���� �˰���� ��� attack02�� �Ƿ��� �õ��� ��찡 ������̶� �Ǵ���
	// ���� ���� ������ idle���·� �ٲ���� ��
	else
		_nextAct = ACT_IDLE;

	// �ִϸ��̼��� �ٲ� ���(_nextAct)�� �ٲ���
	this->AnimationSetting();
}

void player::Render(float elapsedTime)
{
	// �÷��̾�� �����ϴ� ���� �ᱹ �𵨸��� skinnedMesh�� �����ۿ� ���°��̴�
	// ���� ��ų�̳� bullet������ ������ ���⿡ �߰��� ����
	interfaceCharacter::Render(elapsedTime * _aniRate);
}
