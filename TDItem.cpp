// TDItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TDItem.h"


// TDItem

IMPLEMENT_DYNAMIC(TDItem, CWnd)

TDItem::TDItem() :
	uiCurMenus(1)
{

}

TDItem::TDItem(PSOFT_TAG_PAGE CurTagPage, int iSer) :
	uiCurMenus(iSer)
{
	stCurTagPage = *CurTagPage;
	SOFT_SUB_ITEM stSubItem = { 0 };
	for (size_t i = 0; i < stCurTagPage.dwNumOfSubItems; i++)
	{
		stSubItem = stCurTagPage.lpSubItem[i];
		ssSumItem.push_back(stSubItem);
	}
}

TDItem::~TDItem()
{
}

BEGIN_MESSAGE_MAP(TDItem, CWnd)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


//更新按钮位置
int TDItem::TagPage_UpdateItemsPos()
{
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

	for (DWORD i = 0; i < ssSumItem.size(); i++)
	{
#define Me ssSumItem.at(i)
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
		else if (i < ssSumItem.size())
		{
			if ((ssSumItem.at(i + 1).wMinWidth > lngHalf) || CHK_FLAGS(ssSumItem.at(i + 1).dwAttributes, SIA_FULLLINE))
			{
				rcItem.bottom += Me.wHeight + 2;
				blTail = FALSE;
			}
		}

#undef Me 
	}
	return 0;
}

int TDItem::TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage)
{
	PSOFT_TAG_PAGE TagPage = 0;

	if (!this)
		return 0;

	HWND hwSoftItem = this->m_hWnd;

	if (lpTagPage == NULL)
		lpTagPage = &stCurTagPage;
	else
		stCurTagPage = *lpTagPage;

	TagPage = &stCurTagPage;

	BOOL blTail = FALSE;
	LONG lngLeft, lngWidth, lngHalf;

	TagPage_DestroyItems(TRUE);

	TagPage_OnEnter();

	rcItem.left = 2;
	rcItem.top = 2;
	rcItem.right = WIDTH_SOFTMENU - WIDTH_SUBMENU - 4;
	rcItem.bottom = rcItem.top;

	rcLastItem.left = 0;
	rcLastItem.top = 0;
	rcLastItem.right = 0;
	rcLastItem.bottom = 0;

	lngHalf = (rcItem.right - rcItem.left - 2) / 2;

	ssSumItem.clear();//清空按钮hwnd栈;

	for (DWORD i = 0; i < TagPage->dwNumOfSubItems; i++)
	{
		ssSumItem.push_back(TagPage->lpSubItem[i]);
#define Me   ssSumItem.at(i)

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
					SubCtrl_Button_Create(hwSoftItem, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
					SubCtrl_RadioButton_Create(hwSoftItem, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
					SubCtrl_ComboButton_Create(hwSoftItem, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
					SubCtrl_StaticButton_Create(hwSoftItem, &Me, lngLeft, rcItem.bottom, lngWidth, Me.wHeight);

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
				::GetWindowRect(Me._hWnd, &(Me.rect));

			if (CHK_FLAGS(Me.dwAttributes, SIAE_DISABLED))
				::EnableWindow(Me._hWnd, FALSE);
		}

		if (blTail == FALSE)
			rcItem.bottom += Me.wHeight + 2;
		else if (i < TagPage->dwNumOfSubItems)
		{
			if ((TagPage->lpSubItem[i + 1].wMinWidth > lngHalf) || CHK_FLAGS(TagPage->lpSubItem[i + 1].dwAttributes, SIA_FULLLINE))
			{
				rcItem.bottom += Me.wHeight + 2;
				blTail = FALSE;
			}
		}

#undef Me 
	}

	UpdateDataByTagPage(&ssSumItem);
	RedrawWindow(NULL, NULL, RDW_ERASE | RDW_ALLCHILDREN);
	UpdateSoftMenu();
	SoftItem_SetFocus(dwFocusItem, 0);
	return 0;
}

BOOL TDItem::SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem)
{
	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_ATCTION))
		return TRUE;
	return false;
}

