#pragma once

class skinnedMesh;

struct tagCharStatus
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
	ACT_IDLE,			//������
	ACT_WARKING_FRONT,	//������ �ȱ�
	ACT_WARKING_BACK,	//�ڷ� �ȱ�
	ACT_RUN_FRONT,		//������ �ٱ�
	ACT_RUN_BACK,		//�ڷ� �ٱ�
	ACT_ATTACK00,		//����00
	ACT_ATTACK01,		//����01
	ACT_ATTACK02,		//����02
	ACT_ATTACK03,		//����03
	ACT_ULTIMATE,		//�ñر�
	ACT_COMBO01,		//�޺�
	ACT_COMBO02,
	ACT_ATTACKED00,		//�ǰݸ��
	ACT_SKILL01,		//��ų
	ACT_SKILL02,
	ACT_SKILL03,
	ACT_DEATH,			//���� ��
	ACT_END

};

class interfaceCharacter
{
protected:
	skinnedMesh*	_skinnedMesh;
	tagCharStatus	_status;
	ACT				_act;

	bool			_isDead;

	//�߰��� (����׿� �浹��)
	tagSphere		_sphere;

public:
	interfaceCharacter();
	virtual ~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render();
	bool isAbsoluteMotion();

	virtual void AnimationSetting();
};

