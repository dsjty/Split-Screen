#include "stdafx.h"

extern CALDLG_CTXT dcCal_1;

static void UpdateButtonState(HWND hClient);
static void ChangeCurPortNumber(int nPort);


INT_PTR WINAPI fndeCal_1_4(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
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
		OrigSoftMenu_Enter(CA_CAL_CAL_OnePCal);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);
		
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_OK), FALSE);
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_OK), FALSE);
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_GB_P1), GetStringByIndex(L"Port 1\0端口1\0端1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_GB_P2), GetStringByIndex(L"Port 2\0端口2 \0端口2\0\0", nLangId));

		ChangeCurPortNumber(0);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_O), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_S), GetStringByIndex(L"Short(f)\0短路器(f)\0短路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_L), GetStringByIndex(L"Load(f)\0负载(f)\0負載(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));


		ChangeCurPortNumber(1);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_O), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_S), GetStringByIndex(L"Short(f)\0短路器(f)\0短路器(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));

		lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
		if (lpThis_Temp)
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_L), GetStringByIndex(L"Load(f)\0负载(f)\0負載(f)\0\0", nLangId));
		else
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));


		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_O2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_S2), GetStringByIndex(L"Short(m)\0短路器(m)\0短路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_L2), GetStringByIndex(L"Load(m)\0负载(m)\0負載(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_O2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_S2), GetStringByIndex(L"Short(m)\0短路器(m)\0短路器(m)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_L2), GetStringByIndex(L"Load(m)\0负载(m)\0負載(m)\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P1_OK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL14_P2_OK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));

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
	OrigSoftMenu_Enter(CA_CAL_CAL_OnePCal);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

	void *lpThis = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 0);
	
	OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis - BASE), TA_CAL_CAL_OnePCal_SP, nPort);
}

static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;
	VOID *lpThis_Temp = nullptr;
	

	ChangeCurPortNumber(0);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);
	
	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_O2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL14_P1_O2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_S2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL14_P1_S2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 2, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}


	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_L2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL14_P1_L2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 3, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P1_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 4, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL14_P1_OK), blTmp);


	ChangeCurPortNumber(1);
	OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_O2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL14_P2_O2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_S2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL14_P2_S2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 2, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	
	lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_L2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		ShowWindow(GetDlgItem(hClient, IDC_CAL14_P2_L2), 0);
		OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 3, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL14_P2_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	OrigSoftMenu_GetItemState(CA_CAL_CAL_OnePCal, 4, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL14_P2_OK), blTmp);
}

INT_PTR CALLBACK fndpCal_1_4(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

	void *lpThis_Temp = nullptr;

	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_PAINT:
		return 0;
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
				case IDC_CAL14_P1_O:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
					if (lpThis_Temp)
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 0);
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 1);
					break;

				case IDC_CAL14_P1_O2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 1);
					break;
					
				case IDC_CAL14_P1_S:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
					if (lpThis_Temp)
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 0);
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 2);
					break;

				case IDC_CAL14_P1_S2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 1);
					break;


				case IDC_CAL14_P1_L:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
					if (lpThis_Temp)
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 0);
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 3);
					break;

				case IDC_CAL14_P1_L2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 1);
					break;

				case IDC_CAL14_P2_O:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
					if (lpThis_Temp)
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 0);
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 1);
					break;

				case IDC_CAL14_P2_O2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 1);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 1);
					break;

				case IDC_CAL14_P2_S:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
					if (lpThis_Temp)
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 0);
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 2);
					break;

				case IDC_CAL14_P2_S2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 2);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 1);
					break;


				case IDC_CAL14_P2_L:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
					if (lpThis_Temp)
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 0);
					else
						OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 3);
					break;

				case IDC_CAL14_P2_L2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);

					lpThis_Temp = GetSubMenuPointer(CA_CAL_CAL_OnePCal, 3);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), TA_CAL_CAL_OnePCal_OP, 1);
					break;

				case IDC_CAL14_P1_OK:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);
					OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 4);
					break;

				case IDC_CAL14_P2_OK:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems(CA_CAL_CAL_OnePCal);
					OrigSoftMenu_ItemClicked2(CA_CAL_CAL_OnePCal, TA_CAL_CAL_OnePCal, 4);
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


CALDLG_CTXT dcCal_1_4 =
{
	NULL,
	IDD_CAL_1_4,
	DFL_CMD_PREV | DFL_LBL_INFO1,
	&fndeCal_1_4,
	&fndpCal_1_4,
	NULL,
	NULL,
	NULL,
	L"Manual Calibration\0手动校准\0手動校準\0\0",
	L"1 Port Cal\0\x31端口校准\0\x31端口校準\0\0",
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	RESERVE_DWORD4
};