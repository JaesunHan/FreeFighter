#pragma once
#include "sceneInterface.h"

class storyScene : public _scene
{
public:
	storyScene();
	~storyScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
};

