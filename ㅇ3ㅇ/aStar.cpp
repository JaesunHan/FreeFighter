#include "stdafx.h"
#include "aStar.h"
#include "naviMesh.h"
#include "naviCell.h"


aStar::aStar()
	: _nearDis(0)
	, _start(NULL)
	, _end(NULL)
	, _current(NULL)
	, _target(NULL)
{
}


aStar::~aStar()
{
}

void aStar::Setup(D3DXVECTOR3* start, D3DXVECTOR3* target)
{
	_startPos = start;
	_target = target;

	//시작 셀 찾기
	for (auto p : _naviMesh->GetNaviMesh())
	{
		if (D3DXIntersectTri(&p->GetVertex()[0],
			&p->GetVertex()[1],
			&p->GetVertex()[2],
			start,
			&D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			NULL, NULL, NULL))
		{
			_start = p;
			//_start->SetAttribute("start");
			break;
		}
	}
	//끝 셀 찾기
	for (auto p : _naviMesh->GetNaviMesh())
	{
		if (D3DXIntersectTri(&p->GetVertex()[0],
			&p->GetVertex()[1],
			&p->GetVertex()[2],
			target,
			&D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			NULL, NULL, NULL))
		{
			_end = p;
			//_end->SetAttribute("end");
			break;
		}
	}

	_current = _start;
}

void aStar::MakeHeap(naviCell* currentCell)
{
	//갈 수 있는 타일 _vOpenList에 저장

	float tempTotalCost = 5000;
	naviCell* tempCell = NULL;

	for (int i = 0; i < 3; i++)
	{
		if (currentCell->GetLink()[i] == _end) return;

		if (currentCell->GetLink()[i])
		{
			if (!currentCell->GetIsOpen()) continue;
			if (currentCell == _start) continue;

			float deltaX = _target->x - currentCell->GetLink()[i]->GetTriCenter().x;
			float deltaY = _target->y - currentCell->GetLink()[i]->GetTriCenter().y;
			float deltaZ = _target->z - currentCell->GetLink()[i]->GetTriCenter().z;

			float dis = max(max(deltaX, deltaY), deltaZ);

			if (tempTotalCost > dis)
			{
				tempTotalCost = dis;
				tempCell = currentCell->GetLink()[i];
			}
		}
	}

	_current = tempCell;
	_current->SetIsOpen(false);
	_vOpenList.push_back(tempCell);

	MakeHeap(_current);
}

void aStar::PathFinder()
{
	MakeHeap(_current);

}

void aStar::Init()
{
	_naviMesh = new naviMesh;
}

void aStar::Release()
{
}

void aStar::Update()
{
	PathFinder();
}

void aStar::Render()
{
}
