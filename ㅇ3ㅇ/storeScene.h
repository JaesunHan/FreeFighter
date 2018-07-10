#pragma once
#include "interfaceCharacter.h"
#include "sceneInterface.h"
#include "uiButton.h"


#define		MAX_SKILL_NUM		3
#define		MAX_STRING_NUM		1025


enum STORE_ANIMATIONSET
{
	SOTRE_ANIM_NON = -1,
	SOTRE_ANIM_IDLE = 0,
	SOTRE_ANIM_ATTACK00,
	SOTRE_ANIM_ATTACK01,
	SOTRE_ANIM_ATTACK02,
	SOTRE_ANIM_ATTACK03
};


//class skinnedMesh;
class cube;
class camera;

class storeCharacter : public interfaceCharacter
{
public:
	// skinned mesh : xfile 읽어온 정보가 들어가고
	//skinnedMesh*		characterSkinMesh;
	//캐릭터 레벨
	int					_characterLv;
	//캐릭터 경험치
	int					_characterExp;
	//캐릭터가 갖고 있는 스킬들의 레벨(3개)
	int					_characterSkillLv[MAX_SKILL_NUM];
	//캐릭터의 공격력 방어력
	float				_characterAtk, _characterDef;

	D3DXMATRIX			_matWorld, _matS, _matR, _matT;
	//애니메이션 번호
	UINT				_aniIndex[ACT_END];
	//캐릭터가 보유한 캐릭터 갯수
	int					_skillNum;
	

#ifdef UNICODE	
	WCHAR				characterName[1024];
#else
	char*				characterName;
#endif
public :

	storeCharacter();
	~storeCharacter();

public: 
	void setCharacterSkinnedMesh(skinnedMesh* pSkinnedMesh)
	{
		_skinnedMesh = pSkinnedMesh;
	}
	//캐릭터의 애니메이션 변경
	void setCharacterAnimationset(UINT animIdx);


};

class gameObject;
class storeScene : public _scene, public _buttonDelegate
{
private:
	uiButton*					_buttons;
	vector<uiButton*>			_vecSkillBtns;
	//uiButton*					_haveButton;		//보유중 버튼

	//플레이어가 보유한 골드량
	int							_playerGold;
	//플레이어가 보유한 캐릭터가 담길 벡터
	vector<storeCharacter*>		_vecPlayerCharacters;
	//플레이어가 보유한 총 캐릭터 갯수
	int							_playerCharacterNum;

	//하늘로 쓸 큐브
	cube*						_sky;
	camera*						_cam;

	vector<gameObject>			_vecGround;
	vector<gameObject>			_vecGroundSurface;
	D3DXVECTOR3					_translationV;
	//캐릭터 선택 인덱스
	int							_characterIdx;
	//보유중 버튼 누르면 true, 미보유 버튼 부르면 false
	bool						_isHaveCharacter;
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
	void renderCharacterGround();
	void renderHaveCharacters();
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


	void cameraZoom(float zoom);
};

