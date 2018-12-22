#include "stdafx.h"

extern WORD wWidth_MainWnd, wHeight_MainWnd;

const LPCWSTR wcsListSelPort[] =
{
	L"1\0\0",
	L"2\0\0"
};

const LPCWSTR wcsListTristate2[] =
{
	L"Off\0关闭\0關閉\0\0",
	L"Absolute\0绝对\0絕對\0\0",
	L"Margin\0相对\0相對\0\0"
};

const LPCWSTR wcsListDevice[] =
{
	L"Se-Bal\0\0",
	L"Bal-Bal\0\0",
	L"SE-SE-Bal\0\0",
	L"Bal\0\0"
};

const LPCWSTR wcsList12[] =
{
	L"1\0\0",
	L"2\0\0",
	L"3\0\0",
	L"4\0\0",
	L"5\0\0",
	L"6\0\0",
	L"7\0\0",
	L"8\0\0",
	L"9\0\0",
	L"10\0\0",
	L"11\0\0",
	L"12\0\0"
};

const LPCWSTR wcsListFLType[] =
{
	L"Bandpass\0带通\0帶通\0\0",
	L"Lowpass Step\0低通阶跃\0低通階躍\0\0",
	L"Lowpass Imp\0低通脉冲\0低通脈衝\0\0"
};

const LPCWSTR wcsListFLUnit[] =
{
	L"Seconds\0秒\0秒\0\0",
	L"Meters\0米\0米\0\0",
	L"Feet\0英尺\0英呎\0\0"
};

const LPCWSTR wcsListFLWindow[] =
{
	L"Maximum\0最大\0最大0\0",
	L"Normal\0正常\0正常\0\0",
	L"Minimum\0最小\0最小\0\0"
};


const LPCWSTR wcsListShape[] =
{
	L"Maximum\0最大\0最大0\0",
	L"Wide\0一般\0一般\0\0",
	L"Normal\0正常\0正常\0\0",
	L"Minimum\0最小\0最小\0\0"
};

const LPCWSTR wcsListFLRefType[] =
{
	L"One Way\0\0",
	L"Round Trip\0\0"
};

const LPCWSTR wcsListGatingType[] =
{
	L"Bandpass\0带通\0帶通\0\0",
	L"NOTCh\0凹峰\0凹峰\0\0"
};

const LPCWSTR wcsListCONVFUN[] =
{
	L"Z:Reflection\0Z:反射\0Z:反射\0\0",
	L"Z:Transmission\0Z:传输\0Z:傳輸\0\0",
	L"Z:Trans-Shunt\0Z:Trans-Shunt\0Z:Trans-Shunt\0\0",
	L"Y:Reflection\0Y:反射\0Z:反射\0\0",
	L"Y:Transmission\0Y:传输\0Y:傳輸\0\0",
	L"Y:Trans-Shunt\0Y:Trans-Shunt\0Y:Trans-Shunt\0\0",
	L"1 / S\0\0",
	L"Conjugation\0\0"
};

static int WINAPI fnUpdateData_TDR(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);



void WINAPI fnItemClicked_BalUnAll_OFF(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	typedef void(__thiscall * fnBalUnOpen)(bool blOpen);

	fnBalUnOpen fnBO = (fnBalUnOpen)(BASE + 0x314DD0);

	fnBO(0);
}

void WINAPI fnItemClicked_BalUnAll_On(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	typedef void(__thiscall * fnBalUnOn)(bool blOpen);

	fnBalUnOn fnBO = (fnBalUnOn)(BASE + 0x314DD0);

	fnBO(1);
}

int WINAPI fnItemClicked_OpenELL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Enter(CA_ANALYSIS);
		OrigSoftMenu_Enter(CA_LIMITTEST);

		OrigSoftMenu_Enter(lpSubItem->lpThis);
		OrigSoftMenu_UpdateItems(lpSubItem->lpThis);

		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
	}
	return 0;
}

int WINAPI fnItemClicked_CloseELL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
 	if (wParam == IC_CLICKED_LAST)
 	{
 		OrigSoftMenu_Leave(lpSubItem->lpThis);
 
 		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
 	}

	return 0;
}

int WINAPI fnItemClicked_OpenERL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
 	if (wParam == IC_CLICKED_LAST)
 	{
 		OrigSoftMenu_Enter(CA_ANALYSIS);
 
 		OrigSoftMenu_Enter(CA_RIPPLELIMIT);
 
 		OrigSoftMenu_Enter(lpSubItem->lpThis);
 		OrigSoftMenu_UpdateItems(lpSubItem->lpThis);
 
 		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
 	}

	return 0;
}

