#pragma once
#include "interfaceCharacter.h"


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

	bool	_motionChange;
	Kinds	_kinds;		//���ʹ� �Ӽ�
	float	_distance;	//�Ÿ����ε� ���� ���� �𸣰���

protected:
	// AI�� �� ������
	enum enemyState
	{
		ENEMY_STATE_NONE = -1,
		ENEMY_STATE_WAIT,
		ENEMY_STATE_DOING,
		ENEMY_STATE_END
	};

	int			_RndCount;		//����ī��Ʈ
	enemyState	_enemyState;	//���ʹ� ���� ����
	
public:
	enemy();
	virtual ~enemy();

	// interfaceCharacter��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render() override;

	//�������� ���� ���ݼ����ε� �ϴ� ����
	virtual void SetStatus(int num);

	//�� �״�� ���ʹ� ������
	virtual void Moving();

	//�Ÿ�����
	virtual void SetDistance(float dis) { _distance = dis; }
	//Ÿ�ٰ� ���ǰŸ��� ���Ͻ����� ������ Ʈ��
	virtual bool YouAndIDistance();

	// (~~~)�Ÿ� 1�� 2 ������ �Ÿ��� ��ȯ
	static float YouAndIDistance(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02);
	//���ʹ� 1�� 2�� ���ؼ� �� �տ� �ִ� (�÷��̾�� �����) ���ʹ̸� ��ȯ
	static enemy* Collision(D3DXVECTOR3* target, enemy* v1, enemy* v2);

	//���̽�Ÿ
	virtual void EnemyAI() = 0;

};

