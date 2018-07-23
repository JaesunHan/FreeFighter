#pragma once
class hpBar
{
private:
	wstring _keyName;

	D3DXCOLOR _startColor;
	D3DXCOLOR _currentColor;
	D3DXCOLOR _endColor;

	float _width;

	image* _hpBar;

public:
	hpBar();
	~hpBar();

	//키값, 경로, 이름, 시작컬러, 끝컬러
	void Init(wstring keyName, wstring filePath, wstring fileName, D3DXCOLOR startColor, D3DXCOLOR endColor);
	void Update(float currentHp, float maxHp);
	void Render(float x, float y, D3DXVECTOR3 sca = D3DXVECTOR3(1, 1, 1));
	void Render(D3DXVECTOR3 pos, D3DXVECTOR3 sca = D3DXVECTOR3(1, 1, 1));

	wstring GetKeyName() { return _keyName; }
};

