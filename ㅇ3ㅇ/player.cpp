#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"
#include "particleSystems.h"
#include "enemyManager.h"
#include "enemy.h"
#include "hpBar.h"
#include "itemManager.h"
#include "item.h"

player::player()
	: _keySet(NULL)
	, _currentCharacter(CHAR_NONE)
	, _opponent(NULL)
	, _comboCount(30)
	, _em(NULL)
	, _isJump(true)
	, _portrait(NULL)
	, _name(_T(""))
	, _hpBar(NULL)
	, _im(NULL)
{
	for (int i = 0; i < 3; ++i)
	{
		_coolTime[i].currentTime = 1.0f;
		_coolTime[i].totalTime = 1.0f;
		_coolTimeBar[i] = NULL;
	}
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
	// ui초기화(위치잡아주기)
	_portrait = new uiImageView;
	_portrait->init(_T("portraitEdge_back") + _name, _T(".\\texture\\ui\\portraitEdge_back.png"), vp.Width / 2 * p + 100, vp.Height - 100);

	uiImageView* ui = new uiImageView;
	ui->init(_T("portrait_") + _name, (_T(".\\texture\\portraits\\") + _name + _T(".png")).c_str(), vp.Width / 2 * p + 100, vp.Height - 100);

	_portrait->addChild(ui);

	ui = new uiImageView;
	ui->init(_T("portraitEdge") + _name, _T(".\\texture\\ui\\portraitEdge.png"), vp.Width / 2 * p + 100, vp.Height - 100);

	_portrait->addChild(ui);

	// 스킬 아이콘 불러오기
	ui = new uiImageView;
	ui->init(_name + _T("skill0"), (_T(".\\texture\\ui\\skillIcon\\") + _name + _T("_skill0.png")).c_str(), vp.Width / 2 * p + 40, vp.Height / 2 - 35 - 70);

	_portrait->addChild(ui);

	ui = new uiImageView;
	ui->init(_name + _T("skill1"), (_T(".\\texture\\ui\\skillIcon\\") + _name + _T("_skill1.png")).c_str(), vp.Width / 2 * p + 40, vp.Height / 2 - 35);
	
	_portrait->addChild(ui);
	
	ui = new uiImageView;
	ui->init(_name + _T("skill2"), (_T(".\\texture\\ui\\skillIcon\\") + _name + _T("_skill2.png")).c_str(), vp.Width / 2 * p + 40, vp.Height / 2 - 35 + 70);
	
	_portrait->addChild(ui);

	// HPbar
	_hpBar = new hpBar;
	WCHAR tempKey[256];
	swprintf(tempKey, _T("playerHP%d"), p);
	wstring tempKeyName = tempKey + _name;
	WCHAR tempHP[256];
	swprintf(tempHP, _T("%d.tga"), _currentCharacter);
	_hpBar->Init(tempKeyName, _T(".\\texture\\hpBar\\"), tempHP, GREEN, RED);

	// coolTimeBar
	for (int i = 0; i < 3; ++i)
	{
		_coolTimeBar[i] = new hpBar;
		swprintf(tempKey, _T("playerCool%d_%d"), p, i);
		_coolTimeBar[i]->Init(tempKey, _T(".\\texture\\hpBar\\"), _T("coolTime.tga"), YELLOW, D3DCOLOR_ARGB(255, 50, 50, 0));
	}
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

	for (int i = 0; i < 3; ++i)
		SAFE_DELETE(_coolTimeBar[i]);
}

