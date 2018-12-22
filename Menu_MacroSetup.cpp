#include "stdafx.h"

static int WINAPI fnUpdateData_SelectMacro(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

int WINAPI fnItemClicked_LoadProj(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
		TagPage_RefreshItems(TRUE);
	}

	return 0;
}


//系统子条目
static SOFT_SUB_ITEM subitemMacro[] =
{
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"VBA Editor\0VBA编辑器\0VBA編輯器\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"New Project\0新建目标文件\0新建目標文件\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_CLICKED | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
		L"Load Project\0载入目标文件\0載入目標文件\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_LoadProj, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		4,
		L"Save Project\0保存目标文件\0保存目標文件\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		5,
		L"Close Editor\0关闭编辑器\0關閉編輯器\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
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
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		0,
		L"Select Macro\0选择宏\0選擇宏\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, 0, &fnUpdateData_SelectMacro, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO_SM,
		CA_MACRO_SM,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		7,
		L"Stop\0终止\0終止\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		8,
		L"Continue\0继续\0繼續\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
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
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		9,
		L"Echo Window\0返回窗口\0返回窗口\0\0",
		NULL,
		BtnWidth_W,
		48,
		NULL,
		{ (void *)0x000C0B00, 0, (void *)0x00D64C78, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		10,
		L"Clear Echo\0清空返回窗口\0清空返回窗口\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_MACRO,
		CA_MACRO,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

static int WINAPI fnUpdateData_SelectMacro(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (lpSubItem && lpSubItem->lpOpt[4] && lpSubItem->lpParams)
	{
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], (LPCWSTR)lpSubItem->lpParams);
	}

	return 0;
}

static int WINAPI fnTagPageEnter_Macro(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_MACRO);
	OrigSoftMenu_UpdateItems(CA_MACRO);

	BOOL blTmp = FALSE;

	OrigSoftMenu_GetItemState(CA_MACRO, 6, &blTmp, NULL, NULL);

	if (blTmp & 0xFF)
	{
		OrigSoftMenu_UpdateItems(CA_MACRO_SM);

		int nMax = GetSubMenuItemCount(CA_MACRO_SM);

		NOT_FLAGS(subitemMacro[6].dwAttributes, SIAE_DISABLED);

		if (nMax > 0)
		{
			LPSTR lpText = GetSubMenuItemText(CA_MACRO_SM, 0);
			int nLen;
			WCHAR wcsText[MAX_PATH];

			wcsText[0] = 0;

			MultiByteToWideChar(CP_ACP, 0, lpText, -1, wcsText, MAX_PATH);
			nLen = wcslen(wcsText);

			subitemMacro[6].wHeight = 56;
			subitemMacro[6].lpParams = malloc((nLen + 4) * sizeof(WCHAR));

			if (subitemMacro[6].lpParams)
				swprintf_s((WCHAR *)subitemMacro[6].lpParams, nLen + 4, L"%s\0\0", wcsText);
		}
		else
		{
			subitemMacro[6].wHeight = 26;
			subitemMacro[6].lpParams = NULL;
		}
	}
	else
	{
		SET_FLAGS(subitemMacro[6].dwAttributes, SIAE_DISABLED);
		subitemMacro[6].wHeight = 26;
		subitemMacro[6].lpParams = NULL;
	}

	return 0;
}

static int WINAPI fnTagPageLeave_Macro(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	if (subitemMacro[6].lpParams) free((void *)subitemMacro[6].lpParams);

	return 0;
}

static int WINAPI fnTagPageEnter_LoadRun(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_MACRO);
	OrigSoftMenu_UpdateItems(CA_MACRO);

	OrigSoftMenu_UpdateItems(CA_MACRO_LR);

	int nMax = GetSubMenuItemCount(CA_MACRO_LR);
	char *lpszText;
	SOFT_SUB_ITEM SubItem;

	memset(&SubItem, 0, sizeof(SOFT_SUB_ITEM));

	SubItem.dwFlags = SIF_ORIGCLICK | SIF_NOT_ENTER;
	SubItem.dwAttributes = SIA_FULLLINE;
	SubItem.dwStyle = SIS_ButtonEx;
	SubItem.wMinWidth = 16;
	SubItem.wHeight = 28;
	SubItem._hWnd = NULL;
	SubItem.dwGroupIndex = INVALID_INDEX;
	SubItem.lpVTable = TA_MACRO_LR;
	SubItem.lpThis = CA_MACRO_LR;

	for (int nIndex = 0; nIndex < nMax; nIndex++)
	{
		SubItem.dwFunctionId = (DWORD)nIndex;
		SubItem.szItemText = (WCHAR *)malloc(sizeof(WCHAR) * MAX_PATH);
		SubItem.szItemText[0] = 0;
		lpszText = GetSubMenuItemText(CA_MACRO_LR, nIndex);

		if (SubItem.szItemText && lpszText)
		{
			MultiByteToWideChar(CP_ACP, 0, lpszText, -1, SubItem.szItemText, MAX_PATH);
		}

		TagPage_AddItem(lpTagPage, &SubItem);
	}

	return 0;
}

