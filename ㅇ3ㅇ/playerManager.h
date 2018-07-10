#pragma once


//����



class player;
class enemyManager;





class playerManager
{

private:
	enemyManager * _enemyManager;										//���Ŀ� ���ʹ̶� ��ȣ�ۿ��� ���� �ڵ�

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

	void setLucius(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	void setGigas(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	void setAranzebia(D3DXVECTOR3 scale, D3DXVECTOR3 position);
	void setKnight(D3DXVECTOR3 scale, D3DXVECTOR3 position);

	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }


	//vector<player*>	GetPlayer() { return _vPlayer; }							//���׹̰� �÷��̾ ������ ������
	//void SetMemoryEnemyManager(enemyManager* EM) { _EM = EM; }		//���ʹ̿��� ���� �����

};

