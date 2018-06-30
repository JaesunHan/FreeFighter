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

	void init();
	void release();
	void render();
};

