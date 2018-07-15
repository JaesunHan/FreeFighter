#pragma once

#include "gameObject.h"

class playerManager;
class enemyManager;

enum tagItemType
{
	NONE = -1,
	POTION,
	GOLD,
	END
};

class skinnedMesh;
class item
{
protected:

	////아이템의 형체
	//LPD3DXMESH _itemMesh;
	//vector<tagObjectMtlData>		_vecItemMtlData;

	vector<gameObject>			_itemMesh;

	D3DXMATRIX			_matWorld;	

	D3DXVECTOR3			_vTrans;
	D3DXVECTOR3			_vScale;
	D3DXVECTOR3			_vRotate;

	tagItemType			_itemType;			//아이템 종류
	float						_itemEffect;		//아이템이 물약이면 회복, 돈이면 획득량
	int							_price;					//스킬이나 렙업할때의 가격
	
	playerManager*		_player;
	enemyManager*		_enemy;



private:

	//skinnedMesh * _itemSkin;


	//충돌 처리 할 때 쓸 컨트롤러
	PxController* _itemController;

	//적용 효과
	//1. HP 회복  of    2. Gold 획득량
	//float _applyData;
	//




public:
	item();
	~item();


#ifdef UNICODE	
	//아이템 모델이 있는      폴더,                파일 이름
	virtual void init(const WCHAR* folder	, const WCHAR* file);

	virtual void init(const WCHAR* folder, const WCHAR* file, D3DXVECTOR3 Position);

	virtual void init(const WCHAR* folder, const WCHAR* file, D3DXVECTOR3 Position, float gold);


#else
	void init(const char* folder, const char* file);
#endif
	virtual void update();
	virtual void render();
	virtual void release();



	//캐릭터가 아이템 위에서 있을때 할 짓거리들?
	void onTriggerItem();	

	//캐릭터가 아이템을 얻긴했는데 무슨 아이템을 얻었는지 구분할때 쓸 함수
	void getItem();

	//아이템 효과 가져오기(접근자였던가)
	int getItemEffect() { return _itemEffect; }

	void setPlayer(playerManager* player) { _player = player; }
	void setEM(enemyManager* enemy) { _enemy = enemy; }
};