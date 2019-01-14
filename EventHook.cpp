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

extern WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_SoftMenu;
extern WORD wBackupWidth;

void *lpOrgJmpTabPtr_09 = NULL;
bool bPreset = FALSE;

void SetSoftMenuWidth(WORD wWidth);

typedef int(__stdcall *dwfn_00BC3028)(WPARAM wParam, LPARAM lParam);

dwfn_00BC3028 fn00BC3028 = NULL;


void SetInputType(int nNewType)
{
	nInputType = nNewType;
}

void SetInputItem(PSOFT_SUB_ITEM lpSubItem)
{
	lpInputItem = lpSubItem;
}


int WINAPI PhysEventHandler_Button(WPARAM wParam, LPARAM lParam)
{
	int nRet = 1;

	switch (lParam)
	{
	case 0x0D:
	{
		if (nInputType == ITID_GMK || nInputType == ITID_PW_GMK)
		{
			PSTMSG(hwMainWnd, 0x0432, 0xB, MAKELPARAM(0x0035, 0x0001));
		}
		else if (nInputType == ITID_NUM)
		{
			PSTMSG(hwMainWnd, 0x0432, 0xB, MAKELPARAM(0x0038, 0x0001)); 
		}
		else
		{
			if (fn00BC3028)
				nRet = fn00BC3028(wParam, lParam);
			else
				nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
		}
	}
	break;

	case 0x1D:
	{
		if (nInputType == ITID_GMK || nInputType == ITID_PW_GMK)
		{
			PSTMSG(hwMainWnd, 0x0432, 0xB, MAKELPARAM(0x0036, 0x0001));
		}
		else if (nInputType == ITID_NUM)
		{
			PSTMSG(hwMainWnd, 0x0432, 0xB, MAKELPARAM(0x0039, 0x0001));
		}
		else
		{
			if (fn00BC3028)
				nRet = fn00BC3028(wParam, lParam);
			else
				nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
		}
	}
	break;

	case 0x2D:
	{
		if (nInputType == ITID_GMK || nInputType == ITID_PW_GMK)
			PSTMSG(hwMainWnd, 0x0432, 0xB, MAKELPARAM(0x0037, 0x0001));
		else if (nInputType == ITID_NUM)
			PSTMSG(hwMainWnd, 0x0432, 0xB, MAKELPARAM(0x003A, 0x0001));
		else
		{
			if (fn00BC3028)
				nRet = fn00BC3028(wParam, lParam);
			else
				nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
		}
	}
	break;

	default:
		if (fn00BC3028)
			nRet = fn00BC3028(wParam, lParam);
		else
			nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
		break;
	}

	return nRet;
}


//************************************
// 函数名:    PhysEventHandler_Entry
// Access:    public 
// 返回值类型:   int WINAPI
// 参数: WPARAM wParam
// 参数: LPARAM lParam
// 说明: 三个单位键的消息分发处理函数
//************************************
int WINAPI PhysEventHandler_Entry(WPARAM wParam, LPARAM lParam)
{
	int nRet = 1;
	HWND hwSoftItem;
	if (uiCurFocusMenu == 2)
		hwSoftItem = cwMenuWnd2->GetItemHwnd();
	else
		hwSoftItem = cwMenuWnd->GetItemHwnd();

	switch (wParam)
	{
	case 0x40:	
	case 0x24:
		nRet = PhysEventHandler_Button(wParam, lParam);
		break;

	case 0x42:	 //左旋三档
	case 0x43:	 //左旋三档
	case 0x44:	 //左旋三档
		switch (nInputType)
		{
		case ITID_GMK:
		case ITID_NUM:
			if (wParam == 0x42)
				PSTMSG(hwSoftItem, WM_FINETUNE, (WPARAM)-1, lParam);
			else
				PSTMSG(hwSoftItem, WM_FINETUNE, (WPARAM)-2, lParam);
			break;

		case ITID_PW_GMK:
			if (wParam == 0x42)
				PopWnd_Finetune(FALSE, -1, lParam);
			else
				PopWnd_Finetune(FALSE, -2, lParam);
			break;

		default:
			if (fn00BC3028)
				nRet = fn00BC3028(wParam, lParam);
			else
				nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
			break;
		}
		break;


	case 0x45:	//右旋三挡
	case 0x46:	//右旋三挡
	case 0x47:	//右旋三挡
		switch (nInputType)
		{
		case ITID_GMK:
		case ITID_NUM:
			if (wParam == 0x45)
				PSTMSG(hwSoftItem, WM_FINETUNE, (WPARAM)1, lParam);
			else
				PSTMSG(hwSoftItem, WM_FINETUNE, (WPARAM)2, lParam);
			break;

		case ITID_PW_GMK:
			if (wParam == 0x45)
				PopWnd_Finetune(FALSE, 1, lParam);
			else
				PopWnd_Finetune(FALSE, 2, lParam);

			break;

		default:
			if (fn00BC3028)
				nRet = fn00BC3028(wParam, lParam);
			else
				nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
			break;
		}
		break;

	default:
		if (fn00BC3028)
			nRet = fn00BC3028(wParam, lParam);
		else
			nRet = ((dwfn_00BC3028)(0x309EF0 + BASE))(wParam, lParam);
		break;
	}

	return nRet;
}

//************************************
// 函数名:    PhysEventHook
// Access:    public 
// 返回值类型:   int
// 说明: hook三个单位键消息处理函数
//************************************
int PhysEventHook()
{
	if (*(DWORD *)(0x3660FC0 + BASE) != (DWORD)&PhysEventHandler_Entry)
	{
		fn00BC3028 = (dwfn_00BC3028)*(DWORD *)(0x3660FC0 + BASE);
		*(DWORD *)(0x3660FC0 + BASE) = (DWORD)&PhysEventHandler_Entry;
		WriteMemory((void *)(0x30A3F1 + BASE), (void *)(0x3660FC0 + BASE), 4);

		return (int)fn00BC3028;
	}
	return 0;
}


