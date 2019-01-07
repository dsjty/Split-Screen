#pragma once

#include "stdafx.h"

//窗口类原子
ATOM wcSoftMenu = 0;
ATOM wcSoftItem = 0;
ATOM wcToolBar = 0;

DWORD dwBaseAdd = 0;

extern WORD wWidth_SoftMenu;
void SetSoftMenuWidth(WORD wWidth);
BOOL WndCHK_TDR();

DWORD dwTDRDataAdd = NULL;

//语言Id 0=英语,1=简体中文,2=繁体中文
int nLangId = 1;

int nChannels = 0, nTraces = 0;


//钩子跳转指针结构
static HOOK_JMPPTR hjpOnSize = { (BASE + 0x94E3F9), (DWORD)&ef_CWnd__OnSize_main, 6, 0 };

//Hook指针的结构体数组
HOOK_PTR HookPtr[] =
{
	{ (void**)0xE90338, NULL, &ef_CWnd__Create },  //CWnd::Create  ,Ref: 004A8D58   .  FF52 5C       call    dword ptr ds:[edx+0x5C]
	{ NULL, NULL, NULL }
};

//位图句柄
//hBmp_Button* 为按钮背景图的位图句柄, 1为按钮,2为标签,S为选中,u为不可用,R为返回键用;
HBITMAP hBmp_Button1, hBmp_Button1s, hBmp_Button2, hBmp_ButtonR, hBmp_ButtonU, hBmp_Button2s, hBmp_ButtonF;
//复选框位图句柄
HBITMAP hBmp_Checked, hBmp_Unchecked;
//频标的确认按钮位图句柄
HBITMAP hBmp_Enter;

//备份的字节码
static WORD wBakw_004A8FA0 = 0xFF6A, wBakw_004A90A0 = 0xFF6A;

