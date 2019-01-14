#include "stdafx.h"

static LRESULT CALLBACK wp_ComboBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern CalKit cCalkit;

//Sub Control :: UpdatePos
int SubCtrl_ComboButton_UpdatePos(PSOFT_SUB_ITEM lpMe)
{
	if (lpMe == NULL)
		return -1;

	if ((lpMe->_hWnd) && (lpMe->lpOpt[4]))
	{
		RECT rcSub;

		GetClientRect(lpMe->_hWnd, &rcSub);

		rcSub.left += 6;

		if (rcSub.bottom - 30 < 26)
			rcSub.top = 20;
		else
			rcSub.top = rcSub.bottom - 32;

		MoveWindow((HWND)lpMe->lpOpt[4], rcSub.left, rcSub.top, rcSub.right - 12, 20, TRUE);
	}

	return 0;
}

int SubCtrl_ComboButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	HWND hCombo = NULL;

	if (lpMe->dwStyle == SIS_ComboButtonEx || lpMe->dwStyle == SIS_ComboRadioButtonEx)
	{
		lpMe->_hWnd = CreateWindowExW(0, WC_BUTTONW, GetSoftItemTextByIndex(lpMe, nLangId), WS_CHILD | WS_VISIBLE |
			(CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | BS_OWNERDRAW, x, y, nWidth, nHeight, hWnd, NULL, hMod, NULL);

		if (lpMe->_hWnd)
		{
			lpMe->lpOpt[4] = hCombo = CreateWindowExW(0, WC_COMBOBOXW, NULL, WS_CHILD | WS_VISIBLE |
				(CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL, 0, 0, 0, 0, lpMe->_hWnd, NULL, hMod, NULL);

			if (lpMe->lpOpt[4])
			{
				WNDPROC wpTmp = (WNDPROC)SetWindowLong((HWND)lpMe->lpOpt[4], GWL_WNDPROC, (LONG)&wp_ComboBox);

				if (wpfn_ComboBox == NULL)
					wpfn_ComboBox = wpTmp;
			}
			SubCtrl_ComboButton_UpdatePos(lpMe);
		}
	}
	if ((hCombo) && (lpMe->dwNumberOfParams != 0) && (lpMe->lpParams != NULL))
	{
		if (!lpMe->dwReserve[3])	//wstring 和 原来的LPCWSTR切换语言方式不兼容诶!
		{
			LPCWSTR *lppWStr = (LPCWSTR *)lpMe->lpParams;

			for (DWORD dwIdx = 0; dwIdx < lpMe->dwNumberOfParams; dwIdx++)
			{
				ComboBox_InsertStringW(hCombo, dwIdx, GetStringByIndex(lppWStr[dwIdx], nLangId));
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
					ComboBox_InsertStringW(hCombo, dwIdx, GetStringByIndex(lppWStr[dwIdx].c_str(), nLangId, lpMe->dwReserve[3]));
				else
				{
					memset(pBuffer, 0, sizeof(WCHAR) * 100);
					::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)stCalObj.dwObjNameAdd, -1, pBuffer, lppWStr[dwIdx].size());
					lppWStr[dwIdx].assign(pBuffer);
					ComboBox_InsertStringW(hCombo, dwIdx, GetStringByIndex(lppWStr[dwIdx].c_str(), nLangId, lpMe->dwReserve[3]));
				}
			}
		}
		ComboBox_SetCurSel(hCombo, 0);
	}
	return 0;
}

LRESULT SubCtrl_ComoboButton_OnClicked(PSOFT_SUB_ITEM lpSubItem,  HWND hWnd)
{
	if (lpSubItem->dwStyle == SIS_ComboRadioButtonEx)
		SET_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED);

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_SELECTED) && (lpSubItem->lpEvent[FNID_SELECTED]))
	{
		func_ItemEvent_Selected fnSelected = (func_ItemEvent_Selected)lpSubItem->lpEvent[FNID_SELECTED];

		fnSelected(0, 0, 0, lpSubItem, ComboBox_GetCurSel((HWND)lpSubItem->lpOpt[4]));

		UpdateCurrentItemsAndData();
	}

	return 0;
}

LRESULT CALLBACK wp_ComboBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch (msg)
	{
	case WM_CHAR:
	{
		HWND hItem = GetParent(hWnd);

		TDMenu *temp = nullptr;
		if (uiCurFocusMenu == 2)
			temp = cwMenuWnd2;
		else
			temp = cwMenuWnd;

		if (GetParent(hItem) != temp->GetItemHwnd())
		{
			if (wpfn_ComboBox)
				lResult = CallWindowProc(wpfn_ComboBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		switch (wParam)
		{
		case VK_SPACE:
			/*
			if (wpfn_ComboBox)
			lResult = CallWindowProc(wpfn_ComboBox, hWnd, msg, VK_RETURN, lParam);
			else
			lResult = DefWindowProc(hWnd, msg, VK_RETURN, lParam);

			SetFocus(hItem);
			*/

			//SNDMSG(hWnd, WM_CHAR, VK_RETURN, 0);

			keybd_event(VK_RETURN, 0, 0, 0);
			keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
			break;

		case VK_RETURN:
			if (wpfn_ComboBox)
				lResult = CallWindowProc(wpfn_ComboBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);

			SetFocus(hItem);
			break;

		default:
			if (wpfn_ComboBox)
				lResult = CallWindowProc(wpfn_ComboBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
	}
	break;

	default:
		if (wpfn_ComboBox)
			lResult = CallWindowProc(wpfn_ComboBox, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return lResult;
}