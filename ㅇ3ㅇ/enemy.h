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

	Kinds	_kinds;
	float	_distance;
	bool	_isCollision;
	
public:
	enemy();
	virtual ~enemy();

	virtual bool GetIsCollision() { return _isCollision; }
	virtual void SetIsCollisionCheak(bool cheak) { _isCollision = cheak; }

	// interfaceCharacter��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName) override;
	virtual void Update() override;
	virtual void Render() override;

	//�� �״�� ���ʹ� ������
	virtual void Moving() override;

	//�ִϸ��̼� ����
	virtual void AnimationSetting() = 0;

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

