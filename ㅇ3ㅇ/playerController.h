#pragma once


class playerController
{
protected:

	D3DXMATRIX		_localTM;
	D3DXMATRIX		_worldTM;


	D3DXVECTOR3	_localPos;
	D3DXVECTOR3	_worldPos;

	D3DXVECTOR3	_worldScale;
	D3DXVECTOR3	_worldRotation;

	D3DXVECTOR3	_worldDir;

	float _speedPlayer;
	float _RotX;
	float _RotY;
	float _RotZ;

private:



public:
	playerController();
	~playerController();

	void Setup();
	void Update();
	void moving();
	//void changeMotion();


};

