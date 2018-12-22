#include "stdafx.h"

void *lpThis_2PortCal = NULL;
void *lpThis_2PC_R = NULL;
void *lpThis_2PC_T = NULL;
void *lpThis_2PC_I = NULL;
BYTE btLastState = 0;

extern CALDLG_CTXT dcCal_1;

static void UpdateButtonState(HWND hClient);


INT_PTR WINAPI fndeCal_1_5(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL)
		return -1;

	INT_PTR lResult = 0;
	void *lpThis_Temp = nullptr;
	int iMenuindex = 0;

	switch (dwCode)
	{
	case DEC_ENTER:
		OrigSoftMenu_UpdateItems(CA_CALIBRAT);
		OrigSoftMenu_Enter(CA_CAL_CAL);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL);

		lpThis_2PortCal = GetSubMenuPointer(CA_CAL_CAL, 5);


		if (lpThis_2PortCal)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_2PortCal - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2PortCal - BASE));

			if (*(int*)((int)lpThis_2PortCal + 0x4) >= 0x7)
				iMenuindex++;

			lpThis_2PC_R = GetSubMenuPointer((void *)((DWORD)lpThis_2PortCal - BASE), iMenuindex++);
			if (lpThis_2PC_R)
			{
				OrigSoftMenu_Enter((void *)((DWORD)lpThis_2PC_R - BASE));
				OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2PC_R - BASE));
			}

			lpThis_2PC_T = GetSubMenuPointer((void *)((DWORD)lpThis_2PortCal - BASE), iMenuindex++);
			if (lpThis_2PC_T)
			{
				OrigSoftMenu_Enter((void *)((DWORD)lpThis_2PC_T - BASE));
				OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2PC_T - BASE));
			}

			lpThis_2PC_I = GetSubMenuPointer((void *)((DWORD)lpThis_2PortCal - BASE), iMenuindex++);
			if (lpThis_2PC_I)
			{
				OrigSoftMenu_Enter((void *)((DWORD)lpThis_2PC_I - BASE));
				OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2PC_I - BASE));
			}
		}

		EnableButton_Cal(DEC_CMD_OK, FALSE);

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_GB_P1), GetStringByIndex(L"Port1 Reflection\0端口1反射\0端口1反射\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_GB_P2), GetStringByIndex(L"Port2 Reflection\0端口2反射\0端口2反射\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_GB_TM), GetStringByIndex(L"Transmission\0传输\0傳輸\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_GB_P12), GetStringByIndex(L"Isolation(Optional)\0隔离(可选)\0隔離(可選)\0\0", nLangId));


		//PORT1
		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 0))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_O), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_O2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_O2), 0);
		}

		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 1))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_S), GetStringByIndex(L"Short(f)\0短路器(f)\0短路器(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_S2), GetStringByIndex(L"Short(m)\0短路器(m)\0短路器(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_S2), 0);
		}

		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 2))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_L), GetStringByIndex(L"Load(f)\0负载(f)\0負載(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_L2), GetStringByIndex(L"Load(m)\0负载(m)\0負載(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P1_L2), 0);
		}



		//PORT2
		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 3))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_O), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_O2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_O2), 3);
		}

		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 4))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_S), GetStringByIndex(L"Short(f)\0短路器(f)\0短路器(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_S2), GetStringByIndex(L"Short(m)\0短路器(m)\0短路器(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_S2), 4);
		}

		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 5))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_L), GetStringByIndex(L"Load(f)\0负载(f)\0負載(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_L2), GetStringByIndex(L"Load(m)\0负载(m)\0負載(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_P2_L2), 5);
		}

		//trans.....
		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_T - BASE), 0))
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_TM_T1), GetStringByIndex(L"Thru(f)\0短接(f)\0短接(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_TM_T2), GetStringByIndex(L"Thru(m)\0短接(m)\0短接(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_TM_T1), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));
			EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_TM_T2), 5);
		}

		//Isolation.....
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL15_CMD_TM_T1), GetStringByIndex(L"Isolation(Optional)\0隔离\0隔離\0\0", nLangId));


		UpdateButtonState((HWND)lParam2);
		SetTimer((HWND)lParam2, 1, 50, NULL);
		break;

	case DEC_CMD_PREV:
		KillTimer(lpDlgCtxt->hwClient, 1);
		UpdateDialog_Cal(&dcCal_1, 0);
		break;

	case DEC_CMD_OK:
	{
		if (lpThis_2PortCal == NULL)
		{
			lpThis_2PortCal = GetSubMenuPointer(CA_CAL_CAL, 5);

			if (lpThis_2PortCal)
			{
				OrigSoftMenu_Enter((void*)((DWORD)lpThis_2PortCal - BASE));
				OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PortCal - BASE));
			}
			else
				break;
		}

		OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_2PortCal - BASE), TA_CAL_CAL_TWOPCal, 3);
	}
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

inline void GetSubMenuPtr_R()
{
	if (lpThis_2PortCal)
	{
		lpThis_2PC_R = GetSubMenuPointer((void*)((DWORD)lpThis_2PortCal - BASE), 0);
	}
	else
	{
		lpThis_2PortCal = GetSubMenuPointer(CA_CAL_CAL, 5);

		if (lpThis_2PortCal)
		{
			OrigSoftMenu_Enter((void*)((DWORD)lpThis_2PortCal - BASE));
			OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PortCal - BASE));
			lpThis_2PC_R = GetSubMenuPointer((void*)((DWORD)lpThis_2PortCal - BASE), 0);
		}
	}
}

