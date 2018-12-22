#include "stdafx.h"

#define WIDTH_SOFTMENU_MIN          208				//这里取值必须满足(N-0.5)/1.25为整数...因为懒得在程序里做判断纠错...
#define WIDTH_SOFTMENU_MAX          240
#define WIDTH_SOFTMENU              WIDTH_SOFTMENU_MIN

#define WIDTH_SUBMENU               90

#define HEIGHT_DIFF_SOFTMENU        18

extern WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_Toolbar;
extern HHOOK hhkcwrp_MainWnd, hhkcwp_MainWnd;
extern HWND hwToolbar;
extern DWORD dwTopHeight;
extern DWORD *lpdwTopHeight;

static DWORD *lpdwMenuWidth = NULL;
static BOOL sStartRef = FALSE;			//用于第一次启动时刷新界面操作;

//SoftMenu Width
WORD wWidth_SoftMenu = WIDTH_SOFTMENU;
WORD wHeight_SoftMenu = 0;

static int px_begin = 0;

static BOOL blCapture = FALSE;
static BOOL blMove = FALSE;

//菜单区域的上下箭头rect
static RECT rcItemUp, rcItemDown, rcMenuUp, rcMenuDown;

static RECT rcMenuButton, rcRetButton;

//菜单区域的上下箭头的箭头状态
static BOOL blMenuUp = FALSE, blMenuDown = FALSE, blItemUp = FALSE, blItemDown = FALSE;

//自绘控件的状态 State
static int nState = 0, nLastState = 0;
static int nClickState = 0, nLastClickState = 0;
//static WNDPROC wp_OrgDrawProc = NULL;

static DWORD dwLastTick = 0;

//菜单当前index
DWORD dwTagPageIndex = 0;

//获取软件宽度值开关;
static BOOL blWidth = FALSE;

void DSM_Title(HWND hWnd, HDC hDC, const LPPAINTSTRUCT lpps);
void DSM_TagPage(HWND hWnd, HDC hDC, const LPPAINTSTRUCT lpps);

