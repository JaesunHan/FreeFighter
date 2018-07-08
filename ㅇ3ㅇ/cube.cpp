#include "stdafx.h"
#include "cube.h"
#include <time.h>


cube::cube()
	: _position(0, 0, 0)
{
	D3DXMatrixIdentity(&_worldMatrix);
}


cube::~cube()
{
}

void cube::init()
{
#ifdef PC_VERTEX
	srand(time(NULL));
	vector<tagPC_Vertex> temp;
	tagPC_Vertex v;

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	temp.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	temp.push_back(v);

	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[3]);

	_vertex.push_back(temp[7]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[7]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[4]);

	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[7]);

	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[0]);

	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[7]);

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

	D3DXVECTOR3 temp1, temp2;
	D3DXVECTOR3 cross;

	temp[0].t = D3DXVECTOR2(0, 0.85);
	temp[1].t = D3DXVECTOR2(0, 0.15);
	temp[2].t = D3DXVECTOR2(0.25, 0.15);
	temp[3].t = D3DXVECTOR2(0.25, 0.85);

	temp1 = temp[1].p - temp[0].p;
	temp2 = temp[3].p - temp[0].p;
	D3DXVec3Cross(&cross, &temp1, &temp2);
	D3DXVec3Normalize(&cross, &cross);
	temp[0].n = cross;
	temp[1].n = cross;
	temp[2].n = cross;
	temp[3].n = cross;

	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[3]);

	temp[3].t = D3DXVECTOR2(0.25, 0.85);
	temp[2].t = D3DXVECTOR2(0.25, 0.15);
	temp[6].t = D3DXVECTOR2(0.5, 0.15);
	temp[7].t = D3DXVECTOR2(0.5, 0.85);

	temp1 = temp[2].p - temp[3].p;
	temp2 = temp[7].p - temp[3].p;
	D3DXVec3Cross(&cross, &temp1, &temp2);
	D3DXVec3Normalize(&cross, &cross);
	temp[3].n = cross;
	temp[2].n = cross;
	temp[6].n = cross;
	temp[7].n = cross;

	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[2]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[7]);

	temp[7].t = D3DXVECTOR2(0.5, 0.85);
	temp[6].t = D3DXVECTOR2(0.5, 0.15);
	temp[5].t = D3DXVECTOR2(0.75, 0.15);
	temp[4].t = D3DXVECTOR2(0.75, 0.85);

	temp1 = temp[6].p - temp[7].p;
	temp2 = temp[4].p - temp[7].p;
	D3DXVec3Cross(&cross, &temp1, &temp2);
	D3DXVec3Normalize(&cross, &cross);
	temp[7].n = cross;
	temp[6].n = cross;
	temp[5].n = cross;
	temp[4].n = cross;

	_vertex.push_back(temp[7]);
	_vertex.push_back(temp[6]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[7]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[4]);

	temp[4].t = D3DXVECTOR2(0.75, 0.85);
	temp[5].t = D3DXVECTOR2(0.75, 0.15);
	temp[1].t = D3DXVECTOR2(1, 0.15);
	temp[0].t = D3DXVECTOR2(1, 0.85);

	temp1 = temp[5].p - temp[4].p;
	temp2 = temp[0].p - temp[4].p;
	D3DXVec3Cross(&cross, &temp1, &temp2);
	D3DXVec3Normalize(&cross, &cross);
	temp[4].n = cross;
	temp[5].n = cross;
	temp[1].n = cross;
	temp[0].n = cross;

	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[5]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[1]);
	_vertex.push_back(temp[0]);

	temp[4].t = D3DXVECTOR2(0, 1);
	temp[0].t = D3DXVECTOR2(0, 0.85);
	temp[3].t = D3DXVECTOR2(1, 0.85);
	temp[7].t = D3DXVECTOR2(1, 1);

	temp1 = temp[0].p - temp[4].p;
	temp2 = temp[7].p - temp[4].p;
	D3DXVec3Cross(&cross, &temp1, &temp2);
	D3DXVec3Normalize(&cross, &cross);
	temp[4].n = cross;
	temp[0].n = cross;
	temp[3].n = cross;
	temp[7].n = cross;

	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[0]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[4]);
	_vertex.push_back(temp[3]);
	_vertex.push_back(temp[7]);

	temp[1].t = D3DXVECTOR2(0, 0.15);
	temp[5].t = D3DXVECTOR2(0, 0);
	temp[6].t = D3DXVECTOR2(1, 0);
	temp[2].t = D3DXVECTOR2(1, 0.15);

	temp1 = temp[5].p - temp[1].p;
	temp2 = temp[2].p - temp[1].p;
	D3DXVec3Cross(&cross, &temp1, &temp2);
	D3DXVec3Normalize(&cross, &cross);
	temp[1].n = cross;
	temp[5].n = cross;
	temp[6].n = cross;
	temp[2].n = cross;

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