//************************************
// 函数名:    EventHandler_09
// Access:    public 
// 返回值类型:   int WINAPI
// 参数: WPARAM * _wParam
// 参数: LPARAM * _lParam
// 说明: 前面板各个按键事件消息分发处理
//************************************

int WINAPI EventHandler_09(WPARAM *_wParam, LPARAM *_lParam)
{
	
	LPWORD lpVirtCode = (LPWORD)_lParam;
	int nRet = 1;
	TDMenu *temp;
	if (uiCurFocusMenu == 2)
		temp = cwMenuWnd2;
	else
		temp = cwMenuWnd;

	switch (LOWORD(*_lParam))
	{
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x05:
		PSTMSG(temp->m_hWnd, WM_REFRESH, 0, 0); 
		break;

	case 0x04:
		PSTMSG(temp->m_hWnd, WM_REFRESH, 0, 0);
		OrigSoftMenu_ItemClicked2(CA_TRIGGER, TA_TRIGGER, 3);
		OrigSoftMenu_ItemClicked2(CA_TRIGGER, TA_TRIGGER, 2);
		UpdateSoftMenu();
		break;

	case 0x06:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMeasurement);
		nRet = 0;
		break;

	case 0x07:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuTracesConfig);
		nRet = 0;
		break;

	case 0x08:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 2, (LPARAM)&menuMeasurement);
		nRet = 0;
		break;

	case 0x09:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuDisplay);
		nRet = 0;
		break;

	case 0x0A:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuAverage);
		nRet = 0;
		break;

	case 0x0B:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuCalibration);
		nRet = 0;
		break;

	case 0x0C:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuFrequency);
		nRet = 0;
		break;

	case 0x0D:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuPower);
		nRet = 0;
		break;

	case 0x0E:
		if (NULL == IsWindowVisible(temp->GetSafeHwnd()))
		{
			nRet = 0;
			break;
		}
		temp->SoftMenu_Pop();
		nRet = 0;
		break;

	case 0x0F:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuFrequency);
		nRet = 0;
		break;

	case 0x10:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuSweepSetup);
		nRet = 0;
		break;

	case 0x11:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuChannelsConfig);
		nRet = 0;
		break;

	case 0x24:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMarker);
		nRet = 0;
		break;

	case 0x26:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 5, (LPARAM)&menuMarker);
		nRet = 0;
		break;

	case 0x27:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuAnalysis);
		nRet = 0;
		break;

	case 0x22:
	case 0x28:
	case 0x29:
	case 0x2A:
	case 0x2B:
	case 0x2C:
	case 0x2D:
	case 0x2E:
	case 0x2F:
	case 0x30:
	case 0x31:
	case 0x19:
	case 0x1A:
	case 0x1B:
	case 0x1C:
	case 0x32:
	case 0x33:
	case 0x3A:
		if (NULL == IsWindowVisible(temp->GetSafeHwnd()))
		{
			nRet = 0;
			break;
		}
		break;

	case 0x3C:		//'隐藏/显示'菜单
	{
		if (IsWindowVisible(temp->GetSafeHwnd()))
		{
			wBackupWidth = wWidth_SoftMenu;
			wWidth_SoftMenu = 0;
			SetSoftMenuWidth(wWidth_SoftMenu);
			ShowWindow(temp->GetSafeHwnd(), SW_HIDE);
		}
		else
		{
			wWidth_SoftMenu = wBackupWidth;
			int lngWidth = (wWidth_SoftMenu - 0.5) / 1.25;
			SetSoftMenuWidth(lngWidth);
			ShowWindow(temp->GetSafeHwnd(), SW_SHOW);
		}

		SizeMainWnd(FALSE);

		nRet = 0;
	}
	break;

	case 0x3E:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuMacroSetup);
		nRet = 0;
		break;

	case 0x46:	//帮助
		if (NULL == IsWindowVisible(temp->GetSafeHwnd()))
		{
			nRet = 0;
			break;
		}
		keybd_event(VK_F1, 0, 0, 0);
		keybd_event(VK_F1, 0, KEYEVENTF_KEYUP, 0);
		nRet = 0;
		break;

	case 0x43:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuSaveRecall);
		nRet = 0;
		break;

	case 0x44:
		PSTMSG(temp->GetSafeHwnd(), WM_SWITCH_SUBMENU, 0, (LPARAM)&menuSystem);
		nRet = 0;
		break;

	case 0x45:
		if (bPreset==TRUE)
			break;
		bPreset = TRUE;
		ConfirmPreset();
		nRet = 0;
		break;
	}

return nRet;
}


//************************************
// 函数名:    __fnhk_Event_09
// Access:    public 
// 返回值类型:   NAKED int WINAPI
// 说明: hook前面板按键消息函数
//************************************
NAKED int WINAPI __fnhk_Event_09()
{
	__asm pushad
	__asm lea eax, dword ptr[ebp + 0x0C]
	__asm push eax
	__asm lea eax, dword ptr[ebp + 0x08]
	__asm push eax
	__asm call EventHandler_09
	__asm test eax, eax
	__asm popad
	__asm je lbl_Default
	__asm jmp dword ptr[lpOrgJmpTabPtr_09]

	lbl_Default:
		__asm mov ecx, dword ptr[ebp - 0x0C]
		__asm pop edi
		__asm pop esi
		__asm xor eax, eax
		__asm mov dword ptr fs : [0], ecx
		__asm pop ebx
		__asm mov esp, ebp
		__asm pop ebp
		__asm retn 0x08
}