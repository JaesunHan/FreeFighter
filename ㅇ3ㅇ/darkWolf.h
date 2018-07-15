#pragma once
#include "enemy.h"

// 검늑
// 0 -> Stun
// 1 -> Run
// 2 -> Idle
// 3 -> Dead
// 4 -> Damaged
// 5 -> Attack_02
// 6 -> Attack_01

//ACT_NONE = -1,
//ACT_IDLE,			//가만히
//ACT_WARKING_FRONT,	//앞으로 걷기
//ACT_WARKING_BACK,	//뒤로 걷기
//ACT_RUN_FRONT,		//앞으로 뛰기
//ACT_RUN_BACK,		//뒤로 뛰기
//ACT_ATTACK00,		//공격00
//ACT_ATTACK01,		//공격01
//ACT_ATTACK02,		//공격02
//ACT_ATTACK03,		//공격03
//ACT_ULTIMATE,		//궁극기
//ACT_COMBO01,		//콤보
//ACT_COMBO02,
//ACT_ATTACKED00,		//피격모션
//ACT_SKILL01,		//스킬
//ACT_SKILL02,
//ACT_SKILL03,
//ACT_DEATH,			//죽을 때
//ACT_END

class darkWolf : public enemy
{
public:
	darkWolf();
	virtual ~darkWolf();

	// enemy을(를) 통해 상속됨
	virtual void Init(wstring keyPath, wstring keyName, int stage) override;
};

