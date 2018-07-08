#pragma once
#include "interfaceCharacter.h"
#include "sceneInterface.h"
#include "uiButton.h"


#define		MAX_SKILL_NUM		3
#define		MAX_STRING_NUM		1025

class skinnedMesh;
class cube;
class camera;
class storeCharacter : public interfaceCharacter
{
public:
	// skinned mesh : xfile 읽어온 정보가 들어가고
	//skinnedMesh*		characterSkinMesh;
	//캐릭터 레벨
	int					characterLv;
	//캐릭터 경험치
	int					characterExp;
	//캐릭터가 갖고 있는 스킬들의 레벨(3개)
	int					characterSkillLv[MAX_SKILL_NUM];
	//캐릭터의 공격력 방어력
	float				characterAtk, characterDef;

#ifdef UNICODE	
	WCHAR*				characterName;
#else
	char*				characterName;
#endif
};


class storeScene : public _scene, public _buttonDelegate
{
private:
	uiButton*					_buttons;
	
	//플레이어가 보유한 골드량
	int							_playerGold;
	//플레이어가 보유한 캐릭터가 담길 벡터
	vector<storeCharacter>		_vecPlayerCharacters;
	//플레이어가 보유한 총 캐릭터 갯수
	int							_playerCharacterNum;

	//하늘로 쓸 큐브
	cube*						_sky;
	camera*						_cam;
public:
	storeScene();
	~storeScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	virtual void OnClick(uiButton* d) override;

	void setSky();
	void setLight();
#ifdef UNICODE
	void loadPlayerInformation(const WCHAR* folder, const WCHAR* fileName);
	void savePlayerInformation(const WCHAR* folder, const WCHAR* fileName);
	//데이터를 읽어올때 호출할 함수(init 에서 한번 호출)
	void loadCharactersData(const WCHAR* folder, const WCHAR* fileName);
	//변경된 데이터를 저장(update 에서 강화 성공시마다 호출)
	void saveCharactersData(const WCHAR* folder, const WCHAR* fileName);
#else
	void loadPlayerInformation(const char*folder, const char* fileName);
	void savePlayerInformation(const char* folder, const char* fileName);
	//데이터를 읽어올때 호출할 함수(init 에서 한번 호출)
	void loadCharactersData(const char* folder, const char* fileName);
	//변경된 데이터를 저장(update 에서 강화 성공시마다 호출)
	void saveCharactersData(const char* folder, const char* fileName);
#endif // UNICODE



};

