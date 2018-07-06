#pragma once

class player;
class enemy;



class playerManager
{

private:
	enemy * _enemy;										//추후에 에너미랑 상호작용을 위한 코드

private:
	vector<player*>		_vPlayer;					//플레이어가 가질 정보를 담을 벡터값

public:
	playerManager();
	~playerManager();

	void Init();
	void Update();
	void Render();

	void setLucius(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	void setGigas(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	void setAranzebia(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	void setKnight(D3DXVECTOR3 scale, D3DXVECTOR3 position);

	//vector<player*>	GetPlayer() { return _vPlayer; }							//에네미가 플레이어꺼 정보를 받을때
	//void SetMemoryEnemyManager(enemyManager* EM) { _EM = EM; }		//에너미에서 쓰게 만든거

};

