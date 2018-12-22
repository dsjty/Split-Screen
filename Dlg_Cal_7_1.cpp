#include "stdafx.h"

extern CALDLG_CTXT dcCal_7;

void UpdateComboBox_STD(HWND hCtl);

VOID ComboBoxInit(HWND hDlg);


void *lpThis_SCLS_O = NULL;
void *lpThis_SCLS_O_P1 = NULL;
void *lpThis_SCLS_O_P2 = NULL;

void *lpThis_SCLS_S = NULL;
void *lpThis_SCLS_S_P1 = NULL;
void *lpThis_SCLS_S_P2 = NULL;

void *lpThis_SCLS_L = NULL;
void *lpThis_SCLS_L_P1 = NULL;
void *lpThis_SCLS_L_P2 = NULL;

void *lpThis_SCLS_T = NULL;
void *lpThis_SCLS_T_P12 = NULL;

void *lpThis_SCLS_TRLT = NULL;
void *lpThis_SCLS_TRLT_P12 = nullptr;

void *lpThis_SCLS_TLM = NULL;
void *lpThis_SCLS_TLM_P12 = nullptr;

void *lpThis_SCLS_SUBC = NULL;

void *lpThis_SCLS_TRLR = nullptr;

void EumSubMenuList(HWND hwnd, void *lpThis)
{
	DWORD *lpLabel = 0;
	int nIndex = 0, nStdNum;
	void *lpThisTemp = nullptr;
	PMENUPTRSTR lpSTDSubName = 0;

	ComboBox_DeleteAll(hwnd);
	OrigSoftMenu_UpdateItems(lpThis);

	nStdNum = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_CAL7_CB_DEFSTD));

	lpSTDSubName = (PMENUPTRSTR)((DWORD)lpThis + BASE);

	lpLabel = (DWORD *)GetOffsetPointer(lpSTDSubName, 0x14);
	do
	{
		WCHAR wcsText[MAX_PATH] = { 0 };
		if (lpLabel)
		{
			MultiByteToWideChar(1253, 0, (LPCTSTR)((DWORD*)lpLabel[nIndex]), -1, wcsText, MAX_PATH);
		}
		else
		{
			swprintf_s(wcsText, MAX_PATH, L"[%d:Invalid]", nIndex);
		}

		ComboBox_InsertStringW(hwnd, nIndex, wcsText);
		nIndex++;
	} while (nIndex < lpSTDSubName->MenuNum);
}


static void UpdateComboBoxSel(HWND hClient)
{
	int nIndex;

	lpThis_SCLS_SUBC = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 0);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_SUBC - BASE));
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_SUBC - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_SUBC - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_SC), nIndex);
	}


	lpThis_SCLS_O = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 1);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O - BASE));

	lpThis_SCLS_O_P1 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_O - BASE), 1);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O_P1 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_O_P1 - BASE));
		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_OP1), nIndex);
	}

	lpThis_SCLS_O_P2 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_O - BASE), 2);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O_P2 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_O_P2 - BASE));
		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_OP2), nIndex);
	}


	lpThis_SCLS_S = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 2);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S - BASE));

	lpThis_SCLS_S_P1 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_S - BASE), 1);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S_P1 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_S_P1 - BASE));
		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_SP1), nIndex);
	}

	lpThis_SCLS_S_P2 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_S - BASE), 2);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S_P2 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_S_P2 - BASE));
		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_SP2), nIndex);
	}



	lpThis_SCLS_L = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 3);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L - BASE));

	lpThis_SCLS_L_P1 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_L - BASE), 1);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L_P1 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_L_P1 - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_LP1), nIndex);
	}

	lpThis_SCLS_L_P2 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_L - BASE), 2);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L_P2 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_L_P2 - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_LP2), nIndex);
	}



	lpThis_SCLS_T = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 4);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_T - BASE));

	lpThis_SCLS_T_P12 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_T - BASE), 1);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_T_P12 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_T_P12 - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_P12), nIndex);
	}




	lpThis_SCLS_TRLT = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 5);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT - BASE));

	lpThis_SCLS_TRLT_P12 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_TRLT - BASE), 1);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT_P12 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_TRLT_P12 - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_TP12), nIndex);
	}

	


	lpThis_SCLS_TRLR = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 6);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLR - BASE));

	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLR - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_TRLR - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_TRLR), nIndex);
	}



	lpThis_SCLS_TLM = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 7);
	OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM - BASE));

	lpThis_SCLS_TLM_P12 = GetSubMenuPointer((void *)((DWORD)lpThis_SCLS_TLM - BASE), 1);
	{
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM_P12 - BASE));
		nIndex = GetSubMenuSelected_Radio((void *)((DWORD)lpThis_SCLS_TLM_P12 - BASE));

		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL71_CB_LM12), nIndex);
	}
}

