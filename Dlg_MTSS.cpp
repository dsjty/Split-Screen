#include "stdafx.h"
#include "Dlg_MTSS.h"

#define MULTIPORT_TEST_SET_1         0
#define MULTIPORT_TEST_SET_2         1

LRESULT CALLBACK wp_MT_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int iPortMenuNum = 4;

static void *lpThis_DC[4] =
{
	NULL, NULL, NULL, NULL
};

typedef struct _CTRLLINE_
{
	char Line1 : 1;
	char Line2 : 1;
	char Line3 : 1;
	char Line4 : 1;
	char Line5 : 1;
	char Line6 : 1;
	char Line7 : 1;
	char Line8 : 1;
}*PCTRLLINE, CTRLLINE;

static int nTSMode, nTraCount = 4, nCurTra = 0;
static void *lpThis_MTSSMode[2] = { NULL, NULL };
static void *lpThis_MTSSMode_RC[2] = { NULL, NULL };
static void *lpThis_R = NULL, *lpThis_G = NULL, *lpThis_B = NULL;
static int nMTSSCur[2] = { 0,0 };

void UpdateMTSSValue(HWND hDlg);
void ComboBoxClick(HWND hDlg, int nCurTra, int nColor, int nCurSel);
VOID SelectTSClick(HWND hDlg, int nTSSel);
void ComboSelectInit(HWND hDlg, int IDC_SER, LPCSTR *lpcSTR, int i);
VOID ButtonClick(HWND hDlg, int iCLNum, int iCurSel);
bool GetSubMenustatus(void *lpThis);

bool is_allow(int flag, int permission)
{
	return ((flag & permission) == permission);
}

