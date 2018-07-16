#pragma once

#include <vector>
using namespace std;

#include "interfaceCharacter.h"
#include "playerKeySet.h"

#define SPEED		0.1f
#define ANGLESPEED	(3.0f * DEG2RAD)
#define GRAVITY		0.0098f
#define JUMPPOWER	0.3f

class particleSystem;
class enemyManager;

class player : public interfaceCharacter
{
protected:
	PLAYER_KEYSET		_keySet;
	PLAYABLE_CHARACTER	_currentCharacter;
	int					_comboCount;

	interfaceCharacter*	_opponent;

protected:
	float				_aniRate;
	bool				_isFastSkillOn;

	bool				_isJump;

protected:
	enemyManager*		_em;

public:
	player();
	virtual ~player();
	
	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName);

	virtual void release();

	virtual void Update() override;
	virtual void move();
	virtual void jump();
	virtual void attack();

	virtual void useSkill();

	virtual void useSkill1() = 0;
	virtual void useSkill2() = 0;
	virtual void useSkill3() = 0;

	virtual void changeAct(ACT a);

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;

	inline void setIsFast(bool f) { _isFastSkillOn = f; }
	inline bool getIsFast() { return _isFastSkillOn; }

	inline void setEMMemory(enemyManager* em) { _em = em; }
};
