#include "stdafx.h"
#include "frustum.h"


frustum::frustum()
{
}


frustum::~frustum()
{
}

HRESULT frustum::init()
{
	_vProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));
	_vProjVertex.push_back(D3DXVECTOR3(-1,  1, 0));
	_vProjVertex.push_back(D3DXVECTOR3( 1,  1, 0));
	_vProjVertex.push_back(D3DXVECTOR3( 1, -1, 0));
	
	_vProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));
	_vProjVertex.push_back(D3DXVECTOR3(-1,  1, 1));
	_vProjVertex.push_back(D3DXVECTOR3( 1,  1, 1));
	_vProjVertex.push_back(D3DXVECTOR3( 1, -1, 1));

	_vWorldVertex.resize(8);
	_vPlane.resize(6);

	return S_OK;
}

void frustum::release()
{
}

void frustum::update()
{
	D3DXMATRIX view, projection;
	D3DDEVICE->GetTransform(D3DTS_PROJECTION, &projection);
	D3DDEVICE->GetTransform(D3DTS_VIEW, &view);

	for (int i = 0; i < _vProjVertex.size(); ++i)
	{
		D3DXVec3Unproject(&_vWorldVertex[i],
			&_vProjVertex[i],
			NULL,
			&projection,
			&view,
			NULL);
	}

	// ����
	D3DXPlaneFromPoints(&_vPlane[0], &_vWorldVertex[0], &_vWorldVertex[1], &_vWorldVertex[2]);
	// �ĸ�
	D3DXPlaneFromPoints(&_vPlane[1], &_vWorldVertex[6], &_vWorldVertex[5], &_vWorldVertex[4]);
	// ����
	D3DXPlaneFromPoints(&_vPlane[2], &_vWorldVertex[1], &_vWorldVertex[5], &_vWorldVertex[6]);
	// �Ʒ���
	D3DXPlaneFromPoints(&_vPlane[3], &_vWorldVertex[0], &_vWorldVertex[3], &_vWorldVertex[7]);
	// ���ʸ�
	D3DXPlaneFromPoints(&_vPlane[4], &_vWorldVertex[1], &_vWorldVertex[0], &_vWorldVertex[4]);
	// �����ʸ�
	D3DXPlaneFromPoints(&_vPlane[5], &_vWorldVertex[2], &_vWorldVertex[6], &_vWorldVertex[7]);

}

bool frustum::isIn(tagSphere* s)
{
	for (int i = 0; i < _vPlane.size(); ++i)
	{
		// �� ��� �ٱ��� ����
		if (D3DXPlaneDotCoord(&_vPlane[i], &s->center) > s->radius)
			return false;
	}

	return true;
}
