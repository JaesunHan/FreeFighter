#include "stdafx.h"
#include "state.h"
#include "enemy.h"

void appear::Update()
{
	if (_enemy)
		_enemy->Appear();
}

// ===========================================================================================================================

void idle::Update()
{
	if (_enemy)
		_enemy->Idle();
}

// ===========================================================================================================================

void run::Update()
{
	if (_enemy)
		_enemy->Moving();
}

// 

void rndRun::Update()
{
	if (_enemy)
		_enemy->RNDMoving();
}

// ===========================================================================================================================

void goHome::Update()
{
	if (_enemy)	
		_enemy->GoHome();
}

// ===========================================================================================================================

void damage01::Update()
{
	if (_enemy)
		_enemy->Damage();
}

// ===========================================================================================================================

void recovery::Update()
{
	if (_enemy)
		_enemy->Recovery();
}

// ===========================================================================================================================

void death::Update()
{
	if (_enemy)
		_enemy->Death();
}

// ===========================================================================================================================

void attack01::Update()
{
	if (_enemy)
		_enemy->Attack01();
}
void attack02::Update()
{
	if (_enemy)
		_enemy->Attack02();
}
void attack03::Update()
{
	if (_enemy)
		_enemy->Attack03();
}

// ===========================================================================================================================
