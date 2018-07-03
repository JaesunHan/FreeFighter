#pragma once
#include "sceneInterface.h"
#include "uiButton.h"

class storeScene : public _scene, public _buttonDelegate
{
private:
	uiButton* _buttons;

public:
	storeScene();
	~storeScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	virtual void OnClick(uiButton* d) override;
};

