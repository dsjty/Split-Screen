#include "stdafx.h"

#define PRIV_M_NORMAL         0
#define PRIV_M_INVERT         1

#define PRIV_I_DT1            0
#define PRIV_I_DT2            1
#define PRIV_I_DT3            2
#define PRIV_I_DT4            3
#define PRIV_I_MT1            4
#define PRIV_I_MT2            5
#define PRIV_I_MT3            6
#define PRIV_I_MT4            7
#define PRIV_I_GM             8
#define PRIV_I_GS             9
#define PRIV_I_LF             10
#define PRIV_I_LL             11
#define PRIV_I_BG             12

#define PFLG_I_DT1            0x00000001
#define PFLG_I_DT2            0x00000002
#define PFLG_I_DT3            0x00000004
#define PFLG_I_DT4            0x00000008
#define PFLG_I_MT1            0x00000010
#define PFLG_I_MT2            0x00000020
#define PFLG_I_MT3            0x00000040
#define PFLG_I_MT4            0x00000080
#define PFLG_I_GM             0x00000100
#define PFLG_I_GS             0x00000200
#define PFLG_I_LF             0x00000400
#define PFLG_I_LL             0x00000800
#define PFLG_I_BG             0x00001000


static int nMode, nTraCount = 4, nCurTra = 0;
static void *lpThis_Mode[2] = { NULL, NULL };
static void *lpThis_Mode_RC[2] = { NULL, NULL };
static void *lpThis_R = NULL, *lpThis_G = NULL, *lpThis_B = NULL;

void UpdateColorValue(HWND hDlg);
int GetTrNum();
void RadioBtnInit(HWND hwnd);
VOID RadioClickUp_DT(HWND hDlg, int iTrNum);
VOID RadioClickUp_MT(HWND hDlg, int iTrNum);
void ComboBoxClick(HWND hDlg, int nCurTra, int nColor, int nCurSel);


INT_PTR WINAPI fndeColor(PDLG_CTXT lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2)
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

		OrigSoftMenu_Enter(CA_SYS_MISC);
		OrigSoftMenu_UpdateItems(CA_SYS_MISC);

		OrigSoftMenu_Enter(CA_SYS_MISC_DS);
		OrigSoftMenu_UpdateItems(CA_SYS_MISC_DS);

		OrigSoftMenu_Enter(CA_COLR);
		OrigSoftMenu_UpdateItems(CA_COLR);

		lpCA_NOR = GetSubMenuPointer(CA_COLR, 0);
		OrigSoftMenu_Enter((void*)((DWORD)lpCA_NOR - BASE));
		OrigSoftMenu_UpdateItems((void*)((DWORD)lpCA_NOR - BASE));

		lpCA_NOR_DT = GetSubMenuPointer((void*)((DWORD)lpCA_NOR - BASE), 0);
		OrigSoftMenu_Enter((void*)((DWORD)lpCA_NOR_DT - BASE));
		OrigSoftMenu_UpdateItems((void*)((DWORD)lpCA_NOR_DT - BASE));

		UpdateColorValue((HWND)lParam2);
	}
	break;

	case DEC_CMD_CLOSE:
		lResult = TRUE;
		break;
	}

	return lResult;
}

void UpdateColorValue(HWND hDlg)
{
	int nR, nG, nB;

	if (nMode < 0 || nMode > 1)
		return;

	OrigSoftMenu_ItemClicked2(CA_COLR, TA_COLR, nMode);

	if (lpThis_Mode[nMode] == NULL)
	{
		lpThis_Mode[nMode] = GetSubMenuPointer(CA_COLR, nMode);

		OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	}

	OrigSoftMenu_UpdateItems(CA_COLR_XX_RGB);

	if (lpThis_R == NULL)
		lpThis_R = GetSubMenuPointer(CA_COLR_XX_RGB, 0);
	if (lpThis_G == NULL)
		lpThis_G = GetSubMenuPointer(CA_COLR_XX_RGB, 1);
	if (lpThis_B == NULL)
		lpThis_B = GetSubMenuPointer(CA_COLR_XX_RGB, 2);

	if (lpThis_Mode[nMode] == NULL || lpThis_R == NULL || lpThis_G == NULL || lpThis_B == NULL)
		return;

	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, PRIV_I_GM);
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));

	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), nB);


	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, PRIV_I_GS);
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), nB);


	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, PRIV_I_LF);
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), nB);


	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, PRIV_I_LL);
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), nB);


	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, PRIV_I_BG);
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), nB);
}

