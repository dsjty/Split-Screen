#include "stdafx.h"
extern CALDLG_CTXT dcCal_1;

void *lpThis_2TRLCal = NULL;
void *lpThis_2TRLCal_TL = NULL;
void *lpThis_2TRLCal_REF = NULL;
void *lpThis_2TRLCal_LM = NULL;


bool nBtnSer = 0;	//4端口比2端口 多了一个端口选择菜单




static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;
	PMENUPTRSTR lpThis_Temp = nullptr, lpThis_Temp2 = nullptr;

	if (!lpThis_2TRLCal)
		lpThis_2TRLCal = GetSubMenuPointer(CA_CAL_CAL, PORTNUM + 4);

	lpThis_Temp = (PMENUPTRSTR)lpThis_2TRLCal_TL;

	OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
	Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_TL_12TL), (blTmp) ? BST_CHECKED : BST_UNCHECKED);


	lpThis_Temp = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 0);

	if ((void*)lpThis_Temp)
	{
		lpThis_Temp = (PMENUPTRSTR)lpThis_2TRLCal_REF;
		lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 0);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_P1R_R1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_P1R_R2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

		lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 1);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_P2R_R1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_P2R_R2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_P1R_R1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_P2R_R1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}


	lpThis_Temp = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);

	if ((void*)lpThis_Temp)
	{
		lpThis_Temp = (PMENUPTRSTR)lpThis_2TRLCal_LM;

		lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 0);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));

		switch (lpThis_Temp2->MenuNum)
		{
		case 2:
		{
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

			lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 1);
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

			lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 2);
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			break;
		}
		case 4:
		{
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 2, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 3, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

			lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 1);
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 2, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 3, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

			lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 2);
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 2, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 3, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			break;
		}
		case 6:
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 2, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 3, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 4, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 5, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

			lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 1);
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 2, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 3, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 4, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 5, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);

			lpThis_Temp2 = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 2);
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp2 - BASE));
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 0, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 1, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 2, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 3, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 4, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp2 - BASE), 5, NULL, &blTmp, NULL);
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM2), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
			break;
		}
	}
	else
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12LM_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12FD_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2, NULL, &blTmp, NULL);
		Button_SetCheck(GetDlgItem(hClient, IDC_CAL16_CMD_12Rs_LM1), (blTmp) ? BST_CHECKED : BST_UNCHECKED);
	}
}



