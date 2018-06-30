#pragma once
#include "cubeNode.h"

class cubeLeg : public cubeNode
{
private:
	bool _isLeft;

	float _angle;
	float _realAngle;

	GO_DIRECTION	_go;

public:
	cubeLeg();
	~cubeLeg();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	inline void setIsLeft(bool l) { _isLeft = l; }
	inline void setGoDir(GO_DIRECTION go) { _go = go; }
};

