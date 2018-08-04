#include "stdafx.h"
#include "darkLord.h"
#include "stateContext.h"
#include "particleSystems.h"
#include "hpBar.h"


darkLord::darkLord()
{
	_AniIndex[ACT_APPEAR]		= 6;
	_AniIndex[ACT_IDLE]			= 4;
	_AniIndex[ACT_RUN_FRONT]	= 12;
	_AniIndex[ACT_ATTACK00]		= 0;
	_AniIndex[ACT_ATTACK01]		= 1;
	_AniIndex[ACT_ATTACK02]		= 2;
	_AniIndex[ACT_DAMAGED]		= 7;
	_AniIndex[ACT_RECOVERY]		= 5;
	_AniIndex[ACT_DEATH]		= 9;

	_aniRate[0]					= 0.65f;
	_aniRate[1]					= 0.65f;
	_aniRate[2]					= 0.2f;
}


darkLord::~darkLord()
{
}

void darkLord::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_hpBar->Init(_T("�߰�����"), _T(".\\texture\\hpBar"), _T(".\\1.TGA"));

	_correctionAngle = 0.0f;

	_kinds = ENEMY_DARKLORD;
}

void darkLord::SetStatus(int stage)
{
	_status.maxHp = 3000.0f;
	_status.currentHp = _status.maxHp;
	_status.mp = 300.0f;
	_status.atkDmg = 100.0f;
	_status.def = 50.0f;
	_status.speed = 0.1f;
}

void darkLord::Render(float elapsedTime)
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�ִϸ��̼� ����
	if (!GetIsDeadAnimationEnd())
		interfaceCharacter::Render(elapsedTime);
	else
		interfaceCharacter::Render(0.0f);

	for (int i = 0; i < _vParticle.size(); i++)
	{
		_vParticle[i]->render();
	}

	if (_hpBar)
	{
		float maxRange = 15.0f;

		if (_targetPos)
		{
			float range = D3DXVec3Length(&(*_targetPos - _worldPos));

			if (range <= maxRange)
			{
				//float temp = (maxRange - range) / maxRange;
				//if (temp > 0.9f) temp = 0.9f;
				D3DVIEWPORT9 vp;
				D3DDEVICE->GetViewport(&vp);
				_hpBar->Render(vp.X + vp.Width / 2, vp.Y + 10.0f, D3DXVECTOR3(4.5f, 0.5f, 0.0f));
			}
		}
	}

}