LRESULT CALLBACK cwrphk_MainWnd(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK cwphk_MainWnd(int nCode, WPARAM wParam, LPARAM lParam);
void SetSoftMenuWidth(WORD wWidth);
void UpdateToolbarHeight();
int PhysEventHook();

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

	ResetHookPointer(HookPtr[0]);

	cwMainWnd = pParentWnd;
	hwMainWnd = pParentWnd->m_hWnd;


#if CF_NEWMENU
	if (hhkcwp_MainWnd == NULL)
		hhkcwp_MainWnd = SetWindowsHookEx(WH_CALLWNDPROC, &cwphk_MainWnd, hMod, GetCurrentThreadId());
	
	if (hhkcwrp_MainWnd == NULL)
		hhkcwrp_MainWnd = SetWindowsHookEx(WH_CALLWNDPROCRET, &cwrphk_MainWnd, hMod, GetCurrentThreadId());

	hwSoftMenu = CreateWindowEx(WS_EX_STATICEDGE, (LPCTSTR)wcSoftMenu, "MENU 1", WS_POPUP | WS_CAPTION | WS_VISIBLE | WS_CLIPCHILDREN, (int)0, 0, (int)wWidth_SoftMenu, (int)wHeight_SoftMenu, pParentWnd->m_hWnd, NULL, hMod, NULL);
	
	hwSoftMenu2 = CreateWindowEx(WS_EX_STATICEDGE, (LPCTSTR)wcSoftMenu, "MENU 2", WS_POPUP | WS_CAPTION | WS_VISIBLE | WS_CLIPCHILDREN, (int)wWidth_SoftMenu, 0, (int)wWidth_SoftMenu, (int)wHeight_SoftMenu, pParentWnd->m_hWnd, NULL, hMod, NULL);
	
	if (hwSoftMenu)
	{
		SizeMainWnd(FALSE);
		//SetFocus(hwSoftMenu);
		//SetFocus(hwSoftMenu2);
	}
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

void SoftMenu_Reset()
{
	PSOFT_MENU lpSoftMenu = &menuRoot;

	if (lpMenuStack[btMenuIndex])
	{
		PSOFT_MENU lpCurSoftMenu = lpMenuStack[btMenuIndex];

		if (CHK_FLAGS(lpCurSoftMenu->dwFlags, SMF_FN_LEAVE) && (lpCurSoftMenu->fnLeave))
			lpCurSoftMenu->fnLeave(0, 0, 0, lpCurSoftMenu);
	}

	lpMenuStack[0] = lpSoftMenu;
	btMenuIndex = 0;

	if (CHK_FLAGS(lpSoftMenu->dwFlags, SMF_FN_ENTER) && (lpSoftMenu->fnEnter))
		lpSoftMenu->fnEnter(0, 0, 0, lpSoftMenu);

	dwTagPageIndex = 0;
	TagPage_RefreshItems(&lpSoftMenu->lpTagPage[0]);
	SoftItem_SetFocus(0, 0);

	UpdateSoftMenu();
	return;
}

//************************************
// 函数名:    SoftMenu_Push
// Access:    public 
// 返回值类型:   void
// 参数: PSOFT_MENU lpSoftMenu
// 说明: 菜单压栈(用于返回键)
//************************************
void SoftMenu_Push(PSOFT_MENU lpSoftMenu)
{
	PSOFT_TAG_PAGE lpTagPage;
	//BYTE btNew = btMenuIndex + 1;
	BYTE btNew = 1;		//始终只有一个栈了;所以返回键始终都是返回主菜单

	if (lpSoftMenu == NULL) 
		return;
	if (btNew == 0) 
		btNew = 0xFF;

	lpMenuStack[btNew] = lpSoftMenu;

	if (lpMenuStack[btMenuIndex])
	{
		PSOFT_MENU lpCurSoftMenu = lpMenuStack[btMenuIndex];

		if (CHK_FLAGS(lpCurSoftMenu->dwFlags, SMF_FN_LEAVE) && (lpCurSoftMenu->fnLeave))
			lpCurSoftMenu->fnLeave(0, 0, 0, lpCurSoftMenu);
	}

	btMenuIndex = btNew;

	if (CHK_FLAGS(lpSoftMenu->dwFlags, SMF_FN_ENTER) && (lpSoftMenu->fnEnter))
		lpSoftMenu->fnEnter(0, 0, 0, lpSoftMenu);

	lpTagPage = &(lpSoftMenu->lpTagPage[0]);
	dwTagPageIndex = 0;

	TagPage_RefreshItems(lpTagPage);
	SoftItem_SetFocus(0, 0);
	UpdateSoftMenu();
	return;
}

//************************************
// 函数名:    SoftMenu_Pop
// Access:    public 
// 返回值类型:   void
// 说明: 菜单出栈(用于返回键)
//************************************
void SoftMenu_Pop()
{
	if (btMenuIndex == 0) 
		return;

	PSOFT_TAG_PAGE lpTagPage;
	BYTE btNew = btMenuIndex - 1;

	if (lpMenuStack[btMenuIndex])
	{
		PSOFT_MENU lpCurSoftMenu = lpMenuStack[btMenuIndex];

		if (CHK_FLAGS(lpCurSoftMenu->dwFlags, SMF_FN_LEAVE) && (lpCurSoftMenu->fnLeave))
			lpCurSoftMenu->fnLeave(0, 0, 0, lpCurSoftMenu);
	}

	while (lpMenuStack[btNew] == NULL)
	{
		if (btNew == 0)
		{
			lpMenuStack[btNew] = &menuRoot;
			break;
		}

		btNew--;
	}

	btMenuIndex = btNew;

	if (lpMenuStack[btMenuIndex])
	{
		PSOFT_MENU lpNewSoftMenu = lpMenuStack[btMenuIndex];

		if (CHK_FLAGS(lpNewSoftMenu->dwFlags, SMF_FN_ENTER) && (lpNewSoftMenu->fnEnter))
			lpNewSoftMenu->fnEnter(0, 0, 0, lpNewSoftMenu);
	}

	lpTagPage = &(lpMenuStack[btMenuIndex]->lpTagPage[0]);
	dwTagPageIndex = 0;
	
	TagPage_RefreshItems(lpTagPage);
	SoftItem_SetFocus(0, 0);
	UpdateSoftMenu();
	return;
}

/*切换软菜单
@lpSoftMenu     要切换的软菜单
@dwNewIndex     要切换的软菜单中要激活的标签页
@dwFlags        未使用
*/
void SoftMenu_Switch(PSOFT_MENU lpSoftMenu, DWORD dwNewIndex, DWORD dwFlags)
{
	PSOFT_TAG_PAGE lpTagPage;
	//BYTE btNew = btMenuIndex + 1;
	BYTE btNew = 1;

	if (lpSoftMenu == NULL) 
		return;

	if (CHK_FLAGS(dwFlags, 0x01))
		btNew = 1;

	if (btNew == 0) 
		btNew = 0xFF;

	lpMenuStack[btNew] = lpSoftMenu;

	if (lpMenuStack[btMenuIndex])
	{
		PSOFT_MENU lpCurSoftMenu = lpMenuStack[btMenuIndex];

		if (CHK_FLAGS(lpCurSoftMenu->dwFlags, SMF_FN_LEAVE) && (lpCurSoftMenu->fnLeave))
		{
			lpCurSoftMenu->fnLeave(0, 0, 0, lpCurSoftMenu);
		}
	}

	btMenuIndex = btNew;

	if (CHK_FLAGS(lpSoftMenu->dwFlags, SMF_FN_ENTER) && (lpSoftMenu->fnEnter))
		lpSoftMenu->fnEnter(0, 0, 0, lpSoftMenu);

	if ((dwNewIndex >= lpSoftMenu->dwNumOfTagPages))
		dwNewIndex = 0;

	dwTagPageIndex = dwNewIndex;
	lpTagPage = &(lpSoftMenu->lpTagPage[dwTagPageIndex]);


	if (IsWindowVisible(hwSoftMenu) == FALSE)
	{
		SNDMSG(hwMainWnd, 0x0432, 9, MAKELPARAM(0x003B, 0x0001));
	}

	TagPage_RefreshItems(lpTagPage);
	SoftItem_SetFocus(0, 0);
	UpdateSoftMenu();
	return;
}

void SizeMainWnd(BOOL blSync)
{
	if (hwMainWnd)
	{
		if (blSync)
			SendMessageA(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
		else
			PostMessageA(hwMainWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(wWidth_MainWnd, wHeight_MainWnd));
	}
}

//************************************
// 函数名:    wpfn_SoftMenu
// FullName:  wpfn_SoftMenu
// Access:    public 
// 返回值类型:   LRESULT CALLBACK
// 参数: HWND hWnd
// 参数: UINT msg
// 参数: WPARAM wParam
// 参数: LPARAM lParam
// 说明: 关于软菜单的操作(软菜单的消息处理)；
//************************************
LRESULT CALLBACK wpfn_SoftMenu(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL blTME = TRUE;
	static BOOL blSetTitle = TRUE;
	static short TagPageOrd = -1;

	switch (msg)
	{
	case WM_CREATE:
	{
		LOGFONT logfont;

		memset(&lpMenuStack[1], 0, sizeof(PSOFT_MENU) * 255);

		//设置软菜单的Z序
		SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		//创建画笔
		hPen_Gray = CreatePen(PS_SOLID, 1, RGB(1, 107, 161));
		if (hPen_Gray == NULL)
			hPen_Gray = (HPEN)GetStockObject(WHITE_PEN);

		//创建画刷
		hPatternBrush_LtBlue = CreatePatternBrush(LoadBitmap(hMod, MAKEINTRESOURCE(IDB_BMP_BLUE)));
		if (hPatternBrush_LtBlue == NULL)
			hPatternBrush_LtBlue = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

		hBrush_Light = CreateSolidBrush(RGB(0, 120, 200));
		if (hBrush_Light == NULL)
			hBrush_Light = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

		hBrush_LightGreen = CreateSolidBrush(RGB(96, 180, 255));
		if (hBrush_LightGreen == NULL)
			hBrush_LightGreen = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

		//标签页背景色
		hBrush_Dark = CreateSolidBrush(RGB(28, 45, 71));
		if (hBrush_Dark == NULL)
			hBrush_Dark = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		//校准对话框背景色;
		hCalDlg_bk = CreateSolidBrush(RGB(40, 68, 101));
		if (hCalDlg_bk == NULL)
			hCalDlg_bk = (HBRUSH)GetStockObject(DKGRAY_BRUSH);

		//创建字体
		logfont.lfHeight = 14;
		logfont.lfWidth = 0;
		logfont.lfEscapement = 0;
		logfont.lfOrientation = 0;
		logfont.lfWeight = FW_NORMAL;
		logfont.lfItalic = 0;
		logfont.lfUnderline = 0;
		logfont.lfStrikeOut = 0;
		logfont.lfCharSet = DEFAULT_CHARSET;
		logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
		logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logfont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
		logfont.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
		strcpy_s(logfont.lfFaceName, LF_FACESIZE, "Tahoma" /*"Arial"*/);

		//Arial
		hFont_cfg1 = CreateFontIndirectA(&logfont);
		if (hFont_cfg1 == NULL)
			hFont_cfg1 = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);

		logfont.lfHeight = 16;
		hFont_cfg2= CreateFontIndirectA(&logfont);
		if (hFont_cfg2 == NULL)
			hFont_cfg2 = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);

		hwSoftItem = CreateWindowEx(0, (LPCTSTR)wcSoftItem, NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN, 16, 40, (int)(wWidth_SoftMenu - (WIDTH_SUBMENU + 4)), (int)(wHeight_SoftMenu - 58), hWnd, NULL, hMod, NULL);

		if (hwSoftItem)
		{
			btMenuIndex = 0;
			TagPage_RefreshItems(lpMenuStack[0]->lpTagPage);
		}
		SetTimer(hWnd, 0x1, 1000, NULL);//两次调整窗口尺寸时间间隔,500ms时有失效.
	}
	return 0;

	case WM_TIMER:
	{
		static bool t = false;
		HWND hParenthwnd = GetParent(hWnd);

		//为了使窗口能扩展至第二屏幕，必须先还原为非最大化&最小化;
		if (t == false)
		{
			PostMessage(hParenthwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			t = true;
		}
		else
		{
			wndTDRCHK();

			wWidth_MainWnd += 1;
			UpdateSize_UI();
			SizeMainWnd(TRUE);

			SetWindowPos(hParenthwnd, NULL, 0, 0, 2370, 1080, SWP_NOZORDER | SWP_FRAMECHANGED);

			UpdateWindow(hParenthwnd);
			PhysEventHook();
			KillTimer(hWnd, 0x1);
		}
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps), hCDC;
		BOOL blCDC = TRUE;
		HBITMAP hBM;
		RECT rect;
		int cx, cy;

		if (hDC == NULL) 
			break;

		GetClientRect(hWnd, &rect);
		cx = rect.right - rect.left;
		cy = rect.bottom - rect.top;

		//尝试使用双缓冲
		hCDC = CreateCompatibleDC(hDC);

		//判断双缓冲
		if (hCDC == NULL)
		{
			hCDC = hDC;
			blCDC = FALSE;
		}
		else if (hBM = CreateCompatibleBitmap(hDC, cx, cy))
		{
			SelectObject(hCDC, hBM);
			DeleteObject(hBM);
		}
		else
		{
			DeleteDC(hCDC);
			hCDC = hDC;
			blCDC = FALSE;
		}

		//绘制软菜单外边框
		SelectObject(hCDC, hBrush_Dark);
		Rectangle(hCDC, rect.left-20, rect.top, rect.right, rect.bottom);

		//绘制
		DSM_Title(hWnd, hCDC, &ps);
		DSM_TagPage(hWnd, hCDC, &ps);

		if (blCDC)
		{
			BitBlt(hDC, rect.left, rect.top, cx, cy, hCDC, rect.left, rect.top, SRCCOPY);
			DeleteDC(hCDC);
		}

		EndPaint(hWnd, &ps);
	}
	return 0;

	case WM_ERASEBKGND:
		return TRUE;

	case WM_LBUTTONDOWN:
	{
		int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);

		SetFocus(hwSoftItem);

		if ((px >= 0) && (px < 2))
		{
			nClickState = 0;

			if (!blCapture)
			{
				SetCapture(hWnd);
				px_begin = px;
				blCapture = TRUE;
				return 0;
			}
		}
		else if (HitRect(rcItemUp, px, py))
			nClickState = 1;
		else if (HitRect(rcItemDown, px, py))
			nClickState = 2;
		else if (HitRect(rcMenuUp, px, py))
			nClickState = 3;
		else if (HitRect(rcMenuDown, px, py))
			nClickState = 4;
		else if (HitRect(rcRetButton, px, py))
			nClickState = 5;
		else if (HitRect(rcMenuButton, px, py))
		{
			PSOFT_MENU lpSoftMenu = GetCurrentSoftMenu();
			BOOL blNone = TRUE;

			for (DWORD i = 0; i < lpSoftMenu->dwNumOfTagPages; i++)
			{
				if (HitRect(lpSoftMenu->lpTagPage[i].rect, px, py))
				{
					nClickState = 20 + (int)i;
					blNone = FALSE;
					break;
				}
			}

			if (blNone)
				nClickState = 0;
		}
		else
			nClickState = 0;

		if (nLastClickState != nClickState)
		{
			nLastClickState = nClickState;
			UpdateSoftMenu();
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);

		blTME = TRUE;

		if (blCapture)
		{
			nClickState = 0;
			nLastClickState = 0;
			UpdateSoftMenu();

			ReleaseCapture();
			blCapture = FALSE;
			SetFocus(hwSoftItem);
			return 0;
		}
		else if (HitRect(rcMenuButton, px, py))
		{
			PSOFT_MENU lpSoftMenu = GetCurrentSoftMenu();
			BOOL blNone = TRUE, blTest = TRUE;

			for (DWORD i = 0; i < lpSoftMenu->dwNumOfTagPages; i++)
			{
				if (HitRect(lpSoftMenu->lpTagPage[i].rect, px, py))
				{
					if (nClickState == 20 + (int)i)
					{
						blTest = FALSE;
						nClickState = 0;
						nLastClickState = 0;
						TagPage_SetIndex(i);
						if (lpSoftMenu == &menuRoot)
							TagPageOrd = i;
					}
					blNone = FALSE;
					break;
				}
			}

			if (blTest)
			{
				nClickState = 0;
				nLastClickState = 0;
				UpdateSoftMenu();
			}

			SetFocus(hwSoftItem);
			return 0;
		}
		else if (HitRect(rcRetButton, px, py))
		{
			nClickState = 0;
			nLastClickState = 0;
			SoftMenu_Reset();

			if (-1 != TagPageOrd)
				TagPage_SetIndex(TagPageOrd);

			SetFocus(hwSoftItem);
			return 0;
		}
		else
		{
			nClickState = 0;
			nLastClickState = 0;
			UpdateSoftMenu();
			SetFocus(hwSoftItem);
			return 0;
		}
	}
	break;

	case WM_MOUSELEAVE:
	{
		blTME = TRUE;
		ReleaseCapture();
		blCapture = FALSE;
	}
	break;

	case WM_SETCURSOR:
	{
		if (blCapture || blMove)
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			return TRUE;
		}
	}
	break;

	case WM_LBUTTONDBLCLK:
	{
		int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);
		RECT rect;

		rect.left = 2;
		rect.top = 2;
		rect.right = wWidth_SoftMenu - 4;
		rect.bottom = 32;

		if (HitRect(rect, px, py)) 
			SoftMenu_Pop();
	}
	break;

	case WM_DESTROY:
	{
		if (hPen_Gray)
			DeleteObject(hPen_Gray);
		if (hPatternBrush_LtBlue)
			DeleteObject(hPatternBrush_LtBlue);
	}
	break;

	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			SetWindowPos(hwSoftItem, NULL, 4, 40, (int)(LOWORD(lParam) - (WIDTH_SUBMENU + 4)), (int)(HIWORD(lParam) - 44), SWP_NOZORDER);
		}
		break;

	case WM_SETFOCUS:
	{
		SetFocus(hwSoftItem);
		return 0;
	}
	break;

	case WM_SWITCH_SUBMENU:
	{
		if (lParam)
			SoftMenu_Switch((PSOFT_MENU)lParam, wParam, 0);
	}
	break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void UpdateSoftMenu()
{
	InvalidateRect(hwSoftMenu, NULL, TRUE);
	UpdateWindow(hwSoftMenu);

	InvalidateRect(hwSoftMenu2, NULL, TRUE);
	UpdateWindow(hwSoftMenu2);
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
	if (!blWidth)
		return;

	LONG lngWidth = 0, lngHeight = 0, lngToolHeight = 0;

	RECT rect2;
	cwMainWnd->GetClientRect(&rect2);
	wWidth_MainWnd = rect2.right - rect2.left;
	lngHeight = rect2.bottom - rect2.top;

	wHeight_SoftMenu = lngHeight - HEIGHT_DIFF_SOFTMENU;


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
	{
		lngWidth = (wWidth_SoftMenu - 0.5) / 1.25;
		*lpdwMenuWidth = 0; //lngWidth;
	}

	
	if (!lpdwTopHeight)
	{
		UpdateToolbarHeight();
		if (lpdwTopHeight)
		{
			lngToolHeight= (dwTopHeight - 0.5) / 1.25;
			*lpdwTopHeight = lngToolHeight;
		}
	}
	else
	{
		lngToolHeight = (dwTopHeight - 0.5) / 1.25;
		*lpdwTopHeight = lngToolHeight;
	}

	if (IsWindowVisible(hwSoftMenu))
		wWidth_Toolbar = wWidth_MainWnd - wWidth_SoftMenu;
	else
		wWidth_Toolbar = wWidth_MainWnd;

	SetWindowPos(hwToolbar, NULL, 0, 0, wWidth_MainWnd - wWidth_SoftMenu, dwTopHeight, SWP_NOZORDER);

	InvalidateRect(hwToolbar, NULL, TRUE);
	UpdateWindow(hwToolbar);
	

	wHeight_SoftMenu = wHeight_MainWnd - HEIGHT_DIFF_SOFTMENU;

	if (IsWindowVisible(hwSoftMenu))
		SetWindowPos(hwSoftMenu, NULL, wWidth_MainWnd - wWidth_SoftMenu, 0, wWidth_SoftMenu, wHeight_SoftMenu, SWP_NOZORDER);
	if (IsWindowVisible(hwSoftMenu2))
		SetWindowPos(hwSoftMenu2, NULL, 0, 0, wWidth_SoftMenu, wHeight_SoftMenu, SWP_NOZORDER);

	RedrawWindow(hwMainWnd, NULL, NULL, 0);

	Toolbar_UpdateItemsPos();
}