//窗口过程
LRESULT CALLBACK wpfn_ToolBar(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//初始化原程序界面多语言hook
int InitLocaleHook();

//输入框跳过
#if CF_FNHK_PASS_004A8FA0 
NAKED int __stdcall fnhk_x1463D0(int nVar0, int nVar1, int nVar2, int nVar3)
{
	__asm xor eax, eax
	__asm inc eax
	__asm retn 0x10
}
#endif

//文本输入框跳过
#if CF_FNHK_PASS_004A90A0
NAKED int __stdcall fnhk_x13D550(int nVar0)
{
	__asm xor eax, eax
	__asm inc eax
	__asm retn 0x04
}
#endif

//009061C7 挂钩函数 (第四章 曲线信息栏 实现函数)
#ifdef CF_FNHK_00906467
//typedef void *(__thiscall *func_00905E20)(void *lpThis, int nQueryTraceIndex);
//static func_00905E20 fn00905E20 = (func_00905E20)0x00905E20;

typedef void *(__thiscall *func_00906190)(void *lpThis, LPPOINT lpPoint);
static func_00906190 fn00906190 = (func_00906190)0x00906190;

//extern SOFT_MENU menuMeasurement;
extern HWND hwSoftMenu, hwSoftMenu2;

int WINAPI fnGetPointX(LPPOINT lpPt, void *lpESI)
{
	if (lpESI == NULL) return lpPt->x;

	void *lpBase = (void *)((int)lpESI + 0xE0);
	LPRECT lpRect;
	//bool *lpBool;
	int nIndex = 0;

	do
	{
		lpRect = (LPRECT)((int)GetOffsetPointer(lpBase, 0) + 0x0C);

		if (PtInRect(lpRect, *lpPt))
			return lpPt->x - lpRect->left;

		nIndex++;
		lpBase = (void *)((int)lpBase + 4);

	} while (nIndex < 17);

	return lpPt->x;
}

NAKED void * fnhk_00906467()
{
// 	__asm push dword ptr[esp + 0x04]
// 	__asm call dword ptr fn00906190
// 	__asm push eax
// 	__asm test eax, eax
// 	__asm je lbl_Retn
// 	__asm mov ecx, dword ptr[esp + 0x08]
// 	__asm test ecx, ecx
// 	__asm je lbl_Retn
// 	__asm push[esp + 0x10]
// 	__asm push ecx
// 	__asm call fnGetPointX
// 	//__asm mov edx, dword ptr [ecx]
// 
// 	__asm mov edx, eax
// 	__asm cmp edx, 0x20
// 	__asm jl lbl_Retn
// 	__asm lea ecx, menuMeasurement
// 	__asm push ecx
// 	__asm cmp edx, 0x40
// 	__asm jl lbl_SParam
// 	__asm push 1
// 	__asm jmp lbl_PSTMSG
// 
// lbl_SParam :
// 	__asm push 0
// 
// lbl_PSTMSG :
// 	__asm push WM_SWITCH_SUBMENU
// 	__asm push hwSoftMenu
// 	__asm call dword ptr[PostMessageA]
// 	__asm pop eax
// 	__asm xor eax, eax
// 	__asm retn 0x04
// 
// 	   lbl_Retn:
// 	__asm pop eax
// 	__asm retn 0x04
	__asm retn
}
#endif

//008C4B55 挂钩函数 (第五章 测试状态栏 实现函数)
#if CF_FNHK_008C4B55


void WINAPI UpdateTextStruct(PBAS_STR lpBasStr, int nChan)
{
	LPCSTR lpCmd;
	int nLen, nDiff;
	double dblPwr;
	char szTmp[16];

	if (lpBasStr == NULL || lpBasStr->lpszText == NULL) 
		return;

	if (lpBasStr->dwStringLen == 0 || lpBasStr->dwBufferMaxLen == 0) 
		return;

	switch (nChan)
	{
	case 0:
		lpCmd = "SOURce1:POWer:LEVel:IMMediate:AMPLitude";
		break;

	case 1:
		lpCmd = "SOURce2:POWer:LEVel:IMMediate:AMPLitude";
		break;

	case 2:
		lpCmd = "SOURce3:POWer:LEVel:IMMediate:AMPLitude";
		break;

	case 3:
		lpCmd = "SOURce4:POWer:LEVel:IMMediate:AMPLitude";
		break;

	default:
		return;
	}

	if (GetCommandVariant_Dbl(lpCmd, (void *)0x00A048B4, (void *)0x00A048BC, NULL, &dblPwr) < 0)
		dblPwr = -1.0f;

	sprintf_s(szTmp, 16, "  %.2lf dBm", dblPwr);

	nLen = strlen(szTmp);
	nDiff = lpBasStr->dwBufferMaxLen - lpBasStr->dwStringLen - 1;

	if (nDiff >= nLen)
	{
		strncat_s(lpBasStr->lpszText, lpBasStr->dwBufferMaxLen, szTmp, nLen);
		lpBasStr->dwStringLen = strlen(lpBasStr->lpszText);
	}
}

typedef void *(__thiscall *func_004B91C0)(void *lpThis, void *lpVar1, PBAS_STR lpBasStr);
func_004B91C0 fn004B91C0 = (func_004B91C0)0x004B91C0;

//状态信息栏相关
NAKED void * fnhk_008C4B55()
{
	__asm mov eax, dword ptr[esp + 0x08]
	__asm push ecx  //backup this
	__asm push dword ptr[esi + 0x24]
	__asm push eax
	__asm call UpdateTextStruct
	__asm pop ecx
	__asm jmp dword ptr[fn004B91C0]
}
#endif

//重新设置主窗口标题
#if CF_SET_TITLE
static LPWSTR priv_Title = L"TD3619D";
static int nOrgAddr_CWnd_SetWindowTextW = NULL;

NAKED int fnhk_JmpSetTitle()
{
	__asm mov eax, priv_Title
	__asm mov dword ptr[esp + 0x04], eax
	__asm jmp dword ptr[nOrgAddr_CWnd_SetWindowTextW]
}
#endif

//挂钩焦点 (保持E5062程序在激活窗口时,焦点始终在软菜单上)
#if CF_HOOKFOCUS
NAKED HWND fnhk_SetFocus()
{
	__asm push hwSoftItem
	__asm call dword ptr[SetFocus]
	__asm retn
}
#endif

//初始化指针挂钩
int InitHookPointers(PHOOK_PTR lpHookPtr)
{
	if (lpHookPtr == NULL)
		return 0;

	int nCount = 0;

	while (lpHookPtr->lppPtrAddr)
	{
		lpHookPtr->lpOrgAddr = *(lpHookPtr->lppPtrAddr);

		if (WriteMemory(lpHookPtr->lppPtrAddr, &(lpHookPtr->lpDestAddr), sizeof(void *)))
			nCount++;

		lpHookPtr++;
	}

	return nCount;
}

//重置指针挂钩
int ResetHookPointer(HOOK_PTR lpHookPtr)
{
	if (lpHookPtr.lppPtrAddr == NULL)
		return 0;

	if (WriteMemory(lpHookPtr.lppPtrAddr, &(lpHookPtr.lpOrgAddr), sizeof(void *)))
		return 1;

	return 0;
}

//恢复重置指针挂钩
int RestoreHookPointers(PHOOK_PTR lpHookPtr)
{
	if (lpHookPtr == NULL)
		return 0;

	int nCount = 0;

	while (lpHookPtr->lppPtrAddr)
	{
		lpHookPtr->lpOrgAddr = *(lpHookPtr->lppPtrAddr);

		if (WriteMemory(lpHookPtr->lppPtrAddr, &(lpHookPtr->lpOrgAddr), sizeof(void *)))
			nCount++;

		lpHookPtr++;
	}

	return nCount;
}

//初始化指令挂钩
BOOL InitHookInst(PHOOK_JMPPTR lpHookInst)
{
	if (lpHookInst == NULL)
		return FALSE;

	DWORD dwMax = (lpHookInst->dwSize > 16) ? 16 : lpHookInst->dwSize;
	BYTE btInst[8];

	memcpy_s(lpHookInst->btBackup, dwMax, (LPVOID)lpHookInst->lpInstAddr, dwMax);

	btInst[0] = 0xFF;
	btInst[1] = 0x25;

	*(DWORD *)(&btInst[2]) = (DWORD)&lpHookInst->dwAddress;

	return WriteMemory((LPVOID)lpHookInst->lpInstAddr, btInst, 6);
}

//恢复指令挂钩
BOOL RestoreHookInst(PHOOK_JMPPTR lpHookInst)
{
	if (lpHookInst == NULL)
		return FALSE;

	DWORD dwMax = (lpHookInst->dwSize > 16) ? 16 : lpHookInst->dwSize;

	return WriteMemory((LPVOID)lpHookInst->lpInstAddr, lpHookInst->btBackup, dwMax);
}

//设置偏移挂钩
BOOL SetOffsetHook(int *lpOffset, int *lpOldAddress, int nAddress)
{
	if (lpOffset == NULL || lpOldAddress == NULL)
		return FALSE;

	int nNext = (int)lpOffset + sizeof(int), nTmp;

	*lpOldAddress = nNext + *lpOffset;
	nTmp = nAddress - nNext;

	return WriteMemory(lpOffset, &nTmp, sizeof(int));
}

//设置指针
BOOL SetPointer(int *lpOffset, int *lpOldPointer, int nPointer)
{
	if (lpOffset == NULL)
		return FALSE;

	if (lpOldPointer)
		*lpOldPointer = *lpOffset;

	return WriteMemory(lpOffset, &nPointer, sizeof(int));
}


//DllMain 进程附加
BOOL APIENTRY DM_ProcessAttach(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	int nTmp;

	hMod = hModule;
	hMainMod = GetModuleHandle(NULL);
	dwBaseAdd = (DWORD)hMainMod;
	hjpOnSize.lpInstAddr += (DWORD)dwBaseAdd;

	HookPtr[0].lppPtrAddr = (void**)((DWORD)(HookPtr[0].lppPtrAddr) + dwBaseAdd);
	HookPtr[0].lpDestAddr = &ef_CWnd__Create;

	if (!InitHookInst(&hjpOnSize))
		return FALSE;

	InitCommonControls();

	//注册SoftMenu窗口类
	if (wcSoftMenu == 0)
	{
		WNDCLASSEX wcex;

		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc = ::DefWindowProc;
		wcex.hInstance = hMod;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_INACTIVEBORDER);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _T("WndCls_SoftMenu_X1");
		wcex.hIconSm = NULL;

		wcSoftMenu = RegisterClassEx(&wcex);

		if (wcSoftMenu == 0)
			return FALSE;
	}
	
	//注册SoftItem窗口类
	if (wcSoftItem == 0)
	{
		WNDCLASSEX wcex;

		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc = ::DefWindowProc;
		wcex.hInstance = hMod;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = CreateSolidBrush(RGB(40, 68, 101));
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _T("WndCls_SoftItem_X1");
		wcex.hIconSm = NULL;

		wcSoftItem = RegisterClassEx(&wcex);

		if (wcSoftItem == 0)
			return FALSE;
	}

	//注册ToolBar窗口类
	if (wcToolBar == 0)
	{
		WNDCLASSEX wcex;
	
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);
	
		wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc = &wpfn_ToolBar;
		wcex.hInstance = hMod;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _T("WndCls_ToolBar_X1");
		wcex.hIconSm = NULL;
	
		wcToolBar = RegisterClassEx(&wcex);
	
		if (wcToolBar == 0)
			return FALSE;
	}

	nLangId = GetPrivateProfileIntW(L"System", L"LangId", 1, L"NACore.ini");
	const WCHAR *lpInfFile;
	lpInfFile = L"C:\\ProgramData\\Agilent\\E5070\\e5070.ini";
	nTraces = GetPrivateProfileIntW(L"INSTR", L"TRACE", 0, lpInfFile);
	nChannels = GetPrivateProfileIntW(L"INSTR", L"CHANNEL", 0, lpInfFile);

	//此处初始化资源句柄
	hBmp_Button1 = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_Button1s = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_1S), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_Button2s = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_2S), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_Button2 = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_ButtonR = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_R), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_ButtonU = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_U), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_ButtonF = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_BTN_F), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_Checked = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_CHK), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_Unchecked = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_UNCHK), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBmp_Enter = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BMP_ENTER), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	InitHookPointers(HookPtr);  //CreateWidnows


	//输入框跳过
