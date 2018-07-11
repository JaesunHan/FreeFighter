#include "stdafx.h"
#include "aranzebia.h"
#include "skinnedMesh.h"


aranzebia::aranzebia()
{
}

aranzebia::~aranzebia()
{
}

void aranzebia::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	//	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_ARANZEBIA;

	//���������� �ڡڡڡڡڡڡ�

	_skinnedMesh->setAnimationIndexBlend(_AniIndex[_currentAct]);

	//_skinnedMesh->setAnimationIndexBlend(ACT_IDLE);

	_keySet = _playerKeySet[p];



	//�浹��???
	_sphere.radius = 0.05f;

	D3DXCreateSphere(D3DDEVICE, _sphere.radius, 4, 4, &_sphere.sphere, 0);

}
void aranzebia::animation()
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