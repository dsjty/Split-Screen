#include "stdafx.h"

extern SOFT_MENU menuMeasurement;
extern SOFT_MENU menuTracesConfig;
extern SOFT_MENU menuChannelsConfig;
extern SOFT_MENU menuMarker;
extern SOFT_MENU menuAnalysis;
extern SOFT_MENU menuAverage;
extern SOFT_MENU menuSweepSetup;
extern SOFT_MENU menuCalibration;
extern SOFT_MENU menuFrequency;
extern SOFT_MENU menuPower;
extern SOFT_MENU menuSystem;
extern SOFT_MENU menuSaveRecall;
extern SOFT_MENU menuDisplay;
extern SOFT_MENU menuMacroSetup;
extern SOFT_MENU menuPreset;

int WINAPI fnClicked_Preset(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

//
//曲线子条目
SOFT_SUB_ITEM subitemTrace[] =
{
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Traces Config\0曲线配置\0曲線配置\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm#Setting_trace_display" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuTracesConfig,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1024, 0, 0 }
	}
	,
	{
		SIF_SNDMSGCMD,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Trace Next\0切换曲线\0切換曲線\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm#Setting_trace_display" },
		RESERVE_DWORD16,
		0,
		NULL,
		(WPARAM)0x000003EB,
		0,
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1024, 0, 0 }
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
		BtnHeith_Root,
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
		{ 0, 1010, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Measurement\0测量\0測量\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Measurement.htm" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuMeasurement,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1021, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Marker\0频标\0頻標\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Data_Analysis/Analyzing_Data_on_the_Trace_Using_the_Marker.htm" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuMarker,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1082, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Analysis\0分析\0分析\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Data_Analysis/Analysis.htm" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuAnalysis,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1127, 0, 0 }
	}

};

int WINAPI fnClicked_ChannelMax(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam==IC_CLICKED_LAST)
	{
		OrigSoftMenu_ItemClicked2(CA_TRIGGER, TA_TRIGGER, 3);
		OrigSoftMenu_ItemClicked2(CA_TRIGGER, TA_TRIGGER, 2);
	}
	return 0;
}

int WINAPI fnClicked_Test(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		PSTMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuDisplay);

		//OrigSoftMenu_ItemClicked2(CA_SYSTEM, TA_SYSTEM, 2);
	}
	return 0;
}

//通道子条目
SOFT_SUB_ITEM subitemChannel[] =
{
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Channels Config\0通道配置\0通道配置\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm#Setting_channel_display__layout_of_channel_windows_" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuChannelsConfig,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1024, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Average\0平均\0平均\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm#Parameter_setting_for_each_setup_item__analyzer__channel__trace_" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuAverage,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1024, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Sweep Setup\0扫描设置\0掃描設置\0\0",
			NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuSweepSetup,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1026, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Calibration\0校准\0校準\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"::/Measurement/Calibration/Calibration.htm" },
		RESERVE_DWORD16,
		0,
		NULL,
		NULL,
		NULL,
		&menuCalibration,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1031, 0, 0 }
	}
//	,
//	{
//		SIF_FN_CLICKED,
//		SIA_FULLLINE,
//		SIS_ButtonEx,
//		0,
//		L"Test\0\0",
//		NULL,
//		BtnWidth_W,
//		BtnHeith_H,
//		NULL,
//		RESERVE_DWORD16,
//		{ 0, &fnClicked_Test,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//		0,
//		NULL,
//		NULL,
//		NULL,
//		0,
//		0,
//		NULL,
//		RESERVE_DWORD4,
//		RESERVE_DWORD4
//	}
};


//激励源子条目
SOFT_SUB_ITEM subitemStimulus[] =
{
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Frequency\0频率\0頻率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		&menuFrequency,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		1,
		L"Power\0功率\0功率\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		&menuPower,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
};

//系统子条目
SOFT_SUB_ITEM subitemSystem[] =
{
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Display\0显示\0顯示\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		&menuDisplay,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Save/Recall\0存储/调用\0存儲/調用\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		&menuSaveRecall,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1096, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"System\0系统\0系統\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		&menuSystem,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Macro Setup\0宏指令设置\0宏指令設置\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		&menuMacroSetup,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 0, 0, 0 }
	}
	,
	{
		SIF_ISMENU,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Help\0帮助\0幫助\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1001, 0, 0 }
	}
	,
	{
		SIF_FN_CLICKED,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Preset\0复位\0復位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_Root,
		NULL,
		RESERVE_DWORD16,
		{ 0, &fnClicked_Preset, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		INVALID_INDEX,
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		NULL,
		RESERVE_DWORD4,
		{ 0, 1010, 0, 0 }
	}
};

int WINAPI fnClicked_Preset(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (wParam == IC_CLICKED_LAST)
	{
		ConfirmPreset();
	}
	return 0;
}


SOFT_TAG_PAGE submenuMain[] =
{
	{
		0,
		0,
		L"Channel\0通道\0通道\0\0",
		NULL,
		sizeof(subitemChannel) / sizeof(SOFT_SUB_ITEM),
		subitemChannel,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm", 0, 0, 0 }
	}
	,
	{
		0,
		0,
		L"Trace\0曲线\0曲線\0\0",
		NULL,
		sizeof(subitemTrace) / sizeof(SOFT_SUB_ITEM),
		subitemTrace,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Channels_and_Traces.htm", 0, 0, 0 }
	}
	,
	{
		0,
		0,
		L"Stimulus\0激励源\0激勵源\0\0",
		NULL,
		sizeof(subitemStimulus) / sizeof(SOFT_SUB_ITEM),
		subitemStimulus,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Measurement/Setting_Measurement_Conditions/Setting_Stimulus_Conditions.htm", 0, 0, 0 }
	}
	,
	{
		0,
		0,
		L"System\0系统\0系統\0\0",
		NULL,
		sizeof(subitemSystem) / sizeof(SOFT_SUB_ITEM),
		subitemSystem,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Setting_Control_Functions/System.htm", 0, 0, 0 }
	}
};

static int WINAPI fnSoftMenuEnter_Root(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_MENU *lpSoftMenu)
{
	DirectCall((void*)(BASE + (DWORD)CA_ROOT), GetOffsetPointer((void*)(BASE + (DWORD)TA_ROOT), 0x08));
	return 0;
}

//根菜单
SOFT_MENU menuRoot =
{
	SMF_FN_ENTER,
	0,
	L"TD3618D Menu\0TD3618D 菜单\0TD3618D 菜單\0\0",
	NULL,
	sizeof(submenuMain) / sizeof(SOFT_TAG_PAGE),
	submenuMain,
	&fnSoftMenuEnter_Root,
	NULL,
	0,
	RESERVE_DWORD4
};

void UpdatePresetState()
{
	const char *lpInfFile;
	UINT uVal;

	lpInfFile = (const char *)GetOffsetPointer((void *)0x00BB41B0, 0x94);

	uVal = GetPrivateProfileIntA("PRESET", "CONFIRM", 1, lpInfFile);

	if (uVal != 0)
	{
		subitemSystem[5].dwFlags = SIF_ISMENU;
		subitemSystem[5].dwFunctionId = 0;
		subitemSystem[5].lpVTable = NULL;
		subitemSystem[5].lpThis = &menuPreset;
	}
	else
	{
		subitemSystem[5].dwFlags = SIF_ORIGCLICK | SIF_NOT_ENTER;
		subitemSystem[5].dwFunctionId = 0;
		subitemSystem[5].lpVTable = TA_PRESET;
		subitemSystem[5].lpThis = CA_PRESET;
	}
}