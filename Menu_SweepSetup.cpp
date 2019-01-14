#include "stdafx.h"

const char szFMODe[] = "SENSe*:SEGMent:FMODe";
const char szBWIDth[] = "SENSe*:SEGMent:BWIDth:RESolution:CONTrol";
const char szPOWer[] = "SENSe*:SEGMent:POWer:LEVel:CONTrol";
const char szPortPOWer[] = "SENSe*:SEGMent:LIST:POWer:PORT1:STATe";
const char szDELay[] = "SENSe*:SEGMent:SWEep:DELay:CONTrol";
const char szTIME[] = "SENSe*:SEGMent:SWEep:TIME:CONTrol";
const char szSweepMode[] = "SENSe*:SEGMent:SWEep:GENeration:CONTrol";
const char szCState[] = "SENSe*:SEGMent:LIST:CONTrol:STATe";
const char szSState[] = "SENSe*:SEGMent:SLOCal:STATe";




const LPCWSTR wcsListPR[] =
{
	L"-5 to 10\0\0",
	L"-15 to 0\0\0",
	L"-25 to -10\0\0",
	L"-35 to -20\0\0",
	L"-45 to -30\0\0"
};

const LPCWSTR wcsListST[] =
{
	L"Lin Freq\0线性频率\0線性頻率\0\0",
	L"Log Freq\0对数频率\0對數頻率\0\0",
	L"Segment\0分段\0分段\0\0",
	L"Power Sweep\0功率扫描\0功率掃描\0\0"
};

const LPCWSTR wcsListFreqMode[] =
{
	L"Start/Stop\0起始/终止\0起始/終止\0\0",
	L"Center/Span\0中心频率/带宽\0中心頻率/帶寬\0\0"
};

const LPCWSTR wcsListSegDisplay[] =
{
	L"Freq Base\0频率规则\0頻率規則\0\0",
	L"Order Base\0排序规则\0排序規則\0\0"
};

const LPCWSTR wcsListTriggerSource[] =
{
	L"Internal\0内部\0內部\0\0",
	L"External\0外部\0外部\0\0",
	L"Manual\0手动\0手動\0\0",
	L"Bus\0总线\0總線\0\0"
};

int WINAPI fnClicked_PortCouple(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnUpdateData_SS_PC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);


int WINAPI fnItemClicked_OpenEST(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Enter(CA_SWEEPSET);

		OrigSoftMenu_Enter(lpSubItem->lpThis);
		OrigSoftMenu_UpdateItems(lpSubItem->lpThis);
	}

	return 0;
}

int WINAPI fnItemClicked_CloseEST(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Leave(lpSubItem->lpThis);
	}

	return 0;
}


int WINAPI fnUpdateIndex_FreqMode(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	LPCWSTR *lppWStr = (LPCWSTR *)lpSubItem->lpParams;
	LPCWSTR lpText = NULL;

	if (lpSubItem->lpOpt[2] == NULL)
		return -1;

	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}

	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);

	if ((*lppWStr) && ((DWORD)nIndex < lpSubItem->dwNumberOfParams))
	{
		lpText = GetStringByIndex(lppWStr[nIndex], nLangId);
	}
	else
		lpText = L"!ERROR!";

	if (lpSubItem->lpOpt[4])
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], lpText);

	return 0;
}

int WINAPI fnItemClicked_FreqMode(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		fnUpdateIndex_FreqMode(0, 0, 0, lpSubItem);
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
		{ 0, &fnClicked_PortCouple, 0, &fnUpdateData_SS_PC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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

static int WINAPI fnUpdateData_SS_PC(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
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
			EnableWindow(subitemPower[2]._hWnd, FALSE);
			InvalidateRect(subitemPower[2]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[2]._hWnd);
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
			EnableWindow(subitemPower[2]._hWnd, TRUE);
			InvalidateRect(subitemPower[2]._hWnd, NULL, TRUE);
			UpdateWindow(subitemPower[2]._hWnd);
		}
	}

	return 0;
}


