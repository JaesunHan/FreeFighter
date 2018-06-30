#include "stdafx.h"
#include "heightMap.h"
#include "ray.h"
#include "character.h"


heightMap::heightMap()
	: _numOfGrid(0)
	, _map(NULL)
{
}


heightMap::~heightMap()
{
}

void heightMap::init()
{
	this->LoadFile(_T(".\\heightMap\\HeightMap.raw"));

	TEXTUREMANAGER->addTexture(_T("terrain"), _T(".\\heightMap\\terrain.jpg"));

	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&_worldMatrix);
	D3DXMatrixTranslation(&matT, (-_numOfGrid / 2) * 0.1f, 0.0f, -(_numOfGrid / 2) * 0.1f);
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	_worldMatrix = matS * matT;
}

void heightMap::release()
{
	if (_map)
	{
		_map->Release();
		_map = NULL;
	}
}

void heightMap::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		ray r = ray::rayAtWorldSpace(_ptMouse.x, _ptMouse.y);

		tagPNT_Vertex* vertexBuffer = NULL;
		_map->LockVertexBuffer(0, (void**)&vertexBuffer);

		D3DXVECTOR3 pickedPos;
		bool isPicked = false;
		for (int i = 0; i < _numOfGrid - 1 && !isPicked; ++i)
		{
			for (int j = 0; j < _numOfGrid - 1; ++j)
			{
				D3DXVECTOR3 v0, v1, v2;
				D3DXVec3TransformCoord(&v0, &vertexBuffer[i * _numOfGrid + j].p,		&_worldMatrix);
				D3DXVec3TransformCoord(&v1, &vertexBuffer[(i + 1) * _numOfGrid + j].p,	&_worldMatrix);
				D3DXVec3TransformCoord(&v2, &vertexBuffer[i * _numOfGrid + j + 1].p,	&_worldMatrix);
				if (r.ray::IntersectTri(v0, v1, v2, pickedPos))
				{
					isPicked = true;
					break;
				}

				D3DXVec3TransformCoord(&v0, &vertexBuffer[(i + 1) * _numOfGrid + j].p,		&_worldMatrix);
				D3DXVec3TransformCoord(&v1, &vertexBuffer[(i + 1) * _numOfGrid + j + 1].p,	&_worldMatrix);
				D3DXVec3TransformCoord(&v2, &vertexBuffer[i * _numOfGrid + j + 1].p,		&_worldMatrix);
				if (r.ray::IntersectTri(v0, v1, v2, pickedPos))
				{
					isPicked = true;
					break;
				}
			}
		}

		if (isPicked)
		{
			_player->moveTo(pickedPos);
		}

		_map->UnlockVertexBuffer();
	}
}

void heightMap::render()
{
	D3DMATERIAL9 mtl;
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
	mtl.Ambient.r = mtl.Diffuse.r = 0.3f;
	mtl.Ambient.g = mtl.Diffuse.g = 0.3f;
	mtl.Ambient.b = mtl.Diffuse.b = 0.3f;
	mtl.Ambient.a = mtl.Diffuse.a = 0.3f;
	D3DDEVICE->SetMaterial(&mtl);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
	if (!_isDebug)
	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_T("terrain")));
	else
	D3DDEVICE->SetTexture(0, NULL);
	D3DDEVICE->SetFVF(tagPNT_Vertex::FVF);
	D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	_map->DrawSubset(0);
	D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	_map->DrawSubset(0);
}

