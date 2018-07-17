#include "stdafx.h"
#include "storeScene.h"
#include "skinnedMesh.h"
#include "cube.h"
#include "camera.h"
#include "gameObject.h"


void storeCharacter::init()
{
	_skinnedMesh = new skinnedMesh;

	//스킬을 2개 보유하고 있고 순서가 \
		0 : stun					\
		1 : run						\
		2 : idle					\
		3 : dead					\
		4 : damager					\
		5 : attack_02				\
		6 : attack_01				\
	인 애들
	if (lstrcmp(characterName, _T("woodGiant"))
		|| lstrcmp(characterName, _T("fepee"))
		|| lstrcmp(characterName, _T("reaper")))
	{
		_skillNum = 0;								//캐릭터가 보유한 스킬 갯수
		_aniIndex[STORE_ANIM_IDLE] = 2;
		_aniIndex[STORE_ANIM_ATTACK00] = ACT_ATTACK00;
		_aniIndex[STORE_ANIM_ATTACK01] = 5;
		_aniIndex[STORE_ANIM_ATTACK02] = 6;
		_aniIndex[STORE_ANIM_ATTACK03] = 7;
		_skillPoint = 0;
	}
	else if (lstrcmp(characterName, _T("zealot")))
	{
		_skillNum = 0;								//캐릭터가 보유한 스킬 갯수
		_aniIndex[STORE_ANIM_IDLE] = 4;
		_aniIndex[STORE_ANIM_ATTACK00] = 0;
		_aniIndex[STORE_ANIM_ATTACK01] = 1;
		_aniIndex[STORE_ANIM_ATTACK02] = 2;
		_aniIndex[STORE_ANIM_ATTACK03] = 0;
		_skillPoint = 0;
	}
	for (int i = 0; i < 3; ++i)
		_priceSkillPoint[i] = 1;
}

storeCharacter::storeCharacter()
{
	

}

storeCharacter::~storeCharacter()
{
}

void storeCharacter::setCharacterAnimationset(UINT animIdx)
{
	_skinnedMesh->setAnimationIndexBlend(animIdx);
}


storeScene::storeScene()
	: _buttons(NULL)
	, _sky(NULL)
	, _cam(NULL)
	
{
}

storeScene::~storeScene()
{
	if(_sky)
		SAFE_DELETE(_sky);
	if (_cam)
		SAFE_OBJRELEASE(_cam);
}

