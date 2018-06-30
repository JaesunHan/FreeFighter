#pragma once

#include <fstream>
#include <vector>
using namespace std;

class character;

class heightMap
{
private:
	fstream		_fin;
	int			_numOfGrid;
	LPD3DXMESH	_map;

	D3DXMATRIX	_worldMatrix;

	character*	_player;

public:
	heightMap();
	~heightMap();

	void init();
	void release();
	void update();
	void render();

#ifdef UNICODE
	void LoadFile(const WCHAR* fileName);
#else
	void LoadFile(const char* fileName);
#endif

	void getPlayerIndex(D3DXVECTOR3& pos);

	inline void setPlayerMemoryAddress(character* p) { _player = p; }
};

