#pragma once
#include "cubeNode.h"

class cubeHead : public cubeNode
{
private:
	float _headAngle;

	GO_DIRECTION	_go;

public:
	cubeHead();
	~cubeHead();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	inline void setGoDir(GO_DIRECTION go) { _go = go; }
};

