#pragma once


//����



class player;
class enemyManager;





class playerManager
{

private:
	enemyManager * _enemy;										//���Ŀ� ���ʹ̶� ��ȣ�ۿ��� ���� �ڵ�

private:
	vector<player*>		_vPlayer;					//�÷��̾ ���� ������ ���� ���Ͱ�
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
	void setBalkiri();


	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }


	vector<player*>	GetPlayer() { return _vPlayer; }							//���׹̰� �÷��̾ ������ ������
	void SetMemoryEnemyManager(enemyManager* EM) { _enemy = EM; }		//���ʹ̿��� ���� �����

};