INT_PTR WINAPI fndeMTSS(PDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
{
	if (lpDlgCtxt == NULL)
		return -1;

	INT_PTR lResult = 0;
	void *lpCA_NOR = nullptr;
	void *lpCA_NOR_DT = nullptr;


	switch (dwCode)
	{
	case DEC_ENTER:
	{
		OrigSoftMenu_Enter(CA_SYSTEM);
		OrigSoftMenu_UpdateItems(CA_SYSTEM);

		OrigSoftMenu_Enter(CA_SYSTEM_MTSS);
		OrigSoftMenu_UpdateItems(CA_SYSTEM_MTSS);

		lpThis_MTSSMode[0] = lpTestSet1 = (void*)((DWORD)GetSubMenuPointer(CA_SYSTEM_MTSS, 0) - BASE);
		OrigSoftMenu_Enter(lpTestSet1);
		OrigSoftMenu_UpdateItems(lpTestSet1);

		lpTestSet1_Sel = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 0) - BASE);
		lpTestSet1_Port1 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 3) - BASE);
		lpTestSet1_Port2 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 4) - BASE);
		lpTestSet1_Port3 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 5) - BASE);
		lpTestSet1_Port4 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 6) - BASE);
		lpTestSet1_CLA = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 7) - BASE);


		lpThis_MTSSMode[1] = lpTestSet2 = (void*)((DWORD)GetSubMenuPointer(CA_SYSTEM_MTSS, 1) - BASE);
		OrigSoftMenu_Enter(lpTestSet2);
		OrigSoftMenu_UpdateItems(lpTestSet2);

		lpTestSet2_Sel = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 0) - BASE);
		lpTestSet2_Port1 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 3) - BASE);
		lpTestSet2_Port2 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 4) - BASE);
		lpTestSet2_Port3 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 5) - BASE);
		lpTestSet2_Port4 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 6) - BASE);
		lpTestSet2_CLA = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 7) - BASE);


		nTSMode = 0;
		iPortMenuNum = 4;
		void *lpSubThis = GetSubMenuPointer(nTSMode ? lpTestSet1 : lpTestSet2, 0);
		OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
		OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
		OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), 0);

		Button_SetCheck(GetDlgItem((HWND)lParam2, IDC_RADIO_Test1), BST_CHECKED);

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_RADIO_Test1), GetStringByIndex(L"Test Set 1\0测试装置1\0測試裝置1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_RADIO_Test2), GetStringByIndex(L"Test Set 2\0测试装置2\0測試裝置2\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_Sel), GetStringByIndex(L"Select Test Set\0选择测试装置\0選擇測試裝置\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_MTSS_Ctrl), GetStringByIndex(L"Control\0控制\0控制\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_MTSS_Prop), GetStringByIndex(L"Property\0校准信息显示\0校准信息顯示\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port1), GetStringByIndex(L"Port 1\0端口 1\0端口 1\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port2), GetStringByIndex(L"Port 2\0端口 2\0端口 2\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port3), GetStringByIndex(L"Port 3\0端口 3\0端口 3\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port4), GetStringByIndex(L"Port 4\0端口 4\0端口 4\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port5), GetStringByIndex(L"Port 5\0端口 5\0端口 5\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port6), GetStringByIndex(L"Port 6\0端口 6\0端口 6\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port7), GetStringByIndex(L"Port 7\0端口 7\0端口 7\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port8), GetStringByIndex(L"Port 8\0端口 8\0端口 8\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port9), GetStringByIndex(L"Port 9\0端口 9\0端口 9\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_Port10), GetStringByIndex(L"Port10\0端口10\0端口10\0\0", nLangId));


		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineA), GetStringByIndex(L"Contrlo Line\0控制线\0控制線\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line1), GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line2), GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line3), GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line4), GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line5), GetStringByIndex(L"Line5( LOW )\0线5( 低 )\0線5( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line6), GetStringByIndex(L"Line6( LOW )\0线6( 低 )\0線6( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line7), GetStringByIndex(L"Line7( LOW )\0线7( 低 )\0線7( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlA_Line8), GetStringByIndex(L"Line8( LOW )\0线8( 低 )\0線8( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlA_DC), GetStringByIndex(L"DC Source\0直流电源\0直流電源\0\0", nLangId));


		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineB), GetStringByIndex(L"Contrlo Line B\0控制线B\0控制線B\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlB_DC), GetStringByIndex(L"DC Source\0直流电源\0直流電源\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line1), GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line2), GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line3), GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line4), GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));


		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineC), GetStringByIndex(L"Contrlo Line C\0控制线C\0控制線C\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlC_DC), GetStringByIndex(L"DC Source\0直流电源\0直流電源\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line1), GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line2), GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line3), GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line4), GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineD), GetStringByIndex(L"Contrlo Line D\0控制线D\0控制線D\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlD_DC), GetStringByIndex(L"DC Source\0直流电源\0直流電源\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line1), GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line2), GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line3), GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
		SetWindowTextW(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line4), GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

		ShowWindow(GetDlgItem((HWND)lParam2, IDC_COMBO_Port5), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_Port5), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_COMBO_Port6), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_Port6), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_COMBO_Port7), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_Port7), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_Port8), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_Port9), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_Port10), 0);

		ShowWindow(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineB), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line1), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line2), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line3), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlB_Line4), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlB_DC), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_EDIT_CtrlB_DC), 0);

		ShowWindow(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineC), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line1), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line2), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line3), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlC_Line4), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlC_DC), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_EDIT_CtrlC_DC), 0);

		ShowWindow(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlLineD), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line1), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line2), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line3), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_BTN_CtrlD_Line4), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_STATIC_CtrlD_DC), 0);
		ShowWindow(GetDlgItem((HWND)lParam2, IDC_EDIT_CtrlD_DC), 0);

		ComboSelectInit((HWND)lParam2, IDC_MTSS_SelTS, (LPCSTR*)TestSetList, sizeof(TestSetList) / sizeof(LPCSTR));
		ComboSelectInit((HWND)lParam2, IDC_COMBO_Port1, (LPCSTR*)List91_9P1, sizeof(List91_9P1) / sizeof(LPCSTR));
		ComboSelectInit((HWND)lParam2, IDC_COMBO_Port2, (LPCSTR*)List91_9P2, sizeof(List91_9P2) / sizeof(LPCSTR));
		ComboSelectInit((HWND)lParam2, IDC_COMBO_Port3, (LPCSTR*)List91_9P3, sizeof(List91_9P3) / sizeof(LPCSTR));
		ComboSelectInit((HWND)lParam2, IDC_COMBO_Port4, (LPCSTR*)List91_9P4, sizeof(List91_9P4) / sizeof(LPCSTR));

		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_MTSS_SelTS), 0);
		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_COMBO_Port1), 0);
		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_COMBO_Port2), 0);
		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_COMBO_Port3), 0);
		ComboBox_SetCurSel(GetDlgItem((HWND)lParam2, IDC_COMBO_Port4), 0);

		SelectTSClick((HWND)lParam2, 0);
	}
	break;

	case DEC_CMD_CLOSE:
		lResult = TRUE;
		break;
	}

	return lResult;
}