//DrawSoftMenu 绘制标题 (Title)
void DSM_Title(HWND hWnd, HDC hDC, const LPPAINTSTRUCT lpps)
{
	RECT rect;
	SelectObject(hDC, hPatternBrush_LtBlue);
	RoundRect(hDC, 2, 2, wWidth_SoftMenu - 4, 32, 8, 8);

	rect.left = 26;
	rect.top = 10;
	rect.right = wWidth_SoftMenu - 26;
	rect.bottom = 28;

	SetTextColor(hDC, RGB(240, 240, 60));
	SetBkMode(hDC, TRANSPARENT);
	SelectObject(hDC, hFont_cfg2);

	DrawTextW(hDC, GetCurrentSoftMenuTitleByIndex(nLangId), -1, &rect, DT_CENTER | DT_SINGLELINE);
}

//DrawSoftMenu 绘制标签页 (TagPage)
//************************************
// 函数名:    DSM_TagPage
// Access:    public 
// 返回值类型:   void
// 参数: HWND hWnd
// 参数: HDC hDC
// 参数: const LPPAINTSTRUCT lpps
// 说明: 循环根据画刷颜色绘制右侧菜单(标签)
//************************************
void DSM_TagPage(HWND hWnd, HDC hDC, const LPPAINTSTRUCT lpps)
{
	RECT rect, rect2;
	int nHeight;
	DWORD dwTmp;
	PSOFT_MENU lpSoftMenu = GetCurrentSoftMenu();

	rect.left = wWidth_SoftMenu - WIDTH_SUBMENU;
	rect.top = 36;
	rect.right = wWidth_SoftMenu - 4;
	rect.bottom = wHeight_MainWnd - HEIGHT_DIFF_SOFTMENU - 6;

	nHeight = rect.bottom - rect.top;

	//按钮界面周围实线
	{
		SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(6, 28, 62)));
		//深色
		MoveToEx(hDC, rect.left + 1, rect.top + 1, NULL);//↓
		LineTo(hDC, rect.left + 1, rect.bottom + 1);

		MoveToEx(hDC, rect.left + 2, rect.top + 1, NULL);//←
		LineTo(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU), rect.top + 1);

		MoveToEx(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2) - 1, rect.top, NULL);//←↓
		LineTo(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1);

		MoveToEx(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1 + 2, NULL);//↓→
		LineTo(hDC, rect.left + 1, rect.bottom + 2);


		SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(48, 83, 123)));
		//浅色
		MoveToEx(hDC, rect.left - 1, rect.top + 2, NULL);//↓
		LineTo(hDC, rect.left - 1, rect.bottom);

		MoveToEx(hDC, rect.left, rect.top + 3, NULL);//←
		LineTo(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.top + 3);

		MoveToEx(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2) + 1, rect.top + 2, NULL);//↙
		LineTo(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom);

		MoveToEx(hDC, rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1, NULL);//↘
		LineTo(hDC, rect.left - 1, rect.bottom + 1);
	}

	rect2.left = wWidth_SoftMenu - (WIDTH_SUBMENU - 4);
	rect2.top = 36;
	rect2.right = rect2.left + (WIDTH_SUBMENU - 10);
	rect2.bottom = rect2.top /*+ 16*/;

	rect2.top = rect2.bottom + 4;
	rect2.bottom = rect2.top + (nHeight - 44);

	rcMenuButton.left = rect2.left; 
	rcMenuButton.top = rect2.top;
	rcMenuButton.right = rect2.right;

	SelectObject(hDC, hFont_cfg1);

	for (dwTmp = 0; dwTmp < lpSoftMenu->dwNumOfTagPages; dwTmp++)
	{
		if (rect2.top + 28 > rect2.bottom) 
			break;

		LPCWSTR lpText;
		HBITMAP hBrush;
		int nPushed = 0;
		int Hight = 55;

		lpSoftMenu->lpTagPage[dwTmp].rect.left = rect2.left;
		lpSoftMenu->lpTagPage[dwTmp].rect.top = rect2.top;
		lpSoftMenu->lpTagPage[dwTmp].rect.right = rect2.right;
		lpSoftMenu->lpTagPage[dwTmp].rect.bottom = rect2.top + Hight;

		rect2.top += Hight+3;

		lpText = (lpSoftMenu->lpTagPage[dwTmp].szTagText) ? lpSoftMenu->lpTagPage[dwTmp].szTagText : GetStringByIndex(lpSoftMenu->lpTagPage[dwTmp].lpszTagText, nLangId);

		hBrush = hBmp_Button2;

		if (dwTagPageIndex == (int)dwTmp)
			nPushed++;
		else if ((nClickState >= 20) && (nClickState - 20 == (int)dwTmp))
			nPushed++;

		if (nPushed)
		{
			hBrush = hBmp_Button2s;
			lpSoftMenu->lpTagPage[dwTmp].rect.left -= 4;
			lpSoftMenu->lpTagPage[dwTmp].rect.right -= 4;
			DrawSolidEdge(hDC, &lpSoftMenu->lpTagPage[dwTmp].rect, hBrush, 0x10, lpText);
			lpSoftMenu->lpTagPage[dwTmp].rect.left += 4;
			lpSoftMenu->lpTagPage[dwTmp].rect.right += 4;
		}
		else
			DrawSolidEdge(hDC, &lpSoftMenu->lpTagPage[dwTmp].rect, hBrush, 0x01, lpText);
	}

	rcMenuButton.bottom = rect2.top - 2;

	if (lpSoftMenu != &menuRoot)
	{
		rcRetButton.left = rect2.left;
		rcRetButton.top = rect2.top + 4;
		rcRetButton.right = rect2.right;
		rcRetButton.bottom = rcRetButton.top + 28;

		if (nClickState == 5)
			DrawSolidEdge(hDC, &rcRetButton, hBmp_ButtonF, 0x01, GetStringByIndex(L"Return\0返回\0返回\0\0", nLangId));
		else
			DrawSolidEdge(hDC, &rcRetButton, hBmp_ButtonR, 0x01, GetStringByIndex(L"Return\0返回\0返回\0\0", nLangId));
	}
	else
	{
		rcRetButton.left = 0;
		rcRetButton.top = 0;
		rcRetButton.right = 0;
		rcRetButton.bottom = 0;
	}
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

