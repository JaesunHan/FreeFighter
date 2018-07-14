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

	Kinds	_kinds;				//���ʹ� �Ӽ�
	float	_distance;

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

	enemyManager* _em;				// ������
	stateContext* _currentState;	// ��������
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime()) override;

	// ������� ī��Ʈ
	int GetDisappearCount() { return _disappearCount; }
	void SetDisappearCount(float t = 1.0f) { _disappearCount += t; }

	// ## �� ���� ## 
	// ������
	virtual void Idle();
	// ������
	virtual void Moving();
	// �ǰ�
	virtual void Damage();
	// ����
	virtual void Death();
	// ����
	virtual void Attack01();
	virtual void Attack02();
	virtual void Attack03();

	// �׾����� ( ���ϸ��̼� ���� )
	virtual bool GetIsDead() { return _isDead; }
	// �׾����� ( �ִϸ��̼� �� )
	virtual bool GetIsDeadAnimationEnd();

	//Ÿ�ٰ� ���ǰŸ��� ���Ͻ����� ������ Ʈ��
	virtual bool YouAndIDistance();

	virtual void EnemyStoryAI();
	virtual void EnemyFightAI();

	inline void setEmMemory(enemyManager* em) { _em = em; }

};