int WINAPI fnItemClicked_CloseERL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
 	if (wParam == IC_CLICKED_LAST)
 	{
 		OrigSoftMenu_Leave(lpSubItem->lpThis);
 
 		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
 	}
	return 0;
}


int WINAPI fnItemClicked_OpenEPL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Enter(CA_ANALYSIS);

		OrigSoftMenu_Enter(CA_POINTLIMIT);

		OrigSoftMenu_Enter(lpSubItem->lpThis);
		OrigSoftMenu_UpdateItems(lpSubItem->lpThis);

		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
	}

	return 0;
}

int WINAPI fnItemClicked_CloseEPL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		OrigSoftMenu_Leave(lpSubItem->lpThis);

		PSTMSG(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
	}
	return 0;
}


int WINAPI fnUpdateData_RefType(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
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

int WINAPI fnItemClicked_RefType(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		fnUpdateData_RefType(0, 0, 0, lpSubItem);
	}

	return 0;
}


int WINAPI fnUpdateData_BAL(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	void *lpTemp = nullptr;

	if (lpSubItem->lpOpt[2] == NULL)
		return -1;
	
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_TOPO);

	lpTemp = GetSubMenuPointer(CA_ANALY_FIXSIM_TOPO, 1);
	if (!lpTemp)
		return 0;

	OrigSoftMenu_UpdateItems((void*)((DWORD)lpTemp - BASE));

	nIndex = GetSubMenuSelected_Radio((void*)((DWORD)lpTemp - BASE));
	
	ComboBox_SetCurSel((HWND)lpSubItem->lpOpt[4], nIndex);

	return 0;
}

int WINAPI fnItemSelected_FS(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem, int nIndex)
{
	if (nIndex == -1)
		nIndex = 0;
	void *lpTemp = nullptr;

	lpTemp = GetSubMenuPointer(CA_ANALY_FIXSIM_TOPO, 1);

	if (!lpTemp)
		return 0;

	OrigSoftMenu_Enter((void*)((DWORD)lpTemp - BASE));
	OrigSoftMenu_UpdateItems((void*)((DWORD)lpTemp - BASE));
	OrigSoftMenu_ItemClicked2((void*)((DWORD)lpTemp - BASE), (void**)((DWORD)lpTemp - BASE), nIndex);

	return 0;
}


//固定装置仿真子条目
SOFT_SUB_ITEM subitemFixtureSim[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Fixture Simulator\0固定装置仿真\0固定裝置仿真\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)(0x0D620BC), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM,
		CA_ANALY_FIXSIM,
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
		L"Device\0设备选择\0設備選擇\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0, 0, (void *)0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_TOPO_DEV,
		CA_ANALY_FIXSIM_TOPO_DEV,
		sizeof(wcsListDevice) / sizeof(LPCWSTR),
		wcsListDevice,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		1,
		L"Port(Bal)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D61B8C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_FS,&fnUpdateData_BAL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_TOPG_BAL_P1,
		CA_ANALY_FIXSIM_TOPG_BAL_P1,
		sizeof(wcsListSelPort) / sizeof(LPCWSTR),
		wcsListSelPort,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		2,
		L"Property\0校准信息显示\0校准信息顯示\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00050400, 0, (void *)(0x00D61BC4), (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_TOPO,
		CA_ANALY_FIXSIM_TOPO,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		2,
		L"BalUn\0巴伦\0巴倫\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00030200, 0, (void *)(0xD61B24), (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM,
		CA_ANALY_FIXSIM,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE  | SIA_UPDATEITEM,
		SIS_ButtonEx,
		3,
		L"BalUn OFF All Tra \0BalUn OFF All Tra\0BalUn OFF All Tra\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_BalUnAll_OFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM,
		CA_ANALY_FIXSIM,
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
		4,
		L"BalUn ON All Tra \0BalUn ON All Tra\0BalUn ON All Tra\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_BalUnAll_On, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM,
		CA_ANALY_FIXSIM,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};

