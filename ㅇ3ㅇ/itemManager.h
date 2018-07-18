#pragma once

class item;
class playerManager;
class enemyManager;

class itemManager
{
private:

	vector<item*>		_vItem;					//�������� ������ ��� �� ����
												//vector<item*>::iterator _viItem;
	playerManager*		_pm;
	enemyManager*		_em;
private:
	PxControllerManager * _cm;
	PxMaterial*				_material;

public:
	itemManager();
	~itemManager();

	void Init();
	void Update();
	void Render();
	void CreateItem();

	//������ ���� �׳��� ���ؼ�
	void setPlayerAdressLink(playerManager* player) { _pm = player; }
	void setEnemyAdressLink(enemyManager* enemy) { _em = enemy; }



	//��������
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }

};

