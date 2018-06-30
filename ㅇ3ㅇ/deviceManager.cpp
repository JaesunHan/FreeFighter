#include "stdafx.h"
#include "deviceManager.h"


deviceManager::deviceManager()
{
	_d3d = NULL;
	_d3dDevice = NULL;

	// D3D ������Ʈ ��ü�� ������ �°� ����
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// ����̽� ���� �˾ƿ� �׸�
	D3DCAPS9 tempCaps;
	_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &tempCaps);
	

	int vertexProcessing;
	// D3DDEVCAPS_HWTRANSFORMANDLIGHT == �ּ� Ÿ�� ������ ���� �� �������� ����
	if (tempCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS tempParam;
	ZeroMemory(&tempParam, sizeof(D3DPRESENT_PARAMETERS));
	tempParam.SwapEffect = D3DSWAPEFFECT_DISCARD;	// å�� �� ���� ���� ȿ������ ����̶�� ��������(�������� ��...)
	tempParam.Windowed = true;						// �� â�� ������ ������� ��ü ȭ������
	tempParam.BackBufferFormat = D3DFMT_UNKNOWN;	// ����� ���� ���� �����ֱ�(�⺻���� unknown)
	tempParam.EnableAutoDepthStencil = true;		// ???
	tempParam.AutoDepthStencilFormat = D3DFMT_D24S8;	// ���� ���� ���ٽ� ������ ũ��

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,	// ���
		D3DDEVTYPE_HAL,		// ����̽� Ÿ��
		_hWnd,				// ������ �ڵ�
		vertexProcessing,	// �� ����̽��� ����ؼ� ����Ʈ���� ���μ����� �� ����, �ϵ���� ���μ����� �� ����
		&tempParam,			// ����̽� ���� �� ��(���Ƿ� ���� ����)
		&_d3dDevice);		// ����̽� �������̽��� ���� ģ��
}


deviceManager::~deviceManager()
{
}

void deviceManager::destroy()
{
	ULONG u = _d3d->Release();
	u = _d3dDevice->Release();	// Release���� ��ȯ�� ref count�� ���� 0�� �ƴϸ� ������ ���ƴٴ� ��

	assert(u == 0 && "����̽��� �̿��� ������ ��ü �� �������� ���� ��ü�� �ִ�!!");
}
