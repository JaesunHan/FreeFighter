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

	int					_currentFrameX;
	int					_currentFrameY;

public:
	uiObject();
	virtual ~uiObject();

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void addChild(uiObject* c);

	inline void setParnet(uiObject* p) { _parent = p; }
	inline uiObject* getParent() { return _parent; }

	inline void setPosition(D3DXVECTOR3 pos) { _position = pos; }
	inline D3DXVECTOR3 getPosition() { return _position; }

	inline void setDest(float dx, float dy) { _position.x = dx - _size.width / 2; _position.y = dy - _size.height / 2; }

	inline void setCurrentFrameX(int fx) { _currentFrameX = fx; }
	inline void setCurrentFrameY(int fy) { _currentFrameY = fy; }

	inline int getCurrentFrameX() { return _currentFrameX; }
	inline int getCurrentFrameY() { return _currentFrameY; }
};

