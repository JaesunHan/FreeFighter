#pragma once

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

public:
	cube();
	~cube();

	virtual void init();
	virtual void release();
	virtual void update(D3DXMATRIX* parent = NULL);
	virtual void render();

	void positionWorld(D3DXVECTOR3 pos);
	void translateWorld(D3DXVECTOR3 pos);
	void translateLocal(D3DXVECTOR3 pos);

	void rotateWorld(float angleX, float angleY, float angleZ);
	void rotateLocal(float angleX, float angleY, float angleZ);

	void scaleWorld(float sx, float sy, float sz);
	void scaleLocal(float sx, float sy, float sz);

	void transFormLocal(float tx, float ty, float tz, float angleX, float angleY, float angleZ, float sx, float sy, float sz);

	inline D3DXVECTOR3 getPosition() { return _position; }
};