void UpdateMTSSValue(HWND hDlg)
{
	int nCtrlLine = 0;
	int nTSSel = 0;
	int nPortSel = 0;

	WCHAR wcsTmp[MAX_PATH] = { 0 };

	if (nTSMode < 0 || nTSMode > 1)
		return;

	if (lpThis_MTSSMode[nTSMode] == NULL)
	{
		lpThis_MTSSMode[nTSMode] = GetSubMenuPointer(CA_SYSTEM_MTSS, nTSMode);
	}

	OrigSoftMenu_Enter(lpThis_MTSSMode[nTSMode]);
	OrigSoftMenu_UpdateItems(lpThis_MTSSMode[nTSMode]);

	nTSSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));


	nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port1 : lpTestSet2_Port1);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port1), nPortSel);
	nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port2 : lpTestSet2_Port2);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port2), nPortSel);
	nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port3 : lpTestSet2_Port3);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port3), nPortSel);
	nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port4 : lpTestSet2_Port4);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port4), nPortSel);
	if (iPortMenuNum == 7)
	{
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port5 : lpTestSet2_Port5);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port6 : lpTestSet2_Port6);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port7 : lpTestSet2_Port7);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
	}
	else if (iPortMenuNum == 10)
	{
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port5 : lpTestSet2_Port5);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port6 : lpTestSet2_Port6);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port7 : lpTestSet2_Port7);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port8 : lpTestSet2_Port8);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port8), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port9 : lpTestSet2_Port9);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port9), nPortSel);
		nPortSel = GetSubMenustatus(!nTSMode ? lpTestSet1_Port10 : lpTestSet2_Port10);
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port10), nPortSel);
	}


	{
		int blCHK = 0;
		GetButtonStateIndex((char*)((DWORD)szTestSetCtrl[nTSMode] - BASE), 0, &blCHK, 0);
		Button_SetCheck(GetDlgItem(hDlg, IDC_MTSS_Ctrl), blCHK ? BST_CHECKED : BST_UNCHECKED);

		GetButtonStateIndex((char*)((DWORD)szTestSetProp[nTSMode] - BASE), 0, &blCHK, 0);
		Button_SetCheck(GetDlgItem(hDlg, IDC_MTSS_Prop), blCHK ? BST_CHECKED : BST_UNCHECKED);
	}

	if (nTSSel == 0 || nTSSel == 1 || nTSSel == 2)
		GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
	else
		GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);

	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line5), (is_allow(nCtrlLine, 0x10)) == 1 ? GetStringByIndex(L"Line5( HIGH )\0线5( 高 )\0線5( 高 )\0\0", nLangId) : GetStringByIndex(L"Line5( LOW )\0线5( 低 )\0線5( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line6), (is_allow(nCtrlLine, 0x20)) == 1 ? GetStringByIndex(L"Line6( HIGH )\0线6( 高 )\0線6( 高 )\0\0", nLangId) : GetStringByIndex(L"Line6( LOW )\0线6( 低 )\0線6( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line7), (is_allow(nCtrlLine, 0x40)) == 1 ? GetStringByIndex(L"Line7( HIGH )\0线7( 高 )\0線7( 高 )\0\0", nLangId) : GetStringByIndex(L"Line7( LOW )\0线7( 低 )\0線7( 低 )\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line8), (is_allow(nCtrlLine, 0x80)) == 1 ? GetStringByIndex(L"Line8( HIGH )\0线8( 高 )\0線8( 高 )\0\0", nLangId) : GetStringByIndex(L"Line8( LOW )\0线8( 低 )\0線8( 低 )\0\0", nLangId));

	//用于统一更新DC编辑框
	if (IsWindowVisible(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC)))
	{
		char strTmp[MAX_PATH] = { 0 };
		void *lpTable = nullptr;

		if (nTSMode == 0)
		{
			OrigSoftMenu_Enter(lpTestSet1_CLA);
			OrigSoftMenu_UpdateItems(lpTestSet1_CLA);

			lpTable = (void**)((DWORD)lpTestSet1_CLA + BASE);
			FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
			MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
			SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), wcsTmp);
			ZeroMemory(wcsTmp, MAX_PATH - 1);

			if (IsWindowVisible(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1)))
			{
				OrigSoftMenu_Enter(lpTestSet1_CLB);
				OrigSoftMenu_UpdateItems(lpTestSet1_CLB);

				GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[1][0] - BASE), 0, &nCtrlLine, 0);

				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

				lpTable = (void**)((DWORD)lpTestSet1_CLB + BASE);
				FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
				SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), wcsTmp);
				ZeroMemory(wcsTmp, MAX_PATH - 1);


				OrigSoftMenu_Enter(lpTestSet1_CLC);
				OrigSoftMenu_UpdateItems(lpTestSet1_CLC);

				GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[2][0] - BASE), 0, &nCtrlLine, 0);

				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

				lpTable = (void**)((DWORD)lpTestSet1_CLC + BASE);
				FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
				SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), wcsTmp);
				ZeroMemory(wcsTmp, MAX_PATH - 1);


				OrigSoftMenu_Enter(lpTestSet1_CLD);
				OrigSoftMenu_UpdateItems(lpTestSet1_CLD);

				GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[3][0] - BASE), 0, &nCtrlLine, 0);

				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
				
				lpTable = (void**)((DWORD)lpTestSet1_CLD + BASE);
				FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
				SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), wcsTmp);
				ZeroMemory(wcsTmp, MAX_PATH - 1);
			}
		}
		else
		{
			ZeroMemory(wcsTmp, MAX_PATH - 1);

			OrigSoftMenu_Enter(lpTestSet2_CLA);
			OrigSoftMenu_UpdateItems(lpTestSet2_CLA);

			lpTable = (void**)((DWORD)lpTestSet2_CLA + BASE);
			FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
			MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
			SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), wcsTmp);
			ZeroMemory(wcsTmp, MAX_PATH - 1);

			if (IsWindowVisible(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1)))
			{
				OrigSoftMenu_Enter(lpTestSet2_CLB);
				OrigSoftMenu_UpdateItems(lpTestSet2_CLB);

				GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[1][1] - BASE), 0, &nCtrlLine, 0);
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

				lpTable = (void**)((DWORD)lpTestSet2_CLB + BASE);
				FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
				SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), wcsTmp);
				ZeroMemory(wcsTmp, MAX_PATH - 1);


				OrigSoftMenu_Enter(lpTestSet2_CLC);
				OrigSoftMenu_UpdateItems(lpTestSet2_CLC);

				GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[2][1] - BASE), 0, &nCtrlLine, 0);
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

				lpTable = (void**)((DWORD)lpTestSet2_CLC + BASE);
				FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
				SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), wcsTmp);
				ZeroMemory(wcsTmp, MAX_PATH - 1);


				OrigSoftMenu_Enter(lpTestSet2_CLD);
				OrigSoftMenu_UpdateItems(lpTestSet2_CLD);

				GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[3][1] - BASE), 0, &nCtrlLine, 0);
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
				SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));

				lpTable = (void**)((DWORD)lpTestSet2_CLD + BASE);
				FmtValueToString((void *)(0x010B4870), strTmp, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, strTmp, -1, wcsTmp, MAX_PATH);
				SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), wcsTmp);
			}
		}
	}
}

