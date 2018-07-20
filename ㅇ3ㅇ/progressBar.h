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
	image*	_hpBarHalf;		//얘는 저희 전용입니다. 다른데서 쓰면 터집니다 mayBe
	image*  _hpBarAlmost;	//얘는 저희 전용입니다. 다른데서 쓰면 터집니다 mayBe
	image*	_hpBarFront;

public:
	progressBar();
	~progressBar();

	// 키값 , 파일경로 (첫 .\\쓰면 안됨) , 파일이름 (첫 \\쓰면 안됨) , 파일형식 , maxHp
	void Init(wstring keyName, wstring filePath, wstring fileName, wstring fileForm , float maxHp);
	// 현재 체력
	void Update(float currentGauge);
	void Update(float currentGauge, float maxGauge);
	// 2D상의 좌표 x, y
	void Render(float x, float y);
	void Render(float x, float y, D3DXVECTOR3 sca);
	// 3D좌표 넣으면 알아서 반환됨 함수가 있슴돠
	void Render(D3DXVECTOR3 dest);
	void Render(D3DXVECTOR3 dest, D3DXVECTOR3 sca);

	wstring GetProgressBarKey() { return _keyName; }
};

