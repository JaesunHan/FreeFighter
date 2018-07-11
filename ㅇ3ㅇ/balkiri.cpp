#include "stdafx.h"
#include "balkiri.h"
#include "skinnedMesh.h"

balkiri::balkiri()
{
	_AniIndex[ACT_IDLE] = 11;
	_AniIndex[ACT_RUN_FRONT] = 2;
	_AniIndex[ACT_ATTACK00] = 3;
	_AniIndex[ACT_ATTACK01] = 7;
	_AniIndex[ACT_ULTIMATE] = 8;

}

balkiri::~balkiri()
{
}

void balkiri::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	//	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_BALKIRI;

	//지우지말기 ★★★★★★★

	_skinnedMesh->setAnimationIndexBlend(_AniIndex[_currentAct]);

	//_skinnedMesh->setAnimationIndexBlend(ACT_IDLE);

	_keySet = _playerKeySet[p];



	//충돌원???
	_sphere.radius = 0.05f;

	D3DXCreateSphere(D3DDEVICE, _sphere.radius, 4, 4, &_sphere.sphere, 0);


}


void balkiri::animation()
{
	//	_skinnedMesh->setAnimationIndexBlend(_AniIndex[_nextAct]);

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

	//	_skinnedMesh->setAnimationIndexBlend(_AniIndex[_nextAct]);

	//	AnimationSetting();

}