LRESULT TDItem::OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd)
{
	LRESULT lResult = 0;

	switch (nCode)
	{
		case BN_CLICKED:
			{
				uiCurFocusMenu = uiCurMenus;

				PopWnd_Destroy(0, TRUE);

				PSTMSG_432_2();

				//更新焦点值
				for (size_t i = 0; i < ssSumItem.size(); i++)
				{
					if (ssSumItem.at(i)._hWnd)
					{
						if (hWnd = ssSumItem.at(i)._hWnd)
						{
							dwFocusItem = i;
							break;
						}
					}
				}

				SoftItem_ActivationItem(lpSubItem);
			}
	}
	return 0;
}

int TDItem::TagPage_DestroyItems(BOOL blLeave)
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (lpTagPage == NULL)
		return -1;

	if (CHK_FLAGS(lpTagPage->dwFlags, TPF_FN_LEAVE) && (lpTagPage->fnLeave))
		return lpTagPage->fnLeave(0, 1, 0, lpTagPage);

	for (DWORD i = 0; i < ssSumItem.size(); i++)
	{
		if (ssSumItem.at(i)._hWnd)
		{
			vcButton.at(i)->DestroyWindow();
		}
	}
	UpdateWindow();
	return 0;
}

int TDItem::TagPage_OnEnter()
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (CHK_FLAGS(lpTagPage->dwFlags, TPF_FN_ENTER) && (lpTagPage->fnEnter))
		return lpTagPage->fnEnter(0, 1, 0, lpTagPage);
}

int TDItem::SoftItem_SetFocus(DWORD dwNewFocus, DWORD dwNewFlags)
{
	PSOFT_SUB_ITEM lpSubItem = NULL;

	if (dwNewFocus >= ssSumItem.size())
		return -9;

	for (; dwNewFocus < ssSumItem.size(); dwNewFocus++)
	{
		lpSubItem = &(ssSumItem.at(dwNewFocus));

		if (lpSubItem == NULL)
			continue;

		if ((lpSubItem->_hWnd != NULL) && (::IsWindowEnabled(lpSubItem->_hWnd) != FALSE) && (lpSubItem->dwStyle != SIS_Delimiter))
		{
			if (CHK_FLAGS(dwNewFlags, 0x01) && (lpSubItem->lpOpt[4]))
				::SetFocus((HWND)lpSubItem->lpOpt[4]);
			else if (lpSubItem->_hWnd)
				::SetFocus(lpSubItem->_hWnd);
			else
				return -9;

			SoftItem_ScrollFocus();

			return 0;
		}
	}
	return -10;
}

int TDItem::SoftItem_ScrollFocus()
{
	PSOFT_SUB_ITEM lpFocusItem = &(ssSumItem.at(dwFocusItem));
	RECT rcFocus, rcClient;
	LONG lngDiff;

	if (lpFocusItem == NULL || lpFocusItem->_hWnd == NULL)
		return -1;

	::GetClientRect(lpFocusItem->_hWnd, &rcFocus);
	GetClientRect(&rcClient);

	::ClientToScreen(lpFocusItem->_hWnd, &rcFocus);
	ClientToScreen(&rcClient);

	if (rcFocus.top < rcClient.top + 2)
	{
		lngDiff = (rcClient.top + 2) - rcFocus.top;

		ScrollWindowEx(0, lngDiff, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
		UpdateWindow();
	}
	else if (rcFocus.bottom > rcClient.bottom - 2)
	{
		lngDiff = (rcClient.bottom - 2) - rcFocus.bottom;

		ScrollWindowEx(0, lngDiff, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
		UpdateWindow();
	}

	return 0;
}

void TDItem::SoftItem_ActivationItem(PSOFT_SUB_ITEM lpSubItem)
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
				PSOFT_SUB_ITEM lpSubItem2 = &ssSumItem.at(dwIndex + lpSubItem->dwActiveOffset);

				if (lpSubItem2 && ((lpSubItem2->dwStyle == SIS_RadioButtonEx) || (lpSubItem2->dwStyle == SIS_ComboRadioButtonEx)))
				{
					NOT_FLAGS(lpSubItem2->dwAttributes, SIAE_CHECKED);
					lpSubItem->dwActiveOffset = 0;

					::InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
					::UpdateWindow(lpSubItem->_hWnd);

					return;
				}
			}
		}

		lpSubItem->dwActiveOffset = 0;
		::InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		::UpdateWindow(lpSubItem->_hWnd);
		return;
	}
	else
	{
		PSOFT_SUB_ITEM lpHeaderItem = GetGroupHeader(lpSubItem);

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
					PSOFT_SUB_ITEM lpSubItem2 = &ssSumItem.at(dwIndex + lpHeaderItem->dwActiveOffset);

					if (lpSubItem2 && ((lpSubItem2->dwStyle == SIS_RadioButtonEx) || (lpSubItem2->dwStyle == SIS_ComboRadioButtonEx)))
					{
						NOT_FLAGS(lpSubItem2->dwAttributes, SIAE_CHECKED);
						lpHeaderItem->dwActiveOffset = GetGroupOffsetIndex(lpSubItem);

						::InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
						::UpdateWindow(lpSubItem->_hWnd);
						return;
					}
				}
			}

			lpHeaderItem->dwActiveOffset = GetGroupOffsetIndex(lpSubItem);
			::InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
			::UpdateWindow(lpSubItem->_hWnd);
			return;
		}
		::InvalidateRect(lpSubItem->_hWnd, NULL, TRUE);
		::UpdateWindow(lpSubItem->_hWnd);
	}
}

