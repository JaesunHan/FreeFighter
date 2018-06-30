#pragma once

#include <fstream>
#include <strstream>
#include <vector>
#include <map>
using namespace std;

#include "Asciitok.h"
#include "mtlTexData.h"

class objectNode;

#define ASELOADER	ASELoadManager::GetInstance()

class ASELoadManager
{
	SINGLETONE(ASELoadManager)

private:
	vector<tagObjectMtlData>	_materialRef;

	map<string, objectNode*>	_objs;

	//SCENE 정보 담아둘 변수들
private:
	DWORD	_firstFrame;
	DWORD	_lastFrame;
	DWORD	_frameSpeed;
	DWORD	_ticksPerFrame;

public:
#ifdef UNICODE
	objectNode* load(const WCHAR* fileName = L"");
#else
	objectNode* load(const char* fileName = "");
#endif

	void processScene(fstream& file);

	void processMaterialList(fstream& file);
	void processMaterial(fstream& file);
	void processSubMaterial(fstream& file);
	void processMapDiffuse(fstream& file, tagObjectMtlData& mtlData);
	void processMapBump(fstream& file);
	void processMapGeneric(fstream& file);

	void processGeomObject(fstream& file);
	D3DXMATRIX processTransformMatrix(fstream& file, objectNode* obj);

	void processMesh(fstream& file, objectNode* obj);
	void processVertexList(OUT vector<D3DXVECTOR3>& v, IN fstream& file);
	void processTVertexList(OUT vector<D3DXVECTOR2>& vt, IN fstream& file);
	void processFaceList(OUT vector<tagPNT_Vertex>& f, IN fstream& file, IN vector<D3DXVECTOR3>& v);
	void processTFaceList(OUT vector<tagPNT_Vertex>& f, IN fstream& file, IN vector<D3DXVECTOR2>& vt);
	void processNormals(OUT vector<tagPNT_Vertex>& f, IN fstream& file);
	void processTMAnimation(fstream& file, objectNode* obj);

	void processControlPosTrack(fstream& file, objectNode* obj);
	void processControlRotTrack(fstream& file, objectNode* obj);
	void processControlScaleTrack(fstream& file, objectNode* obj);
	void processControlPosTCB(fstream& file, objectNode* obj);
	void processControlRotTCB(fstream& file, objectNode* obj);
	void processControlScaleTCB(fstream& file, objectNode* obj);
	void processControlPosBezier(fstream& file, objectNode* obj);
	void processControlRotBezier(fstream& file, objectNode* obj);
	void processControlScaleBezier(fstream& file, objectNode* obj);

	string getToken(const char* inputData, int& cursor);
};

