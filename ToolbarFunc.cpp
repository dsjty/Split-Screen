#include "stdafx.h"

#define MENU_SYSTEM             1
#define MENU_STIMULUS           2
#define MENU_CHANNELS           3
#define MENU_TRACES             4

#define MENU_SYS_SYSTEM         10
#define MENU_SYS_SAVERECALL     11
#define MENU_SYS_DISPLAY        12
#define MENU_SYS_MACRO          13
#define MENU_SYS_HELP           14
#define MENU_SYS_PRESET         15

#define MENU_STI_FREQ           20
#define MENU_STI_POWER          21

#define MENU_CEL_NEXT           30
#define MENU_CEL_MAX            31
#define MENU_CEL_CONFIG         32
#define MENU_CEL_AVG            33
#define MENU_CEL_SWEEP          34
#define MENU_CEL_CAL            35

#define MENU_TRC_NEXT           40
#define MENU_TRC_MAX            41
#define MENU_TRC_CONFIG         42
#define MENU_TRC_MEAS           43
#define MENU_TRC_MARKER         44
#define MENU_TRC_ANALYSIS       45 

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


static HMENU hSubMenu_System = NULL;
static HMENU hSubMenu_Stimulus = NULL;
static HMENU hSubMenu_Channels = NULL;
static HMENU hSubMenu_Traces = NULL;
static HMENU hPopupMenu = NULL;


void ScreenToBitmap(HWND hwnd);

