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

	D3DXVECTOR3			_vTrans;				//��ġ����
	D3DXVECTOR3			_vScale;				//ũ�����
	D3DXVECTOR3			_vRotate;				//���¹���

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
	virtual ~item();


#ifdef UNICODE	
	//������ ���� �ִ�      ����,                ���� �̸�
	virtual void init();

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra);

	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 tra, float gold);


#else
	void init(const char* folder, const char* file);
#endif
	virtual void update();
	virtual void render();
	virtual void release();



	//ĳ���Ͱ� ������ ������ ������ �� ���Ÿ���?
	//�����غ��� �̰� �÷��̾ �ؾߵǴ°ǰ�?
	void onTriggerItem();

	//ĳ���Ͱ� �������� ����ߴµ� ���� �������� ������� �����Ҷ� �� �Լ�
	//�̰͵� ����������??
	void getItem();

	//��ų�̶� ����ġ�� ���� �� ����
	int getPrice() { return _price; }

	//������ Ÿ�� ����(0.����, 1.���)
	int getItemType() { return _itemType; }

	//������ ȿ�� ��������(�����ڿ�����)
	int getItemEffect() { return _itemEffect; }

	void setPlayer(playerManager* player) { _player = player; }
	void setEM(enemyManager* enemy) { _enemy = enemy; }
};