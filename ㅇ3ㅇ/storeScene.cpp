#include "stdafx.h"
#include "storeScene.h"
#include "skinnedMesh.h"
#include "cube.h"
#include "camera.h"
#include "gameObject.h"


void storeCharacter::init()
{
	_skinnedMesh = new skinnedMesh;

	//��ų�� 2�� �����ϰ� �ְ� ������ \
		0 : stun					\
		1 : run						\
		2 : idle					\
		3 : dead					\
		4 : damager					\
		5 : attack_02				\
		6 : attack_01				\
	�� �ֵ�
	if (lstrcmp(characterName, _T("woodGiant"))
		|| lstrcmp(characterName, _T("fepee"))
		|| lstrcmp(characterName, _T("reaper")))
	{
		_skillNum = 0;								//ĳ���Ͱ� ������ ��ų ����
		_aniIndex[STORE_ANIM_IDLE] = 2;
		_aniIndex[STORE_ANIM_ATTACK00] = ACT_ATTACK00;
		_aniIndex[STORE_ANIM_ATTACK01] = 5;
		_aniIndex[STORE_ANIM_ATTACK02] = 6;
		_aniIndex[STORE_ANIM_ATTACK03] = 7;
	}
	
	
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
		SAFE_DELETE(_cam);
}

HRESULT storeScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	//�ڷ� ���� ��ư
	_buttons = new uiButton;
	_buttons->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), 10 + 200/2, 10 + 50/2, 3);
	_buttons->setDelegate(this);
	
	//������ ��ư
	uiButton* haveButton = new uiButton;
	haveButton->init(_T("Have"), _T(".\\texture\\buttons\\Have.png"), 10 + 200 / 2, 65 + 50 / 2, 3);
	haveButton->setDelegate(this);
	_buttons->addChild(haveButton);

	//�̺��� ��ư
	uiButton* dontHaveButton = new uiButton;
	dontHaveButton->init(_T("Donthave"), _T(".\\texture\\buttons\\Donthave.png"), 220 + 200 / 2, 65 + 50 / 2, 3);
	dontHaveButton->setDelegate(this);
	_buttons->addChild(dontHaveButton);

	//skill1 ��ư
	uiButton* skill1Button = new uiButton;
	skill1Button->init(_T("skill1"), _T(".\\texture\\buttons\\skillButtons\\skilbtn1.png"), vp.Width/2 + 150, 60, 3);
	skill1Button->setDelegate(this);
	//_buttons->addChild(skill1Button);
	_vecSkillBtns.push_back(skill1Button);

	//skill2 ��ư
	uiButton* skill2Button = new uiButton;
	skill2Button->init(_T("skill2"), _T(".\\texture\\buttons\\skillButtons\\skilbtn2.png"), vp.Width / 2 + 150 +150, 60, 3);
	skill2Button->setDelegate(this);
	//skill1Button->addChild(skill2Button);
	_vecSkillBtns.push_back(skill2Button);

	//skill1 ��ư
	uiButton* skill3Button = new uiButton;
	skill3Button->init(_T("skill3"), _T(".\\texture\\buttons\\skillButtons\\skilbtn3.png"), vp.Width / 2 + 150 + 300, 60, 3);
	skill3Button->setDelegate(this);
	//skill1Button->addChild(skill3Button);
	_vecSkillBtns.push_back(skill3Button);

	//��ȭ ��ư
	_strongBtn = new uiButton;
	_strongBtn->init(_T("strong"), _T(".\\texture\\buttons\\skillButtons\\Strong.png"), vp.Width / 2 + 150 + 150, vp.Height - 60, 3);
	_strongBtn->setDelegate(this);
	//_buttons->addChild(strongBtn);
	


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
	}
	//�� ��ư, ������ ��ư, �̺��� ��ư ������Ʈ
	if (_buttons)
		_buttons->update();

	//������ ��ư Ŭ������ ���� ��ų ��ư�� ��ȭ ��ư�� ���ڰ��ؾ��Ѵ�.
	if (_isHaveCharacter)
	{
		//��ų ��ư ������Ʈ
		for (int i = 0; i < _vecPlayerCharacters[_characterIdx]->_skillNum; ++i)
		{
			if (_vecSkillBtns[i])
				_vecSkillBtns[i]->update();
		}
		//��ȭ ��ư ������Ʈ
		if (_strongBtn)
			_strongBtn->update();

		D3DDEVICE->LightEnable(_characterSpotLightIdx, TRUE);
	}
	else
	{
		D3DDEVICE->LightEnable(_characterSpotLightIdx, FALSE);
	}

	//����
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		savePlayerInformation(_T("iniData"), _T("playerInfo"));
		saveCharactersData(_T("iniData"), _T("playerCharacters"));
	}
	if (_cam)
	{
		_cam->update();
	}

	_vecPlayerCharacters[_characterIdx]->Update();
}

