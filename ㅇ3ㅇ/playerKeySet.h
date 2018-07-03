#pragma once
#include <Windows.h>

enum PLAYERS
{
	PLAYER_NONE = -1,
	PLAYER_1P,
	PLAYER_2P,
	PLAYER_END
};

enum PLAYER_KEY
{
	KEY_NONE = -1,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_ATTACK,
	KEY_SKILL_0,
	KEY_SKILL_1,
	KEY_SKILL_2,
	KEY_END
};

static int _playerKeySet[PLAYER_END][KEY_END] = 
{
	{					// player1
		VK_LEFT,		// move left
		VK_RIGHT,		// move right
		VK_UP,			// move front
		VK_DOWN,		// move back
		VK_NUMPAD0,		// attack
		VK_NUMPAD1,		// skill 0
		VK_NUMPAD2,		// skill 1
		VK_NUMPAD3,		// skill 2
	},
	{					// player2
		'A',			// move left
		'D',			// move right
		'W',			// move front
		'S',			// move back
		VK_SPACE,		// attack
		'V',			// skill 0
		'B',			// skill 1
		'N',			// skill 2
	}
};