void player::Update()
{
	float rate = _skinnedMesh->getCurrentAnimationRate();
	// 플레이어의 공격에 관련된 모든 것(?)을 바꾸는 함수
	this->attack();
	// 플레이어의 스킬 사용
	this->useSkill();
	// 플레이어의 이동에 관련된 모든 것(?)을 바꾸는 함수
	this->move();
	this->jump();

	// attack상태(AbsoluteMotion)가 다시 바뀌기 전에 처리
	this->attackEnemy();

	// 현재 상태가 AbsoluteMotion일 경우
	if (this->isAbsoluteMotion())
	{
		// 애니메이션이 끝나면 일단 만만한 idle상태로 바꿔줌
		if (_skinnedMesh->IsAnimationEnd())
			this->changeAct(ACT_IDLE);
	}

	// 위에선 월드매트릭스를 만들 때 필요한 정보들을 바꿔주기만 했고
	// 실제로 월드매트릭스를 만드는 함수는 이것
	this->CreateWorldMatrix();

	if (_isFastSkillOn)
		_aniPlaySpeed = 2.0f;
	else
		_aniPlaySpeed = 1.0f;
	// interfaceCharacter::Update() 의 경우 결국 skinnedMesh의 블렌드 애니메이션 처리밖에 안해줌
	// 그러므로 여기까지 오기 전에 충분히 수치와 애니메이션정보를 바꿔준 후 업캐스팅해도 무방함
	interfaceCharacter::Update();

	// 파티클(스킬) 업데이트
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
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		_status.currentHp += _status.maxHp / 10;
	}

	if (_hpBar)
		_hpBar->Update(_status.currentHp, _status.maxHp);

	for (int i = 0; i < 3; ++i)
	{
		if (_coolTimeBar[i])
		{
			_coolTime[i].currentTime += TIMEMANAGER->getElapsedTime();
			if (_coolTime[i].currentTime > _coolTime[i].totalTime)
				_coolTime[i].currentTime = _coolTime[i].totalTime;
			_coolTimeBar[i]->Update(_coolTime[i].currentTime, _coolTime[i].totalTime, false);
		}
	}
}

void player::move()
{
	// 움직이는것은 변화가 있으면 안되는 모션(AbsoluteMotion)일 경우 움직이면 아니되오
	if (this->isAbsoluteMotion()) return;

	// 키 입력하는것에 따라 speed값과 모션을 바꿔줌
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
	
	// 회전에 사용할 angle값 설정
	float angle;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
		angle = -ANGLESPEED;
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
		angle = ANGLESPEED;
	else
		angle = 0.0f;

	// 설정된 angle값만큼 플레이어가 바라보는 방향(_worldDir)을 바꿔줌
	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, angle);
	D3DXVec3TransformNormal(&_worldDir, &_worldDir, &matR);
	D3DXVec3Normalize(&_worldDir, &_worldDir);

	// 물리엔진에 적용할 속도값을 설정
	// 현재 우리 게임은 점프가 없기 때문에 y축의 속도는 0로 설정했으나
	// 만약 점프가 있는 게임에서는 y축속도는 여기서 정하는게 아니라 다른곳에서 설정하는 것이 좋음
	_velocity.x = _worldDir.x * speed;
	_velocity.z = _worldDir.z * speed;

	// 물리엔진표 컨트롤러로 위에서 설정한 속도만큼 이동
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

	// 플레이어의 월드 위치를 바꿔줌
	_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

	this->getItem();
}

void player::jump()
{
	if (_isDebug)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_velocity.y = JUMPPOWER;
			_isJump = true;
		}
	}

	if (_isJump)
	{
		_velocity.y -= GRAVITY;
	}
}

void player::attack()
{
	// 카운트는 진리인 것이다. 그러한 것이다.
	_comboCount++;

	// 어택키를 누를 때 마다 카운트를 0으로 바꾸면서 콤보를 이어나갈 가능성을 만들어줌
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
		_comboCount = 0;

	// 카운트가 30이 되기 전 애니메이션이 끝난다면 콤보가 이어진다
	if (_comboCount < 30)
	{
		// 일단 지금 공격이 가능한 상태(AbsoluteMotion이 아닌 경우)이면 attack00으로 바꿔줌
		if (!this->isAbsoluteMotion())
			this->changeAct(ACT_ATTACK00);
		// 현재 attack00인데 콤보를 이어나갈 가능성이 있으면 attack01상태로 바꿔줌
		// 그 밑에도 마찬가지
		else if (_currentAct == ACT_ATTACK00 && _skinnedMesh->IsAnimationEnd())
			this->changeAct(ACT_ATTACK01);
		else if (_currentAct == ACT_ATTACK01 && _skinnedMesh->IsAnimationEnd())
			this->changeAct(ACT_ATTACK02);
	}
}

