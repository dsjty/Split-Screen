#include "stdafx.h"
#include "SharedData.h"

const LPCSTR szTRACking[] =
{
	"CALCulate*:TRACe*:MARKer1:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer2:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer3:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer4:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer5:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer6:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer7:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer8:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer9:FUNCtion:TRACking",
	"CALCulate*:TRACe*:MARKer10:FUNCtion:TRACking",
};

const LPCSTR szMULTiTRACking[] =
{
	"CALCulate*:TRACe*:MARKer1:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer2:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer3:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer4:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer5:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer6:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer7:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer8:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer9:FUNCtion:MULTi:TRACking",
	"CALCulate*:TRACe*:MARKer10:FUNCtion:MULTi:TRACking",
};

const char szPPOLarity[] = "CALCulate*:TRACe*:MARKer*:FUNCtion:PPOLarity";
const char szMULTiPPOLarity[] = "CALCulate*:TRACe*:MARKer*:FUNCtion:MULTi:PPOLarity";
const char szTTRansition[] = "CALCulate*:TRACe*:MARKer*:FUNCtion:TTRansition";
const char szMULTiTTRansition[] = "CALCulate*:TRACe*:MARKer*:FUNCtion:MULTi:TTRansition";


const LPCWSTR wcsListOffOn[] =
{
	L"Off\0关闭\0關閉\0\0",
	L"On\0打开\0打開\0\0"
};

const LPCWSTR wcsListTristate[] =
{
	L"Positive\0正\0正\0\0",
	L"Negative\0负\0負\0\0",
	L"Both\0两者\0兩者\0\0"
};

int WINAPI fnItemClicked_Marker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_RefMarker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_ClrAllMarker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_MarkerToRefMarker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_RefMarkerMode(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

//PopWndUpdateProc
int WINAPI func_PWUP_Marker(PSOFT_SUB_ITEM lpSubItem, PPWUPS lpPWUPS, DWORD dwFlags);


//频标子条目
SOFT_SUB_ITEM subitemMarker[] =
{
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		0,
		L"Marker 1\0频标 1\0頻標 1\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)0, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)1, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		1,
		L"Marker 2\0频标 2\0頻標 2\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)1, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)2, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		2,
		L"Marker 3\0频标 3\0頻標 3\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)2, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)3, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		3,
		L"Marker 4\0频标 4\0頻標 4\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)3, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)4, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		0,
		L"Marker 5\0频标 5\0頻標 5\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)4, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)5, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MREMARKER,
		CA_MREMARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		1,
		L"Marker 6\0频标 6\0頻標 6\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)5, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)6, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MREMARKER,
		CA_MREMARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		2,
		L"Marker 7\0频标 7\0頻標 7\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)6, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)7, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MREMARKER,
		CA_MREMARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		3,
		L"Marker 8\0频标 8\0頻標 8\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)7, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)8, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MREMARKER,
		CA_MREMARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_UNCHECKFUNC | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_PSTMSG_432_2 | SIA_FULLLINE,
		SIS_CheckButtonEx,
		4,
		L"Marker 9\0频标 9\0頻標 9\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)8, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)9, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_Marker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MREMARKER,
		CA_MREMARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER | SIF_POPINPUTWND | SIF_FN_CLICKED,
		SIA_FULLLINE | SIA_GETCHKSTATE | SIA_FINETUNE | SIA_FINETUNE2 | SIA_SETSTATEIDX | SIA_UPDATEITEM | SIA_PSTMSG_432_2,
		SIS_CheckButtonEx,
		5,
		L"Ref Marker\0基准频标\0基準頻標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ 0, (void *)0x010AEF8C, (void *)0x035BADD0, (void *)9, 0, 0, 0, 0, TA_CLRMARKER, CA_CLRMARKER, (void *)10, &func_PWUP_Marker, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_RefMarker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_CLICKED,
		SIA_FULLLINE | SIA_UPDATEITEM | SIA_PSTMSG_432_2,
		SIS_ButtonEx,
		0,
		L"All OFF\0清除所有频标\0清除所有頻標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_ClrAllMarker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CLRMARKER,
		CA_CLRMARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED,
		SIA_FULLLINE | SIA_UPDATEITEM | SIA_PSTMSG_432_2,
		SIS_ButtonEx,
		7,
		L"Marker -> Ref Marker\0频标 -> 基准频标\0頻標 -> 基準頻標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_MarkerToRefMarker, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		8,
		L"Ref Marker Mode\0基准频标模式\0基準頻標模式\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D7AF78, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_RefMarkerMode, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKER,
		CA_MARKER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

int WINAPI fnItemClicked_Marker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		int nCurIndex = 0;
		bool blRef = false;

		OrigSoftMenu_UpdateItems(CA_MARKER);
		UpdateCheckBoxState(lpSubItem);

		GetMarkerStateIndex((void *)(0x035BADD0), &nCurIndex, NULL, &blRef);

		if (nCurIndex == 9)
			EnableWindow(subitemMarker[11]._hWnd, FALSE);
		else
			EnableWindow(subitemMarker[11]._hWnd, TRUE);

		PopWnd_UpdateInputBox();
	}

	return 0;
}

