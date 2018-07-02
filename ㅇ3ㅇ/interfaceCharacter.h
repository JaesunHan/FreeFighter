#pragma once

class skinnedMesh;

struct tagCharState
{
	int hp;		//ü��
	int mp;		//����
	int atkDmg; //���ݷ�
	int def;	//����
};

//����
enum ACT
{
	ACT_NONE = -1,
	ACT_IDLE,		//������
	ACT_RUN,		//������
	ACT_ATTACK,		//����
	ACT_COMBO01,	//�޺�
	ACT_COMBO02,
	ACT_SKILL01,	//��ų
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