INT_PTR CALLBACK fndpColor(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		nMode = 0;
		Button_SetCheck(GetDlgItem(hDlg, IDC_CLR_CMD_NORMAL), BST_CHECKED);

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_MODE), GetStringByIndex(L"Mode:\0模式:\0模式:\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_CMD_NORMAL), GetStringByIndex(L"Normal\0正常\0正常\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_CMD_INVERT), GetStringByIndex(L"Invert\0反转\0反轉\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_CMD_DEFCLR), GetStringByIndex(L"Reset Color\0默认颜色\0默認顏色\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDOK), GetStringByIndex(L"Done\0完成\0完成\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDCANCEL), GetStringByIndex(L"Cancel\0取消\0取消\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_DT1), GetStringByIndex(L"Data Trace\0数据曲线\0數據曲線\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_MT1), GetStringByIndex(L"Mem Trace\0存储曲线\0存儲曲線\0\0", nLangId));


		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_GM), GetStringByIndex(L"Graticule Main\0主网格\0主網格\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_GS), GetStringByIndex(L"Graticule Sub\0子网格\0子網格\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_LF), GetStringByIndex(L"Limit Fail\0极限测试失败\0極限測試失敗\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_LL), GetStringByIndex(L"Limit Line\0极限线标\0極限線標\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_GB_BG), GetStringByIndex(L"Background\0背景\0背景\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_R), GetStringByIndex(L"Red\0红\0紅\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_R2), GetStringByIndex(L"Red\0红\0紅\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_R3), GetStringByIndex(L"Red\0红\0紅\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_R11), GetStringByIndex(L"Red\0红\0紅\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_R12), GetStringByIndex(L"Red\0红\0紅\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_R13), GetStringByIndex(L"Red\0红\0紅\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_G), GetStringByIndex(L"Green\0绿\0綠\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_G2), GetStringByIndex(L"Green\0绿\0綠\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_G3), GetStringByIndex(L"Green\0绿\0綠\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_G11), GetStringByIndex(L"Green\0绿\0綠\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_G12), GetStringByIndex(L"Green\0绿\0綠\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_G13), GetStringByIndex(L"Green\0绿\0綠\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_B), GetStringByIndex(L"Blue\0蓝\0藍\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_B2), GetStringByIndex(L"Blue\0蓝\0藍\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_B3), GetStringByIndex(L"Blue\0蓝\0藍\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_B11), GetStringByIndex(L"Blue\0蓝\0藍\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_B12), GetStringByIndex(L"Blue\0蓝\0藍\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_CLR_LBL_B13), GetStringByIndex(L"Blue\0蓝\0藍\0\0", nLangId));



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), 5, L"5");



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), 5, L"5");



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GM_B), 5, L"5");



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_GS_B), 5, L"5");



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LF_B), 5, L"5");



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_LL_B), 5, L"5");



		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_R), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_G), 5, L"5");

		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), 0, L"0");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), 1, L"1");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), 2, L"2");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), 3, L"3");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), 4, L"4");
		ComboBox_InsertStringW(GetDlgItem(hDlg, IDC_CLR_CB_BG_B), 5, L"5");
				
		RadioBtnInit(hDlg);

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
				case IDC_RADIO_DT1:
					RadioClickUp_DT(hDlg, 0);
					break;
				case IDC_RADIO_DT2:
					RadioClickUp_DT(hDlg, 1);
					break;
				case IDC_RADIO_DT3:
					RadioClickUp_DT(hDlg, 2);
					break;
				case IDC_RADIO_DT4:
					RadioClickUp_DT(hDlg, 3);
					break;
				case IDC_RADIO_DT5:
					RadioClickUp_DT(hDlg, 4);
					break;
				case IDC_RADIO_DT6:
					RadioClickUp_DT(hDlg, 5);
					break;
				case IDC_RADIO_DT7:
					RadioClickUp_DT(hDlg, 6);
					break;
				case IDC_RADIO_DT8:
					RadioClickUp_DT(hDlg, 7);
					break;
				case IDC_RADIO_DT9:
					RadioClickUp_DT(hDlg, 8);
					break;
				case IDC_RADIO_DT10:
					RadioClickUp_DT(hDlg, 9);
					break;
				case IDC_RADIO_DT11:
					RadioClickUp_DT(hDlg, 10);
					break;
				case IDC_RADIO_DT12:
					RadioClickUp_DT(hDlg, 11);
					break;
				case IDC_RADIO_DT13:
					RadioClickUp_DT(hDlg, 12);
					break;
				case IDC_RADIO_DT14:
					RadioClickUp_DT(hDlg, 13);
					break;
				case IDC_RADIO_DT15:
					RadioClickUp_DT(hDlg, 14);
					break;
				case IDC_RADIO_DT16:
					RadioClickUp_DT(hDlg, 15);
					break;

				case IDC_RADIO_MT1:
					RadioClickUp_MT(hDlg, 0 + nTraCount);
					break;
				case IDC_RADIO_MT2:
					RadioClickUp_MT(hDlg, 1 + nTraCount);
					break;
				case IDC_RADIO_MT3:
					RadioClickUp_MT(hDlg, 2 + nTraCount);
					break;
				case IDC_RADIO_MT4:
					RadioClickUp_MT(hDlg, 3 + nTraCount);
					break;
				case IDC_RADIO_MT5:
					RadioClickUp_MT(hDlg, 4 + nTraCount);
					break;
				case IDC_RADIO_MT6:
					RadioClickUp_MT(hDlg, 5 + nTraCount);
					break;
				case IDC_RADIO_MT7:
					RadioClickUp_MT(hDlg, 6 + nTraCount);
					break;
				case IDC_RADIO_MT8:
					RadioClickUp_MT(hDlg, 7 + nTraCount);
					break;
				case IDC_RADIO_MT9:
					RadioClickUp_MT(hDlg, 8 + nTraCount);
					break;
				case IDC_RADIO_MT10:
					RadioClickUp_MT(hDlg, 9 + nTraCount);
					break;
				case IDC_RADIO_MT11:
					RadioClickUp_MT(hDlg, 10 + nTraCount);
					break;
				case IDC_RADIO_MT12:
					RadioClickUp_MT(hDlg, 11 + nTraCount);
					break;
				case IDC_RADIO_MT13:
					RadioClickUp_MT(hDlg, 12 + nTraCount);
					break;
				case IDC_RADIO_MT14:
					RadioClickUp_MT(hDlg, 13 + nTraCount);
					break;
				case IDC_RADIO_MT15:
					RadioClickUp_MT(hDlg, 14 + nTraCount);
					break;
				case IDC_RADIO_MT16:
					RadioClickUp_MT(hDlg, 15 + nTraCount);
					break;
					
				case IDC_CLR_CMD_NORMAL:
					nMode = 0;
					UpdateColorValue(hDlg);
					break;

				case IDC_CLR_CMD_INVERT:
					nMode = 1;
					UpdateColorValue(hDlg);
					break;

				case IDC_CLR_CMD_DEFCLR:
				{
					OrigSoftMenu_ItemClicked2(CA_COLR, CA_COLR, nMode);

					if (lpThis_Mode_RC[nMode] == NULL)
					{
						if (lpThis_Mode[nMode] == NULL)
						{
							lpThis_Mode[nMode] = GetSubMenuPointer(CA_COLR, nMode);

							OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
						}

						if (lpThis_Mode[nMode] == NULL)
							break;

						lpThis_Mode_RC[nMode] = GetSubMenuPointer((void*)((DWORD)lpThis_Mode[nMode] - BASE), 13);
						if (lpThis_Mode_RC[nMode] == NULL)
							break;
					}

					void *temp = GetSubMenuPointer((void*)((DWORD)lpThis_Mode[nMode] - BASE), nTraCount * 2 + 5);
					OrigSoftMenu_ItemClicked2((void*)((DWORD)temp - BASE), TA_COLR_XX_RC, 0);

					UpdateColorValue(hDlg);
				}
				break;

				case IDOK:
					DestroyDialog_Def(0);
					break;

				case IDCANCEL:
					DestroyDialog_Def(0);
					break;
				}
				break;
			}
			else if (wNc == CBN_SELCHANGE)
			{
				switch (wId)
				{
				case IDC_CLR_CB_DT1_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R));
					ComboBoxClick(hDlg, nCurTra, 0, index);
				}
				break;

				case IDC_CLR_CB_DT1_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G));
					ComboBoxClick(hDlg, nCurTra, 1, index);
				}
				break;

				case IDC_CLR_CB_DT1_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B));
					ComboBoxClick(hDlg, nCurTra, 2, index);
				}
				break;

				case IDC_CLR_CB_MT1_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R));
					ComboBoxClick(hDlg, nCurTra, 0, index);
				}
				break;

				case IDC_CLR_CB_MT1_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G));
					ComboBoxClick(hDlg, nCurTra, 1, index);
				}
				break;

				case IDC_CLR_CB_MT1_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B));
					ComboBoxClick(hDlg, nCurTra, 2, index);
				}	
				break;

				case IDC_CLR_CB_GM_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GM_R));
					ComboBoxClick(hDlg, nTraCount * 2, 0, index);
				}
				break;
				case IDC_CLR_CB_GM_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GM_G));
					ComboBoxClick(hDlg, nTraCount * 2, 1, index);
				}
				break;
				case IDC_CLR_CB_GM_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GM_B));
					ComboBoxClick(hDlg, nTraCount * 2, 2, index);
				}
				break;

				case IDC_CLR_CB_GS_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GS_R));
					ComboBoxClick(hDlg, nTraCount * 2 + 1, 0, index);
				}
				break;
				case IDC_CLR_CB_GS_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GS_G));
					ComboBoxClick(hDlg, nTraCount * 2 + 1, 1, index);
				}
				break;
				case IDC_CLR_CB_GS_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_GS_B));
					ComboBoxClick(hDlg, nTraCount * 2 + 1, 2, index);
				}
				break;

				case IDC_CLR_CB_LF_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LF_R));
					ComboBoxClick(hDlg, nTraCount * 2 + 2, 0, index);
				}
				break;
				case IDC_CLR_CB_LF_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LF_G));
					ComboBoxClick(hDlg, nTraCount * 2 + 2, 1, index);
				}
				break;
				case IDC_CLR_CB_LF_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LF_B));
					ComboBoxClick(hDlg, nTraCount * 2 + 2, 2, index);
				}
				break;

				case IDC_CLR_CB_LL_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LL_R));
					ComboBoxClick(hDlg, nTraCount * 2 + 3, 0, index);
				}
				break;
				case IDC_CLR_CB_LL_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LL_G));
					ComboBoxClick(hDlg, nTraCount * 2 + 3, 1, index);
				}
				break;
				case IDC_CLR_CB_LL_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_LL_B));
					ComboBoxClick(hDlg, nTraCount * 2 + 3, 2, index);
				}
				break;

				case IDC_CLR_CB_BG_R:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_BG_R));
					ComboBoxClick(hDlg, nTraCount * 2 + 4, 0, index);
				}
				break;
				case IDC_CLR_CB_BG_G:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_BG_G));
					ComboBoxClick(hDlg, nTraCount * 2 + 4, 1, index);
				}
				break;
				case IDC_CLR_CB_BG_B:
				{
					int index = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_BG_B));
					ComboBoxClick(hDlg, nTraCount * 2 + 4, 2, index);
				}
				break;
				}
				break;
			}
		}
	}
	break;

	case WM_CLOSE:
		DestroyDialog_Def(0);
		break;
	}

	return FALSE;
}


