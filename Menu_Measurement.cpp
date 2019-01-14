#include "stdafx.h"
#include "SharedData.h"


extern SOFT_MENU menuSimth;
extern SOFT_MENU menuPolar;

const char szAuxRange1[] = "SENSe*:VOLTage1:DC:RANGe:UPPer";
const char szAuxRange2[] = "SENSe*:VOLTage2:DC:RANGe:UPPer";


const LPCWSTR wcsListAbsolute[] =
{
	L"A(1)\0\0",
	L"A(2)\0\0",
	L"B(1)\0\0",
	L"B(2)\0\0",
	L"R1(1)\0\0",
	L"R1(2)\0\0",
	L"R2(1)\0\0",
	L"R2(2)\0\0"
};

const LPCWSTR wcsListAuxRag[] =
{
	L"1V\0\0",
	L"10V\0\0",
};

const LPCWSTR wcsListSweepPort[] =
{
	L"1\0\0",
	L"2\0\0",
};

const LPCWSTR wcsListSimth[] =
{
	L"Lin / Phase\0线性 / 相位\0線性 / 相位\0\0",
	L"Log / Phase\0对数 / 相位\0對數 / 相位\0\0",
	L"Real / Imag\0实部 / 虚部\0實部 / 虛部\0\0",
	L"R + jX\0R + jX\0R + jX\0\0",
	L"G + jB\0G + jB\0G + jB\0\0"
};

const LPCWSTR wcsListPolar[] =
{
	L"Lin / Phase\0线性 / 相位\0線性 / 相位\0\0",
	L"Log / Phase\0对数 / 相位\0對數 / 相位\0\0",
	L"Real / Imag\0实部 / 虚部\0實部 / 虛部\0\0"
};

const LPCWSTR wcsListTrackMode[] =
{
	L"Off\0关闭\0關閉\0\0",
	L"Track Peak\0跟踪峰值\0跟蹤峰值\0\0",
	L"Track Freq\0跟踪频率\0跟蹤頻率\0\0"
};

int WINAPI fnUpdateData_SParam(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnUpdateData_Format(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnUpdateData_TrackMode(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

int WINAPI fnSwitchAuxInput(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	void *lpTemp = nullptr;
	switch (dwFlags)
	{
		case 1:
		{
			OrigSoftMenu_ItemClicked2(CA_SPARAM, TA_SPARAM, 1 + PORTNUM*PORTNUM);

			lpTemp = GetSubMenuPointer(CA_SPARAM, 1 + PORTNUM*PORTNUM);

			OrigSoftMenu_Enter((void*)((DWORD)lpTemp - BASE));
			OrigSoftMenu_UpdateItems((void*)((DWORD)lpTemp - BASE));
			break;
		}
		case 2:
		{
			OrigSoftMenu_ItemClicked2(CA_SPARAM, TA_SPARAM, 2 + PORTNUM*PORTNUM);

			lpTemp = GetSubMenuPointer(CA_SPARAM, 2 + PORTNUM*PORTNUM);

			OrigSoftMenu_Enter((void*)((DWORD)lpTemp - BASE));
			OrigSoftMenu_UpdateItems((void*)((DWORD)lpTemp - BASE));
			break;
		}
	}
	lpSubItem->lpThis = (void*)((DWORD)lpTemp - BASE);
	lpSubItem->lpVTable = (void**)((DWORD)lpTemp - BASE);

	return 1;
}

int WINAPI fnUpdateIndex_AuxRange(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{

	typedef void *(__cdecl *fn_00023650)(void *lpOutput, PAVG_STRA pbsInput, int nNum);
	typedef void *(__cdecl *fn_00A33D80)(PAVG_STRA pbsVar, void *lpMemAddr2);

	fn_00023650 fn00023650 = (fn_00023650)(BASE + 0x00023650);
	fn_00A33D80 fn00A33D80 = (fn_00A33D80)(BASE + 0x00A33D80);

	DWORD nIndex = 0;
	LPCWSTR *lppWStr = (LPCWSTR *)lpSubItem->lpParams;
	LPCWSTR lpText = NULL;

	if (lpSubItem->lpOpt[2] == NULL)
		return -1;

	if (!lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] + BASE);
		lpSubItem->lpOpt[12] = (void*)0x1;
	}


	void *lpAlloc, *lpTmp;
	int nLen = strlen((char*)(lpSubItem->lpOpt[2]));
	AVG_STRA bsVar;
	BYTE btUnkObj[0x50] = { 0 };

	if (nLen == 0)
		return -2;

	lpAlloc = malloc(nLen + 0xF);

	bsVar.lpszText = (char *)lpAlloc;
	bsVar.dwStringLen = nLen;

	if (bsVar.lpszText == NULL)
		return -3;

	bsVar.lpszText[0] = GET_BYTE_0(lpSubItem->lpOpt[0]);
	bsVar.lpszText++;

	if (bsVar.dwStringLen >= 0x8)
	{
		bsVar.dwBufferMaxLen = nLen + 0x8;
		strcpy_s(bsVar.lpszText, bsVar.dwBufferMaxLen, (char*)(lpSubItem->lpOpt[2]));
	}
	else
	{
		bsVar.dwBufferMaxLen = 0x7;
		strcpy_s(bsVar.szText, bsVar.dwBufferMaxLen, (char*)(lpSubItem->lpOpt[2]));
	}

	lpTmp = fn00023650(btUnkObj, &bsVar, 0);

	lpTmp = fn00A33D80((PAVG_STRA)((int)lpTmp + 0x24), GetOffsetPointer(lpTmp, 0x20));
	nIndex = *(int *)((int)lpTmp + 0x24);

	if (nIndex == 0x40240000)
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], L"10V");
	else if (nIndex == 0x3FF00000)
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], L"1V");

	return 0;
}

