#pragma once

class cube;

class testCube
{
private:
	cube* _cube;

private:
	D3DXVECTOR3 _vPos;
	D3DXVECTOR3 _vDir;
	float		_rotY;
	D3DXMATRIX	_worldTM;

public:
	testCube();
	~testCube();

	void Setup();
	void Update();
	void Render();

	D3DXVECTOR3 GetPos() { return _vPos; }

};

