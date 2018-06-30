#include "stdafx.h"
#include "cubeMan.h"
#include "cubeArm.h"
#include "cubeBody.h"
#include "cubeHead.h"
#include "cubeLeg.h"

cubeMan::cubeMan()
	: _go(GO_NONE)
{
}


cubeMan::~cubeMan()
{
}

void cubeMan::init()
{
	TEXTUREMANAGER->addTexture(L"cubeMan", L".\\texture\\cubeMan.png");

	_body = new cubeBody;
	_body->init();
	_body->scaleLocal(2.0f, 3.0f, 0.5f);
	_body->translateLocal(D3DXVECTOR3(0, 0, 0));
	_root = _body;
	_head = new cubeHead;
	_head->init();
	_head->scaleLocal(1.0f, 1.0f, 1.0f);
	_head->translateLocal(D3DXVECTOR3(0, 2, 0));
	for (int i = 0; i < PARTS_END; ++i)
	{
		_leg[i] = new cubeLeg;
		_leg[i]->init();
		_leg[i]->scaleLocal(1.0f, 2.0f, 1.0f);
		_arms[i] = new cubeArm;
		_arms[i]->init();
		_arms[i]->scaleLocal(1.0f, 2.0f, 1.0f);
	}
	_leg[PARTS_LEFT]->translateLocal(D3DXVECTOR3(-0.5f, -0.5f, 0.0f));
	_leg[PARTS_RIGHT]->translateLocal(D3DXVECTOR3(0.5f, -0.5f, 0.0f));
	_leg[PARTS_LEFT]->positionWorld(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
	_leg[PARTS_RIGHT]->positionWorld(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
	_arms[PARTS_LEFT]->translateLocal(D3DXVECTOR3(-1.5f, -0.5f, 0.0f));
	_arms[PARTS_RIGHT]->translateLocal(D3DXVECTOR3(1.5f, -0.5f, 0.0f));
	_arms[PARTS_LEFT]->positionWorld(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	_arms[PARTS_RIGHT]->positionWorld(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	_leg[PARTS_LEFT]->setIsLeft(true);
	_arms[PARTS_LEFT]->setIsLeft(true);

	_root->addChild(_head);
	_root->addChild(_leg[PARTS_LEFT]);
	_root->addChild(_leg[PARTS_RIGHT]);
	_root->addChild(_arms[PARTS_LEFT]);
	_root->addChild(_arms[PARTS_RIGHT]);

	_root->setParentMatrix(&this->_worldMatrix);

	_dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	_dirAngle = 0.0f;
	_speed = 0.1f;

	ZeroMemory(&_light, sizeof(D3DLIGHT9));
	_light.Type = D3DLIGHT_SPOT;
	_light.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_light.Range = 10.0f;
	_light.Position = this->getPos();
	_light.Direction = -_dir;
	_light.Attenuation0 = 0.0f;
	_light.Attenuation1 = 0.0f;
	_light.Attenuation2 = 0.0f;
	_light.Falloff = 1.0f;
	_light.Phi = D3DX_PI / 3;
	_light.Theta = D3DX_PI / 3;
	D3DDEVICE->SetLight(_numOfLight, &_light);
	D3DDEVICE->LightEnable(_numOfLight, TRUE);
	_lightChannel = _numOfLight;
	_numOfLight++;

	D3DMATERIAL9 mtl;
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
	mtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	MATERIALMANAGER->addMaterial(L"cubeMan", mtl);
}

void cubeMan::release()
{
	_root->release();
	SAFE_DELETE(_root);
}

void cubeMan::update()
{
	character::update();

	_root->update();
	if (KEYMANAGER->isStayKeyDown('W'))
		_go = GO_FRONT;
	else if (KEYMANAGER->isStayKeyDown('S'))
		_go = GO_BACK;
	else
		_go = GO_NONE;
	
	_leg[PARTS_LEFT]->setGoDir(_go);
	_arms[PARTS_LEFT]->setGoDir(_go);
	_leg[PARTS_RIGHT]->setGoDir(_go);
	_arms[PARTS_RIGHT]->setGoDir(_go);

	if (KEYMANAGER->isStayKeyDown('A'))
		_head->setGoDir(GO_LEFT);
	else if (KEYMANAGER->isStayKeyDown('D'))
		_head->setGoDir(GO_RIGHT);
	else
		_head->setGoDir(GO_NONE);

	_light.Position = this->getPos();
	_light.Direction = (-_dir);
	D3DXVec3Normalize((D3DXVECTOR3*)&_light.Direction, (D3DXVECTOR3*)&_light.Direction);
	D3DDEVICE->SetLight(_lightChannel, &_light);
}

void cubeMan::render()
{
	character::render();

	D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(L"cubeMan"));
	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(L"cubeMan"));

	_root->render();
}

D3DXVECTOR3 cubeMan::getPos()
{
	D3DXMATRIX dirRotation;
	_dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMatrixRotationY(&dirRotation, _dirAngle);
	D3DXVec3TransformNormal(&_dir, &_dir, &dirRotation);
	D3DXVECTOR3 temp = this->getPosition() + (-1) * _dir;
	return temp;
}

int cubeMan::getIdx()
{
	//int idxX = (this->getPos().x + NUMX / 2);
	//int idxY = (this->getPos().y + NUMY / 2);
	//int idxZ = (this->getPos().z + NUMZ / 2);
	//return idxY * NUMX * NUMZ + idxZ * NUMX + idxX;
	return 0;
}

int cubeMan::getCurrentType()
{
	return _currentType;
}