int WINAPI fnItemClicked_AuxRange1(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		fnSwitchAuxInput(1, 0, 0, lpSubItem);
		fnUpdateIndex_AuxRange(0, 0, 0, lpSubItem);
	}

	return 0;
}


int WINAPI fnItemSelected_AuxInput1(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem, int nIndex)
{
	if (nIndex == -1)
		nIndex = 0;
	void *lpTemp = nullptr;

	fnSwitchAuxInput(1, 0, 0, lpSubItem);

	lpTemp = GetSubMenuPointer(lpSubItem->lpThis, 1);

	OrigSoftMenu_UpdateItems((void*)((DWORD)lpTemp - BASE));
	OrigSoftMenu_Enter((void*)((DWORD)lpTemp - BASE));
	
	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpTemp - BASE), (void**)((DWORD)lpTemp - BASE), nIndex);

	return 0;
}

int WINAPI fnItemClicked_AuxRange2(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		fnSwitchAuxInput(2, 0, 0, lpSubItem);
		fnUpdateIndex_AuxRange(0, 0, 0, lpSubItem);
	}

	return 0;
}


int WINAPI fnItemSelected_AuxInput2(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem, int nIndex)
{
	if (nIndex == -1)
		nIndex = 0;
	void *lpTemp = nullptr;

	fnSwitchAuxInput(2, 0, 0, lpSubItem);

	lpTemp = GetSubMenuPointer(lpSubItem->lpThis, 1);

	OrigSoftMenu_UpdateItems((void*)((DWORD)lpTemp - BASE));
	OrigSoftMenu_Enter((void*)((DWORD)lpTemp - BASE));

	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpTemp - BASE), (void**)((DWORD)lpTemp - BASE), nIndex);

	return 0;
}


