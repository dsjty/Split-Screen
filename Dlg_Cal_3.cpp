#include "stdafx.h"

extern  CALDLG_CTXT dcCal_3_1;

extern CalKit cCalkit;

#define PRIV_CMDTEXT            (const char *)0x00B63F5C

INT_PTR WINAPI fndeCal_3(PCALDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	//if (lpDlgCtxt == NULL)
	//	return -1;
	//
	//INT_PTR lResult = 0;
	//
	//switch (dwCode)
	//{
	//case DEC_ENTER:
	//{
	//	OrigSoftMenu_Enter(CA_CAL_TSC);
	//	OrigSoftMenu_UpdateItems(CA_CAL_TSC);
	//
	//	OrigSoftMenu_Enter(CA_CTC);
	//	OrigSoftMenu_UpdateItems(CA_CTC);
	//
	//	SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL3_LBL_CALTYPE), GetStringByIndex(L"Cal Type\0校准类型\0校准類型\0\0", nLangId));
	//
	//	SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_CAL3_LBL_CALKIT), GetStringByIndex(L"Cal Kit\0校准件\0校准件\0\0", nLangId));
	//
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALTYPE), 0, GetStringByIndex(L"ERES\0\0", nLangId));
	//
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALTYPE), 1, GetStringByIndex(L"SOLT2\0\0", nLangId));
	//
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 0, cCalkit.CalKitList[0].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 1, cCalkit.CalKitList[1].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 2, cCalkit.CalKitList[2].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 3, cCalkit.CalKitList[3].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 4, cCalkit.CalKitList[4].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 5, cCalkit.CalKitList[5].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 6, cCalkit.CalKitList[6].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 7, cCalkit.CalKitList[7].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 8, cCalkit.CalKitList[8].c_str());
	//	ComboBox_InsertStringW(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 9, cCalkit.CalKitList[9].c_str());
	//
	//	int nIndex = 0;
	//	GetButtonStateIndex(PRIV_CMDTEXT, NULL, &nIndex, 0x00010000);
	//
	//	if (nIndex == 1)
	//		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALTYPE), 1);
	//	else
	//		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALTYPE), 0);
	//
	//	ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_CAL3_CB_CALKIT), 0);
	//}
	//break;
	//
	//case DEC_CMD_NEXT:
	//{
	//	int nIndex = 0;
	//	int nCalType, nCalKit;
	//
	//	nCalType = ComboBox_GetCurSel(GetDlgItem(lpDlgCtxt->hwClient, IDC_CAL3_CB_CALTYPE));
	//	nCalKit = ComboBox_GetCurSel(GetDlgItem(lpDlgCtxt->hwClient, IDC_CAL3_CB_CALKIT));
	//
	//	if (nCalType == CB_ERR || nCalKit == CB_ERR) 
	//		break;
	//
	//	OrigSoftMenu_Enter(CA_CALIBRAT_CK);
	//	OrigSoftMenu_ItemClicked2(CA_CALIBRAT_CK, TA_CALIBRAT_CK, nCalKit);
	//
	//	switch (nCalType)
	//	{
	//	case 0:
	//	{
	//		GetButtonStateIndex(PRIV_CMDTEXT, NULL, &nIndex, 0x00010000);
	//
	//		if (nIndex != 0)
	//		{
	//			OrigSoftMenu_ItemClicked2(CA_CTC, TA_CTC, 6);
	//		}
	//		UpdateDialog_Cal(&dcCal_3_1, 0);
	//	}
	//	break;
	//	case 1:
	//	{
	//		GetButtonStateIndex(PRIV_CMDTEXT, NULL, &nIndex, 0x00010000);
	//
	//		if (nIndex != 1)
	//		{
	//			OrigSoftMenu_ItemClicked2(CA_CTC, TA_CTC, 6);
	//		}
	//		UpdateDialog_Cal(&dcCal_3_1, 0);
	//	}
	//	break;
	//
	//	default:
	//		break;
	//	}
	//}
	//break;
	//
	//case DEC_CMD_CANCEL:
	//	lResult = TRUE;
	//	break;
	//
	//case DEC_CMD_CLOSE:
	//	lResult = TRUE;
	//	break;
	//}

	return TRUE;
}

INT_PTR CALLBACK fndpCal_3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//switch (msg)
	//{
	//case WM_INITDIALOG:
	//	return TRUE;
	//case WM_CTLCOLORSTATIC:
	//{
	//	if ((lParam == (LPARAM)GetDlgItem(hDlg, IDC_CAL3_LBL_CALTYPE)) || (lParam == (LPARAM)GetDlgItem(hDlg, IDC_CAL3_LBL_CALKIT)))
	//	{
	//		SetTextColor((HDC)wParam, RGB(250, 32, 32));
	//		SetBkMode((HDC)wParam, TRANSPARENT);
	//		return (INT_PTR)GetStockObject(NULL_BRUSH);
	//	}
	//}
	//break;
	//}

	return FALSE;
}

CALDLG_CTXT dcCal_3 =
{
	NULL,
	IDD_CAL_3,
	DFL_CMD_NEXT | DFL_LBL_INFO1,
	&fndeCal_3,
	&fndpCal_3,
	NULL,
	NULL,
	NULL,
	L"Test Set Cal\0测试装置校准\0測試裝置校準\0\0",
	NULL,
	L"\0\0",
	NULL,
	NULL,
	NULL,
	NULL,
	L"Exit\0退出\0退出\0\0",
	RESERVE_DWORD4,
	RESERVE_DWORD4
};