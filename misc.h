#pragma once

#ifndef _INC_WINDOWS
#include <Windows.h>
#endif

#ifndef _INC_WINDOWSX
#include <Windowsx.h>
#endif

static WORD wBackupWidth;

typedef struct _HOOK_POINTER
{
  void                 ** lppPtrAddr;
  void                  * lpOrgAddr;
  void                  * lpDestAddr;
} HOOK_PTR, *PHOOK_PTR;

typedef struct _HOOK_JUMPPOINTER
{
  DWORD                   lpInstAddr;
  DWORD                   dwAddress;
  DWORD                   dwSize;
  BYTE                    btBackup[16];
} HOOK_JMPPTR, *PHOOK_JMPPTR;

typedef struct _BAS_STR
{
	char          * lpszText;
	void          * lpUnkObj1;     //BYTE ?
	void          * lpUnkObj2;     //BYTE ?
	void          * lpUnkObj3;     //BYTE ?
	DWORD           dwStringLen;
	DWORD           dwBufferMaxLen;
} BAS_STR, *PBAS_STR;

//avg输入输出字符结构体
typedef struct _AVG_STR
{
	union
	{
		WCHAR			szText[8];
		WCHAR			*lpszText;
	};
	DWORD           dwStringLen;
	DWORD           dwBufferMaxLen;
}AVG_STR, *PAVG_STR;

typedef struct _AVG_STRA
{
	union
	{
		char			szText[16];
		char			*lpszText;
	};
	DWORD           dwStringLen;
	DWORD           dwBufferMaxLen;
}AVG_STRA, *PAVG_STRA;

//本地化文本的HOOK结构体
typedef struct _LOCALE_TEXT_
{
  void          * lpHookAddr;
  void          * lpOrigAddr;
  const WCHAR   * lpLocaleText;
  WCHAR          * lpszCurText;
  WCHAR            szCurText[48];
} LOCALE_TEXT, *PLOCALE_TEXT;

//原程序free函数
typedef void(__cdecl *fn_Free)(void *_Block);

typedef double(__thiscall *fn_GetDouble)(void *lpThis);

typedef BOOL(__thiscall *fn_SetDouble)(void *lpThis, double dblInput);

typedef PAVG_STR(__thiscall *fn_FmtToStringAvg)(void *lpThis, PAVG_STR lpOutBasStr, double dblVal);

typedef PAVG_STR(__thiscall *fn_FmtToString)(void *lpThis, PAVG_STR lpOutBasStr, double dblVal);

typedef double(__thiscall *fn_ScanfToDouble)(void *lpThis, PAVG_STR lpInBasStr);

bool GetScreenRect(int ScreenNo, RECT *rect);
/*
Finetune::
nNumber:
旋钮轻微扭动,鼠标点击微调控件:0
旋钮猛烈扭动:2

*/
typedef double(__thiscall *fn_FineTune)(void *lpThis, double dblVal, bool blUpDown, int nNumber /* 0,1,2 */);

typedef double(__thiscall *fn_FineTune2)(void *lpThis, double dblVal, bool blUpDown);



typedef BOOL(__stdcall * pEnumDiaplayDevices)
(
	LPCTSTR lpDevice,                // device name
	DWORD iDevNum,                   // display device
	PDISPLAY_DEVICE lpDisplayDevice, // device information
	DWORD dwFlags                    // reserved
);