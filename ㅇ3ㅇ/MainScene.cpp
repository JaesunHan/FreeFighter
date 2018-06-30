#include "stdafx.h"
#include "MainScene.h"
#include "button.h"


MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

HRESULT MainScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	button* testButton = new button;
	testButton->init(_T("testButton"), _T(".\\texture\\testButton.png"), vp.Width / 2, vp.Height / 2);

	_buttons.push_back(testButton);

	testButton = new button;
	testButton->init(_T("test"), _T(".\\texture\\test.png"), vp.Width / 2, vp.Height / 2 + 70);

	_buttons.push_back(testButton);

	return S_OK;
}

void MainScene::update()
{
	for (int i = 0; i < _buttons.size(); ++i)
		_buttons[i]->update();
}

void MainScene::release()
{
	for (int i = 0; i < _buttons.size(); ++i)
		SAFE_OBJRELEASE(_buttons[i]);

	_buttons.clear();
}

void MainScene::render()
{
	for (int i = 0; i < _buttons.size(); ++i)
		_buttons[i]->render();
}
