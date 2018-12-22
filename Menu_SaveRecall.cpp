#include "stdafx.h"

const LPCWSTR wcsListSType[] =
{
	L"State Only\0仅状态\0僅狀態\0\0",
	L"State & Cal\0状态和校准数据\0狀態和校準數據\0\0",
	L"State & Trace\0状态和曲线\0狀態和曲線\0\0",
	L"All\0全部\0全部\0\0"
};

const LPCWSTR wcsListSType_[] =
{
	L"State Only\0仅状态\0僅狀態\0\0",
	L"State && Cal\0状态和校准数据\0狀態和校準數據\0\0",
	L"State && Trace\0状态和曲线\0狀態和曲線\0\0",
	L"All\0全部\0全部\0\0"
};

const LPCWSTR wcsListCT[] =
{
	L"Disp Only\0仅显示\0僅顯示\0\0",
	L"All\0全部\0全部\0\0"
};


int WINAPI fnUpdateData_CT(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	LPCWSTR *lppWStr = (LPCWSTR *)lpSubItem->lpParams;
	LPCWSTR lpText = NULL;

	if (lpSubItem->lpOpt[2] == NULL) 
		return -1;
	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}
	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);

	if ((*lppWStr) && ((DWORD)nIndex < lpSubItem->dwNumberOfParams))
	{
		lpText = GetStringByIndex(lppWStr[nIndex], nLangId);
	}
	else
		lpText = L"!ERROR!";

	if (lpSubItem->lpOpt[4])
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], lpText);

	return 0;
}

int WINAPI fnItemClicked_CT(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		fnUpdateData_CT(0, 0, 0, lpSubItem);
	}

	return 0;
}

int WINAPI fnUpdateData_File(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (lpSubItem->dwFunctionId < 10)
	{
		HANDLE hFile;
		char szPath[MAX_PATH];

		if (lpSubItem->szItemText == NULL)
		{
			lpSubItem->szItemText = (WCHAR *)malloc(MAX_PATH * sizeof(WCHAR));
			if (lpSubItem->szItemText == NULL) 
				return -1;
		}

		switch (lpSubItem->dwFunctionId)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			sprintf_s(szPath, MAX_PATH, "D:\\STATE%02d.STA", lpSubItem->dwFunctionId + 1);
			break;

		case 8:
			strcpy_s(szPath, MAX_PATH, "D:\\AUTOREC.STA");
			break;

		case 9:
			strcpy_s(szPath, MAX_PATH, "D:\\USERPRES.STA");
			break;
		}

		hFile = CreateFileA(szPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			wcscpy_s(lpSubItem->szItemText, MAX_PATH, GetStringByIndex(lpSubItem->lpszItemText, nLangId));
		}
		else
		{
			CloseHandle(hFile);

			swprintf_s(lpSubItem->szItemText, MAX_PATH, L"%s*", GetStringByIndex(lpSubItem->lpszItemText, nLangId));
		}

		SetWindowTextW(lpSubItem->_hWnd, lpSubItem->szItemText);
		InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		UpdateWindow(lpSubItem->_hWnd);
	}

	return 0;
}

int WINAPI fnItemClicked_File(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{

	if ((wParam == IC_CLICKED_LAST))
	{
		fnUpdateData_File(0, 0, 0, lpSubItem);
	}

	return 0;
}

static int WINAPI fnUpdateData_SC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	typedef int(__cdecl *func_007666D0)(DWORD dwIndex);
	typedef int(__cdecl *func_007666E0)(DWORD dwIndex);

	if (lpSubItem->dwFunctionId < 8)
	{
		BOOL blTest = FALSE;
		int nType = 0;

		if (lpSubItem->szItemText == NULL)
		{
			lpSubItem->szItemText = (WCHAR *)malloc(MAX_PATH * sizeof(WCHAR));
			if (lpSubItem->szItemText == NULL) 
				return -1;
		}

		switch (lpSubItem->dwFunctionId)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			func_007666D0 fn009360B0 = (func_007666D0)0x009360B0;
			if (fn009360B0(lpSubItem->dwFunctionId))
				blTest = TRUE;

			GetButtonStateIndex((const char *)0x00D64508, (void *)0x01, &nType, 0x00020100);

			if (nType < 0 || nType >= 4) 
				nType = 0;
		}
		break;

		case 4:
		case 5:
		case 6:
		case 7:
		{
			func_007666E0 fn009360D0 = (func_007666E0)0x009360D0;
			if (fn009360D0(lpSubItem->dwFunctionId - 4))
				blTest = TRUE;
		}
		break;
		}

		if (blTest)
		{
			if (lpSubItem->dwFunctionId < 4)
			{
				swprintf_s(lpSubItem->szItemText, MAX_PATH, L"%s %c*", GetStringByIndex(wcsListSType_[nType], nLangId), lpSubItem->dwFunctionId + 0x41);
			}
			else
			{
				swprintf_s(lpSubItem->szItemText, MAX_PATH, L"%s*", GetStringByIndex(lpSubItem->lpszItemText, nLangId));
			}
		}
		else
		{
			if (lpSubItem->dwFunctionId < 4)
			{
				swprintf_s(lpSubItem->szItemText, MAX_PATH, L"%s %c", GetStringByIndex(wcsListSType_[nType], nLangId), lpSubItem->dwFunctionId + 0x41);
			}
			else
			{
				wcscpy_s(lpSubItem->szItemText, MAX_PATH, GetStringByIndex(lpSubItem->lpszItemText, nLangId));
			}
		}

		SetWindowTextW(lpSubItem->_hWnd, lpSubItem->szItemText);
		InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		UpdateWindow(lpSubItem->_hWnd);
	}

	return 0;
}

