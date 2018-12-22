#include "stdafx.h"

int WINAPI fnhk_DrawTextW(HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format);

static HFONT hFont_DrawRect = NULL; //绘图区域字体
static HFONT hFont_Backup = NULL;
static void *lpfnDrawTextW = &fnhk_DrawTextW;

#define _LT_  LocaleText

LOCALE_TEXT LocaleText[] =
{
	{
		(void *)(0x98F3D2),
		NULL,
		L"Tr\0曲线\0曲線\0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x98C65D),
		NULL,
		L"/ Ref \0/ 基准 \0/ 基準 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9FB153),
		NULL,
		L"Scale \0分辨率 \0分辨率 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9926C1),
		NULL,
		L"ExtRef\0外基准\0外基准\0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9926B0),
		NULL,
		L"ExtRef\0外基准\0外基准\0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9924DF),
		NULL,
		L"Svc\0服务\0服务\0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9924F0),
		NULL,
		L"Svc\0服务\0服务\0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x987F31),
		NULL,
		L"Start \0起始 \0起始 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x987FAF),
		NULL,
		L"Stop \0终止 \0终止 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9927FE),
		NULL,
		L"Stop \0终止 \0终止 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x992815),
		NULL,
		L"Stop \0终止 \0终止 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x9928A3),
		NULL,
		L"Run \0运行 \0運行 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x992926),
		NULL,
		L"Setup \0设置 \0設置 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x992605),
		NULL,
		L"Ready \0准备 \0準備 \0\0",
		NULL,
		{ 0 }
	}
	,
	{
		(void *)(0x992616),
		NULL,
		L"Ready \0准备 \0準備 \0\0",
		NULL,
		{ 0 }
	}
};


int WINAPI fnhk_DrawTextW(HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
	HGDIOBJ hGdiObjFont = GetCurrentObject(hdc, OBJ_FONT);
	int nRet;

	SelectObject(hdc, hFont_DrawRect);
	nRet = DrawTextW(hdc, lpchText, cchText, lprc, format);
	SelectObject(hdc, hGdiObjFont);

	return nRet;
}

inline int GetMaxLocaleText()
{
	return sizeof(_LT_) / sizeof(LOCALE_TEXT);
}

void UpdateCurrentLocale()
{
	int nMax = GetMaxLocaleText();
	LPCWSTR lpcText;

	for (int nIndex = 0; nIndex < nMax; nIndex++)
	{
		lpcText = GetStringByIndex(_LT_[nIndex].lpLocaleText, nLangId);

		if (lpcText)
		{
			int nLen = wcslen(lpcText);

			if (nLen >= 48)
			{
				if (_LT_[nIndex].lpszCurText)
					free(_LT_[nIndex].lpszCurText);

				_LT_[nIndex].lpszCurText = (WCHAR *)malloc(nLen + 1);

				if (_LT_[nIndex].lpszCurText == NULL)
					continue;

				wcscpy_s(_LT_[nIndex].lpszCurText, nLen + 1, lpcText);
			}
			else
				wcscpy_s(_LT_[nIndex].szCurText, 48, lpcText);
		}
	}
}

static void SetTextHook()
{
	int nMax = GetMaxLocaleText();

	//更新当前语言翻译
	UpdateCurrentLocale();

	for (int nIndex = 0; nIndex < nMax; nIndex++)
	{
		if (_LT_[nIndex].lpOrigAddr == NULL)
		{
			if (_LT_[nIndex].lpszCurText)
				SetPointer((int *)BASE + (DWORD)_LT_[nIndex].lpHookAddr, (int *)&(_LT_[nIndex].lpOrigAddr), (int)_LT_[nIndex].lpszCurText);
			else
				SetPointer((int *)BASE + (DWORD)_LT_[nIndex].lpHookAddr, (int *)&(_LT_[nIndex].lpOrigAddr), (int)_LT_[nIndex].szCurText);
		}
	}
}

//************************************
// 函数名:    SetFuncHook
// Access:    public static 
// 返回值类型:   void
// 说明: 设置函数hook
//************************************
static void SetFuncHook()
{
	int nTmp;

	SetPointer((int *)(BASE + 0x9F8301), NULL, (int)&lpfnDrawTextW);
	SetPointer((int *)(BASE + 0x9F8372), NULL, (int)&lpfnDrawTextW);
	SetPointer((int *)(BASE + 0x94DD1A), NULL, (int)&lpfnDrawTextW);
}


int InitLocaleHook()
{
#define FONT_SIZE           12
	LOGFONTW logfont;
	int nTmp;

	//创建字体
	logfont.lfHeight = FONT_SIZE;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_NORMAL;
	logfont.lfItalic = 0;
	logfont.lfUnderline = 0;
	logfont.lfStrikeOut = 0;
	logfont.lfCharSet = GB2312_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
	logfont.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
	wcscpy_s(logfont.lfFaceName, LF_FACESIZE, L"Simsun");

	hFont_DrawRect = CreateFontIndirectW(&logfont);

	if (hFont_DrawRect == NULL) 
		return -1;

	//BYTE btTemp[5] = { 0xB8, 0, 0, 0, 0 };
	//btTemp[1] = FONT_SIZE;

	//WriteMemory((void *)(BASE + 0x132EB7), btTemp, 5);
	//WriteMemory((void *)(BASE + 0x132F0D), btTemp, 5);

	nTmp = 0x12 - FONT_SIZE;
	WriteMemory((void *)(BASE + 0x991C5F), &nTmp, sizeof(BYTE));


	//hook 相关地址
	SetTextHook();
	SetFuncHook();
	return 0;
#undef FONT_SIZE
}

#undef _LT_