//端口匹配
SOFT_SUB_ITEM subitemPortMatch[]=
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Port Matching\0端口匹配\0端口匹配\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)(0xD61FB8), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
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
		1,
		L"Select Port\0端口选择\0端口選擇\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D76234, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_SELPORT,
		CA_ANALY_FIXSIM_SELPORT,
		sizeof(wcsListSelPort) / sizeof(LPCWSTR),
		wcsListSelPort,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		L"Select Circuit\0电路选择\0電路選擇\0\0",
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
		SIA_GROUP,
		SIS_RadioButtonEx,
		0,
		L"None\0空\0空\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)0,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		1,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_SeLShC,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		2,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_ShCSeL,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		3,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_ShLSeC,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		4,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_SeCShL,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		5,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_ShLShC,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		6,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_SeCShC,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		6,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_ShCSeC,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		8,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_SeLShL,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		9,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_ShLSeL,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		10,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_User,
		NULL,
		TA_ANALY_FIXSIM_SELCIR,
		CA_ANALY_FIXSIM_SELCIR,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		3,
		L"C(C1)\0C(C1)\0C(C1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		4,
		L"G(G1)\0G(G1)\0G(G1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		5,
		L"L(L1)\0L(L1)\0L(L1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		6,
		L"R(R1)\0R(R1)\0R(R1)\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		7,
		L"C2\0C2\0C2\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		8,
		L"G2\0G2\0G2\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		9,
		L"L2\0L2\0L2\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		10,
		L"R2\0R2\0R2\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEITEM,
		SIS_ButtonEx,
		11,
		L"User Files...\0用户文件...\0用戶文件...\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PMATCH,
		CA_ANALY_FIXSIM_PMATCH,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		L"Port ZConversion\0端口阻抗变换\0端口阻抗變換\0\0",
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
		0,
		L"Port ZConversion\0端口阻抗变换\0端口阻抗變換\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)(0xD6208C), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PZCON,
		CA_ANALY_FIXSIM_PZCON,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		1,
		L"Port1 Z0 Real\0端口1ZO实部\0端口1ZO實部\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3408, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PZCON,
		CA_ANALY_FIXSIM_PZCON,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		2,
		L"Port1 Z0 Imag\0端口1ZO虚部\0端口1ZO虛部\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3408, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PZCON,
		CA_ANALY_FIXSIM_PZCON,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		3,
		L"Port2 Z0 Real\0端口2ZO实部\0端口2Z0實部\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3408, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PZCON,
		CA_ANALY_FIXSIM_PZCON,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK ,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		4,
		L"Port2 Z0 Imag\0端口2ZO虚部\0端口2ZO虛部\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3408, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_PZCON,
		CA_ANALY_FIXSIM_PZCON,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
		,
		{
			0,
			SIA_FULLLINE,
			SIS_Delimiter,
			0,
			L"De-Embedding\0非嵌入\0非嵌入\0\0",
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
			0,
			L"De-Embedding\0非嵌入\0非嵌入\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)(0xD61E2C), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DeEMBED,
			CA_ANALY_FIXSIM_DeEMBED,
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
			1,
			L"Select Port\0端口选择\0端口選擇\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ (void *)0x00010000, 0, (void *)0x00D76234, (void *)0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, &fnItemSelected_Default, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DeEMBED_SELPORT,
			CA_ANALY_FIXSIM_DeEMBED_SELPORT,
			PORTNUM,
			wcsList12,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE | SIA_UPDATEITEM,
			SIS_ButtonEx,
			3,
			L"User Files...\0用户文件...\0用戶文件...\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DeEMBED,
			CA_ANALY_FIXSIM_DeEMBED,
			NULL,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
};