INT_PTR CALLBACK fndpMTSS(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int nCtrlLine = 0;
	int index = 0;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		wpfn_InputEdit = (WNDPROC)SetWindowLong(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), GWL_WNDPROC, (LONG)&wp_MT_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), GWL_WNDPROC, (LONG)&wp_MT_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), GWL_WNDPROC, (LONG)&wp_MT_InputEdit);
		SetWindowLong(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), GWL_WNDPROC, (LONG)&wp_MT_InputEdit);
		return TRUE;
	}

	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == BN_CLICKED)
			{
				switch (wId)
				{
				case IDC_MTSS_Ctrl:
					OrigSoftMenu_Enter(lpThis_MTSSMode[nTSMode]);
					OrigSoftMenu_UpdateItems(lpThis_MTSSMode[nTSMode]);
					OrigSoftMenu_ItemClicked2(lpThis_MTSSMode[nTSMode], TA_SYSTEM_MTSS_TS, 1);
					break;
				case IDC_MTSS_Prop:
					OrigSoftMenu_Enter(lpThis_MTSSMode[nTSMode]);
					OrigSoftMenu_UpdateItems(lpThis_MTSSMode[nTSMode]);
					OrigSoftMenu_ItemClicked2(lpThis_MTSSMode[nTSMode], TA_SYSTEM_MTSS_TS, 2);
					break;
				case IDC_RADIO_Test1:
					nTSMode = 0;
					ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS), nMTSSCur[0]);
					lpThis_MTSSMode[nTSMode] = (void*)((DWORD)GetSubMenuPointer(CA_SYSTEM_MTSS, 0) - BASE);
					UpdateMTSSValue(hDlg);
					break;
				case IDC_RADIO_Test2:
					nTSMode = 1;
					ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS), nMTSSCur[1]);
					lpThis_MTSSMode[nTSMode] = (void*)((DWORD)GetSubMenuPointer(CA_SYSTEM_MTSS, 1) - BASE);
					UpdateMTSSValue(hDlg);
					break;
				case IDC_BTN_CtrlA_Line1:
				{
					ButtonClick(hDlg, 1, 0);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line2:
				{
					ButtonClick(hDlg, 1, 1);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line3:
				{
					ButtonClick(hDlg, 1, 2);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line4:
				{
					ButtonClick(hDlg, 1, 3);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line5:
				{
					ButtonClick(hDlg, 1, 4);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line5), (is_allow(nCtrlLine, 0x10)) == 1 ? GetStringByIndex(L"Line5( HIGH )\0线5( 高 )\0線5( 高 )\0\0", nLangId) : GetStringByIndex(L"Line5( LOW )\0线5( 低 )\0線5( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line6:
				{
					ButtonClick(hDlg, 1, 5);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line6), (is_allow(nCtrlLine, 0x20)) == 1 ? GetStringByIndex(L"Line6( HIGH )\0线6( 高 )\0線6( 高 )\0\0", nLangId) : GetStringByIndex(L"Line6( LOW )\0线6( 低 )\0線6( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line7:
				{
					ButtonClick(hDlg, 1, 6);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line7), (is_allow(nCtrlLine, 0x40)) == 1 ? GetStringByIndex(L"Line7( HIGH )\0线7( 高 )\0線7( 高 )\0\0", nLangId) : GetStringByIndex(L"Line7( LOW )\0线7( 低 )\0線7( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlA_Line8:
				{
					ButtonClick(hDlg, 1, 7);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					if (nTSel == 0 || nTSel == 1 || nTSel == 2)
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine1[nTSMode] - BASE), 0, &nCtrlLine, 0);
					else
						GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[0][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlA_Line8), (is_allow(nCtrlLine, 0x80)) == 1 ? GetStringByIndex(L"Line8( HIGH )\0线8( 高 )\0線8( 高 )\0\0", nLangId) : GetStringByIndex(L"Line8( LOW )\0线8( 低 )\0線8( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlB_Line1:
				{
					ButtonClick(hDlg, 2, 0);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[1][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlB_Line2:
				{
					ButtonClick(hDlg, 2, 1);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[1][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlB_Line3:
				{
					ButtonClick(hDlg, 2, 2);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[1][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlB_Line4:
				{
					ButtonClick(hDlg, 2, 3);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[1][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlC_Line1:
				{
					ButtonClick(hDlg, 3, 0);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[2][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlC_Line2:
				{
					ButtonClick(hDlg, 3, 1);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[2][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlC_Line3:
				{
					ButtonClick(hDlg, 3, 2);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[2][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlC_Line4:
				{
					ButtonClick(hDlg, 3, 3);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[2][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlD_Line1:
				{
					ButtonClick(hDlg, 4, 0);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[3][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), (is_allow(nCtrlLine, 0x1)) == 1 ? GetStringByIndex(L"Line1( HIGH )\0线1( 高 )\0線1( 高 )\0\0", nLangId) : GetStringByIndex(L"Line1( LOW )\0线1( 低 )\0線1( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlD_Line2:
				{
					ButtonClick(hDlg, 4, 1);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[3][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), (is_allow(nCtrlLine, 0x2)) == 1 ? GetStringByIndex(L"Line2( HIGH )\0线2( 高 )\0線2( 高 )\0\0", nLangId) : GetStringByIndex(L"Line2( LOW )\0线2( 低 )\0線2( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlD_Line3:
				{
					ButtonClick(hDlg, 4, 2);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[3][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), (is_allow(nCtrlLine, 0x4)) == 1 ? GetStringByIndex(L"Line3( HIGH )\0线3( 高 )\0線3( 高 )\0\0", nLangId) : GetStringByIndex(L"Line3( LOW )\0线3( 低 )\0線3( 低 )\0\0", nLangId));
					break;
				}
				case IDC_BTN_CtrlD_Line4:
				{
					ButtonClick(hDlg, 4, 3);

					int nTSel = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));

					GetButtonStateIndex((char*)((DWORD)szTSCtrlLine4[3][nTSMode] - BASE), 0, &nCtrlLine, 0);
					SetWindowTextW(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), (is_allow(nCtrlLine, 0x8)) == 1 ? GetStringByIndex(L"Line4( HIGH )\0线4( 高 )\0線4( 高 )\0\0", nLangId) : GetStringByIndex(L"Line4( LOW )\0线4( 低 )\0線4( 低 )\0\0", nLangId));
					break;
				}
				case IDOK:
					DestroyDialog_Def(0);
					break;
				}
				UpdateMTSSValue(hDlg);
			}
			else if (wNc == CBN_SELCHANGE)
			{
				switch (wId)
				{
				case IDC_MTSS_SelTS:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_MTSS_SelTS));
					nMTSSCur[nTSMode] = index;
					switch (index)
					{
					case 0:
					case 1:
					case 3:
					case 5:
					case 7:
						iPortMenuNum = 4;
						break;
					case 2:
					case 4:
						iPortMenuNum = 7;
						break;
					case 6:
						iPortMenuNum = 10;
						break;
					default:
						break;
					}

					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 0);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);

					SelectTSClick(hDlg, index);
					break;
				}
				case IDC_COMBO_Port1:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port1));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 3);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port2:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port2));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 4);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port3:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port3));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 5);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port4:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port4));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 6);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port5:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 7);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port6:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 8);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port7:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 9);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port8:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port8));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 10);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port9:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port9));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 11);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				case IDC_COMBO_Port10:
				{
					index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port10));
					void *lpSubThis = GetSubMenuPointer(!nTSMode ? lpTestSet1 : lpTestSet2, 12);
					OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));
					OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), index);
					break;
				}
				}
				UpdateMTSSValue(hDlg);
			}
		}
		break;
	}

	case WM_CLOSE:
	{
		DestroyDialog_Def(0);
		break;
	}
	}
	return FALSE;
}



