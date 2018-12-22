#include "stdafx.h"
#include "htmlhelp.h"

#define WM_MYTIMER               (WM_USER + 2)

extern HFONT hFont_cfg1, hFont_cfg2;
#pragma comment (lib,"Htmlhelp.lib")

static const WCHAR wcsHelpPath[] = L"D:\\TianDa\\Help\\TD3618D_HELP.chm";
static int timess = 2;

WORD wWidth_SoftItem = 0, wHeight_SoftItem = 0;
RECT rcItem, rcLastItem;
static DWORD dwFocusItem = 0, dwLastFocus = INVALID_INDEX;
static DWORD dwFocusFlags = 0;
static PSOFT_TAG_PAGE lpCurTagPage = NULL;

//子控件 :: 更新位置
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags);
int SubCtrl_RadioButton_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags);
int SubCtrl_CheckButton_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags);
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags);
int SubCtrl_ComboButton_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags);

//子控件 :: 创建
int SubCtrl_Button_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_RadioButton_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_CheckButton_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_InputButton_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_ComboButton_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);

//子控件 :: 点击事件
LRESULT SubCtrl_Button_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd);
LRESULT SubCtrl_RadioButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd);
LRESULT SubCtrl_CheckButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd);
LRESULT SubCtrl_InputButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd);
LRESULT SubCtrl_ComoboButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd);

//窗口hook相关函数
void SetWndProc_Button(WNDPROC wpNewProc, BOOL blForce);
LRESULT CALLBACK wp_Button(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int TagPage_OnEnter()
{
	PSOFT_TAG_PAGE lpTagPage = lpCurTagPage;

	if (lpTagPage == NULL)
		return -1;

	if (CHK_FLAGS(lpTagPage->dwFlags, TPF_FN_ENTER) && (lpTagPage->fnEnter))
		return lpTagPage->fnEnter(0, 1, 0, lpTagPage);

	return -1;
}

int TagPage_OnLeave()
{
	PSOFT_TAG_PAGE lpTagPage = lpCurTagPage;

	if (lpTagPage == NULL) 
		return -1;

	if (CHK_FLAGS(lpTagPage->dwFlags, TPF_FN_LEAVE) && (lpTagPage->fnLeave))
		return lpTagPage->fnLeave(0, 1, 0, lpTagPage);

	return -1;
}

//************************************
// 函数名:    TagPage_ShowHelp
// Access:    public 
// 返回值类型:   void *
// 说明: 帮助文档链接,注意下面的lpCurTagPage->lpReserve[0]
//************************************
void * TagPage_ShowHelp(PSOFT_SUB_ITEM lpSubPage)
{
	if (lpCurTagPage && lpCurTagPage->lpReserve[0])
	{
		WCHAR wcsTmp[1024];
		swprintf_s(wcsTmp, 1024, L"%s%s", wcsHelpPath, lpCurTagPage->lpReserve[0]);
		return ShellExecuteW(NULL, L"open", L"hh.exe", wcsTmp, NULL, SW_SHOW);
	}
	else if ((0 != lpSubPage &&lpSubPage->dwReserve[1]) || (lpCurTagPage&&lpCurTagPage->lpReserve[1]))
	{
		HWND hWnd = FindWindow(NULL, "TD3619");
		HtmlHelp(hWnd, "D:\\TianDa\\Help\\TD3618D_HELP.chm", HH_HELP_CONTEXT, lpSubPage->dwReserve[1]);
	}
	return NULL;
}

int TagPage_DestroyItems(BOOL blLeave)
{
	PSOFT_TAG_PAGE lpTagPage = lpCurTagPage;

	if (lpTagPage == NULL) 
		return -1;

	for (DWORD i = 0; i < lpTagPage->dwNumOfSubItems; i++)
	{
		if (lpTagPage->lpSubItem[i]._hWnd)
		{
			DestroyWindow(lpTagPage->lpSubItem[i]._hWnd);
			lpTagPage->lpSubItem[i]._hWnd = NULL;
		}
	}

	return 0;
}

//TagPage RefreshItems 刷新控件
int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage)
{
	if (lpTagPage == NULL) 
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	TagPage_DestroyItems(TRUE);

	if (lpTagPage != lpCurTagPage)
	{
		TagPage_OnLeave();
		lpCurTagPage = lpTagPage;
		TagPage_OnEnter();
	}

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
#define Me   lpTagPage->lpSubItem[i]

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

		case SIS_Delimiter://分隔符			
		{
			if (Me.wHeight <= 20)
			{
				if (0 == Me.lpszItemText)
					Me.wHeight = 5;
				else
					Me.wHeight = 12;
			}

			lngWidth -= 4;

			LPCWSTR lpLblTitle = GetSoftItemTextByIndex(&Me, nLangId);
			DWORD dwExStyle = 0;

			if (lpLblTitle == NULL)
			{
				dwExStyle = WS_EX_STATICEDGE;
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
	UpdateSoftMenu();
	return 0;
}

int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage, BOOL blReload)
{
	if (lpTagPage == NULL)
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	TagPage_DestroyItems(TRUE);

	if (lpTagPage != lpCurTagPage || blReload != FALSE)
	{
		TagPage_OnLeave();
		lpCurTagPage = lpTagPage;
		TagPage_OnEnter();
	}

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
	//UpdateSoftMenu();
	return 0;
}

int TagPage_RefreshItems(BOOL blReload)
{
	int nRet = TagPage_RefreshItems(lpCurTagPage, blReload);
	SoftItem_SetFocus(dwFocusItem, dwFocusFlags);
	return nRet;
}

int TagPage_UpdateItemsPos(DWORD dwFlags)
{
	PSOFT_TAG_PAGE lpTagPage = lpCurTagPage;

	if (lpTagPage == NULL)
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	lpCurTagPage = lpTagPage;

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

//判断一个项目是否被激活
BOOL SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem)
{
	if (lpSubItem)
	{
		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_GROUP))
		{
			if (lpSubItem->dwActiveOffset == 0)
				return TRUE;
			else
				return FALSE;
		}
		else
		{
			PSOFT_SUB_ITEM lpGroupHeader = GetGroupHeader(SoftItem_GetCurrentTagPage(), lpSubItem);

			if (lpGroupHeader)
			{
				DWORD dwHeaderIndex = GetCurrentSoftItemIndex(lpGroupHeader);
				DWORD dwCurrentIndex = GetCurrentSoftItemIndex(lpSubItem);

				if ((dwHeaderIndex != INVALID_INDEX) && (dwCurrentIndex != INVALID_INDEX))
				{
					if (dwHeaderIndex + lpGroupHeader->dwActiveOffset == dwCurrentIndex)
						return TRUE;
					else
						return FALSE;
				}
			}
		}
	}

	return FALSE;
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