INT_PTR WINAPI fndeCal_1_6(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL)
		return -1;

	if (PORTNUM == 4)
		nBtnSer = true;
	else
		nBtnSer = false;

	INT_PTR lResult = 0;
	void *lpThis_Temp = nullptr, *lpThis_Temp2 = nullptr;
	;
	int iMenuindex = 0;

	switch (dwCode)
	{
	case DEC_ENTER:
		OrigSoftMenu_UpdateItems(CA_CALIBRAT);
		OrigSoftMenu_Enter(CA_CAL_CAL);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL);

		lpThis_2TRLCal = GetSubMenuPointer(CA_CAL_CAL, 3 + PORTNUM + 1);
		
		if (lpThis_2TRLCal)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_2TRLCal - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2TRLCal - BASE));
		}

		lpThis_2TRLCal_TL = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal - BASE), nBtnSer + 0);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_2TRLCal_TL - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2TRLCal_TL - BASE));

		lpThis_2TRLCal_REF = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal - BASE), nBtnSer + 1);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_2TRLCal_REF - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2TRLCal_REF - BASE));

		lpThis_2TRLCal_LM = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal - BASE), nBtnSer + 2);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_2TRLCal_LM - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2TRLCal_LM - BASE));


		EnableButton_Cal(DEC_CMD_OK, FALSE);

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_GB_TL), GetStringByIndex(L"Thru/Line\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_GB_REF), GetStringByIndex(L"Port1 Reflection\0端口1反射\0端口1反射\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_GB_REF2), GetStringByIndex(L"Port2 Reflection\0端口2反射\0端口2反射\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_GB_12LM), GetStringByIndex(L"1-2 Line/Match\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_GB_12Fd), GetStringByIndex(L"1-2 Fwd(S21)\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_GB_12Rs), GetStringByIndex(L"1-2 Rvs(S12)\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_TL_12TL), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));

		//reflect
		if (lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal - BASE), nBtnSer + 1))
		{
			if (lpThis_Temp2 = GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 0))
			{
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P1R_R1), GetStringByIndex(L"Reflect 1\0\0", nLangId));
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P1R_R2), GetStringByIndex(L"Reflect 2\0\0", nLangId));
			}
			else
			{
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P1R_R1), GetStringByIndex(L"Reflect 1\0\0", nLangId));
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P1R_R2), 0);
			}

			if (lpThis_Temp2 = GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 1))
			{
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P2R_R1), GetStringByIndex(L"Reflect 1\0\0", nLangId));
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P2R_R2), GetStringByIndex(L"Reflect 2\0\0", nLangId));
			}
			else
			{
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P2R_R1), GetStringByIndex(L"Reflect 1\0\0", nLangId));
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P2R_R2), 0);
			}
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P1R_R1), GetStringByIndex(L"Reflect 1\0\0", nLangId));
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_P1R_R2), 0);
		}


		//Line/Match
		lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal - BASE), nBtnSer + 2);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));
		if (lpThis_Temp)
		{
			void *lpThisTemp = GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE),0);
			
			if (lpThisTemp)
			{
				OrigSoftMenu_Enter((void *)((DWORD)lpThisTemp - BASE));
				OrigSoftMenu_UpdateItems((void *)((DWORD)lpThisTemp - BASE));
				PMENUPTRSTR lpSubMenu = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpThis_Temp - BASE), 0);
				
				switch (lpSubMenu->MenuNum)
				{
				case 2:
				{
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM3), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM4), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM5), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM6), 0);
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM3), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM4), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM5), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM6), 0);
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM3), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM4), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM5), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM6), 0);
					break;
				}
				case 4:
				{
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM3), GetStringByIndex(L"Line/Match 3\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM4), GetStringByIndex(L"Line/Match 4\0\0", nLangId));
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM5), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM6), 0);
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM3), GetStringByIndex(L"Line/Match 3\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM4), GetStringByIndex(L"Line/Match 4\0\0", nLangId));
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM5), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM6), 0);
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM3), GetStringByIndex(L"Line/Match 3\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM4), GetStringByIndex(L"Line/Match 4\0\0", nLangId));
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM5), 0);
					ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM6), 0);
					break;
				}
				case 6:
				{
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM3), GetStringByIndex(L"Line/Match 3\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM4), GetStringByIndex(L"Line/Match 4\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM5), GetStringByIndex(L"Line/Match 5\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM6), GetStringByIndex(L"Line/Match 6\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM3), GetStringByIndex(L"Line/Match 3\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM4), GetStringByIndex(L"Line/Match 4\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM5), GetStringByIndex(L"Line/Match 5\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM6), GetStringByIndex(L"Line/Match 6\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM2), GetStringByIndex(L"Line/Match 2\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM3), GetStringByIndex(L"Line/Match 3\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM4), GetStringByIndex(L"Line/Match 4\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM5), GetStringByIndex(L"Line/Match 5\0\0", nLangId));
					SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM6), GetStringByIndex(L"Line/Match 6\0\0", nLangId));
					break;
				}
				default:
					break;
				}
			}
			else
			{
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM2), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM3), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM4), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM5), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM6), 0);
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM2), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM3), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM4), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM5), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM6), 0);
				SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM2), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM3), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM4), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM5), 0);
				ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12Rs_LM6), 0);
			}
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM1), GetStringByIndex(L"Line/Match 1\0\0", nLangId));
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM3), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM4), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM5), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12LM_LM6), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM1), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM3), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM4), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM5), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM6), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM1), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM3), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM4), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM5), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL16_CMD_12FD_LM6), 0);
		}
		
		UpdateButtonState((HWND)lParam2);
		SetTimer((HWND)lParam2, 1, 100, NULL);
		break;

	case DEC_CMD_PREV:
		KillTimer(lpDlgCtxt->hwClient, 1);
		UpdateDialog_Cal(&dcCal_1, 0);
		break;

	case DEC_CMD_OK:
	{
		if (lpThis_2TRLCal == NULL)
		{
			lpThis_2TRLCal = GetSubMenuPointer(CA_CAL_CAL, 4 + PORTNUM);

			if (lpThis_2TRLCal)
			{
				OrigSoftMenu_Enter((void*)((DWORD)lpThis_2TRLCal - BASE));
				OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_2TRLCal - BASE));
			}
			else
				break;
		}

		OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_2TRLCal - BASE), TA_CAL_CAL_2TRLCal, nBtnSer + 3);
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


