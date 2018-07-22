#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"
#include "hitEffect.h"

interfaceCharacter::interfaceCharacter()
	: _currentAct(ACT_NONE)
	, _nextAct(ACT_NONE)
	, _skinnedMesh(NULL)
	, _controller(NULL)
	, _worldSca(1.0f, 1.0f, 1.0f)
	, _worldPos(0.0f, 0.0f, 0.0f)
	, _worldDir(0.0f, 0.0f, 1.0f)
	, _velocity(0, 0, 0)
	, _isDead(false)
	, _isOneHit(false)
{
	D3DXMatrixIdentity(&_worldTM);

	for (int i = 0; i < ACT_END; i++)
	{
		_AniIndex[i] = -1;
	}

	for (int i = 0; i < ATTACK_END; i++)
	{
		_aniRate[i] = 0;
	}

	ZeroMemory(&_status, sizeof(tagCharStatus));
}


interfaceCharacter::~interfaceCharacter()
{
	if(_skinnedMesh)
		_skinnedMesh->destroy();

	for (int i = 0; i < _vParticle.size(); ++i)
		SAFE_OBJRELEASE(_vParticle[i]);
	_vParticle.clear();
}

void interfaceCharacter::Init(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath, keyPath.c_str(), keyName.c_str());
	_skinnedMesh->setParentMatrix(&_worldTM);
}

void interfaceCharacter::Update()
{
	_skinnedMesh->update();

	for (int i = 0; i < _vParticle.size(); ++i)
		_vParticle[i]->update(TIMEMANAGER->getElapsedTime());
}

void interfaceCharacter::Render(float elapsedTime)
{
	_skinnedMesh->render(elapsedTime);
}

void interfaceCharacter::RenderParticle()
{
	// �̰� �и��ص� ������ ��ƼŬ�� ����Ʈ '��������Ʈ'�� ������ ������ ����� ����
	// ������� ���丮������ ��ƼŬ��� -> ��׶��� ��� �ϸ� ��ƼŬ�� ��׶��忡 ����������(��ƼŬ ���� 3d���� ��ġ���� ���� ����)
	// ���� ��׶��庸�� ���߿� �׷�������
	// �ٵ� �÷��̾� �������� ���� ���� ������ ��׶��� ���� �׷�������(����Ʈ ����)
	// ���� ���� ������
	for (int i = 0; i < _vParticle.size(); ++i)
		_vParticle[i]->render();
}

void interfaceCharacter::HitDamage(float damage)
{
	_status.currentHp -= damage;

	if (_status.currentHp > 0)
	{
		_nextAct = ACT_DAMAGED;
	}
	else
	{
		_isDead = true;
		_nextAct = ACT_DEATH;
	}
}

void interfaceCharacter::HitCheck(interfaceCharacter* IChar, float damage, float distance, float attackArea)
{
	if (!_isOneHit) return;

	if (_skinnedMesh->getCurrentAnimationRate())
	{
		D3DXVECTOR3 temp = _worldPos + _worldDir * distance;

		D3DXVECTOR3 pos = IChar->GetPosition();
		if (temp.x - attackArea < pos.x && temp.x + attackArea > pos.x &&
			temp.y - attackArea < pos.y && temp.y + attackArea > pos.y &&
			temp.z - attackArea < pos.z && temp.z + attackArea > pos.z)
		{
			IChar->HitDamage(damage);
			IChar->createHitEffect(0.25f);
		}
	}

}

void interfaceCharacter::HitCheck(interfaceCharacter* IChar, float damage, float distance, float attackArea, float progressPercent)
{
	if (!_isOneHit) return;

	if (_skinnedMesh->getCurrentAnimationRate() > progressPercent)
	{
		D3DXVECTOR3 temp = _worldPos + _worldDir * distance;

		D3DXVECTOR3 pos = IChar->GetPosition();
		if (temp.x - attackArea < pos.x && temp.x + attackArea > pos.x &&
			temp.y - attackArea < pos.y && temp.y + attackArea > pos.y &&
			temp.z - attackArea < pos.z && temp.z + attackArea > pos.z)
		{
			IChar->HitDamage(damage);
			IChar->createHitEffect(0.25f);
		}
	}
}

