#pragma once
#include "player.h"



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

class aranzebia : public player
{
private:
	//PLAYER_KEYSET	_keySet;
public:
	aranzebia();
	virtual ~aranzebia();

	virtual void Init(PLAYERS p, wstring keyPath, wstring keyName);
	virtual void animation();

};