static void InitPopupMenu()
{
	if (hPopupMenu == NULL)
	{
		MENUITEMINFOW MII;

		if (hSubMenu_System) 
			DestroyMenu(hSubMenu_System);

		if (hSubMenu_Stimulus) 
			DestroyMenu(hSubMenu_Stimulus);

		if (hSubMenu_Channels) 
			DestroyMenu(hSubMenu_Channels);

		if (hSubMenu_Traces) 
			DestroyMenu(hSubMenu_Traces);

		hSubMenu_System = CreatePopupMenu();
		hSubMenu_Stimulus = CreatePopupMenu();
		hSubMenu_Channels = CreatePopupMenu();
		hSubMenu_Traces = CreatePopupMenu();
		hPopupMenu = CreatePopupMenu();

		memset(&MII, 0, sizeof(MENUITEMINFOW));
		MII.cbSize = sizeof(MENUITEMINFOW);
		
		//根菜单
		MII.fMask = MIIM_FTYPE | MIIM_SUBMENU | MIIM_ID | MIIM_STRING;
		MII.fType = MFT_OWNERDRAW;

		MII.wID = MENU_CHANNELS;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Channels\0通道\0通道\0\0", nLangId);
		MII.hSubMenu = hSubMenu_Channels;
		InsertMenuItemW(hPopupMenu, MENU_CHANNELS, FALSE, &MII);

		MII.wID = MENU_TRACES;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Traces\0曲线\0曲線\0\0", nLangId);
		MII.hSubMenu = hSubMenu_Traces;
		InsertMenuItemW(hPopupMenu, MENU_TRACES, FALSE, &MII);

		MII.wID = MENU_STIMULUS;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Stimulus\0激励源\0激勵源\0\0", nLangId);
		MII.hSubMenu = hSubMenu_Stimulus;
		InsertMenuItemW(hPopupMenu, MENU_STIMULUS, FALSE, &MII);

		MII.wID = MENU_SYSTEM;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"System\0系统\0系統\0\0", nLangId);
		MII.hSubMenu = hSubMenu_System;
		InsertMenuItemW(hPopupMenu, MENU_SYSTEM, FALSE, &MII);
				
		memset(&MII, 0, sizeof(MENUITEMINFOW));
		MII.cbSize = sizeof(MENUITEMINFOW);
		//START子菜单
		MII.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STRING;
		MII.fType = MFT_OWNERDRAW;
		
		//通道
		MII.wID = MENU_CEL_CONFIG;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Channels Config\0通道配置\0通道配置\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Channels, MENU_CEL_CONFIG, FALSE, &MII);

		MII.wID = MENU_CEL_NEXT;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Channel Next\0切换通道\0切換通道\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Channels, MENU_CEL_NEXT, FALSE, &MII);

		MII.wID = MENU_CEL_MAX;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Channel Max\0通道最大化\0通道最大化\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Channels, MENU_CEL_MAX, FALSE, &MII);

		MII.wID = MENU_CEL_AVG;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Average\0平均\0平均\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Channels, MENU_CEL_AVG, FALSE, &MII);

		MII.wID = MENU_CEL_SWEEP;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Sweep Setup\0扫描设置\0掃描設置\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Channels, MENU_CEL_SWEEP, FALSE, &MII);

		MII.wID = MENU_CEL_CAL;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Calibration\0校准\0校準\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Channels, MENU_CEL_CAL, FALSE, &MII);

		//曲线
		MII.wID = MENU_TRC_CONFIG;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Traces Config\0曲线配置\0曲線配置\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Traces, MENU_TRC_CONFIG, FALSE, &MII);

		MII.wID = MENU_TRC_NEXT;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Trace Next\0切换曲线\0切換曲線\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Traces, MENU_TRC_NEXT, FALSE, &MII);

		MII.wID = MENU_TRC_MAX;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Trace Max\0曲线最大化\0曲線最大化\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Traces, MENU_TRC_MAX, FALSE, &MII);
		
		MII.wID = MENU_TRC_MEAS;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Measurement\0测量\0測量\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Traces, MENU_TRC_MEAS, FALSE, &MII);

		MII.wID = MENU_TRC_MARKER;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Marker\0频标\0頻標\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Traces, MENU_TRC_MARKER, FALSE, &MII);

		MII.wID = MENU_TRC_ANALYSIS;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Analysis\0分析\0分析\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Traces, MENU_TRC_ANALYSIS, FALSE, &MII);

		//激励源
		MII.wID = MENU_STI_FREQ;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Frequency\0频率\0頻率\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Stimulus, MENU_STI_FREQ, FALSE, &MII);

		MII.wID = MENU_STI_POWER;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Power\0功率\0功率\0\0", nLangId);
		InsertMenuItemW(hSubMenu_Stimulus, MENU_STI_POWER, FALSE, &MII);

		//系统
		MII.wID = MENU_SYS_DISPLAY;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Display\0显示\0顯示\0\0", nLangId);
		InsertMenuItemW(hSubMenu_System, MENU_SYS_DISPLAY, FALSE, &MII);

		MII.wID = MENU_SYS_SAVERECALL;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Save/Recall\0存储/调用\0存儲/調用\0\0", nLangId);
		InsertMenuItemW(hSubMenu_System, MENU_SYS_SAVERECALL, FALSE, &MII);

		MII.wID = MENU_SYS_SYSTEM;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"System\0系统\0系統\0\0", nLangId);
		InsertMenuItemW(hSubMenu_System, MENU_SYS_SYSTEM, FALSE, &MII);

		MII.wID = MENU_SYS_MACRO;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Macro Setup\0宏指令设置\0宏指令設置\0\0", nLangId);
		InsertMenuItemW(hSubMenu_System, MENU_SYS_MACRO, FALSE, &MII);

		MII.wID = MENU_SYS_HELP;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Help\0帮助\0幫助\0\0", nLangId);
		InsertMenuItemW(hSubMenu_System, MENU_SYS_HELP, FALSE, &MII);

		MII.wID = MENU_SYS_PRESET;
		MII.dwTypeData = (LPWSTR)GetStringByIndex(L"Preset\0复位\0復位\0\0", nLangId);
		InsertMenuItemW(hSubMenu_System, MENU_SYS_PRESET, FALSE, &MII);		
	}
}

static void UpdatePopupMenu()
{

}
	//弹出式菜单事件
int WINAPI fntbEvent_Start(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
	{
		RECT rect;
		POINT pt1;
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN), nY;
		UINT uFlags = 0;

		if (hPopupMenu == NULL)
			InitPopupMenu();
		else
			UpdatePopupMenu();

		GetClientRect(hToolbar, &rect);

		pt1.x = rect.left;
		pt1.y = rect.top;
		ClientToScreen(hToolbar, &pt1);
		rect.left = pt1.x;
		rect.top = pt1.y;

		pt1.x = rect.right;
		pt1.y = rect.bottom;
		ClientToScreen(hToolbar, &pt1);
		rect.right = pt1.x;
		rect.bottom = pt1.y;

		if (nScreenHeight - rect.bottom >= 220)
		{
			nY = rect.bottom + 2;
		}
		else
		{
			nY = rect.top - 2;
			uFlags |= TPM_BOTTOMALIGN;
		}

		TrackPopupMenu(hPopupMenu, uFlags, rect.left, nY, 0, hToolbar, NULL);
	}
	break;
	}

	return 0;
}

