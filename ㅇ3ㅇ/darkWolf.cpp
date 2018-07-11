#include "stdafx.h"
#include "darkWolf.h"
#include "skinnedMesh.h"

darkWolf::darkWolf()
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_ATTACK00] = 5;
	_AniIndex[ACT_ATTACK01] = 6;
	_AniIndex[ACT_ATTACKED00] = 4;
	_AniIndex[ACT_DEATH] = 3;
}

darkWolf::~darkWolf()
{
}

void darkWolf::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);

	_kinds = ENEMY_DARKWOLF;
	_distance = 2.0f;

	_sphere.radius = 0.5f;
	//_sphere.center = D3DXVECTOR3(0, 0.5f, 0.5f);

	D3DXCreateSphere(D3DDEVICE, _sphere.radius, 8, 8, &_sphere.sphere, 0);
}

void darkWolf::EnemyAI()
{

}