HRESULT storeScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	//뒤로 가기 버튼
	_buttons = new uiButton;
	_buttons->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), 10 + 200/2, 10 + 50/2, 3);
	_buttons->setDelegate(this);
	
	//보유중 버튼
	uiButton* haveButton = new uiButton;
	haveButton->init(_T("Have"), _T(".\\texture\\buttons\\Have.png"), 10 + 200 / 2, 65 + 50 / 2, 3);
	haveButton->setDelegate(this);
	_buttons->addChild(haveButton);

	//미보유 버튼
	uiButton* dontHaveButton = new uiButton;
	dontHaveButton->init(_T("Donthave"), _T(".\\texture\\buttons\\Donthave.png"), 220 + 200 / 2, 65 + 50 / 2, 3);
	dontHaveButton->setDelegate(this);
	_buttons->addChild(dontHaveButton);

	//skill1 버튼
	uiButton* skill1Button = new uiButton;
	skill1Button->init(_T("skill1"), _T(".\\texture\\buttons\\skillButtons\\skilbtn1.png"), vp.Width/2 + 150, 60, 3);
	skill1Button->setDelegate(this);
	//_buttons->addChild(skill1Button);
	_vecSkillBtns.push_back(skill1Button);

	//skill2 버튼
	uiButton* skill2Button = new uiButton;
	skill2Button->init(_T("skill2"), _T(".\\texture\\buttons\\skillButtons\\skilbtn2.png"), vp.Width / 2 + 150 +150, 60, 3);
	skill2Button->setDelegate(this);
	//skill1Button->addChild(skill2Button);
	_vecSkillBtns.push_back(skill2Button);

	//skill1 버튼
	uiButton* skill3Button = new uiButton;
	skill3Button->init(_T("skill3"), _T(".\\texture\\buttons\\skillButtons\\skilbtn3.png"), vp.Width / 2 + 150 + 300, 60, 3);
	skill3Button->setDelegate(this);
	//skill1Button->addChild(skill3Button);
	_vecSkillBtns.push_back(skill3Button);

	//스킬강화 버튼
	_skillStrongBtn = new uiButton;
	_skillStrongBtn->init(_T("skillStrong"), _T(".\\texture\\buttons\\skillButtons\\Strong.png"), vp.Width / 2 + 150 + 150, vp.Height - 60, 3);
	_skillStrongBtn->setDelegate(this);
	
	//캐릭터 강화 버튼
	_characterStrongBtn = new uiButton;
	_characterStrongBtn->init(_T("characterStrong"), _T(".\\texture\\buttons\\skillButtons\\CharacterStrong.png"), 300, vp.Height - 60, 3);
	_characterStrongBtn->setDelegate(this);

	loadPlayerInformation(_T("iniData"), _T("playerInfo"));
	loadCharactersData(_T("iniData"), _T("playerCharacters"));

	setSky();
	setLight();

	_cam = new camera;
	_cam->init();

	_vecGround = OBJLOADER->load(_T(".\\obj\\store_Character_Ground.obj"));
	_vecGroundSurface = OBJLOADER->load(_T(".\\obj\\store_Character_Ground_surface.obj"));

	D3DXVECTOR3 scaleV(0.16f, 0.16f, 0.16f);
	_translationV = D3DXVECTOR3(-1.47f, -1.0f, 0.0f);
	for (int i = 0; i < _vecGround.size(); ++i)
	{	
		_vecGround[i].scaleWorld(scaleV.x, scaleV.y, scaleV.z);
		_vecGround[i].positionWorld(_translationV);
		//_vecGround[i].rotateWorld(0.0f, D3DX_PI - 0.16f, 0.0f);
		_vecGround[i].update();
	}
	for (int i = 0; i < _vecGroundSurface.size(); ++i)
	{
		_vecGroundSurface[i].scaleWorld(scaleV.x, scaleV.y, scaleV.z);
		_vecGroundSurface[i].positionWorld(_translationV);
		//_vecGroundSurface[i].rotateWorld(0.0f, D3DX_PI - 0.16f, 0.0f);
		_vecGroundSurface[i].update();
	}
	_characterIdx = 0;
	_isHaveCharacter = false;
	_selectSkillNum = -1;
	if(_cam)
		_cam->update();

	
	return S_OK;
}

void storeScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_characterIdx++;
		if (_characterIdx >= _vecPlayerCharacters.size())
		{
			_characterIdx = 0;
			//_vecPlayerCharacters[_characterIdx]->_skillId
		}
		_selectSkillNum = -1;
	}
	//백 버튼, 보유중 버튼, 미보유 버튼 업데이트
	if (_buttons)
		_buttons->update();

	//보유중 버튼 클릭했을 때만 스킬 버튼과 강화 버튼이 동자가해야한다.
	if (_isHaveCharacter)
	{
		//스킬 버튼 업데이트
		for (int i = 0; i < _vecPlayerCharacters[_characterIdx]->_skillNum; ++i)
		{
			if (_vecSkillBtns[i])
				_vecSkillBtns[i]->update();
		}
		//강화 버튼 업데이트
		if (_skillStrongBtn)
			_skillStrongBtn->update();
		if (_characterStrongBtn)
			_characterStrongBtn->update();

		D3DDEVICE->LightEnable(_characterSpotLightIdx, TRUE);
	}
	else
	{
		D3DDEVICE->LightEnable(_characterSpotLightIdx, FALSE);
	}

	//저장
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		savePlayerInformation(_T("iniData"), _T("playerInfo"));
		saveCharacterSkillData(_T("iniData"), _T("playerCharacters"));
	}
	//if (_cam)
	//{
	//	_cam->update();
	//}

	_vecPlayerCharacters[_characterIdx]->Update();
}

