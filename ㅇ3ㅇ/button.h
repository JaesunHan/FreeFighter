#pragma once

class button
{
private:
#ifdef UNICODE
	wstring			_buttonName;
#else
	string			_buttonName;
#endif

	RECT			_buttonRc;
	bool			_isSelected;
	D3DXVECTOR3		_pos;
	float			_width, _height;
	LPD3DXSPRITE	_sprite;

public:
	button();
	~button();

#ifdef UNICODE
	HRESULT init(wstring buttonName, wstring fileName, float x, float y);
#else
	HRESULT init(string buttonName, string fileName, float x, float y);
#endif
	void release();
	void update();
	void render();
};

