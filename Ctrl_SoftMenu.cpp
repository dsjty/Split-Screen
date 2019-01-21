#include "stdafx.h"
#include <vector>

//原区域静态值，为了双开切成全局试试
short TagPageOrd = -1;
BOOL blTME = TRUE;

DWORD *lpdwMenuWidth = NULL;

CRect crWnd1Rect = { 0 }, crWnd2Rect = { 0 };
int px_begin = 0;

BOOL blCapture = FALSE;
static BOOL blMove = FALSE;
SOFT_MENU lpSoftMenu = { 0 };
SOFT_TAG_PAGE lpTagPage = { 0 };
std::vector<MONITORINFOEX> m_vec_Monitor;

//菜单区域的上下箭头rect
RECT rcItemUp, rcItemDown, rcMenuUp, rcMenuDown;

//菜单当前index
DWORD dwTagPageIndex = 0;

//获取软件宽度值开关;
BOOL blWidth = FALSE;

LRESULT CALLBACK cwrphk_MainWnd(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK cwphk_MainWnd(int nCode, WPARAM wParam, LPARAM lParam);
void SetSoftMenuWidth(WORD wWidth);
void UpdateToolbarHeight();

int SetWindowsPoint(HWND hWnd);

BOOL CALLBACK AddMonitorsCallBack(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{

	MONITORINFOEX mi;
	{
		mi.cbSize = sizeof(mi);
		::GetMonitorInfo(hMonitor, &mi);
	}

	int nIndex = m_vec_Monitor.size();
	m_vec_Monitor.push_back(mi);
	return TRUE;
}

int SetWindowsPoint(HWND hWnd)
{
	UINT uiMainSceenWidth = 0, uiMainSceenHeight = 0, uiMajorSceenWidth = 0, uiMajorSceenHeight = 0;
	UINT uiWidth = 0, uiHeight = 0;

	ShowWindow(hWnd, SW_RESTORE);
	//获取分屏数据
	EnumDisplayMonitors(NULL, NULL, AddMonitorsCallBack, 0);
	if (!m_vec_Monitor.size())
		return 0;

	if (m_vec_Monitor.at(0).rcMonitor.right)
	{
		crWnd1Rect = m_vec_Monitor.at(0).rcWork;
		RECT rcMain = m_vec_Monitor.at(0).rcWork;
		uiMainSceenWidth = rcMain.right - rcMain.left;
		uiMainSceenHeight = rcMain.bottom - rcMain.top;

		if (m_vec_Monitor.at(1).rcMonitor.right)
		{
			crWnd2Rect = m_vec_Monitor.at(1).rcWork;
			RECT rcPrim = m_vec_Monitor.at(1).rcWork;
			uiWidth = rcPrim.right - WIDTH_SOFTMENU * 2;
			uiMajorSceenHeight = rcPrim.bottom - rcPrim.top;

			if (m_vec_Monitor.at(1).dwFlags == MONITORINFOF_PRIMARY)
				uiHeight = uiMajorSceenHeight;
		}
		else
			uiWidth = uiMainSceenWidth + uiMajorSceenWidth - WIDTH_SOFTMENU * 2;

		if (m_vec_Monitor.at(0).dwFlags == MONITORINFOF_PRIMARY)
			uiHeight = uiMainSceenHeight;
	}

	SetWindowPos(hwMainWnd, 0, WIDTH_SOFTMENU, 0, uiWidth, uiHeight, SWP_SHOWWINDOW | SWP_NOZORDER);

	crWnd1Rect.left += WIDTH_SOFTMENU + 10;
	crWnd2Rect.right -= WIDTH_SOFTMENU + 10;

	return uiWidth;
}

void UpdateWidthPointer()
{
	void *lpVar = (void *)(BASE + 0x35B7918);

	lpVar = GetOffsetPointer(lpVar, 0x04);
	if (!lpVar)
		return;

	lpVar = GetOffsetPointer(lpVar, 0x04);
	if (!lpVar)
		return;

	lpVar = GetOffsetPointer(lpVar, 0x04);
	if (!lpVar)
		return;

	lpVar = GetOffsetPointer(lpVar, 0x08);
	if (!lpVar)
		return;

	lpVar = GetOffsetPointer(lpVar, 0x30);
	if (!lpVar)
		return;

	lpVar = GetOffsetPointer(lpVar, 0x14);
	if (!lpVar)
		return;

	lpdwMenuWidth = (DWORD *)((int)lpVar + 0x24);
}

#if CF_FNHK_MOUSEEVENT
DWORD nBackAddr = 0;
DWORD wBake_eax = 0;
DWORD *dwTemp;//因为只需要hook在某一个消息段内，需要本地址取值做判断;

NAKED int fnhk_Ba12FCB8(int nValue, POINT pt)
{
	__asm push eax

	dwTemp = (DWORD*)(BASE + 0x162DFB4);
	__asm mov eax, [dwTemp]
	__asm mov eax, [eax]
	__asm cmp eax, 0x1
	__asm je lbl_RetnAddr

	nBackAddr = BASE + 0x12FCE3;
	__asm pop eax
	__asm push ebp
	__asm mov ebp, esp
	__asm jmp dword ptr nBackAddr

	lbl_RetnAddr :
	 __asm call UpdateCurrentItemsAndData

	 nBackAddr = BASE + 0x12FCE3;
	 __asm pop eax
	 __asm push ebp
	 __asm mov ebp, esp
	 __asm jmp dword ptr nBackAddr
}

#endif

//Hook 后的软菜单创建函数
BOOL WINAPI _CWnd__Create(CWnd *lpThis, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	blWidth = TRUE;

	BOOL blRet = TRUE;
	CRect crect = { 0,0,wWidth_SoftMenu - WIDTH_SUBMENU,980 };
	CRect crect2 = crect;

	EnumDisplayMonitors(NULL, NULL, AddMonitorsCallBack, 0);

	{
		UINT uiMainSceenWidth = 0, uiMainSceenHeight = 0, uiMajorSceenWidth = 0, uiMajorSceenHeight = 0;
		UINT uiWidth = 0, uiHeight = 0;
		if(m_vec_Monitor.size())
		{
			if (m_vec_Monitor.at(0).rcWork.right)
			{
				RECT rcMain = m_vec_Monitor.at(0).rcWork;
				uiMainSceenWidth = rcMain.right - rcMain.left;
				uiMainSceenHeight = rcMain.bottom - rcMain.top;

				if (m_vec_Monitor.at(1).rcWork.right)
				{
					RECT rcPrim = m_vec_Monitor.at(1).rcWork;
					uiMajorSceenWidth = rcPrim.right - rcPrim.left;
					uiMajorSceenHeight = rcPrim.bottom - rcPrim.top;

					if (m_vec_Monitor.at(1).dwFlags == MONITORINFOF_PRIMARY)
						uiHeight = uiMajorSceenHeight;
				}
				if (m_vec_Monitor.at(0).dwFlags == MONITORINFOF_PRIMARY)
					uiHeight = uiMainSceenHeight;
			}
			uiWidth = uiMainSceenWidth + uiMajorSceenWidth - WIDTH_SOFTMENU * 2;
			crect.bottom = wHeight_MainWnd = uiHeight;
			crect2.bottom = uiHeight;
			crect2.left = uiWidth;
		}
	}

	ResetHookPointer(HookPtr[0]);

	cwMainWnd = pParentWnd;
	hwMainWnd = pParentWnd->m_hWnd;

#if CF_NEWMENU
	if (hhkcwp_MainWnd == NULL)
		hhkcwp_MainWnd = SetWindowsHookEx(WH_CALLWNDPROC, &cwphk_MainWnd, hMod, GetCurrentThreadId());
	
	if (hhkcwrp_MainWnd == NULL)
		hhkcwrp_MainWnd = SetWindowsHookEx(WH_CALLWNDPROCRET, &cwrphk_MainWnd, hMod, GetCurrentThreadId());

	cwMenuWnd = new TDMenu(1);
	cwMenuWnd2 = new TDMenu(2);

	cwMenuWnd->CreateEx(WS_EX_ACCEPTFILES | WS_EX_TOOLWINDOW, (LPCTSTR)wcSoftMenu, "MENU 1", WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN, crect, pParentWnd, NULL, NULL);
	hwSoftMenu = cwMenuWnd->m_hWnd;

	cwMenuWnd2->CreateEx(WS_EX_ACCEPTFILES | WS_EX_TOOLWINDOW, (LPCTSTR)wcSoftMenu, "MENU 2", WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN, crect2, pParentWnd, NULL, NULL);
	hwSoftMenu2 = cwMenuWnd2->m_hWnd;

#endif

#if CF_MYTOOLBAR
	Toolbar_Create(hwMainWnd);
#endif

#if CF_HIDEMENU
	SetMenu(hwMainWnd, NULL);
#endif

#if CF_PHYSEVENT
	PhysEventHook();
#endif

#if CF_FNHK_MOUSEEVENT
	{
		int nTmp;

		nTmp = 0xE9;
		WriteMemory((void *)(BASE + 0x12FCB8), &nTmp, 1);
		SetOffsetHook((int *)(BASE + 0x12FCB9), &nTmp, (int)&fnhk_Ba12FCB8);

		nTmp = 0xD6EB;
		WriteMemory((void *)(BASE + 0x12FCE0), &nTmp, 2);
	}
#endif
	return blRet;
}

void SizeMainWnd(BOOL blSync)
{
	SetWindowsPoint(cwMainWnd->GetSafeHwnd());
}


/*设置软菜单高度
替换原程序中的软菜单宽度
*/
void SetSoftMenuWidth(WORD wWidth)
{
	if (!lpdwMenuWidth)
	{
		UpdateWidthPointer();

		if (lpdwMenuWidth)
			*lpdwMenuWidth = 0; //wWidth;
	}
	else
	{
		*lpdwMenuWidth = 0; //wWidth;
	}
}

/*设置工具栏高度
替换原程序中的上方输入框高度
*/
void SetToolbarHeight(WORD wHeight)
{
 	if (!lpdwTopHeight)
 	{
 		UpdateToolbarHeight();
 
 		if (lpdwTopHeight)
 		{
 			*lpdwTopHeight = wHeight;
 		}
 	}
 	else
 	{
 		*lpdwTopHeight = wHeight;
 	}
}

void UpdateSize_UI()
{
	UINT uiWidth = 0, uiHeight = 0;

	if (!blWidth)
		return;

	LONG lngWidth = 0, lngHeight = 0, lngToolHeight = 0;

	RECT rect2;
	cwMainWnd->GetClientRect(&rect2);
	wWidth_MainWnd = rect2.right - rect2.left;
	lngHeight = rect2.bottom - rect2.top;

	wHeight_SoftMenu = lngHeight - HEIGHT_SOFTMENU;

	{
		UINT uiMainSceenWidth = 0, uiMainSceenHeight = 0, uiMajorSceenWidth = 0, uiMajorSceenHeight = 0;

		if (m_vec_Monitor.at(0).rcMonitor.right)
		{
			RECT rcMain = m_vec_Monitor.at(0).rcWork;
			uiMainSceenWidth = rcMain.right - rcMain.left;
			uiMainSceenHeight = rcMain.bottom - rcMain.top;

			if (m_vec_Monitor.at(1).rcMonitor.right)
			{
				RECT rcPrim = m_vec_Monitor.at(1).rcWork;
				uiWidth = rcPrim.right - WIDTH_SOFTMENU * 2;
				uiMajorSceenHeight = rcPrim.bottom - rcPrim.top;

				if (m_vec_Monitor.at(1).dwFlags == MONITORINFOF_PRIMARY)
					uiHeight = uiMajorSceenHeight;
			}
			else
				uiWidth = uiMainSceenWidth + uiMajorSceenWidth - WIDTH_SOFTMENU * 2;

			if (m_vec_Monitor.at(0).dwFlags == MONITORINFOF_PRIMARY)
				uiHeight = uiMainSceenHeight;
		}
	}

	if (!lpdwMenuWidth)
	{
		UpdateWidthPointer();

		if (lpdwMenuWidth)
		{
			lngWidth = (wWidth_SoftMenu - 0.5) / 1.25;
			*lpdwMenuWidth = 0; //lngWidth;
		}
	}
	else
	{		lngWidth = (wWidth_SoftMenu - 0.5) / 1.25;

		*lpdwMenuWidth = 0; //lngWidth;
	}


	if (IsWindowVisible(hwSoftMenu))
		SetWindowPos(hwSoftMenu, NULL, 0, 0, WIDTH_SOFTMENU, uiHeight, SWP_NOZORDER);
	if (IsWindowVisible(hwSoftMenu2))
		SetWindowPos(hwSoftMenu2, NULL, uiWidth + WIDTH_SOFTMENU, 0, WIDTH_SOFTMENU, uiHeight, SWP_NOZORDER);

	RedrawWindow(hwMainWnd, NULL, NULL, 0);

	Toolbar_UpdateItemsPos();
}

/*
标签页,动态添加一个条目
@lpTagPage 要添加条目的标签页
@lpSubItem  要添加的条目
*/
DWORD TagPage_AddItem(PSOFT_TAG_PAGE lpTagPage, PSOFT_SUB_ITEM lpSubItem)
{
	if (lpTagPage == NULL) 
		return INVALID_INDEX;

	if (CHK_NOFLAGS(lpTagPage->dwFlags, TPF_DYNAMIC)) 
		return INVALID_INDEX;

	DWORD dwRet;

	if (lpTagPage->dwNumOfSubItems == 0 || lpTagPage->lpSubItem == NULL)
	{
		if (lpTagPage->lpSubItem) free(lpTagPage->lpSubItem);

		lpTagPage->lpSubItem = (PSOFT_SUB_ITEM)malloc(sizeof(SOFT_SUB_ITEM));

		lpTagPage->dwNumOfSubItems = 1;

		if (lpSubItem)
			memcpy_s(lpTagPage->lpSubItem, sizeof(SOFT_SUB_ITEM), lpSubItem, sizeof(SOFT_SUB_ITEM));
		else
			memset(lpTagPage->lpSubItem, 0, sizeof(SOFT_SUB_ITEM));

		dwRet = 0;
	}
	else
	{
		dwRet = lpTagPage->dwNumOfSubItems;

		lpTagPage->lpSubItem = (PSOFT_SUB_ITEM)realloc(lpTagPage->lpSubItem, sizeof(SOFT_SUB_ITEM) * (dwRet + 1));

		if (lpTagPage->lpSubItem == NULL)
		{
			lpTagPage->dwNumOfSubItems = 0;
			return INVALID_INDEX;
		}

		lpTagPage->dwNumOfSubItems++;

		if (lpSubItem)
			memcpy_s(&(lpTagPage->lpSubItem[dwRet]), sizeof(SOFT_SUB_ITEM), lpSubItem, sizeof(SOFT_SUB_ITEM));
		else
			memset(&(lpTagPage->lpSubItem[dwRet]), 0, sizeof(SOFT_SUB_ITEM));
	}

	return dwRet;
}

/*
标签页,释放动态创建的条目
*/
DWORD TagPage_FreeItem(PSOFT_TAG_PAGE lpTagPage)
{
	if (lpTagPage == NULL) 
		return 0;

	if (CHK_NOFLAGS(lpTagPage->dwFlags, TPF_DYNAMIC)) 
		return 0;

	if (lpTagPage->lpSubItem == NULL) 
		return 0;

	DWORD dwRet = lpTagPage->dwNumOfSubItems;

	for (DWORD dwIndex = 0; dwIndex < dwRet; dwIndex++)
	{
		if (lpTagPage->lpSubItem[dwIndex].szItemText)
		{
			free(lpTagPage->lpSubItem[dwIndex].szItemText);
			lpTagPage->lpSubItem[dwIndex].szItemText = NULL;
		}
	}

	free(lpTagPage->lpSubItem);

	lpTagPage->lpSubItem = NULL;
	lpTagPage->dwNumOfSubItems = 0;

	return dwRet;
}


void UpdateSoftMenu()
{
	InvalidateRect(cwMainWnd->m_hWnd, NULL, TRUE);
	UpdateWindow(cwMainWnd->m_hWnd);
}



