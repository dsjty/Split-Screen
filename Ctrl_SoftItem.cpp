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
	if (&lpCurTagPage && lpCurTagPage.lpReserve[0])
	{
		WCHAR wcsTmp[1024];
		swprintf_s(wcsTmp, 1024, L"%s%s", wcsHelpPath, lpCurTagPage.lpReserve[0]);
		return ShellExecuteW(NULL, L"open", L"hh.exe", wcsTmp, NULL, SW_SHOW);
	}
	else if ((0 != lpSubPage && lpSubPage->dwReserve[1]) || (lpCurTagPage.lpszTagText && lpCurTagPage.lpReserve[1]))
	{
		HWND hWnd = FindWindow(NULL, "TD3619");
		HtmlHelp(hWnd, "D:\\TianDa\\Help\\TD3618D_HELP.chm", HH_HELP_CONTEXT, lpSubPage->dwReserve[1]);
	}
	return NULL;
}

//TagPage RefreshItems 刷新控件
int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage, BOOL blReload)
{
	if (lpTagPage == NULL)
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	TagPage_DestroyItems(TRUE);

	if (lpCurTagPage.dwNumOfSubItems == 0)
	{
		memcpy(&lpCurTagPage, lpTagPage, sizeof(SOFT_TAG_PAGE));
	}

	lpTagPage = &lpCurTagPage;

	rcItem.left = 2;
	rcItem.top = 2;
	rcItem.right = wWidth_SoftItem - 2;
	rcItem.bottom = rcItem.top;

	rcLastItem.left = 0;
	rcLastItem.top = 0;
	rcLastItem.right = 0;
	rcLastItem.bottom = 0;

	lngHalf = (rcItem.right - rcItem.left - 2) / 2;

	for (DWORD i = 0; i < lpTagPage->dwNumOfSubItems; i++)
	{
#define Me          lpTagPage->lpSubItem[i]
		lngLeft = rcItem.left;
		lngWidth = wWidth_SoftItem - 4;

		//一行2个
		if (CHK_NOFLAGS(Me.dwAttributes, SIA_FULLLINE) && (Me.wMinWidth <= lngHalf))
		{
			if (blTail)
			{
				lngLeft = rcItem.left + lngHalf + 2;
				lngWidth = lngHalf;
				blTail = FALSE;
			}
			else
			{
				lngWidth = lngHalf;
				blTail = TRUE;
			}
		}
		else
		{
			blTail = FALSE;
		}

		switch (Me.dwStyle)
		{
		case SIS_ButtonEx:
			//普通按钮
		{
			SubCtrl_Button_Create(hwSoftItem, 0, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

			if (Me._hWnd)
			{
				SNDMSG(Me._hWnd, WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);

				SetWindowLongA(Me._hWnd, GWL_ID, (LONG)i + 1000);
				SetWindowLongA(Me._hWnd, GWL_USERDATA, (LONG)&Me);

				if (CHK_FLAGS(Me.dwAttributes, SIA_EXLBL) && (Me.lpOpt[4]))
				{
					SNDMSG((HWND)Me.lpOpt[4], WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);
				}
			}
		}
		break;

		case SIS_RadioButtonEx:
			//单选按钮
		{
			SubCtrl_RadioButton_Create(hwSoftItem, 0, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

			if (Me._hWnd)
			{
				SNDMSG(Me._hWnd, WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);

				SetWindowLongA(Me._hWnd, GWL_ID, (LONG)i + 1000);
				SetWindowLongA(Me._hWnd, GWL_USERDATA, (LONG)&Me);
			}
		}
		break;

		case SIS_CheckButtonEx:
			//复选框
		{
			SubCtrl_CheckButton_Create(hwSoftItem, 0, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

			if (Me._hWnd)
			{
				SNDMSG(Me._hWnd, WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);

				SetWindowLongA(Me._hWnd, GWL_ID, (LONG)i + 1000);
				SetWindowLongA(Me._hWnd, GWL_USERDATA, (LONG)&Me);
			}
		}
		break;

		case SIS_InputButtonEx:
			//输入框
		{
			SubCtrl_InputButton_Create(hwSoftItem, 0, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

			if (Me._hWnd)
			{
				SNDMSG(Me._hWnd, WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);

				SetWindowLongA(Me._hWnd, GWL_ID, (LONG)i + 1000);
				SetWindowLongA(Me._hWnd, GWL_USERDATA, (LONG)&Me);

				if (Me.lpOpt[4])
				{
					SNDMSG((HWND)Me.lpOpt[4], WM_SETFONT, (WPARAM)GetStockObject(SYSTEM_FIXED_FONT), TRUE);
				}
			}
		}
		break;

		case SIS_ComboButtonEx:
		case SIS_ComboRadioButtonEx:
			//下拉列表
		{
			SubCtrl_ComboButton_Create(hwSoftItem, 0, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

			if (Me._hWnd)
			{
				SNDMSG(Me._hWnd, WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);

				SetWindowLongA(Me._hWnd, GWL_ID, (LONG)i + 1000);
				SetWindowLongA(Me._hWnd, GWL_USERDATA, (LONG)&Me);

				if ((Me.dwStyle == SIS_ComboButtonEx || Me.dwStyle == SIS_ComboRadioButtonEx) && (Me.lpOpt[4]))
				{
					SNDMSG((HWND)Me.lpOpt[4], WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);
				}
			}
		}
		break;

		case SIS_Delimiter:
			//分隔符
		{
			if (Me.wHeight < 20)
				Me.wHeight = 12;


			LPCWSTR lpLblTitle = GetSoftItemTextByIndex(&Me, nLangId);
			DWORD dwExStyle = 0;

			if (lpLblTitle == NULL)
			{
				dwExStyle = WS_EX_STATICEDGE;
				lpLblTitle = L"————";
			}

			Me._hWnd = CreateWindowExW(dwExStyle, WC_STATICW, lpLblTitle,
				WS_CHILD | WS_VISIBLE | SS_CENTER, lngLeft, rcItem.bottom, lngWidth, Me.wHeight, hwSoftItem, NULL, hMod, NULL);

			if (Me._hWnd)
			{
				SNDMSG(Me._hWnd, WM_SETFONT, (WPARAM)hFont_cfg1, TRUE);

				SetWindowLongA(Me._hWnd, GWL_ID, (LONG)i + 1000);
				SetWindowLongA(Me._hWnd, GWL_USERDATA, (LONG)&Me);
				InvalidateRect(Me._hWnd, NULL, TRUE);
			}
		}
		break;
		}

		if (Me._hWnd)
		{
			if (Me.dwStyle != SIS_Delimiter)
				SetWndProc_Button((WNDPROC)SetWindowLong(Me._hWnd, GWL_WNDPROC, (LONG)&wp_Button), FALSE);

			GetWindowRect(Me._hWnd, &(Me.rect));

			if (CHK_FLAGS(Me.dwAttributes, SIAE_DISABLED))
				EnableWindow(Me._hWnd, FALSE);
		}

		if (blTail == FALSE)
			rcItem.bottom += Me.wHeight + 2;
		else if (i < lpTagPage->dwNumOfSubItems)
		{
			if ((lpTagPage->lpSubItem[i + 1].wMinWidth > lngHalf) || CHK_FLAGS(lpTagPage->lpSubItem[i + 1].dwAttributes, SIA_FULLLINE))
			{
				rcItem.bottom += Me.wHeight + 2;
				blTail = FALSE;
			}
		}

#undef Me 
	}

	UpdateDataByTagPage(lpTagPage);
	RedrawWindow(hwSoftItem, NULL, NULL, RDW_ERASE | RDW_ALLCHILDREN);
	return 0;
}

int TagPage_RefreshItems(BOOL blReload)
{
	int nRet = TagPage_RefreshItems(&lpCurTagPage, blReload);
	SoftItem_SetFocus(dwFocusItem, dwFocusFlags);
	return nRet;
}

int TagPage_UpdateItemsPos(DWORD dwFlags)
{
	PSOFT_TAG_PAGE lpTagPage = &lpCurTagPage;

	if (lpTagPage == NULL)
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	memcpy(&lpCurTagPage, lpTagPage, sizeof(lpCurTagPage));

	rcItem.left = 2;
	rcItem.top = 2;
	rcItem.right = wWidth_SoftItem - 2;
	rcItem.bottom = rcItem.top;

	rcLastItem.left = 0;
	rcLastItem.top = 0;
	rcLastItem.right = 0;
	rcLastItem.bottom = 0;

	lngHalf = (rcItem.right - rcItem.left - 2) / 2;

	for (DWORD i = 0; i < lpTagPage->dwNumOfSubItems; i++)
	{
#define Me lpTagPage->lpSubItem[i]
		if (Me._hWnd == NULL)
			continue;

		lngLeft = rcItem.left;
		lngWidth = wWidth_SoftItem - 4;

		//一行2个
		if (CHK_NOFLAGS(Me.dwAttributes, SIA_FULLLINE) && (Me.wMinWidth <= lngHalf))
		{
			if (blTail)
			{
				lngLeft = rcItem.left + lngHalf + 2;
				lngWidth = lngHalf;
				blTail = FALSE;
			}
			else
			{
				lngWidth = lngHalf;
				blTail = TRUE;
			}
		}
		else
		{
			blTail = FALSE;
		}

		MoveWindow(Me._hWnd, lngLeft, rcItem.bottom, lngWidth, Me.wHeight, TRUE);

		switch (Me.dwStyle)
		{
		case SIS_ButtonEx:
			//普通按钮
		{
			SubCtrl_Button_UpdatePos(&Me, 0);
		}
		break;

		case SIS_RadioButtonEx:
			//单选按钮
		{
			SubCtrl_RadioButton_UpdatePos(&Me, 0);
		}
		break;

		case SIS_CheckButtonEx:
			//复选框
		{
			SubCtrl_CheckButton_UpdatePos(&Me, 0);
		}
		break;

		case SIS_InputButtonEx:
			//输入框
		{
			SubCtrl_InputButton_UpdatePos(&Me, 0);
		}
		break;

		case SIS_ComboButtonEx:
		case SIS_ComboRadioButtonEx:			//下拉列表
		{
			SubCtrl_ComboButton_UpdatePos(&Me, 0);
		}
		break;

		}

		if (Me._hWnd)
		{
			GetWindowRect(Me._hWnd, &(Me.rect));

			if (CHK_FLAGS(Me.dwAttributes, SIAE_DISABLED))
				EnableWindow(Me._hWnd, FALSE);
		}

		if (blTail == FALSE)
			rcItem.bottom += Me.wHeight + 2;
		else if (i < lpTagPage->dwNumOfSubItems)
		{
			if ((lpTagPage->lpSubItem[i + 1].wMinWidth > lngHalf) || CHK_FLAGS(lpTagPage->lpSubItem[i + 1].dwAttributes, SIA_FULLLINE))
			{
				rcItem.bottom += Me.wHeight + 2;
				blTail = FALSE;
			}
		}

#undef Me 
	}

	return 0;
}

//设置激活项目的index
void SoftItem_SetActiveSoftItem(DWORD dwIndex)
{
	PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();

	if (lpTagPage && (dwIndex < lpTagPage->dwNumOfSubItems))
	{
		lpTagPage->dwActiveIndex = (dwIndex == INVALID_INDEX) ? 0 : dwIndex;
	}
}

void SoftItem_ActivationItem(PSOFT_SUB_ITEM lpSubItem)
{
	if (lpSubItem == NULL) 
		return;

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_GROUP))  //该子条目是一个组的头部
	{
		if (lpSubItem->dwActiveOffset == 0)
			return;

		if (lpSubItem->dwStyle == SIS_RadioButtonEx || lpSubItem->dwStyle == SIS_ComboRadioButtonEx)
		{
			DWORD dwIndex = GetCurrentSoftItemIndex(lpSubItem);

			if (dwIndex != INVALID_INDEX)
			{
				SoftItem_SetActiveSoftItem(dwIndex);
				PSOFT_SUB_ITEM lpSubItem2 = GetSoftItemByIndex(dwIndex + lpSubItem->dwActiveOffset);

				if (lpSubItem2 && ((lpSubItem2->dwStyle == SIS_RadioButtonEx) || (lpSubItem2->dwStyle == SIS_ComboRadioButtonEx)))
				{
					NOT_FLAGS(lpSubItem2->dwAttributes, SIAE_CHECKED);
					lpSubItem->dwActiveOffset = 0;

					InvalidateRect(lpSubItem2->_hWnd, NULL, TRUE);
					UpdateWindow(lpSubItem2->_hWnd);

					InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
					UpdateWindow(lpSubItem->_hWnd);

					return;
				}
			}
		}

		lpSubItem->dwActiveOffset = 0;
		InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		UpdateWindow(lpSubItem->_hWnd);
		return;
	}
	else
	{
		PSOFT_SUB_ITEM lpHeaderItem = GetGroupHeader(SoftItem_GetCurrentTagPage(), lpSubItem);

		if (lpHeaderItem)
		{
			DWORD dwHeaderIndex = GetCurrentSoftItemIndex(lpHeaderItem);
			DWORD dwIndex = GetCurrentSoftItemIndex(lpSubItem);

			if (dwIndex != INVALID_INDEX)
			{
				SoftItem_SetActiveSoftItem(dwIndex);

				if (dwHeaderIndex != INVALID_INDEX)
				{
					if (dwHeaderIndex + lpHeaderItem->dwActiveOffset == dwIndex)
						return;
				}
			}

			if (lpSubItem->dwStyle == SIS_RadioButtonEx || lpSubItem->dwStyle == SIS_ComboRadioButtonEx)
			{
				DWORD dwIndex = GetCurrentSoftItemIndex(lpHeaderItem);

				if (dwIndex != INVALID_INDEX)
				{
					PSOFT_SUB_ITEM lpSubItem2 = GetSoftItemByIndex(dwIndex + lpHeaderItem->dwActiveOffset);

					if (lpSubItem2 && ((lpSubItem2->dwStyle == SIS_RadioButtonEx) || (lpSubItem2->dwStyle == SIS_ComboRadioButtonEx)))
					{
						NOT_FLAGS(lpSubItem2->dwAttributes, SIAE_CHECKED);
						lpHeaderItem->dwActiveOffset = GetGroupOffsetIndex(SoftItem_GetCurrentTagPage(), lpSubItem);

						InvalidateRect(lpSubItem2->_hWnd, NULL, TRUE);
						UpdateWindow(lpSubItem2->_hWnd);

						InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
						UpdateWindow(lpSubItem->_hWnd);

						return;
					}
				}
			}

			lpHeaderItem->dwActiveOffset = GetGroupOffsetIndex(SoftItem_GetCurrentTagPage(), lpSubItem);
			InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
			UpdateWindow(lpSubItem->_hWnd);
			return;
		}

		InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		UpdateWindow(lpSubItem->_hWnd);
	}
}

void SoftItem_ActivationItemByOffsetIndex(PSOFT_SUB_ITEM lpSubItem, int nOffsetIndex)
{
	if (lpSubItem == NULL) 
		return;

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_GROUP))  //该子条目是一个组的头部
	{
		DWORD dwIndex = GetCurrentSoftItemIndex(lpSubItem);

		if (dwIndex == INVALID_INDEX)
			return;

		PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();

		if (dwIndex + nOffsetIndex >= lpTagPage->dwNumOfSubItems)
			return;

		PSOFT_SUB_ITEM lpDestItem = GetSoftItemByIndex(dwIndex + nOffsetIndex);

		SoftItem_ActivationItem(lpDestItem);
	}
	else
	{
		PSOFT_SUB_ITEM lpHeaderItem = GetGroupHeader(SoftItem_GetCurrentTagPage(), lpSubItem);

		if (lpHeaderItem)
		{
			DWORD dwIndex = GetCurrentSoftItemIndex(lpHeaderItem);

			if (dwIndex == INVALID_INDEX) 
				return;

			PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();

			if (dwIndex + nOffsetIndex >= lpTagPage->dwNumOfSubItems)
				return;

			PSOFT_SUB_ITEM lpDestItem = GetSoftItemByIndex(dwIndex + nOffsetIndex);

			SoftItem_ActivationItem(lpDestItem);
		}
	}

	return;
}

inline PSOFT_TAG_PAGE SoftItem_GetCurrentTagPage()
{
	return &lpCurTagPage;
}


int SoftItem_InvalidLastFocus()
{
	PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();

	if (lpTagPage == NULL)
		return -1;
	if (dwLastFocus >= lpTagPage->dwNumOfSubItems)
		return -2;

	if (lpTagPage->lpSubItem[dwLastFocus]._hWnd)
	{
		InvalidateRect(lpTagPage->lpSubItem[dwLastFocus]._hWnd, NULL, TRUE);
		UpdateWindow(lpTagPage->lpSubItem[dwLastFocus]._hWnd);
	}

	return 0;
}

int SoftItem_SetFocusValue(DWORD dwNewFocus, DWORD dwNewFlags)
{
	PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();

	if (lpTagPage == NULL)
		return -1;
	if (dwNewFocus >= lpTagPage->dwNumOfSubItems)
		return -2;

	dwLastFocus = dwFocusItem;
	dwFocusItem = dwNewFocus;
	dwFocusFlags = dwNewFlags;

	return 0;
}

PSOFT_SUB_ITEM SoftItem_GetFocusItem()
{
	return GetSoftItemByIndex(dwFocusItem);
}

PSOFT_SUB_ITEM SoftItem_GetLastFocusItem()
{
	return GetSoftItemByIndex(dwLastFocus);
}

int SoftItem_ScrollFocus()
{
	PSOFT_SUB_ITEM lpFocusItem = SoftItem_GetFocusItem();
	RECT rcFocus, rcClient;
	LONG lngDiff;

	if (lpFocusItem == NULL || lpFocusItem->_hWnd == NULL)
		return -1;

	GetClientRect(lpFocusItem->_hWnd, &rcFocus);
	GetClientRect(hwSoftItem, &rcClient);

	ClientToScreen(lpFocusItem->_hWnd, &rcFocus);
	ClientToScreen(hwSoftItem, &rcClient);

	if (rcFocus.top < rcClient.top + 2)
	{
		lngDiff = (rcClient.top + 2) - rcFocus.top;

		ScrollWindowEx(hwSoftItem, 0, lngDiff, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
		UpdateWindow(hwSoftItem);
	}
	else if (rcFocus.bottom > rcClient.bottom - 2)
	{
		lngDiff = (rcClient.bottom - 2) - rcFocus.bottom;

		ScrollWindowEx(hwSoftItem, 0, lngDiff, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
		UpdateWindow(hwSoftItem);
	}

	return 0;
}

/*
SoftItem :: SetFocus
设置软菜单条目的焦点

DWORD dwNewFocus:
新焦点在当前标签页的index (lpTagPage->lpSubItem的第几个元素)

DWORD dwNewFlags:
设置焦点的标志:
0x01:   设置到条目的子控件上

*/
int SoftItem_SetFocus(DWORD dwNewFocus, DWORD dwNewFlags)
{
	PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();
	PSOFT_SUB_ITEM lpSubItem = NULL;

	if (lpTagPage == NULL)
		return -8;
	if (dwNewFocus >= lpTagPage->dwNumOfSubItems)
		return -9;

	while (dwNewFocus < lpTagPage->dwNumOfSubItems)
	{
		lpSubItem = GetSoftItemByIndex(dwNewFocus);

		if (lpSubItem == NULL)
			continue;

		if ((lpSubItem->_hWnd != NULL) && (IsWindowEnabled(lpSubItem->_hWnd) != FALSE) && (lpSubItem->dwStyle != SIS_Delimiter))
		{
			if (CHK_FLAGS(dwNewFlags, 0x01) && (lpSubItem->lpOpt[4]))
				SetFocus((HWND)lpSubItem->lpOpt[4]);
			else if (lpSubItem->_hWnd)
				SetFocus(lpSubItem->_hWnd);
			else
				return -9;

			SoftItem_ScrollFocus();

			return 0;
		}

		dwNewFocus++;
	}

	return -10;
}

/*
SoftItem :: PrevItem
设置焦点到当前焦点的前一个控件上
*/
int SoftItem_PrevItem()
{
	PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();
	PSOFT_SUB_ITEM lpSubItem = NULL;
	DWORD dwNewFocus = dwFocusItem - 1;

	if (lpTagPage == NULL) 
		return -1;

	while (dwNewFocus < lpTagPage->dwNumOfSubItems)
	{
		lpSubItem = GetSoftItemByIndex(dwNewFocus);

		if (lpSubItem == NULL) 
			continue;

		if ((lpSubItem->_hWnd != NULL) && (IsWindowEnabled(lpSubItem->_hWnd) != FALSE) && (lpSubItem->dwStyle != SIS_Delimiter))
		{
			return SoftItem_SetFocus(dwNewFocus, 0);
		}

		dwNewFocus--;
	}

	return -2;
}

/*
SoftItem :: NextItem
设置焦点到当前焦点的后一个控件上
*/
int SoftItem_NextItem()
{
	PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();
	PSOFT_SUB_ITEM lpSubItem = NULL;
	DWORD dwNewFocus = dwFocusItem + 1;

	if (lpTagPage == NULL) 
		return -1;

	while (dwNewFocus < lpTagPage->dwNumOfSubItems)
	{
		lpSubItem = GetSoftItemByIndex(dwNewFocus);

		if (lpSubItem == NULL) 
			continue;

		if ((lpSubItem->_hWnd != NULL) && (IsWindowEnabled(lpSubItem->_hWnd) != FALSE) && (lpSubItem->dwStyle != SIS_Delimiter))
		{
			return SoftItem_SetFocus(dwNewFocus, 0);
		}

		dwNewFocus++;
	}

	return -2;
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