int WINAPI fnItemClicked_RefMarker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		int nCurIndex = 0;
		bool blRef = false;

		OrigSoftMenu_UpdateItems(CA_MARKER);
		UpdateCheckBoxState(lpSubItem);

		GetMarkerStateIndex((void *)0x035BADD0, &nCurIndex, NULL, &blRef);

		if (nCurIndex == 9)
			EnableWindow(subitemMarker[11]._hWnd, FALSE);
		else
			EnableWindow(subitemMarker[11]._hWnd, TRUE);

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED))
		{
			if (nCurIndex == 9)
			{
				PopWnd_SetTitleSuffix(NULL);
			}
			else
			{
				if (blRef)
					PopWnd_SetTitleSuffix(GetStringByIndex(L"-Ref\0-基准\0-基準\0\0", nLangId));
				else
					PopWnd_SetTitleSuffix(NULL);
			}
		}
		else
			PopWnd_SetTitleSuffix(NULL);

		PopWnd_UpdateInputBox();
	}

	return 0;
}

int WINAPI fnItemClicked_ClrAllMarker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		if (MessageBoxW(hwMainWnd, GetStringByIndex(L"Clear all markers?\0是否清除所有频标?\0是否清除所有頻標?\0\0", nLangId), L"Info", MB_YESNO) == IDYES)
		{
			OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
			OrigSoftMenu_UpdateItems(CA_MARKER);
			PopWnd_Destroy(NULL, TRUE);
		}
	}

	return 0;
}

int WINAPI fnItemClicked_MarkerToRefMarker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_UpdateItems(CA_MARKER);
		PopWnd_UpdateInputBox();
	}

	return 0;
}

int WINAPI fnItemClicked_RefMarkerMode(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		int nCurIndex = 0;
		bool blRef = false;

		UpdateCheckBoxState(lpSubItem);
		GetMarkerStateIndex((void *)0x035BADD0, &nCurIndex, NULL, &blRef);

		if (nCurIndex == 9)
			EnableWindow(subitemMarker[11]._hWnd, FALSE);
		else
			EnableWindow(subitemMarker[11]._hWnd, TRUE);

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED))
		{
			if (nCurIndex == 9)
			{
				PopWnd_SetTitleSuffix(NULL);
			}
			else
			{
				if (blRef)
					PopWnd_SetTitleSuffix(GetStringByIndex(L"-Ref\0-基准\0-基準\0\0", nLangId));
				else
					PopWnd_SetTitleSuffix(NULL);
			}
		}
		else
			PopWnd_SetTitleSuffix(NULL);

		PopWnd_UpdateInputBox();
	}
	return 0;
}

