#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
	: _width(0)
	, _hpBarFront(NULL)
	, _hpBarBack(NULL)
	, _isHit(false)
{

}


progressBar::~progressBar()
{
	
}

// Ű�� , ���ϰ�� (ù .\\���� �ȵ�) , �����̸� (ù \\���� �ȵ�) , �������� , maxHp
void progressBar::Init(wstring keyName, wstring filePath, wstring fileName, wstring fileForm , float maxHp)
{
	_isHit = false;
	_currentHp = _maxHp = maxHp;

	_currentTime = 0.0f;
	_totalTime = 1.5f;

	// ü�¹� , texture , hpBar , ���� ex) .bmp, .png
	wstring backKey		= keyName + _T("Back");
	wstring halfKey		= keyName + _T("Half");
	wstring almostKey	= keyName + _T("Almost");
	wstring frontKey	= keyName + _T("Front");

	wstring backFile	= _T(".\\") + filePath + _T("\\") + fileName + _T("Back") + fileForm;
	wstring halfFile	= _T(".\\") + filePath + _T("\\") + fileName + _T("_50%") + fileForm;
	wstring almostFile	= _T(".\\") + filePath + _T("\\") + fileName + _T("_25%") + fileForm;
	wstring frontFile	= _T(".\\") + filePath + _T("\\") + fileName + _T("Front") + fileForm;

	_hpBarBack		= IMAGEMANAGER->addImage(backKey, backFile.c_str());
	_hpBarHalf		= IMAGEMANAGER->addImage(halfKey, halfFile.c_str());
	_hpBarAlmost	= IMAGEMANAGER->addImage(almostKey, almostFile.c_str());
	_hpBarFront		= IMAGEMANAGER->addImage(frontKey, frontFile.c_str());

	if (_hpBarFront)
	{
		_width = _hpBarFront->getWidth();
		_maxWidth = _width;
	}
		
}

void progressBar::Update(float currentGauge)
{
	// t = ���� �ð� / ��Ż �ð�
	// from = ������ġ, to = ������ġ
	// (1 - t) * from + t * to;

	if (currentGauge != _currentHp)
	{
		_isHit = true;
		_currentTime = 0.0f;
		_currentHp = currentGauge;
		_fromGauge = _width;
		_toGauge = (_currentHp / _maxHp) * _hpBarFront->getWidth();
	}

	if (_isHit)
	{
		_currentTime += TIMEMANAGER->getElapsedTime();
		float t = _currentTime / _totalTime;

		if (_currentTime > _totalTime)
		{
			_isHit = false;
			_currentHp = currentGauge;
			_currentTime = 0.0f;
		}		
		else
			_width = (1 - t) * _fromGauge + t * _toGauge;
	}
	else
		_currentTime = 0.0f;

	// �� ��¥ ���� �� ���ư��µ� �� ���ư����� �𸣰��� ���� ­�µ� ���� ���������� (����)
	//if (_hpBarFront)
	//{
	//	float currentTime = TIMEMANAGER->getElapsedTime();
	//	float totalTime = 1.0f;
	//	float t = currentTime / totalTime;
	//	float from = _width;
	//	float to = (currentGauge / maxGauge) * _hpBarFront->getWidth();
	//
	//	if (t < totalTime)
	//		_width = (1 - t) * from + t * to;
	//}
	
	if (_width <= 0) _width = 0;
}


void progressBar::Render(float x, float y)
{
	if (_hpBarBack)
		_hpBarBack->render(x, y, 0, 0, _hpBarBack->getWidth(), _hpBarBack->getHeight());

	if (_hpBarFront)
	{
		if (_width / _maxWidth * 100 > 50.0f)
			_hpBarFront->render(x, y, 0, 0, _width, _hpBarFront->getHeight());
		else if (_width / _maxWidth * 100 > 25.0f)
			_hpBarHalf->render(x, y, 0, 0, _width, _hpBarFront->getHeight());
		else
			_hpBarAlmost->render(x, y, 0, 0, _width, _hpBarFront->getHeight());
	}
		
}

void progressBar::Render(float x, float y, D3DXVECTOR3 sca)
{
	if (_hpBarBack)
		_hpBarBack->render(x, y, 0, 0, _hpBarBack->getWidth(), _hpBarBack->getHeight(), sca);

	if (_hpBarFront)
	{
		if (_width / _maxWidth * 100 > 50.0f)
			_hpBarFront->render(x, y, 0, 0, _width, _hpBarFront->getHeight(), sca);
		else if (_width / _maxWidth * 100 > 25.0f)
			_hpBarHalf->render(x, y, 0, 0, _width, _hpBarFront->getHeight(), sca);
		else
			_hpBarAlmost->render(x, y, 0, 0, _width, _hpBarFront->getHeight(), sca);
	}
}

void progressBar::Render(D3DXVECTOR3 dest)
{
	D3DXVECTOR2 realDest = get3Dto2D(dest);

	if (_hpBarBack)
		_hpBarBack->render(realDest.x, realDest.y, 0, 0, _hpBarBack->getWidth(), _hpBarBack->getHeight());

	if (_hpBarFront)
	{
		if (_width / _maxWidth * 100 > 50.0f)
			_hpBarFront->render(realDest.x, realDest.y, 0, 0, _width, _hpBarFront->getHeight());
		else if (_width / _maxWidth * 100 > 25.0f)
			_hpBarHalf->render(realDest.x, realDest.y, 0, 0, _width, _hpBarFront->getHeight());
		else
			_hpBarAlmost->render(realDest.x, realDest.y, 0, 0, _width, _hpBarFront->getHeight());
	}
}

void progressBar::Render(D3DXVECTOR3 dest, D3DXVECTOR3 sca)
{
	D3DXVECTOR2 realDest = get3Dto2D(dest);

	if (_hpBarBack)
		_hpBarBack->render(realDest.x, realDest.y, 0, 0, _hpBarBack->getWidth(), _hpBarBack->getHeight(), sca);

	if (_hpBarFront)
	{
		if (_width / _maxWidth * 100 > 50.0f)
			_hpBarFront->render(realDest.x, realDest.y, 0, 0, _width, _hpBarFront->getHeight(), sca);
		else if (_width / _maxWidth * 100 > 25.0f)
			_hpBarHalf->render(realDest.x, realDest.y, 0, 0, _width, _hpBarFront->getHeight(), sca);
		else
			_hpBarAlmost->render(realDest.x, realDest.y, 0, 0, _width, _hpBarFront->getHeight(), sca);
	}
}


