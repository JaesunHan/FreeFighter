#pragma once

#include <vector>
using namespace std;

#include "interfaceCharacter.h"
#include "playerKeySet.h"
#include "gameMode.h"

#include "uiImageView.h"

#define SPEED		0.1f
#define ANGLESPEED	(3.0f * DEG2RAD)
#define GRAVITY		0.0098f
#define JUMPPOWER	0.3f

#define DAMAGEDTIME 5

struct tagCoolTime
{
	float currentTime;
	float totalTime;
};

class particleSystem;
class enemyManager;
class itemManager;
class hpBar;

// �÷��̾ ������ �� �ִ� �𵨵�
static wstring _characterName[CHAR_END] =
{
	_T("zealot"),
	_T("reaper"),
	_T("woodGiant"),
	_T("fepee")
};

class player : public interfaceCharacter
{
protected:
	wstring				_name;
	PLAYER_KEYSET		_keySet;
	PLAYABLE_CHARACTER	_currentCharacter;
	int					_comboCount;

	interfaceCharacter*	_opponent;

protected:
	float				_aniPlaySpeed;
	bool				_isFastSkillOn;
	float				_spdBuffTime;
	float				_atkBuffTime;
	float				_atkRate;
	float				_defBuffTime;
	float				_defRate;

	bool				_isJump;

protected:
	enemyManager*		_em;

protected:
	itemManager*		_im;

	// ui��
protected:
	uiImageView*		_portrait;
	hpBar*				_hpBar;

	int					_whiteCount;
	int					_bloodAlpha;
	int					_bloodMax;
	bool				_isIncreaseBloodAlpha;

	tagCoolTime			_coolTime[3];
	hpBar*				_coolTimeBar[3];

	int					_earnedGold;

public:
	player();
	virtual ~player();
	
	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName);
	void statusInit(GAME_MODE mode);

	virtual void release();

	virtual void Update() override;
	virtual void move();
	virtual void jump();
	virtual void attack();

	virtual void HitDamage(float damage);

	virtual void attackEnemy();

	virtual void useSkill();

	virtual void useSkill1() = 0;
	virtual void useSkill2() = 0;
	virtual void useSkill3() = 0;

	virtual void changeAct(ACT a);

	virtual void getItem();

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;
	virtual void RenderUi(D3DVIEWPORT9 vp, bool itsMe);

	inline void setIsFast(bool f) { _isFastSkillOn = f; }
	inline bool getIsFast() { return _isFastSkillOn; }

	inline void setOpponent(interfaceCharacter*	o) { _opponent = o; }
	inline interfaceCharacter* getOpponent() { return _opponent; }

	inline void setEMMemory(enemyManager* em) { _em = em; }
	inline enemyManager* getEM() { return _em; }

	inline void setIMMemory(itemManager* im) { _im = im; }

	inline float getAtk() { return _status.atkDmg * _atkRate; }
	inline float getDef() { return _status.def * _defRate; }

	inline wstring getName() { return _name; }

	inline int getEarnedGold() { return _earnedGold; }
};