inline void GetSubMenuPtr_T()
{
	if (lpThis_2PortCal)
	{
		lpThis_2PC_T = GetSubMenuPointer((void*)((DWORD)lpThis_2PortCal - BASE), 1);
	}
	else
	{
		lpThis_2PortCal = GetSubMenuPointer(CA_CAL_CAL, 5);

		if (lpThis_2PortCal)
		{
			OrigSoftMenu_Enter((void*)((DWORD)lpThis_2PortCal - BASE));
			OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PortCal - BASE));
			lpThis_2PC_T = GetSubMenuPointer((void*)((DWORD)lpThis_2PortCal - BASE), 1);
		}
	}
}

inline void GetSubMenuPtr_I()
{
	if (lpThis_2PortCal)
	{
		lpThis_2PC_I = GetSubMenuPointer((void*)((DWORD)lpThis_2PortCal - BASE), 2);
	}
	else
	{
		lpThis_2PortCal = GetSubMenuPointer(CA_CAL_CAL, 5);

		if (lpThis_2PortCal)
		{
			OrigSoftMenu_Enter((void*)((DWORD)lpThis_2PortCal - BASE));
			OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PortCal - BASE));
			lpThis_2PC_I = GetSubMenuPointer((void*)((DWORD)lpThis_2PortCal - BASE), 2);
		}
	}
}

static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;
	void *lpThis_Temp = nullptr;

	if (!lpThis_2PortCal)
		lpThis_2PortCal = GetSubMenuPointer(CA_CAL_CAL, 5);

	if (lpThis_2PortCal)
	{
		OrigSoftMenu_Enter((void*)((DWORD)lpThis_2PortCal - BASE));
		OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PortCal - BASE));

		OrigSoftMenu_GetItemState((void*)((DWORD)lpThis_2PortCal - BASE), 3, &blTmp, NULL, NULL);
		EnableButton_Cal(DEC_CMD_OK, blTmp);
	}

	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PortCal - BASE));
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2PC_R - BASE));


	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_R - BASE), 0);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_O2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_P1_O2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_R - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_R - BASE), 1);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_S2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_P1_S2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_R - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_R - BASE), 2);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_L2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_P1_L2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_R - BASE), 2, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P1_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	//P2
	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_R - BASE), 3);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_O2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_P2_O2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_R - BASE), 3, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_O), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_R - BASE), 4);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_S2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_P2_S2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_R - BASE), 4, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_S), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_R - BASE), 5);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_L2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_P2_L2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_R - BASE), 5, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P2_L), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	//Tran....
	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_T - BASE), 0);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_TM_T1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_TM_T2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL15_CMD_TM_T2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_T - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_TM_T1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}

	//Isolation...
	lpThis_Temp = GetSubMenuPointer((void*)((DWORD)lpThis_2PC_I - BASE), 0);
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P12_I), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2PC_I - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL15_CMD_P12_I), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
}



INT_PTR CALLBACK fndpCal_1_5(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	void*	lpThis_Temp = nullptr;
	void*	lpThis_SP = nullptr;

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
				case IDC_CAL15_CMD_P1_O:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();

					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 0);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_R - BASE), TA_CAL_CAL_TWOPCal_R, 0);
					break;

				case IDC_CAL15_CMD_P1_O2:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 0);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL15_CMD_P1_S:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();

					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 1);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_R - BASE), TA_CAL_CAL_TWOPCal_R, 1);
					break;

				case IDC_CAL15_CMD_P1_S2:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 1);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL15_CMD_P1_L:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();

					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 2);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_R - BASE), TA_CAL_CAL_TWOPCal_R, 2);
					break;

				case IDC_CAL15_CMD_P1_L2:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 2);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL15_CMD_P2_O:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();

					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 3);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_R - BASE), TA_CAL_CAL_TWOPCal_R, 3);
					break;

				case IDC_CAL15_CMD_P2_O2:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 3);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL15_CMD_P2_S:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();

					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 4);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_R - BASE), TA_CAL_CAL_TWOPCal_R, 4);
					break;

				case IDC_CAL15_CMD_P2_S2:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 4);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL15_CMD_P2_L:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();

					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 5);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_R - BASE), TA_CAL_CAL_TWOPCal_R, 5);
					break;

				case IDC_CAL15_CMD_P2_L2:
					if (lpThis_2PC_R == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_R - BASE), 5);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL15_CMD_TM_T1:
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_T - BASE), 0);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_T - BASE), TA_CAL_CAL_TWOPCal_T, 0);
					break;

				case IDC_CAL15_CMD_TM_T2:
					if (lpThis_2PC_T == NULL)
						GetSubMenuPtr_R();
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_T - BASE), 0);
					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;


				case IDC_CAL15_CMD_P12_I:
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2PC_I - BASE), 0);
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2PC_I - BASE), TA_CAL_CAL_TWOPCal_I, 0);
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


CALDLG_CTXT dcCal_1_5 =
{
	NULL,
	IDD_CAL_1_5,
	DFL_CMD_PREV | DFL_CMD_OK | DFL_LBL_INFO1,
	&fndeCal_1_5,
	&fndpCal_1_5,
	NULL,
	NULL,
	NULL,
	L"Manual Calibration\0手动校准\0手動校準\0\0",
	L"2 Port Cal\0\x32端口校准\0\x32端口校準\0\0",
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	RESERVE_DWORD4
};