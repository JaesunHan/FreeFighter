#pragma once

class progressBar
{
private:
	wstring	_keyName;

	float	_width;
	image*	_hpBarFront;
	image*	_hpBarBack;

public:
	progressBar();
	~progressBar();

	void Init();
	void Update(float currentGauge, float maxGauge);
	void Render(float x, float y);

	wstring GetProgressBarKey() { return _keyName; }
};

