#include "stdafx.h"
#include "ASELoadManager.h"
#include "objectNode.h"


ASELoadManager::ASELoadManager()
{
}


ASELoadManager::~ASELoadManager()
{
}

#ifdef UNICODE
objectNode* ASELoadManager::load(const WCHAR* fileName)
{
	if (_materialRef.size() != 0)
		_materialRef.clear();

	if (_objs.size() != 0)
		_objs.clear();

	fstream fin;
	fin.open(fileName);

	if (fin.fail())
	{
		fin.close();
		return NULL;
	}

	while (!fin.eof())
	{
		char fileInputStr[1024];
		fin.getline(fileInputStr, sizeof(fileInputStr));
		int currentCursor = 0;

		while (true)
		{
			string token = this->getToken(fileInputStr, currentCursor);

			if (token == ID_COMMENT)
				break;
			else if (token == ID_SCENE)
			{
				this->processScene(fin);
				break;
			}
			else if (token == ID_MATERIAL_LIST)
			{
				this->processMaterialList(fin);
				break;
			}
			else if (token == ID_GEOMETRY)
			{
				this->processGeomObject(fin);
				break;
			}

			if (currentCursor >= strlen(fileInputStr))
				break;
		}
	}

	fin.close();

	objectNode* root = NULL;
	map<string, objectNode*>::iterator iter = _objs.begin();
	for (iter; iter != _objs.end(); ++iter)
	{
		if (!iter->second->getParent())
			root = iter->second;

		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, NULL, &iter->second->getNodeTm());
		vector<tagPNT_Vertex> tempVertex;
		vector<tagPNT_Vertex> origin = iter->second->getVertices();
		tempVertex.resize(origin.size());
		for (int i = 0; i < origin.size(); ++i)
		{
			D3DXVec3TransformCoord(&tempVertex[i].p, &origin[i].p, &inverse);
			tempVertex[i].t = origin[i].t;
			D3DXVec3TransformNormal(&tempVertex[i].n, &origin[i].n, &inverse);
		}

		iter->second->setVertices(tempVertex);

		iter->second->init();
		iter->second->setSceneInfo(_firstFrame, _lastFrame, _frameSpeed, _ticksPerFrame);
	}

	return root;
}
#else
objectNode* ASELoadManager::load(const char* fileName)
{
	if (_materialRef.size() != 0)
		_materialRef.clear();

	if (_objs.size() != 0)
		_objs.clear();

	fstream fin;
	fin.open(fileName);

	if (fin.fail())
	{
		fin.close();
		return NULL;
	}

	while (!fin.eof())
	{
		char fileInputStr[1024];
		fin.getline(fileInputStr, sizeof(fileInputStr));
		int currentCursor = 0;

		while (true)
		{
			string token = this->getToken(fileInputStr, currentCursor);

			if (token == ID_COMMENT)
				break;
			else if (token == ID_SCENE)
			{
				this->processScene(fin);
				break;
			}
			else if (token == ID_MATERIAL_LIST)
			{
				this->processMaterialList(fin);
				break;
			}
			else if (token == ID_GEOMETRY)
			{
				this->processGeomObject(fin);
				break;
			}

			if (currentCursor >= strlen(fileInputStr))
				break;
		}
	}

	fin.close();

	objectNode* root = NULL;
	map<string, objectNode*>::iterator iter = _objs.begin();
	for (iter; iter != _objs.end(); ++iter)
	{
		if (!iter->second->getParent())
			root = iter->second;

		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, NULL, &iter->second->getNodeTm());
		vector<tagPNT_Vertex> tempVertex;
		vector<tagPNT_Vertex> origin = iter->second->getVertices();
		tempVertex.resize(origin.size());
		for (int i = 0; i < origin.size(); ++i)
		{
			D3DXVec3TransformCoord(&tempVertex[i].p, &origin[i].p, &inverse);
			tempVertex[i].t = origin[i].t;
			D3DXVec3TransformNormal(&tempVertex[i].n, &origin[i].n, &inverse);
		}

		iter->second->setVertices(tempVertex);

		iter->second->init();
		iter->second->setSceneInfo(_firstFrame, _lastFrame, _frameSpeed, _ticksPerFrame);
	}

	return root;
}
#endif