//绘制项目的过程 (按钮背景,复选框样式,扩展标签等)
static void OnDrawItem_Button(int nCtrlId, LPDRAWITEMSTRUCT lpDIS, PSOFT_SUB_ITEM lpSubItem)
{
	if (lpDIS == NULL || lpSubItem == NULL) 
		return;

	HDC hDC = lpDIS->hDC, hCDC;
	BOOL blCDC = TRUE;
	HBITMAP hBM;
	RECT rect, rect2;
	int cx, cy;
	LPCWSTR lpcSubText = NULL;
	HWND hFocus;
	WCHAR wStr[MAX_PATH];

	GetClientRect(lpDIS->hwndItem, &rect);
	cx = rect.right - rect.left;
	cy = rect.bottom - rect.top;

	rect2 = rect;

	hCDC = CreateCompatibleDC(hDC);

	//判断双缓冲
	if (hCDC == NULL)
	{
		hCDC = hDC;
		blCDC = FALSE;
	}
	else if (hBM = CreateCompatibleBitmap(hDC, cx, cy))
	{
		SelectObject(hCDC, hBM);
		DeleteObject(hBM);
	}
	else
	{
		DeleteDC(hCDC);
		hCDC = hDC;
		blCDC = FALSE;
	}

  {
	  HFONT hFont = (HFONT)SNDMSG(lpDIS->hwndItem, WM_GETFONT, 0, 0);
	  if (hFont) 
		  SelectObject(hCDC, hFont);
  }

  SetBkMode(hCDC, TRANSPARENT);

  if (lpSubItem->dwStyle == SIS_CheckButtonEx) /*|| lpSubItem->dwStyle == SIS_CheckInputButtonEx)*/
	  UpdateCheckBoxState(lpSubItem);

  if (IsWindowEnabled(lpDIS->hwndItem) == FALSE || CHK_FLAGS(lpSubItem->dwAttributes, SIA_UNREAD))
  {
	  DrawStretchBitmap(hCDC, hBmp_ButtonU, &rect);
  }
  else if (CHK_FLAGS(lpDIS->itemState, ODS_SELECTED) || CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED) || SoftItem_IsActive(lpSubItem))
  {
	  DrawStretchBitmap(hCDC, hBmp_Button1s, &rect);
  }
  else
  {
	  DrawStretchBitmap(hCDC, hBmp_Button1, &rect);
  }

  hFocus = GetFocus();

  //绘制焦点矩形
  if ((((DWORD)nCtrlId == dwFocusItem) || (lpDIS->hwndItem == hFocus) || (lpDIS->hwndItem == GetParent(hFocus))) && !CHK_FLAGS(lpSubItem->dwAttributes, SIA_UNREAD))
  {
	  DrawStretchBitmap(hCDC, hBmp_Button1s, &rect);
  }

  GetWindowTextW(lpDIS->hwndItem, wStr, MAX_PATH);
  SetTextColor(hCDC, RGB(240,240,240));	//修改菜单字体颜色

  rect2 = rect;

  if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_SHOWSUB))
	  lpcSubText = GetActiveItemTextBySoftMenu(lpSubItem->lpSoftMenu);

  if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_SHOWSUB) && CHK_FLAGS(lpSubItem->dwFlags, SIF_ISMENU) && (cy > 40) && (lpcSubText))  //ShowSub
  {
	  rect2.left += 2;
	  rect2.top += 2;
	  rect2.right -= 2;
	  rect2.bottom -= 32;
	  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER);
	 
	  rect2.left += 2;
	  rect2.top = rect2.bottom + 3;
	  rect2.right -= 2;
	  rect2.bottom = rect.bottom - 3;
	  FillRect(hCDC, &rect2, GetStockBrush(WHITE_BRUSH));
	  DrawEdge(hCDC, &rect2, EDGE_SUNKEN, BF_RECT);
	 
	  rect2.left++;
	  rect2.top++;
	  rect2.right--;
	  rect2.bottom--;
	 
	  DrawTextW(hCDC, lpcSubText, -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
  }
  else if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_BITMAP))  //位图
  {
	  DWORD dwLE;
	  rect2.left += 2;
	  rect2.top += 2;
	  rect2.right -= 2;
	  rect2.bottom -= 2;

	  if (lpSubItem->lpOpt[4] == NULL)
		  lpSubItem->lpOpt[4] = LoadImage((CHK_FLAGS(lpSubItem->dwAttributes, SIA_MAINRES) ? hMainMod : hMod), MAKEINTRESOURCE(lpSubItem->nBitmapId), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	  dwLE = GetLastError();

	  if (lpSubItem->lpOpt[4])
	  {
		  DrawStretchBitmap(hCDC, (HBITMAP)lpSubItem->lpOpt[4], &rect2);
	  }
  }
  else  //default
  {
	  switch (lpSubItem->dwStyle)
	  {
	  case SIS_CheckButtonEx:
	  {
		  RECT rect3;
		  rect3 = rect2;
		  if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_FULLLINE))
		  {
			  rect2.left += (rect3.right - rect3.left) / 5 / 2 - 5;
			  rect2.right = (rect3.right - rect3.left) / 5 / 2 + 9;
		  }
		  else
		  {
			  rect2.left += (rect3.right - rect3.left) / 5 - 5;
			  rect2.right = (rect3.right - rect3.left) / 5  + 9;
		  }
		  rect2.top = lpSubItem->wHeight / 2 - 7;
		  rect2.bottom = lpSubItem->wHeight / 2 + 7;

		  if (CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED))
			  DrawStretchBitmap(hCDC, hBmp_Checked, &rect2);
		  else
			  DrawStretchBitmap(hCDC, hBmp_Unchecked, &rect2);
		  rect3.left = rect2.right + 2;
		  if (nLangId == 0)
		  {
			  if (wcslen(wStr) > 12)
			  {
				  rect3.top += 3;
				  rect3.left += 6;
				  rect3.right -= 7;
				  rect3.bottom += 8;
				  DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
			  }
			  else
				  DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		  }
		  else
		  {
			  if (wcslen(wStr) > 6)
			  {
				  rect3.top += 3;
				  rect3.left += 7;
				  rect3.right -= 8;
				  rect3.bottom += 8;
				  DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
			  }
			  else
			  {
				  rect3.top -= 3;
				  DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			  }
		  }

	  }
	  break;

	  case SIS_InputButtonEx:
	  case SIS_ComboButtonEx:
	  case SIS_ComboRadioButtonEx:
		  rect2.left += 2;
		  rect2.right -= 2;

		  rect2.top += 4;
		  rect2.bottom = rect.bottom - 23;		  //调整其他框字符}
		  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER);
		  break;

	  default: // SIS_ButtonEx:
		  if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_EXLBL) && CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEITEM))
		  {
			  rect2.left += 2;
			  rect2.top += 3;
			  rect2.right -= 2;
			  rect2.bottom -= 2;
			  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_VCENTER);
		  }
		  else
		  {
			  if (nLangId == 0)
			  {
				  if (wcslen(wStr) > 15)
				  {
					  rect2.top += 2;
					  rect2.left += 7;
					  rect2.right -= 7;
					  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
				  }
				  else
					  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			  }
			  else
			  {
				  if (wcslen(wStr) > 9)
				  {
					  rect2.left += 7;
					  rect2.right -= 7;
					  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
				  }
				  else
					  DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			  }
		  }
	  break;
	  }
  }

  if (blCDC)
  {
	  BitBlt(hDC, rect.left, rect.top, cx, cy, hCDC, rect.left, rect.top, SRCCOPY);
	  DeleteDC(hCDC);
  }

  if ((lpSubItem->dwStyle == SIS_InputButtonEx) && (lpSubItem->lpOpt[1]) && (lpSubItem->lpOpt[4]))
  {
	  if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_POPINPUTWND))
	  {
		  InvalidateRect((HWND)lpSubItem->lpOpt[4], NULL, TRUE);
		  UpdateWindow((HWND)lpSubItem->lpOpt[4]);
	  }
  }
}

