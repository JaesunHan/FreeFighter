#pragma once
#include "player.h"


      //�Ͽ︵?����?		9//0~84     
     //�չ���	8			//85~119  
     //�ڹ���	7			//120~155
    //�նٱ�		6		   //156~177
   //�ڶٱ�		5		   //178~194
   //����1   	4				//195~245
   //����2   	3				//246~319
  //����3   	2				//320~372
  //IDLE		1				//373~570
  //���		0				 //571~688


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

//const int knightIndex[ACT_END] = {8,1,2,3,4,5,6,7,-1,-1,-1,-1,-1,-1,-1,-1,9 };


class knight : public player
{
private:
	//PLAYER_KEYSET	_keySet;
public:
	knight();
	virtual ~knight();

	virtual void Init(PLAYERS p, wstring keyPath, wstring keyName);

	virtual void animation();

};