int WINAPI func_PWUP_Marker(PSOFT_SUB_ITEM lpSubItem, PPWUPS lpPWUPS, DWORD dwFlags)
{
	int nCurIndex = 0;
	bool blRef = false;

	TDMenu *temp;
	if (2 == uiCurFocusMenu)
		temp = cwMenuWnd2;
	else
		temp = cwMenuWnd;


	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}

	GetMarkerStateIndex(lpSubItem->lpOpt[2], &nCurIndex, NULL, &blRef);

	switch (nCurIndex)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	{
		DWORD dwFlags = 0;

		if (CHK_FLAGS(subitemMarker[nCurIndex].dwAttributes, SIA_FINETUNE))
			SET_FLAGS(dwFlags, SIA_FINETUNE);

		if (CHK_FLAGS(subitemMarker[nCurIndex].dwAttributes, SIA_FINETUNE2))
			SET_FLAGS(dwFlags, SIA_FINETUNE2);

		lpPWUPS->lpSubItem = &subitemMarker[nCurIndex];
		lpPWUPS->lpInput = subitemMarker[nCurIndex].lpOpt[1];
		lpPWUPS->lpTitle = GetStringByIndex(lpSubItem->lpszItemText, nLangId);

		if (nCurIndex == 9)
		{
			lpPWUPS->lpwcsSuffix[0] = 0;
			EnableWindow(subitemMarker[11]._hWnd, FALSE);
		}
		else
		{
			if (blRef)
				wcscpy_s(lpPWUPS->lpwcsSuffix, MAX_PATH, GetStringByIndex(L"-Ref\0-基准\0-基準\0\0", nLangId));
			else
				lpPWUPS->lpwcsSuffix[0] = 0;

			EnableWindow(subitemMarker[11]._hWnd, TRUE);
		}

		temp->tdItem->SoftItem_ActivationItem(lpPWUPS->lpSubItem);
	}
	break;

	default:
		return -1;
		break;
	}

	return 0;
}

static int WINAPI fnUpdateData_Tracking(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = GetSubMenuSelected_Radio(CA_MARKERSEA), nCurIndex;
	bool blRef;

	GetMarkerStateIndex((void *)0x035BADD0, &nCurIndex, NULL, &blRef);

	if (nCurIndex < 0 || nCurIndex > 9)
	{
		lpSubItem->lpOpt[2] = (void *)szTRACking[0];
		lpSubItem->lpOpt[12] = (void*)1;
		return 0;
	}

	switch (nIndex)
	{
	case 4:
	case 5:
		lpSubItem->lpOpt[2] = (void *)szMULTiTRACking[nCurIndex];
		lpSubItem->lpOpt[12] = (void*)1;
		break;

	default:
		lpSubItem->lpOpt[2] = (void *)szTRACking[nCurIndex];
		lpSubItem->lpOpt[12] = (void*)1;
		break;
	}

	return 0;
}

