#include "stdafx.h"


extern CALDLG_CTXT dcCal_7_1;

static int nLastIdx = -1;

LRESULT CALLBACK wp_DC7_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void *lpThis_STD[21] =
{
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

void UpdateComboBox_STD(HWND hCtl)
{
	ComboBox_DeleteAll(hCtl);
	OrigSoftMenu_UpdateItems(CA_CAL_MCK_DSTD);

	char *lpLabel;
	int nIndex = 1;	
	void *lpSTDSubName = nullptr;
	
	ComboBox_InsertStringW(hCtl, 0, L"None");
	do
	{
		lpSTDSubName = GetSubMenuPointer(CA_CAL_MCK_DSTD, nIndex - 1);
		lpLabel = (char *)GetOffsetPointer(lpSTDSubName, 0x0C);

		WCHAR wcsText[MAX_PATH] = { 0 };
		if (lpLabel )
		{
			MultiByteToWideChar(1253, 0, lpLabel, -1, wcsText, MAX_PATH);
		}
		else
		{
			swprintf_s(wcsText, MAX_PATH, L"[%d:Invalid]", nIndex);
		}

		ComboBox_InsertStringW(hCtl, nIndex, wcsText);
		nIndex++;
	} while (nIndex < 0x1F);
}

void UpdateComboBox_STDType(HWND hCtl)
{
	DWORD *lpLabel = 0;
	int nIndex = 0, nStdNum;
	void *lpSTDSubName = nullptr, *lpThisTemp = nullptr;

	ComboBox_DeleteAll(hCtl);
	OrigSoftMenu_UpdateItems(CA_CAL_MCK_DSTD);
	
	nStdNum = ComboBox_GetCurSel(GetDlgItem(hCtl, IDC_CAL7_CB_DEFSTD));

	lpThisTemp = GetSubMenuPointer(CA_CAL_MCK_DSTD, nStdNum);
	OrigSoftMenu_Enter((void*)((DWORD)lpThisTemp - BASE));
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThisTemp - BASE));

	lpThisTemp = GetSubMenuPointer((void*)((DWORD)lpThisTemp - BASE), 1);
	OrigSoftMenu_Enter((void*)((DWORD)lpThisTemp - BASE));
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThisTemp - BASE));

	lpSTDSubName = (void**)((DWORD)lpThisTemp + 0x14);

	lpLabel = (DWORD *)GetOffsetPointer(lpSTDSubName, 0);
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

		ComboBox_InsertStringW(hCtl, nIndex, wcsText);
		nIndex++;
	} while (nIndex < 0x7);
}

static void UpdateTypeState_STD(HWND hClient, int nIndex)
{
	int j = 0, nStdNum = 0;
	void *lpThis_Temp = nullptr;
	void *lpThis_Temp2 = nullptr;
	BOOL blTmp = FALSE;

	OrigSoftMenu_Enter(CA_CAL_MCK_DSTD);
	OrigSoftMenu_UpdateItems(CA_CAL_MCK_DSTD);

	nStdNum = ComboBox_GetCurSel(GetDlgItem(hClient, IDC_CAL7_CB_DEFSTD));
	lpThis_Temp = GetSubMenuPointer(CA_CAL_MCK_DSTD, nStdNum);
	OrigSoftMenu_Enter((void*)((DWORD)lpThis_Temp - BASE));
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Temp - BASE));

	lpThis_Temp2 = GetSubMenuPointer((void*)((DWORD)lpThis_Temp - BASE), 1);
	OrigSoftMenu_Enter((void*)((DWORD)lpThis_Temp2 - BASE));
	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Temp2 - BASE), (void**)((DWORD)lpThis_Temp2 - BASE), nIndex);
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Temp - BASE));

	for (int i = 2; j < 16; i++,j++)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis_Temp - BASE), i, &blTmp, NULL, NULL);	

		EnableWindow(GetDlgItem(hClient, 1510 + j), blTmp ? TRUE : FALSE);
	}
}

