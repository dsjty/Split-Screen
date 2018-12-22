#include "stdafx.h"

WCHAR *wcOriePortChar[] = { L"None",L"A",L"B" ,L"C" ,L"D" };

static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;
	void *lpThis_Temp = nullptr;

	OrigSoftMenu_UpdateItems(CA_CAL_CAL_Resp_T);

	if (GetButtonCheckState((void*)0x00D661B8, 0))
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_UnT), BST_CHECKED);
	else	
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_UnT), BST_UNCHECKED);

	if (GetButtonCheckState((void*)0x00D66184, 0))
	{
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_ORT), BST_CHECKED);
		EnableWindow(GetDlgItem(hClient, IDC_CAL2_CMD_ORT_PORT1), 1);
		EnableWindow(GetDlgItem(hClient, IDC_CAL2_CMD_ORT_PORT2), 1);
	}
	else
	{
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_ORT), BST_UNCHECKED);
		EnableWindow(GetDlgItem(hClient, IDC_CAL2_CMD_ORT_PORT1), 0);
		EnableWindow(GetDlgItem(hClient, IDC_CAL2_CMD_ORT_PORT2), 0);
	}

	OrigSoftMenu_GetItemState(CA_ECAL_PORTCAL, 0, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_P1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	OrigSoftMenu_GetItemState(CA_ECAL_PORTCAL, 1, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_P1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

	OrigSoftMenu_GetItemState(CA_ECAL, 1, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_P2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

	OrigSoftMenu_GetItemState(CA_ECAL_THRUCAL, 0, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_RT_S21), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	OrigSoftMenu_GetItemState(CA_ECAL_THRUCAL, 1, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_RT_S12), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

	OrigSoftMenu_GetItemState(CA_ECAL_THRUCAL, 0, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_ER_S21), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	OrigSoftMenu_GetItemState(CA_ECAL_THRUCAL, 1, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL2_CMD_ER_S12), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

	OrigSoftMenu_Enter(CA_ECAL_CHAR);
	OrigSoftMenu_UpdateItems(CA_ECAL_CHAR);
	for (size_t i = 0; i < 6; i++)
	{
		OrigSoftMenu_GetItemState(CA_ECAL_CHAR, i, &blTmp, NULL, NULL);
		EnableWindow(GetDlgItem(hClient, 1300 + i), blTmp);
	}
}

INT_PTR WINAPI fndeCal_2(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL) 
		return -1;

	INT_PTR lResult = 0;

	switch (dwCode)
	{
	case DEC_ENTER:
	{
		int nOnOff = 0;

		OrigSoftMenu_Enter(CA_ECAL);
		OrigSoftMenu_UpdateItems(CA_ECAL);
		OrigSoftMenu_Enter(CA_ECAL_PORTCAL);
		OrigSoftMenu_UpdateItems(CA_ECAL_PORTCAL);
		OrigSoftMenu_Enter(CA_ECAL_THRUCAL);
		OrigSoftMenu_UpdateItems(CA_ECAL_THRUCAL);
		OrigSoftMenu_Enter(CA_ECAL_EnhRes);
		OrigSoftMenu_UpdateItems(CA_ECAL_EnhRes);
		OrigSoftMenu_Enter(CA_ECAL_ORIT);
		OrigSoftMenu_UpdateItems(CA_ECAL_ORIT);
		OrigSoftMenu_Enter(CA_ECAL_CHAR);
		OrigSoftMenu_UpdateItems(CA_ECAL_CHAR);

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_UnT), GetStringByIndex(L"Inknown Thru\0未知短接\0未知短接\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CZINF), GetStringByIndex(L"Characterization Info\0描绘信息\0描繪信息\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CONCHK), GetStringByIndex(L"Confidence Check\0可信度检查\0可信度檢查\0\0", nLangId));
		
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_GB_1PC), GetStringByIndex(L"1-Port Cal\0\x31端口校准\0\x31端口校準\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_P1), GetStringByIndex(L"Port 1\0端口1\0端口1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_P2), GetStringByIndex(L"Port 2\0端口2\0端口2\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_GB_2PC), GetStringByIndex(L"2-Port Cal\0\x32端口校准\0\x32端口校準\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_2PC), GetStringByIndex(L"2-Port Cal\0\x32端口校准\0\x32端口校準\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_GB_RT), GetStringByIndex(L"Response (Thru)\0响应短接\0響應短接\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_GB_ER), GetStringByIndex(L"Enhanced Response\0增强型响应\0增強型響應\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_GB_CTZ), GetStringByIndex(L"Characterization\0Characterization\0Characterization\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CT_FT), GetStringByIndex(L"Factory\0工厂\0工廠\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CT_USER1), GetStringByIndex(L"User1\0用户1\0用戶1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CT_USER2), GetStringByIndex(L"User2\0用户2\0用戶2\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CT_USER3), GetStringByIndex(L"User3\0用户3\0用戶3\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CT_USER4), GetStringByIndex(L"User4\0用户4\0用戶4\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_CT_USER5), GetStringByIndex(L"User5\0用户5\0用戶5\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_GB_OR), GetStringByIndex(L"Orientation\0Orientation\0Orientation\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_ORT), GetStringByIndex(L"Auto Orientation\0自动方向\0自動方向\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_ORT_PT1), GetStringByIndex(L"Port 1\0端口1\0端口1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_ORT_PT2), GetStringByIndex(L"Port 2\0端口2\0端口2\0\0", nLangId));

		for (int i = 0; i < ((PORTNUM == 4) ? 5 : 3); i++)
		{
			ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_ORT_PORT1), i, wcOriePortChar[i]);
			ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL2_CMD_ORT_PORT2), i, wcOriePortChar[i]);
		}

		UpdateButtonState((HWND)lParam2);
	}
	break;

	case DEC_CMD_OK:
		lResult = TRUE;
		break;

	case DEC_CMD_CANCEL:
		lResult = TRUE;
		break;

	case DEC_CMD_CLOSE:
		lResult = TRUE;
		break;
	}

	return lResult;
}

