#include "stdafx.h"
#include "objLoadManager.h"

#include "gameObject.h"


objLoadManager::objLoadManager()
{
}


objLoadManager::~objLoadManager()
{
}

#ifdef UNICODE
vector<gameObject> objLoadManager::load(const WCHAR* fileName, D3DXVECTOR3* half)
{
	vector<gameObject> objects;
	gameObject* tempObject = NULL;

	fstream fin;
	fin.open(fileName);

	float minx, miny, minz;
	float maxx, maxy, maxz;
	minx = miny = minz = 0;
	maxx = maxy = maxz = 0;

	vector<D3DXVECTOR3> v;
	vector<D3DXVECTOR2> vt;
	vector<D3DXVECTOR3> vn;
	vector<tagPNT_Vertex> f;
	vector<string> usingAttribute;
	map<string, tagObjectMtlData> mtls;
	char mtlName[1024];

	char mtlFileName[1024];

	bool isStart = false;

	while (!fin.eof())
	{
		char str[1024];
		fin.getline(str, 1024);

		if (str[0] == '#' ||
			str[0] == 's')
		{
			continue;
		}
		else if (str[0] == 'v')
		{
			if (str[1] == ' ')
			{
				float x, y, z;
				sscanf_s(str, "v  %f %f %f", &x, &y, &z);
				v.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (str[1] == 't')
			{
				float x, y, z;
				sscanf_s(str, "vt  %f %f %f", &x, &y, &z);
				y = 1 - y;
				vt.push_back(D3DXVECTOR2(x, y));
			}
			else if (str[1] == 'n')
			{
				float x, y, z;
				sscanf_s(str, "vn  %f %f %f", &x, &y, &z);
				vn.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (str[0] == 'm')
		{
			sscanf_s(str, "mtllib  %s", mtlFileName, sizeof(mtlFileName));
			if (mtlFileName[0] == '.' && mtlFileName[1] == '/')
				mtls = loadMtlLib(&mtlFileName[2]);
			else
				mtls = loadMtlLib(mtlFileName);
		}
		else if (str[0] == 'u')
		{
			sscanf_s(str, "usemtl %s", mtlName, sizeof(mtlName));
		}
		else if (str[0] == 'g')
		{
			isStart = !isStart;
			if (isStart)
			{
				if (tempObject)
				{
					tempObject->setVertices(f);
					tempObject->setMtl(mtls[mtlName].mtlName);
					tempObject->setTextureName(mtls[mtlName].textureName);
					tempObject->init();
					objects.push_back((*tempObject));
					
					f.clear();
				}
			
				tempObject = new gameObject;
			}
			else
			{
				//f.clear();
			}
		}
		else if (str[0] == 'f')
		{
			usingAttribute.push_back(mtlName);
			int idxV[3];
			int idxVT[3];
			int idxVN[3];
			if (vt.size() == 0)
				sscanf_s(str, "f  %d//%d %d//%d %d//%d", &idxV[0], &idxVN[0], &idxV[1], &idxVN[1], &idxV[2], &idxVN[2]);
			else
				sscanf_s(str, "f  %d/%d/%d %d/%d/%d %d/%d/%d", &idxV[0], &idxVT[0], &idxVN[0], &idxV[1], &idxVT[1], &idxVN[1], &idxV[2], &idxVT[2], &idxVN[2]);
			
			for (int i = 0; i < 3; ++i)
			{
				tagPNT_Vertex tempVertex;
				tempVertex.p = v[idxV[i] - 1];
				tempVertex.n = vn[idxVN[i] - 1];
			
				if (vt.size() == 0)
					tempVertex.t = D3DXVECTOR2(0, 0);
				else
					tempVertex.t = vt[idxVT[i] - 1];
			
				f.push_back(tempVertex);
			}

			vector<int> tempVIndex;
			vector<int> tempVTIndex;
			vector<int> tempVNIndex;
			string temp;
			int count = 0;
			for (int i = 0; i < strlen(str) + 1; ++i)
			{
				temp = "";
				if ('0' <= str[i] && str[i] <= '9')
				{
					while ('0' <= str[i] && str[i] <= '9')
					{
						temp += str[i];
						++i;
					}
				}

				if (str[i] == '/')
				{
					if (count == 0)
					{
						if (temp != "")
							tempVIndex.push_back(atoi(temp.c_str()));
					}
					else if (count == 1)
					{
						if (temp != "")
							tempVTIndex.push_back(atoi(temp.c_str()));
					}
					count++;
				}
				else if (str[i] == ' ' || i == strlen(str))
				{
					if (temp != "")
						tempVNIndex.push_back(atoi(temp.c_str()));

					count = 0;
				}
			}

			if (tempVIndex.size() == 3)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];
				
					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];
				
					f.push_back(tempVertex);
				}
			}
			else if (tempVIndex.size() == 4)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}

				tagPNT_Vertex tempVertex;
				tempVertex.p = v[tempVIndex[0] - 1];
				tempVertex.n = vn[tempVNIndex[0] - 1];

				if (tempVTIndex.size() > 2)
					tempVertex.t = vt[tempVTIndex[0] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[3] - 1];
				tempVertex.n = vn[tempVNIndex[3] - 1];

				if (tempVTIndex.size() > 3)
					tempVertex.t = vt[tempVTIndex[3] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[2] - 1];
				tempVertex.n = vn[tempVNIndex[2] - 1];

				if (tempVTIndex.size() > 0)
					tempVertex.t = vt[tempVTIndex[2] - 1];

				f.push_back(tempVertex);
			}
		}
	}

	fin.close();

	if (f.size() != 0)
	{
		if (tempObject)
		{
			tempObject->setVertices(f);
			tempObject->setMtl(mtls[mtlName].mtlName);
			tempObject->setTextureName(mtls[mtlName].textureName);
			tempObject->init();
			objects.push_back((*tempObject));
		}
	}

	SAFE_DELETE(tempObject);

	if (half)
	{
		minx = v[0].x;
		miny = v[0].y;
		minz = v[0].z;

		maxx = v[0].x;
		maxy = v[0].y;
		maxz = v[0].z;

		for (int i = 0; i < v.size(); ++i)
		{
			if (minx > v[i].x)
				minx = v[i].x;
			if (miny > v[i].y)
				miny = v[i].y;
			if (minz > v[i].z)
				minz = v[i].z;

			if (maxx < v[i].x)
				maxx = v[i].x;
			if (maxy < v[i].y)
				maxy = v[i].y;
			if (maxz < v[i].z)
				maxz = v[i].z;
		}

		half->x = (minx + maxx) / 2;
		half->y = (miny + maxy) / 2;
		half->z = (minz + maxz) / 2;
	}

	return objects;
}