#ifdef UNICODE
void heightMap::LoadFile(const WCHAR* fileName)
{
	_fin.open(fileName, ios::in | ios::binary);

	_fin.seekp(0, ios::end);
	_numOfGrid = _fin.tellp();

	_numOfGrid = sqrtf(_numOfGrid);

	_fin.seekp(0, ios::beg);

	D3DXCreateMeshFVF((_numOfGrid - 1) * (_numOfGrid - 1) * 2,
		_numOfGrid * _numOfGrid,
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		tagPNT_Vertex::FVF,
		D3DDEVICE,
		&_map);

	tagPNT_Vertex* vertexBuffer = NULL;
	_map->LockVertexBuffer(0, (void**)&vertexBuffer);

	for (int i = 0; i < _numOfGrid; ++i)
	{
		for (int j = 0; j < _numOfGrid; ++j)
		{
			BYTE temp;
			_fin.read((char*)&temp, sizeof(BYTE));
			vertexBuffer[i * _numOfGrid + j].p = D3DXVECTOR3(j, temp / 10.0f, i);
			vertexBuffer[i * _numOfGrid + j].t = D3DXVECTOR2(j / (float)(_numOfGrid - 1), i / (float)_numOfGrid);
			vertexBuffer[i * _numOfGrid + j].n = D3DXVECTOR3(0, 1, 0);
		}
	}

	_map->UnlockVertexBuffer();

	DWORD* indexBuffer = NULL;
	_map->LockIndexBuffer(0, (void**)&indexBuffer);

	int count = 0;
	for (int i = 0; i < _numOfGrid - 1; ++i)
	{
		for (int j = 0; j < _numOfGrid - 1; ++j)
		{
			indexBuffer[count++] = i * _numOfGrid + j;
			indexBuffer[count++] = (i + 1) * _numOfGrid + j;
			indexBuffer[count++] = i * _numOfGrid + j + 1;

			indexBuffer[count++] = (i + 1) * _numOfGrid + j;
			indexBuffer[count++] = (i + 1) * _numOfGrid + j + 1;
			indexBuffer[count++] = i * _numOfGrid + j + 1;

			if (i == 0 || j == 0) continue;
			D3DXVECTOR3 v0, v1;
			v0 = vertexBuffer[(i + 1) * _numOfGrid + j].p - vertexBuffer[(i - 1) * _numOfGrid + j].p;
			v1 = vertexBuffer[i * _numOfGrid + j + 1].p - vertexBuffer[i * _numOfGrid + j - 1].p;
			D3DXVec3Cross(&vertexBuffer[i * _numOfGrid + j].n, &v0, &v1);
			D3DXVec3Normalize(&vertexBuffer[i * _numOfGrid + j].n, &vertexBuffer[i * _numOfGrid + j].n);
		}
	}

	_map->UnlockIndexBuffer();

	_fin.close();
}
#else
void heightMap::LoadFile(const char* fileName)
{
	_fin.open(fileName, ios::in | ios::binary);

	_fin.seekp(0, ios::end);
	_numOfGrid = _fin.tellp();

	_numOfGrid = sqrtf(_numOfGrid);

	_fin.seekp(0, ios::beg);

	D3DXCreateMeshFVF((_numOfGrid - 1) * (_numOfGrid - 1) * 2,
		_numOfGrid * _numOfGrid,
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		tagPNT_Vertex::FVF,
		D3DDEVICE,
		&_map);

	tagPNT_Vertex* vertexBuffer = NULL;
	_map->LockVertexBuffer(0, (void**)&vertexBuffer);

	for (int i = 0; i < _numOfGrid; ++i)
	{
		for (int j = 0; j < _numOfGrid; ++j)
		{
			BYTE temp;
			_fin.read((char*)&temp, sizeof(BYTE));
			vertexBuffer[i * _numOfGrid + j].p = D3DXVECTOR3(j, temp / 10.0f, i);
			vertexBuffer[i * _numOfGrid + j].t = D3DXVECTOR2(j / (float)(_numOfGrid - 1), i / (float)_numOfGrid);
			vertexBuffer[i * _numOfGrid + j].n = D3DXVECTOR3(0, 1, 0);
		}
	}

	_map->UnlockVertexBuffer();

	DWORD* indexBuffer = NULL;
	_map->LockIndexBuffer(0, (void**)&indexBuffer);

	int count = 0;
	for (int i = 0; i < _numOfGrid - 1; ++i)
	{
		for (int j = 0; j < _numOfGrid - 1; ++j)
		{
			indexBuffer[count++] = i * _numOfGrid + j;
			indexBuffer[count++] = (i + 1) * _numOfGrid + j;
			indexBuffer[count++] = i * _numOfGrid + j + 1;

			indexBuffer[count++] = (i + 1) * _numOfGrid + j;
			indexBuffer[count++] = (i + 1) * _numOfGrid + j + 1;
			indexBuffer[count++] = i * _numOfGrid + j + 1;

			if (i == 0 || j == 0) continue;
			D3DXVECTOR3 v0, v1;
			v0 = vertexBuffer[(i + 1) * _numOfGrid + j].p - vertexBuffer[(i - 1) * _numOfGrid + j].p;
			v1 = vertexBuffer[i * _numOfGrid + j + 1].p - vertexBuffer[i * _numOfGrid + j - 1].p;
			D3DXVec3Cross(&vertexBuffer[i * _numOfGrid + j].n, &v0, &v1);
			D3DXVec3Normalize(&vertexBuffer[i * _numOfGrid + j].n, &vertexBuffer[i * _numOfGrid + j].n);
		}
	}

	_map->UnlockIndexBuffer();

	_fin.close();
}
#endif

