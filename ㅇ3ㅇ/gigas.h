#pragma once
#include "player.h"

//gigas ������ ����
//
//Ÿ��Ʈ ����Ʈ0
//����1
//��2
//���뽬����(attack00)3
//Į���� IDLE4
//Į���� IDLE5
//����6
//�÷�ġ��(attack01)7
//��ȣ����(attack02)8
//����η���9

//ACT_NONE = -1,
//ACT_IDLE,			//������    0
//ACT_WARKING_FRONT,	//������ �ȱ�	1
//ACT_WARKING_BACK,	//�ڷ� �ȱ�		2
//ACT_RUN_FRONT,		//������ �ٱ�	3
//ACT_RUN_BACK,		//�ڷ� �ٱ�	4
//ACT_ATTACK00,		//����00		5
//ACT_ATTACK01,		//����01		6
//ACT_ATTACK02,		//����02		7
//ACT_ATTACK03,		//����03		8
//ACT_ULTIMATE,		//�ñر�		9
//ACT_COMBO01,		//�޺�		10
//ACT_COMBO02,						11
//ACT_ATTACKED00,		//�ǰݸ��	12
//ACT_SKILL01,		//��ų				13
//ACT_SKILL02,								14
//ACT_SKILL03,								15
//ACT_DEATH,			//���� ��		16
//ACT_END

//const int gigasIndex[ACT_END] = {5,-1,-1,2,-1,3,7,-1,-1,8,-1,-1,-1,-1,-1,-1,6};

class gigas : public player
{
private:
	//PLAYER_KEYSET	_keySet;

public:
	gigas();
	virtual ~gigas();

	virtual void Init(PLAYERS p, wstring keyPath, wstring keyName);
	virtual void animation();
};

