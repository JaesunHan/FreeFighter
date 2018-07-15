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

	////�������� ��ü
	//LPD3DXMESH _itemMesh;
	//vector<tagObjectMtlData>		_vecItemMtlData;

	vector<gameObject>			_itemMesh;

	D3DXMATRIX			_matWorld;	

	D3DXVECTOR3			_vTrans;
	D3DXVECTOR3			_vScale;
	D3DXVECTOR3			_vRotate;

	tagItemType			_itemType;			//������ ����
	float						_itemEffect;		//�������� �����̸� ȸ��, ���̸� ȹ�淮
	int							_price;					//��ų�̳� �����Ҷ��� ����
	
	playerManager*		_player;
	enemyManager*		_enemy;



private:

	//skinnedMesh * _itemSkin;


	//�浹 ó�� �� �� �� ��Ʈ�ѷ�
	PxController* _itemController;

	//���� ȿ��
	//1. HP ȸ��  of    2. Gold ȹ�淮
	//float _applyData;
	//




public:
	item();
	~item();


#ifdef UNICODE	
	//������ ���� �ִ�      ����,                ���� �̸�
	virtual void init(const WCHAR* folder	, const WCHAR* file);

	virtual void init(const WCHAR* folder, const WCHAR* file, D3DXVECTOR3 Position);

	virtual void init(const WCHAR* folder, const WCHAR* file, D3DXVECTOR3 Position, float gold);


#else
	void init(const char* folder, const char* file);
#endif
	virtual void update();
	virtual void render();
	virtual void release();



	//ĳ���Ͱ� ������ ������ ������ �� ���Ÿ���?
	void onTriggerItem();	

	//ĳ���Ͱ� �������� ����ߴµ� ���� �������� ������� �����Ҷ� �� �Լ�
	void getItem();

	//������ ȿ�� ��������(�����ڿ�����)
	int getItemEffect() { return _itemEffect; }

	void setPlayer(playerManager* player) { _player = player; }
	void setEM(enemyManager* enemy) { _enemy = enemy; }
};