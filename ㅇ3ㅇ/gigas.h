#pragma once
#include "player.h"

//gigas 프레임 순서
//
//타운트 샤우트0
//스턴1
//런2
//빽대쉬어택(attack00)3
//칼꽃은 IDLE4
//칼들은 IDLE5
//죽음6
//올려치기(attack01)7
//용호난무(attack02)8
//히어로랜딩9

//ACT_NONE = -1,
//ACT_IDLE,			//가만히    0
//ACT_WARKING_FRONT,	//앞으로 걷기	1
//ACT_WARKING_BACK,	//뒤로 걷기		2
//ACT_RUN_FRONT,		//앞으로 뛰기	3
//ACT_RUN_BACK,		//뒤로 뛰기	4
//ACT_ATTACK00,		//공격00		5
//ACT_ATTACK01,		//공격01		6
//ACT_ATTACK02,		//공격02		7
//ACT_ATTACK03,		//공격03		8
//ACT_ULTIMATE,		//궁극기		9
//ACT_COMBO01,		//콤보		10
//ACT_COMBO02,						11
//ACT_ATTACKED00,		//피격모션	12
//ACT_SKILL01,		//스킬				13
//ACT_SKILL02,								14
//ACT_SKILL03,								15
//ACT_DEATH,			//죽을 때		16
//ACT_END

const int gigasIndex[ACT_END] = {5,-1,-1,2,-1,3,7,-1,-1,8,-1,-1,-1,-1,-1,-1,6};

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

