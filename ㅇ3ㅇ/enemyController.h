#pragma once

class enemyController
{
protected:
	D3DXMATRIX	_localTM;
	D3DXVECTOR3 _localPos;

	D3DXMATRIX	_worldTM;
	D3DXVECTOR3 _worldPos;
	D3DXVECTOR3 _worldDir;

	D3DXVECTOR3* _targetPos;

public:
	enemyController();
	~enemyController();

	virtual void EnemyAI() = 0;
	virtual bool YouAndMeDistance(D3DXVECTOR3 playerPos, float num) = 0;
};