void TDItem::SoftItem_SetActiveSoftItem(DWORD dwIndex)
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (lpTagPage && (dwIndex < lpTagPage->dwNumOfSubItems))
		lpTagPage->dwActiveIndex = (dwIndex == INVALID_INDEX) ? 0 : dwIndex;
}

void TDItem::SoftItem_ActivationItemByOffsetIndex(PSOFT_SUB_ITEM lpSubItem, int nOffsetIndex)
{
	if (lpSubItem == NULL)
		return;

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_GROUP))  //该子条目是一个组的头部
	{
		DWORD dwIndex = GetCurrentSoftItemIndex(lpSubItem);

		if (dwIndex == INVALID_INDEX)
			return;

		if (dwIndex + nOffsetIndex >= ssSumItem.size())
			return;

		PSOFT_SUB_ITEM lpDestItem = &ssSumItem.at(dwIndex + nOffsetIndex);

		SoftItem_ActivationItem(lpDestItem);
	}
	else
	{
		PSOFT_SUB_ITEM lpHeaderItem = GetGroupHeader(lpSubItem);

		if (lpHeaderItem)
		{
			DWORD dwIndex = GetCurrentSoftItemIndex(lpHeaderItem);

			if (dwIndex == INVALID_INDEX)
				return;

			if (dwIndex + nOffsetIndex >= ssSumItem.size())
				return;

			PSOFT_SUB_ITEM lpDestItem = &ssSumItem.at(dwIndex + nOffsetIndex);

			SoftItem_ActivationItem(lpDestItem);
		}
	}

	return;
}

DWORD TDItem::GetCurrentSoftItemIndex(PSOFT_SUB_ITEM lpSubItem)
{
	return lpSubItem->dwGroupIndex;
}

PSOFT_SUB_ITEM TDItem::GetGroupHeader(PSOFT_SUB_ITEM lpSubItem)
{
	if (lpSubItem == NULL)
		return NULL;
	if (lpSubItem->dwAttributes & SIA_GROUP)
		return NULL;
	if (lpSubItem->dwGroupIndex >= ssSumItem.size())
		return NULL;

	if (ssSumItem.at(lpSubItem->dwGroupIndex).dwAttributes & SIA_GROUP)
		return &(ssSumItem.at(lpSubItem->dwGroupIndex));

	return NULL;
}

DWORD TDItem::GetGroupOffsetIndex(PSOFT_SUB_ITEM lpSubItem)
{
	if (lpSubItem == NULL)
		return 0;
	if (lpSubItem->dwAttributes & SIA_GROUP)
		return 0;
	if (lpSubItem->dwGroupIndex >= ssSumItem.size())
		return 0;

	DWORD dwOffset = GetCurrentSoftItemIndex(lpSubItem) - lpSubItem->dwGroupIndex;
	return dwOffset;
}

int TDItem::SoftItem_SetFocusValue(DWORD dwNewFocus, DWORD dwNewFlags)
{
	PSOFT_TAG_PAGE lpTagPage = &stCurTagPage;

	if (lpTagPage == NULL)
		return -1;
	if (dwNewFocus >= lpTagPage->dwNumOfSubItems)
		return -2;

	dwLastFocus = dwFocusItem;
	dwFocusItem = dwNewFocus;
	dwFocusFlags = dwNewFlags;

	return 0;
}

