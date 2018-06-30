#pragma once
#include <vector>

#ifdef UNICODE
struct tagIniData
{
	const WCHAR* subject;	//�׸�			����
	const WCHAR* title;		//������			����
	const WCHAR* body;		//�������� ��	97
};
#else
struct tagIniData
{
	const char* subject;	//�׸�			����
	const char* title;		//������			����
	const char* body;		//�������� ��	97
};
#endif

class iniDataManager
{
	SINGLETONE(iniDataManager)
#ifdef UNICODE
private:
	typedef vector<tagIniData>				arrIniData;
	typedef vector<tagIniData>::iterator	arrIniDataIter;

	typedef vector<arrIniData>				arrIniDatas;
	typedef vector<arrIniData>::iterator	arrIniDatasIter;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init();
	void release();

	void addData(const WCHAR* subject, const WCHAR* title, const WCHAR* body);
	void iniSave(WCHAR* fileName);

	WCHAR* loadDataString(const WCHAR* fileName, const WCHAR* subject, const WCHAR* title);

	int loadDataInterger(const WCHAR* fileName, const WCHAR* subject, const WCHAR* title);

#else
private:
	typedef vector<tagIniData>				arrIniData;
	typedef vector<tagIniData>::iterator	arrIniDataIter;

	typedef vector<arrIniData>				arrIniDatas;
	typedef vector<arrIniData>::iterator	arrIniDatasIter;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init();
	void release();

	void addData(const char* subject, const char* title, const char* body);
	void iniSave(char* fileName);

	char* loadDataString(const char* fileName, const char* subject, const char* title);

	int loadDataInterger(const char* fileName, const char* subject, const char* title);
#endif

};

