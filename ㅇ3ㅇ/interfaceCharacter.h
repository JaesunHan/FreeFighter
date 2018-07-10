#pragma once

class skinnedMesh;

// 빛재선님이 하실겁니다.
// 추가해주세요 ^^
struct tagCharStatus
{
	FLOAT hp;		//체력
	FLOAT mp;		//마나
	FLOAT atkDmg;	//공격력
	FLOAT def;		//방어력
	FLOAT speed;	//속도
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
	skinnedMesh*	_skinnedMesh;	//스킨드매쉬
	tagCharStatus	_status;		//캐릭터 스텟
	ACT				_act;			//캐릭터 행동
	bool			_isDead;		//캐릭터가 죽었니?
	tagSphere		_sphere;		//추가됨 (디버그용 충돌원)

protected:
	//SRT (공통)
	D3DXVECTOR3		_worldSca;
	D3DXVECTOR3		_worldRot;
	D3DXVECTOR3		_worldPos;
	D3DXVECTOR3		_worldDir;
	D3DXMATRIX		_worldTM;
	//에너미가 쓸거
	D3DXVECTOR3*	_targetPos;

	//물리엔진
protected:
	PxController*	_controller;	//★물리엔진 컨트롤러★
	PxVec3			_velocity;

public:
	interfaceCharacter();
	virtual ~interfaceCharacter();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render();
	// 절대모션 ( 이 행동이 끝날때까지 false , 다 끝나면 true )
	virtual bool isAbsoluteMotion();
	// 애니메이션 셋팅
	virtual void AnimationSetting();
	// 컨트롤러 생성
	virtual void createContoller(PxControllerManager** cm, PxMaterial* m);

	// ##### 편리함을 위한 접근자 & 설정자 #####
	//월드 포지션
	D3DXVECTOR3& GetPosition() { return _worldPos; }
	//에너미전용 (타겟설정)
	void SetTarget(D3DXVECTOR3* target) { _targetPos = target; }
	//SRT설정
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

