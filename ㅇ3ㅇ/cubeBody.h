#pragma once
#include "cubeNode.h"

class cubeBody : public cubeNode
{
public:
	cubeBody();
	~cubeBody();

	virtual void init() override;
	virtual void render() override;
};