static int WINAPI fnTagPageLeave_FreeItem(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	TagPage_FreeItem(lpTagPage);
	return 0;
}

static int WINAPI fnTagPageEnter_UserMenu(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_MACRO);
	OrigSoftMenu_UpdateItems(CA_MACRO);

	OrigSoftMenu_UpdateItems(CA_MACRO_UM);

	int nMax = GetSubMenuItemCount(CA_MACRO_UM);
	char *lpszText;
	SOFT_SUB_ITEM SubItem;

	memset(&SubItem, 0, sizeof(SOFT_SUB_ITEM));

	SubItem.dwFlags = SIF_ORIGCLICK | SIF_NOT_ENTER;
	SubItem.dwAttributes = SIA_FULLLINE;
	SubItem.dwStyle = SIS_ButtonEx;
	SubItem.wMinWidth = 16;
	SubItem.wHeight = 28;
	SubItem._hWnd = NULL;
	SubItem.dwGroupIndex = INVALID_INDEX;
	SubItem.lpVTable = TA_MACRO_UM;
	SubItem.lpThis = CA_MACRO_UM;

	for (int nIndex = 0; nIndex < nMax; nIndex++)
	{
		SubItem.dwFunctionId = (DWORD)nIndex;
		SubItem.szItemText = (WCHAR *)malloc(sizeof(WCHAR) * MAX_PATH);
		SubItem.szItemText[0] = 0;
		lpszText = GetSubMenuItemText(CA_MACRO_UM, nIndex);

		if (SubItem.szItemText && lpszText)
		{
			MultiByteToWideChar(CP_ACP, 0, lpszText, -1, SubItem.szItemText, MAX_PATH);
		}

		TagPage_AddItem(lpTagPage, &SubItem);
	}

	SubItem.szItemText = NULL;

	SubItem.dwFlags = 0;
	SubItem.dwAttributes = SIA_FULLLINE;
	SubItem.dwStyle = SIS_Delimiter;
	SubItem.dwFunctionId = 0;
	SubItem.wMinWidth = 40;
	SubItem.wHeight = 20;
	SubItem.lpVTable = NULL;
	SubItem.lpThis = NULL;
	TagPage_AddItem(lpTagPage, &SubItem);

	SubItem.dwFlags = SIF_ORIGCLICK | SIF_NOT_ENTER;
	SubItem.dwAttributes = SIA_FULLLINE;
	SubItem.dwStyle = SIS_ButtonEx;
	SubItem.dwFunctionId = 12;
	SubItem.wMinWidth = 16;
	SubItem.wHeight = 28;
	SubItem.lpVTable = TA_MACRO;
	SubItem.lpThis = CA_MACRO;
	SubItem.lpszItemText = L"User Menu Preset\0用户菜单复位\0用戶菜單復位\0\0";
	TagPage_AddItem(lpTagPage, &SubItem);

	return 0;
}

//宏指令设置子菜单
SOFT_TAG_PAGE submenuMacroSetup[] =
{
	{
		TPF_FN_ENTER | TPF_FN_LEAVE,
		0,
		L"Macro\0宏\0宏\0\0",
		NULL,
		sizeof(subitemMacro) / sizeof(SOFT_SUB_ITEM),
		subitemMacro,
		RESERVE_DWORD4,
		&fnTagPageEnter_Macro,
		&fnTagPageLeave_Macro,
		0,
		{ L"::/Programming/VBA_Programming/Operation_Basics/Operation_Basics.htm", 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER | TPF_FN_LEAVE | TPF_DYNAMIC,
		0,
		L"Load && Run\0载入和运行\0載入和運行\0\0",
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		&fnTagPageEnter_LoadRun,
		&fnTagPageLeave_FreeItem,
		0,
		{L"::/Programming/VBA_Programming/Operation_Basics/Running_a_VBA_Program.htm",0,0,0}
	}
	,
	{
		TPF_FN_ENTER | TPF_FN_LEAVE | TPF_DYNAMIC,
		0,
		L"User Menu\0用户菜单\0用戶菜單\0\0",
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		&fnTagPageEnter_UserMenu,
		&fnTagPageLeave_FreeItem,
		0,
		{ L"::/Programming/VBA_Programming/VBA_Programming.htm", 0, 0, 0 }
	}
};

//宏指令设置主菜单
SOFT_MENU menuMacroSetup =
{
	0,
	0,
	L"Macro Setup\0宏指令设置\0宏指令設置\0\0",
	NULL,
	sizeof(submenuMacroSetup) / sizeof(SOFT_TAG_PAGE),
	submenuMacroSetup,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
