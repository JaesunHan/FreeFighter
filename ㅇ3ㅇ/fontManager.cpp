#include "stdafx.h"
#include "fontManager.h"


fontManager::fontManager()
{
}


fontManager::~fontManager()
{
}

LPD3DXFONT fontManager::addFont(FONT_TYPE type)
{
	LPD3DXFONT newFont = findFont(type);

	if (newFont)
		return newFont;

	D3DXFONT_DESC desc;
	ZeroMemory(&desc, sizeof(D3DXFONT_DESC));

	if (type == FONT_DEFAULT)
	{
		desc.Height = 25;
		desc.Width = 13;
		desc.Weight = FW_MEDIUM;
		desc.Italic = false;
		desc.CharSet = DEFAULT_CHARSET;
		desc.OutputPrecision = OUT_DEFAULT_PRECIS;
		desc.PitchAndFamily = FF_DONTCARE;
	}

	D3DXCreateFontIndirect(D3DDEVICE, &desc, &newFont);
	_fonts.insert(make_pair(type, newFont));

	return newFont;
}

LPD3DXFONT fontManager::findFont(FONT_TYPE type)
{
	map<FONT_TYPE, LPD3DXFONT>::iterator iter = _fonts.find(type);

	if (iter != _fonts.end())
	{
		return iter->second;
	}

	return NULL;
}

BOOL fontManager::deleteFont(FONT_TYPE type)
{
	map<FONT_TYPE, LPD3DXFONT>::iterator iter = _fonts.find(type);

	if (iter != _fonts.end())
	{
		iter->second->Release();
		_fonts.erase(iter);
		return TRUE;
	}

	return FALSE;
}

BOOL fontManager::deleteAll()
{
	map<FONT_TYPE, LPD3DXFONT>::iterator iter = _fonts.begin();
	for (iter; iter != _fonts.end();)
	{
		if (iter->second)
		{
			iter->second->Release();
			iter = _fonts.erase(iter);
		}
		else ++iter;
	}

	_fonts.clear();

	return TRUE;
}

void fontManager::release()
{
	this->deleteAll();
}
