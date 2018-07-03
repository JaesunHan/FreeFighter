#include "stdafx.h"
#include "playerSelector.h"
#include "uiImageView.h"


playerSelector::playerSelector()
	: _keySet(NULL)
	, _edge(NULL)
	, _cantSelectCharacter(NULL)
	, _scale(1.0f)
	, _angle(0.0f)
	, _position(0.0f, 0.0f, 0.0f)
{
	D3DXMatrixIdentity(&_characterWolrd);
}


playerSelector::~playerSelector()
{
}

HRESULT playerSelector::init(PLAYERS p)
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	_players = p;
	_keySet = _playerKeySet[p];

	if (p == PLAYER_1P)
	{
		_currentCharacter = CHAR_ZEALOT;
		_scale = 1.0f;
		_angle = -60.0f * DEG2RAD;
		_position.x = -3.0f;

		_edge = new uiImageView;
		_edge->init(_T("edge_1p"), _T(".\\texture\\edge_1p.png"), vp.Width / 2 - 165 + 110 * _currentCharacter, vp.Height / 2 + 100);

		_currentIdxX = 0;
		_currentIdxY = 0;
	}
	else if (p == PLAYER_2P)
	{
		_currentCharacter = CHAR_KNIGHT;
		_scale = 0.006f;
		_angle = 60.0f * DEG2RAD;
		_position.x = 3.0f;

		_edge = new uiImageView;
		_edge->init(_T("edge_2p"), _T(".\\texture\\edge_2p.png"), vp.Width / 2 - 165 + 110 * _currentCharacter, vp.Height / 2 + 100);

		_currentIdxX = 3;
		_currentIdxY = 0;
	}

	return S_OK;
}

void playerSelector::release()
{
	if (_edge)
		SAFE_OBJRELEASE(_edge);
}

void playerSelector::update()
{
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_LEFT]))
	{
		_currentIdxX--;
		if (_currentIdxX < 0)
			_currentIdxX = 3;

		if (_cantSelectCharacter)
		{
			if (_currentIdxX + _currentIdxY * 4 == (*_cantSelectCharacter))
				_currentIdxX--;

			if (_currentIdxX < 0)
				_currentIdxX = 3;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_RIGHT]))
	{
		_currentIdxX++;
		if (_currentIdxX > 3)
			_currentIdxX = 0;

		if (_cantSelectCharacter)
		{
			if (_currentIdxX + _currentIdxY * 4 == (*_cantSelectCharacter))
				_currentIdxX++;

			if (_currentIdxX > 3)
				_currentIdxX = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_UP]))
	{
		_currentIdxY--;
		if (_currentIdxY < 0)
			_currentIdxY = 0;

		if (_cantSelectCharacter)
		{
			if (_currentIdxX + _currentIdxY * 4 == (*_cantSelectCharacter))
				_currentIdxY--;

			if (_currentIdxY < 0)
				_currentIdxY = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_DOWN]))
	{
		_currentIdxY++;
		if (_currentIdxY > 0)
			_currentIdxY = 0;

		if (_cantSelectCharacter)
		{
			if (_currentIdxX + _currentIdxY * 4 == (*_cantSelectCharacter))
				_currentIdxY++;

			if (_currentIdxY > 0)
				_currentIdxY = 0;
		}
	}

	_currentCharacter = (PLAYABLE_CHARACTER)(_currentIdxX + _currentIdxY * 4);

	if (_currentCharacter == CHAR_ZEALOT)
		_scale = 1.0f;
	else
		_scale = 0.006f;

	D3DXMATRIX matS, matR, matT;
	D3DXMatrixScaling(&matS, _scale, _scale, _scale);
	D3DXMatrixRotationY(&matR, _angle);
	D3DXMatrixTranslation(&matT, _position.x, _position.y, _position.z);

	_characterWolrd = matS * matR * matT;

	if (_edge)
	{
		D3DVIEWPORT9 vp;
		D3DDEVICE->GetViewport(&vp);

		_edge->setDest(vp.Width / 2 - 165 + 110 * _currentCharacter, vp.Height / 2 + 100);
		_edge->update();
	}
}

void playerSelector::render()
{
	if (_edge)
		_edge->render();
}
