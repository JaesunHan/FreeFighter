#pragma once
#include "character.h"

enum PARTS
{
	PARTS_NONE = -1,
	PARTS_LEFT,
	PARTS_RIGHT,
	PARTS_END
};

class cubeNode;
class cubeArm;
class cubeBody;
class cubeHead;
class cubeLeg;

enum GO_DIRECTION;

class cubeMan : public character
{
private:
	cubeNode* _root;
	cubeHead* _head;
	cubeNode* _body;
	cubeLeg* _leg[PARTS_END];
	cubeArm* _arms[PARTS_END];

	int				_currentType;

	D3DLIGHT9		_light;
	int				_lightChannel;

	GO_DIRECTION	_go;

public:
	cubeMan();
	~cubeMan();

	void init();
	void release();
	void update();
	void render();

	D3DXVECTOR3 getPos();
	int getIdx();
	int getCurrentType();
};

