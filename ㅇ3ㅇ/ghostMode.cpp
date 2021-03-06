#include "stdafx.h"
#include "ghostMode.h"
#include "player.h"
#include "reaper.h"


ghostMode::ghostMode()
	: _radius(1.0f)
	, _ghostModeTime(0.0f)
	, _player(NULL)
{
}


ghostMode::~ghostMode()
{
}

HRESULT ghostMode::init(float radius, int numParticles, const WCHAR * filePath)
{
	_radius = radius;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	_ghostModeTime = 0.0f;

	for (int i = 0; i < numParticles; ++i)
		this->addParticle();

	particleSystem::init(filePath);

	return S_OK;
}

void ghostMode::update(float timeDelta)
{
	// 戚薦採斗 剰革級戚 嬢胸惟 崇送食醤拝走 衣舛背醤敗
	// 凧壱稽 古鯵痕呪拭 timeDelta戚闇
	// 奪拭 赤掩掘 蓄亜澗 背鎌澗汽 貝 廃 腰亀 照処埴せせ
	// 酔識 督銅適 馬蟹 馬蟹税 崇送績聖 薦嬢背左切
	// 析舘 爽汐舛軒背辞 左鎧匝惟 しし 爽汐 舛軒馬檎辞 敗 陥獣 坐郊 戚背照鞠澗暗 弘嬢左壱 眼壕杷壱身 しせ

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		D3DXMATRIX matR;
		// 焼猿 velocity研 唖紗亀稽 彰陥 梅走?? 掻淡鞠蟹? しし
		D3DXMatrixRotationY(&matR, iter->velocity.y);
		// 益 唖亀 幻鏑 匂走芝聖 宜形爽澗暗績
		D3DXVec3TransformCoord(&iter->position, &iter->position, &matR);

		// 暗軒拭 魚献 識莫左娃生稽 事聖 郊蚊捜
		// 識莫左娃戚虞澗依税 奄層精 獣娃幻 赤澗闇 焼劃
		// t = 薄仙 / 穿端
		// 走榎 _radius亜 督銅適級戚 赤聖 呪 赤澗 鋼走硯 置企葵戚醤
		// 益君糠稽 穿端亜 喫
		// 益軒壱 湿斗櫛 pos 却 陥 y葵戚 0戚艦猿
		// 舘授備 据生稽 魚閃辞 暗軒亜 杖幻鏑 恭嬢閃赤劃研
		// distance拭 眼焼黍暗走
		// 益軒壱 益惟 郊稽 薄仙
		// t = 薄仙 / 穿端亜 吉暗走
		// 紫叔 戚 督銅適精 督銅適級 崇送績精 戚惟 魁績
		// 戚賎 杉球拭辞税 崇送績
		// 巴傾戚嬢研 魚虞人醤畏走??
		D3DXVECTOR3 center(0, 0, 0);
		D3DXVECTOR3 pos = iter->position;
		pos.y = 0.0f;
		float distance = getDistance(center, pos);
		float d = distance / _radius;
		iter->currentColor = (1 - d) * iter->startColor + d * iter->endColor;

		// 持失吉 獣娃 著舛
		iter->lifeTime += TIMEMANAGER->getElapsedTime();
	}

	// 杉球 是帖説奄 魁
	D3DXVECTOR3 playerPos = _player->GetPosition();
	// 戚 購拭櫛 刃混馬惟 業旭精惟
	//D3DXMatrixTranslation(&_worldMatrix, playerPos.x, playerPos.y, playerPos.z);
	_worldMatrix._41 = playerPos.x;
	_worldMatrix._42 = playerPos.y;
	_worldMatrix._43 = playerPos.z;
	//戚惟 魁? しし 希 拝暗 蒸壱? 薄仙 督銅適精 益君背

	_ghostModeTime += TIMEMANAGER->getElapsedTime();
	if (_ghostModeTime > 5.0f)
	{
		((reaper*)_player)->turnOffGhostMode();

		list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

		for (; iter != _particles.end(); ++iter)
			iter->isAlive = false;
	}
}