static void UpdateType_STD(HWND hClient, int nIndex)
{
	if ((nIndex >= 0) && (nIndex < 30) && (lpThis_STD[nIndex]))
	{
		lpThis_STD[nIndex] = GetSubMenuPointer(CA_CAL_MCK_DSTD, nIndex);
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_STD[nIndex] - BASE));

		void *lpThis2 = GetSubMenuPointer((void *)((DWORD)lpThis_STD[nIndex] - BASE), 1);

		if (lpThis2 == NULL) 
			return;

		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis2 - BASE));

		int nTmp = GetSubMenuSelected_Radio((void *)((DWORD)lpThis2 - BASE));
		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL7_CB_STDTYPE), nTmp);

		UpdateTypeState_STD(hClient, nTmp);
	}
}

static void UpdateValue_STD(HWND hClient, int nIndex)
{
	int nTmp = 0;
	char szTmp[MAX_PATH] = { 0 };
	WCHAR wcsTmp[MAX_PATH] = { 0 };

	GetInputStringObjectW((void *)0x010B3628, wcsTmp, MAX_PATH, &nTmp);
	SendDlgItemMessage(hClient, IDC_CAL7_EDIT_KIT, EM_LIMITTEXT, nTmp, NULL);

	//85038A/F/M    85039B   85036B/E   85032B/E   85032F   85052D   85033D   85033E
	if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[7].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[7].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[6].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[6].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[5].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[5].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[4].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[4].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[3].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[3].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[2].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[2].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[1].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[1].c_str());
	else if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[0].c_str()))
		wcscpy_s(wcsTmp, cCalkit.CalKitList[0].c_str());

	SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_KIT), wcsTmp);

	ZeroMemory(wcsTmp, MAX_PATH - 1);

	GetInputStringObjectW((void *)0x010B362C, wcsTmp, MAX_PATH, &nTmp);
	SendDlgItemMessage(hClient, IDC_CAL7_EDIT_KIT, EM_LIMITTEXT, nTmp, NULL);
	SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_STDLBL), wcsTmp);


	if ((nIndex >= 0) && (nIndex < 30) && (lpThis_STD[nIndex]))
	{
		OrigSoftMenu_ItemClicked2(CA_CAL_MCK_DSTD, TA_CAL_MCK_DSTD, nIndex);
		OrigSoftMenu_Enter((void *)((DWORD)lpThis_STD[nIndex] - BASE));
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_STD[nIndex] - BASE));

		UpdateType_STD(hClient, nIndex);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 0);
		GetInputStringObjectW((void *)0x010B362C, wcsTmp, MAX_PATH, &nTmp);
		SendDlgItemMessage(hClient, IDC_CAL7_EDIT_STDLBL, EM_LIMITTEXT, nTmp, NULL);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_STDLBL), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 2);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_C0), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 3);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_C1), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 4);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_C2), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 5);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_C3), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 6);
		FmtValueToString((void *)(0x01637C48 ), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_L0), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 7);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_L1), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 8);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_L2), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 9);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_L3), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 10);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_OD), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 11);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_OZ), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 12);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_OL), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 13);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_AI), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 14);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_MinF), wcsTmp);

		ZeroMemory(wcsTmp, MAX_PATH);
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nIndex] - BASE), TA_CALMCK_DSTD_ALL, 15);
		FmtValueToString((void *)(0x01637C48), szTmp, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wcsTmp, MAX_PATH);
		SetWindowTextW(GetDlgItem(hClient, IDC_CAL7_EDIT_MAXF), wcsTmp);

		void *lpThis_LT = nullptr;
		int n = ComboBox_GetCurSel(GetDlgItem(hClient, IDC_CAL7_CB_DEFSTD));
		lpThis_LT = GetSubMenuPointer(CA_CAL_MCK_DSTD, n);
		OrigSoftMenu_Enter((void*)((DWORD)lpThis_LT - BASE));
		OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_LT - BASE));
		lpThis_LT = GetSubMenuPointer((void*)((DWORD)lpThis_LT - BASE), 17);
		OrigSoftMenu_Enter((void*)((DWORD)lpThis_LT - BASE));
		OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_LT - BASE));

		nIndex = GetSubMenuSelected_Radio((void*)((DWORD)lpThis_LT - BASE));
		ComboBox_SetCurSel(GetDlgItem(hClient, IDC_CAL7_CB_LENTP), nIndex);
	}
}


