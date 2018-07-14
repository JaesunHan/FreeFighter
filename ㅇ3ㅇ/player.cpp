#include "stdafx.h"
#include "player.h"
#include "camera.h"

player::player()
	: _keySet(NULL)
	, _currentCharacter(CHAR_NONE)
	, _opponent(NULL)
{
}

player::~player()
{
}

void player::Init(PLAYERS p, PLAYABLE_CHARACTER character, wstring keyPath, wstring keyName)
{
	_keySet = _playerKeySet[p];

	_currentCharacter = character;
	if (character == CHAR_ZEALOT)
		_worldSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	else
		_worldSca = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	_status.speed = 0.5f;

	interfaceCharacter::Init(keyPath, keyName);
}

void player::release()
{
}

void player::Update()
{
	this->move();
	this->CreateWorldMatrix();
	interfaceCharacter::Update();
}

void player::move()
{
	float speed;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
		speed = SPEED;
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
		speed = -SPEED;
	else
		speed = 0.0f;
	
	float angle;
	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
		angle = -ANGLESPEED;
	else if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
		angle = ANGLESPEED;
	else
		angle = 0.0f;

	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, angle);
	D3DXVec3TransformNormal(&_worldDir, &_worldDir, &matR);
	D3DXVec3Normalize(&_worldDir, &_worldDir);

	PxVec3 velocity;
	velocity.x = _worldDir.x * speed;
	velocity.z = _worldDir.z * speed;
	velocity.y = 0.0f;

	_controller->move(velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

	_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
}

void player::Render(float elapsedTime)
{
	interfaceCharacter::Render(elapsedTime);
}
