#pragma once
#include "sceneInterface.h"
#include "uiButton.h"

class returnScene : public _scene, public _buttonDelegate
{
private:
	uiButton*	_buttons;

public:
	returnScene();
	~returnScene();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void OnClick(uiButton * d) override;
};

