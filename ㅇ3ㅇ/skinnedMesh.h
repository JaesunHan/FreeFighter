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

	void render();
	void render(LPD3DXFRAME frame);

	void setBoneMatrixPtrs(LPD3DXFRAME frame);
	void setAnimationSet(UINT index);
	void setAnimationIndexBlend(UINT index);

	bool IsAnimationEnd();

	inline void setParentMatrix(D3DXMATRIX* p) { _parentMatrix = p; }
};

