#pragma once

class AllocatedHierachy;

class skinnedMesh
{
private:
	LPD3DXFRAME					_root;
	LPD3DXANIMATIONCONTROLLER	_aniController;

	UINT						_currentAnimationSet;
	UINT						_maxAnimationSet;

	float						_blendTime;
	float						_passedBlendTime;

	D3DXMATRIX*					_parentMatrix;

	tagSphere					_sphere;

public:
	skinnedMesh();
	~skinnedMesh();

#ifdef UNICODE
	void init(wstring keyName, const WCHAR* folder, const WCHAR* file);
	void init(const WCHAR* folder, const WCHAR* file);
#else
	void init(string keyName, const char* folder, const char* file);
	void init(const char* folder, const char* file);
#endif
	void release();
	void destroy();
	void update();
	void update(LPD3DXFRAME frame, LPD3DXFRAME parent = NULL);
	void updateSkinnedMesh(LPD3DXFRAME frame);

	// 뷰포트가 나뉨에 따라 렌더를 2번 하는 경우가 생기는데, 이 때 애니메이션이 넘나 빨리돎
	// 그래서 진행 시간을 매개변수로 받아서 처리하려고 바꿈
	void render(float elapsedTime = TIMEMANAGER->getElapsedTime());
	void render(LPD3DXFRAME frame);

	void setBoneMatrixPtrs(LPD3DXFRAME frame);
	void setAnimationSet(UINT index);
	void setAnimationIndexBlend(UINT index);

	bool IsAnimationEnd();

	inline void setParentMatrix(D3DXMATRIX* p) { _parentMatrix = p; }

	inline tagSphere* getSphere() { return &_sphere; }
};

