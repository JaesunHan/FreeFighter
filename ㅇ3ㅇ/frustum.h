#pragma once

#include <vector>
using namespace std;

class frustum
{
private:
	vector<D3DXVECTOR3>		_vProjVertex;
	vector<D3DXVECTOR3>		_vWorldVertex;
	vector<D3DXPLANE>		_vPlane;

public:
	frustum();
	~frustum();

	HRESULT init();
	void release();
	void update();
	bool isIn(tagSphere* s);
};

