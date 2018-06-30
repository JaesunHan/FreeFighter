#pragma once
#include <vector>
using namespace std;

#include "gameObject.h"

class action;

class objectNode : public gameObject
{
	vector<objectNode*>	_child;
	D3DXMATRIX*			_parentMatrix;
	objectNode*			_parent;

	D3DXMATRIX			_nodeTM;

	vector<TRANSLATION*>	_vPosTrack;
	vector<ROTATION*>		_vRotTrack;

	// ase파일의 scene정보
private:
	DWORD	_firstFrame;
	DWORD	_lastFrame;
	DWORD	_frameSpeed;
	DWORD	_ticksPerFrame;

	DWORD	_currentFrame;

public:
	objectNode();
	~objectNode();

	virtual void init();
	virtual void init(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz);
	virtual void release();
	virtual void update();
	virtual void render();

	void addChild(objectNode* child);

	void addPosTrack(TRANSLATION* p);
	void addRotTrack(ROTATION* r);

	void setSceneInfo(DWORD first, DWORD last, DWORD frameSpeed, DWORD ticksPerFrame);
	int getKeyFrame();

	void calcLocalR(IN int keyFrame, OUT D3DXMATRIX& matR);
	void calcLocalT(IN int keyFrame, OUT D3DXMATRIX& matT);

	inline void setWorldMatrix(D3DXMATRIX m) { _worldMatrix = m; }
	inline D3DXMATRIX getWorldMatrix() { return _worldMatrix; }
	inline void setLocalMatrix(D3DXMATRIX m) { _localMatrix = m; }
	inline D3DXMATRIX getLocalMatrix() { return _localMatrix; }
	inline void setNodeTm(D3DXMATRIX m) { _nodeTM = m; }
	inline D3DXMATRIX getNodeTm() { return _nodeTM; }

	inline void setParentMatrix(D3DXMATRIX* p) { _parentMatrix = p; }
	inline D3DXMATRIX* getParentMatrix() { return _parentMatrix; }
	inline void setParent(objectNode* p) { _parent = p; }
	inline objectNode* getParent() { return _parent; }
};

