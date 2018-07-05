#include "stdafx.h"
#include "darkWolf.h"
#include "skinnedMesh.h"

darkWolf::darkWolf()
{
}

darkWolf::~darkWolf()
{
}

void darkWolf::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	enemyController::Init();
	_skinnedMesh->setParentMatrix(&_worldTM);
	_kinds = ENEMY_DARKWOLF;
	_distance = 2.0f;
}

void darkWolf::EnemyAI()
{

}
