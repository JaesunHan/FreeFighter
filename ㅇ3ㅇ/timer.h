#pragma once
class timer
{
private:
	bool _isHardware;			//하드웨어가 좋은지 여부
	float _timeScale;
	float _timeElapsed;

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSframeCount;

	float _FPSTimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT init(void);
	void tick(float lockFPS = 0.0f);

	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }

#ifdef UNICODE
	unsigned long getFrameRate(WCHAR* str = NULL) const;
#else
	unsigned long getFrameRate(char* str = NULL) const;
#endif

};

