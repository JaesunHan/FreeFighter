#pragma once

class naviCell;

class naviMesh
{
private:
	vector<naviCell*> _vMesh;

public:
	naviMesh();
	~naviMesh();

	void AddCell(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2);
	void LinkDetection();

	vector<naviCell*> GetNaviMesh() { return _vMesh; }
};

