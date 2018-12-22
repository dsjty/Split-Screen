#include "stdafx.h"

const LPCWSTR wcsListTracesNum[] =
{
	L" 1 \0 1 \0 1 \0\0",
	L" 2 \0 2 \0 2 \0\0",
	L" 3 \0 3 \0 3 \0\0",
	L" 4 \0 4 \0 4 \0\0",
	L" 5 \0 5 \0 5 \0\0",
	L" 6 \0 6 \0 6 \0\0",
	L" 7 \0 7 \0 7 \0\0",
	L" 8 \0 8 \0 8 \0\0",
	L" 9 \0 9 \0 9 \0\0",
};


//曲线配置子条目
SOFT_SUB_ITEM subitemTracesConfig[] =
{
	{
		SIF_FN_SELECTED | SIF_FN_UPDATEDATA,
		SIA_FULLLINE,
		SIS_ComboButtonEx,
		1,
		L"Number of Traces\0曲线数\0曲線數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ (void *)0x00010000, 0, (void *)0x00D6A8CC, (void *)0x0B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, &fnItemSelected_Default, &fnUpdateData_DEC_Default, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		TA_TRACESNUM,
		CA_TRACESNUM,
		sizeof(wcsListTracesNum) / sizeof(LPCWSTR),
		wcsListTracesNum,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK,
		SIA_BITMAP | SIA_MAINRES | SIA_GROUP,
		SIS_RadioButtonEx,
		0,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_X1,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X2_1,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X2_2,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X2_3,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X2_4,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X3_1,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X3_2,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		7,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		1,
		(void *)IDB_BMP_X3_3,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X3_4,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X3_5,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		1,
		(void *)IDB_BMP_X3_6,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		11,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		1,
		(void *)IDB_BMP_X4_1,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		12,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		1,
		(void *)IDB_BMP_X4_2,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
		13,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		1,
		(void *)IDB_BMP_X4_3,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
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
    	14,
    	NULL,
    	NULL,
    	BtnWidth_W,
    	BtnHeith_H2,
    	NULL,
    	RESERVE_DWORD16,
    	RESERVE_DWORD16,
    	0,
    	(void *)IDB_BMP_X6_1,
    	NULL,
    	TA_ALLOCTRACES,
    	CA_ALLOCTRACES,
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
    	15,
    	NULL,
    	NULL,
    	BtnWidth_W,
    	BtnHeith_H2,
    	NULL,
    	RESERVE_DWORD16,
    	RESERVE_DWORD16,
    	0,
    	(void *)IDB_BMP_X6_2,
    	NULL,
    	TA_ALLOCTRACES,
    	CA_ALLOCTRACES,
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
    	16,
    	NULL,
    	NULL,
    	BtnWidth_W,
    	BtnHeith_H2,
    	NULL,
    	RESERVE_DWORD16,
    	RESERVE_DWORD16,
    	0,
    	(void *)IDB_BMP_X8_1,
    	NULL,
    	TA_ALLOCTRACES,
    	CA_ALLOCTRACES,
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
    	17,
    	NULL,
    	NULL,
    	BtnWidth_W,
    	BtnHeith_H2,
    	NULL,
    	RESERVE_DWORD16,
    	RESERVE_DWORD16,
    	0,
    	(void *)IDB_BMP_X8_2,
    	NULL,
    	TA_ALLOCTRACES,
    	CA_ALLOCTRACES,
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
		18,
		NULL,
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		(void *)IDB_BMP_X9_1,
		NULL,
		TA_ALLOCTRACES,
		CA_ALLOCTRACES,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}    
};


//当前曲线子条目
SOFT_SUB_ITEM subitemCurrentTraces[] =
{
	{
		SIF_SNDMSGCMD,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Trace Prev\0前一曲线\0前壹曲線\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		(WPARAM)0x000003EA,
		0,
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_SNDMSGCMD,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Trace Next\0后一曲线\0後壹曲線\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		(WPARAM)0x000003EB,
		0,
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_SNDMSGCMD,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Trace Max\0曲线最大化\0曲線最大化\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		(WPARAM)0x000003ED,
		0,
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


int WINAPI fnTagPageEnter_TracesConfig(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage);


//曲线配置子菜单
SOFT_TAG_PAGE submenuTracesConfig[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"Traces Config\0曲线配置\0曲線配置\0\0",
		NULL,
		sizeof(subitemTracesConfig) / sizeof(SOFT_SUB_ITEM),
		subitemTracesConfig,
		RESERVE_DWORD4,
		&fnTagPageEnter_TracesConfig,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm#Setting_trace_display", 0, 0, 0 }
	}
	,
	{
		0,
		0,
		L"Current Traces\0当前曲线\0當前曲線\0\0",
		NULL,
		sizeof(subitemCurrentTraces) / sizeof(SOFT_SUB_ITEM),
		subitemCurrentTraces,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm", 0, 0, 0 }
	}
};



int WINAPI fnTagPageEnter_TracesConfig(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
{
	OrigSoftMenu_UpdateItems(CA_DISPLAY);
	OrigSoftMenu_UpdateItems(CA_ALLOCTRACES);

	if (nTraces <= 9)
		subitemTracesConfig[0].dwNumberOfParams = nTraces;

	switch (nTraces)
	{
	case 4:
		submenuTracesConfig[0].dwNumOfSubItems = 14 + 1;
		break;
	case 6:
		submenuTracesConfig[0].dwNumOfSubItems = 16 + 1;
		break;
	case 8:
		submenuTracesConfig[0].dwNumOfSubItems = 18 + 1;
		break;
	case 9:
		submenuTracesConfig[0].dwNumOfSubItems = 19 + 1;
		break;
	case 12:
		submenuTracesConfig[0].dwNumOfSubItems = 19 + 1;
		break;
	case 16:
		submenuTracesConfig[0].dwNumOfSubItems = 19 + 1;
		break;
	case 24:
		submenuTracesConfig[0].dwNumOfSubItems = 19 + 1;
		break;
	case 36:
		submenuTracesConfig[0].dwNumOfSubItems = 19 + 1;
		break;
	default:
		break;
	}

	return 0;
}

//曲线配置主菜单
SOFT_MENU menuTracesConfig =
{
	0,
	0,
	L"Traces Config\0曲线配置\0曲線配置\0\0",
	NULL,
	sizeof(submenuTracesConfig) / sizeof(SOFT_TAG_PAGE),
	submenuTracesConfig,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
