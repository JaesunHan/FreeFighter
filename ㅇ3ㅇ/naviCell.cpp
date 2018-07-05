#include "stdafx.h"
#include "naviCell.h"


naviCell::naviCell()
{
}


naviCell::~naviCell()
{
}

void naviCell::Init(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2)
{
	_attribute = "";

	_vertex.push_back(v0);
	_vertex.push_back(v1);
	_vertex.push_back(v2);

	_triCenter = (_vertex[0] + _vertex[1] + _vertex[2]) / 3;

	_verMid.push_back((v0 - v1) / 2);
	_verMid.push_back((v0 - v2) / 2);
	_verMid.push_back((v1 - v2) / 2);

	_triVerMidInterval.push_back(_verMid[0] - _triCenter);
	_triVerMidInterval.push_back(_verMid[1] - _triCenter);
	_triVerMidInterval.push_back(_verMid[2] - _triCenter);
}
