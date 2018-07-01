#pragma once

#include <vector>
using namespace std;

#include "sceneInterface.h"

class button;

class MainScene : public iScene
{
private:
	vector<button*> _buttons;

public:
	MainScene();
	~MainScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
};

