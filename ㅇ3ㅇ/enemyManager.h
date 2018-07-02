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

public:
	enemyManager();
	~enemyManager();

	void Init();
	void Update();
	void Render();

	void ChangeStage(int num);

	void SetPlayerMemAdressLink(player* pP) { _player = pP; }
};

