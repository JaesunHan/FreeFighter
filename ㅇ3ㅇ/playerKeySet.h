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
		'F',			// move left
		'H',			// move right
		'T',			// move front
		'G',			// move back
		'Z',			// attack
		'A',			// skill 0
		'S',			// skill 1
		'D',			// skill 2
	},
	{					// player2
		VK_LEFT,		// move left
		VK_RIGHT,		// move right
		VK_UP,			// move front
		VK_DOWN,		// move back
		'L',		// attack
		'P',		// skill 0
		VK_OEM_4,		// skill 1
		VK_OEM_6,		// skill 2
	}
};

typedef int* PLAYER_KEYSET;

enum PLAYABLE_CHARACTER
{
	CHAR_NONE = -1,
	CHAR_ZEALOT,
	CHAR_REAPER,
	CHAR_WOODGIANT,
	CHAR_FEPEE,
	CHAR_END
};