//扫描设置子条目
SOFT_SUB_ITEM subitemSweepSetup[] =
{
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		1,
		L"Sweep Time\0扫描时间\0掃描時間\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SWEEPSET,
		CA_SWEEPSET,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		2,
		L"Sweep Delay\0扫描延迟\0掃描延遲\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C78, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SWEEPSET,
		CA_SWEEPSET,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_FINETUNE,
		SIS_InputButtonEx,
		4,
		L"Points\0扫描点数\0掃描點數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B6C8C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SWEEPSET,
		CA_SWEEPSET,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		5,
		L"Sweep Type\0扫描类型\0掃描類型\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000B0A00, 0, (void *)0x00D6760C, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_ST,
		CA_SS_ST,
		sizeof(wcsListST) / sizeof(LPCWSTR),
		wcsListST,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//扫描设置子条目
SOFT_SUB_ITEM subitemSegment[] =
{
	{
		SIF_FN_CLICKED,
		SIA_FULLLINE,
		SIS_ButtonEx,
		6,
		L"Open Edit Segment Table\0打开编辑段标签\0打開編輯段標簽\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_OpenEST, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_CLICKED | SIF_FN_SETFOCUS,
		SIA_FULLLINE,
		SIS_ButtonEx,
		6,
		L"Close Edit Segment Table\0关闭编辑段标签\0關閉編輯段標簽\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_CloseEST, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		0,
		L"Freq Mode\0频率模式\0頻率模式\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)szFMODe, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		{ 0, &fnItemClicked_FreqMode, 0, &fnUpdateIndex_FreqMode, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		sizeof(wcsListFreqMode) / sizeof(LPCWSTR),
		wcsListFreqMode,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"List IFBW\0中频带宽列表\0中頻帶寬列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szBWIDth, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
		2,
		L"List Power\0功率列表\0功率列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szPOWer, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
		3,
		L"List Port Power\0端口功率列表\0端口功率列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szPortPOWer, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
		L"List Delay\0延迟列表\0延遲列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szDELay, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
		5,
		L"List Sweep Mode\0扫描模式列表\0掃描模式列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szSweepMode, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
		6,
		L"List Time\0时间列表\0時間列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szTIME, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
		7,
		L"List State\0状态列表\0狀態列表\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szCState, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
			8,
			L"List Shift LO\0List Shift LO\0List Shift LO\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)szSState, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_SS_EST,
			CA_SS_EST,
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
		9,
		L"List Port IFBW\0端口带宽\0端口帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D7DBA4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		10,
		L"Delete\0删除\0刪除\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		11,
		L"Add\0增加\0增加\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Clear Segment Table\0清除段标签\0清除段標簽\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST_CST,
		CA_SS_EST_CST,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		13,
		L"Export to CSV file\0导出到CSV文件\0導出到CSV文件\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		14,
		L"Import from CSV file\0从CSV文件导入\0從CSV文件導入\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SS_EST,
		CA_SS_EST,
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
			15,
			L"Arbitrary Segments\0Arbitrary Segments\0Arbitrary Segments\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)0x00D673A4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_SS_EST,
			CA_SS_EST,
			NULL,
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
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		7,
		L"Segment Display\0段显示\0段顯示\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00030200, 0, (void *)0x00D64EA4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_FreqMode, 0, &fnUpdateIndex_FreqMode, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_SWEEPSET,
		CA_SWEEPSET,
		sizeof(wcsListSegDisplay) / sizeof(LPCWSTR),
		wcsListSegDisplay,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};



int WINAPI fnUpdateData_Trigger(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	TDMenu *temp = nullptr;
	if (uiCurFocusMenu == 2)
		temp = cwMenuWnd2;
	else
		temp = cwMenuWnd;

	if (lpSubItem->lpOpt[2] == NULL)
		return -1;

	nIndex = GetSubMenuSelected_Radio(CA_TRIGGER);

	temp->tdItem->SoftItem_ActivationItemByOffsetIndex(lpSubItem, nIndex);

	return 0;
}

//触发子条目
SOFT_SUB_ITEM subitemTrigger[] =
{
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GROUP | SIA_GETBTNSTATE,
		SIS_RadioButtonEx,
		0,
		L"Hold\0保持\0保持\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00080700, 0, (void *)0x00D650E8, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, &fnUpdateData_Trigger, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEITEM,
		SIS_RadioButtonEx,
		1,
		L"Single\0单步\0單步\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEITEM,
		SIS_RadioButtonEx,
		2,
		L"Continuous\0连续\0連續\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
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
		SIA_FULLLINE,
		SIS_ButtonEx,
		3,
		L"Hold All Channels\0保持所有通道\0保持所有通道\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		4,
		L"Continuous Disp Channels\0连续显示所有通道\0連續顯示所有通道\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		5,
		L"Trigger Source\0触发源\0觸發源\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00000000, 0, (void *)0x00D68CD8, (void *)0x92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRIGGER_TS,
		CA_TRIGGER_TS,
		sizeof(wcsListTriggerSource) / sizeof(LPCWSTR),
		wcsListTriggerSource,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		8,
		L"Restart\0重新开始\0重新開始\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		9,
		L"Trigger\0触发\0觸發\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_FINETUNE,
		SIS_InputButtonEx,
		11,
		L"Trigger Delay\0Trigger Delay\0Trigger Delay\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B71A8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRIGGER,
		CA_TRIGGER,
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
			12,
			L"Low Latency\0Low Latency\0Low Latency\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)0x00D68BEC, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_TRIGGER,
			CA_TRIGGER,
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
			13,
			L"Ext Trig Output\0Ext Trig Output\0Ext Trig Output\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)0x00D68BD4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_TRIGGER,
			CA_TRIGGER,
			NULL,
			NULL,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
};

int WINAPI fnTagPageEnter_Power(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_SWEEPSET);
	OrigSoftMenu_UpdateItems(CA_SS_PWR);
	return 0;
}

int WINAPI fnTagPageEnter_SweepSetup(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_SWEEPSET);
	return 0;
}