int TDItem::SoftItem_PrevItem()
{
	PSOFT_SUB_ITEM lpSubItem = NULL;
	DWORD dwNewFocus = dwFocusItem - 1;

	while (dwNewFocus < ssSumItem.size())
	{
		lpSubItem = &ssSumItem.at(dwNewFocus);

		if (lpSubItem == NULL)
			continue;

		if ((lpSubItem->_hWnd != NULL) && (::IsWindowEnabled(lpSubItem->_hWnd) != FALSE) && (lpSubItem->dwStyle != SIS_Delimiter))
		{
			dwFocusItem = dwNewFocus;
			return SoftItem_SetFocus(dwNewFocus, 0);
		}

		dwNewFocus--;
	}

	return -2;
}

int TDItem::SoftItem_NextItem()
{
	PSOFT_SUB_ITEM lpSubItem = NULL;
	DWORD dwNewFocus = dwFocusItem + 1;

	while (dwNewFocus < ssSumItem.size())
	{
		lpSubItem = &ssSumItem.at(dwNewFocus);

		if (lpSubItem == NULL)
			continue;

		if ((lpSubItem->_hWnd != NULL) && (::IsWindowEnabled(lpSubItem->_hWnd) != FALSE) && (lpSubItem->dwStyle != SIS_Delimiter))
		{
			dwFocusItem = dwNewFocus;
			return SoftItem_SetFocus(dwNewFocus, 0);
		}

		dwNewFocus++;
	}

	return -2;
}

PSOFT_SUB_ITEM TDItem::GetItemByIndex(int nIndex)
{
	return &ssSumItem.at(nIndex);
}

int TDItem::SubCtrl_Button_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	char *temp = new char[30];
	WideCharToMultiByte(CP_ACP, 0, GetSoftItemTextByIndex(lpMe, nLangId), -1, temp, sizeof(char) * 30, nullptr, nullptr);

	TD_Button *tempBtn = new TD_Button(lpMe);
	tempBtn->CreateEx(0, WC_BUTTON, temp, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		x, y, nWidth, nHeight, hWnd, nullptr, 0);

	lpMe->_hWnd = tempBtn->m_hWnd;
	
	//带扩展标签的按钮
	if (CHK_FLAGS(lpMe->dwAttributes, SIA_EXLBL) && (lpMe->_hWnd))
	{
		tempBtn->SetEXLBLToAttributes(lpMe);
	}

	tempBtn->SetSoftSubItem(lpMe);
	vcButton.push_back(tempBtn);

	delete temp;
	return 0;
}

int TDItem::SubCtrl_RadioButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	char *temp = new char[30];
	WideCharToMultiByte(CP_ACP, 0, GetSoftItemTextByIndex(lpMe, nLangId), -1, temp, sizeof(char) * 30, nullptr, nullptr);

	if (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP))
		iValueforRadioID++;

	int radioID = 0;

	if (lpMe->dwStyle == SIS_RadioButtonEx)
	{
		radioID = iValueforRadioID * 1000 + lpMe->dwGroupIndex;
	}

	TD_Button *tempBtn = new TD_Button(lpMe);
	tempBtn->CreateEx(0, WC_BUTTON, temp, WS_CHILD | WS_VISIBLE | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | BS_OWNERDRAW | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
		x, y, nWidth, nHeight, hWnd, (HMENU)radioID, 0);

	lpMe->_hWnd = tempBtn->m_hWnd;

	tempBtn->SetSoftSubItem(lpMe);
	vcButton.push_back(tempBtn);

	delete temp;
	return 0;
}