INT_PTR WINAPI fndeCal_7_1(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL)
		return -1;
	void *lpThisTemp = nullptr;

	INT_PTR lResult = 0;

	switch (dwCode)
	{
	case DEC_ENTER:
	{

		int nIndex = 0;

		OrigSoftMenu_Enter(CA_CAL_MCK);
		OrigSoftMenu_UpdateItems(CA_CAL_MCK);
		OrigSoftMenu_ItemClicked2(CA_CAL_MCK, TA_CAL_MCK, 1);

		OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS);
		OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS);

		lpThis_SCLS_SUBC = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 0);
		if (lpThis_SCLS_SUBC)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_SUBC - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_SUBC - BASE));
		}

		lpThis_SCLS_O = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 1);
		if (lpThis_SCLS_O)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O - BASE));
		}

		lpThis_SCLS_S = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 2);
		if (lpThis_SCLS_S)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S - BASE));
		}

		lpThis_SCLS_L = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 3);
		if (lpThis_SCLS_L)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L - BASE));
		}

		lpThis_SCLS_T = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 4);
		if (lpThis_SCLS_T)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_T - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_T - BASE));
		}

		lpThis_SCLS_TRLT = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 5);
		if (lpThis_SCLS_TRLT)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
		}

		lpThis_SCLS_TLM = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 7);
		if (lpThis_SCLS_TLM)
		{
			OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TLM - BASE));
			OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM - BASE));
		}

		ComboBoxInit((HWND)lParam2);

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_GB_O), GetStringByIndex(L"Open\0开路器\0開路器\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_GB_S), GetStringByIndex(L"Short\0短路器\0短路器\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_GB_L), GetStringByIndex(L"Load\0负载\0負載\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_GB_T), GetStringByIndex(L"Thru\0短接\0短接\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_OA), GetStringByIndex(L"Set All\0全部设置\0全部設置\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_SA), GetStringByIndex(L"Set All\0全部设置\0全部設置\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_LA), GetStringByIndex(L"Set All\0全部设置\0全部設置\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_OP1), GetStringByIndex(L"Port 1\0端口1\0端口1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_SP1), GetStringByIndex(L"Port 1\0端口1\0端口1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_LP1), GetStringByIndex(L"Port 1\0端口1\0端口1\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_OP2), GetStringByIndex(L"Port 2\0端口2\0端口2\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_SP2), GetStringByIndex(L"Port 2\0端口2\0端口2\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_LP2), GetStringByIndex(L"Port 2\0端口2\0端口2\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_P12), GetStringByIndex(L"Port 1-2\0端口1-2\0端口1-2\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL71_LBL_TRLT), GetStringByIndex(L"TRL Reflect\0\0", nLangId));

		EumSubMenuList(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_SC), CA_CAL_MCK_SPCCLS_SUBCLA);
		EumSubMenuList(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_TRLR), CA_CAL_MCK_SPCCLS_TRLREF);


		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_OA));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_OP1));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_OP2));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_SA));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_SP1));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_SP2));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LA));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LP1));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LP2));

		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_TA));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_P12));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_P13));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_P14));

		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_TRLA));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_TP12));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_TP13));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_TP14));

		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LMA));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LM12));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LM13));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL71_CB_LM14));

		UpdateComboBoxSel((HWND)lParam2);
	}
	break;

	case DEC_CMD_PREV:
		UpdateDialog_Cal(&dcCal_7, 0);
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

