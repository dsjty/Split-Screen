// TDItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TDItem.h"


// TDItem

IMPLEMENT_DYNAMIC(TDItem, CWnd)

TDItem::TDItem()
{

}

TDItem::TDItem(PSOFT_TAG_PAGE CurTagPage)
{
	stCurTagPage = *CurTagPage;
}

TDItem::~TDItem()
{
}

BEGIN_MESSAGE_MAP(TDItem, CWnd)
END_MESSAGE_MAP()


//更新按钮位置
int TDItem::TagPage_UpdateItemsPos()
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (lpTagPage == NULL)
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

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

		::MoveWindow(Me._hWnd, lngLeft, rcItem.bottom, lngWidth, Me.wHeight, TRUE);

		switch (Me.dwStyle)
		{
			case SIS_ButtonEx:			//普通按钮
			{
				SubCtrl_Button_UpdatePos(&Me);	
				break;
			}
			case SIS_RadioButtonEx:			//单选按钮
				break;

			case SIS_CheckButtonEx:			//复选框
				break;

			case SIS_InputButtonEx:			//输入框
			{
				SubCtrl_InputButton_UpdatePos(&Me);		
				break;
			}
			case SIS_ComboButtonEx:
			case SIS_ComboRadioButtonEx:			//下拉列表
			{
				SubCtrl_ComboButton_UpdatePos(&Me);	
				break;
			}
		}

		if (Me._hWnd)
		{
			::GetWindowRect(Me._hWnd, &(Me.rect));

			if (CHK_FLAGS(Me.dwAttributes, SIAE_DISABLED))
				::EnableWindow(Me._hWnd, FALSE);
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
}

//绘制项目的过程 (按钮背景,复选框样式,扩展标签等)
void TDItem::OnDrawItem_Button(int nCtrlId, LPDRAWITEMSTRUCT lpDIS, PSOFT_SUB_ITEM lpSubItem)
{
	if (lpDIS == NULL || lpSubItem == NULL)
		return;

	HDC hDC = lpDIS->hDC, hCDC;
	BOOL blCDC = TRUE;
	HBITMAP hBM;
	RECT rect, rect2;
	int cx, cy;
	LPCWSTR lpcSubText = NULL;
	CWnd *hFocus;
	WCHAR wStr[MAX_PATH];

	GetClientRect(&rect);
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

	if (lpSubItem->dwStyle == SIS_CheckButtonEx)
		UpdateCheckBoxState(lpSubItem);

	if (IsWindowEnabled() == FALSE || CHK_FLAGS(lpSubItem->dwAttributes, SIA_UNREAD))
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
	if ((((DWORD)nCtrlId == dwFocusItem) || (lpDIS->hwndItem == hFocus->m_hWnd) || (lpDIS->hwndItem == GetParent()->m_hWnd)) && !CHK_FLAGS(lpSubItem->dwAttributes, SIA_UNREAD))
	{
		DrawStretchBitmap(hCDC, hBmp_Button1s, &rect);
	}

	GetWindowTextW(lpDIS->hwndItem, wStr, MAX_PATH);
	SetTextColor(hCDC, RGB(240, 240, 240));	//修改菜单字体颜色

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
				rect2.right = (rect3.right - rect3.left) / 5 + 9;
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
			::InvalidateRect((HWND)lpSubItem->lpOpt[4], NULL, TRUE);
			::UpdateWindow((HWND)lpSubItem->lpOpt[4]);
		}
	}
}

