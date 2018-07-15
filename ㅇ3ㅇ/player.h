#pragma once

#include "interfaceCharacter.h"
#include "playerKeySet.h"

#define SPEED		0.1f
#define ANGLESPEED	(3.0f * DEG2RAD)

class player : public interfaceCharacter
{
private:
	PLAYER_KEYSET		_keySet;
	PLAYABLE_CHARACTER	_currentCharacter;
	int					_comboCount;

	interfaceCharacter*	_opponent;

public:
	player();
	virtual ~player();
	
	virtual void Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName);

	virtual void release();

	virtual void Update() override;
	virtual void move();
	virtual void attack();

	virtual void changeAct(ACT a);

	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;
};