#if CF_FNHK_PASS_004A8FA0
	{
		int nOffset = (int)&fnhk_x1463D0 - (BASE + 0x1463D0);
		BYTE btTmp[8];

		btTmp[0] = 0xE9;
		*(int *)&btTmp[1] = nOffset;
		*(WORD *)&btTmp[6] = 0xF9EB;

		WriteMemory((void *)(BASE + 0x1463CB), btTmp, 5);
		wBakw_004A8FA0 = *(WORD *)(BASE + 0x1463D0);
		WriteMemory((void *)(BASE + 0x1463D0), &btTmp[6], 2);
	}
#endif

	//文本输入框跳过
#if CF_FNHK_PASS_004A90A0
	{
		BYTE btTmp[3] = { 0xC2, 0x04, 0x00 };
		WriteMemory((void *)(BASE + 0x13D550), btTmp, 3);
	}
#endif


	//009061C7 挂钩函数 (第四章 曲线信息栏 实现函数)
#if CF_FNHK_00906467
	SetOffsetHook((int *)(BASE + 0x9F7BF5), &nTmp, (int)&fnhk_00906467);
#endif


	//008C4B55 挂钩函数 (第五章 测试状态栏 实现函数)
#if CF_FNHK_008C4B55 
	SetOffsetHook((int *)0x008C4B56, &nTmp, (int)&fnhk_008C4B55);
