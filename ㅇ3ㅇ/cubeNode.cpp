#include "stdafx.h"
#include "cubeNode.h"


cubeNode::cubeNode()
	: _parent(NULL)
	, _textureName("")
{
}


cubeNode::~cubeNode()
{
	for (int i = 0; i < _child.size(); ++i)
	{
		_child[i]->release();
		SAFE_DELETE(_child[i]);
	}
	_child.clear();
}

void cubeNode::init()
{
	cube::init();
}

void cubeNode::init(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz)
{
	cube::init();

	this->transFormLocal(tx, ty, tz, angleX, angleY, angleZ, sx, sy, sz);
}

void cubeNode::release()
{
	for (int i = 0; i < _child.size(); ++i)
	{
		_child[i]->release();
		SAFE_DELETE(_child[i]);
	}
	_child.clear();

	cube::release();
}

void cubeNode::update()
{
	cube::update();

	if (_parent)
		_worldMatrix *= (*_parent);

	for (int i = 0; i < _child.size(); ++i)
		_child[i]->update();
}

void cubeNode::render()
{
	if (_textureName != "")
		D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_textureName));
	cube::render();

	for (int i = 0; i < _child.size(); ++i)
		_child[i]->render();
}

void cubeNode::addChild(cubeNode* child)
{
	child->_parent = &this->_worldMatrix;
	_child.push_back(child);
}
