#pragma once

class playerController
{
protected:

	D3DXMATRIX		_localTM;
	D3DXMATRIX		_worldTM;	


	D3DXVECTOR3	_localPos;
	D3DXVECTOR3	_worldPos;

	D3DXVECTOR3	_worldDir;

private:

public:
	playerController();
	~playerController();

	void Setup();
	void Update();


};

