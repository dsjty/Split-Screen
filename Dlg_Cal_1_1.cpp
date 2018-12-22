#include "stdafx.h"

void *lpThis_RS = NULL;
void *lpThis_RS_SP = nullptr;

extern CALDLG_CTXT dcCal_1;

static void UpdateButtonState(HWND hClient);


//************************************
// 函数名:    CalResPortDis
// 函数性质:    public static 
// 函数类型:   void *
//如 给CALCAL的指针，即探测CALCAL-RES下的指定按钮是否是菜单。
//第二个参数是子菜单的序号,第三个参数是子菜单的按钮序列
// 描述://探测子菜单下的指定按钮看是否是菜单，是的返回0 否则返回子菜单CA指针;
//************************************
static void *CalResPortDis(void * ulpThis, int nSubMenu, int nIndex)
{
	PMENUPTRSTR lpVar = nullptr;
	PMENUPTRSTR stcThisList = nullptr;
	void *lpThis_SEC = nullptr;

	//获取res菜单的指针;
	lpThis_SEC = GetSubMenuPointer(ulpThis, nSubMenu);

	//探测res菜单下的指定按钮看是否是菜单，是的返回0 否则返回子菜单CA指针;
	stcThisList = (PMENUPTRSTR)lpThis_SEC;
	stcThisList = (PMENUPTRSTR)(void**)stcThisList->SubMenuThisList;
	stcThisList = (PMENUPTRSTR)((DWORD)(stcThisList)+(DWORD)(nIndex * 4));

	if (stcThisList)
		return stcThisList;
	return 0;
}

INT_PTR WINAPI fndeCal_1_1(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
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

		lpThis_RS = GetSubMenuPointer(CA_CAL_CAL, 1);

		if (lpThis_RS)
		{
			OrigSoftMenu_Enter((void*)((DWORD)lpThis_RS - BASE));
			OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_RS - BASE));
		}
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_OK), FALSE);
		EnableWindow(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_OK), FALSE);		
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_GB_P1), GetStringByIndex(L"Port1\0端口1\0端口1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_GB_P2), GetStringByIndex(L"Port2\0端口2\0端口2\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_OK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_OK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));


		//检测OPEN和负载等是否有下级菜单
		//OPEN检测
		lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
		lpThis_Temp = *(void**)lpThis_Temp;
		if (lpThis_Temp)
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_S), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_S), GetStringByIndex(L"Open(f)\0开路器(f)\0開路器(f)\0\0", nLangId));

			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_S2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_S2), GetStringByIndex(L"Open(m)\0开路器(m)\0開路器(m)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_S), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_S), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));

			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_S2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_S2), 0);
		}
		//load检测
		lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
		lpThis_Temp = *(void**)lpThis_Temp;
		if (lpThis_Temp)
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_L), GetStringByIndex(L"Load(f)(Optional)\0负载(f)(可选)\0負載(f)(可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_L), GetStringByIndex(L"Load(f)(Optional)\0负载(f)(可选)\0負載(f)(可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_L2), GetStringByIndex(L"Load(m)(Optional)\0负载(m)(可选)\0負載(m)(可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_L2), GetStringByIndex(L"Load(m)(Optional)\0负载(m)(可选)\0負載(m)(可選)\0\0", nLangId));
		}
		else
		{
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_L), GetStringByIndex(L"Load(Optional)\0负载(可选)\0負載(可選)\0\0", nLangId));
			SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_L), GetStringByIndex(L"Load(Optional)\0负载(可选)\0負載(可選)\0\0", nLangId));
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL11_P1_L2), 0);
			ShowWindow(GetDlgItem((HWND)lParam2, IDC_CAL11_P2_L2), 0);
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

	if (lpThis_RS == NULL)
		lpThis_RS = GetSubMenuPointer(CA_CAL_CAL, 1);

	OrigSoftMenu_Enter((void *)((DWORD)lpThis_RS - BASE));
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

	if (lpThis_RS_SP == NULL)
		lpThis_RS_SP = GetSubMenuPointer((void *)((DWORD)lpThis_RS - BASE), 0);

	if (nullptr == lpThis_RS_SP)
	{
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 0);
		return;
	}

	OrigSoftMenu_Enter((void *)((DWORD)lpThis_RS_SP - BASE));
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

	OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS_SP - BASE), TA_CAL_CAL_Resp_OS_SP, nPort);
}


