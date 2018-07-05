#include "stdafx.h"
#include "naviMesh.h"
#include "naviCell.h"


naviMesh::naviMesh()
{
}


naviMesh::~naviMesh()
{
}

void naviMesh::AddCell(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2)
{
	naviCell* newCell = new naviCell;
	newCell->Init(v0, v1, v2);
	_vMesh.push_back(newCell);
}

void naviMesh::LinkDetection()
{
	for (int i = 0; i < _vMesh.size(); i++)
	{// /
		for (int j = 0; j < 3; j++)
		{// //
			D3DXVECTOR3 rayPos = _vMesh[i]->GetVerMid()[j];
			D3DXVECTOR3 dir;
			D3DXVec3Normalize(&dir, &(_vMesh[i]->GetVerMid()[j] - _vMesh[i]->GetTriCenter()));
			dir *= 0.01f;
			rayPos += dir;
			for (int w = 0; w < _vMesh.size(); w++)
			{// ///
				if (D3DXIntersectTri(&_vMesh[w]->GetVerMid()[0],
					&_vMesh[w]->GetVerMid()[1],
					&_vMesh[w]->GetVerMid()[2],
					&(rayPos + D3DXVECTOR3(0.0f, 100.0f, 0.0f)),
					&D3DXVECTOR3(0.0f, -1.0f, 0.0f),
					NULL, NULL, NULL))
				{
					_vMesh[i]->SetLink(_vMesh[w]);
					break;
				}
			}// ///
			_vMesh[i]->SetLink(NULL);
		}// //
	}// /
}