//差分匹配子条目
SOFT_SUB_ITEM subitemDiffMatch[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Diff Matching\0差分匹配\0差分匹配\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)(0xD61804), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_DIFFMAT,
		CA_ANALY_FIXSIM_DIFFMAT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		L"Select Circuit\0电路选择\0電路選擇\0\0",
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
		SIA_GROUP,
		SIS_RadioButtonEx,
		0,
		L"None\0空\0空\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)0,
		NULL,
		TA_ANALY_FIXSIM_DIFFMAT_SC,
		CA_ANALY_FIXSIM_DIFFMAT_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		1,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_ShuLShC,
		NULL,
		TA_ANALY_FIXSIM_DIFFMAT_SC,
		CA_ANALY_FIXSIM_DIFFMAT_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES,
		SIS_RadioButtonEx,
		2,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_User,
		NULL,
		TA_ANALY_FIXSIM_DIFFMAT_SC,
		CA_ANALY_FIXSIM_DIFFMAT_SC,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}

		,
		{
			SIF_ORIGCLICK ,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			3,
			L"C\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637740, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DIFFMAT,
			CA_ANALY_FIXSIM_DIFFMAT,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			4,
			L"G\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637740, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DIFFMAT,
			CA_ANALY_FIXSIM_DIFFMAT,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			5,
			L"L\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637740, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DIFFMAT,
			CA_ANALY_FIXSIM_DIFFMAT,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			6,
			L"R\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637740, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_DIFFMAT,
			CA_ANALY_FIXSIM_DIFFMAT,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_UPDATEITEM,
		SIS_ButtonEx,
		7,
		L"User Files...\0用户文件...\0用戶文件...\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_FIXSIM_DIFFMAT,
		CA_ANALY_FIXSIM_DIFFMAT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		L"Diff ZConversion\0差分阻抗变换\0差分阻抗變換\0\0",
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
				0,
				L"Diff ZConversion\0差分阻抗变换\0差分阻抗變換\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H,
				NULL,
				{ (void *)0x00010000, 0, (void *)(0xD618DC), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				RESERVE_DWORD16,
				INVALID_INDEX,
				NULL,
				NULL,
				TA_ANALY_FIXSIM_DIFFZCON,
				CA_ANALY_FIXSIM_DIFFZCON,
				NULL,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK ,
				SIA_FULLLINE,
				SIS_InputButtonEx,
				1,
				L"Port(bal)Real\0端口(bal)实部\0端口(bal)實部\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H2,
				NULL,
				{ 0, (void *)0x010B3328, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				RESERVE_DWORD16,
				INVALID_INDEX,
				NULL,
				NULL,
				TA_ANALY_FIXSIM_DIFFZCON,
				CA_ANALY_FIXSIM_DIFFZCON,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
			,
			{
				SIF_ORIGCLICK ,
				SIA_FULLLINE,
				SIS_InputButtonEx,
				2,
				L"Port(bal) Imag\0端口(bal)虚部\0端口(bal)虛部\0\0",
				NULL,
				BtnWidth_W,
				BtnHeith_H2,
				NULL,
				{ 0, (void *)0x010B3328, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				RESERVE_DWORD16,
				INVALID_INDEX,
				NULL,
				NULL,
				TA_ANALY_FIXSIM_DIFFZCON,
				CA_ANALY_FIXSIM_DIFFZCON,
				0,
				NULL,
				RESERVE_DWORD4,
				{ 0, 0, 0, 0 }
			}
		,
		{
			0,
			SIA_FULLLINE,
			SIS_Delimiter,
			0,
			L"Cmn ZConversion\0Cmn阻抗变换\0Cmn阻抗變換\0\0",
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
			0,
			L"Cmn ZConversion\0 Cmn阻抗变换\0 Cmn阻抗變換\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)(0xD61674), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_CMNZCON,
			CA_ANALY_FIXSIM_CMNZCON,
			NULL,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK ,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			1,
			L"Port(bal)Real\0端口(bal)实部\0端口(bal)實部\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x010B3398, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_CMNZCON,
			CA_ANALY_FIXSIM_CMNZCON,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK ,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			2,
			L"Port(bal) Imag\0端口(bal)虚部\0端口(bal)虛部\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x010B3398, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_FIXSIM_CMNZCON,
			CA_ANALY_FIXSIM_CMNZCON,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
};

//极限测试子条目
SOFT_SUB_ITEM subitemLimitTest[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Limit Test\0极限测试\0極限測試\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)(0xD63DA4), (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LIMITTEST,
		CA_LIMITTEST,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1090, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"Limit Line\0极限线标\0極限線標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00050400, 0, (void *)(0xD63C50), (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LIMITTEST,
		CA_LIMITTEST,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		4,
		L"Fail Sign\0失败标志\0失敗標誌\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x000D0C00, 0, (void *)(0xD64F7C), (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LIMITTEST,
		CA_LIMITTEST,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
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
		2,
		L"Open Edit Limit Line\0打开编辑极限线标\0打開編輯極限線標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_OpenELL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LT_ELL,
		CA_LT_ELL,
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
		2,
		L"Close Edit Limit Line\0关闭编辑极限线标\0關閉編輯極限線標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_CloseELL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LT_ELL,
		CA_LT_ELL,
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
		TA_LT_ELL,
		CA_LT_ELL,
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
		1,
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
		TA_LT_ELL,
		CA_LT_ELL,
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
		TA_LT_ELL_CLT,
		CA_LT_ELL_CLT,
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
		3,
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
		TA_LT_ELL,
		CA_LT_ELL,
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
		TA_LT_ELL,
		CA_LT_ELL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
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
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		0,
		L"Stimulus Offset\0激励偏移\0激勵偏移\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)CA_LT_LLO_MAO, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LT_LLO,
		CA_LT_LLO,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		1,
		L"Amplitude Offset\0幅度偏移\0幅度偏移\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B34A0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LT_LLO,
		CA_LT_LLO,
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
		L"Marker -> Amplitude Offset\0频标 -> 幅度偏移\0頻標 -> 幅度偏移\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_LT_LLO,
		CA_LT_LLO,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};


//波动极限子条目
SOFT_SUB_ITEM subitemRippleLimit[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Ripple Limit Test\0波动极限测试\0波動極限測試\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0xD64664, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RIPPLELIMIT,
		CA_RIPPLELIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1091, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"Ripple Limit\0波动极限\0波動極限\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00050400, 0, (void *)0x00D64584, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RIPPLELIMIT,
		CA_RIPPLELIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		5,
		L"Fail Sign\0失败标志\0失敗標誌\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00090800, 0, (void *)0x00D64F7C, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RIPPLELIMIT,
		CA_RIPPLELIMIT,
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
		2,
		L"Ripple Value\0波动值\0波動值\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00080700, 0, (void *)0x00D645D4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RL_RV,
		CA_RL_RV,
		sizeof(wcsListTristate2) / sizeof(LPCWSTR),
		wcsListTristate2,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		3,
		L"Ripple Band\0波动带宽\0波動帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D645AC, (void *)0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RL_RBW,
		CA_RL_RBW,
		sizeof(wcsList12) / sizeof(LPCWSTR),
		wcsList12,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
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
		4,
		L"Open Edit Ripple Limit\0打开编辑波动极限\0打開編輯波動極限\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_OpenERL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RL_ERL,
		CA_RL_ERL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_FN_CLICKED| SIF_FN_SETFOCUS,
		SIA_FULLLINE,
		SIS_ButtonEx,
		4,
		L"Close Edit Ripple Limit\0关闭编辑波动极限\0關閉編輯波動極限\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_CloseERL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RL_ERL,
		CA_RL_ERL,
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
		TA_RL_ERL,
		CA_RL_ERL,
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
		1,
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
		TA_RL_ERL,
		CA_RL_ERL,
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
		L"Clear Ripple Limit Table\0清除波动极限表格\0清除波動極限表格\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_RL_ERL_CRLT,
		CA_RL_ERL_CRLT,
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
		3,
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
		TA_RL_ERL,
		CA_RL_ERL,
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
		TA_RL_ERL,
		CA_RL_ERL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};


//带宽极限子条目
SOFT_SUB_ITEM subitemBandwidthLimit[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"BW Test\0带宽测试\0帶寬測試\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D636BC, (void *)0x06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1092, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"BW Display\0带宽显示\0帶寬顯示\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00060500, 0, (void *)0x00D635E8, (void *)0x06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		2,
		L"BW Marker\0带宽标志\0帶寬標誌\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x000A0900, 0, (void *)0x00D635C0, (void *)0x06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		6,
		L"Fail Sign\0失败标志\0失敗標誌\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x000E0D00, 0, (void *)0x00D64F7C, (void *)0x06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_INPUT_TIME,
		SIS_InputButtonEx,
		3,
		L"N dB Points\0N dB点\0N dB點\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B34F0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		4,
		L"Min Bandwidth\0最小带宽\0最小帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01636EDC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		5,
		L"Max Bandwidth\0最大带宽\0最大帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01636F50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_BWLIMIT,
		CA_BWLIMIT,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};

//转换子条目
SOFT_SUB_ITEM subitemConversion[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Conversion\0转换\0轉換\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D63704, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CONV,
		CA_CONV,
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
		L"Function\0功能\0功能\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000C0B00, 0, (void *)0x00D636DC, (void *)0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_GetSub_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_CONV_FN,
		CA_CONV_FN,
		sizeof(wcsListCONVFUN) / sizeof(LPCWSTR),
		wcsListCONVFUN,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};


//点线子条目
SOFT_SUB_ITEM subitemPointLimit[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"PointLimit Test\0点极限测试\0點極限測試\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x0D64564, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_POINTLIMIT,
		CA_POINTLIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		1,
		L"PointLimit\0PointLimit\0PointLimit\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x0D644D4, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_POINTLIMIT,
		CA_POINTLIMIT,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
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
		2,
		L"Open Edit Limit Test\0Open Edit Limit Test\0Open Edit Limit Test\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_OpenEPL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_POINTLIMIT_EPL,
		CA_POINTLIMIT_EPL,
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
		2,
		L"Close Edit Ripple Limit\0关闭编辑波动极限\0關閉編輯波動極限\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnItemClicked_CloseEPL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_POINTLIMIT_EPL,
		CA_POINTLIMIT_EPL,
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
		TA_POINTLIMIT_EPL,
		CA_POINTLIMIT_EPL,
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
		1,
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
		TA_POINTLIMIT_EPL,
		CA_POINTLIMIT_EPL,
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
		L"Clear Point Limit Table\0清除波动极限表格\0清除波動極限表格\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_POINTLIMIT_CPLT,
		CA_POINTLIMIT_CPLT,
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
			3,
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
			TA_POINTLIMIT_EPL,
			CA_POINTLIMIT_EPL,
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
			TA_POINTLIMIT_EPL,
			CA_POINTLIMIT_EPL,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK,
			SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
			SIS_CheckButtonEx,
			1,
			L"Fail Sign\0Fail Sign\0Fail Sign\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			{ (void *)0x00010000, 0, (void *)0x0D64F7C, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_POINTLIMIT,
			CA_POINTLIMIT,
			NULL,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
};


int WINAPI fnUpdateIndex_GatingType(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
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

int WINAPI fnItemClicked_GatingType(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		fnUpdateIndex_GatingType(0, 0, 0, lpSubItem);
	}

	return 0;
}


//时域分析子条目
SOFT_SUB_ITEM subitemTimeDomain[] =
{
	{
		0,
		SIA_FULLLINE,
		SIS_Delimiter,
		0,
		L"Gating\0选通\0選通\0\0",
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
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Gating\0选通\0選通\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D62618, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING,
		CA_ANALY_GATING,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		1,
		L"Start\0起始\0起始\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637868, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING,
		CA_ANALY_GATING,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		2,
		L"Stop\0终止\0終止\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x016378D0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING,
		CA_ANALY_GATING,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		3,
		L"Center\0中心频率\0中心頻率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x01637938, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING,
		CA_ANALY_GATING,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,

	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		4,
		L"Span\0带宽\0帶寬\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x016379A0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING,
		CA_ANALY_GATING,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_FN_CLICKED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE | SIA_EXLBL | SIA_UPDATEITEM,
		SIS_ButtonEx,
		5,
		L"Type\0类型\0類型\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00030200, 0, (void *)0x00D62670, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, &fnItemClicked_GatingType, 0, &fnUpdateIndex_GatingType, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING,
		CA_ANALY_GATING,
		sizeof(wcsListGatingType) / sizeof(LPCWSTR),
		wcsListGatingType,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		0,
		L"Shape\0形状\0形狀\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x000B0A00, 0, (void *)0x00D62594, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_GATING_SHAPE,
		CA_ANALY_GATING_SHAPE,
		sizeof(wcsListShape) / sizeof(LPCWSTR),
		wcsListShape,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		0,
			SIA_FULLLINE,
			SIS_Delimiter,
			0,
			L"Transform\0变换\0變換\0\0",
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
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		0,
		L"Transform\0变换\0變換\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D634FC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_TRANSFORM,
		CA_ANALY_TRANSFORM,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
		,
		{
			SIF_ORIGCLICK | SIF_NOREPLY,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			1,
			L"Start\0起始\0起始\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637A08, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_TRANSFORM,
			CA_ANALY_TRANSFORM,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK | SIF_NOREPLY,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			2,
			L"Stop\0终止\0終止\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637A70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_TRANSFORM,
			CA_ANALY_TRANSFORM,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK | SIF_NOREPLY,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			3,
			L"Center\0中心频率\0中心頻率\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637AD8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_TRANSFORM,
			CA_ANALY_TRANSFORM,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK | SIF_NOREPLY,
			SIA_FULLLINE,
			SIS_InputButtonEx,
			4,
			L"Span\0带宽\0帶寬\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ 0, (void *)0x01637B40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			RESERVE_DWORD16,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_TRANSFORM,
			CA_ANALY_TRANSFORM,
			0,
			NULL,
			RESERVE_DWORD4,
			{ 0, 0, 0, 0 }
		}
		,
		{
			SIF_ORIGCLICK  ,
			SIA_FULLLINE ,
			SIS_ButtonEx,
			5,
			L"Set Freq Low Pass\0设置低通频率\0設置低通頻率\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H,
			NULL,
			RESERVE_DWORD16,
			RESERVE_DWORD16 ,
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_TRANSFORM,
			CA_ANALY_TRANSFORM,
			0,
			0,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
		,
		{
			SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
			SIA_FULLLINE,
			SIS_ComboButtonEx,
			0,
			L"Type\0类型\0類型\0\0",
			NULL,
			BtnWidth_W,
			BtnHeith_H2,
			NULL,
			{ (void *)0x00010200, 0, (void *)0x00D76DEC, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, &fnItemSelected_Default, &fnUpdateData_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			INVALID_INDEX,
			NULL,
			NULL,
			TA_ANALY_TRANSFORM_TYPE,
			CA_ANALY_TRANSFORM_TYPE,
			sizeof(wcsListFLType) / sizeof(LPCWSTR),
			wcsListFLType,
			RESERVE_DWORD4,
			RESERVE_DWORD4
		}
	,
	{
		SIF_ORIGCLICK | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		0,
		L"Windows\0可视化\0可視化\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00020100, 0, (void *)0x00D765F8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		0,
		0,
		NULL,
		TA_ANALY_TRANSFORM_WINDOWS,
		CA_ANALY_TRANSFORM_WINDOWS,
		sizeof(wcsListFLWindow) / sizeof(LPCWSTR),
		wcsListFLWindow,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		3,
		L"Impulse Width\0脉冲宽度\0脈衝寬度\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B3478, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_TRANSFORM_WINDOWS,
		CA_ANALY_TRANSFORM_WINDOWS,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		4,
		L"Kaiser Beta\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B348C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALY_TRANSFORM_WINDOWS,
		CA_ANALY_TRANSFORM_WINDOWS,
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
		3,
		L"TDR\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00040600, 0, (void *)0x00D76838, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, &fnUpdateData_TDR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALYSIS,
		CA_ANALYSIS,
		NULL,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ORIGCLICK  ,
		SIA_FULLLINE ,
		SIS_ButtonEx,
		4,
		L"Start TDR\0开启 TDR\0開啟 TDR\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16 ,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_ANALYSIS,
		CA_ANALYSIS,
		0,
		0,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

static int WINAPI fnUpdateData_TDR(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;
	GetButtonStateIndex((char*)0x00D76838, 0, &nIndex, 0);

	if (nIndex)
		EnableWindow(subitemTimeDomain[20]._hWnd, 1);
	else
		EnableWindow(subitemTimeDomain[20]._hWnd, 0);

	return 0;
}

int WINAPI fnTagPageEnter_TimeDomain(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM);

	OrigSoftMenu_Enter(CA_ANALY_GATING);
	OrigSoftMenu_UpdateItems(CA_ANALY_GATING);

	OrigSoftMenu_Enter(CA_ANALY_GATING_SHAPE);
	OrigSoftMenu_UpdateItems(CA_ANALY_GATING_SHAPE);

	OrigSoftMenu_Enter(CA_ANALY_TRANSFORM);
	OrigSoftMenu_UpdateItems(CA_ANALY_TRANSFORM);

	OrigSoftMenu_Enter(CA_ANALY_TRANSFORM_TYPE);
	OrigSoftMenu_UpdateItems(CA_ANALY_TRANSFORM_TYPE);

	OrigSoftMenu_Enter(CA_ANALY_TRANSFORM_WINDOWS);
	OrigSoftMenu_UpdateItems(CA_ANALY_TRANSFORM_WINDOWS);
	
	return 0;
}

int WINAPI fnTagPageEnter_FixtureSim(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM);

	OrigSoftMenu_Enter(CA_ANALY_FIXSIM_PMATCH);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_PMATCH);

	OrigSoftMenu_Enter(CA_ANALY_FIXSIM_TOPO);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_TOPO);

	OrigSoftMenu_Enter(CA_ANALY_FIXSIM_SELCIR);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_SELCIR);

	OrigSoftMenu_Enter(CA_ANALY_FIXSIM_PZCON);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_PZCON);

	OrigSoftMenu_Enter(CA_ANALY_FIXSIM_DeEMBED);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_DeEMBED);

	OrigSoftMenu_Enter(CA_ANALY_FIXSIM_CMNZCON);
	OrigSoftMenu_UpdateItems(CA_ANALY_FIXSIM_CMNZCON);
	return 0;
}

int WINAPI fnTagPageEnter_LimitTest(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_LIMITTEST);

	OrigSoftMenu_UpdateItems(CA_LT_LLO);
	OrigSoftMenu_Enter(CA_LT_LLO);
	return 0;
}

int WINAPI fnTagPageLeave_LimitTest(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Leave(CA_LT_ELL);
	return 0;
}

int WINAPI fnTagPageEnter_RippleLimit(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_RIPPLELIMIT);

	return 0;
}