static void UpdateButtonState(HWND hClient)
{
	BOOL blTmp = FALSE;

	ChangeCurPortNumber(0);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

	void* lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
	lpThis_Temp = *(void**)lpThis_Temp;
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_S), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_S), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_S2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_S2), BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL11_P1_S2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_RS - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_S), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_S), BST_UNCHECKED);
	}

	lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
	lpThis_Temp = *(void**)lpThis_Temp;
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_L), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_L), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_L2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_L2), BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL11_P1_L2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_RS - BASE), 2, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_L), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P1_L), BST_UNCHECKED);
	}
	OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_RS - BASE), 3, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL11_P1_OK), blTmp);


	ChangeCurPortNumber(1);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));
	
	lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
	lpThis_Temp = *(void**)lpThis_Temp;
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_S), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_S), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_S2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_S2), BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL11_P2_S2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_RS - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_S), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_S), BST_UNCHECKED);
	}

	lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
	lpThis_Temp = *(void**)lpThis_Temp;
	if (lpThis_Temp)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 0, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_L), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_L), BST_UNCHECKED);

		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), 1, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_L2), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_L2), BST_UNCHECKED);
	}
	else
	{
		EnableWindow(GetDlgItem(hClient, IDC_CAL11_P2_L2), 0);
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_RS - BASE), 2, NULL, &blTmp, NULL);
		if (blTmp)
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_L), BST_CHECKED);
		else
			Button_SetCheck(GetDlgItem(hClient, IDC_CAL11_P2_L), BST_UNCHECKED);
	}
	OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_RS - BASE), 3, &blTmp, NULL, NULL);
	EnableWindow(GetDlgItem(hClient, IDC_CAL11_P2_OK), blTmp);
}

INT_PTR CALLBACK fndpCal_1_1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	void * lpThis_Temp = nullptr;
	void *lpThis_SP = nullptr;

	switch (msg)
	{
	case WM_PAINT:
		return 0;
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
				if (lpThis_RS == NULL)
				{
					lpThis_RS = GetSubMenuPointer(CA_CAL_CAL, 1);

					if (lpThis_RS)
					{
						OrigSoftMenu_Enter((void *)((DWORD)lpThis_RS - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));
					}

					if (lpThis_RS == NULL) 
						break;
				}

				switch (wId)
				{
				case IDC_CAL11_P1_S:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
					lpThis_Temp = *(void**)lpThis_Temp;
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 1);
					break;

				case IDC_CAL11_P1_S2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
					lpThis_Temp = *(void**)lpThis_Temp;

					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL11_P1_L:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
					lpThis_Temp = *(void**)lpThis_Temp;
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 2);
					break;

				case IDC_CAL11_P1_L2:
					ChangeCurPortNumber(0);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
					lpThis_Temp = *(void**)lpThis_Temp;

					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);

					break;

				case IDC_CAL11_P2_S:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
					lpThis_Temp = *(void**)lpThis_Temp;
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 0);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 1);
					break;	

				case IDC_CAL11_P2_S2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 1);
					lpThis_Temp = *(void**)lpThis_Temp;

					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);

					break;

				case IDC_CAL11_P2_L:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
					lpThis_Temp = *(void**)lpThis_Temp;
					if (lpThis_Temp)
					{
						lpThis_SP = *(void **)lpThis_Temp;
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					}
					else
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 2);
					break;

				case IDC_CAL11_P2_L2:
					ChangeCurPortNumber(1);
					OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_RS - BASE));

					lpThis_Temp = CalResPortDis(CA_CAL_CAL, 1, 2);
					lpThis_Temp = *(void**)lpThis_Temp;

					lpThis_SP = *(void **)lpThis_Temp;
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_Temp - BASE), (void *)((DWORD)lpThis_SP - BASE), 1);
					break;

				case IDC_CAL11_P1_OK:
					ChangeCurPortNumber(0);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 3);
					break;

				case IDC_CAL11_P2_OK:
					ChangeCurPortNumber(1);
					OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_RS - BASE), TA_CAL_CAL_Resp_OS, 3);
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


CALDLG_CTXT dcCal_1_1 =
{
	NULL,
	IDD_CAL_1_1,
	DFL_CMD_PREV | DFL_LBL_INFO1,
	&fndeCal_1_1,
	&fndpCal_1_1,
	NULL,
	NULL,
	NULL,
	L"Manual Calibration\0手动校准\0手動校準\0\0",
	L"Response (Short)\0响应 (短路器)\0響應 (短路器)\0\0",
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RESERVE_DWORD4,
	RESERVE_DWORD4
};