#include "stdafx.h"
#include "grid.h"


grid::grid()
{
}


grid::~grid()
{
}


void grid::init()
{
	int numLines = 10;
	float interval = 1.0f;
	float max = interval * numLines;

	tagPC_Vertex v;
	v.c = BLACK;
	for (int i = 1; i <= numLines; i++)
	{
		v.p = D3DXVECTOR3(-max, 0, i);
		_grid.push_back(v);
		v.p = D3DXVECTOR3(max, 0, i);
		_grid.push_back(v);

		v.p = D3DXVECTOR3(-max, 0, -i);
		_grid.push_back(v);
		v.p = D3DXVECTOR3(max, 0, -i);
		_grid.push_back(v);

		v.p = D3DXVECTOR3(i, 0, -max);
		_grid.push_back(v);
		v.p = D3DXVECTOR3(i, 0, max);
		_grid.push_back(v);

		v.p = D3DXVECTOR3(-i, 0, -max);
		_grid.push_back(v);
		v.p = D3DXVECTOR3(-i, 0, max);
		_grid.push_back(v);
	}

	v.p = D3DXVECTOR3(-max, 0, 0);
	_grid.push_back(v);
	v.p = D3DXVECTOR3(max, 0, 0);
	_grid.push_back(v);

	v.p = D3DXVECTOR3(0, 0, -max);
	_grid.push_back(v);
	v.p = D3DXVECTOR3(0, 0, max);
	_grid.push_back(v);

	float angle = 0.0f;
	float dis = 10.0f;
	for (int i = 0; i < 6; ++i)
	{
		v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		_vLine.push_back(v);
		angle += D3DX_PI / 3;
		//v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		//_vLine.push_back(v);
		////_vLine.push_back(v);
		//angle += D3DX_PI / 3;
		//v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		//_vLine.push_back(v);
		////_vLine.push_back(v);
		//angle += D3DX_PI / 3;
		//v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		//_vLine.push_back(v);
		////_vLine.push_back(v);
		//angle += D3DX_PI / 3;
		//v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		//_vLine.push_back(v);
		////_vLine.push_back(v);
		//angle += D3DX_PI / 3;
		//v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		//_vLine.push_back(v);
		////_vLine.push_back(v);
		//angle += D3DX_PI / 3;
		//v.p = D3DXVECTOR3(dis * cosf(angle), 0, dis * sinf(angle));
		//_vLine.push_back(v);
	}
	_vLine.push_back(_vLine[0]);
}

void grid::release()
{
	_grid.clear();
}

void grid::render()
{
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);
	D3DDEVICE->SetTexture(0, NULL);
	D3DDEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D3DDEVICE->SetFVF(tagPC_Vertex::FVF);
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DDEVICE->DrawPrimitiveUP(D3DPT_LINELIST, _grid.size() / 2, &_grid[0], sizeof(tagPC_Vertex));

	vector<tagPC_Vertex> tempAxis;
	tagPC_Vertex center;
	tagPC_Vertex axis;
	center.p = D3DXVECTOR3(0, 0, 0);

	axis.p = D3DXVECTOR3(100, 0, 0);
	center.c = D3DCOLOR_XRGB(255, 0, 0);
	axis.c = D3DCOLOR_XRGB(255, 0, 0);
	tempAxis.push_back(center);
	tempAxis.push_back(axis);

	axis.p = D3DXVECTOR3(0, 100, 0);
	center.c = D3DCOLOR_XRGB(0, 255, 0);
	axis.c = D3DCOLOR_XRGB(0, 255, 0);
	tempAxis.push_back(center);
	tempAxis.push_back(axis);

	axis.p = D3DXVECTOR3(0, 0, 100);
	center.c = D3DCOLOR_XRGB(0, 0, 255);
	axis.c = D3DCOLOR_XRGB(0, 0, 255);
	tempAxis.push_back(center);
	tempAxis.push_back(axis);

	D3DDEVICE->DrawPrimitiveUP(D3DPT_LINELIST, tempAxis.size() / 2, &tempAxis[0], sizeof(tagPC_Vertex));

	//D3DDEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, _vLine.size() - 1, &_vLine[0], sizeof(tagPC_Vertex));

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

	D3DDEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