DLG_CTXT dcMTSSWizard
{
	NULL,
	IDD_MultiPortTest,
	0,
	&fndeMTSS,
	&fndpMTSS,
	RESERVE_DWORD4
};

//************************************
// Method:    SelectTSClick
// FullName:  SelectTSClick
// Access:    public 
// Returns:   VOID
// Qualifier:
// Parameter: HWND hDlg
// Parameter: 还差一个，选择后，其他select选项会变
//************************************
VOID SelectTSClick(HWND hDlg, int nTSSel)
{
	int nPortSel = NULL;
	OrigSoftMenu_UpdateItems(nTSMode ? lpTestSet2 : lpTestSet1);
	switch (nTSSel)
	{
	case 0:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));

		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List91_9P1, sizeof(List91_9P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List91_9P2, sizeof(List91_9P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List91_9P3, sizeof(List91_9P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List91_9P4, sizeof(List91_9P4) / sizeof(LPCSTR));

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlA_DC), 0);

		break;
	}
	case 1:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List91_13P1, sizeof(List91_13P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List91_13P2, sizeof(List91_13P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List91_13P3, sizeof(List91_13P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List91_13P4, sizeof(List91_13P4) / sizeof(LPCSTR));

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlA_DC), 0);

		break;
	}
	case 2:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port5));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port6));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port7));
		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List91_16P1, sizeof(List91_16P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List91_16P2, sizeof(List91_16P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List91_13P3, sizeof(List91_13P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List91_13P4, sizeof(List91_13P4) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port5, (LPCSTR*)List91_16P5, sizeof(List91_16P5) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port6, (LPCSTR*)List91_16P6, sizeof(List91_16P6) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port7, (LPCSTR*)List91_16P7, sizeof(List91_16P7) / sizeof(LPCSTR));

		
		if (!nTSMode)
		{
			OrigSoftMenu_UpdateItems(lpTestSet1);
			if (!lpTestSet1_Port5)
				lpTestSet1_Port5 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 7) - BASE);
			if (!lpTestSet1_Port6)
				lpTestSet1_Port6 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 8) - BASE);
			if (!lpTestSet1_Port7)
				lpTestSet1_Port7 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 9) - BASE);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port5);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port6);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port7);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
		}
		else
		{
			OrigSoftMenu_UpdateItems(lpTestSet2);
			if (!lpTestSet2_Port5)
				lpTestSet2_Port5 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 7) - BASE);
			if (!lpTestSet2_Port6)
				lpTestSet2_Port6 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 8) - BASE);
			if (!lpTestSet2_Port7)
				lpTestSet2_Port7 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 9) - BASE);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port5);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port6);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port7);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
		}


		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 0);


		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlA_DC), 0);
		break;
	}
	case 3:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List92_13P1, sizeof(List92_13P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List92_13P2, sizeof(List92_13P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List92_13P3, sizeof(List92_13P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List92_13P4, sizeof(List92_13P4) / sizeof(LPCSTR));

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineA), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 1);


		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 1);
		
		nTSMode ? lpTestSet2_CLA : lpTestSet1_CLA = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 1) - BASE);
		nTSMode ? lpTestSet2_CLB : lpTestSet1_CLB = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 2) - BASE);
		nTSMode ? lpTestSet2_CLC : lpTestSet1_CLC = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 3) - BASE);
		nTSMode ? lpTestSet2_CLD : lpTestSet1_CLD = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 4) - BASE);
		break;
	}
	case 4:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port5));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port6));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port7));

		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List92_16P1, sizeof(List92_16P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List92_16P2, sizeof(List92_16P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List92_13P3, sizeof(List92_13P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List92_13P4, sizeof(List92_13P4) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port5, (LPCSTR*)List92_16P5, sizeof(List92_16P5) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port6, (LPCSTR*)List92_16P6, sizeof(List92_16P6) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port7, (LPCSTR*)List92_16P7, sizeof(List92_16P7) / sizeof(LPCSTR));

		if (!nTSMode)
		{
			OrigSoftMenu_UpdateItems(lpTestSet1);
			if (!lpTestSet1_Port5)
				lpTestSet1_Port5 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 7) - BASE);
			if (!lpTestSet1_Port6)
				lpTestSet1_Port6 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 8) - BASE);
			if (!lpTestSet1_Port7)
				lpTestSet1_Port7 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 9) - BASE);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port5);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port6);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port7);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
		}
		else
		{
			OrigSoftMenu_UpdateItems(lpTestSet2);
			if (!lpTestSet2_Port5)
				lpTestSet2_Port5 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 7) - BASE);
			if (!lpTestSet2_Port6)
				lpTestSet2_Port6 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 8) - BASE);
			if (!lpTestSet2_Port7)
				lpTestSet2_Port7 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 9) - BASE);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port5);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port6);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port7);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
		}

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineA), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 1);

		nTSMode ? lpTestSet2_CLA : lpTestSet1_CLA = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 1) - BASE);
		nTSMode ? lpTestSet2_CLB : lpTestSet1_CLB = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 2) - BASE);
		nTSMode ? lpTestSet2_CLC : lpTestSet1_CLC = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 3) - BASE);
		nTSMode ? lpTestSet2_CLD : lpTestSet1_CLD = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 4) - BASE);
		break;
	}
	case 5:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List92_22P1, sizeof(List92_22P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List92_22P2, sizeof(List92_22P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List92_22P3, sizeof(List92_22P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List92_22P4, sizeof(List92_22P4) / sizeof(LPCSTR));

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineA), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 1);

		nTSMode ? lpTestSet2_CLA : lpTestSet1_CLA = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 1) - BASE);
		nTSMode ? lpTestSet2_CLB : lpTestSet1_CLB = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 2) - BASE);
		nTSMode ? lpTestSet2_CLC : lpTestSet1_CLC = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 3) - BASE);
		nTSMode ? lpTestSet2_CLD : lpTestSet1_CLD = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 4) - BASE);
		break;
	}
	case 6:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port5));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port6));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port7));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port8));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port9));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port10));
		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List92_28P1, sizeof(List92_28P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List92_28P2, sizeof(List92_28P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List92_28P3, sizeof(List92_28P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List92_28P4, sizeof(List92_28P4) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port5, (LPCSTR*)List92_28P5, sizeof(List92_28P5) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port6, (LPCSTR*)List92_28P6, sizeof(List92_28P6) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port7, (LPCSTR*)List92_28P7, sizeof(List92_28P7) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port8, (LPCSTR*)List92_28P8, sizeof(List92_28P8) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port9, (LPCSTR*)List92_28P9, sizeof(List92_28P9) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port10, (LPCSTR*)List92_28P10, sizeof(List92_28P10) / sizeof(LPCSTR));

		if (!nTSMode)
		{
			OrigSoftMenu_UpdateItems(lpTestSet1);
			if (!lpTestSet1_Port5)
				lpTestSet1_Port5 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 7) - BASE);
			if (!lpTestSet1_Port6)
				lpTestSet1_Port6 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 8) - BASE);
			if (!lpTestSet1_Port7)
				lpTestSet1_Port7 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 9) - BASE);
			if (!lpTestSet1_Port8)
				lpTestSet1_Port8 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 10) - BASE);
			if (!lpTestSet1_Port9)
				lpTestSet1_Port9 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 11) - BASE);
			if (!lpTestSet1_Port10)
				lpTestSet1_Port10 = (void*)((DWORD)GetSubMenuPointer(lpTestSet1, 12) - BASE);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port5);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port6);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port7);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port8);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port8), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port9);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port9), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet1_Port10);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port10), nPortSel);
		}
		else
		{
			OrigSoftMenu_UpdateItems(lpTestSet2);
			if (!lpTestSet2_Port5)
				lpTestSet2_Port5 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 7) - BASE);
			if (!lpTestSet2_Port6)
				lpTestSet2_Port6 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 8) - BASE);
			if (!lpTestSet2_Port7)
				lpTestSet2_Port7 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 9) - BASE);
			if (!lpTestSet2_Port8)
				lpTestSet2_Port8 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 10) - BASE);
			if (!lpTestSet2_Port9)
				lpTestSet2_Port9 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 11) - BASE);
			if (!lpTestSet2_Port10)
				lpTestSet2_Port10 = (void*)((DWORD)GetSubMenuPointer(lpTestSet2, 12) - BASE);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port5);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port5), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port6);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port6), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port7);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port7), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port8);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port8), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port9);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port9), nPortSel);
			nPortSel = GetSubMenuSelected(lpTestSet2_Port10);
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_Port10), nPortSel);
		}


		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineA), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 1);

		nTSMode ? lpTestSet2_CLA : lpTestSet1_CLA = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 1) - BASE);
		nTSMode ? lpTestSet2_CLB : lpTestSet1_CLB = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 2) - BASE);
		nTSMode ? lpTestSet2_CLC : lpTestSet1_CLC = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 3) - BASE);
		nTSMode ? lpTestSet2_CLD : lpTestSet1_CLD = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 4) - BASE);
		break;
	}
	case 7:
	{
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port1));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port2));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port3));
		ComboBox_ResetContent(GetDlgItem(hDlg, IDC_COMBO_Port4));
		ComboSelectInit(hDlg, IDC_COMBO_Port1, (LPCSTR*)List92_X10P1, sizeof(List92_X10P1) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port2, (LPCSTR*)List92_X10P2, sizeof(List92_X10P2) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port3, (LPCSTR*)List92_X10P3, sizeof(List92_X10P3) / sizeof(LPCSTR));
		ComboSelectInit(hDlg, IDC_COMBO_Port4, (LPCSTR*)List92_X10P4, sizeof(List92_X10P4) / sizeof(LPCSTR));

		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port5), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port6), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port7), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port8), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port9), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_COMBO_Port10), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_Port10), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineA), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlA_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineB), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlB_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlB_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlB_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlC_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlC_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlC_DC), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlLineD), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line1), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line3), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_BTN_CtrlD_Line4), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_CtrlD_DC), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_EDIT_CtrlD_DC), 1);

		nTSMode ? lpTestSet2_CLA : lpTestSet1_CLA = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 1) - BASE);
		nTSMode ? lpTestSet2_CLB : lpTestSet1_CLB = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 2) - BASE);
		nTSMode ? lpTestSet2_CLC : lpTestSet1_CLC = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 3) - BASE);
		nTSMode ? lpTestSet2_CLD : lpTestSet1_CLD = (void*)((DWORD)GetSubMenuPointer(nTSMode == 0 ? lpTestSet1 : lpTestSet2, 2 + iPortMenuNum + 4) - BASE);
		break;
	}
	default:
		break;
	}

	

}

