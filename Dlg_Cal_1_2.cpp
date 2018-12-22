#include "stdafx.h"

extern CALDLG_CTXT dcCal_1;
void *lpThis_RT = NULL;
void *lpThis_RT_SP = nullptr;

static void UpdateButtonState(HWND hClient);

INT_PTR WINAPI fndeCal_1_2(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL) 
		return -1;

	INT_PTR lResult = 0;
	void *lpThis_Temp = nullptr;

	switch (dwCode)
	{
	case DEC_ENTER:
		OrigSoftMenu_UpdateItems(CA_CALIBRAT);
		OrigSoftMenu_Enter(CA_CAL_CAL);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL);

		OrigSoftMenu_Enter(CA_CAL_CAL_Resp_T);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_OK), FALSE);
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_OK), FALSE);
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_GB_P21), GetStringByIndex(L"Port 2-1 (S21)\0端口2-1 (S21)\0端口2-1 (S21)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_GB_P12), GetStringByIndex(L"Port 1-2 (S12)\0端口1-2 (S12)\0端口1-2 (S12)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_OK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_OK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));
		
		//检测THRU和ISO等是否有下级菜单
		//THRu检测
		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
		if (lpThis_Temp)
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_T2), GetStringByIndex(L"Thru2\0短接2\0短接2\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_T2), GetStringByIndex(L"Thru2\0短接2\0短接2\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_T2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_T2), 0);
		}

		//Isolation检测
		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
		if (lpThis_Temp)
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_I), GetStringByIndex(L"Isolation (Optional)\0隔离 (可选)\0隔離 (可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_I), GetStringByIndex(L"Isolation (Optional)\0隔离 (可选)\0隔離 (可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_I2), GetStringByIndex(L"Isolation2 (Optional)\0隔离2(可选)\0隔離2(可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_I2), GetStringByIndex(L"Isolation2 (Optional)\0隔离2(可选)\0隔離2(可選)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_I), GetStringByIndex(L"Isolation (Optional)\0隔离 (可选)\0隔離 (可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_I), GetStringByIndex(L"Isolation (Optional)\0隔离 (可选)\0隔離 (可選)\0\0", nLangId));
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL12_P21_I2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL12_P12_I2), 0);
		}		

		UpdateButtonState((HWND)lParam2);
		SetTimer((HWND)lParam2, 1, 100, NULL);
		break;

	case DEC_CMD_PREV:
		KillTimer(lpDlgCtxt->hwClient, 1);
		UpdateDialog_Cal(&dcCal_1, 0);
		break;

	case DEC_CMD_CANCEL:
	{
		LPCWSTR lpText = GetStringByIndex(L"Whether to cancel the calibration data?\0是否取消校准数据?\0是否取消校準數據?\0\0", nLangId);
		LPCWSTR lpTitle = GetStringByIndex(L"Confirm the cancellation\0确认取消操作\0確認取消操作\0\0", nLangId);

		if (DialogMsgBox_Cal(lpText, lpTitle, MB_YESNO) == IDYES)
		{
			OrigSoftMenu_Enter(CA_CAL_CAL_XX_CANCEL);
			OrigSoftMenu_UpdateItems(CA_CAL_CAL_XX_CANCEL);

			OrigSoftMenu_ItemClicked2(CA_CAL_CAL_XX_CANCEL, TA_CAL_CAL_XX_CANCEL, 0);

			UpdateButtonState(lpDlgCtxt->hwClient);
		}
	}

	break;

	case DEC_CMD_CLOSE:
		KillTimer(lpDlgCtxt->hwClient, 1);
		lResult = TRUE;
		break;
	}

	return lResult;
}

static void ChangeCurPortNumber(int nPort)
{
	OrigSoftMenu_Enter(CA_CAL_CAL_Resp_T);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

	if (lpThis_RT_SP == NULL)
		lpThis_RT_SP = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 0);

	if (nullptr == lpThis_RT_SP)
	{
		OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 0);
		return;
	}

	OrigSoftMenu_Enter((void *)((DWORD)lpThis_RT_SP - BASE));
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RT_SP - BASE));

	OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RT_SP - BASE), TA_CAL_CAL_Resp_T_SP, nPort);
}

static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;
	void *lpThis_Temp = nullptr;

	OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

	//端口2-1
	ChangeCurPortNumber(0);
	OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 1, NULL, &blTmp, NULL);

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_T), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_T), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_T2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_T2), BST_UNCHECKED);
	}
	else
	{
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_T), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_T), BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_I), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_I), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_I2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_I2), BST_UNCHECKED);
	}
	else
	{
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 2, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_I), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P21_I), BST_UNCHECKED);
	}

	OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 3, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL12_P21_OK), blTmp);



	//端口1-2
	ChangeCurPortNumber(1);

	OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 1, NULL, &blTmp, NULL);

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_T), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_T), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_T2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_T2), BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL12_P12_T2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_T), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_T), BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_I), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_I), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_I2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_I2), BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL12_P12_I2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 2, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_I), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL12_P12_I), BST_UNCHECKED);
	}

	OrigSoftMenu_GetItemState(CA_CAL_CAL_Resp_T, 3, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL12_P12_OK), blTmp);

}


INT_PTR CALLBACK fndpCal_1_2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	void *lpThis_Temp = nullptr;
	void * lpThis_SP = nullptr;

	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_TIMER:
		if (wParam == 1)
		{
			UpdateButtonState(hDlg);
			return 0;
		}
		break;

	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == BN_CLICKED)
			{
				switch (wId)
				{
				case IDC_CAL12_P21_T:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 1);
					break;

				case IDC_CAL12_P21_T2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL12_P21_I:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 2);
					break;

				case IDC_CAL12_P21_I2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL12_P12_T:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 1);
					break;

				case IDC_CAL12_P12_T2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 1);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL12_P12_I:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 2);
					break;


				case IDC_CAL12_P12_I2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Resp_T, 2);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL12_P21_OK:
					ChangeCurPortNumber(0);
					OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 3);
					break;

				case IDC_CAL12_P12_OK:
					ChangeCurPortNumber(1);
					OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Resp_T, TA_CAL_CAL_Resp_T, 3);
					break;
				}

				UpdateButtonState(hDlg);
			}
		}
	}
	break;
	}

	return FALSE;
}


CALDLG_CTXT dcCal_1_2 =
{
	NULL,
	IDD_CAL_1_2,
	DFL_CMD_PREV | DFL_LBL_INFO1,
	&fndeCal_1_2,
	&fndpCal_1_2,
	NULL,
	NULL,
	NULL,
	L"Manual Calibration\0手动校准\0手動校準\0\0",
	L"Response (Thru)\0响应 (短接)\0響應 (短接)\0\0",
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	RESERVE_DWORD4
};