#pragma once

class skinnedMesh;
class particleSystem;

// ���缱���� �Ͻǰ̴ϴ�.
// �߰����ּ��� ^^
struct tagCharStatus
{
	FLOAT	maxHp;				//�ִ� ü��
	FLOAT	currentHp;			//���� ü��
	FLOAT	mp;					//����
	FLOAT	atkDmg;				//���ݷ�
	FLOAT	def;				//����
	FLOAT	speed;				//�ӵ�
	FLOAT	skillLV1;			//��ų 1�� ����	���ݷ� ����� �� ��ų ������ �ʿ���
	FLOAT	skillLV2;			//��ų 2�� ����	���ݷ� ����� �� ��ų ������ �ʿ���
	FLOAT	skillLV3;			//��ų 3�� ����	���ݷ� ����� �� ��ų ������ �ʿ���

	int		skillPoint;			//ĳ���Ͱ� �����ϸ� skillPoint �� 3 �� ���δ�
};

//����
enum ACT
{
	ACT_NONE = -1,
	ACT_APPEAR,			//����
	ACT_IDLE,			//������
	ACT_WARKING_FRONT,	//������ �ȱ�
	ACT_WARKING_BACK,	//�ڷ� �ȱ�
	ACT_RUN_FRONT,		//������ �ٱ�
	ACT_RUN_BACK,		//�ڷ� �ٱ�
	ACT_ULTIMATE,		//�ñر�
	ACT_COMBO01,		//�޺�
	ACT_COMBO02,
	ACT_DAMAGED,		//�ǰݸ��
	ACT_RECOVERY,		//ȸ��
	ACT_DEATH,			//���� ��
	ACT_ATTACK00,		//����00
	ACT_ATTACK01,		//����01
	ACT_ATTACK02,		//����02
	ACT_ATTACK03,		//����03
	ACT_SKILL01,		//��ų
	ACT_SKILL02,
	ACT_SKILL03,
	ACT_END
};

#define ATTACK_END 10

typedef class interfaceCharacter
{
protected:
	skinnedMesh*	_skinnedMesh;	//��Ų��Ž�
	tagCharStatus	_status;		//ĳ���� ����
	ACT				_currentAct;	//ĳ���� �����ൿ
	ACT				_nextAct;		//ĳ���� �����ൿ
	bool			_isDead;		//ĳ���Ͱ� �׾���?
	tagSphere		_sphere;		//�߰��� (����׿� �浹��)

	bool			_isOneHit;		//�ѹ��� ������
	float			_aniRate[ATTACK_END];

protected:
	//SRT (����)
	D3DXVECTOR3		_worldSca;
	D3DXVECTOR3		_worldPos;
	D3DXVECTOR3		_worldDir;
	D3DXMATRIX		_worldTM;

protected:
	//��������
	PxController*	_controller;	//�ڹ������� ��Ʈ�ѷ���
	PxVec3			_velocity;

	PxControllerManager**	_cm;
	PxMaterial*				_material;

protected:
	int						_AniIndex[ACT_END]; // ���ϸ��̼� �ε��� �缳��

	// �ҷ��� ��ƼŬ�ý������� ��ü�Ѵ�!
protected:
	vector<particleSystem*>		_vParticle;

public:
	interfaceCharacter();
	virtual ~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime());
	virtual void RenderParticle();

	// ���� ������
	virtual void HitCheck(interfaceCharacter* IChar, float damage, float distance, float attackArea);
	virtual void HitCheck(interfaceCharacter* IChar, float damage, float distance, float attackArea, float progressPercent);
	virtual void SetOneHit();
	virtual void HitDamage(float damage);	// �ӽ�
	virtual D3DXVECTOR3 AttackRange(float Distance)
	{
		return _worldPos + _worldDir * Distance;
	}
	// �ִϸ��̼� �ۼ�Ʈ
	virtual float GetAttackAniRate();
	virtual bool IsAttackMotion();
	// ������ ( �� �ൿ�� ���������� false , �� ������ true )
	virtual bool isAbsoluteMotion();
	// ������ ��ġ�� �����Ʈ������ �������
	virtual void CreateWorldMatrix(float correctionAngle = -D3DX_PI / 2);
	// �ִϸ��̼� ����
	virtual void AnimationSetting();
	// ��Ʈ�ѷ� ����
	virtual void createContoller(PxControllerManager** cm, PxMaterial* m);
	virtual void createContoller(PxControllerManager** cm, PxMaterial* m , float radius , float height); // ������ , ���� ����

	virtual void createHitEffect(float radius);

	// ##### ������ ���� ������ & ������ #####
	//���� ������
	D3DXVECTOR3& GetPosition() { return _worldPos; }
	void SetPosition(D3DXVECTOR3 pos) { _worldPos = pos; _controller->setFootPosition(PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z)); }
	//���� �𷺼�(����)
	D3DXVECTOR3 GetDir() { return _worldDir; }
	void SetDir(D3DXVECTOR3 dir) { _worldDir = dir; }
	//SRT����
	void SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 dir, D3DXVECTOR3 pos)
	{
		_worldSca = sca;
		_worldDir = dir;
		_worldPos = pos;

		this->CreateWorldMatrix();

		_controller->setFootPosition(PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z));
	}

	inline PxController* getController() { return _controller; }

} iChar, _char;

