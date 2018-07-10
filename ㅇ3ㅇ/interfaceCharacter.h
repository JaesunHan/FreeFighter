#pragma once

class skinnedMesh;

// ���缱���� �Ͻǰ̴ϴ�.
// �߰����ּ��� ^^
struct tagCharStatus
{
	FLOAT hp;		//ü��
	FLOAT mp;		//����
	FLOAT atkDmg;	//���ݷ�
	FLOAT def;		//����
	FLOAT speed;	//�ӵ�
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
	skinnedMesh*	_skinnedMesh;	//��Ų��Ž�
	tagCharStatus	_status;		//ĳ���� ����
	ACT				_act;			//ĳ���� �ൿ
	bool			_isDead;		//ĳ���Ͱ� �׾���?
	tagSphere		_sphere;		//�߰��� (����׿� �浹��)

protected:
	//SRT (����)
	D3DXVECTOR3		_worldSca;
	D3DXVECTOR3		_worldRot;
	D3DXVECTOR3		_worldPos;
	D3DXVECTOR3		_worldDir;
	D3DXMATRIX		_worldTM;
	//���ʹ̰� ����
	D3DXVECTOR3*	_targetPos;

	//��������
protected:
	PxController*	_controller;	//�ڹ������� ��Ʈ�ѷ���
	PxVec3			_velocity;

public:
	interfaceCharacter();
	virtual ~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render();
	// ������ ( �� �ൿ�� ���������� false , �� ������ true )
	virtual bool isAbsoluteMotion();
	// �ִϸ��̼� ����
	virtual void AnimationSetting();
	// ��Ʈ�ѷ� ����
	virtual void createContoller(PxControllerManager** cm, PxMaterial* m);

	// ##### ������ ���� ������ & ������ #####
	//���� ������
	D3DXVECTOR3& GetPosition() { return _worldPos; }
	//���ʹ����� (Ÿ�ټ���)
	void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	//SRT����
	void SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
	{
		_worldSca = sca;
		_worldRot = rot;
		_worldPos = pos;

		D3DXMATRIX matS, matR, matT;
		D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);
		D3DXMatrixRotationYawPitchRoll(&matR, _worldRot.x, _worldRot.y, _worldRot.z);
		D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

		_worldTM = matS * matR * matT;
		_controller->setPosition(PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z));
	}
};

