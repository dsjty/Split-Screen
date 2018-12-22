#include "stdafx.h"

extern CALDLG_CTXT dcCal_1;

static void UpdateButtonState(HWND hClient);
static void ChangeCurPortNumber(int nPort);


INT_PTR WINAPI fndeCal_1_3(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL) 
		return -1;
	void *lpThis_Temp = nullptr;

	INT_PTR lResult = 0;

	switch (dwCode)
	{
	case DEC_ENTER:
		OrigSoftMenu_UpdateItems(CA_CALIBRAT);
		OrigSoftMenu_Enter(CA_CAL_CAL);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL);
		OrigSoftMenu_Enter(CA_CAL_CAL_Enh);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);
		
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_OK), FALSE);
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_OK), FALSE);

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_GB_P21), GetStringByIndex(L"Port 2-1 (S21 S11)\0端口2-1 (S21 S11)\0端口2-1 (S21 S11)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_GB_P12), GetStringByIndex(L"Port 1-2 (S12 S22)\0端口1-2 (S12 S22)\0端口1-2 (S12 S22)\0\0", nLangId));

		ChangeCurPortNumber(0);

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_O), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_S), GetStringByIndex(L"Short(f)\0短路器(f)\0短路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_L), GetStringByIndex(L"Load(f)\0负载(f)\0負載(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_T), GetStringByIndex(L"Thru(f)\0短接(f)\0短接(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_I), GetStringByIndex(L"Isolation(f)(Optional)\0隔离(f)(可选)\0隔離(f)(可選)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_I), GetStringByIndex(L"Isolation (Optional)\0隔离 (可选)\0隔離 (可選)\0\0", nLangId));

		ChangeCurPortNumber(1);

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_O), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_S), GetStringByIndex(L"Short(f)\0短路器(f)\0短路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_L), GetStringByIndex(L"Load(f)\0负载(f)\0負載(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_T), GetStringByIndex(L"Thru(f)\0短接(f)\0短接(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_I), GetStringByIndex(L"Isolation(f)(Optional)\0隔离(f)(可选)\0隔離(f)(可選)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_I), GetStringByIndex(L"Isolation (Optional)\0隔离 (可选)\0隔離 (可選)\0\0", nLangId));
		
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_O2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_S2), GetStringByIndex(L"Short(m)\0短路器(m)\0短路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_L2), GetStringByIndex(L"Load(m)\0负载(m)\0負載(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_T2), GetStringByIndex(L"Thru(m)\0短接(m)\0短接(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_I2), GetStringByIndex(L"Isolation(m)(Optional)\0隔离(m)(可选)\0隔離(m)(可選)\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_O2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_S2), GetStringByIndex(L"Short(m)\0短路器(m)\0短路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_L2), GetStringByIndex(L"Load(m)\0负载(m)\0負載(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_T2), GetStringByIndex(L"Thru(m)\0短接(m)\0短接(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_I2), GetStringByIndex(L"Isolation(m)(Optional)\0隔离(m)(可选)\0隔離(m)(可選)\0\0", nLangId));
		
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P21_OK),			GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL13_P12_OK),			GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));

		UpdateButtonState((HWND)lParam2);
		SetTimer((HWND)lParam2, 1, 50, NULL);
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
	OrigSoftMenu_Enter(CA_CAL_CAL_Enh_SP);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh_SP);

	OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh_SP, TA_CAL_CAL_Enh_SP, nPort);
}

static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;
	VOID *lpThis_Temp = nullptr;


	ChangeCurPortNumber(0);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_O2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P21_O2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_S2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P21_S2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 2, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_L2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P21_L2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 3, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_T), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_T2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P21_T2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 4, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_T), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_I), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_I2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P21_I2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 5, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P21_I), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 6, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL13_P21_OK), blTmp);


	ChangeCurPortNumber(1);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_O2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P12_O2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_S2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P12_S2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 2, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_L2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P12_L2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 3, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_T), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_T2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P12_T2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 4, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_T), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_I), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_I2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL13_P12_I2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 5, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL13_P12_I), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	OrigSoftMenu_GetItemState(CA_CAL_CAL_Enh, 6, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL13_P12_OK), blTmp);
}


INT_PTR CALLBACK fndpCal_1_3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	void *lpThis_Temp = nullptr, *lpThis_SP = nullptr;

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
				case IDC_CAL13_P21_O:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 1);
					break;

				case IDC_CAL13_P21_O2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P21_S:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 2);
					break;

				case IDC_CAL13_P21_S2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P21_L:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 3);
					break;

				case IDC_CAL13_P21_L2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P21_T:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 4);
					break;

				case IDC_CAL13_P21_T2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P21_I:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 5);
					break;

				case IDC_CAL13_P21_I2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;


				case IDC_CAL13_P12_O:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 1);
					break;

				case IDC_CAL13_P12_O2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 1);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P12_S:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 2);
					break;

				case IDC_CAL13_P12_S2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 2);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P12_L:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 3);
					break;

				case IDC_CAL13_P12_L2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 3);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P12_T:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 4);
					break;

				case IDC_CAL13_P12_T2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 4);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P12_I:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 5);
					break;

				case IDC_CAL13_P12_I2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_Enh);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_Enh, 5);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL13_P21_OK:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(TA_CAL_CAL_Enh);
					OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 6);
					break;

				case IDC_CAL13_P12_OK:
					ChangeCurPortNumber(1);			
					OrigSoftMenu_UpdateItems(TA_CAL_CAL_Enh);
					OrigSoftMenu_ItemClicked2(CA_CAL_CAL_Enh, TA_CAL_CAL_Enh, 6);
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


CALDLG_CTXT dcCal_1_3 =
{
	NULL,
	IDD_CAL_1_3,
	DFL_CMD_PREV | DFL_LBL_INFO1,
	&fndeCal_1_3,
	&fndpCal_1_3,
	NULL,
	NULL,
	NULL,
	L"Manual Calibration\0手动校准\0手動校準\0\0",
	L"Enhanced Response\0增强型响应\0增強型響應\0\0",
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	RESERVE_DWORD4
};