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
	_skinnedMesh->setParentMatrix(&_worldTM);

	_kinds = ENEMY_DARKWOLF;
	_distance = 1.0f;

	_sphere.radius = 0.5f;
	//_sphere.center = D3DXVECTOR3(0, 0.5f, 0.5f);

	D3DXCreateSphere(D3DDEVICE, _sphere.radius, 8, 8, &_sphere.sphere, 0);
}

void darkWolf::EnemyAI()
{

}

void darkWolf::AnimationSetting()
{
	_skinnedMesh->setAnimationIndexBlend(AniIndex[_act]);
}
