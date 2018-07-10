#include "stdafx.h"
#include "testPlayer.h"
#include "skinnedMesh.h"


testPlayer::testPlayer()
	: _mesh(NULL)
	, _state(STATE_IDLE)
	, _jumpPower(0.0f)
	, _isJump(false)
	, _velocity(0, 0, 0)
	, _dir(0, 0, 1)
	, _dirAngle(0.0f)
	, _speed(0.0f)
{
	D3DXMatrixIdentity(&_worldMatrix);
}


testPlayer::~testPlayer()
{
}

HRESULT testPlayer::init()
{
	_mesh = new skinnedMesh;
	_mesh->init(_T("zealot"), _T(".\\xFile\\zealot"), _T("zealot.X"));
	_mesh->setParentMatrix(&_worldMatrix);

	_mesh->setAnimationSet(playerStateIndex[_state]);

	return S_OK;
}

void testPlayer::release()
{
	if (_mesh)
		_mesh->destroy();
}

void testPlayer::update()
{
	if ((KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')) && _state != STATE_WALK)
	{
		_state = STATE_WALK;
		_mesh->setAnimationIndexBlend(playerStateIndex[_state]);
	}

	if ((KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S')) && _state == STATE_WALK)
	{
		_state = STATE_IDLE;
		_mesh->setAnimationIndexBlend(playerStateIndex[_state]);
	}

	if (_mesh)
		_mesh->update();


	D3DXMATRIX matT, matR, matS;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);

	this->move(matR);
	this->jump();

	D3DXMatrixTranslation(&matT, _controller->getPosition().x, _controller->getPosition().y - 8, _controller->getPosition().z);
	D3DXMatrixScaling(&matS, 15.0f, 15.0f, 15.0f);

	_worldMatrix = matS * matR * matT;
}

void testPlayer::move(D3DXMATRIX& matR)
{
	_dir = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixRotationY(&matR, _dirAngle);

	if (!_isJump)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
			_speed = -SPEED;
		else if (KEYMANAGER->isStayKeyDown('S'))
			_speed = SPEED;
		else
			_speed = 0.0f;
	}

	if (KEYMANAGER->isStayKeyDown('A') && !_isJump)
		_dirAngle -= ANGLESPEED * DEG2RAD;
	else if (KEYMANAGER->isStayKeyDown('D') && !_isJump)
		_dirAngle += ANGLESPEED * DEG2RAD;

	D3DXVec3TransformNormal(&_dir, &_dir, &matR);

	_velocity.x = _dir.x * _speed;
	_velocity.z = _dir.z * _speed;

	_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

	PxControllerState state;
	_controller->getState(state);

	if (state.collisionFlags == PxControllerCollisionFlag::eCOLLISION_UP ||
		state.collisionFlags == PxControllerCollisionFlag::eCOLLISION_DOWN)
	{
		_velocity.y = 0.0f;
		_isJump = false;
	}
}

void testPlayer::jump()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_velocity.y = JUMPPOWER;
		_isJump = true;
	}
	
	if (_isJump)
	{
		_velocity.y -= GRAVITY;
	}
}

void testPlayer::render()
{
	if (_mesh)
		_mesh->render();
}

void testPlayer::createController(PxControllerManager** cm, PxMaterial* m)
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
	//_controller->resize(10.0f);
}
