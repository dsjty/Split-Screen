#include "stdafx.h"

//Sub Control :: UpdatePos
int SubCtrl_RadioButton_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags)
{
	return 0;
}

int SubCtrl_RadioButton_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	lpMe->_hWnd = CreateWindowExW(0, WC_BUTTONW, GetSoftItemTextByIndex(lpMe, nLangId),
		WS_CHILD | WS_VISIBLE | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) |
		((lpMe->dwStyle == SIS_RadioButtonEx) ? BS_OWNERDRAW : BS_AUTORADIOBUTTON | BS_PUSHLIKE),
		x, y, nWidth, nHeight,
		hWnd, NULL, hMod, NULL);

	return 0;
}

LRESULT SubCtrl_RadioButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd)
{
	switch (lpSubItem->dwStyle)
	{
	case SIS_RadioButtonEx:
		SET_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED);
		break;
	}

	return 0;
}