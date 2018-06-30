#pragma once
#include <vector>

#ifdef UNICODE
struct tagIniData
{
	const WCHAR* subject;	//亲格			炼款
	const WCHAR* title;		//家力格			公仿
	const WCHAR* body;		//家力格狼 蔼	97
};
#else
struct tagIniData
{
	const char* subject;	//亲格			炼款
	const char* title;		//家力格			公仿
	const char* body;		//家力格狼 蔼	97
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

