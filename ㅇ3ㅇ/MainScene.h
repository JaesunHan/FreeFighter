#pragma once

#include <vector>
using namespace std;

#include "sceneInterface.h"

class uiButton;

class MainScene : public _scene
{
private:
	vector<uiButton*> _buttons;

	int _currentX;
	int _frameCount;

public:
	MainScene();
	~MainScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
};

