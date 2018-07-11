#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"

interfaceCharacter::interfaceCharacter()
	: _act(ACT_IDLE)
	, _skinnedMesh(NULL)
	, _controller(NULL)
	, _worldSca(1.0f, 1.0f, 1.0f)
	, _worldRot(0.0f, 0.0f, 0.0f)
	, _worldPos(0.0f, 0.0f, 0.0f)
	, _worldDir(0.0f, 0.0f, 1.0f)
	, _targetPos(NULL)
	, _velocity(0, 0, 0)
{
	D3DXMatrixIdentity(&_worldTM);
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

void interfaceCharacter::createContoller(PxControllerManager** cm, PxMaterial* m)
{
	PxCapsuleControllerDesc desc;
	desc.position = PxExtendedVec3(0, 0, 0);
	desc.radius = 2.0f;
	desc.height = 10.0f;
	desc.stepOffset = 10.0f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
}