void storeScene::release()
{
	SAFE_OBJRELEASE(_buttons);

	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &temp);
}

void storeScene::render()
{
	
	if (_sky)
	{
		D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		_sky->render();
		D3DDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	if (_buttons)
		_buttons->render();

	//보유중 버튼 눌렀을 때만 스킬 버튼과 강화 버튼이 출력되어야 한다
	if (_isHaveCharacter)
	{
		//스킬 버튼 렌더
		for (int i = 0; i < 3; ++i)
		{
			if (_vecSkillBtns[i])
				_vecSkillBtns[i]->render();
		}
		//강화 버튼 렌더
		if (_skillStrongBtn)
			_skillStrongBtn->render();
		if (_characterStrongBtn)
			_characterStrongBtn->render();

	}
	
	renderCharacterGround();

	if (_isHaveCharacter)
	{
		renderHaveCharacters();

		//캐릭터의 정보 출력하는 함수
		renderCharacterInformation();
	}
	//FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("storeScene"), lstrlen(_T("storeScene")),
	//	&RectMake(100, 100, 100, 100),
	//	DT_LEFT | DT_CENTER | DT_NOCLIP,
	//	BLACK);
	//FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, )
}

void storeScene::OnClick(uiButton* d)
{
	if (d->getButtonName() == _T("Back"))
	{
		SCENEMANAGER->changeScene(_T("mainScene"));
		SCENEMANAGER->sceneInit();
	}
	else if (d->getButtonName() == _T("Have"))
	{
		//보유중인 캐릭터만 보여준다.
		_isHaveCharacter = true;	
	}
	else if (d->getButtonName() == _T("Donthave"))
	{
		_isHaveCharacter = false;
	}
	else if (d->getButtonName() == _T("skill1"))
	{
		_selectSkillNum = 0;
		//스킬1 애니메이션 출력 및 스킬 레벨 출력
		_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[STORE_ANIM_ATTACK01]);
		//_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[0]);
	}
	else if (d->getButtonName() == _T("skill2"))
	{
		//스킬2 애니메이션 출력 및 스킬 레벨 출력
		//캐릭터가 해금한 스킬 갯수가 2이상이면 스킬버튼 클릭이 먹힌다
		if (_vecPlayerCharacters[_characterIdx]->_skillNum >= 2)
		{
			_selectSkillNum = 1;
			_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[STORE_ANIM_ATTACK02]);
		}
	}
	else if (d->getButtonName() == _T("skill3"))
	{
		//스킬3 애니메이션 출력 및 스킬 레벨 출력
		//캐릭터가 해금한 스킬 갯수가 3이상이면 스킬버튼 클릭이 먹힌다
		if (_vecPlayerCharacters[_characterIdx]->_skillNum >= 3)
		{
			_selectSkillNum = 2;
			_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[STORE_ANIM_ATTACK03]);
		}
	}
	//스킬 강화
	else if (d->getButtonName() == _T("skillStrong"))
	{
		if(upgradeCharacterSkill())		//스킬 강화 성공시에만 데이터 저장
			saveCharacterSkillData(_T("iniData"), _T("playerCharacters"));		//강화된 스킬 정보 저장
	}
	//캐릭터 강화
	else if (d->getButtonName() == _T("characterStrong"))
	{
		if (upgradeCharacter())			//캐릭터 강화 성공시에만 데이터 저장
		{
			saveCharacterData(_T("iniData"), _T("playerCharacters"));			//강화된 캐릭터 정보 저장
			savePlayerInformation(_T("iniData"), _T("playerInfo"));				//소비하고 남은 골드량 저장
		}
	}
}

