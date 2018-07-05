#pragma once
#include "interfaceCharacter.h"
#include "enemyController.h"

class enemy : public interfaceCharacter, public enemyController
{
protected:
	enum Kinds
	{
		ENEMY_NONE = -1,
		ENEMY_DARKWOLF,
		ENEMY_WOODGIANT,
		ENEMY_ORCFOREMAN,
		ENEMY_END
	};

	Kinds _kinds;
	float _distance;

protected:
	struct tagSphere
	{
		D3DXVECTOR3 center;
		float radius;
	};

	tagSphere _sphere;
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render();

	virtual void SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos);
	virtual void SetDistance(float dis);

	virtual bool YouAndIDistance();
	virtual float YouAndIDistance(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02);

	virtual void EnemyAI() = 0;

};