void ASELoadManager::processScene(fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);

			if (token == "}")
			{
				return;
			}
			else if (token == ID_FIRSTFRAME)
			{
				string frame = this->getToken(fileInputData, currentCursor);
				sscanf_s(frame.c_str(), "%d", &_firstFrame);
				break;
			}
			else if (token == ID_LASTFRAME)
			{
				string frame = this->getToken(fileInputData, currentCursor);
				sscanf_s(frame.c_str(), "%d", &_lastFrame);
				break;
			}
			else if (token == ID_FRAMESPEED)
			{
				string speed = this->getToken(fileInputData, currentCursor);
				sscanf_s(speed.c_str(), "%d", &_frameSpeed);
				break;
			}
			else if (token == ID_TICKSPERFRAME)
			{
				string tickSperFrame = this->getToken(fileInputData, currentCursor);
				sscanf_s(tickSperFrame.c_str(), "%d", &_ticksPerFrame);
				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processMaterialList(fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);

			if (token == ID_MATERIAL_COUNT)
				break;
			else if (token == ID_MATERIAL)
			{
				this->processMaterial(file);
				break;
			}
			else if (token == "}")
			{
				return;
			}

			if (currentCursor >= strlen(fileInputData))
				break;
		}
	}
}

void ASELoadManager::processMaterial(fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	string name;
	string number[3];
	D3DMATERIAL9 mtl;
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
	tagObjectMtlData mtlData;
	int i;
	bool isSubExist = false;

	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);

			if (token == "}")
			{
				if (!isSubExist)
				{
#ifdef UNICODE
					WCHAR tempName[1024];
					MultiByteToWideChar(CP_ACP, 0, name.c_str(), -1, tempName, sizeof(tempName));
					MATERIALMANAGER->addMaterial(tempName, mtl);
					mtlData.mtlName = tempName;
					TEXTUREMANAGER->addTexture(mtlData.textureName, mtlData.textureName.c_str());
#else
					MATERIALMANAGER->addMaterial(name, mtl);
					mtlData.mtlName = name;
					TEXTUREMANAGER->addTexture(mtlData.textureName, mtlData.textureName.c_str());
#endif
					_materialRef.push_back(mtlData);
				}
				return;
			}
			else if (token == ID_MATNAME)
			{
				name = this->getToken(fileInputData, currentCursor);
				break;
			}
			else if (token == ID_AMBIENT)
			{
				i = 0;
				while (currentCursor < strlen(fileInputData))
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					i++;
				}
				sscanf_s(number[0].c_str(), "%f", &mtl.Ambient.r);
				sscanf_s(number[1].c_str(), "%f", &mtl.Ambient.g);
				sscanf_s(number[2].c_str(), "%f", &mtl.Ambient.b);
				mtl.Ambient.a = 1.0f;
			}
			else if (token == ID_DIFFUSE)
			{
				i = 0;
				while (currentCursor < strlen(fileInputData))
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					i++;
				}
				sscanf_s(number[0].c_str(), "%f", &mtl.Diffuse.r);
				sscanf_s(number[1].c_str(), "%f", &mtl.Diffuse.g);
				sscanf_s(number[2].c_str(), "%f", &mtl.Diffuse.b);
				mtl.Diffuse.a = 1.0f;
			}
			else if (token == ID_SPECULAR)
			{
				i = 0;
				while (currentCursor < strlen(fileInputData))
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					i++;
				}
				sscanf_s(number[0].c_str(), "%f", &mtl.Specular.r);
				sscanf_s(number[1].c_str(), "%f", &mtl.Specular.g);
				sscanf_s(number[2].c_str(), "%f", &mtl.Specular.b);
				mtl.Specular.a = 1.0f;
			}
			else if (token == ID_MAP_DIFFUSE)
			{
				this->processMapDiffuse(file, mtlData);
				break;
			}
			else if (token == ID_MAP_BUMP)
			{
				this->processMapBump(file);
				break;
			}
			else if (token == ID_SUBMATERIAL)
			{
				isSubExist = true;
				this->processSubMaterial(file);
				break;
			}
			else if (token == ID_SHINE)
			{
				string tempPower = this->getToken(fileInputData, currentCursor);
				float power;
				sscanf_s(tempPower.c_str(), "%f", &power);
				mtl.Power = power / 100;
				break;
			}
			else if (token == ID_SHINE_STRENGTH)
			{
				string tempStrength = this->getToken(fileInputData, currentCursor);
				float strength;
				sscanf_s(tempStrength.c_str(), "%f", &strength);
				mtl.Specular.r = mtl.Specular.r * strength / 100;
				mtl.Specular.g = mtl.Specular.g * strength / 100;
				mtl.Specular.b = mtl.Specular.b * strength / 100;
				break;
			}
			else break;

			if (currentCursor >= strlen(fileInputData))
				break;
		}
	}
}