int TDItem::SubCtrl_CheckButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	int nRet = 0;

	char *temp = new char[30];
	WideCharToMultiByte(CP_ACP, 0, GetSoftItemTextByIndex(lpMe, nLangId), -1, temp, sizeof(char) * 30, nullptr, nullptr);

	TD_Button *tempBtn = new TD_Button(lpMe);
	tempBtn->CreateEx(0, WC_BUTTON, temp, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | BS_OWNERDRAW,
		x, y, nWidth, nHeight, hWnd, nullptr, 0);

	lpMe->_hWnd = tempBtn->m_hWnd;

	if (lpMe->_hWnd)
	{
		if (CHK_FLAGS(lpMe->dwAttributes, SIA_GETCHKSTATE) && (lpMe->lpOpt[2]))
		{
			if (lpMe->lpOpt[12])
			{
				lpMe->lpOpt[2] = (void*)((DWORD)lpMe->lpOpt[2] - BASE);
				lpMe->lpOpt[12] = 0;
			}
			if (GetButtonCheckState(lpMe->lpOpt[2], (int)lpMe->lpOpt[3]))
			{
				SET_FLAGS(lpMe->dwAttributes, SIAE_CHECKED);
				Button_SetCheck(lpMe->_hWnd, BST_CHECKED);
			}
			else
			{
				NOT_FLAGS(lpMe->dwAttributes, SIAE_CHECKED);
				Button_SetCheck(lpMe->_hWnd, BST_UNCHECKED);
			}
		}
		else if (CHK_FLAGS(lpMe->dwAttributes, SIA_GETBTNSTATE) && (lpMe->lpOpt[2]))
		{
			int nOnOff = 0;

			if (lpMe->lpOpt[12])
			{
				lpMe->lpOpt[2] = (void*)((DWORD)lpMe->lpOpt[2] - BASE);
				lpMe->lpOpt[12] = 0;
			}
			GetButtonStateIndex((char *)lpMe->lpOpt[2], lpMe->lpOpt[3], &nOnOff, (int)lpMe->lpOpt[0]);

			if (GET_BYTE_0(nOnOff) != 0)
			{
				SET_FLAGS(lpMe->dwAttributes, SIAE_CHECKED);
				Button_SetCheck(lpMe->_hWnd, BST_CHECKED);
			}
			else
			{
				NOT_FLAGS(lpMe->dwAttributes, SIAE_CHECKED);
				Button_SetCheck(lpMe->_hWnd, BST_UNCHECKED);
			}
		}
		else if (CHK_FLAGS(lpMe->dwAttributes, SIAE_CHECKED))
			Button_SetCheck(lpMe->_hWnd, BST_CHECKED);

	}
	else
		nRet = -1;

	tempBtn->SetSoftSubItem(lpMe);
	vcButton.push_back(tempBtn);

	delete temp;
	return nRet;
}

int TDItem::SubCtrl_ComboButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	char *temp = new char[30];
	WideCharToMultiByte(CP_ACP, 0, GetSoftItemTextByIndex(lpMe, nLangId), -1, temp, sizeof(char) * 30, nullptr, nullptr);

	TD_Button *tempBtn = new TD_Button(lpMe);
	tempBtn->CreateEx(0, WC_BUTTON, temp, WS_CHILD | WS_VISIBLE | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | BS_OWNERDRAW,
		x, y, nWidth, nHeight, hWnd, nullptr, 0);

	lpMe->_hWnd = tempBtn->m_hWnd;

	TD_ComBoBtn *Comtmp = new TD_ComBoBtn(lpMe);
	if (lpMe->_hWnd)
	{
		RECT rect = { 0 };
		Comtmp->CreateEx(0, WC_COMBOBOX, 0, WS_CHILD | WS_VISIBLE | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL, rect, tempBtn, 0);
		lpMe->lpOpt[4] = Comtmp->m_hWnd;

		SubCtrl_ComboButton_UpdatePos(lpMe);
	}

	if ((Comtmp->m_hWnd) && (lpMe->dwNumberOfParams != 0) && (lpMe->lpParams != NULL))
	{
		if (!lpMe->dwReserve[3])	//wstring 和 原来的LPCWSTR切换语言方式不兼容诶!
		{
			for (DWORD dwIdx = 0; dwIdx < lpMe->dwNumberOfParams; dwIdx++)
			{
				LPCWSTR *lppWStr = (LPCWSTR *)lpMe->lpParams;
				char *ctemp = new char[20];
				WideCharToMultiByte(CP_ACP, 0, GetStringByIndex(lppWStr[dwIdx], nLangId), -1, ctemp, sizeof(char) * 20, nullptr, nullptr);
				Comtmp->InsertString(dwIdx, ctemp);
				delete ctemp;
			}
		}
		if (1 == lpMe->dwReserve[3])
		{
			wstring* lppWStr = (wstring*)lpMe->lpParams;
			CALKITOBJ stCalObj = { 0 };
			WCHAR pBuffer[100] = { 0 };
			for (DWORD dwIdx = 0; dwIdx < lpMe->dwNumberOfParams; dwIdx++)
			{
				stCalObj = cCalkit.GetCalKitName(dwIdx);
				if (0 == stCalObj.dwObjNameAdd)
				{
					char *ctemp = new char[20];
					WideCharToMultiByte(CP_ACP, 0, GetStringByIndex(lppWStr[dwIdx].c_str(), nLangId), -1, ctemp, sizeof(char) * 20, nullptr, nullptr);
					Comtmp->InsertString(dwIdx, ctemp);
					delete ctemp;
				}
				else
				{
					memset(pBuffer, 0, sizeof(WCHAR) * 100);
					MultiByteToWideChar(CP_ACP, 0, (LPCSTR)stCalObj.dwObjNameAdd, -1, pBuffer, lppWStr[dwIdx].size());
					lppWStr[dwIdx].assign(pBuffer);

					char *ctemp = new char[20];
					WideCharToMultiByte(CP_ACP, 0, GetStringByIndex(lppWStr[dwIdx].c_str(), nLangId), -1, ctemp, sizeof(char) * 20, nullptr, nullptr);
					Comtmp->InsertString(dwIdx, ctemp);
					delete ctemp;
				}
			}
		}
		Comtmp->SetCurSel(0);
	}

	tempBtn->SetSoftSubItem(lpMe);
	vcButton.push_back(tempBtn);

	delete temp;
	return 0;
}

