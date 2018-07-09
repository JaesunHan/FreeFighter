#pragma once
#include "character.h"

#define GRAVITY		0.01f
#define JUMPPOWER	0.5f
#define SPEED		1.0f
#define ANGLESPEED	5.0f

enum TEST_STATE
{
	STATE_NONE = -1,
	STATE_IDLE,
	STATE_WALK,
	STATE_ATTACK1,
	STATE_ATTACK2,
	STATE_ATTACK3,
	STATE_END
};

static UINT playerStateIndex[STATE_END] = { 4, 3, 2, 1, 0 };

class skinnedMesh;

class testPlayer
{
private:
	skinnedMesh*	_mesh;
	TEST_STATE		_state;
	PxController*	_controller;
	D3DXMATRIX		_worldMatrix;

	float			_jumpPower;
	bool			_isJump;

	PxVec3			_velocity;
	D3DXVECTOR3		_dir;
	float			_dirAngle;
	float			_speed;

public:
	testPlayer();
	virtual ~testPlayer();

	HRESULT init();
	void release();
	void update();
	void move(D3DXMATRIX& matR);
	void jump();

	void render();

	void createController(PxControllerManager** cm, PxMaterial* m);
};