//设置当前软菜单中激活的标签页index
int TagPage_SetIndex(DWORD dwNewIndex)
{
	if (lpMenuStack[btMenuIndex] == NULL) 
		return -1;
	if (dwNewIndex >= lpMenuStack[btMenuIndex]->dwNumOfTagPages) 
		return -2;

	dwTagPageIndex = lpMenuStack[btMenuIndex]->dwActiveIndex = dwNewIndex;
	TagPage_RefreshItems(&lpMenuStack[btMenuIndex]->lpTagPage[dwNewIndex]);
	SoftItem_SetFocus(0, 0);
	UpdateSoftMenu();

	return 0;
}

int TagPage_Prev()
{
	PSOFT_MENU lpCurSoftMenu = lpMenuStack[btMenuIndex];

	if (lpCurSoftMenu == NULL) 
		return -10;

	if (dwTagPageIndex - 1 < lpCurSoftMenu->dwNumOfTagPages)
		return TagPage_SetIndex(dwTagPageIndex - 1);

	return 0;
}

int TagPage_Next()
{
	PSOFT_MENU lpCurSoftMenu = lpMenuStack[btMenuIndex];

	if (lpCurSoftMenu == NULL) 
		return -10;

	if (dwTagPageIndex + 1 < lpCurSoftMenu->dwNumOfTagPages)
		return TagPage_SetIndex(dwTagPageIndex + 1);

	return 0;
}