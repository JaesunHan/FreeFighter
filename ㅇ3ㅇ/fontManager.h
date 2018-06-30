#pragma once

#define FONTMANAGER	fontManager::GetInstance()

#ifndef g_pFontManager
#define g_pFontManager FONTMANAGER
#endif

class fontManager
{
public:
	enum FONT_TYPE
	{
		FONT_NONE = -1,
		FONT_DEFAULT,
		FONT_QUEST,	// µîµî
		FONT_END
	};

	SINGLETONE(fontManager)

private:
	map<FONT_TYPE, LPD3DXFONT>		_fonts;

public:
	LPD3DXFONT addFont(FONT_TYPE type);
	LPD3DXFONT findFont(FONT_TYPE type);
	BOOL deleteFont(FONT_TYPE type);
	BOOL deleteAll();

	void release();
};

