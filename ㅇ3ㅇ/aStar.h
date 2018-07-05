#pragma once

class naviMesh;
class naviCell;

class aStar
{
private:
	naviMesh* _naviMesh;

private:
	vector<naviCell*> _totalCell;			

private:
	float		_nearDis;
	naviCell*	_start;
	naviCell*	_end;
	naviCell*	_current;

public:
	aStar();
	~aStar();

	void MakeHeap(D3DXVECTOR3* start, D3DXVECTOR3* target);
	void PathFinder();

	void Init();
	void Release();
	void Update();
	void Render();
	
};