LPCWSTR DeleteStar(LPWSTR wcsStr)
{
	wstring wsStr = wcsStr;
	int iCount = 0;

	iCount = wsStr.rfind(L" *");
	if (iCount != wstring::npos)
		wsStr.erase(wsStr.begin() + iCount, wsStr.begin() + iCount + 2);
	
	wcscpy_s(wcsStr,MAX_PATH, wsStr.c_str());
	return 00;
}

INT_PTR WINAPI fndeCal_7(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL) return -1;

	INT_PTR lResult = 0;

	switch (dwCode)
	{
	case DEC_ENTER:
	{
		OrigSoftMenu_Enter(CA_CALIBRAT);
		OrigSoftMenu_UpdateItems(CA_CALIBRAT);

		OrigSoftMenu_Enter(CA_CAL_MCK);
		OrigSoftMenu_UpdateItems(CA_CAL_MCK);

		OrigSoftMenu_Enter(CA_CAL_MCK_DSTD);
		OrigSoftMenu_UpdateItems(CA_CAL_MCK_DSTD);

		OrigSoftMenu_Enter(CA_CAL_MCK_ResCalKit);
		OrigSoftMenu_UpdateItems(CA_CAL_MCK_ResCalKit);

		nLastIdx = -1;

		for (int nIndex = 0; nIndex < 30; nIndex++)
		{
			lpThis_STD[nIndex] = GetSubMenuPointer(CA_CAL_MCK_DSTD, nIndex);

			if (lpThis_STD[nIndex])
			{
				OrigSoftMenu_Enter((void *)((DWORD)lpThis_STD[nIndex] - BASE));
				OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_STD[nIndex] - BASE));
				OrigSoftMenu_Leave((void *)((DWORD)lpThis_STD[nIndex] - BASE));
			}
		}

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_KIT), GetStringByIndex(L"Label Kit\0校准件命名\0校準件命名\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_CMD_RCK), GetStringByIndex(L"Restore Cal Kit\0恢复默认校准件\0恢復默認校準件\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_DEFSTD), GetStringByIndex(L"Define STDs\0定义标准\0定義標準\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_STDLBL), GetStringByIndex(L"STD Label\0标准命名\0標準命名\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_STDTYPE), GetStringByIndex(L"STD Type\0标准类型\0標準類型\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_OD), GetStringByIndex(L"Offset Delay\0延迟偏移\0延遲偏移\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_OZ), GetStringByIndex(L"Offset Z0\0阻抗偏移\0阻抗偏移\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_OL), GetStringByIndex(L"Offset Loss\0损耗偏移\0損耗偏移\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL7_LBL_AI), GetStringByIndex(L"Arb. Impedance\0绝对阻抗\0絕對阻抗\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL7_CB_LENTP), 0, GetStringByIndex(L"Fixed\0\0", nLangId));
		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL7_CB_LENTP), 1, GetStringByIndex(L"Sliding\0\0", nLangId));
		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL7_CB_LENTP), 2, GetStringByIndex(L"Offset\0\0", nLangId));


		UpdateComboBox_STDType(GetDlgItem((HWND)lParam2, IDC_CAL7_CB_STDTYPE));
		UpdateComboBox_STD(GetDlgItem((HWND)lParam2, IDC_CAL7_CB_DEFSTD));

		UpdateValue_STD((HWND)lParam2, -1);
	}
	break;

	case DEC_CMD_NEXT:
		OrigSoftMenu_Leave(CA_CAL_MCK_ResCalKit);
		OrigSoftMenu_Leave(CA_CAL_MCK_DSTD);
		OrigSoftMenu_Leave(CA_CAL_MCK);
		UpdateDialog_Cal(&dcCal_7_1, 0);
		break;

	case DEC_CMD_CANCEL:
		lResult = TRUE;
		OrigSoftMenu_Leave(CA_CAL_MCK_ResCalKit);
		OrigSoftMenu_Leave(CA_CAL_MCK_DSTD);
		OrigSoftMenu_Leave(CA_CAL_MCK);
		break;

	case DEC_CMD_CLOSE:
		lResult = TRUE;
		OrigSoftMenu_Leave(CA_CAL_MCK_ResCalKit);
		OrigSoftMenu_Leave(CA_CAL_MCK_DSTD);
		OrigSoftMenu_Leave(CA_CAL_MCK);
		break;
	}

	return lResult;
}

