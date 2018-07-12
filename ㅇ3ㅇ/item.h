#pragma once

class skinnedMesh;
class item
{
private:
	//�������� ��ü
	LPD3DXMESH _itemMesh;
	//skinnedMesh * _itemSkin;
	vector<tagObjectMtlData>		_vecItemMtlData;

	//�浹 ó�� �� �� �� ��Ʈ�ѷ�
	PxController* _itemController;

	//���� ȿ��
	//1. HP ȸ��  of    2. Gold ȹ�淮
	float _applyData;
	//

	D3DXMATRIX			_matWorld;	

	D3DXVECTOR3			_vTrans;
	D3DXVECTOR3			_vScale;
	D3DXVECTOR3			_vRotate;


public:
	item();
	~item();


#ifdef UNICODE	
	//������ ���� �ִ�      ����,                ���� �̸�
	void init(const WCHAR* folder	, const WCHAR* file);

#else
	void init(const char* folder, const char* file);
#endif
	void update();
	void render();
	void release();

	
	//HP ���� �Ծ��� �� data + _applyData
	void  usingItem(float& data);
	//��� �Ծ��� �� data + _applyData
	void usingItem(int& data);




};

