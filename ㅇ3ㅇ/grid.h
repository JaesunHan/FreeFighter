#pragma once
#include <vector>

class grid
{
private:
	vector<tagPC_Vertex> _grid;
	vector<tagPC_Vertex> _vLine;

public:
	grid();
	~grid();

	void init(D3DXCOLOR color = WHITE, int numOfLines = 10, float y = 3.0f);
	void release();
	void render();
};

