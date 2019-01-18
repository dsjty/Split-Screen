#include "stdafx.h"

//Sub Control :: UpdatePos
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe)
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