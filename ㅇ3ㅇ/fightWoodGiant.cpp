#include "stdafx.h"
#include "fightWoodGiant.h"
#include "particleSystems.h"


fightWoodGiant::fightWoodGiant()
{
	_AniIndex[ACT_IDLE] = 2;
	_AniIndex[ACT_RUN_FRONT] = 1;
	_AniIndex[ACT_RUN_BACK] = 1;
	_AniIndex[ACT_ATTACK00] = 6;
	_AniIndex[ACT_ATTACK01] = 5;
	_AniIndex[ACT_DAMAGED] = 4;
	_AniIndex[ACT_DEATH] = 3;

	//_AniIndex[ACT_SKILL01] = 6;
	//_AniIndex[ACT_SKILL03] = 6;

	_aniRate[ACT_ATTACK00 - ACT_ATTACK00] = 0.4f;
	_aniRate[ACT_ATTACK01 - ACT_ATTACK00] = 0.35f;
	_aniRate[ACT_ATTACK02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_ATTACK03 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL01 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL02 - ACT_ATTACK00] = 0.3f;
	_aniRate[ACT_SKILL03 - ACT_ATTACK00] = 0.65f;

	_correctionAngle = -D3DX_PI / 2;

	_useSkill = false;
}


fightWoodGiant::~fightWoodGiant()
{
	
}

void fightWoodGiant::SetStatus(int stage)
{
	_status.maxHp		= 2000.0f;
	_status.currentHp	= _status.maxHp;
	_status.mp			= 1000.0f;
	_status.atkDmg		= 100.0f;
	_status.def			= 100.0f;
	_status.speed		= 0.05f;

}


void fightWoodGiant::Attack02()
{
	if (_currentAct == ACT_ATTACK01)
		_useSkill = true;
	else
		_useSkill = false;

	if (_AniIndex[ACT_ATTACK01] != -1)
	{
		_nextAct = ACT_ATTACK01;

		if (!_useSkill)
		{
			for (int i = 0; i < 5; ++i)
			{
				float angleY = getAngle(0, 0, _worldDir.x, _worldDir.z) + D3DX_PI / 2;
				float angleZ = D3DX_PI * 2 / 5 * i;
				leafAtk * temp = new leafAtk;
				temp->init(7.0f, 1.0f, angleZ, angleY, 500, _T("texture\\skill"), _T("fastBuff.png"), D3DXVECTOR3(_worldPos.x, _worldPos.y + 1.5f, _worldPos.z) + _worldDir * 1.0f);

				_vParticle.push_back(temp);
			}
		}
	}

	
}

void fightWoodGiant::UseSkill01()
{
	//_isFastSkillOn = true;
	//fastBuff* temp = new fastBuff;
	//temp->init(200, _T(".\\texture\\skill\\fastBuff.png"));
	//temp->setEnemy(this);
	//
	//_vParticle.push_back(temp);
}

void fightWoodGiant::UseSkill02()
{
}

void fightWoodGiant::UseSkill03()
{
	//for (int i = 0; i < 5; ++i)
	//{
	//	float angleY = getAngle(0, 0, _worldDir.x, _worldDir.z) + D3DX_PI / 2;
	//	float angleZ = D3DX_PI * 2 / 5 * i;
	//	leafAtk* temp = new leafAtk;
	//	temp->init(7.0f, angleZ, angleY, 500, _T("texture\\skill"), _T("fastBuff.png"), D3DXVECTOR3(_worldPos.x, _worldPos.y + 1.5f, _worldPos.z) + _worldDir * 2.0f);
	//	temp->setPlayer(this);
	//
	//	_vParticle.push_back(temp);
	//}
}