void ASELoadManager::processSubMaterial(fstream & file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	string name;
	string number[3];
	D3DMATERIAL9 mtl;
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
	tagObjectMtlData mtlData;
	int i;

	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);

			if (token == "}")
			{
#ifdef UNICODE
				WCHAR tempName[1024];
				MultiByteToWideChar(CP_ACP, 0, name.c_str(), -1, tempName, sizeof(tempName));
				MATERIALMANAGER->addMaterial(tempName, mtl);
				mtlData.mtlName = tempName;
				TEXTUREMANAGER->addTexture(mtlData.textureName, mtlData.textureName.c_str());
#else
				MATERIALMANAGER->addMaterial(name, mtl);
				mtlData.mtlName = name;
				TEXTUREMANAGER->addTexture(mtlData.textureName, mtlData.textureName.c_str());
#endif
				_materialRef.push_back(mtlData);
				return;
			}
			else if (token == ID_MATNAME)
			{
				name = this->getToken(fileInputData, currentCursor);
				break;
			}
			else if (token == ID_AMBIENT)
			{
				i = 0;
				while (currentCursor < strlen(fileInputData))
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					i++;
				}
				sscanf_s(number[0].c_str(), "%f", &mtl.Ambient.r);
				sscanf_s(number[1].c_str(), "%f", &mtl.Ambient.g);
				sscanf_s(number[2].c_str(), "%f", &mtl.Ambient.b);
				mtl.Ambient.a = 1.0f;
			}
			else if (token == ID_DIFFUSE)
			{
				i = 0;
				while (currentCursor < strlen(fileInputData))
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					i++;
				}
				sscanf_s(number[0].c_str(), "%f", &mtl.Diffuse.r);
				sscanf_s(number[1].c_str(), "%f", &mtl.Diffuse.g);
				sscanf_s(number[2].c_str(), "%f", &mtl.Diffuse.b);
				mtl.Diffuse.a = 1.0f;
			}
			else if (token == ID_SPECULAR)
			{
				i = 0;
				while (currentCursor < strlen(fileInputData))
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					i++;
				}
				sscanf_s(number[0].c_str(), "%f", &mtl.Specular.r);
				sscanf_s(number[1].c_str(), "%f", &mtl.Specular.g);
				sscanf_s(number[2].c_str(), "%f", &mtl.Specular.b);
				mtl.Specular.a = 1.0f;
			}
			else if (token == ID_SHINE)
			{
				string tempPower = this->getToken(fileInputData, currentCursor);
				float power;
				sscanf_s(tempPower.c_str(), "%f", &power);
				mtl.Power = power / 100;
				break;
			}
			else if (token == ID_SHINE_STRENGTH)
			{
				string tempStrength = this->getToken(fileInputData, currentCursor);
				float strength;
				sscanf_s(tempStrength.c_str(), "%f", &strength);
				mtl.Specular.r = mtl.Specular.r * strength / 100;
				mtl.Specular.g = mtl.Specular.g * strength / 100;
				mtl.Specular.b = mtl.Specular.b * strength / 100;
				break;
			}
			else if (token == ID_MAP_DIFFUSE)
			{
				this->processMapDiffuse(file, mtlData);
				break;
			}
			else if (token == ID_MAP_BUMP)
			{
				this->processMapBump(file);
				break;
			}
			else break;

			if (currentCursor >= strlen(fileInputData))
				break;
		}
	}
}

