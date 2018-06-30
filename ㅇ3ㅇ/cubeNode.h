#pragma once
#include "cube.h"

#define DISTANCE(distance) (distance * 4)

enum GO_DIRECTION
{
	GO_NONE = -1,
	GO_FRONT,
	GO_BACK,
	GO_LEFT,
	GO_RIGHT,
	GO_END
};

class cubeNode : public cube
{
protected:
	vector<cubeNode*>	_child;
	D3DXMATRIX*			_parent;

#ifdef UNICODE
	wstring				_textureName;
#else
	string				_textureName;
#endif

public:
	cubeNode();
	~cubeNode();

	virtual void init();
	virtual void init(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz);
	virtual void release();
	virtual void update();
	virtual void render();

	void addChild(cubeNode* child);

#ifdef UNICODE
	inline void setTextureName(wstring key) { _textureName = key; }
#else
	inline void setTextureName(string key) { _textureName = key; }
#endif
	inline void setParentMatrix(D3DXMATRIX* p) { _parent = p; }
};

