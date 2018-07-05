#pragma once
#include "interfaceCharacter.h"
#include "sceneInterface.h"
#include "uiButton.h"
#include "skinnedMesh.h"

#define		MAX_SKILL_NUM		3

struct storeCharacter : public interfaceCharacter
{
	// skinned mesh : xfile �о�� ������ ����
	skinnedMesh*		characterSkinMesh;
	//ĳ���� ����
	int					characterLv;
	//ĳ���� ����ġ
	int					characterExp;
	//ĳ���Ͱ� ���� �ִ� ��ų���� ����(3��)
	int					characterSkillLv[MAX_SKILL_NUM];

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
	
	//�÷��̾ ������ ��差
	int							_playerGold;
	//�÷��̾ ������ ĳ���Ͱ� ��� ����
	vector<storeCharacter>		_playerCharacters;



public:
	storeScene();
	~storeScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	virtual void OnClick(uiButton* d) override;
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



};

