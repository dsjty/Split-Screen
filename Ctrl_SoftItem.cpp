#include "stdafx.h"
#include "htmlhelp.h"

#define WM_MYTIMER               (WM_USER + 2)

extern HFONT hFont_cfg1, hFont_cfg2;
#pragma comment (lib,"Htmlhelp.lib")

static const WCHAR wcsHelpPath[] = L"D:\\TianDa\\Help\\TD3618D_HELP.chm";

WORD wWidth_SoftItem = 0, wHeight_SoftItem = 0;
RECT rcItem, rcLastItem;
DWORD dwFocusItem = 0, dwLastFocus = INVALID_INDEX;
DWORD dwFocusFlags = 0;
SOFT_TAG_PAGE lpCurTagPage = { 0 };



//窗口hook相关函数

//************************************
// 函数名:    TagPage_ShowHelp
// Access:    public 
// 返回值类型:   void *
// 说明: 帮助文档链接,注意下面的lpCurTagPage->lpReserve[0]
//************************************
void * TagPage_ShowHelp(PSOFT_SUB_ITEM lpSubPage)
{
	//if (&lpCurTagPage && lpCurTagPage.lpReserve[0])
	//{
	//	WCHAR wcsTmp[1024];
	//	swprintf_s(wcsTmp, 1024, L"%s%s", wcsHelpPath, lpCurTagPage.lpReserve[0]);
	//	return ShellExecuteW(NULL, L"open", L"hh.exe", wcsTmp, NULL, SW_SHOW);
	//}
	//else if ((0 != lpSubPage && lpSubPage->dwReserve[1]) || (lpCurTagPage.lpszTagText && lpCurTagPage.lpReserve[1]))
	//{
	//	HWND hWnd = FindWindow(NULL, "TD3619");
	//	HtmlHelp(hWnd, "D:\\TianDa\\Help\\TD3619D_HELP.chm", HH_HELP_CONTEXT, lpSubPage->dwReserve[1]);
	//}
	return NULL;
}

int SoftItem_Finetune(PSOFT_SUB_ITEM lpSubItem, int nDelta, int nCount)
{
	if (lpSubItem == NULL || lpSubItem->lpOpt[1] == NULL) 
		return -1;

	double dblOutput;

	DWORD dwTemp = BASE + (DWORD)lpSubItem->lpOpt[1];

	fn_GetDouble fnGetDbl = GetAddr_GetDbl((void*)dwTemp);
	fn_SetDouble fnSetDbl = GetAddr_SetDbl((void*)dwTemp);
	BOOL blRet;
	char szText[MAX_PATH] = { 0 };
	WCHAR wcsText[MAX_PATH] = { 0 };

	if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOREPLY) && lpSubItem->lpThis && lpSubItem->lpVTable)
	{
		OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
	}

	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		blRet = InputFineTune(lpSubItem->lpOpt[1], &dblOutput, fnGetDbl((void*)dwTemp), nDelta);
	}

	if (blRet)
	{
		fnSetDbl((void*)dwTemp, dblOutput);
	}

	if (lpSubItem->lpOpt[4] == NULL) 
		return TRUE;

	FmtValueToStringEx(lpSubItem->lpOpt[1], szText, MAX_PATH, fnGetDbl((void*)dwTemp));
	MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);

	SetWindowTextW((HWND)lpSubItem->lpOpt[4], wcsText);
	SelectAllText((HWND)lpSubItem->lpOpt[4]);

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEITEM))
	{
		UpdateCurrentItems();
	}

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEDATA))
	{
		UpdateCurrentItemsAndData();
	}

	return 0;
}

int SoftItem_Finetune2(PSOFT_SUB_ITEM lpSubItem, int nDelta)
{
	if (lpSubItem == NULL || lpSubItem->lpOpt[1] == NULL) 
		return -1;

	DWORD dwTemp = BASE + (DWORD)lpSubItem->lpOpt[1];

	double dblOutput;
	fn_GetDouble fnGetDbl = GetAddr_GetDbl((void*)dwTemp);
	fn_SetDouble fnSetDbl = GetAddr_SetDbl((void*)dwTemp);
	char szText[MAX_PATH] = { 0 };
	WCHAR wcsText[MAX_PATH] = { 0 };

	if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOREPLY) && lpSubItem->lpThis && lpSubItem->lpVTable)
	{
		OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
	}

	if (InputFineTune2(lpSubItem->lpOpt[1], &dblOutput, fnGetDbl((void*)dwTemp), nDelta))
	{
		fnSetDbl((void*)dwTemp, dblOutput);

		if (lpSubItem->lpOpt[4] == NULL) 
			return 1;

		FmtValueToStringEx(lpSubItem->lpOpt[1], szText, MAX_PATH, fnGetDbl((void*)dwTemp));
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);

		SetWindowTextW((HWND)lpSubItem->lpOpt[4], wcsText);
		SelectAllText((HWND)lpSubItem->lpOpt[4]);

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEITEM))
		{
			UpdateCurrentItems();
		}

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEDATA))
		{
			UpdateCurrentItemsAndData();
		}
	}
	else
	{
		return -2;
	}

	return 0;
}