LPD3DXMESH objLoadManager::loadMesh(OUT vector<tagObjectMtlData>& mtlTex, IN const WCHAR* fileName)
{
	vector<gameObject> objects;
	gameObject* tempObject = NULL;

	fstream fin;
	fin.open(fileName);

	vector<D3DXVECTOR3> v;
	vector<D3DXVECTOR2> vt;
	vector<D3DXVECTOR3> vn;
	vector<tagPNT_Vertex> f;
	vector<string> usingAttribute;
	map<string, tagObjectMtlData> mtls;
	char mtlName[1024];

	char mtlFileName[1024];

	bool isStart = false;

	while (!fin.eof())
	{
		char str[1024];
		fin.getline(str, 1024);

		if (str[0] == '#' ||
			str[0] == 's')
		{
			continue;
		}
		else if (str[0] == 'v')
		{
			if (str[1] == ' ')
			{
				float x, y, z;
				sscanf_s(str, "v  %f %f %f", &x, &y, &z);
				v.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (str[1] == 't')
			{
				float x, y, z;
				sscanf_s(str, "vt  %f %f %f", &x, &y, &z);
				vt.push_back(D3DXVECTOR2(x, y));
			}
			else if (str[1] == 'n')
			{
				float x, y, z;
				sscanf_s(str, "vn  %f %f %f", &x, &z, &y);
				vn.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (str[0] == 'm')
		{
			sscanf_s(str, "mtllib  %s", mtlFileName, sizeof(mtlFileName));
			if (mtlFileName[0] == '.' && mtlFileName[1] == '/')
				mtls = loadMtlLib(&mtlFileName[2]);
			else
				mtls = loadMtlLib(mtlFileName);
		}
		else if (str[0] == 'u')
		{
			sscanf_s(str, "usemtl %s", mtlName, sizeof(mtlName));
		}
		else if (str[0] == 'g')
		{
			//isStart = !isStart;
			//if (isStart)
			//{
			//	if (tempObject)
			//	{
			//		tempObject->setVertices(f);
			//		tempObject->setMtl(mtls[mtlName].mtlName);
			//		tempObject->setTextureName(mtls[mtlName].textureName);
			//		tempObject->init();
			//		objects.push_back((*tempObject));
			//		
			//		f.clear();
			//	}
			//
			//	tempObject = new gameObject;
			//}
			//else
			//{
			//	//f.clear();
			//}
		}
		else if (str[0] == 'f')
		{
			usingAttribute.push_back(mtlName);
			//int idxV[3];
			//int idxVT[3];
			//int idxVN[3];
			//if (vt.size() == 0)
			//	sscanf_s(str, "f  %d//%d %d//%d %d//%d", &idxV[0], &idxVN[0], &idxV[1], &idxVN[1], &idxV[2], &idxVN[2]);
			//else
			//	sscanf_s(str, "f  %d/%d/%d %d/%d/%d %d/%d/%d", &idxV[0], &idxVT[0], &idxVN[0], &idxV[1], &idxVT[1], &idxVN[1], &idxV[2], &idxVT[2], &idxVN[2]);
			//
			//for (int i = 0; i < 3; ++i)
			//{
			//	tagPNT_Vertex tempVertex;
			//	tempVertex.p = v[idxV[i] - 1];
			//	tempVertex.n = vn[idxVN[i] - 1];
			//
			//	if (vt.size() == 0)
			//		tempVertex.t = D3DXVECTOR2(0, 0);
			//	else
			//		tempVertex.t = vt[idxVT[i] - 1];
			//
			//	f.push_back(tempVertex);
			//}

			vector<int> tempVIndex;
			vector<int> tempVTIndex;
			vector<int> tempVNIndex;
			string temp;
			int count = 0;
			for (int i = 0; i < strlen(str) + 1; ++i)
			{
				temp = "";
				if ('0' <= str[i] && str[i] <= '9')
				{
					while ('0' <= str[i] && str[i] <= '9')
					{
						temp += str[i];
						++i;
					}
				}

				if (str[i] == '/')
				{
					if (count == 0)
					{
						if (temp != "")
							tempVIndex.push_back(atoi(temp.c_str()));
					}
					else if (count == 1)
					{
						if (temp != "")
							tempVTIndex.push_back(atoi(temp.c_str()));
					}
					count++;
				}
				else if (str[i] == ' ' || i == strlen(str))
				{
					if (temp != "")
						tempVNIndex.push_back(atoi(temp.c_str()));

					count = 0;
				}
			}

			if (tempVIndex.size() == 3)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}
			}
			else if (tempVIndex.size() == 4)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}

				tagPNT_Vertex tempVertex;
				tempVertex.p = v[tempVIndex[0] - 1];
				tempVertex.n = vn[tempVNIndex[0] - 1];

				if (tempVTIndex.size() > 2)
					tempVertex.t = vt[tempVTIndex[0] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[3] - 1];
				tempVertex.n = vn[tempVNIndex[3] - 1];

				if (tempVTIndex.size() > 3)
					tempVertex.t = vt[tempVTIndex[3] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[2] - 1];
				tempVertex.n = vn[tempVNIndex[2] - 1];

				if (tempVTIndex.size() > 0)
					tempVertex.t = vt[tempVTIndex[2] - 1];

				f.push_back(tempVertex);
			}
		}
	}

	fin.close();

	if (f.size() != 0)
	{
		if (tempObject)
		{
			//tempObject->setVertices(f);
			//tempObject->setMtl(mtls[mtlName].mtlName);
			//tempObject->setTextureName(mtls[mtlName].textureName);
			//tempObject->init();
			//objects.push_back((*tempObject));
		}
	}

	SAFE_DELETE(tempObject);

	LPD3DXMESH mesh = NULL;
	DWORD numSubset = mtls.size();
	D3DXCreateMeshFVF(f.size() / 3,
		f.size(),
		D3DXMESH_MANAGED,
		tagPNT_Vertex::FVF,
		D3DDEVICE,
		&mesh);

	tagPNT_Vertex* vertexBuffer = NULL;
	mesh->LockVertexBuffer(0, (void**)&vertexBuffer);

	for (int i = 0; i < f.size(); ++i)
		vertexBuffer[i] = f[i];

	mesh->UnlockVertexBuffer();

	WORD* index = NULL;
	mesh->LockIndexBuffer(0, (void**)&index);

	for (int i = 0; i < f.size(); ++i)
		index[i] = i;

	mesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = NULL;
	mesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int i = 0; i < f.size() / 3; ++i)
	{
		map<string, tagObjectMtlData>::iterator iter = mtls.begin();
		int attributeIndex = 0;
		for (iter; iter != mtls.end(); ++iter)
		{
			if (iter->first == usingAttribute[i])
				break;
			attributeIndex++;
		}

		attributeBuffer[i] = attributeIndex;
	}

	mesh->UnlockAttributeBuffer();

	mtlTex.resize(mtls.size());
	map<string, tagObjectMtlData>::iterator iter = mtls.begin();
	for (int i = 0; i < mtlTex.size(); ++i)
	{
		mtlTex[i] = iter->second;
		++iter;
	}

	DWORD* adjacencyInfo = new DWORD[mesh->GetNumFaces() * 3];
	mesh->GenerateAdjacency(0.0f, adjacencyInfo);

	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		adjacencyInfo,
		0, 0, 0);

	SAFE_DELETE_ARRAY(adjacencyInfo);

	return mesh;
}
#else
vector<gameObject> objLoadManager::load(const char* fileName)
{
	vector<gameObject> objects;
	gameObject* tempObject = NULL;

	fstream fin;
	fin.open(fileName);

	vector<D3DXVECTOR3> v;
	vector<D3DXVECTOR2> vt;
	vector<D3DXVECTOR3> vn;
	vector<tagPNT_Vertex> f;
	vector<string> usingAttribute;
	map<string, tagObjectMtlData> mtls;
	char mtlName[1024];

	char mtlFileName[1024];

	bool isStart = false;

	while (!fin.eof())
	{
		char str[1024];
		fin.getline(str, 1024);

		if (str[0] == '#' ||
			str[0] == 's')
		{
			continue;
		}
		else if (str[0] == 'v')
		{
			if (str[1] == ' ')
			{
				float x, y, z;
				sscanf_s(str, "v  %f %f %f", &x, &z, &y);
				v.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (str[1] == 't')
			{
				float x, y, z;
				sscanf_s(str, "vt  %f %f %f", &x, &y, &z);
				vt.push_back(D3DXVECTOR2(x, y));
			}
			else if (str[1] == 'n')
			{
				float x, y, z;
				sscanf_s(str, "vn  %f %f %f", &x, &z, &y);
				vn.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (str[0] == 'm')
		{
			sscanf_s(str, "mtllib  %s", mtlFileName, sizeof(mtlFileName));
			if (mtlFileName[0] == '.' && mtlFileName[1] == '/')
				mtls = loadMtlLib(&mtlFileName[2]);
			else
				mtls = loadMtlLib(mtlFileName);
		}
		else if (str[0] == 'u')
		{
			sscanf_s(str, "usemtl %s", mtlName, sizeof(mtlName));
		}
		else if (str[0] == 'g')
		{
			isStart = !isStart;
			if (isStart)
			{
				if (tempObject)
				{
					tempObject->setVertices(f);
					tempObject->setMtl(mtls[mtlName].mtlName);
					tempObject->setTextureName(mtls[mtlName].textureName);
					tempObject->init();
					objects.push_back((*tempObject));

					f.clear();
				}

				tempObject = new gameObject;
			}
			else
			{
				//f.clear();
			}
		}
		else if (str[0] == 'f')
		{
			usingAttribute.push_back(mtlName);
			//int idxV[3];
			//int idxVT[3];
			//int idxVN[3];
			//if (vt.size() == 0)
			//	sscanf_s(str, "f  %d//%d %d//%d %d//%d", &idxV[0], &idxVN[0], &idxV[1], &idxVN[1], &idxV[2], &idxVN[2]);
			//else
			//	sscanf_s(str, "f  %d/%d/%d %d/%d/%d %d/%d/%d", &idxV[0], &idxVT[0], &idxVN[0], &idxV[1], &idxVT[1], &idxVN[1], &idxV[2], &idxVT[2], &idxVN[2]);
			//
			//for (int i = 0; i < 3; ++i)
			//{
			//	tagPNT_Vertex tempVertex;
			//	tempVertex.p = v[idxV[i] - 1];
			//	tempVertex.n = vn[idxVN[i] - 1];
			//
			//	if (vt.size() == 0)
			//		tempVertex.t = D3DXVECTOR2(0, 0);
			//	else
			//		tempVertex.t = vt[idxVT[i] - 1];
			//
			//	f.push_back(tempVertex);
			//}

			vector<int> tempVIndex;
			vector<int> tempVTIndex;
			vector<int> tempVNIndex;
			string temp;
			int count = 0;
			for (int i = 0; i < strlen(str) + 1; ++i)
			{
				temp = "";
				if ('0' <= str[i] && str[i] <= '9')
				{
					while ('0' <= str[i] && str[i] <= '9')
					{
						temp += str[i];
						++i;
					}
				}

				if (str[i] == '/')
				{
					if (count == 0)
					{
						if (temp != "")
							tempVIndex.push_back(atoi(temp.c_str()));
					}
					else if (count == 1)
					{
						if (temp != "")
							tempVTIndex.push_back(atoi(temp.c_str()));
					}
					count++;
				}
				else if (str[i] == ' ' || i == strlen(str))
				{
					if (temp != "")
						tempVNIndex.push_back(atoi(temp.c_str()));

					count = 0;
				}
			}

			if (tempVIndex.size() == 3)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}
			}
			else if (tempVIndex.size() == 4)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}

				tagPNT_Vertex tempVertex;
				tempVertex.p = v[tempVIndex[0] - 1];
				tempVertex.n = vn[tempVNIndex[0] - 1];

				if (tempVTIndex.size() > 2)
					tempVertex.t = vt[tempVTIndex[0] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[3] - 1];
				tempVertex.n = vn[tempVNIndex[3] - 1];

				if (tempVTIndex.size() > 3)
					tempVertex.t = vt[tempVTIndex[3] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[2] - 1];
				tempVertex.n = vn[tempVNIndex[2] - 1];

				if (tempVTIndex.size() > 0)
					tempVertex.t = vt[tempVTIndex[2] - 1];

				f.push_back(tempVertex);
			}
		}
	}

	fin.close();

	if (f.size() != 0)
	{
		if (tempObject)
		{
			tempObject->setVertices(f);
			tempObject->setMtl(mtls[mtlName].mtlName);
			tempObject->setTextureName(mtls[mtlName].textureName);
			tempObject->init();
			objects.push_back((*tempObject));
		}
	}

	SAFE_DELETE(tempObject);

	return objects;
}

