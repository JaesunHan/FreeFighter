#include "stdafx.h"
#include "cubeHead.h"


cubeHead::cubeHead()
	: _headAngle(0.0f)
	, _go(GO_NONE)
{
}


cubeHead::~cubeHead()
{
}

void cubeHead::init()
{
#ifdef PC_VERTEX
	cube::init();
#endif

#ifdef PT_VERTEX
	vector<tagPNT_Vertex> temp;
	tagPNT_Vertex v;

	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(0, 0);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(1, 1);
	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(1, 1);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(0, 0);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	temp.push_back(v);

	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	temp.push_back(v);

	temp[0].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(2), DISTANCE(4));
	temp[1].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(2), DISTANCE(2));
	temp[2].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(2));
	temp[3].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(4));
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[3]);

	temp[3].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(4));
	temp[2].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(2));
	temp[6].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(6), DISTANCE(2));
	temp[7].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(6), DISTANCE(4));
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[7]);

	temp[7].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(6), DISTANCE(4));
	temp[6].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(6), DISTANCE(2));
	temp[5].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(8), DISTANCE(2));
	temp[4].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(8), DISTANCE(4));
	_vertex.push_back(temp[7]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[7]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[4]);

	temp[4].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(0), DISTANCE(4));
	temp[5].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(0), DISTANCE(2));
	temp[1].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(2), DISTANCE(2));
	temp[0].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(2), DISTANCE(4));
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[0]);

	temp[4].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(6), DISTANCE(0));
	temp[0].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(6), DISTANCE(2));
	temp[3].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(2));
	temp[7].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(0));
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[7]);

	temp[1].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(0));
	temp[5].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(4), DISTANCE(2));
	temp[6].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(2), DISTANCE(2));
	temp[2].t = TEXTUREMANAGER->getUVPoint("cubeMan", DISTANCE(2), DISTANCE(0));
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[2]);

	_angleX = 0.0f;
	_angleY = 0.0f;
	_angleZ = 0.0f;

	_sx = 1;
	_sy = 1;
	_sz = 1;
#endif
}

void cubeHead::update()
{
	if (_go == GO_LEFT)
	{
		_headAngle = -45 * DEG2RAD;
	}
	else if (_go == GO_RIGHT)
	{
		_headAngle = 45 * DEG2RAD;
	}
	else if (_go == GO_NONE)
		_headAngle = 0.0f;

	this->rotateLocal(0, _headAngle, 0);

	cubeNode::update();
}

void cubeHead::render()
{
	cubeNode::render();
	this->rotateLocal(0, -_headAngle, 0);
}
