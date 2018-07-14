#pragma once

#include "playerKeySet.h"

class uiImageView;

class playerSelector
{
private:
	PLAYERS				_players;
	PLAYER_KEYSET		_keySet;

	PLAYABLE_CHARACTER	_currentCharacter;
	PLAYABLE_CHARACTER*	_cantSelectCharacter;

	float				_scale;
	float				_angle;
	D3DXVECTOR3			_position;
	D3DXMATRIX			_characterWolrd;

	uiImageView*		_edge;

	int					_currentIdxX;
	int					_currentIdxY;

public:
	playerSelector();
	~playerSelector();

	HRESULT init(PLAYERS p);
	void release();
	void update();
	void render();

	bool isSelect();

	inline PLAYABLE_CHARACTER getCurrentSelectedCharacter() { return _currentCharacter; }

	inline void setCantSelectCharacter(playerSelector* c) { _cantSelectCharacter = &c->_currentCharacter; }

	inline D3DXMATRIX* getWorldAdress() { return &_characterWolrd; }
};