int WINAPI fnTagPageEnter_Trigger(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_TRIGGER);
	return 0;
}


//扫描设置子菜单
SOFT_TAG_PAGE submenuSweepSetup[] =
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
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Stimulus_Conditions.htm#Setting_power_level", 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Sweep Setup\0扫描设置\0掃描設置\0\0",
		NULL,
		sizeof(subitemSweepSetup) / sizeof(SOFT_SUB_ITEM),
		subitemSweepSetup,
		RESERVE_DWORD4,
		&fnTagPageEnter_SweepSetup,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Stimulus_Conditions.htm#Setting_the_Number_of_Points", 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Edit SegmentTable\0编辑段标签\0編輯段標籤\0\0",
		NULL,
		sizeof(subitemSegment) / sizeof(SOFT_SUB_ITEM),
		subitemSegment,
		RESERVE_DWORD4,
		&fnTagPageEnter_SweepSetup,
		NULL,
		0,
		{ L"::/Measurement/Data_Output/Saving_Recalling_Instrument_State_for_Each_Channel_into_from.htm#Recalling_Instrument_State_for_Each_Channel", (void*)1097, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Trigger\0触发\0觸發\0\0",
		NULL,
		sizeof(subitemTrigger) / sizeof(SOFT_SUB_ITEM),
		subitemTrigger,
		RESERVE_DWORD4,
		&fnTagPageEnter_Trigger,
		NULL,
		0,
		{ L"::/Measurement/Making_Measurements/Setting_Up_the_Trigger_and_Making_Measurements.htm#Trigger_Source",0, 0, 0 }
	}
};

//扫描设置主菜单
SOFT_MENU menuSweepSetup =
{
	0,
	0,
	L"Sweep Setup\0扫描设置\0掃描設置\0\0",
	NULL,
	sizeof(submenuSweepSetup) / sizeof(SOFT_TAG_PAGE),
	submenuSweepSetup,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
