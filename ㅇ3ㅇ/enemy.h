#pragma once
#include "interfaceCharacter.h"

class enemyManager;
class stateContext;

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

	Kinds	_kinds;				//에너미 속성
	float	_distance;

protected:
	// AI에 쓸 변수들
	enum enemyState
	{
		ENEMY_STATE_NONE = -1,
		ENEMY_STATE_WAIT,
		ENEMY_STATE_DOING,
		ENEMY_STATE_END
	};
	enemyState	_enemyState;		// 에너미 현재 상태
	int			_RndCount;			// 랜덤 카운트
	int			_disappearCount;	// 죽은 에너미가 사라지는데 대기시간

	enemyManager* _em;				// 형제들
	stateContext* _currentState;	// 상태패턴
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;

	// 사라지는 카운트
	int GetDisappearCount() { return _disappearCount; }
	void SetDisappearCount(float t = 1.0f) { _disappearCount += t; }

	// ## 적 상태 ## 
	// 가만히
	virtual void Idle();
	// 움직임
	virtual void Moving();
	// 피격
	virtual void Damage();
	// 죽음
	virtual void Death();
	// 공격
	virtual void Attack01();
	virtual void Attack02();
	virtual void Attack03();

	// 죽엇을때 ( 에니메이션 시작 )
	virtual bool GetIsDead() { return _isDead; }
	// 죽엇을때 ( 애니메이션 끝 )
	virtual bool GetIsDeadAnimationEnd();

	//타겟과 적의거리가 디스턴스보다 작으면 트루
	virtual bool YouAndIDistance();

	virtual void EnemyStoryAI();
	virtual void EnemyFightAI();

	inline void setEmMemory(enemyManager* em) { _em = em; }

};

