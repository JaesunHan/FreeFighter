#include "stdafx.h"
#include "gameObject.h"


gameObject::gameObject()
	: _position(0, 0, 0)
	, _angleX(0.0f)
	, _angleY(0.0f)
	, _angleZ(0.0f)
	, _sx(0.01f)
	, _sy(0.01f)
	, _sz(0.01f)
	, _mtlName(_T(""))
	, _textureName(_T(""))
	, _vb(NULL)
	, _isMesh(false)
{
	D3DXMatrixIdentity(&_worldMatrix);
	D3DXMatrixIdentity(&_localMatrix);
}


gameObject::~gameObject()
{
}

void gameObject::init()
{
	if (_isMesh)
	{
		D3DDEVICE->CreateVertexBuffer(_vertex.size() * sizeof(tagPNT_Vertex),
			0,
			tagPNT_Vertex::FVF,
			D3DPOOL_MANAGED,
			&_vb,
			0);

		_vb->Lock(0, 0, (void**)&_vertexData, 0);

		for (int i = 0; i < _vertex.size(); ++i)
		{
			_vertexData[i] = _vertex[i];
		}

		_vb->Unlock();
	}
}

void gameObject::release()
{
	_vertex.clear();
	if (_isMesh)
	{
		if (_vb)
			_vb->Release();
	}
}

void gameObject::update()
{
	D3DXMATRIX rotation;
	D3DXMATRIX translation;
	D3DXMATRIX scale;
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&translation);
	D3DXMatrixIdentity(&scale);

	D3DXMatrixScaling(&scale, _sx, _sy, _sz);

	D3DXMatrixRotationYawPitchRoll(&rotation, _angleY, _angleX, _angleZ);

	D3DXMatrixTranslation(&translation, _position.x, _position.y, _position.z);

	_localMatrix = scale * rotation * translation;
	_worldMatrix = _localMatrix;
}

void gameObject::render()
{
	if (_textureName == _T("") &&
		_mtlName == _T("")) return;

	//D3DDEVICE->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_textureName));
	D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(_mtlName));
	// 월드매트릭스 적용
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
	// fvf정보 알려주기
	D3DDEVICE->SetFVF(tagPNT_Vertex::FVF);
	
	if (_isMesh)
	{
		D3DDEVICE->SetStreamSource(0, _vb, 0, sizeof(tagPNT_Vertex));
		D3DDEVICE->DrawPrimitive(D3DPT_TRIANGLELIST,
			0,
			_vertex.size() / 3);
	}
	else
	{
		// 그려주는 함수
		D3DDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,	// 점을 어떻게 이어주나
			_vertex.size() / 3,							// 그려줄 갯수
			&_vertex[0],								// 점 시작 주소
			sizeof(tagPNT_Vertex));						// 사이즈
	}

	//D3DDEVICE->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
}

void gameObject::positionWorld(D3DXVECTOR3 pos)
{
	_position = pos;
}

void gameObject::translateWorld(D3DXVECTOR3 pos)
{
	_position += pos;
}

void gameObject::translateLocal(D3DXVECTOR3 pos)
{
	D3DXMATRIX temp;
	D3DXMatrixTranslation(&temp, pos.x, pos.y, pos.z);
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &temp);
	}
}

void gameObject::rotateWorld(float angleX, float angleY, float angleZ)
{
	_angleX += angleX;
	_angleY += angleY;
	_angleZ += angleZ;
}

void gameObject::rotateLocal(float angleX, float angleY, float angleZ)
{
	D3DXMATRIX temp;
	D3DXMatrixRotationYawPitchRoll(&temp, angleY, angleX, angleZ);
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &temp);
		D3DXVec3TransformNormal(&_vertex[i].n, &_vertex[i].n, &temp);
		D3DXVec3Normalize(&_vertex[i].n, &_vertex[i].n);
	}
}

void gameObject::scaleWorld(float sx, float sy, float sz)
{
	_sx = sx;
	_sy = sy;
	_sz = sz;
}

void gameObject::scaleLocal(float sx, float sy, float sz)
{
	D3DXMATRIX temp;
	D3DXMatrixScaling(&temp, sx, sy, sz);
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &temp);
	}
}

void gameObject::transFormLocal(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz)
{
	D3DXMATRIX translation, rotation, scaling, localMatrix;
	D3DXMatrixTranslation(&translation, tx, ty, tz);
	D3DXMatrixRotationYawPitchRoll(&rotation, angleY, angleX, angleZ);
	D3DXMatrixScaling(&scaling, sx, sy, sz);

	localMatrix = scaling * rotation * translation;
	for (int i = 0; i < _vertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&_vertex[i].p, &_vertex[i].p, &localMatrix);
		D3DXVec3TransformNormal(&_vertex[i].n, &_vertex[i].n, &localMatrix);
		D3DXVec3Normalize(&_vertex[i].n, &_vertex[i].n);
	}
}

vector<D3DXVECTOR3> gameObject::getWorldVertex()
{
	vector<D3DXVECTOR3> temp;

	temp.resize(_vertex.size());
	for (int i = 0; i < temp.size(); ++i)
		D3DXVec3TransformCoord(&temp[i], &_vertex[i].p, &_worldMatrix);

	return temp;
}
