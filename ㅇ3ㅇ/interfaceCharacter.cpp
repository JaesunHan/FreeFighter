#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"

interfaceCharacter::interfaceCharacter()
	: _act(ACT_IDLE)
{
}


interfaceCharacter::~interfaceCharacter()
{
	if(_skinnedMesh)
		_skinnedMesh->release();
}

void interfaceCharacter::Init(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath, keyPath.c_str(), keyName.c_str());
}

void interfaceCharacter::Update()
{
	_skinnedMesh->update();
}

void interfaceCharacter::Render()
{
	_skinnedMesh->render();
}

bool interfaceCharacter::isAbsoluteMotion()
{
	if (_act == ACT_ATTACK00 ||
		_act == ACT_ATTACK01 ||
		_act == ACT_ATTACK02 ||
		_act == ACT_ATTACK03 ||
		_act == ACT_ULTIMATE ||
		_act == ACT_COMBO01 ||
		_act == ACT_COMBO02 ||
		_act == ACT_ATTACKED00 ||
		_act == ACT_SKILL01 ||
		_act == ACT_SKILL02 ||
		_act == ACT_SKILL03 ||
		_act == ACT_DEATH) return true;
		
	return false;
}

void interfaceCharacter::AnimationSetting()
{
}
