#include "stdafx.h"

const LPCWSTR wcsListPR[] =
{
	L"-5 to 10\0\0",
	L"-15 to 0\0\0",
	L"-25 to -10\0\0",
	L"-35 to -20\0\0",
	L"-45 to -30\0\0"
};

int WINAPI fnClicked_PortCouple(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnUpdateData_FREQ_PC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);


//频率子条目
SOFT_SUB_ITEM subitemFrequency[] =
{
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_UPDATEDATA,
		SIS_InputButtonEx,
		0,
		L"Start\0起始\0起始\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163C2B8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_STIMULUS,
		CA_STIMULUS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_UPDATEDATA,
		SIS_InputButtonEx,
		1,
		L"Stop\0终止\0終止\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163C368, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_STIMULUS,
		CA_STIMULUS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_UPDATEDATA,
		SIS_InputButtonEx,
		2,
		L"Center\0中心频率\0中心頻率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163C418, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_STIMULUS,
		CA_STIMULUS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_UPDATEDATA,
		SIS_InputButtonEx,
		3,
		L"Span\0带宽\0帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x0163C4C8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_STIMULUS,
		CA_STIMULUS,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

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
		{ 0, &fnClicked_PortCouple, 0, &fnUpdateData_FREQ_PC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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
};

static int WINAPI fnUpdateData_FREQ_PC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (lpSubItem == NULL) 
		return -1;

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

//中频带宽子条目
SOFT_SUB_ITEM subitemIFBW[] =
{
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_FINETUNE,
		SIS_InputButtonEx,
		5,
		L"IF Bandwidth\0中频带宽\0中頻帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B35D4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_AVERAGE,
		CA_AVERAGE,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


int WINAPI fnTagPageEnter_Frequency(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_STIMULUS);
	OrigSoftMenu_UpdateItems(CA_STIMULUS);
	return 0;
}

int WINAPI fnTagPageEnter_Power(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage);

int WINAPI fnTagPageEnter_IFBW(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	static bool blInit = false;

	OrigSoftMenu_UpdateItems(CA_DISPLAY);

	if (!blInit)
	{
		OrigSoftMenu_UpdateItems(CA_AVERAGE);
		blInit = true;
	}

	return 0;
}


//频率子菜单
SOFT_TAG_PAGE submenuFrequency[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"Frequency\0频率\0頻率\0\0",
		NULL,
		sizeof(subitemFrequency) / sizeof(SOFT_SUB_ITEM),
		subitemFrequency,
		RESERVE_DWORD4,
		&fnTagPageEnter_Frequency,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Stimulus_Conditions.htm", (void*)1026, 0, 0 }
	}
	,
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
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Stimulus_Conditions.htm#Setting_power_level", (void*)1026, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"IF Bandwidth\0中频带宽\0中頻帶寬\0\0",
		NULL,
		sizeof(subitemIFBW) / sizeof(SOFT_SUB_ITEM),
		subitemIFBW,
		RESERVE_DWORD4,
		&fnTagPageEnter_IFBW,
		NULL,
		0,
		{ L"::/Measurement/Optimizing_Measurements/Expanding_the_Dynamic_Range.htm#Narrowing_the_IF_bandwidth", 0, 0, 0 }
	}
};

//频率主菜单
SOFT_MENU menuFrequency =
{
	0,
	0,
	L"Frequency\0频率\0頻率\0\0",
	NULL,
	sizeof(submenuFrequency) / sizeof(SOFT_TAG_PAGE),
	submenuFrequency,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
