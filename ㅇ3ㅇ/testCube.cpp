#include "stdafx.h"
#include "testCube.h"

#include "cube.h"


testCube::testCube()
	: _vPos(0, 0, 0)
	, _vDir(0, 0, 1)
	, _rotY(0.0f)
{
	D3DXMatrixIdentity(&_worldTM);
}


testCube::~testCube()
{
	
}

void testCube::Setup()
{
	_cube = new cube;
	_cube->init();

}

void testCube::Update()
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_rotY += 0.1f;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_rotY -= 0.1f;
	}

	D3DXMATRIX  matR, matT;
	D3DXMatrixRotationY(&matR, _rotY);
	D3DXVec3TransformNormal(&_vDir, &D3DXVECTOR3(0, 0, 1), &matR);

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_vPos += _vDir * 0.1f;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_vPos -= _vDir * 0.1f;
	}

	D3DXMatrixTranslation(&matT, _vPos.x, _vPos.y, _vPos.z);

	_worldTM = matR * matT;

	//_cube->update(&_worldTM);
	_cube->SetWorldTM(_worldTM);
}

void testCube::Render()
{
	_cube->render();
}

void testCube::createController(PxControllerManager ** cm, PxMaterial * m)
{
}