//频标搜索子条目
SOFT_SUB_ITEM subitemMarkerSearch[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Max\0最大\0最大\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
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
		L"Min\0最小\0最小\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEDATA,
		SIS_CheckButtonEx,
		6,
		L"Tracking\0跟踪\0跟蹤\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x5E, 0, (void *)szTRACking[0], (void *)0x00001077, 0, 0, 0, 0, 0, 0, 0, 0,(void*)1, 0, 0, 0 },
		{ 0, 0, 0, &fnUpdateData_Tracking, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Search Range\0搜索范围\0搜索範圍\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x0, 0, (void *)0x00D7BF50, (void *)0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SEARCHRANGE,
		CA_SEARCHRANGE,
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
		1,
		L"Start\0起始\0開始\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163A740, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SEARCHRANGE,
		CA_SEARCHRANGE,
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
		2,
		L"Stop\0终止\0終止\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163A788, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SEARCHRANGE,
		CA_SEARCHRANGE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


//峰值搜索子条目
SOFT_SUB_ITEM subitemPeakSearch[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Search Peak\0搜索峰值\0搜索峰值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_PEAKSEA,
		CA_PEAKSEA,
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
		L"Search Left\0搜索左峰值\0搜索左峰值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_PEAKSEA,
		CA_PEAKSEA,
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
		2,
		L"Search Right\0搜索右峰值\0搜索右峰值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_PEAKSEA,
		CA_PEAKSEA,
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
		3,
		L"Peak Excursion\0峰值浏览\0峰值浏覽\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B5374, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_PEAKSEA,
		CA_PEAKSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		4,
		L"Peak Polarity\0峰值极性\0峰值極性\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000A0900, 0, (void *)szPPOLarity, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_PEAKSEA_PP,
		CA_PEAKSEA_PP,
		sizeof(wcsListTristate) / sizeof(LPCWSTR),
		wcsListTristate,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Search Multi Peak\0搜索多峰值\0搜索多峰值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MULPEAKSEA,
		CA_MULPEAKSEA,
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
		1,
		L"Multi Peak Excursion\0多峰值浏览\0多峰值浏覽\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B5374, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MULPEAKSEA,
		CA_MULPEAKSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		2,
		L"Multi Peak Polarity\0多峰值极性\0多峰值極性\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000A0900, 0, (void *)szMULTiPPOLarity, (void *)0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MULPEAKSEA_PP,
		CA_MULPEAKSEA_PP,
		sizeof(wcsListTristate) / sizeof(LPCWSTR),
		wcsListTristate,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//目标搜索子条目
SOFT_SUB_ITEM subitemTargetSearch[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Search Target\0目标搜索\0目標搜索\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TARGSEA,
		CA_TARGSEA,
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
		L"Search Left\0搜索左目标\0搜索左目標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TARGSEA,
		CA_TARGSEA,
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
		2,
		L"Search Right\0搜索右目标\0搜索右目標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TARGSEA,
		CA_TARGSEA,
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
		3,
		L"Target Value\0目标值\0目標值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B5374, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TARGSEA,
		CA_TARGSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		4,
		L"Target Transition\0目标转换\0目標轉換\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000A0900, 0, (void *)szTTRansition, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TARGSEA_TT,
		CA_TARGSEA_TT,
		sizeof(wcsListTristate) / sizeof(LPCWSTR),
		wcsListTristate,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Search Multi Target\0搜索多目标\0搜索多目標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MULTARGSEA,
		CA_MULTARGSEA,
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
		1,
		L"Multi Target Value\0多目标值\0多目標值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B5354, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MULTARGSEA,
		CA_MULTARGSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		2,
		L"Multi Target Transition\0多目标转换\0多目標轉換\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000A0900, 0, (void *)szMULTiTTRansition, (void *)0x06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MULTARGSEA_TT,
		CA_MULTARGSEA_TT,
		sizeof(wcsListTristate) / sizeof(LPCWSTR),
		wcsListTristate,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//带宽/凹峰子条目
SOFT_SUB_ITEM subitemBandwidthAndNotch[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		8,
		L"Bandwidth\0带宽\0帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x006A6900, 0, (void *)0x00D7C048, (void *)0x1C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
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
		L"Bandwidth Value\0带宽值\0帶寬值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B538C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		10,
		L"Notch\0凹峰\0凹峰\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00706F00, 0, (void *)0x00D7C004, (void *)0x1C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
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
		11,
		L"Notch Value\0凹峰值\0凹峰值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B53A4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERSEA,
		CA_MARKERSEA,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


//频标功能子条目
SOFT_SUB_ITEM subitemMarkerFunc[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Marker -> Start\0频标 -> 起始\0頻標 -> 開始\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
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
		L"Marker -> Stop\0频标 -> 终止\0頻標 -> 終止\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
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
		2,
		L"Marker -> Center\0频标 -> 中心频率\0頻標 -> 中心頻率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
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
		3,
		L"Marker -> Reference\0频标 -> 基准\0頻標 -> 基準\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
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
		4,
		L"Marker -> Delay\0频标 -> 延迟\0頻標 -> 延遲\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		5,
		L"Discrete\0离散频标方式\0離散頻標方式\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00201F00, 0, (void *)0x00D7B364, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		6,
		L"Couple\0耦合频标方式\0藕合頻標方式\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00242300, 0, (void *)0x00D7B2DC, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK|SIF_FN_SETFOCUS,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		7,
		L"Marker Table\0频标表格\0頻標表格\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00282700, 0, (void *)0x00D64C78, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		8,
		L"Statistics\0统计\0統計\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00424100, 0, (void *)0x00D64490, (void *)0xF8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MARKERFUNC,
		CA_MARKERFUNC,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		11,
		L"Marker Info\0频标信息\0頻標信息\0\0",
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
		SIF_ORIGCLICK | SIF_NOREPLY,
		0,
		SIS_InputButtonEx,
		0,
		L"X Pos\0X 位置\0X 位置\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163A250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MFAO,
		CA_MFAO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		0,
		SIS_InputButtonEx,
		1,
		L"Y Pos\0Y 位置\0Y 位置\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163A27C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MFAO,
		CA_MFAO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		2,
		L"Align\0对齐\0對齊\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D64CBC, (void *)0x77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MFAO,
		CA_MFAO,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		3,
		L"Active Only\0仅当前的\0僅當前的\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00050400, 0, (void *)0x00D64CEC, (void *)0x77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MFAO,
		CA_MFAO,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

static int WINAPI fnTagPageEnter_Marker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_MARKER);
	OrigSoftMenu_UpdateItems(CA_MARKER);
	return 0;
}

static int WINAPI fnTagPageLeave_Marker(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Leave(CA_MARKER);
	return 0;
}

static int WINAPI fnTagPageEnter_MarkerSearch(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_MARKERSEA);
	return 0;
}

static int WINAPI fnTagPageEnter_MarkerFunction(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_MARKERFUNC);
	OrigSoftMenu_UpdateItems(CA_MFAO);
	return 0;
}

static int WINAPI fnTagPageEnter_PeakSearch(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_MARKERSEA);
	OrigSoftMenu_UpdateItems(CA_PEAKSEA);
	OrigSoftMenu_UpdateItems(CA_MULPEAKSEA);
	return 0;
}

static int WINAPI fnTagPageEnter_TargetSearch(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_MARKERSEA);
	OrigSoftMenu_UpdateItems(CA_TARGSEA);
	OrigSoftMenu_UpdateItems(CA_MULTARGSEA);
	return 0;
}

