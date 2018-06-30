#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{

}

HRESULT timeManager::init(void)		
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)		
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

#ifdef UNICODE
void timeManager::render(HDC hdc)
{
	WCHAR str[256];
	string frameRate;
	//font ��׶��� ���� 2���� �ִ�
	//TRANSPARENT : ����
	//OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);


#ifdef _DEBUG
	{
		wsprintf(str, L"framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, wcslen(str));

		swprintf_s(str, L"worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, wcslen(str));

		swprintf_s(str, L"elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, wcslen(str));
	}
#else
	{
		wsprintf(str, L"framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif

}
#else
void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;
	//font ��׶��� ���� 2���� �ִ�
	//TRANSPARENT : ����
	//OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);


#ifdef _DEBUG
	{
		sprintf(str, "framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	{
		sprintf(str, "framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif

}
#endif