DLG_CTXT dcColorWizard
{
	NULL,
	IDD_COLOR,
	0,
	&fndeColor,
	&fndpColor,
	RESERVE_DWORD4
};

int GetTrNum()
{
	const WCHAR *lpInfFile;
	UINT uVal;

	lpInfFile = (const WCHAR *)GetOffsetPointer((void *)((DWORD)0x01113938 + BASE), 0x6c);

	nTraCount = uVal = GetPrivateProfileIntW(L"INSTR", L"TRACE", 4, lpInfFile);

	return uVal;
}

void RadioBtnInit(HWND hDlg)
{
	int iTrNum = GetTrNum();
	
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT1), GetStringByIndex(L"DataTrace1\0数据曲线1\0數據曲線1\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT2), GetStringByIndex(L"DataTrace2\0数据曲线2\0數據曲線2\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT3), GetStringByIndex(L"DataTrace3\0数据曲线3\0數據曲線3\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT4), GetStringByIndex(L"DataTrace4\0数据曲线4\0數據曲線4\0\0", nLangId));

	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT1), GetStringByIndex(L"MemTrace1\0存储曲线1\0存儲曲線1\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT2), GetStringByIndex(L"MemTrace2\0存储曲线2\0存儲曲線2\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT3), GetStringByIndex(L"MemTrace3\0存储曲线3\0存儲曲線3\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT4), GetStringByIndex(L"MemTrace4\0存储曲线4\0存儲曲線4\0\0", nLangId));

	if (iTrNum == 4)
	{
		for (int i = IDC_RADIO_DT5; i <= 1182; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
		for (int i = IDC_RADIO_MT1; i <= 1198; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
	}
	if (iTrNum == 6)
	{
		for (int i = IDC_RADIO_DT7; i <= 1182; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
		for (int i = IDC_RADIO_MT7; i <= 1198; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT5), GetStringByIndex(L"DataTrace5\0数据曲线5\0數據曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT6), GetStringByIndex(L"DataTrace6\0数据曲线6\0數據曲線6\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT5), GetStringByIndex(L"MemTrace5\0存储曲线5\0存儲曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT6), GetStringByIndex(L"MemTrace6\0存储曲线6\0存儲曲線6\0\0", nLangId));
	}
	if (iTrNum == 8)
	{
		for (int i = IDC_RADIO_DT9; i <= 1182; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
		for (int i = IDC_RADIO_MT9; i <= 1198; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);


		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT5), GetStringByIndex(L"DataTrace5\0数据曲线5\0數據曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT6), GetStringByIndex(L"DataTrace6\0数据曲线6\0數據曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT7), GetStringByIndex(L"DataTrace7\0数据曲线7\0數據曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT8), GetStringByIndex(L"DataTrace8\0数据曲线8\0數據曲線8\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT5), GetStringByIndex(L"MemTrace5\0存储曲线5\0存儲曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT6), GetStringByIndex(L"MemTrace6\0存储曲线6\0存儲曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT7), GetStringByIndex(L"MemTrace7\0存储曲线7\0存儲曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT8), GetStringByIndex(L"MemTrace8\0存储曲线8\0存儲曲線8\0\0", nLangId));
	}
	if (iTrNum == 9)
	{
		for (int i = IDC_RADIO_DT10; i <= 1182; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
		for (int i = IDC_RADIO_MT10; i <= 1198; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT5), GetStringByIndex(L"DataTrace5\0数据曲线5\0數據曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT6), GetStringByIndex(L"DataTrace6\0数据曲线6\0數據曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT7), GetStringByIndex(L"DataTrace7\0数据曲线7\0數據曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT8), GetStringByIndex(L"DataTrace8\0数据曲线8\0數據曲線8\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT9), GetStringByIndex(L"DataTrace9\0数据曲线9\0數據曲線9\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT5), GetStringByIndex(L"MemTrace5\0存储曲线5\0存儲曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT6), GetStringByIndex(L"MemTrace6\0存储曲线6\0存儲曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT7), GetStringByIndex(L"MemTrace7\0存储曲线7\0存儲曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT8), GetStringByIndex(L"MemTrace8\0存储曲线8\0存儲曲線8\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT9), GetStringByIndex(L"MemTrace9\0存储曲线9\0存儲曲線9\0\0", nLangId));

	}
	if (iTrNum == 12)
	{
		for (int i = IDC_RADIO_DT13; i <= 1182; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);
		for (int i = IDC_RADIO_MT13; i <= 1198; i++)
			ShowWindow(GetDlgItem(hDlg, i), 0);

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT5), GetStringByIndex(L"DataTrace5\0数据曲线5\0數據曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT6), GetStringByIndex(L"DataTrace6\0数据曲线6\0數據曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT7), GetStringByIndex(L"DataTrace7\0数据曲线7\0數據曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT8), GetStringByIndex(L"DataTrace8\0数据曲线8\0數據曲線8\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT9), GetStringByIndex(L"DataTrace9\0数据曲线9\0數據曲線9\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT10), GetStringByIndex(L"DataTrace10\0数据曲线10\0數據曲線10\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT11), GetStringByIndex(L"DataTrace11\0数据曲线11\0數據曲線11\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT12), GetStringByIndex(L"DataTrace12\0数据曲线12\0數據曲線12\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT5), GetStringByIndex(L"MemTrace5\0存储曲线5\0存儲曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT6), GetStringByIndex(L"MemTrace6\0存储曲线6\0存儲曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT7), GetStringByIndex(L"MemTrace7\0存储曲线7\0存儲曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT8), GetStringByIndex(L"MemTrace8\0存储曲线8\0存儲曲線8\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT9), GetStringByIndex(L"MemTrace9\0存储曲线9\0存儲曲線9\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT10), GetStringByIndex(L"MemTrace10\0存储曲线10\0存儲曲線10\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT11), GetStringByIndex(L"MemTrace11\0存储曲线11\0存儲曲線11\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT12), GetStringByIndex(L"MemTrace12\0存储曲线12\0存儲曲線12\0\0", nLangId));
	}
	if (iTrNum == 16)
	{
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT5), GetStringByIndex(L"DataTrace5\0数据曲线5\0數據曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT6), GetStringByIndex(L"DataTrace6\0数据曲线6\0數據曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT7), GetStringByIndex(L"DataTrace7\0数据曲线7\0數據曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT8), GetStringByIndex(L"DataTrace8\0数据曲线8\0數據曲線8\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT9), GetStringByIndex(L"DataTrace9\0数据曲线9\0數據曲線9\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT10), GetStringByIndex(L"DataTrace10\0数据曲线10\0數據曲線10\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT11), GetStringByIndex(L"DataTrace11\0数据曲线11\0數據曲線11\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT12), GetStringByIndex(L"DataTrace12\0数据曲线12\0數據曲線12\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT13), GetStringByIndex(L"DataTrace13\0数据曲线13\0數據曲線13\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT14), GetStringByIndex(L"DataTrace14\0数据曲线14\0數據曲線14\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT15), GetStringByIndex(L"DataTrace15\0数据曲线15\0數據曲線15\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_DT16), GetStringByIndex(L"DataTrace16\0数据曲线16\0數據曲線16\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT5), GetStringByIndex(L"MemTrace5\0存储曲线5\0存儲曲線5\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT6), GetStringByIndex(L"MemTrace6\0存储曲线6\0存儲曲線6\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT7), GetStringByIndex(L"MemTrace7\0存储曲线7\0存儲曲線7\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT8), GetStringByIndex(L"MemTrace8\0存储曲线8\0存儲曲線8\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT9), GetStringByIndex(L"MemTrace9\0存储曲线9\0存儲曲線9\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT10), GetStringByIndex(L"MemTrace10\0存储曲线10\0存儲曲線10\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT11), GetStringByIndex(L"MemTrace11\0存储曲线11\0存儲曲線11\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT12), GetStringByIndex(L"MemTrace12\0存储曲线12\0存儲曲線12\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT13), GetStringByIndex(L"MemTrace13\0存储曲线13\0存儲曲線13\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT14), GetStringByIndex(L"MemTrace14\0存储曲线14\0存儲曲線14\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT15), GetStringByIndex(L"MemTrace15\0存储曲线15\0存儲曲線15\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDC_RADIO_MT16), GetStringByIndex(L"MemTrace16\0存储曲线16\0存儲曲線16\0\0", nLangId));
	}

}

VOID RadioClickUp_DT(HWND hDlg, int iTrNum)
{
	int nR, nG, nB;

	nCurTra = iTrNum;

	if (nMode < 0 || nMode > 1)
		return;

	OrigSoftMenu_ItemClicked2(CA_COLR, TA_COLR, nMode);

	if (lpThis_Mode[nMode] == NULL)
	{
		lpThis_Mode[nMode] = GetSubMenuPointer(CA_COLR, nMode);

		OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	}

	OrigSoftMenu_UpdateItems(CA_COLR_XX_RGB);

	if (lpThis_R == NULL)
		lpThis_R = GetSubMenuPointer(CA_COLR_XX_RGB, 0);
	if (lpThis_G == NULL)
		lpThis_G = GetSubMenuPointer(CA_COLR_XX_RGB, 1);
	if (lpThis_B == NULL)
		lpThis_B = GetSubMenuPointer(CA_COLR_XX_RGB, 2);

	if (lpThis_Mode[nMode] == NULL || lpThis_R == NULL || lpThis_G == NULL || lpThis_B == NULL)
		return;

	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, iTrNum);

	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_DT1_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_DT1_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_DT1_B), nB);

}

VOID RadioClickUp_MT(HWND hDlg, int iTrNum)
{
	int nR, nG, nB;

	if (nMode < 0 || nMode > 1)
		return;

	OrigSoftMenu_ItemClicked2(CA_COLR, TA_COLR, nMode);

	if (lpThis_Mode[nMode] == NULL)
	{
		lpThis_Mode[nMode] = GetSubMenuPointer(CA_COLR, nMode);

		OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));
	}

	OrigSoftMenu_UpdateItems(CA_COLR_XX_RGB);

	if (lpThis_R == NULL)
		lpThis_R = GetSubMenuPointer(CA_COLR_XX_RGB, 0);
	if (lpThis_G == NULL)
		lpThis_G = GetSubMenuPointer(CA_COLR_XX_RGB, 1);
	if (lpThis_B == NULL)
		lpThis_B = GetSubMenuPointer(CA_COLR_XX_RGB, 2);

	if (lpThis_Mode[nMode] == NULL || lpThis_R == NULL || lpThis_G == NULL || lpThis_B == NULL)
		return;

	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, iTrNum);

	nR = GetSubMenuSelected((void*)((DWORD)lpThis_R - BASE));
	nG = GetSubMenuSelected((void*)((DWORD)lpThis_G - BASE));
	nB = GetSubMenuSelected((void*)((DWORD)lpThis_B - BASE));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_MT1_R), nR);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_MT1_G), nG);
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_CLR_CB_MT1_B), nB);
}


//************************************
// 函数名:    ComboBoxClick
// 函数性质:    public 
// 函数类型:   void
// 描述: ;nCurTra是当前选择的曲线; nColor 0==Red,1==green,2==blue;nCurSel是 选择的颜色量号;
//************************************
void ComboBoxClick(HWND hDlg, int nCurTra, int nColor,int nCurSel)
{
	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_Mode[nMode] - BASE), TA_COLR_XX, nCurTra);	
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpThis_Mode[nMode] - BASE));

	OrigSoftMenu_ItemClicked2(CA_COLR_XX_RGB, TA_COLR_XX_RGB, nColor);
	OrigSoftMenu_UpdateItems(CA_COLR_XX_RGB);

	if (nColor == 0)
		OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_R - BASE), TA_COLR_XX_RGB_X, nCurSel);
	if (nColor == 1)
		OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_G - BASE), TA_COLR_XX_RGB_X, nCurSel);
	if (nColor == 2)
		OrigSoftMenu_ItemClicked2((void*)((DWORD)lpThis_B - BASE), TA_COLR_XX_RGB_X, nCurSel);
}