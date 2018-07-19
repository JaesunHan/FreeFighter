#pragma once

#include "gameObject.h"

class playerManager;
class enemyManager;

enum tagItemType
{
	NONE = -1,
	POTION,
	GOLD,
	ATTACK,
	SPEED,
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

	D3DXVECTOR3			_vTrans;				//위치백터
	D3DXVECTOR3			_vScale;				//크기백터
	D3DXVECTOR3			_vRotate;				//도는백터

	tagItemType			_itemType;			//아이템 종류
	float						_itemEffect;		//아이템이 물약이면 회복, 돈이면 획득량
	bool							_attackBoost;		//데미지 증가포숀
	bool							_speedBoost;		//이동속도 증가뽀숀
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
	virtual ~item();


#ifdef UNICODE	
	//아이템 모델이 있는      폴더,                파일 이름
	virtual void init();
	//아이템 모델과 위치 선정
	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra);
	//아이템 모델과 위치 선정과 골드량
	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra, float gold);


#else
	void init(const char* folder, const char* file);
#endif
	virtual void update();
	virtual void render();
	virtual void release();

	//void setLight();



	//캐릭터가 아이템 위에서 있을때 할 짓거리들?
	//생각해보니 이건 플레이어가 해야되는건가?
	void onTriggerItem();

	//캐릭터가 아이템을 얻긴했는데 무슨 아이템을 얻었는지 구분할때 쓸 함수
	//이것도 마찬가지네??
	void getItem();

	//스킬이랑 경험치에 쓰일 돈 정보
	int getPrice() { return _price; }

	//아이템 타입 리턴(0.포션, 1.골드)
	int getItemType() { return _itemType; }

	//아이템 효과 가져오기(접근자였던가)
	float getItemEffect() { return _itemEffect; }

	void setPlayer(playerManager* player) { _player = player; }
	void setEM(enemyManager* enemy) { _enemy = enemy; }
};