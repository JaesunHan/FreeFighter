#include "stdafx.h"
#include "lucius.h"
#include "skinnedMesh.h"



lucius::lucius()
{
}


lucius::~lucius()
{
}

void lucius::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	//	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_LUCIUS;

	//지우지말기 ★★★★★★★

	_skinnedMesh->setAnimationIndexBlend(_AniIndex[_currentAct]);

	//_skinnedMesh->setAnimationIndexBlend(ACT_IDLE);

	_keySet = _playerKeySet[p];



	//충돌원???
	_sphere.radius = 0.05f;

	D3DXCreateSphere(D3DDEVICE, _sphere.radius, 4, 4, &_sphere.sphere, 0);


}

void lucius::animation()
{
	if (isAbsoluteMotion())
	{
		if (_skinnedMesh->IsAnimationEnd())
		{
			_nextAct = ACT_IDLE;
			AnimationSetting();

		}
	}


	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
	{
		_nextAct = ACT_ATTACK00;
		AnimationSetting();

	}

	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_SKILL_0]))
	{
		_nextAct = ACT_ULTIMATE;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
	{
		_nextAct = ACT_RUN_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
	{
		_nextAct = ACT_RUN_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
	{
		_nextAct = ACT_RUN_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
	{
		_nextAct = ACT_RUN_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isOnceKeyUp(_keySet[KEY_LEFT]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_RIGHT]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_UP]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_DOWN]))
	{
		_nextAct = ACT_IDLE;
		AnimationSetting();

	}
}