int WINAPI fnTagPageLeave_RippleLimit(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_Leave(CA_RL_ERL);
	return 0;
}

int WINAPI fnTagPageEnter_BWLimit(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_BWLIMIT);

	return 0;
}

int WINAPI fnTagPageEnter_Conversion(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_CONV);

	return 0;
}
int WINAPI fnTagPageEnter_Point(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_ANALYSIS);
	OrigSoftMenu_UpdateItems(CA_POINTLIMIT);

	return 0;
}


//分析子菜单
SOFT_TAG_PAGE submenuAnalysis[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"Fixture Simulator\0固定装置仿真\0固定裝置仿真\0\0",
		NULL,
		sizeof(subitemFixtureSim) / sizeof(SOFT_SUB_ITEM),
		subitemFixtureSim,
		RESERVE_DWORD4,
		&fnTagPageEnter_FixtureSim,
		0,
		0,
		{ 0, 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Port Matching\0端口匹配\0端口匹配\0\0",
		NULL,
		sizeof(subitemPortMatch) / sizeof(SOFT_SUB_ITEM),
		subitemPortMatch,
		RESERVE_DWORD4,
		&fnTagPageEnter_FixtureSim,
		0,
		0,
		{ 0, 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Diff Matching\0差分匹配\0差分匹配\0\0",
		NULL,
		sizeof(subitemDiffMatch) / sizeof(SOFT_SUB_ITEM),
		subitemDiffMatch,
		RESERVE_DWORD4,
		&fnTagPageEnter_FixtureSim,
		0,
		0,
		{ 0, 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Time Domain\0时域分析\0時域分析\0\0",
		NULL,
		sizeof(subitemTimeDomain) / sizeof(SOFT_SUB_ITEM),
		subitemTimeDomain,
		RESERVE_DWORD4,
		&fnTagPageEnter_FixtureSim,
		0,
		0,
		{ 0, 0, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER /* | TPF_FN_LEAVE */,
		0,
		L"Limit Test\0极限测试\0極限測試\0\0",
		NULL,
		sizeof(subitemLimitTest) / sizeof(SOFT_SUB_ITEM),
		subitemLimitTest,
		RESERVE_DWORD4,
		&fnTagPageEnter_LimitTest,
		&fnTagPageLeave_LimitTest,
		0,
		{ L"::/Measurement/Data_Analysis/Limit_Test.htm", (void*)1090, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER | TPF_FN_LEAVE,
		0,
		L"Ripple Limit\0波动极限\0波動極限\0\0",
		NULL,
		sizeof(subitemRippleLimit) / sizeof(SOFT_SUB_ITEM),
		subitemRippleLimit,
		RESERVE_DWORD4,
		&fnTagPageEnter_RippleLimit,
		&fnTagPageLeave_RippleLimit,
		0,
		{ L"::/Measurement/Data_Analysis/Ripple_Test.htm", (void*)1091, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Bandwidth Limit\0带宽极限\0帶寬極限\0\0",
		NULL,
		sizeof(subitemBandwidthLimit) / sizeof(SOFT_SUB_ITEM),
		subitemBandwidthLimit,
		RESERVE_DWORD4,
		&fnTagPageEnter_BWLimit,
		NULL,
		0,
		{ L"::/Measurement/Data_Analysis/Bandwidth_Test.htm", (void*)1092, 0, 0 }
	}
	,
	{
		TPF_FN_ENTER,
		0,
		L"Conversion\0转换\0轉換\0\0",
		NULL,
		sizeof(subitemConversion) / sizeof(SOFT_SUB_ITEM),
		subitemConversion,
		RESERVE_DWORD4,
		&fnTagPageEnter_Conversion,
		NULL,
		0,
		{ 0, L"::/Measurement/Data_Analysis/Performing_Parameter_Conversion_of_Measurement_Results.htm", 0, 0 }
	}
	,
{
	TPF_FN_ENTER,
	0,
	L"PointLimit\0PointLimit\0PointLimit\0\0",
	NULL,
	sizeof(subitemPointLimit) / sizeof(SOFT_SUB_ITEM),
	subitemPointLimit,
	RESERVE_DWORD4,
	&fnTagPageEnter_Point,
	NULL,
	0,
	{ 0, L"::/Measurement/Data_Analysis/Performing_Parameter_Conversion_of_Measurement_Results.htm", 0, 0 }
}
};

//分析主菜单
SOFT_MENU menuAnalysis =
{
	0,
	0,
	L"Analysis\0分析\0分析\0\0",
	NULL,
	sizeof(submenuAnalysis) / sizeof(SOFT_TAG_PAGE),
	submenuAnalysis,
	NULL,
	NULL,
	0,
	{ 0, 0, 0, 0 }
};

