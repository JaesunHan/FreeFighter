#pragma once

class skinnedMesh;

struct tagCharStatus
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
	ACT_IDLE,			//가만히
	ACT_WARKING_FRONT,	//앞으로 걷기
	ACT_WARKING_BACK,	//뒤로 걷기
	ACT_RUN_FRONT,		//앞으로 뛰기
	ACT_RUN_BACK,		//뒤로 뛰기
	ACT_ATTACK00,		//공격00
	ACT_ATTACK01,		//공격01
	ACT_ATTACK02,		//공격02
	ACT_ATTACK03,		//공격03
	ACT_ULTIMATE,		//궁극기
	ACT_COMBO01,		//콤보
	ACT_COMBO02,
	ACT_ATTACKED00,		//피격모션
	ACT_SKILL01,		//스킬
	ACT_SKILL02,
	ACT_SKILL03,
	ACT_DEATH,			//죽을 때
	ACT_END

};

class interfaceCharacter
{
protected:
	skinnedMesh*	_skinnedMesh;
	tagCharStatus	_status;
	ACT				_act;

	bool			_isDead;

	//추가됨 (디버그용 충돌원)
	tagSphere		_sphere;

	PxController*	_controller;

public:
	interfaceCharacter();
	virtual ~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render();
	bool isAbsoluteMotion();

	virtual void AnimationSetting();

	void createContoller(PxControllerManager** cm, PxMaterial* m);
};

