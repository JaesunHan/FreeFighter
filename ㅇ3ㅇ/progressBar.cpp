#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{

}


progressBar::~progressBar()
{

}

void progressBar::Init()
{
	_hpBarBack = IMAGEMANAGER->addImage(NULL, _T(".\\texture\\hpBarBack.bmp"));
	_hpBarFront = IMAGEMANAGER->addImage(NULL, _T(".\\texture\\hpBarFront.bmp"));

	_width = _hpBarFront->getFrameWidth();
}

void progressBar::Update(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _hpBarFront->getWidth();
}

void progressBar::Render(float x , float y)
{
	if (_hpBarBack)
		_hpBarBack->render(x, y, 0, 0, _hpBarBack->getFrameWidth(), _hpBarBack->getFrameHeight());

	if (_hpBarFront)
		_hpBarFront->render(x, y, 0, 0, _width, _hpBarFront->getFrameHeight());
}

