#pragma once


//����



class player;
class enemy;





class playerManager
{

private:
	enemy * _enemy;										//���Ŀ� ���ʹ̶� ��ȣ�ۿ��� ���� �ڵ�

private:
	vector<player*>		_vPlayer;					//�÷��̾ ���� ������ ���� ���Ͱ�
	vector<player*>::iterator _viPlayer;

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

	//vector<player*>	GetPlayer() { return _vPlayer; }							//���׹̰� �÷��̾ ������ ������
	//void SetMemoryEnemyManager(enemyManager* EM) { _EM = EM; }		//���ʹ̿��� ���� �����

};