void ASELoadManager::processMapDiffuse(fstream& file, tagObjectMtlData& mtlData)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);

			if (token == "}")
			{
				return;
			}
			else if (token == ID_BITMAP)
			{
				string textureName = this->getToken(fileInputData, currentCursor);

#ifdef UNICODE
				WCHAR tempName[1024];
				MultiByteToWideChar(CP_ACP, 0, textureName.c_str(), -1, tempName, sizeof(tempName));
				mtlData.textureName = tempName;
#else
				mtlData.textureName = textureName;
#endif
			}
			else break;

			if (currentCursor >= strlen(fileInputData))
				break;
		}
	}
}

void ASELoadManager::processMapBump(fstream & file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_MAP_GENERIC)
			{
				this->processMapGeneric(file);
				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processMapGeneric(fstream & file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processGeomObject(fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	objectNode* newObj = new objectNode;
	string objName;

	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);

			if (token == "}")
			{
				_objs.insert(make_pair(objName, newObj));
				return;
			}
			else if (token == ID_NODE_NAME)
			{
				objName = this->getToken(fileInputData, currentCursor);
				break;
			}
			else if (token == ID_NODE_TM)
			{
				D3DXMATRIX local = this->processTransformMatrix(file, newObj);
				newObj->setNodeTm(local);

				if (newObj->getParent())
				{
					D3DXMATRIX inverse;
					D3DXMatrixInverse(&inverse, NULL, &newObj->getParent()->getNodeTm());
					local = newObj->getNodeTm() * inverse;
				}

				newObj->setLocalMatrix(local);
				break;
			}
			else if (token == ID_NODE_PARENT)
			{
				string parentName = this->getToken(fileInputData, currentCursor);
				map<string, objectNode*>::iterator iter = _objs.find(parentName);
				iter->second->addChild(newObj);
				break;
			}
			else if (token == ID_MESH)
			{
				this->processMesh(file, newObj);
				break;
			}
			else if (token == ID_TM_ANIMATION)
			{
				this->processTMAnimation(file, newObj);
				break;
			}
			else if (token == ID_MATERIAL_REF)
			{
				string tempIndex = this->getToken(fileInputData, currentCursor);
				int tempIdx;
				sscanf_s(tempIndex.c_str(), "%d", &tempIdx);
				newObj->setMtl(_materialRef[tempIdx].mtlName);
				newObj->setTextureName(_materialRef[tempIdx].textureName);
				break;
			}
			else break;

			if (currentCursor >= strlen(fileInputData))
				break;
		}
	}
}

