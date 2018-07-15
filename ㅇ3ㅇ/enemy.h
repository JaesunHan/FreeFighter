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
	Kinds	_kinds;				// ���ʹ� �Ӽ�

	D3DXVECTOR3*	_targetPos;		// �Ѿư� Ÿ��
	D3DXVECTOR3		_respawnPos;	// �¾ ��ġ

protected:
	// AI�� �� ������
	enum enemyState
	{
		ENEMY_STATE_NONE = -1,
		ENEMY_STATE_WAIT,
		ENEMY_STATE_DOING,
		ENEMY_STATE_END
	};
	enemyState	_enemyState;		// ���ʹ� ���� ����
	int			_RndCount;			// ���� ī��Ʈ
	int			_disappearCount;	// ���� ���ʹ̰� ������µ� ���ð�
	float		_atkRange;			// ���ݹ���
	float		_actRange;			// �ൿ����

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

	// ���ʹ����� 
	// ���ݼ���
	virtual tagCharStatus GetStatus() { return _status; }
	virtual void SetStatus(int stage);
	// Ÿ�ټ���
	virtual D3DXVECTOR3* GetTarget() { return _targetPos; }
	virtual void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	// ��������ġ����
	virtual D3DXVECTOR3 GetRespawnPos() { return _respawnPos; }
	virtual void SetRespawnPos(D3DXVECTOR3 pos) { _respawnPos = pos; }
	// ����
	virtual Kinds GetKind() { return _kinds; }
	
	// ��Ʈ �����
	virtual void HitDamage(float damage = 0) override;

	// ������� ī��Ʈ
	virtual int GetDisappearCount() { return _disappearCount; }
	virtual void SetDisappearCount(float t = 1.0f) { _disappearCount += t; }

	// ## �� ���� ## 
	// ������
	virtual void Idle();
	// ������-�⺻
	virtual void Moving();
	// ������-������ ��ҷ� ���ư���
	virtual void GoHome();
	// �ǰ�
	virtual void Damage();
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

	// ����������
	virtual bool WithinRespawnRange();
	// ���ݹ��� 
	virtual bool WithinAttackRange();
	// �ൿ����
	virtual bool WithinActionRange();

	// ���ʹ� ������ �Ÿ� ( ���߿� �����Ҷ� ��ġ�°� ���� )
	virtual bool WithinEnemyRange(D3DXVECTOR3 cheakPos, D3DXVECTOR3 makingPos, float range = 1.0f);

	virtual void EnemyStoryAI();
	virtual void EnemyFightAI();

	inline void setEmMemory(enemyManager* em) { _em = em; }

};

