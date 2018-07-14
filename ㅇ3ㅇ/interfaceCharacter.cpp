#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"

interfaceCharacter::interfaceCharacter()
	: _currentAct(ACT_IDLE)
	, _nextAct(ACT_IDLE)
	, _skinnedMesh(NULL)
	, _controller(NULL)
	, _worldSca(1.0f, 1.0f, 1.0f)
	, _worldPos(0.0f, 0.0f, 0.0f)
	, _worldDir(0.0f, 0.0f, 1.0f)
	, _targetPos(NULL)
	, _velocity(0, 0, 0)
	, _isDead(false)
{
	D3DXMatrixIdentity(&_worldTM);

	for (int i = 0; i < ACT_END; i++)
	{
		_AniIndex[i] = -1;
	}

	ZeroMemory(&_status, sizeof(tagCharStatus));
}


interfaceCharacter::~interfaceCharacter()
{
	if(_skinnedMesh)
		_skinnedMesh->destroy();
}

void interfaceCharacter::Init(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath, keyPath.c_str(), keyName.c_str());
	_skinnedMesh->setParentMatrix(&_worldTM);
}

void interfaceCharacter::Update()
{
	_skinnedMesh->update();
}

void interfaceCharacter::Render(float elapsedTime)
{
	_skinnedMesh->render(elapsedTime);
}

void interfaceCharacter::HitDamage(float damage)
{
	_status.currentHp -= damage;

	if (_status.currentHp > 0) _nextAct = ACT_ATTACKED00;
	else
	{
		_isDead = true;
		_nextAct = ACT_DEATH;
	}
}

void interfaceCharacter::AttackMotionEnd(interfaceCharacter* IChar, float damage, float distance, float attackArea)
{
	if ((_currentAct == ACT_ATTACK00 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_ATTACK01 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_ATTACK02 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_ATTACK03 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_ULTIMATE && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_COMBO01 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_COMBO02 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_SKILL01 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_SKILL02 && _skinnedMesh->IsAnimationEnd()) ||
		(_currentAct == ACT_SKILL03 && _skinnedMesh->IsAnimationEnd()))
	{
		if ( (AttackRange(distance).x - attackArea < IChar->GetPosition().x && AttackRange(distance).x + attackArea > IChar->GetPosition().x) &&
			(AttackRange(distance).y - attackArea < IChar->GetPosition().y && AttackRange(distance).y + attackArea > IChar->GetPosition().y) &&
			(AttackRange(distance).z - attackArea < IChar->GetPosition().z && AttackRange(distance).z + attackArea > IChar->GetPosition().z))
		{
			IChar->HitDamage(damage);
		}
	}

}

D3DXVECTOR3 interfaceCharacter::AttackRange(float Distance)
{
	return _worldPos + _worldDir * Distance;
}

void interfaceCharacter::CreateWorldMatrix()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	// 스케일링
	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);

	// 로테이션(방향은 Y만 돌려도 무방)
	float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) - D3DX_PI / 2;
	D3DXMatrixRotationY(&matR, angle);

	// 트렌스레이션
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	// 월드 매트릭스 변화
	_worldTM = matS * matR * matT;
}

bool interfaceCharacter::isAbsoluteMotion()
{
	if (_currentAct == ACT_ATTACK00 ||
		_currentAct == ACT_ATTACK01 ||
		_currentAct == ACT_ATTACK02 ||
		_currentAct == ACT_ATTACK03 ||
		_currentAct == ACT_ULTIMATE ||
		_currentAct == ACT_COMBO01 ||
		_currentAct == ACT_COMBO02 ||
		_currentAct == ACT_ATTACKED00 ||
		_currentAct == ACT_SKILL01 ||
		_currentAct == ACT_SKILL02 ||
		_currentAct == ACT_SKILL03 ||
		_currentAct == ACT_DEATH) return true;
		
	return false;
}

void interfaceCharacter::AnimationSetting()
{
	if (_currentAct != _nextAct)
	{
		_currentAct = _nextAct;
		_skinnedMesh->setAnimationIndexBlend(_AniIndex[_currentAct]);
	}
}

void interfaceCharacter::createContoller(PxControllerManager** cm, PxMaterial* m)
{
	PxCapsuleControllerDesc desc;
	desc.position = PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z);
	desc.radius = 2.0f;
	desc.height = 10.0f;
	desc.stepOffset = 0.0f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->setUserData(this);
}

void interfaceCharacter::createContoller(PxControllerManager ** cm, PxMaterial * m, float radius, float height)
{
	PxCapsuleControllerDesc desc;
	desc.position = PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z);
	desc.radius = radius;
	desc.height = height;
	desc.stepOffset = 0.0f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->setUserData(this);
}