int WINAPI fnMenuEvent_Start(DWORD dwMenuId, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwMenuId)
	{
	case MENU_SYS_SYSTEM:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuSystem);
		break;

	case MENU_SYS_SAVERECALL:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuSaveRecall);
		break;

	case MENU_SYS_DISPLAY:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuDisplay);
		break;

	case MENU_SYS_MACRO:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMacroSetup);
		break;

	case MENU_SYS_HELP:
		TagPage_ShowHelp(NULL);
		break;

	case MENU_SYS_PRESET:
		//SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuPreset);
		//OrigSoftMenu_ItemClicked2(CA_PRESET, TA_PRESET, 0);
		ConfirmPreset();
		break;
		
	case MENU_STI_FREQ:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuFrequency);
		break;

	case MENU_STI_POWER:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuPower);
		break;
		
	case MENU_CEL_NEXT:
		SNDMSG(hwMainWnd, WM_COMMAND, 0x000003E9, NULL);
		break;

	case MENU_CEL_MAX:
		OrigSoftMenu_ItemClicked2(CA_TRIGGER, TA_TRIGGER, 3);
		OrigSoftMenu_ItemClicked2(CA_TRIGGER, TA_TRIGGER, 2);
		SNDMSG(hwMainWnd, WM_COMMAND, 0x000003EC, NULL);
		UpdateSoftMenu();
		break;

	case MENU_CEL_CONFIG:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuChannelsConfig);
		break;

	case MENU_CEL_AVG:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuAverage);
		break;

	case MENU_CEL_SWEEP:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuSweepSetup);
		break;

	case MENU_CEL_CAL:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuCalibration);
		break;
		
	case MENU_TRC_NEXT:
		SNDMSG(hwMainWnd, WM_COMMAND, 0x000003EB, NULL);
		break;

	case MENU_TRC_MAX:
		SNDMSG(hwMainWnd, WM_COMMAND, 0x000003ED, NULL);
		break;

	case MENU_TRC_CONFIG:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuTracesConfig);
		break;

	case MENU_TRC_MEAS:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMeasurement);
		break;

	case MENU_TRC_MARKER:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMarker);
		break;

	case MENU_TRC_ANALYSIS:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuAnalysis);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Explorer(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		ShellExecuteA(NULL, "explore", "d://", NULL, NULL, SW_SHOW);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Recall(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		OrigSoftMenu_UpdateItems(CA_ROOT);
		OrigSoftMenu_UpdateItems(CA_SR);
		OrigSoftMenu_ItemClicked2(CA_SR_RS, TA_SR_RS, 10);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Save(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		OrigSoftMenu_UpdateItems(CA_ROOT);
		OrigSoftMenu_UpdateItems(CA_SR);
		OrigSoftMenu_ItemClicked2(CA_SR_SS, TA_SR_SS, 10);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_TraceMax(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		SNDMSG(hwMainWnd, WM_COMMAND, 0x000003ED, NULL);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Snapshot(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
	{
		ScreenToBitmap(hToolbar);
		//OrigSoftMenu_ItemClicked2(CA_SYSTEM, TA_SYSTEM, 2);	第一次调用5070功能会莫名其妙的bug，反正功能简单，自己写得了。
		break;
	}
	}
	return 0;
}

int WINAPI fntbEvent_LoadRun(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 1, (LPARAM)&menuMacroSetup);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Print(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		OrigSoftMenu_ItemClicked2(CA_SYSTEM, TA_SYSTEM, 0);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Help(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		TagPage_ShowHelp(NULL);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Invert(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		OrigSoftMenu_ItemClicked2(CA_DISPLAY, TA_DISPLAY, 12);
		UpdateCurrentItemsAndData();
		break;
	}
	return 0;
}

int WINAPI fntbEvent_NewTrace(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
	{
		int nIndex = 0;

		GetButtonStateIndex((char *)0x00D6A8CC, (void *)0x0B, &nIndex, 0x00010000);

		if ((nIndex > 0) && (nIndex < 4))
		{
			OrigSoftMenu_ItemClicked2(CA_TRACESNUM, TA_TRACESNUM, nIndex);
		}
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMeasurement);
	}
	break;
	}

	return 0;
}


int WINAPI fntbEvent_DelTrace(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
	{
		int nIndex = 0;

		GetButtonStateIndex((char *)0x00D6A8CC, (void *)0x0B, &nIndex, 0x00010000);

		if ((nIndex-- > 0))
		{
			OrigSoftMenu_ItemClicked2(CA_TRACESNUM, TA_TRACESNUM, --nIndex);
			SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMeasurement);
		}
	}
	break;
	}

	return 0;
}

