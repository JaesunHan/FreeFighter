#pragma once

#include "gameObject.h"

#define ROTATEITEM	(3.0f * DEG2RAD)

class playerManager;
class enemyManager;

enum tagItemType
{
	ITEM_NONE = -1,
	ITEM_POTION,
	ITEM_GOLD,
	ITEM_ATTACK,
	ITEM_SPEED,
	ITEM_DEFENCE,
	ITEM_END
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

	D3DXVECTOR3			_vPosition;			//��ġ����
	D3DXVECTOR3			_vTrans;				//�̵�����
	D3DXVECTOR3			_vScale;				//ũ�����
	D3DXVECTOR3			_vRotate;				//���¹���

	tagItemType			_itemType;			//������ ����
	float						_itemEffect;		//�������� �����̸� ȸ��, ���̸� ȹ�淮
	bool							_attackBoost;		//������ ��������
	bool							_speedBoost;		//�̵��ӵ� �����Ǽ�
	bool							_defenceBoost;	//���� ���� �����
	int							_price;					//��ų�̳� �����Ҷ��� ����

	playerManager*		_player;
	enemyManager*		_enemy;

	float						_startHeight;
	float						_curveHeight;

	LPD3DXMESH _Mesh;
	float			_radius;

private:



	bool _isAir;
	bool	_isNotGravity;
	float _angleX, _angleY, _angleZ;

	//skinnedMesh * _itemSkin;


	//�浹 ó�� �� �� �� ��������
	//PxController* _itemController;
	//PxVec3			_velocity;
	//
	//PxControllerManager**	_cm;
	//PxMaterial*				_material;

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
	//������ �𵨰� ��ġ ����
	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos);
	//������ �𵨰� ��ġ ������ ��差
	virtual void init(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos, float gold);


#else
	void init(const char* folder, const char* file);
#endif
	virtual void update();
	virtual void render();
	virtual void release();

	//void setLight();

	//������ ���شٿ�!!
	virtual void upDown();


	//ĳ���Ͱ� ������ ������ ������ �� ���Ÿ���?
	//�����غ��� �̰� �÷��̾ �ؾߵǴ°ǰ�?
	void onTriggerItem();

	//ĳ���Ͱ� �������� ����ߴµ� ���� �������� ������� �����Ҷ� �� �Լ�
	//�̰͵� ����������??
	void getItem();

	//��ų�̶� ����ġ�� ���� �� ����
	int getPrice() { return _price; }

	//������ Ÿ�� ����
	int getItemType() { return _itemType; }

	//������ ȿ�� ��������(�����ڿ�����)
	float getItemEffect() { return _itemEffect; }
	
	//������ ���������� �������°�????
	float getItemRadius() { return _radius; }

	void setPlayer(playerManager* player) { _player = player; }
	void setEM(enemyManager* enemy) { _enemy = enemy; }
};