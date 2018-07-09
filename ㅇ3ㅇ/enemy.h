#pragma once
#include "interfaceCharacter.h"
#include "enemyController.h"


class enemy : public interfaceCharacter
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

	Kinds	_kinds;
	float	_distance;
	bool	_isCollision;
	
public:
	enemy();
	virtual ~enemy();

	virtual bool GetIsCollision() { return _isCollision; }
	virtual void SetIsCollisionCheck(bool cheak) { _isCollision = cheak; }

	// interfaceCharacter을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render() override;

	//말 그대로 에너미 움직임
	virtual void Moving();

	//애니메이션 셋팅
	virtual void AnimationSetting() = 0;

	//거리설정
	virtual void SetDistance(float dis) { _distance = dis; }
	//타겟과 적의거리가 디스턴스보다 작으면 트루
	virtual bool YouAndIDistance();

	// (~~~)거리 1과 2 사이의 거리를 반환
	static float YouAndIDistance(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02);
	//에너미 1과 2를 비교해서 더 앞에 있는 (플레이어와 가까운) 에너미를 반환
	static enemy* Collision(D3DXVECTOR3* target, enemy* v1, enemy* v2);

	//에이스타
	virtual void EnemyAI() = 0;

};