INT_PTR CALLBACK fndpCal_1_6(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	void *lpThis_Temp = nullptr, *lpThis_Temp2 = nullptr;
	void *lpThis_SP = nullptr;
	PMENUPTRSTR lpSubMenuPTR = NULL;

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
				case IDC_CAL16_CMD_TL_12TL:
				{
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_2TRLCal_TL - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_2TRLCal_TL - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2TRLCal_TL - BASE), (void **)((DWORD)lpThis_2TRLCal_TL - BASE), 0);

					break;
				}
				case IDC_CAL16_CMD_P1R_R1:
				{
					lpSubMenuPTR = (PMENUPTRSTR)lpThis_2TRLCal_REF;
					OrigSoftMenu_Enter((void *)((DWORD)lpSubMenuPTR - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpSubMenuPTR - BASE));

					lpSubMenuPTR = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpSubMenuPTR - BASE), 0);
					if ((void*)lpSubMenuPTR)
					{
						lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 0);

						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 0);
					}
					else
					{
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2TRLCal_REF - BASE), (void **)((DWORD)lpThis_2TRLCal_REF - BASE), 0);
					}
					break;
				}
				case IDC_CAL16_CMD_P1R_R2:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 0);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 1);

					break;
				}
				case IDC_CAL16_CMD_P2R_R1:
				{
					lpSubMenuPTR = (PMENUPTRSTR)lpThis_2TRLCal_REF;
					OrigSoftMenu_Enter((void *)((DWORD)lpSubMenuPTR - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpSubMenuPTR - BASE));

					lpSubMenuPTR = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpSubMenuPTR - BASE), 0);
					if ((void*)lpSubMenuPTR)
					{
						lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 1);
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 0);
					}
					else
					{
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2TRLCal_REF - BASE), (void **)((DWORD)lpThis_2TRLCal_REF - BASE), 1);
					}
					break;
				}
				case IDC_CAL16_CMD_P2R_R2:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_REF - BASE), 1);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 1);

					break;
				}

				case IDC_CAL16_CMD_12LM_LM1:
				{
					lpSubMenuPTR = (PMENUPTRSTR)lpThis_2TRLCal_LM;
					OrigSoftMenu_Enter((void *)((DWORD)lpSubMenuPTR - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpSubMenuPTR - BASE));

					lpSubMenuPTR = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpSubMenuPTR - BASE), 0);
					if ((void*)lpSubMenuPTR)
					{
						lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
						OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 0);
					}
					else
					{
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2TRLCal_LM - BASE), (void **)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					}
					break;
				}
				case IDC_CAL16_CMD_12LM_LM2:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 1);

					break;
				}
				case IDC_CAL16_CMD_12LM_LM3:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 2);

					break;
				}
				case IDC_CAL16_CMD_12LM_LM4:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 3);

					break;
				}
				case IDC_CAL16_CMD_12LM_LM5:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 4);

					break;
				}
				case IDC_CAL16_CMD_12LM_LM6:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 5);

					break;
				}

				case IDC_CAL16_CMD_12FD_LM1:
				{
					lpSubMenuPTR = (PMENUPTRSTR)lpThis_2TRLCal_LM;
					OrigSoftMenu_Enter((void *)((DWORD)lpSubMenuPTR - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpSubMenuPTR - BASE));

					lpSubMenuPTR = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpSubMenuPTR - BASE), 0);
					if ((void*)lpSubMenuPTR)
					{
						lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1);
						OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 0);
					}
					else
					{
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2TRLCal_LM - BASE), (void **)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					}
					break;
				}
				case IDC_CAL16_CMD_12FD_LM2:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 1);

					break;
				}
				case IDC_CAL16_CMD_12FD_LM3:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 2);

					break;
				}
				case IDC_CAL16_CMD_12FD_LM4:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 3);

					break;
				}
				case IDC_CAL16_CMD_12FD_LM5:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 4);

					break;
				}
				case IDC_CAL16_CMD_12FD_LM6:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 1);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 5);

					break;
				}


				case IDC_CAL16_CMD_12Rs_LM1:
				{
					lpSubMenuPTR = (PMENUPTRSTR)lpThis_2TRLCal_LM;
					OrigSoftMenu_Enter((void *)((DWORD)lpSubMenuPTR - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpSubMenuPTR - BASE));

					lpSubMenuPTR = (PMENUPTRSTR)GetSubMenuPointer((void *)((DWORD)lpSubMenuPTR - BASE), 0);
					if ((void*)lpSubMenuPTR)
					{
						lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2);
						OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 0);
					}
					else
					{
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_2TRLCal_LM - BASE), (void **)((DWORD)lpThis_2TRLCal_LM - BASE), 0);
					}
					break;
				}
				case IDC_CAL16_CMD_12Rs_LM2:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 1);

					break;
				}
				case IDC_CAL16_CMD_12Rs_LM3:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 2);

					break;
				}
				case IDC_CAL16_CMD_12Rs_LM4:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 3);

					break;
				}
				case IDC_CAL16_CMD_12Rs_LM5:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 4);

					break;
				}
				case IDC_CAL16_CMD_12Rs_LM6:
				{
					lpThis_Temp = GetSubMenuPointer((void *)((DWORD)lpThis_2TRLCal_LM - BASE), 2);
					OrigSoftMenu_Enter((void *)((DWORD)lpThis_Temp - BASE));
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_Temp - BASE));

					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void **)((DWORD)lpThis_Temp - BASE), 5);

					break;
				}
				}
				UpdateButtonState(hDlg);
			}
		}
	}
	break;
	}
	return FALSE;
}



CALDLG_CTXT dcCal_1_6 =
{
	NULL,
	IDD_CAL_1_6,
	DFL_CMD_PREV | DFL_CMD_OK | DFL_LBL_INFO1,
	&fndeCal_1_6,
	&fndpCal_1_6,
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