VOID ButtonClick(HWND hDlg, int iCLNum, int iCurSel)
{
	void *lpThis1 = lpThis_MTSSMode[nTSMode];
	void *lpSubThis = nullptr;

	OrigSoftMenu_Enter(lpThis1);
	OrigSoftMenu_UpdateItems(lpThis1);

	lpSubThis = GetSubMenuPointer(lpThis1, 2 + iPortMenuNum + iCLNum);

	OrigSoftMenu_Enter((void*)((DWORD)lpSubThis - BASE));
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpSubThis - BASE));

	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpSubThis - BASE), (void**)((DWORD)lpSubThis - BASE), iCurSel);
}

void ComboSelectInit(HWND hDlg, int IDC_SER, LPCSTR* lpSTR, int nNum)
{
	for (int i = 0; i < nNum; i++)
		ComboBox_InsertString(GetDlgItem(hDlg, IDC_SER), i, lpSTR[i]);
}

bool GetSubMenustatus(void *lpThis)
{
	int blTmp = 0;
	int length = 0;
	lpThis = (void*)((DWORD)lpThis + BASE);
	length = (int)*(void**)((DWORD)lpThis + 0x4);

	for (size_t i = 0; i < length; i++)
	{
		OrigSoftMenu_GetItemState((void *)((DWORD)lpThis - BASE), i, NULL, NULL, &blTmp);
		if (blTmp)
			return i;
	}
	return 0;
}