void storeScene::setSky()
{

	_sky = new cube;
	_sky->init();
	//하늘의 스케일을 1000정도 높인다.
	_sky->scaleLocal(1000.0f, 1000.0f, 1000.0f);
	_sky->SetMtlTexName(_T("storeSkyMaterial"), _T("storeSkyTexture"));
	LPDIRECT3DTEXTURE9 skyTexture;
	TEXTUREMANAGER->addTexture(_sky->GetTexName(), _T(".\\texture\\sky\\sky2.jpg"));
	D3DMATERIAL9		skyMaterial;
	ZeroMemory(&skyMaterial, sizeof(skyMaterial));
	skyMaterial.Ambient = D3DXCOLOR(255, 255, 255, 255);

	MATERIALMANAGER->addMaterial(_sky->GetMtlName(), skyMaterial);

}

void storeScene::setLight()
{
	//태양
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3	vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	D3DDEVICE->SetLight(_numOfLight, &stLight);
	D3DDEVICE->LightEnable(_numOfLight, TRUE);
	_numOfLight++;

	//스뽓 라잍
	D3DLIGHT9		stSpotLight;
	ZeroMemory(&stSpotLight, sizeof(D3DLIGHT9));

	stSpotLight.Type = D3DLIGHT_SPOT;
	stSpotLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stSpotLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stSpotLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3	vSpotDir(-1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vSpotDir, &vSpotDir);
	stSpotLight.Direction = vSpotDir;
	D3DVECTOR vPos;
	vPos = D3DXVECTOR3(-3.5f, 2.0f, -3.0f);				//스포트 라이트 위치 설정
	stSpotLight.Position = vPos;

	stSpotLight.Phi = D3DX_PI / 4.0f;					//빛이 나가는 각도
	stSpotLight.Theta = D3DX_PI / 2.0f;			
	stSpotLight.Range = 100.0f;

	_characterSpotLightIdx = _numOfLight;
	D3DDEVICE->SetLight(_characterSpotLightIdx, &stSpotLight);
	D3DDEVICE->LightEnable(_characterSpotLightIdx, TRUE);
	_numOfLight++;

}