int TDItem::TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage)
{
	if (lpTagPage == NULL)
		return -1;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	TagPage_DestroyItems(TRUE);

	TagPage_OnEnter();

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
			SubCtrl_Button_Create(hwSoftItem,&Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
			SubCtrl_RadioButton_Create(hwSoftItem,&Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
			SubCtrl_CheckButton_Create(hwSoftItem, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
			SubCtrl_InputButton_Create(hwSoftItem, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
			SubCtrl_ComboButton_Create(hwSoftItem,  &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
				::InvalidateRect(Me._hWnd, NULL, TRUE);
			}
		}
		break;
		}

		if (Me._hWnd)
		{
			if (Me.dwStyle != SIS_Delimiter)
				SetWndProc_Button((WNDPROC)SetWindowLong(Me._hWnd, GWL_WNDPROC, (LONG)&wp_Button), FALSE);

			::GetWindowRect(Me._hWnd, &(Me.rect));

			if (CHK_FLAGS(Me.dwAttributes, SIAE_DISABLED))
				::EnableWindow(Me._hWnd, FALSE);
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
	::RedrawWindow(hwSoftItem, NULL, NULL, RDW_ERASE | RDW_ALLCHILDREN);
	UpdateSoftMenu();
	return 0;
}

BOOL TDItem::SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem)
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

LRESULT TDItem::OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd)
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
		case SIS_ButtonEx:
			break;

		case SIS_CheckButtonEx:
			lResult = SubCtrl_CheckButton_OnClicked(lpSubItem, hWnd);
			break;

		case SIS_InputButtonEx:
			lResult = SubCtrl_InputButton_OnClicked(lpSubItem, hWnd);
			break;

		case SIS_RadioButtonEx:
			lResult = SubCtrl_RadioButton_OnClicked(lpSubItem, hWnd);
			break;

		case SIS_ComboButtonEx:
		case SIS_ComboRadioButtonEx:
			lResult = SubCtrl_ComoboButton_OnClicked(lpSubItem, hWnd);
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

		if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_CLICKED) && (lpSubItem->lpEvent[FNID_CLICKED]) && CHK_NOFLAGS(lpSubItem->dwFlags, SIF_FN_SWITCH))
		{
			func_ItemEvent_Clicked fnClicked = (func_ItemEvent_Clicked)lpSubItem->lpEvent[FNID_CLICKED];
			fnClicked(0, IC_CLICKED_LAST, 0, lpSubItem);
		}

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEITEM))
			UpdateCurrentItems();

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEDATA))
			UpdateCurrentItemsAndData();

		if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_SETFOCUS))
			::SetFocus(hWnd);
	}
	return lResult;

	default:
		return -1;
	}
}

int TDItem::TagPage_DestroyItems(BOOL blLeave)
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (lpTagPage == NULL)
		return -1;
	
	if (CHK_FLAGS(lpTagPage->dwFlags, TPF_FN_LEAVE) && (lpTagPage->fnLeave))
		return lpTagPage->fnLeave(0, 1, 0, lpTagPage);
	
	for (DWORD i = 0; i < lpTagPage->dwNumOfSubItems; i++)
	{
		if (lpTagPage->lpSubItem[i]._hWnd)
		{
			::DestroyWindow(lpTagPage->lpSubItem[i]._hWnd);
			lpTagPage->lpSubItem[i]._hWnd = NULL;
		}
	}

	return 0;
}

int TDItem::TagPage_OnEnter()
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (CHK_FLAGS(lpTagPage->dwFlags, TPF_FN_ENTER) && (lpTagPage->fnEnter))
		return lpTagPage->fnEnter(0, 1, 0, lpTagPage);
}

// TDItem 消息处理程序
LRESULT TDItem::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message)
	{
	case WM_NCPAINT:
		break;
	case WM_CREATE:
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
					return DefWindowProc(message, wParam, lParam);
				}

				return TRUE;
			}
		}
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtlWnd = (HWND)lParam;

		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hCtlWnd, GWL_USERDATA);

		if (lpSubItem)
		{
			SetBkMode(hDC, TRANSPARENT);
			return (LRESULT)(HBRUSH)(COLOR_DESKTOP);
		}
		break;
	}
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
						return DefWindowProc(message, wParam, lParam);
					else
						return nRet;
				}
			}
		}
		break; 
	}

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
			::SetFocus(lpSubItem->_hWnd);
			::InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
			::UpdateWindow(lpSubItem->_hWnd);

			return 0;
		}
		break;
	}

	case WM_REFRESH:	//刷新右侧按钮菜单事件
	{
		TagPage_RefreshItems(0);
		break;
	}
	
	default:
		break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}
