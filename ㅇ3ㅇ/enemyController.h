#pragma once

class enemyController
{
protected:
	float _speed;

	D3DXMATRIX	_localTM;
	D3DXVECTOR3 _localPos;

	D3DXMATRIX	_worldTM;
	D3DXVECTOR3 _worldSca;
	D3DXVECTOR3 _worldRot;
	D3DXVECTOR3 _worldPos;
	D3DXVECTOR3 _worldDir;

	D3DXVECTOR3* _targetPos;

public:
	enemyController();
	virtual ~enemyController();

	virtual void Moving();

	void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	void SetPosition(D3DXVECTOR3 pos) { _worldPos = pos; }
	void SetPosition(float x, float y, float z) { _worldPos = D3DXVECTOR3(x, y, z); }
	D3DXVECTOR3 GetPosition() { return _worldPos; }
};

