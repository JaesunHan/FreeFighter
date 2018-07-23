#pragma once
#include "interfaceCharacter.h"

class playerManager;
class enemyManager;
class stateContext;
class hpBar;

// ����
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
	Kinds			_kinds;			// ���ʹ� ����

	D3DXVECTOR3*	_targetPos;		// �Ѿư� Ÿ��
	D3DXVECTOR3		_respawnPos;	// �¾ ��ġ

	float			_correctionAngle;	// ������
	bool			_isAppear;			// ���������

	int				_damagedCount;

	float			_damagedSpeed;

protected:
	// AI ����
	enum enemyState
	{
		ENEMY_STATE_NONE   = -1,
		ENEMY_STATE_APPEAR	= 0,
		ENEMY_STATE_WAIT	= 1,
		ENEMY_STATE_DOING	= 2,
		ENEMY_STATE_END
	};

	float		_atkDistance;		//���ݸ�� ���ϸ� ~�Ÿ� �տ�
	float		_hitRange;			//~ũ�⸸ŭ ��Ʈ�ڽ� ����

	enemyState	_enemyState;		// ���ʹ� ���� ����
	int			_RndCount;			// ���� ī��Ʈ
	int			_changeCount;		// ����� �ٲ� ���� ī��Ʈ
	int			_disappearCount;	// ���� ���ʹ̰� ������µ� ���ð�
	float		_atkRange;			// ���ݹ���
	float		_actRange;			// �ൿ����
	bool		_isOutOfRange;		// ���� �ۿ� �ִ�?

	enemyManager* _em;				// ������
	stateContext* _currentState;	// ��������
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Init(wstring keyPath, wstring keyName, int stage);
	virtual void Update() override;
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;
	virtual void SetParticle();

	virtual void HitDamage(float damage) override;

	virtual float GetAtkDistance() { return _atkDistance; }	//���ݸ�� ���ϸ� ~�Ÿ� �տ�
	virtual float GetHitRange() { return _hitRange; }		//~ũ�⸸ŭ ��Ʈ�ڽ� ����

	// ���ʹ����� 
	// ���ݼ���
	virtual tagCharStatus GetStatus() { return _status; }
	virtual void SetStatus(int stage);
	// Ÿ�ټ���
	virtual D3DXVECTOR3* GetTarget() { return _targetPos; }
	virtual void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	virtual void SetTarget(playerManager* pm);
	// ��������ġ����
	virtual D3DXVECTOR3 GetRespawnPos() { return _respawnPos; }
	virtual void SetRespawnPos(D3DXVECTOR3 pos) { _respawnPos = pos; }
	// ����
	virtual Kinds GetKind() { return _kinds; }
	// ������� ī��Ʈ
	virtual int GetDisappearCount() { return _disappearCount; }
	virtual void SetDisappearCount(float t = 1.0f) { _disappearCount += t; }
	// ��������� (�߰����� �����ְ� ������ ���� �Ұ�)
	virtual bool GetIsAppear() { return _isAppear; }

	// ## �� ���� ## 
	// ���� (�ִ¾ִ� ���� ������)
	virtual void Appear();
	// ������
	virtual void Idle();
	// ������-�⺻
	virtual void Moving();
	// ������-����
	virtual void RNDMoving();
	// ������-������ ��ҷ� ���ư���
	virtual void GoHome();
	// �ǰ� (����)
	virtual void Damage();
	// �ǰ� (�ǰݵǰ� �⺻���·� ���ƿ��� ����)
	virtual void Recovery();
	// ����
	virtual void Death();
	// ����
	virtual void Attack01();
	virtual void Attack02();
	virtual void Attack03();

	// �׾�����
	virtual bool GetIsDead() { return _isDead; }
	// �׾����� ( �ִϸ��̼� �� )
	virtual bool GetIsDeadAnimationEnd();

	// ���������� (�� ����)
	virtual bool RespawnRange(float range = 5.0f);
	// ���ݹ��� 
	virtual bool AttackRange();
	// �ൿ����
	virtual bool ActionRange();

	// ���ʹ� ������ �Ÿ� ( ���߿� �����Ҷ� ��ġ�°� ���� )
	virtual bool BetweenEnemyDistance(D3DXVECTOR3 cheakPos, D3DXVECTOR3 makingPos, float range = 1.0f);

	virtual void EnemyStoryAI();
	virtual void EnemyFightAI();

	inline void setEmMemory(enemyManager* em) { _em = em; }

};

