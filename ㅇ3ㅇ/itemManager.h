#pragma once

class item;
class playerManager;
class enemyManager;

class itemManager
{
private:

	vector<item*>		_vItem;					//아이템의 정보를 담아 줄 벡터
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
	void CreateItem(D3DXVECTOR3 tra);

	//언젠가 쓰일 그날을 위해서
	void setPlayerAdressLink(playerManager* player) { _pm = player; }
	void setEnemyAdressLink(enemyManager* enemy) { _em = enemy; }



	//물리엔진
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }

};

