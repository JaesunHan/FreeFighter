#include "stdafx.h"
#include "objectNode.h"
#include "action.h"


objectNode::objectNode()
	: _parent(NULL)
	, _parentMatrix(NULL)
{
	D3DXMatrixIdentity(&_worldMatrix);
	D3DXMatrixIdentity(&_localMatrix);
}


objectNode::~objectNode()
{
	for (int i = 0; i < _child.size(); ++i)
	{
		_child[i]->release();
		SAFE_DELETE(_child[i]);
	}
	_child.clear();
}

void objectNode::init()
{
	gameObject::init();

	for (int i = 1; i < _vRotTrack.size(); ++i)
		_vRotTrack[i]->quaternion = _vRotTrack[i - 1]->quaternion * _vRotTrack[i]->quaternion;
}

void objectNode::init(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz)
{
	_position = D3DXVECTOR3(tx, ty, tz);

	_angleX = angleX;
	_angleY = angleY;
	_angleZ = angleZ;

	_sx = sx;
	_sy = sy;
	_sz = sz;

	gameObject::update();
}

void objectNode::release()
{
	for (int i = 0; i < _vPosTrack.size(); ++i)
		SAFE_DELETE(_vPosTrack[i]);
	_vPosTrack.clear();
	for (int i = 0; i < _vRotTrack.size(); ++i)
		SAFE_DELETE(_vRotTrack[i]);
	_vRotTrack.clear();

	for (int i = 0; i < _child.size(); ++i)
	{
		_child[i]->release();
		SAFE_DELETE(_child[i]);
	}
	_child.clear();

	gameObject::release();
}

void objectNode::update()
{
	//gameObject::update();

	D3DXMATRIX aniMat, matR, matT;

	int keyFrame = this->getKeyFrame();
	this->calcLocalR(keyFrame, matR);
	this->calcLocalT(keyFrame, matT);

	aniMat = matR * matT;

	_worldMatrix = aniMat;

	if (_parentMatrix)
		_worldMatrix *= (*_parentMatrix);

	for (int i = 0; i < _child.size(); ++i)
		_child[i]->update();
}

void objectNode::render()
{
	gameObject::render();

	for (int i = 0; i < _child.size(); ++i)
		_child[i]->render();
}

void objectNode::addChild(objectNode * child)
{
	child->_parentMatrix = &this->_worldMatrix;
	child->_parent = this;
	_child.push_back(child);
}

void objectNode::addPosTrack(TRANSLATION* p)
{
	_vPosTrack.push_back(p);
}

void objectNode::addRotTrack(ROTATION* r)
{
	_vRotTrack.push_back(r);
}

void objectNode::setSceneInfo(DWORD first, DWORD last, DWORD frameSpeed, DWORD ticksPerFrame)
{
	_firstFrame = first;
	_lastFrame = last;
	_frameSpeed = frameSpeed;
	_ticksPerFrame = ticksPerFrame;
}

int objectNode::getKeyFrame()
{
	int first = _firstFrame * _ticksPerFrame;
	int last = _lastFrame * _ticksPerFrame;

	return (GetTickCount() * _ticksPerFrame / _frameSpeed) % (last - first) + first;
}

void objectNode::calcLocalR(IN int keyFrame, OUT D3DXMATRIX & matR)
{
	D3DXMatrixIdentity(&matR);
	if (_vRotTrack.empty())
	{
		matR = _localMatrix;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}

	if (keyFrame < _vRotTrack[0]->tick)
	{
		D3DXMatrixRotationQuaternion(&matR, &_vRotTrack[0]->quaternion);
		return;
	}
	if (keyFrame >= _vRotTrack.back()->tick)
	{
		D3DXMatrixRotationQuaternion(&matR, &_vRotTrack.back()->quaternion);
		return;
	}

	// 현재 프레임 번호 찾기
	int nextIndex = 0;
	for (int i = 0; i < _vRotTrack.size(); ++i)
	{
		if (keyFrame < _vRotTrack[i]->tick)
		{
			nextIndex = i;
			break;
		}
	}
	int prevIndex = nextIndex - 1;

	float t = (keyFrame - _vRotTrack[prevIndex]->tick) / (float)(_vRotTrack[nextIndex]->tick - _vRotTrack[prevIndex]->tick);

	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q,
		&_vRotTrack[prevIndex]->quaternion,
		&_vRotTrack[nextIndex]->quaternion,
		t);
	D3DXMatrixRotationQuaternion(&matR, &q);
}

void objectNode::calcLocalT(IN int keyFrame, OUT D3DXMATRIX & matT)
{
	D3DXMatrixIdentity(&matT);
	if (_vPosTrack.empty())
	{
		matT._41 = _localMatrix._41;
		matT._42 = _localMatrix._42;
		matT._43 = _localMatrix._43;
		return;
	}

	if (keyFrame < _vPosTrack[0]->tick)
	{
		matT._41 = _vPosTrack[0]->pos.x;
		matT._42 = _vPosTrack[0]->pos.y;
		matT._43 = _vPosTrack[0]->pos.z;
		return;
	}
	if (keyFrame >= _vPosTrack.back()->tick)
	{
		matT._41 = _vPosTrack.back()->pos.x;
		matT._42 = _vPosTrack.back()->pos.y;
		matT._43 = _vPosTrack.back()->pos.z;
		return;
	}

	// 현재 프레임 번호 찾기
	int nextIndex = 0;
	for (int i = 0; i < _vPosTrack.size(); ++i)
	{
		if (keyFrame < _vPosTrack[i]->tick)
		{
			nextIndex = i;
			break;
		}
	}
	int prevIndex = nextIndex - 1;

	float t = (keyFrame - _vPosTrack[prevIndex]->tick) / (float)(_vPosTrack[nextIndex]->tick - _vPosTrack[prevIndex]->tick);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v,
		&_vPosTrack[prevIndex]->pos,
		&_vPosTrack[nextIndex]->pos,
		t);

	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}
