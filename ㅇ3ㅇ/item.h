#pragma once

class skinnedMesh;
class item
{
private:
	//아이템의 형체
	LPD3DXMESH _itemMesh;
	//skinnedMesh * _itemSkin;
	vector<tagObjectMtlData>		_vecItemMtlData;

	//충돌 처리 할 때 쓸 컨트롤러
	PxController* _itemController;

	//적용 효과
	//1. HP 회복  of    2. Gold 획득량
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
	//아이템 모뎅이 있는      폴더,                파일 이름
	void init(const WCHAR* folder	, const WCHAR* file);

#else
	void init(const char* folder, const char* file);
#endif
	void update();
	void render();
	void release();

	
	//HP 포션 먹었을 때 data + _applyData
	void  usingItem(float& data);
	//골드 먹었을 때 data + _applyData
	void usingItem(int& data);




};

