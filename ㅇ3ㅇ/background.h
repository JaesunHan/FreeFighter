#pragma once
class cube;
class background
{
private:
	
	LPD3DXMESH						_meshMap;			//맵 메시
	vector<tagObjectMtlData>		_vecMapMtlData;

	LPD3DXMESH						_meshSurface;			//surface 메시
	vector<tagObjectMtlData>		_vecSurfaceMtlData;

	D3DXMATRIX						_mapMatWorld;			//맵을 배치할 위치

	cube*							_sky;

	PxController*					_pController;
	vector<PxController*>			_vecWallsController;
	PxControllerManager**			_pCM;
	PxMaterial*						_pMaterial;

	int								_cntWallsController;

public:
	background();
	~background();
	HRESULT init();					//기본 하늘 및 배경으로 세팅
#ifdef UNICODE
	//				하늘텍스쳐가있는 폴더와 파일이름,		맵 모델이 있는 폴더와 파일이름
	HRESULT init(WCHAR*	skyFolder, WCHAR* skyFileName, WCHAR* mapFolder, WCHAR* mapFileName);
#else 
	HRESULT init(char*	skyFolder, char* skyFileName, char* mapFolder, char* mapFileName);
#endif // UNICODE

	
	void update();
	void render();
	void release();
	void setLigh();
	void setSky();

	//바닥 컨트롤러
	void createGroundController(PxControllerManager** cm, PxMaterial* m, D3DXVECTOR3 sizeVector);
	void createWallsController();
	void createWall(D3DXVECTOR3 centerPos, vector<int>& skipIndeice);
	void createLineWall(D3DXVECTOR3 centerPos);

	/*
	//벽 컨트롤러
	void createWallsController();
	//생성할 벽 컨트롤러를 어느 위치, 얼만큼 회전 할지
	PxController* createWallBaseController(PxExtendedVec3 pos, PxVec3 upDir, D3DXVECTOR3 sizeVector);

	//생성해 놓은 벽 컨트롤러의 위치 재조정
	//가운데를 기준으로 8각형의 벽이 포진한다.				벽 갯수    몇번째 벡터요소부터
	void setWallsControllerPos(D3DXVECTOR3 vCenter, int wallsNum, int startIdx);
	*/
	inline PxController* getController() { return _pController; }

};

