#include "stdafx.h"
#include "storeScene.h"


storeScene::storeScene()
	: _buttons(NULL)
{
}


storeScene::~storeScene()
{
}

HRESULT storeScene::init()
{
	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);

	_buttons = new uiButton;
	_buttons->init(_T("Back"), _T(".\\texture\\buttons\\Back.png"), vp.Width - 120, vp.Height - 70, 3);
	_buttons->setDelegate(this);

	
	loadPlayerInformation(_T("iniData"), _T("playerInfo"));
	loadCharactersData(_T("iniData"), _T("playerCharacter"));

	return S_OK;
}

void storeScene::update()
{
	if (_buttons)
		_buttons->update();
	//����
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		savePlayerInformation(_T("iniData"), _T("playerInfo"));
		saveCharactersData(_T("iniData"), _T("playerCharacters"));
	}

}

void storeScene::release()
{
	SAFE_OBJRELEASE(_buttons);
}

void storeScene::render()
{
	if (_buttons)
		_buttons->render();

	FONTMANAGER->findFont(fontManager::FONT_DEFAULT)->DrawTextW(NULL, _T("storeScene"), lstrlen(_T("storeScene")),
		&RectMake(100, 100, 100, 100),
		DT_LEFT | DT_CENTER | DT_NOCLIP,
		BLACK);
}

void storeScene::OnClick(uiButton* d)
{
	if (d->getButtonName() == _T("Back"))
	{
		SCENEMANAGER->changeScene(_T("mainScene"));
		SCENEMANAGER->sceneInit();
	}
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
		storeCharacter tmpCharacter;
		tmpCharacter.characterName = INIDATA->loadDataString(folder, fileName, subjectName, _T("CharacterName"));
		tmpCharacter.characterLv = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterLv"));
		tmpCharacter.characterExp = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterExp"));
		tmpCharacter.characterAtk = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterAtk"));
		tmpCharacter.characterDef = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("CharacterDef"));
		tmpCharacter.characterSkillLv[0] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill0Lv"));
		tmpCharacter.characterSkillLv[1] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill1Lv"));
		tmpCharacter.characterSkillLv[2] = INIDATA->loadDataInterger(folder, fileName, subjectName, _T("Skill2Lv"));

		_vecPlayerCharacters.push_back(tmpCharacter);
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