void storeScene::release()
{
	SAFE_OBJRELEASE(_buttons);
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

	//������ ��ư ������ ���� ��ų ��ư�� ��ȭ ��ư�� ��µǾ�� �Ѵ�
	if (_isHaveCharacter)
	{
		//��ų ��ư ����
		for (int i = 0; i < 3; ++i)
		{
			if (_vecSkillBtns[i])
				_vecSkillBtns[i]->render();
		}
		//��ȭ ��ư ����
		if (_strongBtn)
			_strongBtn->render();

	}
	
	renderCharacterGround();

	if(_isHaveCharacter)
		renderHaveCharacters();
	
	//FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("storeScene"), lstrlen(_T("storeScene")),
	//	&RectMake(100, 100, 100, 100),
	//	DT_LEFT | DT_CENTER | DT_NOCLIP,
	//	BLACK);
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
		//�������� ĳ���͸� �����ش�.
		_isHaveCharacter = true;	
	}
	else if (d->getButtonName() == _T("Donthave"))
	{
		_isHaveCharacter = false;
	}
	else if (d->getButtonName() == _T("skill1"))
	{
		//��ų1 �ִϸ��̼� ��� �� ��ų ���� ���
		_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[STORE_ANIM_ATTACK01]);
		//_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[0]);
	}
	else if (d->getButtonName() == _T("skill2"))
	{
		//��ų2 �ִϸ��̼� ��� �� ��ų ���� ���
		//ĳ���Ͱ� �ر��� ��ų ������ 2�̻��̸� ��ų��ư Ŭ���� ������
		if(_vecPlayerCharacters[_characterIdx]->_skillNum >=2)
			_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[STORE_ANIM_ATTACK02]);
	}
	else if (d->getButtonName() == _T("skill3"))
	{
		//��ų1 �ִϸ��̼� ��� �� ��ų ���� ���
		//ĳ���Ͱ� �ر��� ��ų ������ 3�̻��̸� ��ų��ư Ŭ���� ������
		if (_vecPlayerCharacters[_characterIdx]->_skillNum >= 3)
			_vecPlayerCharacters[_characterIdx]->setCharacterAnimationset(_vecPlayerCharacters[_characterIdx]->_aniIndex[STORE_ANIM_ATTACK03]);
	}
	//
	else if (d->getButtonName() == _T("strong"))
	{

	}
}

void storeScene::setSky()
{

	_sky = new cube;
	_sky->init();
	//�ϴ��� �������� 1000���� ���δ�.
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
	//�¾�
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

	//���� ���
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
	vPos = D3DXVECTOR3(-3.5f, 2.0f, -3.0f);				//����Ʈ ����Ʈ ��ġ ����
	stSpotLight.Position = vPos;

	stSpotLight.Phi = D3DX_PI / 4.0f;					//���� ������ ����
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
//ĳ���� ���ö��� ĳ���� ������
void storeScene::renderHaveCharacters()
{
	if (_vecPlayerCharacters.size() == 0)
		return;

	_vecPlayerCharacters[_characterIdx]->Render();
}

void storeScene::upgradeCharacterInfo()
{

}

#ifdef UNICODE
void storeScene::loadPlayerInformation(const WCHAR * folder, const WCHAR * fileName)
{
	//�÷��̾ ������ �ݾ� ������ �о����
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
	//���� ���� �������� ĳ���� �� ���� �о����
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
		tmpCharacter->_characterAtk = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterAtk"));
		tmpCharacter->_characterDef = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterDef"));
		tmpCharacter->_characterSkillLv[0] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill0Lv"));
		if (tmpCharacter->_characterSkillLv[0] > 0)
			tmpCharacter->_skillNum++;
		tmpCharacter->_characterSkillLv[1] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill1Lv"));
		if (tmpCharacter->_characterSkillLv[1] > 0)
			tmpCharacter->_skillNum++;
		tmpCharacter->_characterSkillLv[2] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill2Lv"));
		if (tmpCharacter->_characterSkillLv[2] > 0)
			tmpCharacter->_skillNum++;
		//skinned mesh �����ϱ�
		skinnedMesh* pSkinnedMesh = new skinnedMesh;
		WCHAR xFileFolder[256];
		swprintf(xFileFolder, _T(".\\xFile\\%s"), tmpCharacter->characterName);
		WCHAR xFileName[256];
		swprintf(xFileName, _T("%s.X"), tmpCharacter->characterName);
		pSkinnedMesh->init(subjectName, xFileFolder, xFileName);
		pSkinnedMesh->setAnimationSet(tmpCharacter->_aniIndex[STORE_ANIM_IDLE]);									//�ִϸ��̼��� idle ���·� ��ȯ
		if (lstrcmp(tmpCharacter->characterName, _T("zealot")) == 0)
			D3DXMatrixScaling(&tmpCharacter->_matS, 12.0f, 12.0f, 12.0f);	//������ ����
		else
			D3DXMatrixScaling(&tmpCharacter->_matS, 0.058f, 0.058f, 0.058f);	//������ ����
		tmpCharacter->_matWorld = tmpCharacter->_matS;
		pSkinnedMesh->setParentMatrix(&tmpCharacter->_matWorld);			//�����Ʈ������ ����
		tmpCharacter->setCharacterSkinnedMesh(pSkinnedMesh);				//

		_vecPlayerCharacters.push_back(tmpCharacter);						//���Ϳ� ĳ���� ���
	}
}

void storeScene::saveCharactersData(const WCHAR* folder, const WCHAR * fileName)
{

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
