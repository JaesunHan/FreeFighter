#include "stdafx.h"
#include "deviceManager.h"


deviceManager::deviceManager()
{
	_d3d = NULL;
	_d3dDevice = NULL;

	// D3D 컴포넌트 객체를 버전에 맞게 생성
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// 디바이스 정보 알아올 그릇
	D3DCAPS9 tempCaps;
	_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &tempCaps);
	

	int vertexProcessing;
	// D3DDEVCAPS_HWTRANSFORMANDLIGHT == 주석 타고 들어가보면 설명 다 적혀있음 ㅇㅇ
	if (tempCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS tempParam;
	ZeroMemory(&tempParam, sizeof(D3DPRESENT_PARAMETERS));
	tempParam.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 책에 이 것이 가장 효율적인 방법이라고 나와있음(왜인지는 잘...)
	tempParam.Windowed = true;						// 이 창이 윈도우 모드인지 전체 화면인지
	tempParam.BackBufferFormat = D3DFMT_UNKNOWN;	// 백버퍼 포멧 설정 정해주기(기본값이 unknown)
	tempParam.EnableAutoDepthStencil = true;		// ???
	tempParam.AutoDepthStencilFormat = D3DFMT_D24S8;	// 오토 뎁스 스텐실 버퍼의 크기

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,	// 어뎁터
		D3DDEVTYPE_HAL,		// 디바이스 타입
		_hWnd,				// 윈도우 핸들
		vertexProcessing,	// 이 디바이스를 사용해서 소프트웨어 프로세싱을 할 건지, 하드웨어 프로세싱을 할 건지
		&tempParam,			// 디바이스 생성 값 들(임의로 설정 가능)
		&_d3dDevice);		// 디바이스 인터페이스를 받을 친구
}


deviceManager::~deviceManager()
{
}

void deviceManager::destroy()
{
	ULONG u = _d3d->Release();
	u = _d3dDevice->Release();	// Release에서 반환된 ref count의 값이 0이 아니면 해제가 덜됐다는 뜻

	assert(u == 0 && "디바이스를 이용해 생성한 객체 중 해제되지 않은 객체가 있다!!");
}
