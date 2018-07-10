#pragma once

#include <vector>
using namespace std;

class gameObject
{
protected:
	vector<tagPNT_Vertex>	_vertex;
	IDirect3DVertexBuffer9* _vb;
	tagPNT_Vertex*			_vertexData;

	D3DXVECTOR3				_position;

	D3DXMATRIX				_worldMatrix;
	D3DXMATRIX				_localMatrix;

	float					_angleX;
	float					_angleY;
	float					_angleZ;

	float					_sx;
	float					_sy;
	float					_sz;

#ifdef UNICODE
	wstring					_mtlName;
	wstring					_textureName;
#else
	string					_mtlName;
	string					_textureName;
#endif

	bool					_isMesh;

public:
	gameObject();
	~gameObject();

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void positionWorld(D3DXVECTOR3 pos);
	void translateWorld(D3DXVECTOR3 pos);
	void translateLocal(D3DXVECTOR3 pos);

	void rotateWorld(float angleX, float angleY, float angleZ);
	void rotateLocal(float angleX, float angleY, float angleZ);

	void scaleWorld(float sx, float sy, float sz);
	void scaleLocal(float sx, float sy, float sz);

	void transFormLocal(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz);

	vector<D3DXVECTOR3> getWorldVertex();

	inline D3DXVECTOR3 getPosition() { return _position; }

	inline void setVertices(vector<tagPNT_Vertex> v) { if (_vertex.size() != 0) _vertex.clear(); _vertex = v; }
	inline vector<tagPNT_Vertex> getVertices() { return _vertex; }
	
	inline void setIsMesh(bool b) { _isMesh = b; }



#ifdef UNICODE
	inline void setMtl(wstring m) { _mtlName = m; }

	inline void setTextureName(wstring n) { _textureName = n; }
#else
	inline void setMtl(string m) { _mtlName = m; }

	inline void setTextureName(string n) { _textureName = n; }
#endif
};