INT_PTR CALLBACK fndpCal_7_1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return TRUE;
	}

	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == CBN_SELCHANGE)
			{
				switch (wId)
				{
					/***********************************Sub Class**********************************/
				case IDC_CAL71_CB_SC:
				{
					if (lpThis_SCLS_TRLT_P12)
					{
						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_SUBCLA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_SUBCLA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_SUBCLA, TA_CAL_MCK_SPCCLS_SUBCLA, ComboBox_GetCurSel((HWND)lParam));
					}
					break;
				}

				/***********************************Open**********************************/
				case IDC_CAL71_CB_OA:
				{
					if (lpThis_SCLS_O)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_O - BASE), TA_CAL_MCK_SPCCLS_OSL, 0);

						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_OSL_SA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_OSL_SA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_OSL_SA, TA_CAL_MCK_SPCCLS_OSL_SA, ComboBox_GetCurSel((HWND)lParam));

						UpdateComboBoxSel(hDlg);
					}
				}
				break;

				case IDC_CAL71_CB_OP1:
				{
					if (lpThis_SCLS_O_P1)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_O - BASE), TA_CAL_MCK_SPCCLS_OSL, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O_P1 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O_P1 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_O_P1 - BASE), TA_CAL_MCK_SPCCLS_OSL_PORTn, ComboBox_GetCurSel((HWND)lParam));
					}
				}
				break;

				case IDC_CAL71_CB_OP2:
				{
					if (lpThis_SCLS_O_P2)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_O - BASE), TA_CAL_MCK_SPCCLS_OSL, 2);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O_P2 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O_P2 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_O_P2 - BASE), TA_CAL_MCK_SPCCLS_OSL_PORTn, ComboBox_GetCurSel((HWND)lParam));
					}
				}
				break;

				/***********************************Short**********************************/
				case IDC_CAL71_CB_SA:
				{
					if (lpThis_SCLS_S)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 2);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_S - BASE), TA_CAL_MCK_SPCCLS_OSL, 0);

						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_OSL_SA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_OSL_SA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_OSL_SA, TA_CAL_MCK_SPCCLS_OSL_SA, ComboBox_GetCurSel((HWND)lParam));

						UpdateComboBoxSel(hDlg);
					}
				}
				break;

				case IDC_CAL71_CB_SP1:
				{
					if (lpThis_SCLS_S_P1)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 2);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_S - BASE), TA_CAL_MCK_SPCCLS_OSL, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S_P1 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S_P1 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_S_P1 - BASE), TA_CAL_MCK_SPCCLS_OSL_PORTn, ComboBox_GetCurSel((HWND)lParam));
					}
				}
				break;

				case IDC_CAL71_CB_SP2:
				{
					if (lpThis_SCLS_S_P2)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 2);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_S - BASE), TA_CAL_MCK_SPCCLS_OSL, 2);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S_P2 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S_P2 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_S_P2 - BASE), TA_CAL_MCK_SPCCLS_OSL_PORTn, ComboBox_GetCurSel((HWND)lParam));
					}
				}
				break;

				/***********************************Load**********************************/
				case IDC_CAL71_CB_LA:
				{
					if (lpThis_SCLS_L)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 3);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_L - BASE), TA_CAL_MCK_SPCCLS_OSL, 0);

						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_OSL_SA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_OSL_SA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_OSL_SA, TA_CAL_MCK_SPCCLS_OSL_SA, ComboBox_GetCurSel((HWND)lParam));

						UpdateComboBoxSel(hDlg);
					}
				}
				break;

				case IDC_CAL71_CB_LP1:
				{
					if (lpThis_SCLS_L_P1)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 3);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_L - BASE), TA_CAL_MCK_SPCCLS_OSL, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L_P1 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L_P1 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_L_P1 - BASE), TA_CAL_MCK_SPCCLS_OSL_PORTn, ComboBox_GetCurSel((HWND)lParam));
					}
				}
				break;

				case IDC_CAL71_CB_LP2:
				{
					if (lpThis_SCLS_L_P2)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 3);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_L - BASE), TA_CAL_MCK_SPCCLS_OSL, 2);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L_P2 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L_P2 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_L_P2 - BASE), TA_CAL_MCK_SPCCLS_OSL_PORTn, ComboBox_GetCurSel((HWND)lParam));
					}
				}
				break;

				/***********************************Thru**********************************/
				case IDC_CAL71_CB_TA:
				{
					if (lpThis_SCLS_T)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 4);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_T - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_T - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_T - BASE), TA_CAL_MCK_SPCCLS_THRU, 0);

						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_THRU_SA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_THRU_SA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_THRU_SA, TA_CAL_MCK_SPCCLS_THRU_SA, ComboBox_GetCurSel((HWND)lParam));

						UpdateComboBoxSel(hDlg);
					}
					break;
				}

				case IDC_CAL71_CB_P12:
				{
					if (lpThis_SCLS_T_P12)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 4);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TRLT - BASE), TA_CAL_MCK_SPCCLS_THRU, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_T_P12 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_T_P12 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_T_P12 - BASE), TA_CAL_MCK_SPCCLS_THRU_PORT, ComboBox_GetCurSel((HWND)lParam));
					}
					break;
				}

				/***********************************TRL Thru**********************************/
				case IDC_CAL71_CB_TRLA:
				{
					if (lpThis_SCLS_TRLT)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 5);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TRLT - BASE), TA_CAL_MCK_SPCCLS_THRU, 0);

						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_THRU_SA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_THRU_SA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_THRU_SA, TA_CAL_MCK_SPCCLS_THRU_SA, ComboBox_GetCurSel((HWND)lParam));

						UpdateComboBoxSel(hDlg);
					}
					break;
				}

				case IDC_CAL71_CB_TP12:
				{
					if (lpThis_SCLS_TRLT_P12)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 5);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TRLT - BASE), TA_CAL_MCK_SPCCLS_THRU, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TRLT_P12 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT_P12 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TRLT_P12 - BASE), TA_CAL_MCK_SPCCLS_THRU_PORT, ComboBox_GetCurSel((HWND)lParam));
					}
					break;
				}

				/***********************************TRLReflect**********************************/
				case IDC_CAL71_CB_TRLR:
				{

					OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_TRLREF);
					OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_TRLREF);
					OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_TRLREF, TA_CAL_MCK_SPCCLS_TRLREF, ComboBox_GetCurSel((HWND)lParam));

					UpdateComboBoxSel(hDlg);
					break;
				}

				/***********************************TRLLine/Match**********************************/
				case IDC_CAL71_CB_LMA:
				{
					if (lpThis_SCLS_TLM)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 7);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TLM - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TLM - BASE), TA_CAL_MCK_SPCCLS_THRU, 0);

						OrigSoftMenu_Enter(CA_CAL_MCK_SPCCLS_THRU_SA);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_SPCCLS_THRU_SA);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS_THRU_SA, TA_CAL_MCK_SPCCLS_THRU_SA, ComboBox_GetCurSel((HWND)lParam));
						UpdateComboBoxSel(hDlg);
					}
					break;
				}

				case IDC_CAL71_CB_LM12:
				{
					if (lpThis_SCLS_TLM_P12)
					{
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_SPCCLS, TA_CAL_MCK_SPCCLS, 7);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TLM - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TLM - BASE), TA_CAL_MCK_SPCCLS_THRU, 1);

						OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TLM_P12 - BASE));
						OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM_P12 - BASE));
						OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_SCLS_TLM_P12 - BASE), TA_CAL_MCK_SPCCLS_THRU_PORT, ComboBox_GetCurSel((HWND)lParam));
					}
					break;
				}
				}
			}
		}
	}
	break;

	}

	return FALSE;
}

