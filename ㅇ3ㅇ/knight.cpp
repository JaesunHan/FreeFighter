#include "stdafx.h"
#include "knight.h"
#include "skinnedMesh.h"



knight::knight()
{
	_AniIndex[ACT_WARKING_FRONT] = 8;
	_AniIndex[ACT_WARKING_BACK] = 7;
	_AniIndex[ACT_RUN_FRONT] = 6;
	_AniIndex[ACT_RUN_BACK] = 5;
	_AniIndex[ACT_ATTACK00] = 4;
	_AniIndex[ACT_ATTACK01] = 3;
	_AniIndex[ACT_ATTACK02] = 2;
	_AniIndex[ACT_IDLE] = 1;
	_AniIndex[ACT_DEATH] = 0;
}


knight::~knight()
{
}

void knight::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	//	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_KNIGHT;

	//지우지말기 ★★★★★★★

	_skinnedMesh->setAnimationIndexBlend(_AniIndex[_currentAct]);

	//_skinnedMesh->setAnimationIndexBlend(ACT_IDLE);

	_keySet = _playerKeySet[p];



	//충돌원???
	_sphere.radius = 0.05f;

	D3DXCreateSphere(D3DDEVICE, _sphere.radius, 4, 4, &_sphere.sphere, 0);


}
void knight::animation()
{
	if (isAbsoluteMotion())
	{
		if (_skinnedMesh->IsAnimationEnd())
		{
			_nextAct = ACT_IDLE;
			AnimationSetting();

		}
	}




	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
	{
		_nextAct = ACT_WARKING_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
	{
		_nextAct = ACT_WARKING_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
	{
		_nextAct = ACT_RUN_FRONT;
		AnimationSetting();

	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
	{
		_nextAct = ACT_RUN_BACK;
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



	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
	{
		_nextAct = ACT_ATTACK00;
		AnimationSetting();

	}

	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_SKILL_0]))
	{
		_nextAct = ACT_ATTACK01;
		AnimationSetting();

	}

	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_SKILL_1]))
	{
		_nextAct = ACT_ATTACK02;
		AnimationSetting();

	}
}
