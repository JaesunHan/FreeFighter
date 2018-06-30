#pragma once

#include "character.h"

enum PLAYER_STATE
{
	PLAYER_NONE = -1,
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_ATTACK1,
	PLAYER_ATTACK2,
	PLAYER_ATTACK3,
	PLAYER_END
};

static UINT playerStateIndex[PLAYER_END] = { 4, 3, 2, 1, 0 };

class skinnedMesh;

class player : public character
{
private:
	skinnedMesh*		_mesh;

	PLAYER_STATE		_state;

public:
	player();
	~player();

	void init();
	void release();
	void update();
	void render();
};

