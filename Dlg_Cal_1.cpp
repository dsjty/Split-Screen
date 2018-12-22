#include "stdafx.h"

extern CALDLG_CTXT dcCal_1_0;
extern CALDLG_CTXT dcCal_1_1;
extern CALDLG_CTXT dcCal_1_2;
extern CALDLG_CTXT dcCal_1_3;
extern CALDLG_CTXT dcCal_1_4;
extern CALDLG_CTXT dcCal_1_5;
extern CALDLG_CTXT dcCal_1_6;


extern CalKit cCalkit;

//85038A/F/M    85039B   85036B/E   85032B/E   85032F   85052D   85033D   85033E

INT_PTR WINAPI fndeCal_1(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL) 
		return -1;

	HWND hCALKIT = GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALKIT);

	INT_PTR lResult = 0;
	int nCalSel = 0;

	switch (dwCode)
	{
	case DEC_ENTER:

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL1_LBL_CALTYPE), GetStringByIndex(L"Cal Type\0校准类型\0校准類型\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL1_LBL_CALKIT), GetStringByIndex(L"Cal Kit\0校准件\0校准件\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 0, GetStringByIndex(L"Response (Open)\0响应 (开路器)\0響應 (開路器)\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 1, GetStringByIndex(L"Response (Short)\0响应 (短路器)\0響應 (短路器)\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 2, GetStringByIndex(L"Response (Thru)\0响应 (短接)\0響應 (短接)\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 3, GetStringByIndex(L"Enhanced Response\0增强型响应\0增強型響應\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 4, GetStringByIndex(L"1-Port Cal\0\x31-端口校准\0\x31-端口校準\0\0", nLangId));
		
		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 5, GetStringByIndex(L"2-Port Cal\0\x32-端口校准\0\x32-端口校準\0\0", nLangId));

		ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 6, GetStringByIndex(L"2PortTRLCal\0\x32端口TRL校准\0\x32端口TRL校準\0\0", nLangId));


		OrigSoftMenu_Enter(CA_CAL_CAL);
		OrigSoftMenu_UpdateItems(CA_CAL_CAL);

		for (int i = 0; i < 26; i++)
		{
			ComboBox_InsertStringW(hCALKIT, i, cCalkit.CalKitList[i].c_str());
		}

		{
			WCHAR wcsTmp[MAX_PATH] = {0};
			GetInputStringObjectW((void *)0x010B3628, wcsTmp, MAX_PATH, &nCalSel);
			nCalSel = 0;
			for (int i = 0; i < 26; i++)
			{
				if (0 == wcscmp(wcsTmp, cCalkit.OldCalKitList[i].c_str()))
				{
					nCalSel = i;
					break;
				}
			}
		}
		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_CAL1_CB_CALTYPE), 0);
		ComboBox_SetCurSel(hCALKIT, nCalSel);
		break;

	case DEC_CMD_NEXT:
	{
		int nCalType, nCalKit;

		nCalType = ComboBox_GetCurSel(GetDlgItem(lpDlgCtxt->hwClient, IDC_CAL1_CB_CALTYPE));
		nCalKit = ComboBox_GetCurSel(GetDlgItem(lpDlgCtxt->hwClient, IDC_CAL1_CB_CALKIT));

		if (nCalType == CB_ERR || nCalKit == CB_ERR) 
			break;

		OrigSoftMenu_Enter(CA_CAL_CALK);
		OrigSoftMenu_UpdateItems(CA_CAL_CALK);
		OrigSoftMenu_ItemClicked2(CA_CAL_CALK, TA_CAL_CALK, nCalKit);

		switch (nCalType)
		{
		case 0:
			UpdateDialog_Cal(&dcCal_1_0, 0);
			break;
		case 1:
			UpdateDialog_Cal(&dcCal_1_1, 0);
			break;
		case 2:
			UpdateDialog_Cal(&dcCal_1_2, 0);
			break;
		case 3:
			UpdateDialog_Cal(&dcCal_1_3, 0);
			break;
		case 4:
			UpdateDialog_Cal(&dcCal_1_4, 0);
			break;
		case 5:
			UpdateDialog_Cal(&dcCal_1_5, 0);
			break;
		case 6:
			UpdateDialog_Cal(&dcCal_1_6, 0);
			break;
		default:
			break;
		}
	}
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

INT_PTR CALLBACK fndpCal_1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{		
	case WM_PAINT:
		return 0;
	case WM_INITDIALOG:
		return TRUE;
	case WM_CTLCOLORSTATIC:
	{
		if ((lParam == (LPARAM)GetDlgItem(hDlg, IDC_CAL1_LBL_CALTYPE)) || (lParam == (LPARAM)GetDlgItem(hDlg, IDC_CAL1_LBL_CALKIT)))
		{
			SetTextColor((HDC)wParam, RGB(250, 32, 32));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (INT_PTR)GetStockObject(NULL_BRUSH);
		}
	}
	break;
	}

	return FALSE;
}

CALDLG_CTXT dcCal_1 =
{
	NULL,
	IDD_CAL_1,
	DFL_CMD_NEXT | DFL_LBL_INFO1,
	&fndeCal_1,
	&fndpCal_1,
	NULL,
	NULL,
	NULL,
	L"Manual Calibration\0手动校准\0手動校準\0\0",
	NULL,
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	L"Cancel\0取消\0取消\0\0",
	RESERVE_DWORD4,
	RESERVE_DWORD4
};