#endif


	//修改窗口标题
#if CF_SET_TITLE 
	SetOffsetHook((int *)(BASE + 0x26AFD), &nOrgAddr_CWnd_SetWindowTextW, (int)&fnhk_JmpSetTitle);
#endif


	//设置事件处理器 (虚拟键码处理函数) (第七章 用于挂钩前面板事件及主菜单事件)
#if CF_EVENTHANDLE
	extern void *lpOrgJmpTabPtr_09;
	int WINAPI __fnhk_Event_09();

	lpOrgJmpTabPtr_09 = *(void **)(BASE + 0x149ED4);
	nTmp = (int)&__fnhk_Event_09;
	WriteMemory((void *)(BASE + 0x149ED4), &nTmp, 4);
#endif

	//挂钩焦点 (保持程序在激活窗口时,焦点始终在软菜单上)
#if CF_HOOKFOCUS
	SetOffsetHook((int *)(BASE + 0x96DCDA), &nTmp, (int)&fnhk_SetFocus);
#endif

	InitLocaleHook();  

	return TRUE;
}


//从配置文件里读取TDR开启状态
BOOL WndCHK_TDR()
{
	const WCHAR *lpInfFile;
	BOOL uVal;

	lpInfFile = L"C:\\ProgramData\\Agilent\\E5070\\e5070.ini";

	uVal = GetPrivateProfileIntW(L"INSTR", L"TDR Mode", 0, lpInfFile);

	return uVal;
}