//静态标签颜色
static LRESULT OnCtlColorStatic(PSOFT_SUB_ITEM lpSubItem, HDC hCtlDC, HWND hCtlWnd)
{
	SetBkMode(hCtlDC, TRANSPARENT);
	return (LRESULT)(HBRUSH)(COLOR_DESKTOP);
}

//项目的 WM_COMMAND 处理消息
static LRESULT OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd)
{
	LRESULT lResult = 0;

	switch (nCode)
	{
	case BN_CLICKED:
	{
		PopWnd_Destroy(0, TRUE);

		PSTMSG_432_2();

		switch (lpSubItem->dwStyle)
		{
			//case SIS_Button:
		case SIS_ButtonEx:
			lResult = SubCtrl_Button_OnClicked(lpSubItem, nItemIndex, hWnd);
			break;

			//case SIS_CheckButton:
		case SIS_CheckButtonEx:
			lResult = SubCtrl_CheckButton_OnClicked(lpSubItem, nItemIndex, hWnd);
			break;

		case SIS_InputButtonEx:
			lResult = SubCtrl_InputButton_OnClicked(lpSubItem, nItemIndex, hWnd);
			break;

			//case SIS_RadioButton:
		case SIS_RadioButtonEx:
			lResult = SubCtrl_RadioButton_OnClicked(lpSubItem, nItemIndex, hWnd);
			break;

		case SIS_ComboButtonEx:
		case SIS_ComboRadioButtonEx:
			lResult = SubCtrl_ComoboButton_OnClicked(lpSubItem, nItemIndex, hWnd);
			break;

		default:
			break;
		}

		SoftItem_ActivationItem(lpSubItem);

		if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_SWITCH))
		{
			if (lpSubItem->lpEvent[FNID_CLICKED])
			{
				func_ItemEvent_Clicked fnClicked = (func_ItemEvent_Clicked)lpSubItem->lpEvent[FNID_CLICKED];
				fnClicked(0, IC_CLICKED_LAST, 0, lpSubItem);
			}			
			else if (lpSubItem->lpEvent[FNID_SELECTED])			
			{
				func_ItemEvent_Selected fnSelected = (func_ItemEvent_Selected)lpSubItem->lpEvent[FNID_SELECTED];

				fnSelected(0, 0, 0, lpSubItem, ComboBox_GetCurSel((HWND)lpSubItem->lpOpt[4]));

				UpdateCurrentItemsAndData();
			}			
		}

		if (CHK_FLAGS(lpSubItem->dwFlags, SIF_ORIGCLICK))
		{
			if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOREPLY) && (lpSubItem->dwStyle != SIS_CheckButtonEx))
			{
				if (lpSubItem->lpVTable && lpSubItem->lpThis)
				{
					if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOT_ENTER))
						OrigSoftMenu_Enter(lpSubItem->lpThis);

					OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
				}
			}
		}
		else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_ISMENU) && (lpSubItem->lpSoftMenu))
			SoftMenu_Push(lpSubItem->lpSoftMenu);

		else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_SNDMSGCMD))
			SNDMSG(cwMainWnd->m_hWnd, WM_COMMAND, lpSubItem->wParam, lpSubItem->lParam);
		
 		else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_CALWND) && (lpSubItem->lpCalDlgCtxt))
 			CreateDialog_Cal(lpSubItem->lpCalDlgCtxt, 0);

		else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_DIALOG) && (lpSubItem->lpDlgCtxt))
			CreateDialog_Def(lpSubItem->lpDlgCtxt, 0);

		if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_CLICKED) && (lpSubItem->lpEvent[FNID_CLICKED])&&CHK_NOFLAGS(lpSubItem->dwFlags,SIF_FN_SWITCH))
		{
			func_ItemEvent_Clicked fnClicked = (func_ItemEvent_Clicked)lpSubItem->lpEvent[FNID_CLICKED];
			fnClicked(0, IC_CLICKED_LAST, 0, lpSubItem);
		}

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEITEM))
			UpdateCurrentItems();

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEDATA))
			UpdateCurrentItemsAndData();

		if (CHK_FLAGS(lpSubItem->dwFlags,SIF_FN_SETFOCUS))
			SetFocus(hWnd);
	}
	return lResult;

	default:
		return -1;
	}
}

