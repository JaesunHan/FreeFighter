#include "stdafx.h"
#include "ray.h"


ray::ray()
	: _position(0.0f, 0.0f, 0.0f)
	, _direction(0.0f, 0.0f, 1.0f)
{
}


ray::~ray()
{
}

void ray::init(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	_position = pos;
	_direction = dir;
}

ray ray::rayAtViewSpace(int screenX, int screenY)
{
	D3DVIEWPORT9 viewPort;
	D3DDEVICE->GetViewport(&viewPort);

	D3DXMATRIX projection;
	D3DDEVICE->GetTransform(D3DTS_PROJECTION, &projection);

	float x = (((2.0f * screenX) / viewPort.Width) - 1.0f) / projection._11;
	float y = (((-2.0f * screenY) / viewPort.Height) + 1.0f) / projection._22;
	ray r;
	r._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	r._direction.x = x;
	r._direction.y = y;
	r._direction.z = 1.0f;

	return r;
}

ray ray::rayAtWorldSpace(int screenX, int screenY)
{
	ray r = ray::rayAtViewSpace(screenX, screenY);

	D3DXMATRIX view, viewInverse;
	D3DDEVICE->GetTransform(D3DTS_VIEW, &view);
	D3DXMatrixInverse(&viewInverse, NULL, &view);

	D3DXVec3TransformCoord(&r._position, &r._position, &viewInverse);
	D3DXVec3TransformNormal(&r._direction, &r._direction, &viewInverse);
	D3DXVec3Normalize(&r._direction, &r._direction);

	return r;
}

void ray::TransformRay(ray* r, D3DXMATRIX& m)
{
	D3DXVec3TransformCoord(&r->_position, &r->_position, &m);
	D3DXVec3TransformNormal(&r->_direction, &r->_direction, &m);
	D3DXVec3Normalize(&r->_direction, &r->_direction);
}

bool ray::isPicked(ray* r, tagSphere& s)
{
	//ray r = (*this);
	//
	//D3DXMATRIX worldInverse;
	//D3DXMatrixIdentity(&worldInverse);
	//worldInverse._41 = -s.center.x;
	//worldInverse._42 = -s.center.y;
	//worldInverse._43 = -s.center.z;
	//
	//D3DXVec3TransformCoord(&r._position, &r._position, &worldInverse);
	//D3DXVec3TransformNormal(&r._direction, &r._direction, &worldInverse);
	//
	//float vv = D3DXVec3Dot(&r._direction, &r._direction);
	//float qv = D3DXVec3Dot(&r._position, &r._direction);
	//float qq = D3DXVec3Dot(&r._position, &r._position);
	//float rr = s.radius * s.radius;
	//
	//return qv * qv - vv * (qq - rr) >= 0;
	D3DXVECTOR3 v = r->_position - s.center;

	float b = 2.0f * D3DXVec3Dot(&r->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (s.radius * s.radius);

	float discriminant = (b * b) - (4.0f * c);

	if (discriminant < 0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	if (s0 >= 0 || s1 >= 0)
		return true;

	return false;
}

float ray::calcDistance(ray* r, D3DXVECTOR3 v)
{
	return getDistance(r->_position, v);
}

bool ray::IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3& pickedPosition)
{
	float u, v, dis;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &_position, &_direction, &u, &v, &dis);
	
	pickedPosition = _position + _direction * dis;

	return b;
}
