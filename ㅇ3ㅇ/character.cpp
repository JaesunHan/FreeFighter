#include "stdafx.h"
#include "character.h"
#include "gameObject.h"
#include "heightMap.h"


character::character()
	: _position(0, 0, 0)
	, _angleX(0.0f)
	, _angleY(0.0f)
	, _angleZ(0.0f)
	, _dirAngle(0.0f)
	, _speed(0.0f)
	, _jumpPower(0.0f)
	, _isJump(false)
	, _floor(NULL)
	, _wall(NULL)
	, _to(0, 0, 0)
	, _hMap(NULL)
{
	D3DXMatrixIdentity(&_worldMatrix);
}


character::~character()
{
}

void character::update()
{
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXMATRIX translation;
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&translation);

	D3DXMatrixScaling(&scale, SCALE, SCALE, SCALE);

	if (!_isMove)
		_to = _position;

	D3DXMATRIX dirRotation;
	_dir = D3DXVECTOR3(0, 0, 1);
	/*
	_to.y = _position.y;
	_dir = _position - _to;
	if (!_isMove)
		D3DXVec3Normalize(&_dir, &_dir);
	_dirAngle = getAngle(_position.x, _position.z, _to.x, _to.z) - D3DX_PI / 2;*/
	D3DXMatrixRotationY(&dirRotation, _dirAngle);
	D3DXVec3TransformNormal(&_dir, &_dir, &dirRotation);

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_speed = -SPEED;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speed = SPEED;
	}
	else
	{
		_speed = 0.0f;
	}
	
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_dirAngle -= ANGLESPEED * DEG2RAD;
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_dirAngle += ANGLESPEED * DEG2RAD;
	}

	D3DXVECTOR3 tempSpeed = _dir * _speed;

	_position += tempSpeed;
	_angleY = _dirAngle;

	D3DXMatrixRotationYawPitchRoll(&rotation, _angleY, _angleX, _angleZ);

	D3DXVec3Normalize(&tempSpeed, &tempSpeed);
	this->collisionByWall(tempSpeed);

	this->jump();

	this->collisionByFloor();

	if (_position.y < -1.0f)
	{
		_position.y = -1.0f;
		_isJump = false;
	}
	
	D3DXMatrixTranslation(&translation, _position.x, _position.y, _position.z);

	_worldMatrix = scale * rotation * translation;
}

void character::render()
{
	//D3DXMATRIX dirRotation;
	//_dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//D3DXMatrixRotationY(&dirRotation, _dirAngle);
	//D3DXVec3TransformCoord(&_dir, &_dir, &dirRotation);
	//_dir += _position;
	//_dir = _dir + (2 * (_position - _dir));
	//vector<tagPC_Vertex> temp;
	//tagPC_Vertex ver;
	//ver.p = _position;
	//temp.push_back(ver);
	//ver.p = _dir;
	//temp.push_back(ver);
	//
	//D3DDEVICE->DrawPrimitiveUP(D3DPT_LINELIST, temp.size() / 2, &temp[0], sizeof(tagPC_Vertex));
}

void character::jump()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_isJump)
	{
		_jumpPower = JUMPPOWER;
		_isJump = true;
	}

	if (_isJump)
	{
		_position.y += _jumpPower * SCALE;
		_jumpPower -= GRAVITY;
	}
}

void character::collisionByWall(D3DXVECTOR3 dir)
{
	if (_wall)
	{
		for (int i = 0; i < _wall->size(); ++i)
		{
			vector<D3DXVECTOR3> temp = (*_wall)[i].getWorldVertex();
			for (int j = 0; j < temp.size(); j += 3)
			{
				D3DXVECTOR3 cross;
				D3DXVECTOR3 v1 = temp[j + 1] - temp[j];
				D3DXVECTOR3 v2 = temp[j + 2] - temp[j];
				D3DXVec3Cross(&cross, &v1, &v2);
				D3DXVec3Normalize(&cross, &cross);

				float dot = D3DXVec3Dot(&cross, &dir);
				if (dot != 0.0f) continue;

				float u, v, dis;
				D3DXVECTOR3 rayPosition = _position;
				rayPosition.y += 0.3f;
				if (D3DXIntersectTri(&temp[j], &temp[j + 1], &temp[j + 2], &_position, &dir, &u, &v, &dis))
				{
					if (dis < 1.5f * SCALE)
					{
						D3DXVECTOR3 pos = _position - dir * (1.5f * SCALE - dis);
						_position = pos;
					}
					break;
				}
			}
		}
	}
}

void character::collisionByFloor()
{
	if (_floor)
	{
		bool isOnFloor = false;
		for (int i = 0; i < _floor->size(); ++i)
		{
			vector<D3DXVECTOR3> temp = (*_floor)[i].getWorldVertex();
			for (int j = 0; j < temp.size(); j += 3)
			{
				float u, v, dis;
				D3DXVECTOR3 rayPosition = _position;
				rayPosition.y += 0.3f;
				if (D3DXIntersectTri(&temp[j], &temp[j + 1], &temp[j + 2], &rayPosition, &D3DXVECTOR3(0, -1, 0), &u, &v, &dis))
				{
					isOnFloor = true;
					if (dis < 0.3f * SCALE)
					{
						_position.y += 0.3f * SCALE - dis;
						_isJump = false;
					}
					else
					{
						if (!_isJump)
						{
							_isJump = true;
							_jumpPower = 0.0f;
						}
					}
					break;
				}
			}
		}
		if (!isOnFloor)
		{
			if (_position.y > 0.0f &&
				!_isJump)
			{
				_isJump = true;
				_jumpPower = 0.0f;
			}
		}
	}

	if (_hMap)
	{
		_hMap->getPlayerIndex(_position);
	}
}

void character::moveTo(D3DXVECTOR3 to)
{
	_isMove = true;
	_to = to;
	_speed = -SPEED;
}
