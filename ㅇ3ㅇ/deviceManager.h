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
	LPDIRECT3D9			_d3d;		// directX ��ü ��ü
	LPDIRECT3DDEVICE9	_d3dDevice;	// ������Ʈ ����ϱ� ���� ��ü

public:
	void destroy();

	inline LPDIRECT3DDEVICE9 getDevice() { return _d3dDevice; }
};