INT_PTR CALLBACK fndpCal_7(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		wpfn_InputEdit = (WNDPROC)SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_C0), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_C1), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_C2), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_C3), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_L0), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_L1), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_L2), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_L3), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_OD), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_OZ), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_CAL7_EDIT_AI), GWL_WNDPROC, (LONG)&wp_DC7_InputEdit);
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
				case IDC_CAL7_CMD_RCK:
				{
					if (MessageBoxW(hDlg, L"是否恢复默认校准设置?", L"提示", MB_YESNO) == IDYES)
					{
						HWND hCtl = GetDlgItem(hDlg, IDC_CAL7_CB_DEFSTD);
						int nCurIndex = ComboBox_GetCurSel(hCtl);

						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_ResCalKit, TA_CAL_MCK_ResCalKit, 0);
						UpdateComboBox_STD(hCtl);
						ComboBox_SetCurSel(hCtl, nCurIndex);
						UpdateValue_STD(hDlg, nCurIndex);
					}
				}
				break;
				}
				break;
			}

			switch (wNc)
			{
			case CBN_SELCHANGE:
			{
				switch (wId)
				{
					case IDC_CAL7_CB_DEFSTD:
					{
						nLastIdx = ComboBox_GetCurSel((HWND)lParam);
						OrigSoftMenu_ItemClicked2(CA_CAL_MCK_DSTD, TA_CAL_MCK_DSTD, nLastIdx);
						OrigSoftMenu_UpdateItems(CA_CAL_MCK_DSTD);
						UpdateValue_STD(hDlg, nLastIdx);
					}
					break;

					case IDC_CAL7_CB_STDTYPE:
					{
						UpdateTypeState_STD(hDlg, ComboBox_GetCurSel((HWND)lParam));
						break;
					}				
				}
				break;
			}
			case EN_KILLFOCUS:
			{
				switch (wId)
				{
				case IDC_CAL7_EDIT_KIT:
				{
					int nTmp;
					WCHAR wcsTmp[MAX_PATH];

					GetWindowTextW(GetDlgItem(hDlg, IDC_CAL7_EDIT_KIT), wcsTmp, MAX_PATH);

					DeleteStar(wcsTmp);

					if (wcslen(wcsTmp))
						SetInputStringObjectW((void *)0x10B3628, wcsTmp);
					break;
				}
				case IDC_CAL7_EDIT_STDLBL:
				{
					int nTmp;
					WCHAR wcsTmp[MAX_PATH];

					GetWindowTextW(GetDlgItem(hDlg, IDC_CAL7_EDIT_STDLBL), wcsTmp, MAX_PATH);

					DeleteStar(wcsTmp);

					if (wcslen(wcsTmp))
						SetInputStringObjectW((void *)0x10B362C, wcsTmp);
					break;
				}
				}
				break;
			}
			}
		}
		}
	break;
	case WM_DESTROY:
		{
			TDMenu *temp = nullptr;
			if (2 == uiCurFocusMenu)
				temp = cwMenuWnd2;
			else
				temp = cwMenuWnd;

			SNDMSG(temp->GetSafeHwnd(), WM_REFRESH, 0, 0);
			break;
		}
	}
	return FALSE;
}