void interfaceCharacter::SetOneHit()
{
	if (this->IsAttackMotion() && _skinnedMesh->getCurrentAnimationRate() > GetAttackAniRate())
		_isOneHit = false;

	if (_currentAct == ACT_DAMAGED || _currentAct == ACT_RECOVERY || _currentAct == ACT_DEATH)
		_isOneHit = false;
}

float interfaceCharacter::GetAttackAniRate()
{
	if (this->IsAttackMotion())
		return _aniRate[_currentAct - ACT_ATTACK00];
	else
		return 0;
}


bool interfaceCharacter::IsAttackMotion()
{
	if (_currentAct == ACT_ATTACK00 ||
		_currentAct == ACT_ATTACK01 ||
		_currentAct == ACT_ATTACK02 ||
		_currentAct == ACT_ATTACK03 ||
		_currentAct == ACT_SKILL01 ||
		_currentAct == ACT_SKILL02 ||
		_currentAct == ACT_SKILL03)
	{
		return true;
	}

	return false;
}

bool interfaceCharacter::isAbsoluteMotion()
{
	if (_currentAct == ACT_ATTACK00 ||
		_currentAct == ACT_ATTACK01 ||
		_currentAct == ACT_ATTACK02 ||
		_currentAct == ACT_ATTACK03 ||
		_currentAct == ACT_ULTIMATE ||
		_currentAct == ACT_COMBO01 ||
		_currentAct == ACT_COMBO02 ||
		_currentAct == ACT_DAMAGED ||
		_currentAct == ACT_RECOVERY ||
		_currentAct == ACT_SKILL01 ||
		_currentAct == ACT_SKILL02 ||
		_currentAct == ACT_SKILL03 ||
		_currentAct == ACT_DEATH)
	{
		return true;
	}

	return false;
}

void interfaceCharacter::CreateWorldMatrix(float correctionAngle)
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	// �����ϸ�
	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);

	// �����̼�(������ Y�� ������ ����)
	float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) + correctionAngle;
	D3DXMatrixRotationY(&matR, angle);

	// Ʈ�������̼�
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	// ���� ��Ʈ���� ��ȭ
	_worldTM = matS * matR * matT;
}

void interfaceCharacter::AnimationSetting()
{
	if (_currentAct != _nextAct)
	{
		_currentAct = _nextAct;
		if (IsAttackMotion())  _isOneHit = true;
		_skinnedMesh->setAnimationIndexBlend(_AniIndex[_currentAct]);
	}
}

void interfaceCharacter::createContoller(PxControllerManager** cm, PxMaterial* m)
{
	PxCapsuleControllerDesc desc;
	desc.position = PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z);
	desc.radius = 2.0f;
	desc.height = 10.0f;
	desc.stepOffset = 0.0f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->setUserData(this);

	_cm = cm;
	_material = m;
}

void interfaceCharacter::createContoller(PxControllerManager ** cm, PxMaterial * m, float radius, float height)
{
	PxCapsuleControllerDesc desc;
	desc.position = PxExtendedVec3(_worldPos.x, _worldPos.y, _worldPos.z);
	desc.radius = radius;
	desc.height = height;
	desc.stepOffset = 0.0f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->setUserData(this);

	_cm = cm;
	_material = m;
}

void interfaceCharacter::createHitEffect(float radius)
{
	hitEffect* temp = new hitEffect;
	D3DXVECTOR3 min = _worldPos - D3DXVECTOR3(0.25f, -0.25f, 0.25f);
	D3DXVECTOR3 max = _worldPos + D3DXVECTOR3(0.25f, 0.5f, 0.25f);
	temp->init(radius, 500, _T(".\\texture\\skill\\hitEffect.png"), RND->getFromVec3To(min, max));

	_vParticle.push_back(temp);
}