static int WINAPI fnUpdateData_RC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	typedef int(__cdecl *func_007666D0)(DWORD dwIndex);

	if (lpSubItem->dwFunctionId < 4)
	{
		BOOL blTest = FALSE;
		DWORD nIndex = lpSubItem->dwFunctionId;

		if (lpSubItem->szItemText == NULL)
		{
			lpSubItem->szItemText = (WCHAR *)malloc(MAX_PATH * sizeof(WCHAR));
			if (lpSubItem->szItemText == NULL)
				return -1;
		}

		func_007666D0 fn009360B0 = (func_007666D0)0x009360B0;
		if (fn009360B0(nIndex))
			blTest = TRUE;

		if (blTest)
		{
			int nType = *(int *)((nIndex << 6) + 0x00BBFDE4);

			if ((nType >= 0) && (nType < 4))
			{
				swprintf_s(lpSubItem->szItemText, MAX_PATH, L"%s %c", GetStringByIndex(wcsListSType_[nType], nLangId), nIndex + 0x41);
			}
			else
			{
				wcscpy_s(lpSubItem->szItemText, MAX_PATH, GetStringByIndex(lpSubItem->lpszItemText, nLangId));
			}
		}
		else
		{
			wcscpy_s(lpSubItem->szItemText, MAX_PATH, GetStringByIndex(lpSubItem->lpszItemText, nLangId));
		}

		SetWindowTextW(lpSubItem->_hWnd, lpSubItem->szItemText);
		InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		UpdateWindow(lpSubItem->_hWnd);
	}

	return 0;
}

static int WINAPI fnItemClicked_SC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{

	if ((wParam == IC_CLICKED_LAST))
	{
		fnUpdateData_SC(0, 0, 0, lpSubItem);
	}

	return 0;
}


