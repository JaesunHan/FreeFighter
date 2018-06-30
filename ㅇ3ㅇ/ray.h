#pragma once
class ray
{
private:
	D3DXVECTOR3		_position;
	D3DXVECTOR3		_direction;

public:
	ray();
	~ray();

	void init(D3DXVECTOR3 pos, D3DXVECTOR3 dir);
	static ray rayAtViewSpace(int screenX, int screenY);
	static ray rayAtWorldSpace(int screenX, int screenY);
	static void TransformRay(ray* r, D3DXMATRIX& m);

	static bool isPicked(ray* r, tagSphere& s);
	static float calcDistance(ray* r, D3DXVECTOR3 v);
	bool IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3& pickedPosition);

	inline D3DXVECTOR3 getPosition() { return _position; }
};