int WINAPI fntbEvent_ChannelsConfig(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuChannelsConfig);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_TracesConfig(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
		SNDMSG(hwSoftMenu, WM_SWITCH_SUBMENU, 0, (LPARAM)&menuTracesConfig);
		break;
	}

	return 0;
}

int WINAPI fntbEvent_Marker(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	switch (dwCode)
	{
	case TBEC_CLICKED:
	{
		for (int nIndex = 0; nIndex < 9; nIndex++)
		{
			if (GetButtonCheckState((void *)0x035BADD0, nIndex) == 0)
			{
				if (nIndex < 4)
				{
					OrigSoftMenu_ItemClicked2(CA_MARKER, TA_MARKER, nIndex);
				}
				else
				{
					OrigSoftMenu_ItemClicked2(CA_MREMARKER, TA_MREMARKER, nIndex - 4);
				}

				PSTMSG_432_2();
				UpdateCurrentItemsAndData();
				break;
			}
		}
	}
	break;
	}

	return 0;
}

int WINAPI fntbEvent_MarkerSub(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem)
{
	int iSer = 0;
	switch (dwCode)
	{
	case TBEC_CLICKED:
	{
		for (int nIndex = 9; nIndex > 0; nIndex--)	
		{
			iSer = nIndex + 1;
			if (GetButtonCheckState((void*)0x035BADD0, nIndex) != 0)  //目测问题是查询的按钮为nIndex-1序列
			{
				OrigSoftMenu_ItemClicked2(CA_CLRMARKER, TA_CLRMARKER, iSer);
				break;
			}
		}
		PSTMSG_432_2();
		UpdateCurrentItemsAndData();
	}
	break;
	}
	return 0;
}

void ScreenToBitmap(HWND hwnd)   //lpRect   代表选定区域   
{
	CWnd *pDesktop = CWnd::FromHandle(GetParent(hwnd));
	CDC *pdeskdc = pDesktop->GetDC();
	CRect re;

	//获取窗口的大小
	pDesktop->GetClientRect(&re);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());

	//创建一个兼容的内存画板
	CDC memorydc;
	memorydc.CreateCompatibleDC(pdeskdc);
	//选中画笔
	CBitmap *pold = memorydc.SelectObject(&bmp);
	//绘制图像
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);

	//获取鼠标位置，然后添加鼠标图像
	CPoint po;
	GetCursorPos(&po);
	HICON hinco = (HICON)GetCursor();
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco);

	//选中原来的画笔
	memorydc.SelectObject(pold);
	BITMAP bit;
	bmp.GetBitmap(&bit);

	//定义 图像大小（单位：byte）
	DWORD size = bit.bmWidthBytes * bit.bmHeight;
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);

	//后面是创建一个bmp文件的必须文件头
	BITMAPINFOHEADER pbitinfo;
	pbitinfo.biBitCount = 24;
	pbitinfo.biClrImportant = 0;
	pbitinfo.biCompression = BI_RGB;
	pbitinfo.biHeight = bit.bmHeight;
	pbitinfo.biPlanes = 1;
	pbitinfo.biSize = sizeof(BITMAPINFOHEADER);
	pbitinfo.biSizeImage = size;
	pbitinfo.biWidth = bit.bmWidth;
	pbitinfo.biXPelsPerMeter = 0;
	pbitinfo.biYPelsPerMeter = 0;

	GetDIBits(pdeskdc->m_hDC, bmp, 0, pbitinfo.biHeight, lpdata, (BITMAPINFO*)&pbitinfo, DIB_RGB_COLORS);

	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = 0x4D42;
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ((size + 31) / 32) * 4 * bit.bmHeight;;
	bfh.bfOffBits = 54;


	//写入文件
	//弹框获取文件路径和文件名
	CHAR szFilter[MAX_PATH] = "24-bit Bitmap (*.bmp)|*.bmp| Portable Network Graphics (*.png)|*.png||";
	//   "24-bit Bitmap (*.bmp)|*.bmp| Portable Network Graphics (*.png)|*.png||";
	BOOL bOpenFileDialog = FALSE;
	CFileDialog filedlg(bOpenFileDialog, "bmp", "IMAGE01", NULL, szFilter, pDesktop);

	CStringA strfilePath = "";
	if (IDOK == filedlg.DoModal())
	{
		strfilePath = filedlg.GetPathName();
	}

	CFile file;

	if (file.Open((LPCTSTR)strfilePath.GetBuffer(), CFile::modeCreate | CFile::modeWrite))
	{
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));
		file.Write(lpdata, size);
		file.Close();
	}
	GlobalFree(lpdata);
}



