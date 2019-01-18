#include "stdafx.h"



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