LRESULT CALLBACK wp_DC7_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch (msg)
	{
	case WM_CHAR:
	{
		int nIndex = 0;

		switch (GetWindowLong(hWnd, GWL_ID))
		{
		case IDC_CAL7_EDIT_C0:
			nIndex = 2;
			break;

		case IDC_CAL7_EDIT_C1:
			nIndex = 3;
			break;

		case IDC_CAL7_EDIT_C2:
			nIndex = 4;
			break;

		case IDC_CAL7_EDIT_C3:
			nIndex = 5;
			break;

		case IDC_CAL7_EDIT_L0:
			nIndex = 6;
			break;

		case IDC_CAL7_EDIT_L1:
			nIndex = 7;
			break;

		case IDC_CAL7_EDIT_L2:
			nIndex = 8;
			break;

		case IDC_CAL7_EDIT_L3:
			nIndex = 9;
			break;

		case IDC_CAL7_EDIT_OD:
			nIndex = 10;
			break;

		case IDC_CAL7_EDIT_OZ:
			nIndex = 11;
			break;

		case IDC_CAL7_EDIT_AI:
			nIndex = 13;
			break;

		default:
			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		if (lpThis_STD[nLastIdx] == NULL)
		{
			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		OrigSoftMenu_ItemClicked2(CA_CAL_MCK_DSTD, TA_CAL_MCK_DSTD, nLastIdx);
		OrigSoftMenu_UpdateItems((void *)((DWORD)lpThis_STD[nLastIdx] - BASE));
		OrigSoftMenu_ItemClicked2((void *)((DWORD)lpThis_STD[nLastIdx] - BASE), TA_CALMCK_DSTD_ALL, nIndex);

		switch (wParam)
		{
		case 'n':
		{
			WCHAR wcsText[MAX_PATH];

			GetWindowTextW(hWnd, wcsText, MAX_PATH);
			MakeUnitStringW((void *)(0x01637C48), wcsText, MAX_PATH, "n");
			SetWindowTextW(hWnd, wcsText);
		}
		break;

		case 'u':
		{
			WCHAR wcsText[MAX_PATH];

			GetWindowTextW(hWnd, wcsText, MAX_PATH);
			MakeUnitStringW((void *)(0x01637C48), wcsText, MAX_PATH, "\xEC\0");   //μ
			SetWindowTextW(hWnd, wcsText);
		}
		break;

		case 'm':
		{
			WCHAR wcsText[MAX_PATH];

			GetWindowTextW(hWnd, wcsText, MAX_PATH);
			MakeUnitStringW((void *)(0x01637C48), wcsText, MAX_PATH, "m");
			SetWindowTextW(hWnd, wcsText);
		}
		break;

		default:
		{
			if (((wParam >= 'A') && (wParam <= 'Z')) || ((wParam >= 'a') && (wParam <= 'z')))
				break;

			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
		}
		break;
		}

	}
	break;

	case WM_SETFOCUS:
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		SetInputType(ITID_NUM);
		break;

	case WM_KILLFOCUS:
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		SetInputType(ITID_UNKNOWN);
		break;

	default:
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return lResult;
}


CALDLG_CTXT dcCal_7 =
{
	NULL,
	IDD_CAL_7,
	DFL_CMD_NEXT | DFL_LBL_INFO1,
	&fndeCal_7,
	&fndpCal_7,
	NULL,
	NULL,
	NULL,
	L"Modify Cal Kit\0更换校准件\0更換校準件\0\0",
	L"Define STDs\0定义标准\0定義標準\0\0",
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	L"Exit\0退出\0退出\0\0",
	RESERVE_DWORD4,
	RESERVE_DWORD4
};