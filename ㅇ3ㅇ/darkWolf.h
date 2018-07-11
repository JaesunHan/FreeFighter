#pragma once
#include "enemy.h"

// �˴�
// 0 -> Stun
// 1 -> Run
// 2 -> Idle
// 3 -> Dead
// 4 -> Damaged
// 5 -> Attack_02
// 6 -> Attack_01

//ACT_NONE = -1,
//ACT_IDLE,			//������
//ACT_WARKING_FRONT,	//������ �ȱ�
//ACT_WARKING_BACK,	//�ڷ� �ȱ�
//ACT_RUN_FRONT,		//������ �ٱ�
//ACT_RUN_BACK,		//�ڷ� �ٱ�
//ACT_ATTACK00,		//����00
//ACT_ATTACK01,		//����01
//ACT_ATTACK02,		//����02
//ACT_ATTACK03,		//����03
//ACT_ULTIMATE,		//�ñر�
//ACT_COMBO01,		//�޺�
//ACT_COMBO02,
//ACT_ATTACKED00,		//�ǰݸ��
//ACT_SKILL01,		//��ų
//ACT_SKILL02,
//ACT_SKILL03,
//ACT_DEATH,			//���� ��
//ACT_END

const int _AniIndex[ACT_END] = { 2, -1, -1, 1, -1, 5, 6, -1, -1, -1, -1, -1, 4, -1, -1, -1, 3 };

class darkWolf : public enemy
{
public:
	darkWolf();
	virtual ~darkWolf();

	// enemy��(��) ���� ��ӵ�
	virtual void Init(wstring keyPath, wstring keyName);

	virtual void EnemyAI() override;


};

