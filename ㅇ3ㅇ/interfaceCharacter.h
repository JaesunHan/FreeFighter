#pragma once

class skinnedMesh;

struct tagCharState
{
	int hp;		//체력
	int mp;		//마나
	int speed;	//속도
	int atkDmg; //공격력
	int def;	//방어력
};

//상태
enum ACT
{
	ACT_IDLE,	//가만히
	ACT_MOVE,	//움직임
	ACT_ATTACK,	//공격
};

class interfaceCharacter
{
protected:
	skinnedMesh* _skinnedMesh;
	tagCharState _state;

public:
	interfaceCharacter();
	~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update() = 0;
	virtual void Render() = 0;

};