void storeScene::renderCharacterGround()
{
	D3DXMATRIX matWorld, matS, matT, matR;
	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	D3DXMatrixTranslation(&matT, -5.0f, -2.0f, 0.0f);
	matWorld = matS * matT;

	//D3DDEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	
	if (_isDebug)
	{
		for (int i = 0; i < _vecGroundSurface.size(); ++i)
		{
			_vecGroundSurface[i].render();
		}
	}
	else
	{
		for (int i = 0; i < _vecGround.size(); ++i)
		{
			_vecGround[i].render();
		}
	}


}
//캐릭터 선택란에 캐릭터 렌더링
void storeScene::renderHaveCharacters()
{
	if (_vecPlayerCharacters.size() == 0)
		return;

	_vecPlayerCharacters[_characterIdx]->Render();
}
void storeScene::renderCharacterInformation()
{
	//캐릭터의 레벨 표시
	WCHAR characterLv[512];
	swprintf(characterLv, _T("Lv : %d"), _vecPlayerCharacters[_characterIdx]->_characterLv);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, characterLv, lstrlen(characterLv),
		&RectMake(50, 120, 150, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
	//캐릭터의 경험치 표시
	WCHAR characterExp[512];
	swprintf(characterExp, _T("Exp : %d"), _vecPlayerCharacters[_characterIdx]->_characterExp);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, characterExp, lstrlen(characterExp),
		&RectMake(50, 170, 150, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
	//캐릭터의 공격력 표시
	WCHAR characterAtk[512];
	swprintf(characterAtk, _T("Atk : %f"), _vecPlayerCharacters[_characterIdx]->_characterAtk);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, characterAtk, lstrlen(characterAtk),
		&RectMake(50, 220, 150, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
	//캐릭터의 방어력 표시
	WCHAR characterDef[512];
	swprintf(characterDef, _T("Def : %f"), _vecPlayerCharacters[_characterIdx]->_characterDef);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, characterDef, lstrlen(characterDef),
		&RectMake(50, 270, 150, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
	//캐릭터의 민첩성 표시
	WCHAR characterSpd[512];
	swprintf(characterSpd, _T("Spd : %f"), _vecPlayerCharacters[_characterIdx]->_characterSpd);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, characterSpd, lstrlen(characterSpd),
		&RectMake(50, 320, 150, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);

	//각 스킬 별 데이터 
	//스킬1 
	WCHAR skill1[512];
	swprintf(skill1, _T("skill1 : %d"), _vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum]);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, skill1, lstrlen(skill1),
		&RectMake(600, 270, 150, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
	WCHAR skill1Description[512];
	swprintf(skill1Description, _T("공격력 및 방어력 %f 증가"), (_vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum])*1.5f);
	FONTMANAGER->findFont(fontManager::FONT_SMALLFONT)->DrawTextW(NULL, skill1Description, lstrlen(skill1Description),
		&RectMake(600, 320, 250, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);


}
//스킬 레벨만 먼저 올린다
bool storeScene::upgradeCharacterSkill()
{
	//스킬 선택안했으면 스킬을 올릴 수 없다.
	if (_selectSkillNum < 0 || _selectSkillNum >2)
		return false; 
	//스킬 강화는, 스킬의 레벨이 현재 캐릭터의 레벨보다 높으면 할 수 없다.
	if (_vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum] >=
		_vecPlayerCharacters[_characterIdx]->_characterLv)
		return false;

	//보유중인 스킬포인트가 0이면 스킬을 올릴 수 없다.
	if (_vecPlayerCharacters[_characterIdx]->_skillPoint <= 0)
		return false;

	//스킬을 올리는데 필요한 스킬포인트는 스킬의 렙에 따라 다르다.
	int priceSkillPoint = _vecPlayerCharacters[_characterIdx]->_priceSkillPoint[_selectSkillNum]
							+ _vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum] / 5;
	//보유하고 있는 스킬 포인트가 스킬 올리는데 필요한 스킬포인트 보다 작으면 스킬을 올릴 수 없다
	if (_vecPlayerCharacters[_characterIdx]->_skillPoint < priceSkillPoint)
		return false;


	_vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum] += 1;
	_vecPlayerCharacters[_characterIdx]->_skillPoint -= priceSkillPoint;

	/*
	//스킬을 올린다.
	if (_vecPlayerCharacters[_characterIdx]->_skillPoint > 0)
	{
		
		_vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum] += 1;
		_vecPlayerCharacters[_characterIdx]->_skillPoint -= 1;
	}
	*/
	return true;
}

bool storeScene::upgradeCharacter()
{
	//혹시 모를 예외처리
	//보유중인 캐릭터를 선택했을 때만 캐릭터 정보를 업데이트 할 수 있다.
	if (_isHaveCharacter)
	{
		//골드 소비
		int price = 1000 + _vecPlayerCharacters[_characterIdx]->_characterLv*500;
		_playerGold -= price;

		//1. 캐릭터의 exp 를 증가(랜덤값) 시키고  만약 증가시킨 exp 결과 값이 max를 넘어가면 렙업!
		int improveExp = RND->getFromIntTo(20, 30 + _vecPlayerCharacters[_characterIdx]->_characterExp);
		_vecPlayerCharacters[_characterIdx]->_characterExp += improveExp;
		//캐릭터의 현재 경험치가 max를 넘어서면
		if (_vecPlayerCharacters[_characterIdx]->_characterExp >= calculatMaxExp())
		{
			_vecPlayerCharacters[_characterIdx]->_characterExp = _vecPlayerCharacters[_characterIdx]->_characterExp - calculatMaxExp();
			_vecPlayerCharacters[_characterIdx]->_characterLv += 1;
			//캐릭터의 공격력과 방어력도 증가시킨다.
			//_vecPlayerCharacters[_characterIdx]->_characterAtk = _vecPlayerCharacters[_characterIdx]->_characterLv + (_vecPlayerCharacters[_characterIdx]->_characterAtk * 1.1f);
			//_vecPlayerCharacters[_characterIdx]->_characterDef = _vecPlayerCharacters[_characterIdx]->_characterLv + (_vecPlayerCharacters[_characterIdx]->_characterDef * 1.09f);
			//_vecPlayerCharacters[_characterIdx]->_characterSpd += 0.01f;
		}

	}
	return true;
}

int storeScene::calculatMaxExp()
{
	int maxExp = 100;
	for (int i = 1; i < _vecPlayerCharacters[_characterIdx]->_characterLv; ++i)
	{
		maxExp = maxExp * 2.25;
	}
	return maxExp;
}

#ifdef UNICODE
void storeScene::loadPlayerInformation(const WCHAR * folder, const WCHAR * fileName)
{
	//플레이어가 소지한 금액 데이터 읽어오기
	_playerGold = INIDATA->loadDataInterger(folder, fileName, _T("playerInfo"), _T("Gold"));
}
void storeScene::savePlayerInformation(const WCHAR * folder, const WCHAR * fileName)
{
	WCHAR playerGoldStr[MAX_STRING_NUM];
	//swprintf(playerGoldStr, L"%d", 0);
	swprintf(playerGoldStr, L"%d", _playerGold);
	INIDATA->addData(_T("playerInfo"), _T("Gold"), playerGoldStr);
	INIDATA->iniSave(folder, fileName);
}
void storeScene::loadCharactersData(const WCHAR* folder, const WCHAR * fileName)
{
	//먼저 현재 보유중인 캐릭터 총 갯수 읽어오기
	_playerCharacterNum = INIDATA->loadDataInterger(folder, fileName, _T("PlayerCharactersNum"), _T("PlayerCharactersNum"));

	for (int i = 0; i < _playerCharacterNum; ++i)
	{
		WCHAR subjectName[256];
		swprintf(subjectName, _T("character%d"), i);
		storeCharacter* tmpCharacter = new storeCharacter;
		swprintf(tmpCharacter->characterName, _T("%s"), INIDATA->loadDataString(folder, fileName, subjectName, _T("CharacterName")));
		tmpCharacter->init();
		tmpCharacter->_characterLv = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterLv"));
		tmpCharacter->_characterExp = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterExp"));
		tmpCharacter->_characterAtk = INIDATA->loadDataFloat(folder, fileName, subjectName, _T("CharacterAtk"));
		tmpCharacter->_characterDef = INIDATA->loadDataFloat(folder, fileName, subjectName, _T("CharacterDef"));
		tmpCharacter->_characterSpd = INIDATA->loadDataFloat(folder, fileName, subjectName, _T("CharacterSpd"));
		tmpCharacter->_characterSkillLv[0] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill0Lv"));
		if (tmpCharacter->_characterSkillLv[0] > 0)
			tmpCharacter->_skillNum++;
		tmpCharacter->_characterSkillLv[1] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill1Lv"));
		if (tmpCharacter->_characterSkillLv[1] > 0)
			tmpCharacter->_skillNum++;
		tmpCharacter->_characterSkillLv[2] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill2Lv"));
		if (tmpCharacter->_characterSkillLv[2] > 0)
			tmpCharacter->_skillNum++;
		//스킬 포인트 읽어오기
		tmpCharacter->_skillPoint = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("SkillPoint"));

		//skinned mesh 적용하기
		skinnedMesh* pSkinnedMesh = new skinnedMesh;
		WCHAR xFileFolder[256];
		swprintf(xFileFolder, _T(".\\xFile\\%s"), tmpCharacter->characterName);
		WCHAR xFileName[256];
		swprintf(xFileName, _T("%s.X"), tmpCharacter->characterName);
		pSkinnedMesh->init(subjectName, xFileFolder, xFileName);
		pSkinnedMesh->setAnimationSet(tmpCharacter->_aniIndex[STORE_ANIM_IDLE]);									//애니메이션중 idle 상태로 전환
		if (lstrcmp(tmpCharacter->characterName, _T("zealot")) == 0)
			D3DXMatrixScaling(&tmpCharacter->_matS, 12.0f, 12.0f, 12.0f);	//스케일 조정
		else
			D3DXMatrixScaling(&tmpCharacter->_matS, 0.058f, 0.058f, 0.058f);	//스케일 조정
		tmpCharacter->_matWorld = tmpCharacter->_matS;
		pSkinnedMesh->setParentMatrix(&tmpCharacter->_matWorld);			//월드메트릭스에 적용
		tmpCharacter->setCharacterSkinnedMesh(pSkinnedMesh);				//

		_vecPlayerCharacters.push_back(tmpCharacter);						//벡터에 캐릭터 담기
	}
}
//캐릭터 스킬만 저장
void storeScene::saveCharacterSkillData(const WCHAR* folder, const WCHAR * fileName)
{
	//upgrade 된 스킬 렙 저장
	WCHAR subject[MAX_STRING_NUM];
	swprintf(subject, _T("character%d"), _characterIdx);
	WCHAR title[MAX_STRING_NUM];
	swprintf(title, _T("Skill%dLv"), _selectSkillNum);
	WCHAR bodyStr[MAX_STRING_NUM];				//스킬의 레벨을 문자열로 저장한다.
	swprintf(bodyStr, _T("%d"), _vecPlayerCharacters[_characterIdx]->_characterSkillLv[_selectSkillNum]);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);

	//스킬 포인트 저장
	ZeroMemory(title, sizeof(WCHAR)*MAX_STRING_NUM);
	ZeroMemory(bodyStr, sizeof(WCHAR)*MAX_STRING_NUM);
	swprintf(title, _T("SkillPoint"));
	swprintf(bodyStr, _T("%d"), _vecPlayerCharacters[_characterIdx]->_skillPoint);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);

}

