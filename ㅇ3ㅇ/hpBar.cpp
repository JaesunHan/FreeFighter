#include "stdafx.h"
#include "hpBar.h"


hpBar::hpBar()
{
}


hpBar::~hpBar()
{
}

void hpBar::Init(wstring keyName, wstring filePath, wstring fileName, D3DXCOLOR startColor, D3DXCOLOR endColor)
{
	wstring file = filePath + fileName;
	_keyName = keyName;

	_startColor = startColor;
	_currentColor = _startColor;
	_endColor = endColor;

	IMAGEMANAGER->addImage(_keyName, file.c_str());

	_width = IMAGEMANAGER->findImage(_keyName)->getWidth();
}

void hpBar::Update(float currentHp, float maxHp)
{
	float current = currentHp / maxHp;
	_currentColor = (1 - current) * _endColor + current * _startColor;

	float currentTime = TIMEMANAGER->getElapsedTime();
	float totalTime = 0.5f;
	float t = currentTime / totalTime;
	float from = _width;
	float to = (currentHp / maxHp) * IMAGEMANAGER->findImage(_keyName)->getWidth();

	_width = (1 - t) * from + t * to;

	if (_width <= 0) _width = 0;
}

void hpBar::Render(float x, float y, D3DXVECTOR3 sca)
{
	IMAGEMANAGER->findImage(_keyName)->render(x, y, 0, 0,
		IMAGEMANAGER->findImage(_keyName)->getWidth(),
		IMAGEMANAGER->findImage(_keyName)->getHeight(), sca);

	IMAGEMANAGER->findImage(_keyName)->render(x, y, 0, 0,
		_width,
		IMAGEMANAGER->findImage(_keyName)->getHeight(),
		sca, _currentColor);
}

void hpBar::Render(D3DXVECTOR3 pos, D3DXVECTOR3 sca)
{
	D3DXVECTOR2 v2Temp = get3Dto2D(pos);

	IMAGEMANAGER->findImage(_keyName)->render(v2Temp.x, v2Temp.y, 0, 0,
		IMAGEMANAGER->findImage(_keyName)->getWidth(),
		IMAGEMANAGER->findImage(_keyName)->getHeight(), sca);

	IMAGEMANAGER->findImage(_keyName)->render(v2Temp.x, v2Temp.y, 0, 0,
		_width,
		IMAGEMANAGER->findImage(_keyName)->getHeight(),
		sca, _currentColor);
}
