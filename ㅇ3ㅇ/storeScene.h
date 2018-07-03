#pragma once
#include "sceneInterface.h"

class storeScene : public _scene
{
public:
	storeScene();
	~storeScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
};