void storeScene::saveCharacterData(const WCHAR * folder, const WCHAR * fileName)
{
	//경험치 저장
	WCHAR subject[MAX_STRING_NUM];
	swprintf(subject, _T("character%d"), _characterIdx);
	WCHAR title[MAX_STRING_NUM];
	swprintf(title, _T("CharacterExp"));
	WCHAR bodyStr[MAX_STRING_NUM];				//스킬의 레벨을 문자열로 저장한다.
	swprintf(bodyStr, _T("%d"), _vecPlayerCharacters[_characterIdx]->_characterExp);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);

	//레벨 저장
	ZeroMemory(title, sizeof(WCHAR)*MAX_STRING_NUM);
	ZeroMemory(bodyStr, sizeof(WCHAR)*MAX_STRING_NUM);
	swprintf(title, _T("CharacterLv"));
	swprintf(bodyStr, _T("%d"), _vecPlayerCharacters[_characterIdx]->_characterLv);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);

	//공격력 저장
	ZeroMemory(title, sizeof(WCHAR)*MAX_STRING_NUM);
	ZeroMemory(bodyStr, sizeof(WCHAR)*MAX_STRING_NUM);
	swprintf(title, _T("CharacterAtk"));
	swprintf(bodyStr, _T("%f"), _vecPlayerCharacters[_characterIdx]->_characterAtk);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);

	//방어력 저장
	ZeroMemory(title, sizeof(WCHAR)*MAX_STRING_NUM);
	ZeroMemory(bodyStr, sizeof(WCHAR)*MAX_STRING_NUM);
	swprintf(title, _T("CharacterDef"));
	swprintf(bodyStr, _T("%f"), _vecPlayerCharacters[_characterIdx]->_characterDef);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);

	//방어력 저장
	ZeroMemory(title, sizeof(WCHAR)*MAX_STRING_NUM);
	ZeroMemory(bodyStr, sizeof(WCHAR)*MAX_STRING_NUM);
	swprintf(title, _T("CharacterSpd"));
	swprintf(bodyStr, _T("%f"), _vecPlayerCharacters[_characterIdx]->_characterSpd);
	INIDATA->addData(subject, title, bodyStr);
	INIDATA->iniSave(folder, fileName);
}


#else
void storeScene::loadPlayerInformation(const char * folder, const char * fileName)
{
}

void storeScene::savePlayerInformation(const char * folder, const char * fileName)
{
}

void storeScene::loadCharactersData(const char* folder, const char* fileName)
{
}

void storeScene::saveCharactersData(const char* folder, const char* fileName)
{
}
#endif // UNICODE
void storeScene::cameraZoom(float zoom)
{
	_cam->cameraZoom(zoom);
}