void player::attackEnemy()
{
	if (!_isOneHit) return;

	if (_em)
	{
		for (int i = 0; i < _em->GetEnemy().size(); ++i)
			this->HitCheck(_em->GetEnemy()[i], _status.atkDmg - _em->GetEnemy()[i]->GetStatus().def, 1.0f, 1.0f, this->GetAttackAniRate());
	}

	if (_opponent)
		this->HitCheck(_opponent, _status.atkDmg - _opponent->GetStatus().def, 1.0f, 1.0f, this->GetAttackAniRate());

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
	// 바꾸려하는 모션의 인덱스값이 -1이라는것은 해당 모션이 없다는 뜻임
	if (_AniIndex[a] != -1)
		_nextAct = a;
	// 그럴 경우 강제로 idle상태로 바꿔버림
	// 왜냐하면 만약 attack01->attack02가 실패할 경우 애니메이션은 바뀌지 않지만
	// 현재 짜놓은 알고리즘상 계속 attack02가 되려고 시도할 경우가 생길것이라 판단함
	// 따라서 가장 만만한 idle상태로 바꿔버림 ㅎ
	else
		_nextAct = ACT_IDLE;

	// 애니메이션을 바뀔 모션(_nextAct)로 바꿔줌
	this->AnimationSetting();
}

void player::getItem()
{
	if (!_im) return;

	for (int i = 0; i < _im->getVItem().size();)
	{
		if (!_im->getVItem()[i]) continue;
		D3DXVECTOR3 itemPos = _im->getVItem()[i]->getPosition();
		itemPos.y = _worldPos.y;

		if (getDistance(itemPos, _worldPos) < _im->getVItem()[i]->getItemRadius())
		{
			switch (_im->getVItem()[i]->getItemType())
			{
				case ITEM_POTION:
				{
					itemEffect * temp = new itemEffect;
					temp->init(200, _T(".\\texture\\item\\itemEffect_heal.png"), D3DCOLOR_ARGB(255, 0, 255, 0), 0.1f);
					temp->setPlayer(this);

					_vParticle.push_back(temp);
				}
				break;
				
				case ITEM_GOLD:
				break;
				
				case ITEM_ATTACK:
				{
					itemEffect * temp = new itemEffect;
					temp->init(200, _T(".\\texture\\item\\itemEffect_atk.png"), D3DCOLOR_ARGB(255, 255, 0, 0), 5.0f);
					temp->setPlayer(this);

					_vParticle.push_back(temp);
				}
				break;
				
				case ITEM_SPEED:
				{
					itemEffect * temp = new itemEffect;
					temp->init(200, _T(".\\texture\\item\\itemEffect_spd.png"), D3DCOLOR_ARGB(255, 255, 255, 0), 5.0f);
					temp->setPlayer(this);

					_vParticle.push_back(temp);
				}
				break;
				
				case ITEM_DEFENCE:
				{
					itemEffect * temp = new itemEffect;
					temp->init(200, _T(".\\texture\\item\\itemEffect_def.png"), D3DCOLOR_ARGB(255, 0, 0, 255), 5.0f);
					temp->setPlayer(this);

					_vParticle.push_back(temp);
				}
				break;
			}

			SAFE_OBJRELEASE(_im->getVItem()[i]);
			_im->getVItem().erase(_im->getVItem().begin() + i);
		}
		else ++i;
	}
}

void player::Render(float elapsedTime)
{
	// 플레이어에서 랜더하는 것은 결국 모델링된 skinnedMesh의 랜더밖에 없는것이다
	// 만약 스킬이나 bullet같은게 있으면 여기에 추가할 예정
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

	if (itsMe)
	{
		D3DVIEWPORT9 vp;
		D3DDEVICE->GetViewport(&vp);
		for (int i = 0; i < 3; ++i)
		{
			if (_coolTimeBar[i])
				_coolTimeBar[i]->Render(vp.X + 40, vp.Height / 2 - 5 - 70 + 70 * i);
		}
	}

	if (_portrait)
		_portrait->render();
}
