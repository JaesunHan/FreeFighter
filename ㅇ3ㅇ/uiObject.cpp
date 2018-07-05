#include "stdafx.h"
#include "uiObject.h"


uiObject::uiObject()
	: _position(0.0f, 0.0f, 0.0f)
	, _parent(NULL)
	, _size(0, 0)
	, _currentFrameX(0)
	, _currentFrameY(0)
{
}


uiObject::~uiObject()
{
}

void uiObject::release()
{
	for (int i = 0; i < _vChild.size(); ++i)
		SAFE_OBJRELEASE(_vChild[i]);

	_vChild.clear();
}

void uiObject::update()
{
	D3DXMatrixIdentity(&_worldMatrix);
	_worldMatrix._41 = _position.x;
	_worldMatrix._42 = _position.y;
	_worldMatrix._43 = _position.z;

	if (_parent)
	{
		_worldMatrix._41 += _parent->_worldMatrix._41;
		_worldMatrix._42 += _parent->_worldMatrix._42;
		_worldMatrix._43 += _parent->_worldMatrix._43;
	}

	for (int i = 0; i < _vChild.size(); ++i)
		_vChild[i]->update();
}

void uiObject::render()
{
	for (int i = 0; i < _vChild.size(); ++i)
		_vChild[i]->render();
}

void uiObject::addChild(uiObject * c)
{
	c->setParnet(this);
	_vChild.push_back(c);
}
