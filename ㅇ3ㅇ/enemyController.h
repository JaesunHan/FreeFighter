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

	virtual void Init();
	virtual void Moving();

	virtual float GetSpeed() { return _speed; }
	virtual void SetSpeed(float speed) { _speed = speed; }
	virtual void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	virtual void SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos) 
	{ 
		_worldSca = sca;
		_worldRot = rot;
		_worldPos = pos;
		Init();
	}
	virtual void SetPosition(D3DXVECTOR3 pos) { _worldPos = pos; Init(); }
	virtual void SetPosition(float x, float y, float z) { _worldPos = D3DXVECTOR3(x, y, z); Init(); }
	virtual D3DXVECTOR3 GetPosition() { return _worldPos; }
};

