#pragma once
#include "mtlTexData.h"

#define PT_VERTEX

#ifdef PC_VERTEX
#define CURRNET_MODE	tagPC_Vertex
#define CURRNET_FVF		tagPC_Vertex::FVF
#endif
#ifdef PT_VERTEX
#define CURRNET_MODE	tagPNT_Vertex
#define CURRNET_FVF		tagPNT_Vertex::FVF
#endif

class cube
{
protected:
#ifdef PC_VERTEX
	vector<tagPC_Vertex>	_vertex;
#endif
#ifdef PT_VERTEX
	vector<tagPNT_Vertex>	_vertex;
#endif
	D3DXVECTOR3				_position;

	D3DXMATRIX				_worldMatrix;

	float					_angleX;
	float					_angleY;
	float					_angleZ;

	float					_sx;
	float					_sy;
	float					_sz;

protected:
	//큐브의 재질과 텍스처에 대한 키값을 저장할 구조체
	tagObjectMtlData		_mtlTex;


public:
	cube();
	~cube();

	virtual void init();
	virtual void release();
	virtual void update(D3DXMATRIX* parent = NULL);
	virtual void render();

	//임시로 추가
	void SetWorldTM(D3DXMATRIX worldTM) { _worldMatrix = worldTM; }

	void positionWorld(D3DXVECTOR3 pos);
	void translateWorld(D3DXVECTOR3 pos);
	void translateLocal(D3DXVECTOR3 pos);

	void rotateWorld(float angleX, float angleY, float angleZ);
	void rotateLocal(float angleX, float angleY, float angleZ);

	void scaleWorld(float sx, float sy, float sz);
	void scaleLocal(float sx, float sy, float sz);

	void transFormLocal(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz);

	inline D3DXVECTOR3 getPosition() { return _position; }

#ifdef  UNICODE
	inline void SetMtlTexName(wstring mtlName, wstring texName) {
		_mtlTex.mtlName = mtlName;
		_mtlTex.textureName = texName;
	}
	inline wstring		GetMtlName() {
		return _mtlTex.mtlName;
	}
	inline wstring		GetTexName() {
		return _mtlTex.textureName;
	}
#else
	inline void SetMtlTexName(string mtlName, string texName) {
		_mtlTex.mtlName = mtlName;
		_mtlTex.textureName = texName;
		inline string		GetMtlName() {
			return _mtlTex.mtlName;
}
		inline string		GetTexName() {
			return _mtlTex.textureName;
		}
}
#endif //  UNICODD

	
};

