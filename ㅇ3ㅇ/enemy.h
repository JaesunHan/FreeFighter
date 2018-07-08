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
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void AnimationSetting() = 0;

	virtual void SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos);
	virtual void SetDistance(float dis);

	virtual bool YouAndIDistance();
	virtual float YouAndIDistance(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02);

	virtual void EnemyAI() = 0;

};

