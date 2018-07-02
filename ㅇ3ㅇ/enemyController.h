#pragma once

class enemyController
{
protected:
	int _speed;

	D3DXMATRIX	_localTM;
	D3DXVECTOR3 _localPos;

	D3DXMATRIX	_worldTM;
	D3DXVECTOR3 _worldPos;
	D3DXVECTOR3 _worldDir;

	D3DXVECTOR3* _targetPos;

public:
	enemyController();
	~enemyController();

	virtual void Moving();

	void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	D3DXVECTOR3 GetPosition() { return _worldPos; }
};

