#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{

}


progressBar::~progressBar()
{

}

void progressBar::Init(wstring hpBarBackKeyName, wstring hpBarBackFilePath, wstring hpBarBackFileName,
	wstring hpBarFrontKeyName, wstring hpBarFrontFilePath, wstring hpBarFrontFileName)
{
	wstring backFile = hpBarBackFilePath + hpBarBackFileName;
	wstring frontFile = hpBarFrontFilePath + hpBarFrontFileName;

	_hpBarBack = IMAGEMANAGER->addImage(hpBarBackKeyName, backFile.c_str());
	_hpBarFront = IMAGEMANAGER->addImage(hpBarFrontKeyName, frontFile.c_str());

	if (_hpBarFront)
		_width = _hpBarFront->getFrameWidth();
}

void progressBar::Update(float currentGauge, float maxGauge)
{
	if (_hpBarFront)
		_width = (currentGauge / maxGauge) * _hpBarFront->getWidth();
}

void progressBar::Render(float x , float y)
{
	if (_hpBarBack)
		_hpBarBack->render(x, y, 0, 0, _hpBarBack->getFrameWidth(), _hpBarBack->getFrameHeight());

	if (_hpBarFront)
		_hpBarFront->render(x, y, 0, 0, _width, _hpBarFront->getFrameHeight());
}