INT_PTR CALLBACK fndpCal_2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	void *lpThis_Temp = nullptr;

	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == BN_CLICKED)
			{
				switch (wId)
				{
				case IDC_CAL2_CMD_UnT:
					OrigSoftMenu_ItemClicked2(CA_ECAL, TA_ECAL, PORTNUM + 2);
					break;

				case IDC_CAL2_CMD_CZINF:
					OrigSoftMenu_ItemClicked2(CA_ECAL, TA_ECAL, PORTNUM + 4);
					break;

				case IDC_CAL2_CMD_CONCHK:
					OrigSoftMenu_ItemClicked2(CA_ECAL, TA_ECAL, PORTNUM + 5);
					break;

				case IDC_CAL2_CMD_CT_FT:
					OrigSoftMenu_ItemClicked2(CA_ECAL_CHAR, TA_ECAL_CHAR, 0);
					break;
				case IDC_CAL2_CMD_CT_USER1:
					OrigSoftMenu_ItemClicked2(CA_ECAL_CHAR, TA_ECAL_CHAR, 1);
					break;
				case IDC_CAL2_CMD_CT_USER2:
					OrigSoftMenu_ItemClicked2(CA_ECAL_CHAR, TA_ECAL_CHAR, 2);
					break;
				case IDC_CAL2_CMD_CT_USER3:
					OrigSoftMenu_ItemClicked2(CA_ECAL_CHAR, TA_ECAL_CHAR, 3);
					break;
				case IDC_CAL2_CMD_CT_USER4:
					OrigSoftMenu_ItemClicked2(CA_ECAL_CHAR, TA_ECAL_CHAR, 4);
					break;
				case IDC_CAL2_CMD_CT_USER5:
					OrigSoftMenu_ItemClicked2(CA_ECAL_CHAR, TA_ECAL_CHAR, 5);
					break;

				case IDC_CAL2_CMD_ORT:
					OrigSoftMenu_ItemClicked2(CA_ECAL_ORIT, TA_ECAL_ORIT, 0);
					break;

				case IDC_CAL2_CMD_RT_S21:
					OrigSoftMenu_ItemClicked2(CA_ECAL_THRUCAL, TA_ECAL_THRUCAL, 0);
					break;

				case IDC_CAL2_CMD_RT_S12:
					OrigSoftMenu_ItemClicked2(CA_ECAL_THRUCAL, TA_ECAL_THRUCAL, 1);
					break;

				case IDC_CAL2_CMD_ER_S21:
					OrigSoftMenu_ItemClicked2(CA_ECAL_EnhRes, TA_ECAL_EnhRes, 0);
					break;

				case IDC_CAL2_CMD_ER_S12:
					OrigSoftMenu_ItemClicked2(CA_ECAL_EnhRes, TA_ECAL_EnhRes, 1);
					break;

				case IDC_CAL2_CMD_P1:
					OrigSoftMenu_ItemClicked2(CA_ECAL_PORTCAL, TA_ECAL_PORTCAL, 0);
					break;

				case IDC_CAL2_CMD_P2:
					OrigSoftMenu_ItemClicked2(CA_ECAL_PORTCAL, TA_ECAL_PORTCAL, 1);
					break;

				case IDC_CAL2_CMD_2PC:
					OrigSoftMenu_ItemClicked2(CA_ECAL, TA_ECAL, PORTNUM - 1);
					break;
				}
			}
			if (wNc == CBN_SELCHANGE)
			{
				switch (wId)
				{
				case IDC_CAL2_CMD_ORT_PORT1:
				{
					lpThis_Temp = GetSubMenuPointer(CA_ECAL_ORIT, 1);
					OrigSoftMenu_Enter((void*)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Temp - BASE), (void**)((DWORD)lpThis_Temp - BASE), ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CAL2_CMD_ORT_PORT1)));
					break;
				}
				case IDC_CAL2_CMD_ORT_PORT2:
				{	
					lpThis_Temp = GetSubMenuPointer(CA_ECAL_ORIT, 2);
					OrigSoftMenu_Enter((void*)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Temp - BASE), (void**)((DWORD)lpThis_Temp - BASE), ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CAL2_CMD_ORT_PORT1)));
					break;
				}
				}
			}
		}
		UpdateButtonState(hDlg);
	}
	break;

	}

	return FALSE;
}

CALDLG_CTXT dcCal_2 =
{
	NULL,
	IDD_CAL_2,
	DFL_CMD_OK | DFL_LBL_INFO1,
	&fndeCal_2,
	&fndpCal_2,
	NULL,
	NULL,
	NULL,
	L"ECal\0电子校准\0電子校準\0\0",
	NULL,
	L"\0\0",
	NULL,
	NULL,
	NULL,
	L"Done\0完成\0完成\0\0",
	L"Exit\0退出\0退出\0\0",
	RESERVE_DWORD4,
	RESERVE_DWORD4
};