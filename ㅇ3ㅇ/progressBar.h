#pragma once

class progressBar
{
private:
	wstring	_keyName;

	float	_maxWidth;
	float	_width;

	image*	_hpBarBack;
	image*	_hpBarHalf;
	image*  _hpBarAlmost;
	image*	_hpBarFront;

public:
	progressBar();
	~progressBar();

	void Init(wstring keyName, wstring filePath, wstring fileName, wstring fileForm);
	void Update(float currentGauge, float maxGauge);
	void Render(float x, float y);
	void Render(float x, float y, D3DXVECTOR3 sca);

	wstring GetProgressBarKey() { return _keyName; }
};

