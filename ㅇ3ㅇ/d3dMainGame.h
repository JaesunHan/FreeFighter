#pragma once

class camera;
class cube;
class gameObject;
class objectNode;
class rabbitWomen;
class grid;
class heightMap;
class skinnedMesh;
class player;

class d3dMainGame
{
private:
	camera*	_camera;
	grid*	_grid;

	bool			_isCameraTrace;

	D3DLIGHT9		_light;

	rabbitWomen*	_rw;
	LPD3DXMESH		_map;
	vector<tagObjectMtlData> _mtlTexData;
	vector<gameObject>	_surface;

	LPD3DXFONT	_font;

	tagSphere*		_sphere[3];
	vector<wstring> _materialKey;
	vector<int>		_currentMaterial;

	heightMap*		_hMap;

	vector<tagObjectMtlData>	_zealotMtls;
	LPD3DXMESH					_zealot;

	skinnedMesh*				_z;
	player*						_player;

public:
	d3dMainGame();
	~d3dMainGame();

	void init();
	void release();
	void update();
	void render();

	void cameraZoom(float zoom);
};

