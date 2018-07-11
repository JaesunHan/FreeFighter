#pragma once


//종류



class player;
class enemyManager;





class playerManager
{

private:
	enemyManager * _enemy;										//추후에 에너미랑 상호작용을 위한 코드

private:
	vector<player*>		_vPlayer;					//플레이어가 가질 정보를 담을 벡터값
	vector<player*>::iterator _viPlayer;

private:
	PxControllerManager * _cm;
	PxMaterial*				_material;


public:
	playerManager();
	~playerManager();

	void Init();
	void Update();
	void Render();

	void setLucius();
	void setGigas();
	void setAranzebia();
	void setKnight();

	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }


	vector<player*>	GetPlayer() { return _vPlayer; }							//에네미가 플레이어꺼 정보를 받을때
	void SetMemoryEnemyManager(enemyManager* EM) { _enemy = EM; }		//에너미에서 쓰게 만든거

};

