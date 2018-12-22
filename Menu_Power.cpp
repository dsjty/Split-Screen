#include "stdafx.h"

const LPCWSTR wcsListPR[] =
{
	L"-5 to 10\0\0",
	L"-15 to 0\0\0",
	L"-25 to -10\0\0",
	L"-35 to -20\0\0",
	L"-45 to -30\0\0"
};

//Power :: Port Couple
int WINAPI fnUpdateData_PWR_PC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

int WINAPI fnClicked_PortCouple(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		if (lpSubItem && lpSubItem->lpEvent[FNID_UPDATE_DATA])
		{
			func_ItemEvent_UpdateData fnUpdateData = (func_ItemEvent_UpdateData)lpSubItem->lpEvent[FNID_UPDATE_DATA];
			fnUpdateData(0, 0, 0, lpSubItem);
		}
	}

	return 0;
}

//功率子条目
static SOFT_SUB_ITEM subitemPower[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		0,
		L"Power\0功率\0功率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR,
		CA_SS_PWR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"Port Couple\0端口耦合\0端口藕合\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D81F8C, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, &fnClicked_PortCouple, 0, &fnUpdateData_PWR_PC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR,
		CA_SS_PWR,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		0,
		L"Port 1 Power\0端口1功率\0端口1功率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR_PP,
		CA_SS_PWR_PP,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		1,
		L"Port 2 Power\0端口2功率\0端口2功率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR_PP,
		CA_SS_PWR_PP,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		NULL,
		NULL,
		40,
		BtnHeith_DH,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		4,
		L"Slope\0斜率\0斜率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x000D0C00, 0, (void *)0x00D67870, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR,
		CA_SS_PWR,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		3,
		L"Slope\0斜率\0斜率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C3C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR,
		CA_SS_PWR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		6,
		L"RF Out\0RF 输出\0RF 輸出\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00131200, 0, (void *)0x00DB2868, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR,
		CA_SS_PWR,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		5,
		L"CW Freq\0点频频率\0點頻頻率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C3C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_PWR,
		CA_SS_PWR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

static int WINAPI fnUpdateData_PWR_PC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (lpSubItem == NULL) return -1;

	UpdateCheckBoxState(lpSubItem);

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIAE_CHECKED))
	{
		if (subitemPower[0]._hWnd)
		{
			EnableWindow(subitemPower[0]._hWnd, TRUE);
			InvalidateRect(subitemPower[0]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[0]._hWnd);
		}

		if (subitemPower[3]._hWnd)
		{
			EnableWindow(subitemPower[3]._hWnd, FALSE);
			InvalidateRect(subitemPower[3]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[3]._hWnd);
		}

		if (subitemPower[4]._hWnd)
		{
			EnableWindow(subitemPower[4]._hWnd, FALSE);
			InvalidateRect(subitemPower[4]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[4]._hWnd);
		}
	}
	else
	{
		if (subitemPower[0]._hWnd)
		{
			EnableWindow(subitemPower[0]._hWnd, FALSE);
			InvalidateRect(subitemPower[0]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[0]._hWnd);
		}

		if (subitemPower[3]._hWnd)
		{
			EnableWindow(subitemPower[3]._hWnd, TRUE);
			InvalidateRect(subitemPower[3]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[3]._hWnd);
		}

		if (subitemPower[4]._hWnd)
		{
			EnableWindow(subitemPower[4]._hWnd, TRUE);
			InvalidateRect(subitemPower[4]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[4]._hWnd);
		}
	}

	return 0;
}

int WINAPI fnTagPageEnter_Power(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage);

//功率子菜单
SOFT_TAG_PAGE submenuPower[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"Power\0功率\0功率\0\0",
		NULL,
		sizeof(subitemPower) / sizeof(SOFT_SUB_ITEM),
		subitemPower,
		RESERVE_DWORD4,
		&fnTagPageEnter_Power,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Stimulus_Conditions.htm", 0, 0, 0 }
	}
};

//功率主菜单
SOFT_MENU menuPower =
{
	0,
	0,
	L"Power\0功率\0功率\0\0",
	NULL,
	sizeof(submenuPower) / sizeof(SOFT_TAG_PAGE),
	submenuPower,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
