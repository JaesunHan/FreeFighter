#pragma once

#include <vector>
using namespace std;

typedef struct tagUISize
{
	float width;
	float height;

	tagUISize() : width(0), height(0) {}
	tagUISize(float w, float h) : width(w), height(h) {}
} UISIZE;

class uiObject
{
protected:
	D3DXMATRIX			_worldMatrix;
	D3DXVECTOR3			_position;
	uiObject*			_parent;
	vector<uiObject*>	_vChild;
	UISIZE				_size;

public:
	uiObject();
	virtual ~uiObject();

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void addChild(uiObject* c);

	inline void setParnet(uiObject* p) { _parent = p; }
	inline uiObject* getParent() { return _parent; }
};