LPD3DXMESH objLoadManager::loadMesh(OUT vector<tagObjectMtlData>& mtlTex, IN const char* fileName)
{
	vector<gameObject> objects;
	gameObject* tempObject = NULL;

	fstream fin;
	fin.open(fileName);

	vector<D3DXVECTOR3> v;
	vector<D3DXVECTOR2> vt;
	vector<D3DXVECTOR3> vn;
	vector<tagPNT_Vertex> f;
	vector<string> usingAttribute;
	map<string, tagObjectMtlData> mtls;
	char mtlName[1024];

	char mtlFileName[1024];

	bool isStart = false;

	while (!fin.eof())
	{
		char str[1024];
		fin.getline(str, 1024);

		if (str[0] == '#' ||
			str[0] == 's')
		{
			continue;
		}
		else if (str[0] == 'v')
		{
			if (str[1] == ' ')
			{
				float x, y, z;
				sscanf_s(str, "v  %f %f %f", &x, &z, &y);
				v.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (str[1] == 't')
			{
				float x, y, z;
				sscanf_s(str, "vt  %f %f %f", &x, &y, &z);
				vt.push_back(D3DXVECTOR2(x, y));
			}
			else if (str[1] == 'n')
			{
				float x, y, z;
				sscanf_s(str, "vn  %f %f %f", &x, &z, &y);
				vn.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (str[0] == 'm')
		{
			sscanf_s(str, "mtllib  %s", mtlFileName, sizeof(mtlFileName));
			if (mtlFileName[0] == '.' && mtlFileName[1] == '/')
				mtls = loadMtlLib(&mtlFileName[2]);
			else
				mtls = loadMtlLib(mtlFileName);
		}
		else if (str[0] == 'u')
		{
			sscanf_s(str, "usemtl %s", mtlName, sizeof(mtlName));
		}
		else if (str[0] == 'g')
		{
			//isStart = !isStart;
			//if (isStart)
			//{
			//	if (tempObject)
			//	{
			//		tempObject->setVertices(f);
			//		tempObject->setMtl(mtls[mtlName].mtlName);
			//		tempObject->setTextureName(mtls[mtlName].textureName);
			//		tempObject->init();
			//		objects.push_back((*tempObject));
			//		
			//		f.clear();
			//	}
			//
			//	tempObject = new gameObject;
			//}
			//else
			//{
			//	//f.clear();
			//}
		}
		else if (str[0] == 'f')
		{
			usingAttribute.push_back(mtlName);
			//int idxV[3];
			//int idxVT[3];
			//int idxVN[3];
			//if (vt.size() == 0)
			//	sscanf_s(str, "f  %d//%d %d//%d %d//%d", &idxV[0], &idxVN[0], &idxV[1], &idxVN[1], &idxV[2], &idxVN[2]);
			//else
			//	sscanf_s(str, "f  %d/%d/%d %d/%d/%d %d/%d/%d", &idxV[0], &idxVT[0], &idxVN[0], &idxV[1], &idxVT[1], &idxVN[1], &idxV[2], &idxVT[2], &idxVN[2]);
			//
			//for (int i = 0; i < 3; ++i)
			//{
			//	tagPNT_Vertex tempVertex;
			//	tempVertex.p = v[idxV[i] - 1];
			//	tempVertex.n = vn[idxVN[i] - 1];
			//
			//	if (vt.size() == 0)
			//		tempVertex.t = D3DXVECTOR2(0, 0);
			//	else
			//		tempVertex.t = vt[idxVT[i] - 1];
			//
			//	f.push_back(tempVertex);
			//}

			vector<int> tempVIndex;
			vector<int> tempVTIndex;
			vector<int> tempVNIndex;
			string temp;
			int count = 0;
			for (int i = 0; i < strlen(str) + 1; ++i)
			{
				temp = "";
				if ('0' <= str[i] && str[i] <= '9')
				{
					while ('0' <= str[i] && str[i] <= '9')
					{
						temp += str[i];
						++i;
					}
				}

				if (str[i] == '/')
				{
					if (count == 0)
					{
						if (temp != "")
							tempVIndex.push_back(atoi(temp.c_str()));
					}
					else if (count == 1)
					{
						if (temp != "")
							tempVTIndex.push_back(atoi(temp.c_str()));
					}
					count++;
				}
				else if (str[i] == ' ' || i == strlen(str))
				{
					if (temp != "")
						tempVNIndex.push_back(atoi(temp.c_str()));

					count = 0;
				}
			}

			if (tempVIndex.size() == 3)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}
			}
			else if (tempVIndex.size() == 4)
			{
				for (int i = 0; i < 3; ++i)
				{
					tagPNT_Vertex tempVertex;
					tempVertex.p = v[tempVIndex[2 - i] - 1];
					tempVertex.n = vn[tempVNIndex[2 - i] - 1];

					if (tempVTIndex.size() > i)
						tempVertex.t = vt[tempVTIndex[2 - i] - 1];

					f.push_back(tempVertex);
				}

				tagPNT_Vertex tempVertex;
				tempVertex.p = v[tempVIndex[0] - 1];
				tempVertex.n = vn[tempVNIndex[0] - 1];

				if (tempVTIndex.size() > 2)
					tempVertex.t = vt[tempVTIndex[0] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[3] - 1];
				tempVertex.n = vn[tempVNIndex[3] - 1];

				if (tempVTIndex.size() > 3)
					tempVertex.t = vt[tempVTIndex[3] - 1];

				f.push_back(tempVertex);

				tempVertex.p = v[tempVIndex[2] - 1];
				tempVertex.n = vn[tempVNIndex[2] - 1];

				if (tempVTIndex.size() > 0)
					tempVertex.t = vt[tempVTIndex[2] - 1];

				f.push_back(tempVertex);
			}
		}
	}

	fin.close();

	if (f.size() != 0)
	{
		if (tempObject)
		{
			//tempObject->setVertices(f);
			//tempObject->setMtl(mtls[mtlName].mtlName);
			//tempObject->setTextureName(mtls[mtlName].textureName);
			//tempObject->init();
			//objects.push_back((*tempObject));
		}
	}

	SAFE_DELETE(tempObject);

	LPD3DXMESH mesh = NULL;
	DWORD numSubset = mtls.size();
	D3DXCreateMeshFVF(f.size() / 3,
		f.size(),
		D3DXMESH_MANAGED,
		tagPNT_Vertex::FVF,
		D3DDEVICE,
		&mesh);

	tagPNT_Vertex* vertexBuffer = NULL;
	mesh->LockVertexBuffer(0, (void**)&vertexBuffer);

	for (int i = 0; i < f.size(); ++i)
		vertexBuffer[i] = f[i];

	mesh->UnlockVertexBuffer();

	WORD* index = NULL;
	mesh->LockIndexBuffer(0, (void**)&index);

	for (int i = 0; i < f.size(); ++i)
		index[i] = i;

	mesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = NULL;
	mesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int i = 0; i < f.size() / 3; ++i)
	{
		map<string, tagObjectMtlData>::iterator iter = mtls.begin();
		int attributeIndex = 0;
		for (iter; iter != mtls.end(); ++iter)
		{
			if (iter->first == usingAttribute[i])
				break;
			attributeIndex++;
		}

		attributeBuffer[i] = attributeIndex;
	}

	mesh->UnlockAttributeBuffer();

	mtlTex.resize(mtls.size());
	map<string, tagObjectMtlData>::iterator iter = mtls.begin();
	for (int i = 0; i < mtlTex.size(); ++i)
	{
		mtlTex[i] = iter->second;
		++iter;
	}

	DWORD* adjacencyInfo = new DWORD[mesh->GetNumFaces() * 3];
	mesh->GenerateAdjacency(0.0f, adjacencyInfo);

	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		adjacencyInfo,
		0, 0, 0);

	SAFE_DELETE_ARRAY(adjacencyInfo);

	return mesh;
}
#endif

