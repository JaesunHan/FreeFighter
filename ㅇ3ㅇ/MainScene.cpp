#include "stdafx.h"
#include "MainScene.h"
#include "uiButton.h"


MainScene::MainScene()
	: _currentX(0)
	, _frameCount(0)
{
}


MainScene::~MainScene()
{
}

HRESULT MainScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	uiButton* testButton = new uiButton;
	testButton->init(_T("testButton"), _T(".\\texture\\testButton.png"), vp.Width / 2, vp.Height / 2);

	_buttons.push_back(testButton);

	testButton = new uiButton;
	testButton->init(_T("test"), _T(".\\texture\\test.png"), vp.Width / 2, vp.Height / 2 + 70);

	_buttons.push_back(testButton);

	IMAGEMANAGER->addFrameImage(_T("testFrameImage"), _T(".\\texture\\testFrameImage.bmp"), 11, 2);
	_currentX = 0;
	_frameCount = 0;

	return S_OK;
}

void MainScene::update()
{
	for (int i = 0; i < _buttons.size(); ++i)
		_buttons[i]->update();

	_frameCount++;
	if (_frameCount % 5 == 0)
	{
		_currentX++;
		if (_currentX >= IMAGEMANAGER->findImage(_T("testFrameImage"))->getMaxFrameX())
			_currentX = 0;
	}
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

	IMAGEMANAGER->findImage(_T("testFrameImage"))->frameRender(100, 100, _currentX, 0);
}
