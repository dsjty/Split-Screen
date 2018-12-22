#include "stdafx.h"

//Sub Control :: UpdatePos
int SubCtrl_CheckButton_UpdatePos(PSOFT_SUB_ITEM lpMe, DWORD dwFlags)
{
	return 0;
}


int SubCtrl_CheckButton_Create(HWND hWnd, DWORD dwFlags, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	int nRet = 0;
	
	lpMe->_hWnd = CreateWindowExW(0, WC_BUTTONW, GetSoftItemTextByIndex(lpMe, nLangId),
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | BS_OWNERDRAW,
		x, y, nWidth, nHeight, hWnd, NULL, hMod, NULL);

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

	return nRet;
}

//Sub Control :: Event
LRESULT SubCtrl_CheckButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, int nCtrlId, HWND hWnd)
{
	UpdateCheckBoxState(lpSubItem);

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_UNCHECKFUNC))
	{
		//取消选中存在额外的函数
		if (CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED))
		{
			//当前已命中,执行"取消选中函数"
			if (lpSubItem->lpOpt[8] && lpSubItem->lpOpt[9])
			{
				if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOT_ENTER))
					OrigSoftMenu_Enter(lpSubItem->lpOpt[9]);

				OrigSoftMenu_ItemClicked2(lpSubItem->lpOpt[9], lpSubItem->lpOpt[8], (DWORD)lpSubItem->lpOpt[10]);
			}
		}
		else
		{
			//当前未命中,执行"选中函数"
			if (lpSubItem->lpVTable && lpSubItem->lpThis)
			{
				if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOT_ENTER))
					OrigSoftMenu_Enter(lpSubItem->lpThis);

				OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
			}
		}

		UpdateCheckBoxState(lpSubItem);
	}
	else
	{
		if (lpSubItem->lpVTable && lpSubItem->lpThis)
		{
			if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOT_ENTER))
				OrigSoftMenu_Enter(lpSubItem->lpThis);

			OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
		}

		UpdateCheckBoxState(lpSubItem);
	}

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_POPINPUTWND) && (lpSubItem->lpOpt[1]))
	{
		if (CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED))
		{
			DWORD dwFlags = 0;

			if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_FINETUNE))
				SET_FLAGS(dwFlags, SIA_FINETUNE);

			if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_FINETUNE2))
				SET_FLAGS(dwFlags, SIA_FINETUNE2);

			PopWnd_PopupInputBox(hwMainWnd, GetStringByIndex(lpSubItem->lpszItemText, nLangId),
				lpSubItem->lpOpt[1], lpSubItem, dwFlags);
		}
		else
			PopWnd_Destroy(lpSubItem, FALSE);

	}

	return 0;
}
