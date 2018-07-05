#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{

}

HRESULT iniDataManager::init()
{

	return S_OK;
}

void iniDataManager::release()
{

}

#ifdef UNICODE
void iniDataManager::addData(const WCHAR* subject, const WCHAR* title, const WCHAR* body)
{
	//iOS -> NSMUTABLEARRAY

	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniDataManager::iniSave(const WCHAR * folder, const WCHAR * fileName)
{
	WCHAR str[256];
	WCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	swprintf(dir, L"\\%s\\%s.ini",folder, fileName);

	//현재 디렉토리 경로를 받아와주는 함쑤!
	GetCurrentDirectory(256, str);
	wcsncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}

void iniDataManager::iniSave(const WCHAR* fileName)	  
{
	WCHAR str[256];
	WCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	swprintf(dir, L"\\%s.ini", fileName);

	//현재 디렉토리 경로를 받아와주는 함쑤!
	GetCurrentDirectory(256, str);
	wcsncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}

WCHAR * iniDataManager::loadDataString(const WCHAR * folder, const WCHAR * fileName, const WCHAR * subject, const WCHAR * title)
{
	WCHAR str[256];
	WCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	swprintf(dir, L"\\%s\\%s.ini", folder, fileName);

	GetCurrentDirectory(256, str);
	wcsncat_s(str, 256, dir, 254);

	WCHAR data[66] = { NULL };
	GetPrivateProfileString(subject, title, L"", data, 64, str);


	return data;
}

WCHAR* iniDataManager::loadDataString(const WCHAR* fileName, const WCHAR* subject, const WCHAR* title)
{
	WCHAR str[256];
	WCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	swprintf(dir, L"\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	wcsncat_s(str, 256, dir, 254);

	WCHAR data[66] = { NULL };
	GetPrivateProfileString(subject, title, L"", data, 64, str);


	return data;
}


int iniDataManager::loadDataInterger(const WCHAR * folder, const WCHAR * fileName, const WCHAR * subject, const WCHAR * title)
{
	WCHAR str[256];
	WCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	swprintf(dir, L"\\%s\\%s.ini", folder, fileName);

	GetCurrentDirectory(256, str);
	wcsncat_s(str, 256, dir, 254);



	return GetPrivateProfileInt(subject, title, 0, str);
}

int iniDataManager::loadDataInterger(const WCHAR* fileName, const WCHAR* subject, const WCHAR* title)
{
	WCHAR str[256];
	WCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	swprintf(dir, L"\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	wcsncat_s(str, 256, dir, 254);



	return GetPrivateProfileInt(subject, title, 0, str);
}
#else
void iniDataManager::addData(const char* subject, const char* title, const char* body)
{
	//iOS -> NSMUTABLEARRAY

	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniDataManager::iniSave(char * folder, char * fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s\\%s.ini", folder, fileName);

	//현재 디렉토리 경로를 받아와주는 함쑤!
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}

void iniDataManager::iniSave(char* fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	//현재 디렉토리 경로를 받아와주는 함쑤!
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}

char * iniDataManager::loadDataString(const char * folder, const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s\\%s.ini", folder, fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[66] = { NULL };
	GetPrivateProfileString(subject, title, "", data, 64, str);


	return data;
}

char* iniDataManager::loadDataString(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[66] = { NULL };
	GetPrivateProfileString(subject, title, "", data, 64, str);


	return data;
}


int iniDataManager::loadDataInterger(const char * folder, const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s\\%s.ini", folder, fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);



	return GetPrivateProfileInt(subject, title, 0, str);
}

int iniDataManager::loadDataInterger(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);



	return GetPrivateProfileInt(subject, title, 0, str);
}
#endif
