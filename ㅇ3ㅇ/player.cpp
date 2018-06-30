#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"


player::player()
	: _state(PLAYER_IDLE)
	, _mesh(NULL)
{
}


player::~player()
{
}

void player::init()
{
	_mesh = new skinnedMesh;
	_mesh->init(".\\Zeolot", "zealot.X");
	_mesh->setParentMatrix(&_worldMatrix);
	
	_state = PLAYER_IDLE;
	_mesh->setAnimationSet(playerStateIndex[_state]);
}

void player::release()
{
	if (_mesh)
	{
		_mesh->release();
		SAFE_DELETE(_mesh);
	}
}

void player::update()
{
	if ((KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')) && _state != PLAYER_WALK)
	{
		_state = PLAYER_WALK;
		_mesh->setAnimationIndexBlend(playerStateIndex[_state]);
	}

	if ((KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S')) && _state == PLAYER_WALK)
	{
		_state = PLAYER_IDLE;
		_mesh->setAnimationIndexBlend(playerStateIndex[_state]);
	}

	character::update();

	_mesh->update();
}

void player::render()
{
	if (_mesh)
		_mesh->render();
}
