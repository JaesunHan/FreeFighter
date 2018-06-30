#pragma once

class skinnedMesh;

struct tagCharState
{
	int hp;		//ü��
	int mp;		//����
	int speed;	//�ӵ�
	int atkDmg; //���ݷ�
	int def;	//����
};

//����
enum ACT
{
	ACT_IDLE,	//������
	ACT_MOVE,	//������
	ACT_ATTACK,	//����
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