void TDRCHK()
{
	static BOOL blTDRCHK = FALSE;
	DWORD dwTempAdd = NULL;

	__asm mov dwTempAdd, eax;

	if (dwTempAdd == dwTDRDataAdd)
	{
		wWidth_SoftMenu = wBackupWidth;
		int lngWidth = (wWidth_SoftMenu - 0.5) / 1.25;
		SetSoftMenuWidth(lngWidth);
		ShowWindow(hwSoftMenu, SW_SHOW);
		SoftItem_SetFocus(0, 0);
	}
	SizeMainWnd(FALSE);

	return;
}

//在代码里插入检测TDR关闭状态
NAKED void fnhk_TDRCHK()
{
	__asm
	{
		pushad
		call TDRCHK
		popad
		mov byte ptr ds : [eax + 0x1C], bl
		push eax
		mov eax, 0x0096E1F9
		add eax, dwBaseAdd
		jmp eax
	}
}


void wndTDRCHK()
{
	BOOL blTDR = 0;
	DWORD *bMenu = 0;

	blTDR = WndCHK_TDR();

	if (blTDR)
	{
		//关闭原菜单;
		void *lpVar = (void *)(BASE + 0x35B7918);
		lpVar = GetOffsetPointer(lpVar, 0x04);
		lpVar = GetOffsetPointer(lpVar, 0x04);
		lpVar = GetOffsetPointer(lpVar, 0x04);
		lpVar = GetOffsetPointer(lpVar, 0x08);
		lpVar = GetOffsetPointer(lpVar, 0x30);
		lpVar = GetOffsetPointer(lpVar, 0x24);//+24 TDR数据
		bMenu = (DWORD *)((int)lpVar + 0x1C);
		*bMenu = 0;

		dwTDRDataAdd = (DWORD)lpVar;

		//关闭新菜单;
		wBackupWidth = wWidth_SoftMenu;
		wWidth_SoftMenu = 0;
		SetSoftMenuWidth(wWidth_SoftMenu);
		ShowWindow(hwSoftMenu, SW_HIDE);

		//hook住关闭窗口变量处,以达到实时获取TDR关闭信息
		int nTmp = 0;
		DWORD wCode = 0xE9E9E9E9;

		WriteMemory((void *)(0x0096E1A8 + BASE), &wCode, 1);
		SetOffsetHook((int *)(0x0096E1A9 + BASE), &nTmp, (int)&fnhk_TDRCHK);

		wCode = 0x1458AFEB;
		WriteMemory((void *)(0x0096E1F7 + BASE), &wCode, 3);
		//在 BASE+0x96E1F7 执行hook操作，检测到关闭后再开启新UI；
	}
}


//获取各个屏幕信息参数1为需要获取的屏幕序号
bool GetScreenRect(int ScreenNo, RECT *rect)
{
	pEnumDiaplayDevices xenum=nullptr;

	DISPLAY_DEVICE hDisplayDevice;
	ZeroMemory(&hDisplayDevice, sizeof(hDisplayDevice));

	hDisplayDevice.cb = sizeof(hDisplayDevice);

	HMODULE hModule = LoadLibraryW(L"user32.dll");
	if (hModule) 	
		xenum = (pEnumDiaplayDevices)GetProcAddress(hModule, "EnumDisplayDevicesW");

	if (!xenum) 
	{
		FreeLibrary(hModule);
		return false;
	}

	BOOL flag = xenum(NULL, ScreenNo, &hDisplayDevice, 0);

	if (!flag)
	{
		FreeLibrary(hModule);
		return false;
	}
	
	DEVMODE DeviceMode;
	ZeroMemory(&DeviceMode, sizeof(DeviceMode));
	DeviceMode.dmSize = sizeof(DeviceMode);
	flag = EnumDisplaySettings(hDisplayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &DeviceMode);
	rect->left = DeviceMode.dmPosition.x;
	rect->top = DeviceMode.dmPosition.y;
	rect->right = DeviceMode.dmPelsWidth;
	rect->bottom = DeviceMode.dmPelsHeight;

	FreeLibrary(hModule);
	return true;
}
