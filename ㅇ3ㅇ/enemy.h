#pragma once
#include "interfaceCharacter.h"

class enemyManager;
class stateContext;

enum Kinds
{
	ENEMY_NONE = -1,
	ENEMY_DARKWOLF,
	ENEMY_WOODGIANT,
	ENEMY_ORCFOREMAN,
	ENEMY_END
};

class enemy : public interfaceCharacter
{
protected:
	Kinds	_kinds;				// 에너미 속성

	D3DXVECTOR3*	_targetPos;		// 쫓아갈 타겟
	D3DXVECTOR3		_respawnPos;	// 태어난 위치

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
	float		_atkRange;			// 공격범위
	float		_actRange;			// 행동범위

	enemyManager* _em;				// 형제들
	stateContext* _currentState;	// 상태패턴
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Init(wstring keyPath, wstring keyName, int stage);
	virtual void Update() override;
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;

	// 에너미전용 
	// 스텟설정
	virtual tagCharStatus GetStatus() { return _status; }
	virtual void SetStatus(int stage);
	// 타겟설정
	virtual D3DXVECTOR3* GetTarget() { return _targetPos; }
	virtual void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	// 리스폰위치설정
	virtual D3DXVECTOR3 GetRespawnPos() { return _respawnPos; }
	virtual void SetRespawnPos(D3DXVECTOR3 pos) { _respawnPos = pos; }
	// 종류
	virtual Kinds GetKind() { return _kinds; }
	
	// 히트 대미지
	virtual void HitDamage(float damage = 0) override;

	// 사라지는 카운트
	virtual int GetDisappearCount() { return _disappearCount; }
	virtual void SetDisappearCount(float t = 1.0f) { _disappearCount += t; }

	// ## 적 상태 ## 
	// 가만히
	virtual void Idle();
	// 움직임-기본
	virtual void Moving();
	// 움직임-지정된 장소로 돌아가는
	virtual void GoHome();
	// 피격
	virtual void Damage();
	// 죽음
	virtual void Death();
	// 공격
	virtual void Attack01();
	virtual void Attack02();
	virtual void Attack03();

	// 죽엇을때
	virtual bool GetIsDead() { return _isDead; }
	// 죽엇을때 ( 애니메이션 끝 )
	virtual bool GetIsDeadAnimationEnd();

	// 리스폰범위
	virtual bool WithinRespawnRange();
	// 공격범위 
	virtual bool WithinAttackRange();
	// 행동범위
	virtual bool WithinActionRange();

	// 에너미 사이의 거리 ( 나중에 생성할때 곂치는거 방지 )
	virtual bool WithinEnemyRange(D3DXVECTOR3 cheakPos, D3DXVECTOR3 makingPos, float range = 1.0f);

	virtual void EnemyStoryAI();
	virtual void EnemyFightAI();

	inline void setEmMemory(enemyManager* em) { _em = em; }

};

