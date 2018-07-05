#pragma once
#include "sceneInterface.h"

class fightScene : public _scene
{
public:
	fightScene();
	~fightScene();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
};