//存储子条目
static SOFT_SUB_ITEM subitemSaveState[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"State01\0状态01\0狀態01\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"State02\0状态02\0狀態02\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
		L"State03\0状态03\0狀態03\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		3,
		L"State04\0状态04\0狀態04\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		4,
		L"State05\0状态05\0狀態05\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		5,
		L"State06\0状态06\0狀態06\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		6,
		L"State07\0状态07\0狀態07\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		7,
		L"State08\0状态08\0狀態08\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
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
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		8,
		L"Autorec\0自动记录\0自動記錄\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		9,
		L"UserPres\0用户复位\0用戶復位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_File, 0, &fnUpdateData_File, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
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
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		10,
		L"File Dialog\0文件目录\0文件目錄\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SS,
		CA_SR_SS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
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
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		0,
		L"Save Type\0存储类型\0存儲類型\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D65408, (void *)0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_ST,
		CA_SR_ST,
		sizeof(wcsListSType) / sizeof(LPCWSTR),
		wcsListSType,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		6,
		L"Channel/Trace\0通道/曲线\0通道/曲線\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00030400, 0, (void *)0x00D653C8, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_CT, 0, &fnUpdateData_CT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR,
		CA_SR,
		sizeof(wcsListCT) / sizeof(LPCWSTR),
		wcsListCT,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
		,
		{
			SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
			SIA_FULLLINE | SIA_GETBTNSTATE ,
			SIS_CheckButtonEx,
			7,
			L"Auto Trig Source\0Auto Trig Source\0Auto Trig Source\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00040500, 0, (void *)0xD652CC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			INVALID_INDEX,
			NULL,
			NULL,
			TA_SR,
			CA_SR,
			NULL,
			NULL,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		8,
		L"Save Trace Data\0保存曲线数据\0保存曲線數據\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR,
		CA_SR,
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
		10,
		L"Explorer\0资源管理器\0資源管理器\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR,
		CA_SR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


//恢复子条目
static SOFT_SUB_ITEM subitemRecallState[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"State01\0状态01\0狀態01\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		L"State02\0状态02\0狀態02\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		L"State03\0状态03\0狀態03\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		L"State04\0状态04\0狀態04\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		L"State05\0状态05\0狀態05\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		5,
		L"State06\0状态06\0狀態06\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		6,
		L"State07\0状态07\0狀態07\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		L"State08\0状态08\0狀態08\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
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
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		8,
		L"Autorec\0自动记录\0自動記錄\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
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
		9,
		L"UserPres\0用户复位\0用戶復位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
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
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		10,
		L"File Dialog\0文件目录\0文件目錄\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RS,
		CA_SR_RS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
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
		0,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
		L"Recall by File Name\0通过文件名恢复\0通過文件名恢復\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR,
		CA_SR,
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
		8,
		L"Explorer\0资源管理器\0資源管理器\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR,
		CA_SR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//存储通道
static SOFT_SUB_ITEM subitemSaveChannel[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"State A\0状态A\0狀態A\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SC,
		CA_SR_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"State B\0状态B\0狀態B\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SC,
		CA_SR_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
		L"State C\0状态C\0狀態C\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SC,
		CA_SR_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		3,
		L"State D\0状态D\0狀態D\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SC,
		CA_SR_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEDATA,
		SIS_ButtonEx,
		0,
		L"Clear States\0清除状态\0清除狀態\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_SC_CS,
		CA_SR_SC_CS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//恢复通道
static SOFT_SUB_ITEM subitemRecallChannel[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"State A\0状态A\0狀態A\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RC,
		CA_SR_RC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"State B\0状态B\0狀態B\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RC,
		CA_SR_RC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
		L"State C\0状态C\0狀態C\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RC,
		CA_SR_RC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ButtonEx,
		3,
		L"State D\0状态D\0狀態D\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SR_RC,
		CA_SR_RC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//SS==save state
static int WINAPI fnTagPageEnter_SS(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_SR);
	OrigSoftMenu_UpdateItems(CA_SR);

	OrigSoftMenu_Enter(CA_SR_SS);
	OrigSoftMenu_UpdateItems(CA_SR_SS);
	return 0;
}

//RS==recall state
static int WINAPI fnTagPageEnter_RS(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_SR);
	OrigSoftMenu_UpdateItems(CA_SR);

	OrigSoftMenu_Enter(CA_SR_RS);
	OrigSoftMenu_UpdateItems(CA_SR_RS);
	return 0;
}

//SC==save channel
static int WINAPI fnTagPageEnter_SC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_SR);
	OrigSoftMenu_UpdateItems(CA_SR);

	OrigSoftMenu_Enter(CA_SR_SC);
	OrigSoftMenu_UpdateItems(CA_SR_SC);
	return 0;
}

//RC==Recall channel
static int WINAPI fnTagPageEnter_RC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_SR);
	OrigSoftMenu_UpdateItems(CA_SR);

	OrigSoftMenu_Enter(CA_SR_RC);
	OrigSoftMenu_UpdateItems(CA_SR_RC);
	return 0;
}


//系统子菜单
SOFT_TAG_PAGE submenuSave[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"Save State\0存储状态\0存儲狀態\0\0",
		NULL,
		sizeof(subitemSaveState) / sizeof(SOFT_SUB_ITEM),
		subitemSaveState,
		RESERVE_DWORD4,
		&fnTagPageEnter_SS,
		NULL,
		0,
		{ L"::/Measurement/Data_Output/Saving_and_Recalling_Instrument_State.htm#Saving_Data", (void*)1096, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Recall State\0调用状态\0調用狀態\0\0",
		NULL,
		sizeof(subitemRecallState) / sizeof(SOFT_SUB_ITEM),
		subitemRecallState,
		RESERVE_DWORD4,
		&fnTagPageEnter_RS,
		NULL,
		0,
		{ L"::/Measurement/Data_Output/Saving_and_Recalling_Instrument_State.htm#Recall_Procedure", (void*)1096, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Save Channel\0存储通道\0存儲通道\0\0",
		NULL,
		sizeof(subitemSaveChannel) / sizeof(SOFT_SUB_ITEM),
		subitemSaveChannel,
		RESERVE_DWORD4,
		&fnTagPageEnter_SC,
		NULL,
		0,
		{ L"::/Measurement/Data_Output/Saving_Recalling_Instrument_State_for_Each_Channel_into_from.htm#Saving Instrument State for Each Channel", (void*)1097, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Recall Channel\0调用通道\0調用通道\0\0",
		NULL,
		sizeof(subitemRecallChannel) / sizeof(SOFT_SUB_ITEM),
		subitemRecallChannel,
		RESERVE_DWORD4,
		&fnTagPageEnter_RC,
		NULL,
		0,
		{ L"::/Measurement/Data_Output/Saving_Recalling_Instrument_State_for_Each_Channel_into_from.htm#Recalling_Instrument_State_for_Each_Channel", (void*)1097, 0, 0 }
	}
};

//存储主菜单
SOFT_MENU menuSaveRecall =
{
	0,
	0,
	L"Save/Recall\0存储/调用\0存儲/調用\0\0",
	NULL,
	sizeof(submenuSave) / sizeof(SOFT_TAG_PAGE),
	submenuSave,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
