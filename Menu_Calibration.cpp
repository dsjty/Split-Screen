#include "stdafx.h"

extern WORD wWidth_MainWnd, wHeight_MainWnd;


extern CALDLG_CTXT dcCal_1;
extern CALDLG_CTXT dcCal_2;
extern CALDLG_CTXT dcCal_7;

extern CalKit cCalkit;

void *lpThis_SensorA = nullptr, *lpThis_SensorA_CLS = nullptr;
void *lpThis_SensorB = nullptr, *lpThis_SensorB_CLS = nullptr;
void *lpThis_RecCal_SP1 = nullptr, *lpThis_RecCal_SP2 = nullptr;

static bool blSensor = false;



const LPCWSTR wcsSelPort[] =
{
	L"1\0\0",
	L"2\0\0",
	L"3\0\0",
	L"4\0\0"
};

const LPCWSTR wcsListTrigSour[] =
{
	L"Internal\0内部\0內部\0\0",
	L"System\0系统\0系統\0\0"
};

const LPCSTR szCorrectiong[] =
{
	"SOURce*:POWer:PORT1:CORRection:STATe",
	"SOURce*:POWer:PORT2:CORRection:STATe",
	"SOURce*:POWer:PORT3:CORRection:STATe",
	"SOURce*:POWer:PORT4:CORRection:STATe"
};

const LPCSTR szUseSen[] =
{
	"SOURce*:POWer:PORT1:CORRection:usesensor",
	"SOURce*:POWer:PORT2:CORRection:usesensor",
	"SOURce*:POWer:PORT3:CORRection:usesensor",
	"SOURce*:POWer:PORT4:CORRection:usesensor",
};

const LPCSTR szCompens[] =
{
	"SOURce*:POWer:PORT1:CORRection:COLLect:TABLe:LOSS:STATe",
	"SOURce*:POWer:PORT2:CORRection:COLLect:TABLe:LOSS:STATe",
	"SOURce*:POWer:PORT3:CORRection:COLLect:TABLe:LOSS:STATe",
	"SOURce*:POWer:PORT4:CORRection:COLLect:TABLe:LOSS:STATe"
};

const LPCSTR szRecCalCor[] =
{
	"SENSe*:CORRection:RECeiver1:STATe",
	"SENSe*:CORRection:RECeiver2:STATe",
	"SENSe*:CORRection:RECeiver3:STATe",
	"SENSe*:CORRection:RECeiver4:STATe",
};


const LPCWSTR wcsSensor[] =
{
	L"A\0\0",
	L"B\0\0"
};

int WINAPI fnItemClicked_OpenSensorA(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_CloseSensorA(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_OpenSensorB(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
int WINAPI fnItemClicked_CloseSensorB(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);


static int WINAPI fnUpdateData_Correction(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	GetButtonStateIndex((char*)0x00D7C6BC, 0, &nIndex, 0);

	lpSubItem->lpOpt[2] = (void*)szCorrectiong[nIndex];
	lpSubItem->lpOpt[12] = (void*)1;

	return 0;
}

static int WINAPI fnItemClicked_Sensor(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	GetButtonStateIndex((char*)0x00D7C6BC, 0, &nIndex, 0);

	lpSubItem->lpOpt[2] = (void*)szUseSen[nIndex];
	lpSubItem->lpOpt[12] = (void*)1;

	return 0;
}

static int WINAPI fnItemClicked_Compensation(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	GetButtonStateIndex((char*)0x00D7C6BC, 0, &nIndex, 0);

	lpSubItem->lpOpt[2] = (void*)szCompens[nIndex];
	lpSubItem->lpOpt[12] = (void*)1;

	return 0;
}


static int WINAPI fnUpdateData_Sensor(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	GetButtonStateIndex((char*)0x00D7C6BC, 0, &nIndex, 0);

	if (nIndex)
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], L"B");
	else
		SetWindowTextW((HWND)lpSubItem->lpOpt[4], L"A");

	return 0;
}



int WINAPI fnUpdateIndex_TrigSour(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	LPCWSTR *lppWStr = (LPCWSTR *)lpSubItem->lpParams;
	LPCWSTR lpText = NULL;

	if (lpSubItem->lpOpt[2] == NULL)
		return -1;

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

int WINAPI fnItemClicked_OpenLossCom(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Enter(CA_CALIBRAT);
		OrigSoftMenu_Enter(CA_CAL_PWCAL);
		OrigSoftMenu_UpdateItems(CA_CAL_PWCAL);

		OrigSoftMenu_Enter(CA_CAL_PWCAL_LC);
		OrigSoftMenu_UpdateItems(CA_CAL_PWCAL_LC);

		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
	}
	return 0;
}


int WINAPI fnItemClicked_CloseLossCom(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Leave(lpSubItem->lpThis);

		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
	}
	return 0;
}