D3DXMATRIX ASELoadManager::processTransformMatrix(fstream& file, objectNode* obj)
{
	D3DXMATRIX tempMat;
	D3DXMatrixIdentity(&tempMat);

	float tx, ty, tz;
	float angleX, angleY, angleZ;
	float sx, sy, sz;

	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	string number[3];
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return tempMat;
			}
			else if (token == ID_TM_ROW0)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &tempMat._11);
				sscanf_s(number[2].c_str(), "%f", &tempMat._12);
				sscanf_s(number[1].c_str(), "%f", &tempMat._13);
				break;
			}
			else if (token == ID_TM_ROW2)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &tempMat._21);
				sscanf_s(number[2].c_str(), "%f", &tempMat._22);
				sscanf_s(number[1].c_str(), "%f", &tempMat._23);
				break;
			}
			else if (token == ID_TM_ROW1)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &tempMat._31);
				sscanf_s(number[2].c_str(), "%f", &tempMat._32);
				sscanf_s(number[1].c_str(), "%f", &tempMat._33);
				break;
			}
			else if (token == ID_TM_ROW3)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &tempMat._41);
				sscanf_s(number[2].c_str(), "%f", &tempMat._42);
				sscanf_s(number[1].c_str(), "%f", &tempMat._43);
				break;
			}
			else if (token == ID_TM_POS)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &tx);
				sscanf_s(number[2].c_str(), "%f", &ty);
				sscanf_s(number[1].c_str(), "%f", &tz);
				break;
			}
			else if (token == ID_TM_ROTAXIS)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &angleX);
				sscanf_s(number[2].c_str(), "%f", &angleY);
				sscanf_s(number[1].c_str(), "%f", &angleZ);
				break;
			}
			else if (token == ID_TM_SCALE)
			{
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &sx);
				sscanf_s(number[2].c_str(), "%f", &sy);
				sscanf_s(number[1].c_str(), "%f", &sz);
				break;
			}
			else break;
		}
	}

	return tempMat;
}

