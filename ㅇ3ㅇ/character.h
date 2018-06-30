#pragma once

#define GRAVITY		0.05f
#define SCALE		1.0f
#define JUMPPOWER	0.5f
#define SPEED		0.05f
#define ANGLESPEED	5.0f

class gameObject;
class heightMap;

class character
{
protected:
	D3DXMATRIX		_worldMatrix;
	D3DXVECTOR3		_position;

	float			_angleX;
	float			_angleY;
	float			_angleZ;

	D3DXVECTOR3		_dir;
	float			_speed;
	float			_dirAngle;

	float			_jumpPower;
	bool			_isJump;

	bool			_isMove;
	D3DXVECTOR3		_to;

	vector<gameObject>*		_floor;
	vector<gameObject>*		_wall;

	heightMap*				_hMap;

public:
	character();
	~character();

	void update();
	void render();
	void jump();
	void collisionByWall(D3DXVECTOR3 dir);
	void collisionByFloor();

	void moveTo(D3DXVECTOR3 to);

	inline D3DXVECTOR3 getPosition() { return _position; }
	inline void setFloor(vector<gameObject>* f) { _floor = f; }
	inline void setWall(vector<gameObject>* f) { _wall = f; }

	inline void setHeightMapMemory(heightMap* h) { _hMap = h; }
};

