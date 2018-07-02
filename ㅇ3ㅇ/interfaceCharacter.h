#pragma once

class skinnedMesh;

struct tagCharState
{
	int hp;		//체력
	int mp;		//마나
	int atkDmg; //공격력
	int def;	//방어력
};

//상태
enum ACT
{
	ACT_NONE = -1,
	ACT_IDLE,		//가만히
	ACT_RUN,		//움직임
	ACT_ATTACK,		//공격
	ACT_COMBO01,	//콤보
	ACT_COMBO02,
	ACT_SKILL01,	//스킬
	ACT_SKILL02,
	ACT_SKILL03,
	ACT_END
};


class interfaceCharacter
{
protected:
	skinnedMesh* _skinnedMesh;
	tagCharState _state;

	bool _isDead;

public:
	interfaceCharacter();
	~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render();

};

