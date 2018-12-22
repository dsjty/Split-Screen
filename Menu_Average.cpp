#include "stdafx.h"


//平均子条目
SOFT_SUB_ITEM subitemAverage[] =
{
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Averaging Restart\0平均重新开始\0平均重新開始\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
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
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE,
		SIS_InputButtonEx,
		1,
		L"Avg Factor\0平均系数\0平均系數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B35B4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		2,
		L"Averaging\0平均\0平均\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00050400, 0, (void *)0x00D65580, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_AVERAGE,
		CA_AVERAGE,
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
		L"Avg Trigger\0平均触发\0平均觸發\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x000D0C00, 0, (void *)0x00D68C58, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_AVERAGE,
		CA_AVERAGE,
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
		4,
		L"Smo Aperture\0平滑系数\0平滑系數\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H2,
		NULL,
		{ 0, (void *)0x010B35C4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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
	,
	{
		SIF_ORIGCLICK,
		SIA_FULLLINE | SIA_GETBTNSTATE | SIA_UPDATEITEM,
		SIS_CheckButtonEx,
		5,
		L"Smoothing\0平滑\0平滑\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		{ (void *)0x00090800, 0, (void *)0x00D646AC, (void *)0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_AVERAGE,
		CA_AVERAGE,
		NULL,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		SIF_ORIGCLICK | SIF_NOREPLY,
		SIA_FULLLINE | SIA_FINETUNE,
		SIS_InputButtonEx,
		6,
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

int WINAPI fnTagPageEnter_Average(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage)
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

//平均子菜单
SOFT_TAG_PAGE submenuAverage[] =
{
	{
		TPF_FN_ENTER,
		0,
		L"Average\0平均\0平均\0\0",
		NULL,
		sizeof(subitemAverage) / sizeof(SOFT_SUB_ITEM),
		subitemAverage,
		RESERVE_DWORD4,
		&fnTagPageEnter_Average,
		NULL,
		0,
		{ 0, L"::/Measurement/Optimizing_Measurements/Expanding_the_Dynamic_Range.htm#Turning_on_Sweep_Averaging", 0, 0 }
	}
};

//平均主菜单
SOFT_MENU menuAverage =
{
	0,
	0,
	L"Average\0平均\0平均\0\0",
	NULL,
	sizeof(submenuAverage) / sizeof(SOFT_TAG_PAGE),
	submenuAverage,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};
