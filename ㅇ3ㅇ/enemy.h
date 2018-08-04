#pragma once
#include "interfaceCharacter.h"

class playerManager;
class enemyManager;
class stateContext;
class hpBar;
class state;

// 종류
enum Kinds
{
	ENEMY_NONE		   = -1,
	ENEMY_DARKWOLF		= 0,
	ENEMY_WOODGIANT		= 1,
	ENEMY_BLOODYQUEEN	= 2,
	ENEMY_DURAHAN		= 3,
	ENEMY_ZAKEN			= 4,
	ENEMY_ANUBIS		= 5,
	ENEMY_MUDGOLEM		= 6,
	ENEMY_DARKLORD		= 7,
	ENEMY_KERBEROS		= 8,
	ENEMY_GARGOYLE		= 9,
	ENEMY_END
};


class enemy : public interfaceCharacter
{
protected:
	hpBar*			_hpBar;

protected:
	Kinds			_kinds;			// 에너미 종류

	D3DXVECTOR3*	_targetPos;		// 쫓아갈 타겟
	D3DXVECTOR3		_respawnPos;	// 태어난 위치

	float			_correctionAngle;	// 보정값
	bool			_isAppear;			// 등장씬인지

	int				_damagedCount;

	float			_damagedSpeed;

protected:
	float		_atkDistance;		//공격모션 취하면 ~거리 앞에
	float		_hitRange;			//~크기만큼 히트박스 생성

	int			_RndCount;			// 랜덤 카운트
	int			_changeCount;		// 모션이 바뀔때 쓰일 카운트
	int			_disappearCount;	// 죽은 에너미가 사라지는데 대기시간
	float		_atkRange;			// 공격범위
	float		_actRange;			// 행동범위
	bool		_isOutOfRange;		// 영역 밖에 있니?

	enemyManager* _em;				// 형제들
	stateContext* _currentState;	// 상태패턴
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter을(를) 통해 상속됨
	//virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Init(wstring keyPath, wstring keyName, int stage);
	virtual void Update() override;
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;
	virtual void SetParticle();

	virtual void HitDamage(float damage) override;

	virtual float GetAtkDistance() { return _atkDistance; }	//공격모션 취하면 ~거리 앞에
	virtual float GetHitRange() { return _hitRange; }		//~크기만큼 히트박스 생성

	// 에너미전용
	// 애니메이션 번호 설정
	void ChangeAct(ACT act)
	{
		if (_AniIndex[act] != -1)
			_nextAct = act;
		else
			_nextAct = ACT_IDLE;

		AnimationSetting();
	}
	ACT GetAct() { return _currentAct; }
	// 스텟설정
	virtual void SetStatus(int stage);

	void createWind();
	// 타겟설정
	virtual D3DXVECTOR3* GetTarget() { return _targetPos; }
	virtual void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	virtual void SetTarget(playerManager* pm);
	// 리스폰위치설정
	virtual D3DXVECTOR3 GetRespawnPos() { return _respawnPos; }
	virtual void SetRespawnPos(D3DXVECTOR3 pos) { _respawnPos = pos; }
	// 종류
	virtual Kinds GetKind() { return _kinds; }
	// 사라지는 카운트
	virtual int GetDisappearCount() { return _disappearCount; }
	virtual void SetDisappearCount(float t = 1.0f) { _disappearCount += t; }
	// 등장씬인지 (중간보스 위엄있게 등장을 위한 불값)
	virtual bool GetIsAppear() { return _isAppear; }
	virtual void SetIsAppear(bool b) { _isAppear = b; }
	// 컨트롤러 삭제
	virtual void DestoryPhysX()
	{
		_controller->release();
		_controller = NULL;
	}

	//스킬
	virtual void UseSkill01();
	virtual void UseSkill02();
	virtual void UseSkill03();

	// 죽엇을때
	// 죽엇을때 ( 애니메이션 끝 )
	virtual bool GetIsDeadAnimationEnd();

	// 리스폰범위 (집 영역)
	virtual bool RespawnRange(float range = 5.0f);
	// 공격범위 
	virtual bool AttackRange();
	// 행동범위
	virtual bool ActionRange();

	// 에너미 사이의 거리 ( 나중에 생성할때 곂치는거 방지 )
	virtual bool BetweenEnemyDistance(D3DXVECTOR3 cheakPos, D3DXVECTOR3 makingPos, float range = 1.0f);

	virtual void EnemyStoryAI();
	virtual void EnemyFightAI();

	inline void setEmMemory(enemyManager* em) { _em = em; }
	virtual bool isAnimationEnd();

	virtual void setState(state* s);
};