int TDItem::SubCtrl_InputButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	char *temp = new char[20];
	WideCharToMultiByte(CP_ACP, 0, GetSoftItemTextByIndex(lpMe, nLangId), -1, temp, sizeof(char) * 20, nullptr, nullptr);

	TD_Button *tempBtn = new TD_Button(lpMe);
	tempBtn->CreateEx(0, WC_BUTTON, temp, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN |  BS_OWNERDRAW,
		x, y, nWidth, nHeight, hWnd, nullptr, 0);

	lpMe->_hWnd = tempBtn->m_hWnd;

	if (lpMe->_hWnd)
	{
		if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) || CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
		{
			//存在微调按钮

			if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) && CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
			{
				//同时存在2种微调按钮

				lpMe->lpOpt[5] = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE,
					0, 0, 0, 0,
					lpMe->_hWnd, NULL, hMod, NULL);

				if (lpMe->lpOpt[5])
					SetWindowLong((HWND)lpMe->lpOpt[5], GWL_USERDATA, SIA_FINETUNE);

				lpMe->lpOpt[6] = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE,
					0, 0, 0, 0,
					lpMe->_hWnd, NULL, hMod, NULL);

				if (lpMe->lpOpt[6])
					SetWindowLong((HWND)lpMe->lpOpt[6], GWL_USERDATA, SIA_FINETUNE2);
			}
			else
			{
				//存在单一一种微调按钮
				LONG lngUserData = 0;

				lpMe->lpOpt[5] = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, lpMe->_hWnd, NULL, hMod, NULL);

				if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE))
					lngUserData = SIA_FINETUNE;
				else if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
					lngUserData = SIA_FINETUNE2;

				if (lpMe->lpOpt[5])
					SetWindowLong((HWND)lpMe->lpOpt[5], GWL_USERDATA, lngUserData);
			}
		}

		TD_Edit *EditTmp = new TD_Edit(lpMe);

		EditTmp->CreateEx(WS_EX_CLIENTEDGE, WC_EDITA, 0, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | (CHK_FLAGS(lpMe->dwAttributes, SIA_READONLY) ? ES_READONLY : 0), 0, 0, 0, 0, lpMe->_hWnd, 0, 0);

		lpMe->lpOpt[4] = EditTmp->m_hWnd;

		SubCtrl_InputButton_UpdatePos(lpMe);
	}

	tempBtn->SetSoftSubItem(lpMe);
	vcButton.push_back(tempBtn);

	delete temp;
	return 0;
}

