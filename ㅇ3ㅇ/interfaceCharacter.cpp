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
	_skinnedMesh->init(keyPath, keyPath.c_str(), keyName.c_str());
}

void interfaceCharacter::Update()
{

	switch (_act)
	{
	case ACT_NONE:
		break;
	case ACT_IDLE:
		break;
	case ACT_WARKING_FRONT:
		break;
	case ACT_WARKING_BACK:
		break;
	case ACT_RUN_FRONT:
		_skinnedMesh->setAnimationSet(1);
		break;
	case ACT_RUN_BACK:
		break;
	case ACT_ATTACK00:
		break;
	case ACT_ATTACK01:
		break;
	case ACT_ATTACK02:
		break;
	case ACT_ATTACK03:
		break;
	case ACT_ULTIMATE:
		break;
	case ACT_COMBO01:
		break;
	case ACT_COMBO02:
		break;
	case ACT_ATTACKED00:
		break;
	case ACT_SKILL01:
		break;
	case ACT_SKILL02:
		break;
	case ACT_SKILL03:
		break;
	case ACT_DEATH:
		break;
	case ACT_END:
		break;
	default:
		break;
	}


	_skinnedMesh->update();

	
}

void interfaceCharacter::Render()
{
	_skinnedMesh->render();
}
