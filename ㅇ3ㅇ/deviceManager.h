#pragma once

#define DEVICEMANAGER	deviceManager::GetInstance()
#define D3DDEVICE		deviceManager::GetInstance()->getDevice()

#ifndef g_pDeviceManager
#define g_pDeviceManager DEVICEMANAGER
#endif

#ifndef g_pD3DDevice
#define g_pD3DDevice D3DDEVICE
#endif

class deviceManager
{
	SINGLETONE(deviceManager)

private:
	LPDIRECT3D9			_d3d;		// directX 객체 자체
	LPDIRECT3DDEVICE9	_d3dDevice;	// 컴포넌트 사용하기 위한 객체

public:
	void destroy();

	inline LPDIRECT3DDEVICE9 getDevice() { return _d3dDevice; }
};

