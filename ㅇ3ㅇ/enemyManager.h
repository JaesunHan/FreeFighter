#pragma once

class enemy;
class player;

class enemyManager
{
private:
	player* _player;

private:
	vector<enemy*> _vEnemy;

private:
	int _stage;
	int _timer;

public:
	enemyManager();
	~enemyManager();

	void Init();
	void Update();
	void Render();

	void SetTarget(D3DXVECTOR3* playerPos);
	void ChangeStage(int num);

	void CreateEnemy();

	vector<enemy*> GetEnemy() { return _vEnemy; }
	void SetPlayerMemAdressLink(player* pP) { _player = pP; }
	
};

