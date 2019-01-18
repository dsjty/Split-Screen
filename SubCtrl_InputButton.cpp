#include "stdafx.h"

//Sub Control :: UpdatePos
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe)
{
	if (lpMe == NULL) 
		return -1;

	if (lpMe->_hWnd)
	{
		RECT rcSub;

		GetClientRect(lpMe->_hWnd, &rcSub);

		rcSub.left += 8;
		rcSub.right -= 8;

		if (rcSub.bottom - 30 < 26)
			rcSub.top = 20;
		else
			rcSub.top = rcSub.bottom - 32;

		if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) || CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
		{
			//存在微调按钮
			LONG lngLeft;

			if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) && CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
			{
				//同时存在2种微调按钮
				rcSub.right -= 44;
				lngLeft = rcSub.right + 2;

				if (lpMe->lpOpt[5])
					MoveWindow((HWND)lpMe->lpOpt[5], lngLeft, rcSub.top - 3, 19, 18, TRUE);

				lngLeft += 21;

				if (lpMe->lpOpt[6])
					MoveWindow((HWND)lpMe->lpOpt[6], lngLeft, rcSub.top - 3, 19, 18, TRUE);

			}
			else
			{
				//存在单一一种微调按钮
				rcSub.right -= 22;
				lngLeft = rcSub.right + 2;

				if (lpMe->lpOpt[5])
					MoveWindow((HWND)lpMe->lpOpt[5], lngLeft, rcSub.top - 3, 19, 20, TRUE);
			}
		}

		if (lpMe->lpOpt[4])
			MoveWindow((HWND)lpMe->lpOpt[4], rcSub.left, rcSub.top, rcSub.right - rcSub.left, 20, TRUE);
	}

	return 0;
}
