#include "stdafx.h"
#include "button.h"


button::button()
	: _sprite(NULL)
	, _isSelected(false)
	, _buttonName(_T(""))
	, _pos(0.0f, 0.0f, 0.0f)
{
}


button::~button()
{
}

#ifdef UNICODE
HRESULT button::init(wstring buttonName, wstring fileName, float x, float y)
#else
HRESULT button::init(string buttonName, string fileName, float x, float y)
#endif
{
	if (!TEXTUREMANAGER->addTexture(buttonName, fileName.c_str())) return E_FAIL;

	D3DXCreateSprite(D3DDEVICE, &_sprite);

	_width = TEXTUREMANAGER->find(buttonName)->textureInfo.Width;
	_height = TEXTUREMANAGER->find(buttonName)->textureInfo.Height;

	_buttonName = buttonName;
	_buttonRc = RectMake(0, 0, _width, _height / 2);

	_isSelected = false;

	_pos.x = x - _width / 2;
	_pos.y = y - _height / 2;

	return S_OK;
}

void button::release()
{
	SAFE_RELEASE(_sprite);
}

void button::update()
{
	RECT clickRange = RectMake(_pos.x, _pos.y, _width, _height / 2);
	if (PtInRect(&clickRange, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			_isSelected = true;
		else
			_isSelected = false;
	}
	else
		_isSelected = false;

	if (_isSelected)
		_buttonRc = RectMake(0, _height / 2, _width, _height / 2);
	else
		_buttonRc = RectMake(0, 0, _width, _height / 2);
}

void button::render()
{
	if (!_sprite) return;

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->Draw(TEXTUREMANAGER->findTexture(_buttonName),
		&_buttonRc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&_pos,
		WHITE);

	_sprite->End();
}
