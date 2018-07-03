#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"

interfaceCharacter::interfaceCharacter()
	: _act(ACT_IDLE)
{
}


interfaceCharacter::~interfaceCharacter()
{
	_skinnedMesh->release();
}

void interfaceCharacter::Init(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath.c_str(), keyName.c_str());
}

void interfaceCharacter::Update()
{
	switch (_act)
	{
	case ACT_NONE:
		break;
	case ACT_IDLE:
		_skinnedMesh->setAnimationSet(2);
		break;
	case ACT_RUN:
		_skinnedMesh->setAnimationSet(1);
		break;
	case ACT_ATTACK:
		_skinnedMesh->setAnimationSet(6);
		break;
	case ACT_COMBO01:
		break;
	case ACT_COMBO02:
		break;
	case ACT_SKILL01:
		break;
	case ACT_SKILL02:
		break;
	case ACT_SKILL03:
		break;
	}

	_skinnedMesh->update();

	
}

void interfaceCharacter::Render()
{
	_skinnedMesh->render();
}