//校准子条目
SOFT_SUB_ITEM subitemCalibration[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Correction\0校正\0校正\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D66CB4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CALIBRAT,
		CA_CALIBRAT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_CALWND,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"Calibration\0校准\0校準\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&dcCal_1,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_CALWND,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
		L"ECal\0电子校准\0電子校準\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&dcCal_2,
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
		L"Clear All\0全部清除\0全部清除\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_CLS,
		CA_CAL_CLS,
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
		4,
		L"Property\0校准信息显示\0校準信息顯示\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00030200, 0, (void *)0x00D66C98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CALIBRAT,
		CA_CALIBRAT,
		NULL,
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
		L"Cal Kit\0校准件\0校準件\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D660FC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_CALK,
		CA_CAL_CALK,
		(DWORD)26,
		(void *)cCalkit.CalKitList,
		RESERVE_DWORD4,
		{0,0,0,1}
	}
	,
	{
		SIF_CALWND,
		SIA_FULLLINE,
		SIS_ButtonEx,
		6,
		L"Modify Cal Kit\0更换校准件\0更換校準件\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&dcCal_7,
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
		8,
		L"Velocity Factor\0速度系数\0速度系數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3630, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CALIBRAT,
		CA_CALIBRAT,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		9,
		L"Set Z0\0设置阻抗\0設置阻抗\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3640, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CALIBRAT,
		CA_CALIBRAT,
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
		10,
		L"Cal Trig Source\0校准触发源\0校準觸發源\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00050400, 0, (void *)0x00D66C58, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateIndex_TrigSour, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CALIBRAT,
		CA_CALIBRAT,
		sizeof(wcsListTrigSour) / sizeof(LPCWSTR),
		wcsListTrigSour,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

SOFT_SUB_ITEM subitemPowerCalibration[] =
{
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		0,
		L"Select Port\0选择端口\0選擇端口\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000A0900, 0, (void *)0x00D7C6BC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SP,
		CA_CAL_PWCAL_SP,
		PORTNUM,
		wcsSelPort,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"Correction\0校正\0校正\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00050400, 0, (void *)szCorrectiong[0], 0, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		{ 0, 0, 0, &fnUpdateData_Correction, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL,
		CA_CAL_PWCAL,
		0,
		0,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEITEM,
		SIS_ButtonEx,
		2,
		L"Take Cal Sweep\0测定校准扫描\0測定校準掃描\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL,
		CA_CAL_PWCAL,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEITEM,
		SIS_ButtonEx,
		3,
		L"Abort\0取消\0取消\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL,
		CA_CAL_PWCAL,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA ,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		4,
		L"Use Sensor\0使用传感器\0使用傳感器\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)szUseSen[0], (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		{ 0, &fnItemClicked_Sensor, 0, &fnUpdateData_Sensor, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL,
		CA_CAL_PWCAL,
		PORTNUM,
		wcsSensor,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
		,
		{
			SIF_ORIGCLICK | SIF_NOREPLY,
			SIA_FULLLINE | SIA_INPUT_TIME,
			SIS_InputButtonEx,
			5,
			L"Num of Readings\0读取值\0讀取值\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x010B5664, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_CAL_PWCAL,
			CA_CAL_PWCAL,
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
			6,
			L"Tolerance\0公差\0公差\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x010B5678, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_CAL_PWCAL,
			CA_CAL_PWCAL,
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
			7,
			L"Max Iteration\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x010B56C8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			0,
			NULL,
			NULL,
			TA_CAL_PWCAL,
			CA_CAL_PWCAL,
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
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_FN_CLICKED,
			SIA_FULLLINE,
			SIS_ButtonEx,
			8,
			L"Loss Compen\0损耗补偿\0損耗補償\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			{ 0, &fnItemClicked_OpenLossCom, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			INVALID_INDEX,
			NULL,
			NULL,
			TA_CAL_PWCAL_LC,
			CA_CAL_PWCAL_LC,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
			,
			{
				SIF_FN_CLICKED | SIF_FN_SETFOCUS,
				SIA_FULLLINE,
				SIS_ButtonEx,
				8,
				L"Close Loss Compen\0关闭损耗补偿\0關閉損耗補償\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				RESERVE_DWORD16,
				{ 0, &fnItemClicked_CloseLossCom, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				INVALID_INDEX,
				NULL,
				NULL,
				TA_CAL_PWCAL_LC,
				CA_CAL_PWCAL_LC,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
				SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
				SIS_CheckButtonEx,
				0,
				L"Compensation\0补偿\0補償\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				{ (void *)0x00050400, 0, (void *)szCompens[0], 0, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
				{ 0, 0, 0, &fnItemClicked_Compensation, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				INVALID_INDEX,
				NULL,
				NULL,
				TA_CAL_PWCAL_LC,
				CA_CAL_PWCAL_LC,
				0,
				0,
				RESERVE_DWORD4,
				RESERVE_DWORD4
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_ButtonEx,
				1,
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
				TA_CAL_PWCAL_LC,
				CA_CAL_PWCAL_LC,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_ButtonEx,
				2,
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
				TA_CAL_PWCAL_LC,
				CA_CAL_PWCAL_LC,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_ButtonEx,
				0,
				L"Clear Limit Table\0清除极限表格\0清除極限表格\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				RESERVE_DWORD16,
				RESERVE_DWORD16,
				INVALID_INDEX,
				NULL,
				NULL,
				TA_CAL_PWCAL_LC_CLS,
				CA_CAL_PWCAL_LC_CLS,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_ButtonEx,
				4,
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
				TA_CAL_PWCAL_LC,
				CA_CAL_PWCAL_LC,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK,
				SIA_FULLLINE,
				SIS_ButtonEx,
				5,
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
				TA_CAL_PWCAL_LC,
				CA_CAL_PWCAL_LC,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
};


SOFT_SUB_ITEM subitemSensorASet[] =
{
	{
		SIF_FN_CLICKED,
		SIA_FULLLINE ,
		SIS_ButtonEx,
		9,
		L"OpenSensorSetings\0打开校准传感器设置A\0打开校準傳感器設置A\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_OpenSensorA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_FN_CLICKED | SIF_FN_SETFOCUS,
		SIA_FULLLINE,
		SIS_ButtonEx,
		9,
		L"CloseSensorSetings\0关闭校准传感器设置A\0關閉校準傳感器設置A\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_CloseSensorA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME | SIA_UPDATEITEM,
		SIS_InputButtonEx,
		0,
		L"Ref Cal Factor\0基准校准系数\0基准校準係數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B5628, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
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
		1,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Clear Limit Table\0清除极限表格\0清除極限表格\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS_CLS,
		lpThis_SensorA_CLS,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		4,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		5,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		7,
		L"Zero/Calibrate Sensor\0校准传感器调零\0校準傳感器調零\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorA,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};

SOFT_SUB_ITEM subitemSensorBSet[] =
{
	{
		SIF_FN_CLICKED,
		SIA_FULLLINE,
		SIS_ButtonEx,
		10,
		L"OpenSensor A Setings\0打开校准传感器设置B\0打开校準傳感器設置B\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_OpenSensorB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_FN_CLICKED | SIF_FN_SETFOCUS,
		SIA_FULLLINE,
		SIS_ButtonEx,
		10,
		L"CloseSensor B Setings\0关闭校准传感器设置B\0關閉校準傳感器設置B\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_CloseSensorB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME | SIA_UPDATEITEM,
		SIS_InputButtonEx,
		0,
		L"Ref Cal Factor\0基准校准系数\0基准校準係數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B5628, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
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
		1,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		2,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Clear Limit Table\0清除极限表格\0清除極限表格\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS_CLS,
		lpThis_SensorB_CLS,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		4,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		5,
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
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		7,
		L"Zero/Calibrate Sensor\0校准传感器调零\0校準傳感器調零\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_PWCAL_SAS,
		lpThis_SensorB,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};



static int WINAPI fnItemClicked_RecCalCor(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	GetButtonStateIndex((char*)0xD79444, 0, &nIndex, 0);

	lpSubItem->lpOpt[2] = (void*)szRecCalCor[nIndex];
	lpSubItem->lpOpt[12] = (void*)1;

	return 0;
}

static int WINAPI fnUpdateData_Out(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;

	GetButtonStateIndex((char*)0xD79444, 0, &nIndex, 0);

	lpSubItem->lpOpt[1] = (void*)(0x016383D8 + 0x14 * nIndex);

	return 0;
}

int WINAPI fnUpdateData_RecCal(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

SOFT_SUB_ITEM subitemRecCal[] =
{
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		0,
		L"Select Port\0端口选择\0端口選擇\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0, 0, (void *)0x0D79444, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_RecCal, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_RECCAL_SELP,
		lpThis_RecCal_SP1,
		PORTNUM,
		wcsSelPort,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"Correction\0校正\0校正\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)szRecCalCor[0], 0, 0, 0, 0, 0, 0, 0, 0, 0, (void*)1, 0, 0, 0 },
		{ 0, 0, 0, &fnItemClicked_RecCalCor, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_RECCAL,
		CA_CAL_RECCAL,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		0,
		L"Source Port\0源端口\0源端口\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00020300, 0, (void *)0x0D79420, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_RecCal, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_RECCAL_SELP,
		lpThis_RecCal_SP2,
		PORTNUM,
		wcsSelPort,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_INPUT_TIME | SIA_UPDATEITEM,
		SIS_InputButtonEx,
		3,
		L"Power Offset\0功率偏移\0功率偏移\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x016383D8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0,  0, &fnUpdateData_Out, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		NULL,
		NULL,
		TA_CAL_RECCAL,
		CA_CAL_RECCAL,
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
		L"Calibrate Both\0校准两项\0校準兩項\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CAL_RECCAL,
		CA_CAL_RECCAL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_ButtonEx,
			5,
			L"Calibrate R\0校准R\0校準R\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_CAL_RECCAL,
			CA_CAL_RECCAL,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_ButtonEx,
			6,
			L"Calibrate T\0校准T\0校準T\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_CAL_RECCAL,
			CA_CAL_RECCAL,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}

};

int WINAPI fnUpdateData_RecCal(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (lpSubItem == NULL || lpSubItem->lpThis == NULL)
		return -1;

	int nIndex = GetSubMenuSelected(lpSubItem->lpThis);

	ComboBox_SetCurSel((HWND)lpSubItem->lpOpt[4], nIndex);

	for (size_t i = 4; i < 7; i++)
	{
		OrigSoftMenu_GetItemState(CA_CAL_RECCAL, i, &nIndex, 0, 0);
		EnableWindow(subitemRecCal[i]._hWnd, nIndex);
	}

	return 0;
}

int WINAPI fnItemClicked_OpenSensorA(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_UpdateItems(CA_CAL_PWCAL);

		OrigSoftMenu_Enter(lpThis_SensorA);

		blSensor = true;

		for (size_t i = 1; i < 9; i++)
		{
			EnableWindow(subitemSensorASet[i]._hWnd, TRUE);
		}
	}
	return 0;
}

int WINAPI fnItemClicked_CloseSensorA(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Leave(lpThis_SensorA);

		blSensor = FALSE;

		for (int i = 1; i < 9; i++)
		{
			EnableWindow(subitemSensorASet[i]._hWnd, FALSE);
		}
	}
	return 0;
}

int WINAPI fnItemClicked_OpenSensorB(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_UpdateItems(CA_CAL_PWCAL);

		OrigSoftMenu_Enter(lpThis_SensorB);

		blSensor = true;

		for (size_t i = 0x1; i < 9; i++)
		{
			EnableWindow(subitemSensorBSet[i]._hWnd, TRUE);
		}
	}
	return 0;
}

int WINAPI fnItemClicked_CloseSensorB(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Leave(lpThis_SensorB);

		blSensor = FALSE;

		for (size_t i = 1; i < 9; i++)
		{
			EnableWindow(subitemSensorBSet[i]._hWnd, FALSE);
		}
	}
	return 0;
}


int WINAPI fnTagPageEnter_SensorA(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_CALIBRAT);
	OrigSoftMenu_UpdateItems(CA_CALIBRAT);

	OrigSoftMenu_Enter(CA_CAL_PWCAL);
	OrigSoftMenu_UpdateItems(CA_CAL_PWCAL);

	lpThis_SensorA = (void*)((DWORD)GetSubMenuPointer(CA_CAL_PWCAL, 9) - BASE);

	OrigSoftMenu_Enter(lpThis_SensorA);
	OrigSoftMenu_UpdateItems(lpThis_SensorA);

	lpThis_SensorA_CLS = (void*)((DWORD)GetSubMenuPointer(lpThis_SensorA, 3) - BASE);

	for (int i = 0; i < 9; i++)
		subitemSensorASet[i].lpThis = lpThis_SensorA;
	subitemSensorASet[5].lpThis = lpThis_SensorA_CLS;

	return 0;
}

int WINAPI fnTagPageLeave_SensorA(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Leave(lpThis_SensorA);
	return 0;
}

int WINAPI fnTagPageEnter_SensorB(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_CALIBRAT);
	OrigSoftMenu_UpdateItems(CA_CALIBRAT);

	OrigSoftMenu_Enter(CA_CAL_PWCAL);
	OrigSoftMenu_UpdateItems(CA_CAL_PWCAL);

	lpThis_SensorB = (void*)((DWORD)GetSubMenuPointer(CA_CAL_PWCAL, 0xA) - BASE);

	OrigSoftMenu_Enter(lpThis_SensorB);
	OrigSoftMenu_UpdateItems(lpThis_SensorB);

	lpThis_SensorB_CLS = (void*)((DWORD)GetSubMenuPointer(lpThis_SensorB, 3) - BASE);

	for (int i = 0; i < 9; i++)
		subitemSensorBSet[i].lpThis = lpThis_SensorB;
	subitemSensorBSet[5].lpThis = lpThis_SensorB_CLS;

	return 0;
}

int WINAPI fnTagPageLeave_SensorB(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Leave(lpThis_SensorB);
	return 0;
}


int WINAPI fnTagPageEnter_RecCal(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Enter(CA_CALIBRAT);
	OrigSoftMenu_UpdateItems(CA_CALIBRAT);

	OrigSoftMenu_Enter(CA_CAL_RECCAL);
	OrigSoftMenu_UpdateItems(CA_CAL_RECCAL);

	lpThis_RecCal_SP1 = (void*)((DWORD)GetSubMenuPointer(CA_CAL_RECCAL, 0) - BASE);
	subitemRecCal[0].lpThis = lpThis_RecCal_SP1;

	lpThis_RecCal_SP2 = (void*)((DWORD)GetSubMenuPointer(CA_CAL_RECCAL, 2) - BASE);
	subitemRecCal[2].lpThis = lpThis_RecCal_SP2;

	return 0;
}


//校准子菜单
SOFT_TAG_PAGE submenuCalibration[] =
{
	{
		TPF_FN_ENTER /* | SSF_FN_LEAVE */,
		0,
		L"Calibration\0校准\0校準\0\0",
		NULL,
		sizeof(subitemCalibration) / sizeof(SOFT_SUB_ITEM),
		subitemCalibration,
		RESERVE_DWORD4,
		0,
		NULL,
		0,
		{ L"::/Measurement/Calibration/Calibration.htm", (void*)1031, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER ,
		0,
		L"Power Calibration\0Power校准\0Power校準\0\0",
		NULL,
		sizeof(subitemPowerCalibration) / sizeof(SOFT_SUB_ITEM),
		subitemPowerCalibration,
		RESERVE_DWORD4,
		0,
		NULL,
		0,
		{ L"::/Measurement/Calibration/Calibration.htm", (void*)1031, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER | TPF_FN_LEAVE ,
		0,
		L"Sensor A Settings\0校准器A设置\0校准器A设置\0\0",
		NULL,
		sizeof(subitemSensorASet) / sizeof(SOFT_SUB_ITEM),
		subitemSensorASet,
		RESERVE_DWORD4,
		&fnTagPageEnter_SensorA,
		&fnTagPageLeave_SensorA,
		0,
		{ L"::/Measurement/Calibration/Calibration.htm", (void*)1031, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER | TPF_FN_LEAVE ,
		0,
		L"Sensor B Settings\0校准器B设置\0校准器B设置\0\0",
		NULL,
		sizeof(subitemSensorBSet) / sizeof(SOFT_SUB_ITEM),
		subitemSensorBSet,
		RESERVE_DWORD4,
		&fnTagPageEnter_SensorB,
		&fnTagPageLeave_SensorB,
		0,
		{ L"::/Measurement/Calibration/Calibration.htm", (void*)1031, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER | TPF_FN_LEAVE ,
		0,
		L"Receiver Calibration\0接收机校准\0接收機校準\0\0",
		NULL,
		sizeof(subitemRecCal) / sizeof(SOFT_SUB_ITEM),
		subitemRecCal,
		RESERVE_DWORD4,
		&fnTagPageEnter_RecCal,
		0,
		0,
		{ L"::/Measurement/Calibration/Calibration.htm", (void*)1031, 0, 0 }
	}
};

//校准主菜单
SOFT_MENU menuCalibration =
{
	0,
	0,
	L"Calibration\0校准\0校準\0\0",
	NULL,
	sizeof(submenuCalibration) / sizeof(SOFT_TAG_PAGE),
	submenuCalibration,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};




