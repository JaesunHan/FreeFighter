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
	//저장
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
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
	//플레이어가 소지한 금액 데이터 읽어오기
	_playerGold = INIDATA->loadDataInterger(folder, fileName, _T("playerInfo"), _T("Gold"));


}
void storeScene::savePlayerInformation(const WCHAR * folder, const WCHAR * fileName)
{
}
void storeScene::loadCharactersData(const WCHAR* folder, const WCHAR * fileName)
{
	//플레이어가 소지하고 있는 금액 데이터 읽어오기
	

	storeCharacter tmpCharacter;

	//tmpCharacter



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