void cube::release()
{
	_vertex.clear();
}

void cube::update(D3DXMATRIX* parent)
{
	D3DXMATRIX rotation;
	D3DXMATRIX translation;
	D3DXMATRIX scale;
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&translation);
	D3DXMatrixIdentity(&scale);

	D3DXMatrixScaling(&scale, _sx, _sy, _sz);

	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//	_angleY -= 2 * DEG2RAD;
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//	_angleY += 2 * DEG2RAD;
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//	_angleX -= 2 * DEG2RAD;
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//	_angleX += 2 * DEG2RAD;
	//
	D3DXMatrixRotationYawPitchRoll(&rotation, _angleY, _angleX, _angleZ);
	//
	//D3DXVECTOR3 dir;
	//float speedX = 0.0f;
	//float speedZ = 0.0f;
	//if (KEYMANAGER->isStayKeyDown('W'))
	//	speedZ = 0.05f;
	//if (KEYMANAGER->isStayKeyDown('S'))
	//	speedZ = -0.05f;
	//if (KEYMANAGER->isStayKeyDown('A'))
	//	speedX = -0.05f;
	//if (KEYMANAGER->isStayKeyDown('D'))
	//	speedX = 0.05f;
	//
	//dir = D3DXVECTOR3(speedX, 0, speedZ);
	//D3DXVec3TransformNormal(&dir, &dir, &rotation);
	//
	//D3DXVec3TransformCoord(&_position, &_position, D3DXMatrixTranslation(&translation, dir.x, dir.y, dir.z));
	D3DXMatrixTranslation(&translation, _position.x, _position.y, _position.z);

	_worldMatrix = scale * rotation * translation;

	if (parent)
		_worldMatrix = scale * rotation * translation * (*parent);
}

void cube::render()
{
	// 월드매트릭스 적용
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
	// fvf정보 알려주기
	D3DDEVICE->SetFVF(CURRNET_FVF);

	// 그려주는 함수
	D3DDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,	// 점을 어떻게 이어주나
		_vertex.size() / 3,							// 그려줄 갯수
		&_vertex[0],								// 점 시작 주소
		sizeof(CURRNET_MODE));						// 사이즈

	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);
}

void cube::positionWorld(D3DXVECTOR3 pos)
{
	_position = pos;
}

void cube::translateWorld(D3DXVECTOR3 pos)
{
	_position += pos;
}

void cube::translateLocal(D3DXVECTOR3 pos)
{
	D3DXMATRIX temp;
	D3DXMatrixTranslation(&temp, pos.x, pos.y, pos.z);
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &temp);
	}
}

void cube::rotateWorld(float angleX, float angleY, float angleZ)
{
	_angleX += angleX;
	_angleY += angleY;
	_angleZ += angleZ;
}

void cube::rotateLocal(float angleX, float angleY, float angleZ)
{
	D3DXMATRIX temp;
	D3DXMatrixRotationYawPitchRoll(&temp, angleY, angleX, angleZ);
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &temp);
#ifdef PT_VERTEX
		D3DXVec3TransformNormal(&_vertex[i].n, &_vertex[i].n, &temp);
		D3DXVec3Normalize(&_vertex[i].n, &_vertex[i].n);
#endif
	}
}

void cube::scaleWorld(float sx, float sy, float sz)
{
	_sx = sx;
	_sy = sy;
	_sz = sz;
}

void cube::scaleLocal(float sx, float sy, float sz)
{
	D3DXMATRIX temp;
	D3DXMatrixScaling(&temp, sx, sy, sz);
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &temp);
#ifdef PT_VERTEX
		D3DXVec3TransformNormal(&_vertex[i].n, &_vertex[i].n, &temp);
		D3DXVec3Normalize(&_vertex[i].n, &_vertex[i].n);
#endif
	}
}

void cube::transFormLocal(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz)
{
	D3DXMATRIX translation, rotation, scaling, localMatrix;
	D3DXMatrixTranslation(&translation, tx, ty, tz);
	D3DXMatrixRotationYawPitchRoll(&rotation, angleY, angleX, angleZ);
	D3DXMatrixScaling(&scaling, sx, sy, sz);

	localMatrix = scaling * rotation * translation;
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &localMatrix);
#ifdef PT_VERTEX
		D3DXVec3TransformNormal(&_vertex[i].n, &_vertex[i].n, &localMatrix);
		D3DXVec3Normalize(&_vertex[i].n, &_vertex[i].n);
#endif
	}
}
