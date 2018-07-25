#include "stdafx.h"
#include "mainSceneCharacter.h"
#include "skinnedMesh.h"


mainSceneCharacter::mainSceneCharacter()
	: _worldPos(0, 0, 0)
	, _worldDir(0, 0, 1)
	, _controller(NULL)
	, _velocity(0, 0, 0)
	, _worldSca(1.0f, 1.0f, 1.0f)
	, _currentAni(ANI_NONE)
{
	D3DXMatrixIdentity(&_worldTM);
}


mainSceneCharacter::~mainSceneCharacter()
{
}

HRESULT mainSceneCharacter::init(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath, keyPath.c_str(), keyName.c_str());
	_skinnedMesh->setParentMatrix(&_worldTM);

	if (keyName == _T("zealot.X"))
	{
		_worldSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		_aniIndex[ANI_IDLE] = 4;
		_aniIndex[ANI_MOVE] = 3;
	}
	else
	{
		_worldSca = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

		_aniIndex[ANI_IDLE] = 2;
		_aniIndex[ANI_MOVE] = 1;
	}

	_currentAni = ANI_NONE;
	this->changeAnimation(_currentAni);

	return S_OK;
}

void mainSceneCharacter::release()
{
	if (_skinnedMesh)
	{
		_skinnedMesh->destroy();
		SAFE_DELETE(_skinnedMesh);
	}
}

void mainSceneCharacter::update()
{
	this->move();
	this->CreateWorldMatrix();

	_skinnedMesh->update();
}

void mainSceneCharacter::move()
{
	if (_currentAni != ANI_MOVE) return;

	D3DXVec3Normalize(&_worldDir, &_worldDir);

	//방향 + 크기 == 속도 
	_velocity.x = _worldDir.x * 0.1f;
	_velocity.z = _worldDir.z * 0.1f;

	if (_controller)
	{
		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());
		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
	}
}

void mainSceneCharacter::CreateWorldMatrix(float correctionAngle)
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	// 스케일링
	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);

	// 로테이션(방향은 Y만 돌려도 무방)
	float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) + correctionAngle;
	D3DXMatrixRotationY(&matR, angle);

	// 트렌스레이션
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	// 월드 매트릭스 변화
	_worldTM = matS * matR * matT;
}

void mainSceneCharacter::render(float elapsedTime)
{
	_skinnedMesh->render(elapsedTime);
}

void mainSceneCharacter::createContoller(PxControllerManager ** cm, PxMaterial * m)
{
	PxCapsuleControllerDesc desc;
	desc.position = PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z);
	desc.radius = 2.0f;
	desc.height = 1.0f;
	desc.stepOffset = 0.0001f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->setUserData(this);
}

void mainSceneCharacter::changeAnimation(MAINCHARACTER_ANI ani)
{
	if (_currentAni == ani) return;

	_currentAni = ani;
	_skinnedMesh->setAnimationIndexBlend(_aniIndex[ani]);
}

bool mainSceneCharacter::isCrush()
{
	PxControllerState state;
	_controller->getState(state);
	if (state.collisionFlags == PxControllerCollisionFlag::eCOLLISION_SIDES)
		return true;

	return false;
}

void mainSceneCharacter::setPosition(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	_worldPos = pos;
	_worldDir = dir;

	_controller->setFootPosition(PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z));
}
