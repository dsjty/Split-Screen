#include "stdafx.h"

//Sub Control :: UpdatePos
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags)
{
	if (lpMe == NULL) 
		return -1;

	if (CHK_FLAGS(lpMe->dwAttributes, SIA_EXLBL) && (lpMe->_hWnd) && (lpMe->lpOpt[4]))
	{
		RECT rcSub;

		GetClientRect(lpMe->_hWnd, &rcSub);

		rcSub.left += 9;

		if (rcSub.bottom - 30 <= 26)
			rcSub.top = 18;
		else if (rcSub.bottom - 30 > 38)
			rcSub.top = 20;
		else
			rcSub.top = rcSub.bottom - 30;

		MoveWindow((HWND)lpMe->lpOpt[4], rcSub.left, rcSub.top, rcSub.right - 18, rcSub.bottom - rcSub.top - 7, TRUE);
	}

	return 0;
}

//Sub Control :: Create
int SubCtrl_Button_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	lpMe->_hWnd = CreateWindowExW(0, WC_BUTTONW, GetSoftItemTextByIndex(lpMe, nLangId),
		WS_CHILD | WS_VISIBLE | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) |
		((lpMe->dwStyle == SIS_ButtonEx) ? BS_OWNERDRAW : 0),
		x, y, nWidth, nHeight,
		hWnd, NULL, hMod, NULL);

	//带扩展标签的按钮
	if (CHK_FLAGS(lpMe->dwAttributes, SIA_EXLBL) && (lpMe->_hWnd))
	{
		LPCWSTR lpText = NULL;

		if (lpMe->lpOpt[2])
		{
			LPCWSTR *lppWStr = (LPCWSTR *)lpMe->lpParams;

			int nIndex = 0;

			if (lpMe->lpOpt[12])
			{
				lpMe->lpOpt[2] = (void*)((DWORD)lpMe->lpOpt[2] - BASE);
				lpMe->lpOpt[12] = 0;
			}

			GetButtonStateIndex((char *)lpMe->lpOpt[2], lpMe->lpOpt[3], &nIndex, (int)lpMe->lpOpt[0]);

			if ((*lppWStr) && ((DWORD)nIndex < lpMe->dwNumberOfParams))
				lpText = GetStringByIndex(lppWStr[nIndex], nLangId);
		}

		lpMe->lpOpt[4] = CreateWindowExW(WS_EX_CLIENTEDGE, WC_STATICW, lpText, WS_CHILD | WS_VISIBLE | SS_CENTER,
			0, 0, 0, 0, lpMe->_hWnd, NULL, hMod, NULL);

		if (lpMe->lpOpt[4])
		{
			SubCtrl_Button_UpdatePos(lpMe, 0);
		}
	}

	return 0;
}

//Sub Control :: Event
LRESULT SubCtrl_Button_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd)
{
	return 0;
}