//频标子菜单
SOFT_TAG_PAGE submenuMarker[] =
{
	{
		TPF_FN_ENTER | TPF_FN_LEAVE,
		0,
		L"Marker\0频标\0頻標\0\0",
		NULL,
		sizeof(subitemMarker) / sizeof(SOFT_SUB_ITEM),
		subitemMarker,
		RESERVE_DWORD4,
		&fnTagPageEnter_Marker,
		&fnTagPageLeave_Marker,
		0,
		{ L"::/Measurement/Data_Analysis/Analyzing_Data_on_the_Trace_Using_the_Marker.htm", (void*)1082, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Marker Search\0频标搜索\0頻標搜索\0\0",
		NULL,
		sizeof(subitemMarkerSearch) / sizeof(SOFT_SUB_ITEM),
		subitemMarkerSearch,
		RESERVE_DWORD4,
		&fnTagPageEnter_MarkerSearch,
		NULL,
		0,
		{ L"::/Measurement/Data_Analysis/Searching_for_Positions_that_Match_Specified_Criteria.htm", (void*)1083, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Search Peak\0峰值搜索\0峰值搜索\0\0",
		NULL,
		sizeof(subitemPeakSearch) / sizeof(SOFT_SUB_ITEM),
		subitemPeakSearch,
		RESERVE_DWORD4,
		&fnTagPageEnter_PeakSearch,
		NULL,
		0,
		{ L"::/Measurement/Data_Analysis/Searching_for_Positions_that_Match_Specified_Criteria.htm#Searching_for_the_peak", (void*)1083, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Search Target\0目标搜索\0目標搜索\0\0",
		NULL,
		sizeof(subitemTargetSearch) / sizeof(SOFT_SUB_ITEM),
		subitemTargetSearch,
		RESERVE_DWORD4,
		&fnTagPageEnter_TargetSearch,
		NULL,
		0,
		{ L"::/Measurement/Data_Analysis/Searching_for_Positions_that_Match_Specified_Criteria.htm#Searching_for_the_target_value__target_search_", (void*)1083, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Bandwidth / Notch\0带宽 / 凹峰\0帶寬 / 凹峰\0\0",
		NULL,
		sizeof(subitemBandwidthAndNotch) / sizeof(SOFT_SUB_ITEM),
		subitemBandwidthAndNotch,
		RESERVE_DWORD4,
		&fnTagPageEnter_MarkerSearch,
		NULL,
		0,
		{ L"::/Measurement/Data_Analysis/Determining_the_Bandwidth_of_the_Trace_Bandwidth_Search.htm", (void*)1084, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Marker Function\0频标功能\0頻標功能\0\0",
		NULL,
		sizeof(subitemMarkerFunc) / sizeof(SOFT_SUB_ITEM),
		subitemMarkerFunc,
		RESERVE_DWORD4,
		&fnTagPageEnter_MarkerFunction,
		NULL,
		0,
		{ L"::/Measurement/Data_Analysis/Analyzing_Data_on_the_Trace_Using_the_Marker.htm", (void*)1082, 0, 0 }
	}
};

//频标主菜单
SOFT_MENU menuMarker = {
	0,
	0,
	L"Marker\0频标\0頻標\0\0", NULL, sizeof(submenuMarker) / sizeof(SOFT_TAG_PAGE),
	submenuMarker,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4 };

