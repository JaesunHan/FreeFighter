#pragma once

class skinnedMesh;
class particleSystem;

// 빛재선님이 하실겁니다.
// 추가해주세요 ^^
struct tagCharStatus
{
	FLOAT	maxHp;				//최대 체력
	FLOAT	currentHp;			//현재 체력
	FLOAT	mp;					//마나
	FLOAT	atkDmg;				//공격력
	FLOAT	def;				//방어력
	FLOAT	speed;				//속도
	FLOAT	skillLV1;			//스킬 1의 레벨	공격력 계산할 때 스킬 레벨이 필요함
	FLOAT	skillLV2;			//스킬 2의 레벨	공격력 계산할 때 스킬 레벨이 필요함
	FLOAT	skillLV3;			//스킬 3의 레벨	공격력 계산할 때 스킬 레벨이 필요함

	int		skillPoint;			//캐릭터가 렙업하면 skillPoint 가 3 씩 쌓인다
};



//상태
enum ACT
{
	ACT_NONE = -1,
	ACT_APPEAR,			//등장
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

typedef class interfaceCharacter
{
protected:
	skinnedMesh*	_skinnedMesh;	//스킨드매쉬
	tagCharStatus	_status;		//캐릭터 스텟
	ACT				_currentAct;	//캐릭터 현재행동
	ACT				_nextAct;		//캐릭터 다음행동
	bool			_isDead;		//캐릭터가 죽었니?
	tagSphere		_sphere;		//추가됨 (디버그용 충돌원)

protected:
	//SRT (공통)
	D3DXVECTOR3		_worldSca;
	D3DXVECTOR3		_worldPos;
	D3DXVECTOR3		_worldDir;
	D3DXMATRIX		_worldTM;

protected:
	//물리엔진
	PxController*	_controller;	//★물리엔진 컨트롤러★
	PxVec3			_velocity;

	PxControllerManager**	_cm;
	PxMaterial*				_material;

protected:
	int				_AniIndex[ACT_END]; // 에니메이션 인덱스 재설정

	// 불렛은 파티클시스템으로 대체한다!
protected:
	vector<particleSystem*>		_vParticle;

public:
	interfaceCharacter();
	virtual ~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime());
	virtual void RenderParticle();

	// 공격 에리어
	virtual void AttackMotionEnd(interfaceCharacter* IChar, float damage, float distance, float attackArea);
	virtual void HitDamage(float damage = 1.0f);	// 임시
	virtual D3DXVECTOR3 AttackRange(float Distance);
	// 설정된 수치로 월드매트릭스를 만들어줌
	virtual void CreateWorldMatrix(float correctionAngle = -D3DX_PI / 2);
	// 절대모션 ( 이 행동이 끝날때까지 false , 다 끝나면 true )
	virtual bool isAbsoluteMotion();
	// 애니메이션 셋팅
	virtual void AnimationSetting();
	// 컨트롤러 생성
	virtual void createContoller(PxControllerManager** cm, PxMaterial* m);
	virtual void createContoller(PxControllerManager** cm, PxMaterial* m , float radius , float height); // 반지름 , 높이 설정

	virtual void createHitEffect(float radius);

	// ##### 편리함을 위한 접근자 & 설정자 #####
	//월드 포지션
	D3DXVECTOR3& GetPosition() { return _worldPos; }
	void SetPosition(D3DXVECTOR3 pos) { _worldPos = pos; _controller->setFootPosition(PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z)); }
	//월드 디렉션(방향)
	D3DXVECTOR3 GetDir() { return _worldDir; }
	void SetDir(D3DXVECTOR3 dir) { _worldDir = dir; }
	//SRT설정
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

