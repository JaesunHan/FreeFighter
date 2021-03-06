// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>

using namespace std;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <PxPhysicsAPI.h>
#include <foundation\PxAllocatorCallback.h>
#include <foundation\PxErrorCallback.h>

#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PxFoundationDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PhysX3CharacterKinematicDEBUG_x86.lib")

using namespace physx;

extern HWND		_hWnd;
#define g_hWnd _hWnd
extern POINT	_ptMouse;
extern bool		_isDebug;
extern int		_numOfLight;

#define SINGLETONE(class_name)			\
private:								\
	class_name();						\
	~class_name();						\
										\
public:									\
	static class_name* GetInstance()	\
	{									\
		static class_name temp;			\
		return &temp;					\
	}									\
private:								\

typedef struct tagPC_Vertex
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

	// 플렉서블 vertex format
	// 데이터 포멧을 알려주는듯
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};

	tagPC_Vertex()
	{
		p = D3DXVECTOR3(0, 0, 0);
		c = D3DCOLOR_XRGB(0, 0, 0);
	}
} ST_PC_VERTEX;

typedef struct tagPT_Vertex
{
	D3DXVECTOR3	p;
	D3DXVECTOR2 t;

	// 플렉서블 vertex format
	// 데이터 포멧을 알려주는듯
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_TEX1
	};

	tagPT_Vertex()
	{
		p = D3DXVECTOR3(0, 0, 0);
		t = D3DXVECTOR2(0, 0);
	}
} ST_PT_VERTEX;

typedef struct tagPNT_Vertex
{
	D3DXVECTOR3	p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	// 플렉서블 vertex format
	// 데이터 포멧을 알려주는듯
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};

	tagPNT_Vertex()
	{
		p = D3DXVECTOR3(0, 0, 0);
		n = D3DXVECTOR3(0, 0, 0);
		t = D3DXVECTOR2(0, 0);
	}
} ST_PNT_VERTEX;

typedef struct TRANSLATION
{
	int tick;
	D3DXVECTOR3 pos;

	TRANSLATION() : tick(0), pos(0, 0, 0) {}
} ST_POS_SAMPLE;

typedef struct ROTATION
{
	int tick;
	D3DXVECTOR3 axis;
	float angle;
	D3DXQUATERNION quaternion;

	ROTATION() : tick(0), axis(0, 0, 0), angle(0.0f)
	{
		D3DXQuaternionIdentity(&quaternion);
	}
} ST_ROT_SAMPLE;

struct tagSphere
{
	D3DXVECTOR3	center;
	float		radius;
	bool		isPicked;
	LPD3DXMESH	sphere;

	tagSphere()
		: center(0.0f, 0.0f, 0.0f)
		, radius(1.0f)
		, isPicked(false)
		, sphere(NULL)
	{}

	~tagSphere()
	{
		if (sphere)
			sphere->Release();
	}
};

// ========================== 수학 ==========================
#define DEG2RAD (D3DX_PI / 180.0f)
#define RAD2DEG (180.0f / D3DX_PI)

// ========================== 그 외 매크로 ==========================
#define SAFE_DELETE(p) {if (p) delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p) {if (p) delete[] p; p = NULL;}
#define SAFE_RELEASE(p) { if (p) p->Release(); p = NULL; }
#define SAFE_OBJRELEASE(p) { if(p) {p->release(); SAFE_DELETE(p);}}

#ifdef UNICODE
#define _T(str) L##str
#else
#define _T(str) str
#endif

#define SYNTHESIZE(varType, varName, funName)			 \
protected: varType varName;								 \
public: varType Get##funName(void) { return varName; }	 \
public: void Set##funName(varType var) { varName = var; }\
private:												 \

#define SYNTHESIZE_REF(varType, varName, funName)		  \
protected: varType varName;								  \
public: varType& Get##funName(void) { return varName; }	  \
public: void Set##funName(varType& var) { varName = var; }\
private:												  \

#define BLACK		D3DCOLOR_XRGB(  0,   0,   0)
#define RED			D3DCOLOR_XRGB(255,   0,   0)
#define GREEN		D3DCOLOR_XRGB(  0, 255,   0)
#define BLUE		D3DCOLOR_XRGB(  0,   0, 255)
#define CYAN		D3DCOLOR_XRGB(  0, 255, 255)
#define MAGENTA		D3DCOLOR_XRGB(255,   0, 255)
#define YELLOW		D3DCOLOR_XRGB(255, 255,   0)
#define WHITE		D3DCOLOR_XRGB(255, 255, 255)

// ========================== 매니저들 ==========================
#include "randomFunction.h"
#include "deviceManager.h"
#include "keyManager.h"
#include "textureManager.h"
#include "materialManager.h"
#include "timeManager.h"
#include "objLoadManager.h"
#include "ASELoadManager.h"
#include "fontManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "imageManager.h"
#include "iniDataManager.h"
#include "skinnedMeshManager.h"
#include "physXManager.h"


#include "commonMacroFunction.h"
