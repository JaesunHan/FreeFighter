#pragma once

class naviMesh;
class naviCell;

class aStar
{
private:
	naviMesh* _naviMesh;

private:
	vector<naviCell*>	_vOpenList;	//갈수있는타일
	D3DXVECTOR3*		_startPos;	//시작위치
	D3DXVECTOR3*		_target;	//타겟

private:
	float		_nearDis;
	naviCell*	_start;
	naviCell*	_end;
	naviCell*	_current;

public:
	aStar();
	~aStar();

	void Setup(D3DXVECTOR3* start, D3DXVECTOR3* target);
	void MakeHeap(naviCell* currentCell);
	void PathFinder();

	void Init();
	void Release();
	void Update();
	void Render();
	
};