void heightMap::getPlayerIndex(D3DXVECTOR3& pos)
{
	//D3DXVECTOR3 tempPos = pos;
	//ray r;
	//r.init(tempPos, D3DXVECTOR3(0, -1, 0));

	tagPNT_Vertex* vertexBuffer = NULL;
	_map->LockVertexBuffer(0, (void**)&vertexBuffer);

	D3DXVECTOR3 tempPos = pos;

	int idxX = (tempPos.x - _worldMatrix._41) * 10;
	int idxZ = (tempPos.z - _worldMatrix._43) * 10;

	if (idxX < 0 || idxX >= _numOfGrid) return;
	if (idxZ < 0 || idxZ >= _numOfGrid) return;

	int index1 = idxX + idxZ * _numOfGrid;
	int index2 = (idxX + 1) + (idxZ + 1) * _numOfGrid;

	D3DXVECTOR3 v1, v2;
	D3DXVec3TransformCoord(&v1, &vertexBuffer[index1].p, &_worldMatrix);
	D3DXVec3TransformCoord(&v2, &vertexBuffer[index2].p, &_worldMatrix);

	if (getDistance(tempPos, v1) < getDistance(tempPos, v2))
	{
		float disX, disZ;
		D3DXVECTOR3 vX, vZ;
		disX = tempPos.x - v1.x;
		disZ = tempPos.z - v1.z;

		if (disX < 0)
			disX *= -1;

		if (disZ < 0)
			disZ *= -1;

		D3DXVECTOR3 right, up;
		D3DXVec3TransformCoord(&right, &vertexBuffer[index1 + 1].p, &_worldMatrix);
		D3DXVec3TransformCoord(&up, &vertexBuffer[index1 + _numOfGrid].p, &_worldMatrix);

		vX = (right - v1) * disX;
		vZ = (up - v1) * disZ;

		if (disZ == 0 && disX == 0)
			pos.y = v1.y;
		else if (disX == 0)
			pos.y = vZ.y + v1.y;
		else if (disZ == 0)
			pos.y = vX.y + v1.y;
		else
			pos.y = (vX + vZ).y + v1.y;
	}
	else
	{
		float disX, disZ;
		D3DXVECTOR3 vX, vZ;
		disX = tempPos.x - v2.x;
		disZ = tempPos.z - v2.z;

		if (disX < 0)
			disX *= -1;

		if (disZ < 0)
			disZ *= -1;

		D3DXVECTOR3 left, down;
		D3DXVec3TransformCoord(&left, &vertexBuffer[index2 - 1].p, &_worldMatrix);
		D3DXVec3TransformCoord(&down, &vertexBuffer[index2 - _numOfGrid].p, &_worldMatrix);

		vX = (left - v2) * disX;
		vZ = (down - v2) * disZ;

		if (disZ == 0 && disX == 0)
			pos.y = v2.y;
		else if (disX == 0)
			pos.y = vZ.y + v2.y;
		else if (disZ == 0)
			pos.y = vX.y + v2.y;
		else
			pos.y = (vX + vZ).y + v2.y;
	}

	//D3DXVECTOR3 pickedPos;
	//bool isPicked = false;
	//for (int i = 0; i < _numOfGrid - 1 && !isPicked; ++i)
	//{
	//	for (int j = 0; j < _numOfGrid - 1; ++j)
	//	{
	//		D3DXVECTOR3 v0, v1, v2;
	//		D3DXVec3TransformCoord(&v0, &vertexBuffer[i * _numOfGrid + j].p, &_worldMatrix);
	//		D3DXVec3TransformCoord(&v1, &vertexBuffer[(i + 1) * _numOfGrid + j].p, &_worldMatrix);
	//		D3DXVec3TransformCoord(&v2, &vertexBuffer[i * _numOfGrid + j + 1].p, &_worldMatrix);
	//		if (r.IntersectTri(v0, v1, v2, pickedPos))
	//		{
	//			isPicked = true;
	//			break;
	//		}
	//
	//		D3DXVec3TransformCoord(&v0, &vertexBuffer[(i + 1) * _numOfGrid + j].p, &_worldMatrix);
	//		D3DXVec3TransformCoord(&v1, &vertexBuffer[(i + 1) * _numOfGrid + j + 1].p, &_worldMatrix);
	//		D3DXVec3TransformCoord(&v2, &vertexBuffer[i * _numOfGrid + j + 1].p, &_worldMatrix);
	//		if (r.IntersectTri(v0, v1, v2, pickedPos))
	//		{
	//			isPicked = true;
	//			break;
	//		}
	//	}
	//}
	//
	//if (isPicked)
	//{
	//	int indexX = pickedPos.x;
	//	int indexZ = pickedPos.z;
	//
	//	pos.y = pickedPos.y + 0.25f;
	//
	//	_map->UnlockVertexBuffer();
	//
	//	return indexZ * _numOfGrid + indexX;
	//}

	_map->UnlockVertexBuffer();
}