void ghostMode::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	// 食奄辞採斗亜 亜舌 淫闇績
	// 走榎 馬形澗闇
	// 製...
	// 析舘 娃舘馬惟 巴傾戚嬢 爽是研 桜越桜越 亀澗暗幻 幻級嬢左切

	// 源梅走幻 剰澗 稽鎮 匂走芝戚醤 廃原巨稽 乞窮闇 据繊聖 奄層生稽 持失馬壱
	// worldMatrix研 薪移辞 鎧亜 据馬澗 是帖拭 句錘陥壱 持唖馬檎 喫
	float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);		// 析舘 唖亀研 沓棋馬惟 説走??
	float x = RND->getFromFloatTo(1.0f, _radius) * cosf(angle); // 益 唖亀 * 鋼走硯 馬檎 据 乞丞戚 蟹辛艦陥. (feat.誌唖敗呪)
	float y = RND->getFromFloatTo(0.0f, 1.0f);
	float z = RND->getFromFloatTo(1.0f, _radius) * -sinf(angle);
	attr->position = D3DXVECTOR3(x, y, z);						// 戚薦 段奄 是帖研 説紹嬢

	// 据掘 紗亀虞 敗精 識莫紗亀研 蟹展鎧暗窮 左搭
	// (識莫紗亀 : 送識生稽 亜澗 紗亀)
	// 悦汽 蟹澗 送識生稽 戚疑獣迭 持唖戚 蒸嬢 走榎
	// 益君糠稽 velocity葵聖 噺穿紗亀 葵生稽 承暗醤
	// 益軒壱 酔鍵 走榎 y逐生稽幻 噺穿馬檎 掬
	attr->velocity = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.5f, 10.0f) * DEG2RAD, 0.0f);

	// 亜紗亀澗 走榎 蒸嬢亀 吃暗旭製
	
	attr->isAlive = true;
	attr->startColor = D3DCOLOR_ARGB(255, 134, 114, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 38, 21, 121);

	attr->currentColor = attr->startColor;

	attr->lifeTime = 0.0f;
	// 食奄 猿走亜 坦製 持失
}

void ghostMode::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void ghostMode::render()
{
	if (_particles.empty()) return;

	this->preRender();

	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_textureName));
	D3DDEVICE->SetFVF(tagPC_Vertex::FVF);
	D3DDEVICE->SetStreamSource(0, _vb, 0, sizeof(tagPC_Vertex));
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);

	if (_vbOffset >= _vbSize)
		_vbOffset = 0;

	tagPC_Vertex* vb = NULL;
	_vb->Lock(_vbOffset * sizeof(tagPC_Vertex),
		_vbBatchSize * sizeof(tagPC_Vertex),
		(void**)&vb,
		_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD numParticlesInBatch = 0;

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	for (; iter != _particles.end(); ++iter)
	{
		if (iter->isAlive)
		{
			vb->p = iter->position;
			vb->c = (D3DCOLOR)iter->currentColor;
			vb++;

			numParticlesInBatch++;
			if (numParticlesInBatch == _vbBatchSize)
			{
				_vb->Unlock();

				D3DDEVICE->DrawPrimitive(
					D3DPT_POINTLIST,
					_vbOffset,
					_vbBatchSize);

				_vbOffset += _vbBatchSize;

				if (_vbOffset >= _vbSize)
					_vbOffset = 0;

				_vb->Lock(_vbOffset * sizeof(tagPC_Vertex),
					_vbBatchSize * sizeof(tagPC_Vertex),
					(void**)&vb,
					_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticlesInBatch = 0;
			}
		}
	}

	_vb->Unlock();

	if (numParticlesInBatch != 0)
	{
		D3DDEVICE->DrawPrimitive(
			D3DPT_POINTLIST,
			_vbOffset,
			numParticlesInBatch);
	}

	_vbOffset += _vbBatchSize;

	this->postRender();
}

void ghostMode::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