map<string, tagObjectMtlData> objLoadManager::loadMtlLib(const char* fileName)
{
	char realFilePath[1024];
	sprintf(realFilePath, "./obj/%s", fileName);
	fstream fin;
	fin.open(realFilePath);

	map<string, tagObjectMtlData> mtls;
	D3DMATERIAL9 tempMtl;
	tagObjectMtlData tempMaterial;
	char tempMtlName[1024];

	while (!fin.eof())
	{
		char str[1024];
		fin.getline(str, 1024);

		if (str[0] == 'K')
		{
			if (str[1] == 'a')
			{
				float r, g, b;
				sscanf_s(str, "Ka  %f %f %f", &r, &g, &b);
				tempMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (str[1] == 'd')
			{
				float r, g, b;
				sscanf_s(str, "Kd  %f %f %f", &r, &g, &b);
				tempMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (str[1] == 's')
			{
				float r, g, b;
				sscanf_s(str, "Ks  %f %f %f", &r, &g, &b);
				tempMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if (str[0] == 'n')
		{
			ZeroMemory(&tempMtl, sizeof(D3DMATERIAL9));
			sscanf_s(str, "newmtl %s", tempMtlName, sizeof(tempMtlName));
			mtls.insert(make_pair(tempMtlName, tempMaterial));
		}
		else if (str[0] == 'm')
		{
			char textureName[1024];
			sscanf_s(str, "map_Kd %s", textureName, sizeof(textureName));
#ifdef UNICODE
			WCHAR temp[1024];
			MultiByteToWideChar(CP_ACP, 0, textureName, -1, temp, sizeof(temp));
			mtls[tempMtlName].textureName = temp;

			WCHAR tempFilePath[1024];
			swprintf(tempFilePath, L"./obj/%s", temp);
			TEXTUREMANAGER->addTexture(temp, tempFilePath);

			MultiByteToWideChar(CP_ACP, 0, tempMtlName, -1, temp, sizeof(temp));
			mtls[tempMtlName].mtlName = temp;
			MATERIALMANAGER->addMaterial(mtls[tempMtlName].mtlName, tempMtl);
#else
			mtls[tempMtlName].textureName = textureName;

			char tempFilePath[1024];
			sprintf(tempFilePath, "./obj/%s", textureName);
			TEXTUREMANAGER->addTexture(textureName, tempFilePath);

			mtls[tempMtlName].mtlName = tempMtlName;
			MATERIALMANAGER->addMaterial(mtls[tempMtlName].mtlName, tempMtl);
#endif
		}
	}

	fin.close();

	return mtls;
}