//S参数子条目
SOFT_SUB_ITEM subitemSParam[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GROUP | SIA_GETBTNSTATE,
		SIS_RadioButtonEx,
		0,
		L"S11\0S11\0S11\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D62184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, &fnUpdateData_SParam, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_SPARAM,
		CA_SPARAM,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		1,
		L"S21\0S21\0S21\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM,
		CA_SPARAM,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		2,
		L"S12\0S12\0S12\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM,
		CA_SPARAM,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		3,
		L"S22\0S22\0S22\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM,
		CA_SPARAM,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	/*	,
		{
			SIF_ORIGCLICK ,
			SIA_FULLLINE  ,
			SIS_RadioButtonEx,
			4,
			L"S12\0S12\0S12\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_SPARAM,
			CA_SPARAM,
			0,
			NULL,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_RadioButtonEx,
			5,
			L"S22\0S22\0S22\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_SPARAM,
			CA_SPARAM,
			0,
			NULL,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_RadioButtonEx,
			6,
			L"S32\0S32\0S32\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_SPARAM,
			CA_SPARAM,
			0,
			NULL,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_RadioButtonEx,
			7,
			L"S42\0S42\0S42\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_SPARAM,
			CA_SPARAM,
			0,
			NULL,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
			,
			{
				SIF_ORIGCLICK ,
				SIA_FULLLINE  ,
				SIS_RadioButtonEx,
				8,
				L"S13\0S13\0S13\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				RESERVE_DWORD16,
				RESERVE_DWORD16,
				0,
				NULL,
				NULL,
				TA_SPARAM,
				CA_SPARAM,
				0,
				NULL,
				RESERVE_DWORD4,
				RESERVE_DWORD4
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_RadioButtonEx,
				9,
				L"S23\0S23\0S23\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				RESERVE_DWORD16,
				RESERVE_DWORD16,
				0,
				NULL,
				NULL,
				TA_SPARAM,
				CA_SPARAM,
				0,
				NULL,
				RESERVE_DWORD4,
				RESERVE_DWORD4
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_RadioButtonEx,
				10,
				L"S33\0S33\0S33\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				RESERVE_DWORD16,
				RESERVE_DWORD16,
				0,
				NULL,
				NULL,
				TA_SPARAM,
				CA_SPARAM,
				0,
				NULL,
				RESERVE_DWORD4,
				RESERVE_DWORD4
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_RadioButtonEx,
				11,
				L"S43\0S43\0S43\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				RESERVE_DWORD16,
				RESERVE_DWORD16,
				0,
				NULL,
				NULL,
				TA_SPARAM,
				CA_SPARAM,
				0,
				NULL,
				RESERVE_DWORD4,
				RESERVE_DWORD4
			}
				,
				{
					SIF_ORIGCLICK ,
					SIA_FULLLINE  ,
					SIS_RadioButtonEx,
					12,
					L"S14\0S14\0S14\0\0",
					NULL,
					BtnWidth_W,
					BtnHeith_H,
					NULL,
					RESERVE_DWORD16,
					RESERVE_DWORD16,
					0,
					NULL,
					NULL,
					TA_SPARAM,
					CA_SPARAM,
					0,
					NULL,
					RESERVE_DWORD4,
					RESERVE_DWORD4
				}
				,
				{
					SIF_ORIGCLICK,
					SIA_FULLLINE,
					SIS_RadioButtonEx,
					13,
					L"S24\0S24\0S24\0\0",
					NULL,
					BtnWidth_W,
					BtnHeith_H,
					NULL,
					RESERVE_DWORD16,
					RESERVE_DWORD16,
					0,
					NULL,
					NULL,
					TA_SPARAM,
					CA_SPARAM,
					0,
					NULL,
					RESERVE_DWORD4,
					RESERVE_DWORD4
				}
				,
				{
					SIF_ORIGCLICK,
					SIA_FULLLINE,
					SIS_RadioButtonEx,
					14,
					L"S34\0S34\0S34\0\0",
					NULL,
					BtnWidth_W,
					BtnHeith_H,
					NULL,
					RESERVE_DWORD16,
					RESERVE_DWORD16,
					0,
					NULL,
					NULL,
					TA_SPARAM,
					CA_SPARAM,
					0,
					NULL,
					RESERVE_DWORD4,
					RESERVE_DWORD4
				}
				,
				{
					SIF_ORIGCLICK,
					SIA_FULLLINE,
					SIS_RadioButtonEx,
					15,
					L"S44\0S44\0S44\0\0",
					NULL,
					BtnWidth_W,
					BtnHeith_H,
					NULL,
					RESERVE_DWORD16,
					RESERVE_DWORD16,
					0,
					NULL,
					NULL,
					TA_SPARAM,
					CA_SPARAM,
					0,
					NULL,
					RESERVE_DWORD4,
					RESERVE_DWORD4
				}*/
,
{
	0,
	SIA_FULLLINE,
	SIS_Delimiter,
	0,
	L"Absolute\0Absolute\0Absolute\0\0",
	NULL,
	40,
	BtnHeith_DH,
	NULL,
	RESERVE_DWORD16,
	RESERVE_DWORD16,
	INVALID_INDEX,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	{ 0, 0, 0, 0 }
}
,
{
	SIF_FN_SELECTED,
	SIA_FULLLINE,
	SIS_ComboRadioButtonEx,
	0,
	L"Absolute\0Absolute\0Absolute\0\0",
	NULL,
	BtnWidth_W,
	BtnHeith_H2,
	NULL,
	RESERVE_DWORD16,
	{ 0, 0, &fnItemSelected_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	0,
	NULL,
	NULL,
	TA_SPARAM_ABSOLUTE,
	CA_SPARAM_ABSOLUTE,
	sizeof(wcsListAbsolute) / sizeof(LPCWSTR),
	wcsListAbsolute,
	RESERVE_DWORD4,
	RESERVE_DWORD4
}
,
{
	0,
	SIA_FULLLINE,
	SIS_Delimiter,
	0,
	L"Aux Input 1\0Aux Input 1\0Aux Input 1\0\0",
	NULL,
	40,
	BtnHeith_DH,
	NULL,
	RESERVE_DWORD16,
	RESERVE_DWORD16,
	INVALID_INDEX,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	RESERVE_DWORD4
}
,
{
	SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA | SIF_FN_SWITCH,
	SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
	SIS_ButtonEx,
	0,
	L"Range\0范围\0範圍\0\0",
	NULL,
	BtnWidth_W,
	BtnHeith_H2,
	NULL,
	{ (void *)0x00010000, 0, (void *)szAuxRange1, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
	{ 0, &fnItemClicked_AuxRange1, 0, &fnUpdateIndex_AuxRange, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	INVALID_INDEX,
	NULL,
	NULL,
	TA_SPARAM_AUXINPUT,
	TA_SPARAM_AUXINPUT,
	sizeof(wcsListAuxRag) / sizeof(LPCWSTR),
	wcsListAuxRag,
	RESERVE_DWORD4,
	RESERVE_DWORD4
}
,
{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA | SIF_FN_SWITCH,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		1,
		L"Sweep Port\0扫描端口\0掃描端口\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D621C4, (void *)0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_AuxInput1, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SPARAM_AUXINPUT,
		TA_SPARAM_AUXINPUT,
		sizeof(wcsListSweepPort) / sizeof(LPCWSTR),
		wcsListSweepPort,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		L"Aux Input 2\0Aux Input 2\0Aux Input 2\0\0",
		NULL,
		40,
		BtnHeith_DH,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA | SIF_FN_SWITCH,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		0,
		L"Range\0范围\0範圍\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)szAuxRange2, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		{ 0, &fnItemClicked_AuxRange2, 0, &fnUpdateIndex_AuxRange, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SPARAM_AUXINPUT,
		TA_SPARAM_AUXINPUT,
		sizeof(wcsListAuxRag) / sizeof(LPCWSTR),
		wcsListAuxRag,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA | SIF_FN_SWITCH,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		1,
		L"Sweep Port\0扫描端口\0掃描端口\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D621C4, (void *)0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_AuxInput2, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SPARAM_AUXINPUT,
		TA_SPARAM_AUXINPUT,
		sizeof(wcsListSweepPort) / sizeof(LPCWSTR),
		wcsListSweepPort,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//绝对子条目
SOFT_SUB_ITEM subitemAbsolute[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GROUP | SIA_GETBTNSTATE,
		SIS_RadioButtonEx,
		0,
		L"A(1)\0A(1)\0A(1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D621C4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		1,
		L"A(2)\0A(2)\0A(2)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		2,
		L"B(1)\0B(1)\0B(1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		3,
		L"B(2)\0B(2)\0B(2)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		4,
		L"R1(1)\0R1(1)\0R1(1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE ,
		SIS_RadioButtonEx,
		5,
		L"R1(2)\0R1(2)\0R1(2)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		6,
		L"R2(1)\0R2(1)\0R2(1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		7,
		L"R2(2)\0R2(2)\0R2(2)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SPARAM_ABSOLUTE,
		CA_SPARAM_ABSOLUTE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//格式子条目
SOFT_SUB_ITEM subitemFormat[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GROUP | SIA_GETBTNSTATE,
		SIS_RadioButtonEx,
		0,
		L"Log Mag\0对数\0對數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D648A4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, &fnUpdateData_Format, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		1,
		L"Phase\0相位\0相位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		2,
		L"Group Delay\0群延迟\0群延遲\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED,
		SIA_FULLLINE,
		SIS_ComboRadioButtonEx,
		3,
		L"Smith\0史密斯圆图\0史密斯圓圖\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, &fnItemSelected_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_SIMTH,
		CA_SIMTH,
		sizeof(wcsListSimth) / sizeof(LPCWSTR),
		wcsListSimth,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED,
		SIA_FULLLINE,
		SIS_ComboRadioButtonEx,
		4,
		L"Polar\0极坐标\0極坐標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, &fnItemSelected_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_POLAR,
		CA_POLAR,
		sizeof(wcsListPolar) / sizeof(LPCWSTR),
		wcsListPolar,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		5,
		L"Lin Mag\0线性\0線性\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		6,
		L"SWR\0SWR\0SWR\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		7,
		L"Real\0实部\0實部\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		8,
		L"Imaginary\0虚部\0虛部\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		9,
		L"Expand Phase\0扩展相位\0擴展相位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_RadioButtonEx,
		10,
		L"Positive Phase\0正相位\0正相位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_FORMAT,
		CA_FORMAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//标尺子条目
SOFT_SUB_ITEM subitemScale[] =
{
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		3,
		L"Scale/Div\0分辨率/格\0分辨率/格\0\0",
		NULL,
		BtnWidth_W,
		52,
		NULL,
		{ 0, (void *)0x0163B260, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_UPDATEDATA,
		SIS_InputButtonEx,
		2,
		L"Divisions\0格数\0格數\0\0",
		NULL,
		BtnWidth_W,
		52,
		NULL,
		{ 0, (void *)0x010B5B10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		4,
		L"Reference Position\0基准位置\0基准位置\0\0",
		NULL,
		BtnWidth_W,
		52,
		NULL,
		{ 0, (void *)0x010B5B00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		5,
		L"Reference Value\0基准数值\0基准數值\0\0",
		NULL,
		BtnWidth_W,
		52,
		NULL,
		{ 0, (void *)0x010B5AE8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		7,
		L"Marker -> Reference\0频标 -> 基准\0頻標 -> 基准\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		8,
		L"Electrical Delay\0电子延迟\0電子延遲\0\0",
		NULL,
		BtnWidth_W,
		52,
		NULL,
		{ 0, (void *)0x010B5B20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_ELECTDELAY,
		CA_ELECTDELAY,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		9,
		L"Phase Offset\0相位偏移\0相位偏移\0\0",
		NULL,
		BtnWidth_W,
		52,
		NULL,
		{ 0, (void *)0x010B5B60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//定标子条目
SOFT_SUB_ITEM subitemAutoScale[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Auto Scale\0自动定标\0自動定標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"Auto Scale All\0自动定标 (全部)\0自動定標 (全部)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_SCALE,
		CA_SCALE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


int WINAPI fnTagPageEnter_Format(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_FORMAT);
	return 0;
}

int WINAPI  fnTagPageEnter_Absolute(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_SPARAM_ABSOLUTE);
	return 0;
}

int WINAPI fnTagPageEnter_SParam(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	BOOL blTmp = FALSE;

	DirectCall((void*)(BASE + (DWORD)CA_SPARAM), GetOffsetPointer((void*)(BASE + (DWORD)TA_SPARAM), 0x08));

	OrigSoftMenu_GetItemState(CA_SPARAM, 2, &blTmp, NULL, NULL);

	if (blTmp & 0xFF)
		NOT_FLAGS(subitemSParam[2].dwAttributes, SIAE_DISABLED);
	else
		SET_FLAGS(subitemSParam[2].dwAttributes, SIAE_DISABLED);


	OrigSoftMenu_GetItemState(CA_SPARAM, 3, &blTmp, NULL, NULL);

	if (blTmp & 0xFF)
		NOT_FLAGS(subitemSParam[3].dwAttributes, SIAE_DISABLED);
	else
		SET_FLAGS(subitemSParam[3].dwAttributes, SIAE_DISABLED);

	return 0;
}



//测量子菜单
SOFT_TAG_PAGE submenuMeasurement[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"S Parameter\0S参数\0S參數\0\0",
		NULL,
		sizeof(subitemSParam) / sizeof(SOFT_SUB_ITEM),
		subitemSParam,
		RESERVE_DWORD4,
		&fnTagPageEnter_SParam,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Selecting_Measurement_Parameters.htm#S_parameters", (void*)1027, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Absolute\0绝对\0絕對\0\0",
		NULL,
		sizeof(subitemAbsolute) / sizeof(SOFT_SUB_ITEM),
		subitemAbsolute,
		RESERVE_DWORD4,
		&fnTagPageEnter_SParam,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Selecting_Measurement_Parameters.htm#S_parameters", (void*)1027, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Foramt\0格式\0格式\0\0",
		NULL,
		sizeof(subitemFormat) / sizeof(SOFT_SUB_ITEM),
		subitemFormat,
		RESERVE_DWORD4,
		&fnTagPageEnter_Format,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Selecting_a_Data_Format.htm", (void*)1028, 0, 0 }
	}
	,
	{
		0,
		0,
		L"Scale\0标尺\0標尺\0\0",
		NULL,
		sizeof(subitemScale) / sizeof(SOFT_SUB_ITEM),
		subitemScale,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_the_Scales.htm", (void*)1029, 0, 0 }
	}
	,
	{
		0,
		0,
		L"Auto Scale\0定标\0定標\0\0",
		NULL,
		sizeof(subitemAutoScale) / sizeof(SOFT_SUB_ITEM),
		subitemAutoScale,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_the_Scales.htm", (void*)1029, 0, 0 }
	}
};

//测量主菜单
SOFT_MENU menuMeasurement =
{
	0,
	0,
	L"Measurement\0测量\0測量\0\0",
	NULL,
	sizeof(submenuMeasurement) / sizeof(SOFT_TAG_PAGE),
	submenuMeasurement,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};


int WINAPI fnUpdateData_SParam(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;

	TDMenu *temp = nullptr;
	if (uiCurFocusMenu == 2)
		temp = cwMenuWnd2;
	else
		temp = cwMenuWnd;
	
	if (lpSubItem->lpOpt[2] == NULL) 
		return -1;

	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}
	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);

	switch (nIndex)
	{
	case 1:
	case 2:
	case 3:
		temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, nIndex);
		break;
	default:
		temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, 0);
		break;
	}

	return 0;
}

int WINAPI fnUpdateData_Format(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;

	TDMenu *temp = nullptr;
	if (uiCurFocusMenu == 2)
		temp = cwMenuWnd2;
	else
		temp = cwMenuWnd;

	if (lpSubItem->lpOpt[2] == NULL)
		return -1;
	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}
	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);

	switch (nIndex)
	{
	case 1:
	case 2:
		temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, nIndex);
		break;

	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, nIndex - 6);
		break;

	case 3:
	case 4:
	case 5:
	case 6:
	case 7:

		if (3 < (sizeof(subitemFormat) / sizeof(SOFT_SUB_ITEM)))
		{
			if (subitemFormat[3].dwStyle == SIS_ComboButtonEx || subitemFormat[3].dwStyle == SIS_ComboRadioButtonEx)
				ComboBox_SetCurSel((HWND)subitemFormat[3].lpOpt[4], nIndex - 3);
			temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, 3);
		}

		break;

	case 8:
	case 9:
	case 10:

		if (4 < (sizeof(subitemFormat) / sizeof(SOFT_SUB_ITEM)))
		{
			if (subitemFormat[4].dwStyle == SIS_ComboButtonEx || subitemFormat[4].dwStyle == SIS_ComboRadioButtonEx)
				ComboBox_SetCurSel((HWND)subitemFormat[4].lpOpt[4], nIndex - 8);
			temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, 4);
		}

		break;

	default:
		temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, 0);
		break;
	}

	return 0;
}


int WINAPI fnUpdateData_TrackMode(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;

	if (lpSubItem->lpOpt[2] == NULL) 
		return -1;
	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}
	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);
	ComboBox_SetCurSel((HWND)lpSubItem->lpOpt[4], nIndex);

	return 0;
}

