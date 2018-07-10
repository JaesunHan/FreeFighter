#pragma once
#include "interfaceCharacter.h"
#include "sceneInterface.h"
#include "uiButton.h"


#define		MAX_SKILL_NUM		3
#define		MAX_STRING_NUM		1025


enum STORE_ANIMATIONSET
{
	STORE_ANIM_NONE = -1,
	STORE_ANIM_IDLE = 0,
	STORE_ANIM_ATTACK00,
	STORE_ANIM_ATTACK01,
	STORE_ANIM_ATTACK02,
	STORE_ANIM_ATTACK03
};


//class skinnedMesh;
class cube;
class camera;

class storeCharacter : public interfaceCharacter
{
public:
	// skinned mesh : xfile �о�� ������ ����
	//skinnedMesh*		characterSkinMesh;
	//ĳ���� ����
	int					_characterLv;
	//ĳ���� ����ġ
	int					_characterExp;
	//ĳ���Ͱ� ���� �ִ� ��ų���� ����(3��)
	int					_characterSkillLv[MAX_SKILL_NUM];
	//ĳ������ ���ݷ� ����
	float				_characterAtk, _characterDef;

	D3DXMATRIX			_matWorld, _matS, _matR, _matT;
	//�ִϸ��̼� ��ȣ
	UINT				_aniIndex[ACT_END];
	//ĳ���Ͱ� ������ ĳ���� ����
	int					_skillNum;
	

#ifdef UNICODE	
	WCHAR				characterName[1024];
#else
	char*				characterName;
#endif
public :
	void init();


	storeCharacter();
	~storeCharacter();

public: 
	void setCharacterSkinnedMesh(skinnedMesh* pSkinnedMesh)
	{
		_skinnedMesh = pSkinnedMesh;
	}
	//ĳ������ �ִϸ��̼� ����
	void setCharacterAnimationset(UINT animIdx);


};

class gameObject;
class storeScene : public _scene, public _buttonDelegate
{
private:
	uiButton*					_buttons;
	vector<uiButton*>			_vecSkillBtns;
	uiButton*					_strongBtn;
	//uiButton*					_haveButton;		//������ ��ư

	//�÷��̾ ������ ��差
	int							_playerGold;
	//�÷��̾ ������ ĳ���Ͱ� ��� ����
	vector<storeCharacter*>		_vecPlayerCharacters;
	//�÷��̾ ������ �� ĳ���� ����
	int							_playerCharacterNum;

	//�ϴ÷� �� ť��
	cube*						_sky;
	camera*						_cam;

	vector<gameObject>			_vecGround;
	vector<gameObject>			_vecGroundSurface;
	D3DXVECTOR3					_translationV;
	//ĳ���� ���� �ε���
	int							_characterIdx;
	//������ ��ư ������ true, �̺��� ��ư �θ��� false
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
	//�����͸� �о�ö� ȣ���� �Լ�(init ���� �ѹ� ȣ��)
	void loadCharactersData(const WCHAR* folder, const WCHAR* fileName);
	//����� �����͸� ����(update ���� ��ȭ �����ø��� ȣ��)
	void saveCharactersData(const WCHAR* folder, const WCHAR* fileName);
#else
	void loadPlayerInformation(const char*folder, const char* fileName);
	void savePlayerInformation(const char* folder, const char* fileName);
	//�����͸� �о�ö� ȣ���� �Լ�(init ���� �ѹ� ȣ��)
	void loadCharactersData(const char* folder, const char* fileName);
	//����� �����͸� ����(update ���� ��ȭ �����ø��� ȣ��)
	void saveCharactersData(const char* folder, const char* fileName);
#endif // UNICODE


	void cameraZoom(float zoom);
};