LRESULT CALLBACK wp_MT_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;
	void *lpThisTDc = nullptr;
	switch (msg)
	{
	case WM_CHAR:
	{
		int nIndex = 8;

		switch (GetWindowLong(hWnd, GWL_ID))
		{
		case IDC_EDIT_CtrlA_DC:
			lpThisTDc = lpTestSet1_CLA;
			break;

		case IDC_EDIT_CtrlB_DC:
			lpThisTDc = lpTestSet1_CLB;
			break;

		case IDC_EDIT_CtrlC_DC:
			lpThisTDc = lpTestSet1_CLC;
			break;

		case IDC_EDIT_CtrlD_DC:
			lpThisTDc = lpTestSet1_CLD;
			break;

		default:
			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		if (lpThis_DC[nIndex] == NULL)
		{
			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
		
		OrigSoftMenu_Enter(lpThisTDc);
		OrigSoftMenu_UpdateItems(lpThisTDc);
		OrigSoftMenu_ItemClicked2(lpThisTDc, (void**)((DWORD)lpThisTDc + BASE), nIndex);

		switch (wParam)
		{
		case 'n':
		{
			WCHAR wcsText[MAX_PATH];

			GetWindowTextW(hWnd, wcsText, MAX_PATH);
			MakeUnitStringW((void *)(0x010B4870), wcsText, MAX_PATH, "n");
			SetWindowTextW(hWnd, wcsText);
		}
		break;

		case 'u':
		{
			WCHAR wcsText[MAX_PATH];

			GetWindowTextW(hWnd, wcsText, MAX_PATH);
			MakeUnitStringW((void *)(0x010B4870), wcsText, MAX_PATH, "\xEC\0");   //μ
			SetWindowTextW(hWnd, wcsText);
		}
		break;

		case 'm':
		{
			WCHAR wcsText[MAX_PATH];

			GetWindowTextW(hWnd, wcsText, MAX_PATH);
			MakeUnitStringW((void *)(0x010B4870), wcsText, MAX_PATH, "m");
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

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			PopWnd_Finetune(FALSE, 1, 1);
			break;

		case VK_DOWN:
			PopWnd_Finetune(FALSE, -1, 1);
			break;

		case VK_PRIOR:
			PopWnd_Finetune(TRUE, 1, 1);
			break;

		case VK_NEXT:
			PopWnd_Finetune(TRUE, -1, 1);
			break;

		default:
			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
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
	{
		WCHAR *wcsText = nullptr;
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);
	}

	default:
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return lResult;
}