void ASELoadManager::processMesh(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	vector<D3DXVECTOR3> v;
	vector<D3DXVECTOR2> vt;

	vector<tagPNT_Vertex> f;

	int numVertex = 0;
	int numFaces = 0;
	int numTVertex = 0;
	int numTFaces = 0;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				obj->setVertices(f);
				return;
			}
			else if (token == ID_MESH_NUMVERTEX)
			{
				string num = this->getToken(fileInputData, currentCursor);
				sscanf_s(num.c_str(), "%d", &numVertex);
				v.resize(numVertex);
				break;
			}
			else if (token == ID_MESH_NUMFACES)
			{
				string num = this->getToken(fileInputData, currentCursor);
				sscanf_s(num.c_str(), "%d", &numFaces);
				f.resize(numFaces * 3);
				break;
			}
			else if (token == ID_MESH_VERTEX_LIST)
			{
				if (numVertex != 0)
					this->processVertexList(v, file);
				break;
			}
			else if (token == ID_MESH_FACE_LIST)
			{
				if (numFaces != 0)
					this->processFaceList(f, file, v);
				break;
			}
			else if (token == ID_MESH_NUMTVERTEX)
			{
				string num = this->getToken(fileInputData, currentCursor);
				sscanf_s(num.c_str(), "%d", &numTVertex);
				vt.resize(numTVertex);
				break;
			}
			else if (token == ID_MESH_TVERTLIST)
			{
				if (numTVertex != 0)
					this->processTVertexList(vt, file);
				break;
			}
			else if (token == ID_MESH_NUMTVFACES)
			{
				string num = this->getToken(fileInputData, currentCursor);
				sscanf_s(num.c_str(), "%d", &numTFaces);
				break;
			}
			else if (token == ID_MESH_TFACELIST)
			{
				if (numTFaces != 0)
					this->processTFaceList(f, file, vt);
				break;
			}
			else if (token == ID_MESH_NORMALS)
			{
				if (numFaces != 0)
					this->processNormals(f, file);
				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processVertexList(OUT vector<D3DXVECTOR3>& v, IN fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		string number[3];
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_MESH_VERTEX)
			{
				string tempIndex = this->getToken(fileInputData, currentCursor);
				sscanf(tempIndex.c_str(), "%d", &index);

				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &v[index].x);
				sscanf_s(number[2].c_str(), "%f", &v[index].y);
				sscanf_s(number[1].c_str(), "%f", &v[index].z);
				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processTVertexList(OUT vector<D3DXVECTOR2>& vt, IN fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		string number[2];
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_MESH_TVERT)
			{
				string tempIndex = this->getToken(fileInputData, currentCursor);
				sscanf(tempIndex.c_str(), "%d", &index);

				for (int i = 0; i < 2; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &vt[index].x);
				sscanf_s(number[1].c_str(), "%f", &vt[index].y);
				vt[index].y = 1.0f - vt[index].y;
				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processFaceList(OUT vector<tagPNT_Vertex>& f, IN fstream& file, IN vector<D3DXVECTOR3>& v)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		string number[3];
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_MESH_FACE)
			{
				string tempIndex = this->getToken(fileInputData, currentCursor);
				sscanf(tempIndex.c_str(), "%d:", &index);

				for (int i = 0; i < 3; ++i)
				{
					number[i] = this->getToken(fileInputData, currentCursor);
					number[i] = this->getToken(fileInputData, currentCursor);
				}

				int tempIdx;
				for (int i = 0; i < 3; ++i)
				{
					sscanf_s(number[i].c_str(), "%d", &tempIdx);
					f[index * 3 + (2 - i)].p = v[tempIdx];
				}

				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processTFaceList(OUT vector<tagPNT_Vertex>& f, IN fstream& file, IN vector<D3DXVECTOR2>& vt)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		string number[3];
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_MESH_TFACE)
			{
				string tempIndex = this->getToken(fileInputData, currentCursor);
				sscanf(tempIndex.c_str(), "%d", &index);

				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				int tempIdx;
				for (int i = 0; i < 3; ++i)
				{
					sscanf_s(number[i].c_str(), "%d", &tempIdx);
					f[index * 3 + (2 - i)].t = vt[tempIdx];
				}

				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processNormals(OUT vector<tagPNT_Vertex>& f, IN fstream& file)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	string tempIndex;
	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		string number[3];
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_MESH_FACENORMAL)
			{
				tempIndex = this->getToken(fileInputData, currentCursor);
				sscanf(tempIndex.c_str(), "%d", &index);
				//
				//for (int i = 0; i < 3; ++i)
				//	number[i] = this->getToken(fileInputData, currentCursor);
				//
				//for (int i = 0; i < 3; ++i)
				//{
				//	sscanf_s(number[0].c_str(), "%f", &f[index * 3 + i].n.x);
				//	sscanf_s(number[2].c_str(), "%f", &f[index * 3 + i].n.y);
				//	sscanf_s(number[1].c_str(), "%f", &f[index * 3 + i].n.z);
				//}

				D3DXVECTOR3 normal[3];

				for (int i = 0; i < 3; ++i)
				{
					char tempStr[1024];
					file.getline(tempStr, sizeof(tempStr));
					currentCursor = 0;
					this->getToken(tempStr, currentCursor);
					this->getToken(tempStr, currentCursor);
					for (int j = 0; j < 3; ++j)
						number[j] = this->getToken(tempStr, currentCursor);

					sscanf_s(number[0].c_str(), "%f", &normal[i].x);
					sscanf_s(number[2].c_str(), "%f", &normal[i].y);
					sscanf_s(number[1].c_str(), "%f", &normal[i].z);
				}

				f[index * 3 + 0].n = normal[0];
				f[index * 3 + 1].n = normal[2];
				f[index * 3 + 2].n = normal[1];

				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processTMAnimation(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		string number[3];
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == "*CONTROL_POS_TRACK")
			{
				this->processControlPosTrack(file, obj);
				break;
			}
			else if (token == "*CONTROL_ROT_TRACK")
			{
				this->processControlRotTrack(file, obj);
				break;
			}
			else if (token == "*CONTROL_SCALE_TRACK")
			{
				this->processControlScaleTrack(file, obj);
				break;
			}
			else if (token == ID_CONTROL_POS_TCB)
			{
				this->processControlPosTCB(file, obj);
				break;
			}
			else if (token == ID_CONTROL_ROT_TCB)
			{
				this->processControlRotTCB(file, obj);
				break;
			}
			else if (token == ID_CONTROL_SCALE_TCB)
			{
				this->processControlScaleTCB(file, obj);
				break;
			}
			else if (token == ID_CONTROL_POS_BEZIER)
			{
				this->processControlPosBezier(file, obj);
				break;
			}
			else if (token == ID_CONTROL_ROT_BEZIER)
			{
				this->processControlRotBezier(file, obj);
				break;
			}
			else if (token == ID_CONTROL_SCALE_BEZIER)
			{
				this->processControlScaleBezier(file, obj);
				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlPosTrack(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	TRANSLATION* track = NULL;

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_POS_SAMPLE)
			{
				track = new TRANSLATION;
				string tick = this->getToken(fileInputData, currentCursor);
				sscanf_s(tick.c_str(), "%d", &track->tick);

				string number[3];
				for (int i = 0; i < 3; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &track->pos.x);
				sscanf_s(number[2].c_str(), "%f", &track->pos.y);
				sscanf_s(number[1].c_str(), "%f", &track->pos.z);

				obj->addPosTrack(track);

				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlRotTrack(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	ROTATION* track;

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else if (token == ID_ROT_SAMPLE)
			{
				track = new ROTATION;
				string tick = this->getToken(fileInputData, currentCursor);
				sscanf_s(tick.c_str(), "%d", &track->tick);

				string number[4];
				for (int i = 0; i < 4; ++i)
					number[i] = this->getToken(fileInputData, currentCursor);

				sscanf_s(number[0].c_str(), "%f", &track->axis.x);
				sscanf_s(number[2].c_str(), "%f", &track->axis.y);
				sscanf_s(number[1].c_str(), "%f", &track->axis.z);
				sscanf_s(number[3].c_str(), "%f", &track->angle);

				D3DXQuaternionRotationAxis(&track->quaternion, &track->axis, track->angle);

				obj->addRotTrack(track);

				break;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlScaleTrack(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlPosTCB(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlRotTCB(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlScaleTCB(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlPosBezier(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlRotBezier(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

void ASELoadManager::processControlScaleBezier(fstream& file, objectNode* obj)
{
	char fileInputData[1024];
	ZeroMemory(fileInputData, sizeof(fileInputData));

	int index;
	while (true)
	{
		file.getline(fileInputData, sizeof(fileInputData));

		int currentCursor = 0;
		while (true)
		{
			string token = this->getToken(fileInputData, currentCursor);
			if (token == "}")
			{
				return;
			}
			else break;
		}
	}
}

string ASELoadManager::getToken(const char* inputData, int& cursor)
{
	string token = "";
	while (true)
	{
		if (inputData[cursor] == ' ' || inputData[cursor] == '\t')
		{
			do
			{
				cursor++;
			} while (inputData[cursor] == ' ' || inputData[cursor] == '\t');
		}

		if (inputData[cursor] == '*')
		{
			while (inputData[cursor] != ' ' &&
				   inputData[cursor] != '\t')
			{
				if (cursor >= strlen(inputData))
					break;

				token += inputData[cursor];
				cursor++;
			}
			break;
		}
		else if (inputData[cursor] == '"')
		{
			cursor++;
			while (inputData[cursor] != '"')
			{
				if (cursor >= strlen(inputData))
					break;

				token += inputData[cursor];
				cursor++;
			}
			break;
		}
		else if (('0' <= inputData[cursor] && inputData[cursor] <= '9') || inputData[cursor] == '-')
		{
			if (inputData[cursor] == '-')
			{
				token += inputData[cursor];
				cursor++;
			}

			while ('0' <= inputData[cursor] && inputData[cursor] <= '9')
			{
				token += inputData[cursor];
				cursor++;

				if (inputData[cursor] == '.')
				{
					token += inputData[cursor];
					cursor++;
				}
			}

			if (inputData[cursor] == ':')
			{
				token += inputData[cursor];
				cursor++;
			}

			break;
		}
		else if (inputData[cursor] == 'A' ||
				 inputData[cursor] == 'B' ||
				 inputData[cursor] == 'C')
		{
			while (inputData[cursor] != ' ' &&
				   inputData[cursor] != '\t')
			{
				if (cursor >= strlen(inputData))
					break;

				token += inputData[cursor];
				cursor++;
			}
			break;
		}
		else if (inputData[cursor] == '}')
		{
			token += '}';
			break;
		}

		if (cursor >= strlen(inputData))
			return token;
	}

	return token;
}