CALDLG_CTXT dcCal_7_1 =
{
  NULL,
  IDD_CAL_7_1,
  DFL_CMD_PREV | DFL_LBL_INFO1,
  &fndeCal_7_1,
  &fndpCal_7_1,
  NULL,
  NULL,
  NULL,
  L"Modify Cal Kit\0更换校准件\0更換校準件\0\0",
  L"Specify CLSs\0指定标准类别\0指定標準類別\0\0",
  L"\0\0",
  NULL,
  NULL,
  NULL,
  NULL,
  L"Exit\0退出\0退出\0\0",
  RESERVE_DWORD4,
  RESERVE_DWORD4
};

VOID ComboBoxInit(HWND hDlg)
{
	MENUPTRSTR *lpTemp = nullptr;

	if (!lpThis_SCLS_O)
		lpThis_SCLS_O = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 1);

	{
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_O - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_O - BASE));

		lpTemp = (PMENUPTRSTR)lpThis_SCLS_O;

		if (!(DWORD)lpTemp->SubMenuThisList + 0xC)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_OP3), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_OP3), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x10)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_OP4), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_OP4), 0);
		}
	}

	if (!lpThis_SCLS_S)
		lpThis_SCLS_S = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 2);

	{
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_S - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_S - BASE));

		lpTemp = (PMENUPTRSTR)lpThis_SCLS_S;

		if (!(DWORD)lpTemp->SubMenuThisList + 0xC)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_SP3), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_SP3), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x10)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_SP4), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_SP4), 0);
		}
	}

	if (!lpThis_SCLS_L)
		lpThis_SCLS_L = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 3);

	{
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_L - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_L - BASE));

		lpTemp = (PMENUPTRSTR)lpThis_SCLS_L;

		if (!(DWORD)lpTemp->SubMenuThisList + 0xC)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LP3), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LP3), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x10)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LP4), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LP4), 0);
		}
	}

	if (!lpThis_SCLS_T)
		lpThis_SCLS_T = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 4);

	{
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_T - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_T - BASE));

		lpTemp = (PMENUPTRSTR)lpThis_SCLS_T;

		if (!(DWORD)lpTemp->SubMenuThisList + 0x8)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_P13), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_P13), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0xC)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_P14), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_P14), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x10)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_P14), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_P14), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x14)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_P23), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_P23), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x18)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_P24), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_P24), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x1C)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_P34), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_P34), 0);
		}
	}

	if (!lpThis_SCLS_TRLT)
		lpThis_SCLS_TRLT = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 5);

	{
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TRLT - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TRLT - BASE));

		lpTemp = (PMENUPTRSTR)lpThis_SCLS_TRLT;

		if (!(DWORD)lpTemp->SubMenuThisList + 0x8)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_TP13), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_TP13), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0xC)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_TP14), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_TP14), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x10)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_TP23), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_TP23), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x14)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_TP24), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_TP24), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x18)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_TP34), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_TP34), 0);
		}
	}

	if (!lpThis_SCLS_TLM)
		lpThis_SCLS_TLM = GetSubMenuPointer(CA_CAL_MCK_SPCCLS, 7);

	{
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_SCLS_TLM - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_SCLS_TLM - BASE));

		lpTemp = (PMENUPTRSTR)lpThis_SCLS_TLM;

		if (!(DWORD)lpTemp->SubMenuThisList + 0x8)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LM13), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LM13), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0xC)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LM14), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LM14), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x10)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LM23), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LM23), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x14)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LM24), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LM24), 0);
		}
		if (!(DWORD)lpTemp->SubMenuThisList + 0x18)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_LBL_LM34), 0);
			ShowWindow(GetDlgItem(hDlg, IDC_CAL71_CB_LM34), 0);
		}
	}
}

