#pragma once

class progressBar
{
private:
	wstring	_keyName;

	float	_maxWidth;
	float	_width;

	float	_fromGauge;		//현재 체력바 위치
	float	_toGauge;		//도착할 체력바 위치

	float	_maxHp;			//총 체력
	float	_currentHp;		//현제 체력

	float	_isHit;			//맞았냐
	float	_currentTime;	//현재시간
	float	_totalTime;		//총시간

	image*	_hpBarBack;
	image*	_hpBarHalf;
	image*  _hpBarAlmost;
	image*	_hpBarFront;

public:
	progressBar();
	~progressBar();

	void Init(wstring keyName, wstring filePath, wstring fileName, wstring fileForm , float maxHp);
	void Update(float currentGauge);
	void Render(float x, float y);
	void Render(float x, float y, D3DXVECTOR3 sca);
	void Render(D3DXVECTOR3 dest);
	void Render(D3DXVECTOR3 dest, D3DXVECTOR3 sca);

	wstring GetProgressBarKey() { return _keyName; }
};

