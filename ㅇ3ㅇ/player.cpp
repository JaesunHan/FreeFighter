#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"
#include "particleSystems.h"
#include "enemyManager.h"
#include "enemy.h"
#include "hpBar.h"

player::player()
	: _keySet(NULL)
	, _currentCharacter(CHAR_NONE)
	, _opponent(NULL)
	, _comboCount(30)
	, _em(NULL)
	, _isJump(false)
	, _portrait(NULL)
	, _name(_T(""))
	, _hpBar(NULL)
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

	_aniPlaySpeed = 1.0f;
	_isFastSkillOn = false;

	this->AnimationSetting();

	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);
	_name = _characterName[_currentCharacter];
	// ui�ʱ�ȭ(��ġ����ֱ�)
	_portrait = new uiImageView;
	_portrait->init(_T("portraitEdge_back") + _name, _T(".\\texture\\ui\\portraitEdge_back.png"), vp.Width / 2 * p + 100, vp.Height - 100);

	uiImageView* ui = new uiImageView;
	ui->init(_T("portrait_") + _name, (_T(".\\texture\\portraits\\") + _name + _T(".png")).c_str(), vp.Width / 2 * p + 100, vp.Height - 100);

	_portrait->addChild(ui);

	ui = new uiImageView;
	ui->init(_T("portraitEdge") + _name, _T(".\\texture\\ui\\portraitEdge.png"), vp.Width / 2 * p + 100, vp.Height - 100);

	_portrait->addChild(ui);

	// ��ų ������ �ҷ�����
	ui = new uiImageView;
	ui->init(_name + _T("skill0"), (_T(".\\texture\\ui\\skillIcon\\") + _name + _T("_skill0.png")).c_str(), vp.Width / 2 * p + 66, vp.Height / 2 - 38 - 96);

	_portrait->addChild(ui);

	ui = new uiImageView;
	ui->init(_name + _T("skill1"), (_T(".\\texture\\ui\\skillIcon\\") + _name + _T("_skill1.png")).c_str(), vp.Width / 2 * p + 66, vp.Height / 2 - 38);
	
	_portrait->addChild(ui);
	
	ui = new uiImageView;
	ui->init(_name + _T("skill2"), (_T(".\\texture\\ui\\skillIcon\\") + _name + _T("_skill2.png")).c_str(), vp.Width / 2 * p + 66, vp.Height / 2 - 38 + 96);
	
	_portrait->addChild(ui);

	// HPbar
	_hpBar = new hpBar;
	WCHAR tempKey[256];
	swprintf(tempKey, _T("playerHP%d"), p);
	WCHAR tempHP[256];
	swprintf(tempHP, _T("%d.tga"), _currentCharacter);
	_hpBar->Init(tempKey, _T(".\\texture\\hpBar\\"), tempHP, GREEN, RED);
}

void player::statusInit(GAME_MODE mode)
{
	wstring folder = _T("iniData");
	wstring fileName = _T("playerCharacters");
	WCHAR subject[1024];
	swprintf(subject, _T("character%d"), _currentCharacter);

	int level;
	if (mode == GAME_STORY)
		level = INIDATA->loadDataInterger(folder.c_str(), fileName.c_str(), subject, _T("CharacterLv"));
	else if (mode == GAME_FIGHT)
		level = 10;

	_status.maxHp = INIDATA->loadDataFloat(folder.c_str(), fileName.c_str(), subject, _T("CharacterHp"));
	_status.atkDmg = INIDATA->loadDataFloat(folder.c_str(), fileName.c_str(), subject, _T("CharacterAtk"));
	_status.def = INIDATA->loadDataFloat(folder.c_str(), fileName.c_str(), subject, _T("CharacterDef"));
	_status.speed = INIDATA->loadDataFloat(folder.c_str(), fileName.c_str(), subject, _T("CharacterSpd"));
	_status.skillLV1 = INIDATA->loadDataInterger(folder.c_str(), fileName.c_str(), subject, _T("Skill0Lv"));
	_status.skillLV2 = INIDATA->loadDataInterger(folder.c_str(), fileName.c_str(), subject, _T("Skill1Lv"));
	_status.skillLV3 = INIDATA->loadDataInterger(folder.c_str(), fileName.c_str(), subject, _T("Skill2Lv"));

	for (int i = 2; i <= level; ++i)
	{
		_status.maxHp += 100;
		_status.atkDmg = i + (_status.atkDmg * 1.1f);
		_status.def = i + (_status.def * 1.09f);
		_status.speed += 0.01f;
	}

	_status.currentHp = _status.maxHp;
}

void player::release()
{
	SAFE_OBJRELEASE(_portrait);
	SAFE_DELETE(_hpBar);
}

void player::Update()
{
	float rate = _skinnedMesh->getCurrentAnimationRate();
	// �÷��̾��� ���ݿ� ���õ� ��� ��(?)�� �ٲٴ� �Լ�
	this->attack();
	// �÷��̾��� ��ų ���
	this->useSkill();
	// �÷��̾��� �̵��� ���õ� ��� ��(?)�� �ٲٴ� �Լ�
	this->move();
	this->jump();

	// attack����(AbsoluteMotion)�� �ٽ� �ٲ�� ���� ó��
	this->attackEnemy();

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
		_aniPlaySpeed = 2.0f;
	else
		_aniPlaySpeed = 1.0f;
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

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
	{
		_status.currentHp -= _status.maxHp / 10;
	}

	if (_hpBar)
		_hpBar->Update(_status.currentHp, _status.maxHp);
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

void player::attackEnemy()
{
	if (!_isOneHit) return;

	for (int i = 0; i < _em->GetEnemy().size(); ++i)
		this->HitCheck(_em->GetEnemy()[i], _status.atkDmg - _em->GetEnemy()[i]->GetStatus().def, 1.0f, 1.0f, this->GetAttackAniRate());

	if (this->IsAttackMotion() && _skinnedMesh->getCurrentAnimationRate() > this->GetAttackAniRate())
		_isOneHit = false;
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
	interfaceCharacter::Render(elapsedTime * _aniPlaySpeed);
}

void player::RenderUi(D3DVIEWPORT9 vp, bool itsMe)
{
	if (_hpBar)
	{
		if (itsMe)
		{
			float scaX = 1.5f;
			float destX = vp.X + 200 * scaX;
			float destY = vp.Height - 50;
			_hpBar->Render(destX, destY, D3DXVECTOR3(scaX, 1.0f, 1.0f));
		}
		else
		{
			D3DXVECTOR3 viewPos;
			D3DXMATRIX view;
			D3DDEVICE->GetTransform(D3DTS_VIEW, &view);
			D3DXVec3TransformCoord(&viewPos, &_worldPos, &view);

			float sca = (20.0f - viewPos.z) / 20.0f;
			if (sca > 1.0f)
				sca = 1.0f;
			else if (sca < 0.0f)
				sca = 0.0f;

			_hpBar->Render(_worldPos, D3DXVECTOR3(sca, sca, sca));
		}
	}

	if (_portrait)
		_portrait->render();
}