//软菜单项目区域窗口过程
LRESULT CALLBACK wpfn_SoftItem(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL blTME = TRUE;
	static BOOL blStop = FALSE;

	switch (msg)
	{
	case WM_NCPAINT:
		break;
	case WM_CREATE:
		break;
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			PSOFT_TAG_PAGE lpTagPage = lpCurTagPage;

			wWidth_SoftItem = LOWORD(lParam);
			wHeight_SoftItem = HIWORD(lParam);

			TagPage_UpdateItemsPos(0);
		}
		break;

	case WM_DRAWITEM:
	{
		if (wParam)
		{
			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;
			PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(lpDIS->hwndItem, GWL_USERDATA);

			if (lpSubItem)
			{
				switch (lpSubItem->dwStyle)
				{
				case SIS_ButtonEx:
				case SIS_RadioButtonEx:
				case SIS_CheckButtonEx:
				case SIS_InputButtonEx:
				case SIS_ComboButtonEx:
				case SIS_ComboRadioButtonEx:
					OnDrawItem_Button((int)wParam - 1000, lpDIS, lpSubItem);
					break;

				default:
					return DefWindowProc(hWnd, msg, wParam, lParam);
				}

				return TRUE;
			}
		}
	}
	break;

	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtlWnd = (HWND)lParam;
	
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hCtlWnd, GWL_USERDATA);
	
		if (lpSubItem)
			return OnCtlColorStatic(lpSubItem, hDC, hCtlWnd);
	}
	break;

	case WM_MYTIMER:
		UpdateCurrentItemsAndData();
		break;

	case WM_COMMAND:
	{
		if (lParam)
		{
			WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);
			PSOFT_SUB_ITEM lpSubItem = GetSoftItemByIndex((int)wId - 1000);

			if ((lpSubItem) && (lpSubItem == (PSOFT_SUB_ITEM)GetWindowLong((HWND)lParam, GWL_USERDATA)))
			{
				LRESULT nRet;

				if (lpSubItem->dwStyle < SIS_Invalid)
				{
					nRet = OnCommand_Button(lpSubItem, wId - 1000, wNc, (HWND)lParam);

					if (nRet == -1)
						return DefWindowProc(hWnd, msg, wParam, lParam);
					else
						return nRet;
				}
			}
		}
	}
	break;

	case WM_SETFOCUS:
	{
		PSOFT_TAG_PAGE lpTagPage = SoftItem_GetCurrentTagPage();
		PSOFT_SUB_ITEM lpSubItem = NULL;

		if (dwFocusItem >= lpTagPage->dwNumOfSubItems) dwFocusItem = 0;

		while (dwFocusItem < lpTagPage->dwNumOfSubItems)
		{
			lpSubItem = GetSoftItemByIndex(dwFocusItem);

			if (lpSubItem == NULL)
				break;
			if (lpSubItem->dwStyle != SIS_Delimiter)
				break;

			lpSubItem = NULL;
			dwFocusItem++;
		}

		if ((lpSubItem) && (lpSubItem->_hWnd))
		{
			SetFocus(lpSubItem->_hWnd);
			InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
			UpdateWindow(lpSubItem->_hWnd);

			return 0;
		}
	}
	break;

	case WM_REFRESH:	//刷新右侧按钮菜单事件
	{
		TagPage_RefreshItems(lpCurTagPage);
		SetFocus(hWnd);
		break;
	}

	case WM_FINETUNE:
	{
		SoftItem_Finetune(SoftItem_GetFocusItem(), (int)wParam, (int)lParam);
	}
	return 0;

	case WM_DESTROY:
		blStop = TRUE;
		Sleep(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

inline PSOFT_TAG_PAGE SoftItem_GetCurrentTagPage()
{
	return lpCurTagPage;
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
