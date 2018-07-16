#pragma once
class cube;
class background
{
private:
	
	LPD3DXMESH						_meshMap;			//�� �޽�
	vector<tagObjectMtlData>		_vecMapMtlData;

	LPD3DXMESH						_meshSurface;			//surface �޽�
	vector<tagObjectMtlData>		_vecSurfaceMtlData;

	D3DXMATRIX						_mapMatWorld;			//���� ��ġ�� ��ġ

	cube*							_sky;

	PxController*					_pController;
	vector<PxController*>			_vecWallsController;
	PxControllerManager**			_pCM;
	PxMaterial*						_pMaterial;

	int								_cntWallsController;

public:
	background();
	~background();
	HRESULT init();					//�⺻ �ϴ� �� ������� ����
#ifdef UNICODE
	//				�ϴ��ؽ��İ��ִ� ������ �����̸�,		�� ���� �ִ� ������ �����̸�
	HRESULT init(WCHAR*	skyFolder, WCHAR* skyFileName, WCHAR* mapFolder, WCHAR* mapFileName);
#else 
	HRESULT init(char*	skyFolder, char* skyFileName, char* mapFolder, char* mapFileName);
#endif // UNICODE

	
	void update();
	void render();
	void release();
	void setLigh();
	void setSky();

	//�ٴ� ��Ʈ�ѷ�
	void createGroundController(PxControllerManager** cm, PxMaterial* m, D3DXVECTOR3 sizeVector);
	//�� ��Ʈ�ѷ�
	void createWallsController();
	//������ �� ��Ʈ�ѷ��� ��� ��ġ, ��ŭ ȸ�� ����
	PxController* createWallBaseController(PxExtendedVec3 pos, PxVec3 upDir, D3DXVECTOR3 sizeVector);

	void createWall(D3DXVECTOR3 centerPos, vector<int>& skipIndeice);
	//������ ���� �� ��Ʈ�ѷ��� ��ġ ������
	//����� �������� 8������ ���� �����Ѵ�.				�� ����    ���° ���Ϳ�Һ���
	void setWallsControllerPos(D3DXVECTOR3 vCenter, int wallsNum, int startIdx);

	inline PxController* getController() { return _pController; }

};