int TDItem::SubCtrl_StaticButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	if (lpMe->wHeight <= 20)
	{
		if (0 == lpMe->lpszItemText)
			lpMe->wHeight = 5;
		else
			lpMe->wHeight = 12;
	}

	nWidth -= 4;

	DWORD dwExStyle = 0;

	if (lpMe->lpszItemText == NULL)
	{
		dwExStyle = WS_EX_STATICEDGE;
	}

	char *temp = new char[30];
	WideCharToMultiByte(CP_ACP, 0, GetSoftItemTextByIndex(lpMe, nLangId), -1, temp, 30, nullptr, nullptr);

	TD_Button *tempBtn = new TD_Button(lpMe);
	tempBtn->CreateEx(dwExStyle, WC_STATIC, temp, WS_CHILD | WS_VISIBLE | SS_CENTER,
		x, rcItem.bottom, nWidth, lpMe->wHeight, hWnd, nullptr, 0);

	lpMe->_hWnd = tempBtn->m_hWnd;

	tempBtn->SetSoftSubItem(lpMe);
	vcButton.push_back(tempBtn);

	delete temp;
	return 0;
}

// TDItem 消息处理程序
LRESULT TDItem::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message)
	{
		case  WM_CREATE:
			TagPage_RefreshItems(0);
			break;

		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED)
			{
				wWidth_SoftItem = LOWORD(lParam);
				wHeight_SoftItem = HIWORD(lParam);

				TagPage_UpdateItemsPos();
			}
			break;

		case WM_KEYUP:
			{
				PSOFT_SUB_ITEM lpSubItem = &ssSumItem.at(dwFocusItem);
				if (lpSubItem->dwStyle != SIS_Delimiter)
				{
					switch (wParam)
					{
						case VK_F1:
							TagPage_ShowHelp(&ssSumItem.at(dwFocusItem));
							break;

						case VK_UP:
							SoftItem_PrevItem();
							break;

						case VK_DOWN:
							SoftItem_NextItem();
							break;

						case VK_RETURN:
							{
								switch (lpSubItem->dwStyle)
								{
									case SIS_InputButtonEx:
										{
											if (lpSubItem->lpOpt[4])
											{
												::SetFocus((HWND)lpSubItem->lpOpt[4]);
												::SelectAllText((HWND)lpSubItem->lpOpt[4]);
											}
											break;
										}
									case SIS_ComboButtonEx:
									case SIS_ComboRadioButtonEx:
										{
											if (lpSubItem->lpOpt[4])
											{
												::SetFocus((HWND)lpSubItem->lpOpt[4]);
												ComboBox_ShowDropdown((HWND)lpSubItem->lpOpt[4], TRUE);
											}
											break;
										}
									default:
										break;
								}
								break;
							}

						default:
							DefWindowProc(message, wParam, lParam);
							break;
					}
				}
			}

		case WM_COMMAND:
			{
				if (lParam)
				{
					WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);
					PSOFT_SUB_ITEM lpSubItem = GetItemByIndex((int)wId - 1000);

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

		case WM_REFRESH:	//刷新右侧按钮菜单事件
			{
				TagPage_RefreshItems(0);
				break;
			}

		case  WM_UPDATEMENU:
			{
				for (int i = 0; i < ssSumItem.size(); i++)
				{
					if (ssSumItem.at(i)._hWnd)
					{
						::InvalidateRect(ssSumItem.at(i)._hWnd, NULL, TRUE);
						::UpdateWindow(ssSumItem.at(i)._hWnd);
					}
				}
				InvalidateRect(NULL, TRUE);
				UpdateWindow();
			}

		case WM_FINETUNE:
			{
				SoftItem_Finetune(&ssSumItem.at(dwFocusItem), (int)wParam, (int)lParam);
				break;
			}

		case WM_DESTROY:
			{
				Sleep(0);
				break;
			}

		case WM_SETFOCUS:
			{
				uiCurFocusMenu = uiCurMenus;

				PSOFT_SUB_ITEM lpSubItem = NULL;

				if (dwFocusItem >= ssSumItem.size())
					dwFocusItem = 0;

				while (dwFocusItem < ssSumItem.size())
				{
					lpSubItem = &ssSumItem.at(dwFocusItem);

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
				}
				break;
			}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}