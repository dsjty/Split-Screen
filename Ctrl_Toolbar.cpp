#include "stdafx.h"

#define CF_TOPHEIGHT                1

#define MAX_LINE                    14
#define START_LEFT                  4
#define START_TOP                   4
#define START_TOPEX                 48
#define DEFAULT_BTN_WIDTH           38
#define DEFAULT_ITEM_HEIGHT         38
#define DEFAULT_TB_HEIGHT           47
#define DEFAULT_TB_RIGHT            17

#define TF_STOP                     0x00000001
#define TF_EXITED                   0x80000000

extern WORD wWidth_MainWnd, wHeight_MainWnd;

static HANDLE hThread = NULL;
static DWORD dwThreadFlags = 0;
static int nLeft = START_LEFT, nLeftEx = START_LEFT;
static int nTop = START_TOP, nTopEx = START_TOPEX;

static void *lpOrgInputObj = NULL;

void SetToolbarHeight(WORD wHeight);

static func_tbMenuEvent fnMenuEvent = NULL;
static PSOFT_TB_ITEM lptbMenuItem = NULL;

int Toolbar_AddItem(PSOFT_TB_ITEM lptbItem);
int Toolbar_DelItem(PSOFT_TB_ITEM lptbItem);
int Toolbar_CreateItems(DWORD dwFlags);

int WINAPI fntbEvent_Start(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Explorer(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Recall(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Save(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_TraceMax(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Snapshot(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_LoadRun(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Print(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Help(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Invert(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_NewTrace(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_DelTrace(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_ChannelsConfig(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_TracesConfig(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_Marker(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
int WINAPI fntbEvent_MarkerSub(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);

int WINAPI fnMenuEvent_Start(DWORD dwMenuId, struct _SOFT_TOOLBAR_ITEM *lptbItem);

void OnDrawItem_POPMENU(HWND hWnd, LPDRAWITEMSTRUCT lpmis, HBITMAP hBmp);

//以下结构为定义工具栏按钮的结构, 第三个元素为图标Id
SOFT_TB_ITEM toolbarItem[] =
{
	{
		NULL,
		NULL,
		IDI_START,
		STBF_ICON | STBF_MENUEVENT,
		STBS_BUTTON,
		NULL,
		&fnMenuEvent_Start,
		&fntbEvent_Start,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_EXPLORER,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Explorer,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_RECALL,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Recall,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_SAVE,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Save,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_TRACEMAX,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_TraceMax,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_SNAPSHOT,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Snapshot,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_LOADRUN,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_LoadRun,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_NEWTRACE,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_NewTrace,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_DELTRACE,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_DelTrace,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_CHANNELSCONFIG,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_ChannelsConfig,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_TRACESCONFIG,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_TracesConfig,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_MARKER,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Marker,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_MARKERSUB,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_MarkerSub,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_INVERT,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Invert,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDB_BITMAP2,
		STBF_BITMAP,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Print,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
	,
	{
		NULL,
		NULL,
		IDI_HELP,
		STBF_ICON,
		STBS_BUTTON,
		NULL,
		NULL,
		&fntbEvent_Help,
		NULL,
		0,
		DEFAULT_BTN_WIDTH,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};


void UpdateToolbarHeight()
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

	lpVar = GetOffsetPointer(lpVar, 0x34);
	if (!lpVar)
		return;
	lpOrgInputObj = (void*)lpVar;
	lpdwTopHeight = (DWORD *)((int)lpVar + 0x24);
}

unsigned int WINAPI tpToolbarProc(void *lParam)
{
	if (hwToolbar)
	{
		DestroyWindow(hwToolbar);
		hwToolbar = NULL;
	}

	hwToolbar = CreateWindowExW(WS_EX_STATICEDGE, (LPCWSTR)wcToolBar, NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, wWidth_MainWnd - wWidth_SoftMenu, DEFAULT_TB_HEIGHT, (HWND)lParam, NULL, hMod, NULL);

	dwTopHeight = DEFAULT_TB_HEIGHT;

	if (hwToolbar)
	{
		UpdateSize_UI();
		Toolbar_CreateItems(0);
	}
	else
	{
		SET_FLAGS(dwThreadFlags, TF_EXITED);
		return -1;
	}

	MSG msg;
	BOOL blRet;

	while ((blRet = GetMessageW(&msg, NULL, 0, 0)) != 0)
	{
		if (blRet == -1)
		{
			continue;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		if (CHK_FLAGS(dwThreadFlags, TF_STOP))
			PostMessageW(hwToolbar, WM_QUIT, 0, 0);
	}

	SET_FLAGS(dwThreadFlags, TF_EXITED);
	return 0;
}


#if CF_TOPHEIGHT
static BOOL blSetHook_008B3224 = TRUE;

NAKED void fnhk_008B3224()
{
	__asm push ecx
	__asm mov ecx, lpOrgInputObj
	__asm cmp ecx, eax
	__asm jne lbl_Org
	__asm pop ecx
	__asm mov ebx, 0x0096BE8C
	__asm add ebx,BASE
	__asm jmp ebx

	lbl_Org:
	__asm mov ecx, 0x0096BE71
	__asm add ecx, BASE
	__asm cmp byte ptr[eax + 0x1C], 0x0
	__asm jmp ecx
}
#endif


int Toolbar_Create(HWND hParent)
{
#if CF_TOPHEIGHT
	if (blSetHook_008B3224)
	{
		blSetHook_008B3224 = FALSE;

		int nTmp;
		DWORD wCode = 0xE9E9E9E9;

		WriteMemory((void *)(0x0096BE16 + BASE), &wCode, 1);
		SetOffsetHook((int *)(0x0096BE17 + BASE), &nTmp, (int)&fnhk_008B3224);

		wCode = 0x5990A6EB;
		WriteMemory((void *)(0x0096BE6E + BASE), &wCode, 4);
	}
#endif

	if (hThread == NULL)
	{
		hThread = (HANDLE)_beginthreadex(NULL, 0, &tpToolbarProc, hParent, 0, NULL);
	}
	else
	{
		if (CHK_FLAGS(dwThreadFlags, TF_EXITED))
		{
			CloseHandle(hThread);
			hThread = (HANDLE)_beginthreadex(NULL, 0, &tpToolbarProc, hParent, 0, NULL);
		}
	}

	return 0;
}

int Toolbar_Redraw()
{
	DWORD dwLimit = sizeof(toolbarItem) / sizeof(SOFT_TB_ITEM);

	for (DWORD dwIndex = 0; dwIndex < dwLimit; dwIndex++)
	{
		if (toolbarItem[dwIndex].hwCtrl)
		{
			InvalidateRect(toolbarItem[dwIndex].hwCtrl, NULL, TRUE);
			UpdateWindow(toolbarItem[dwIndex].hwCtrl);
		}
	}

	RedrawWindow(hwToolbar, NULL, NULL, RDW_ERASE);
	return 0;
}

int Toolbar_UpdateItemsPos()
{
	DWORD dwLimit = sizeof(toolbarItem) / sizeof(SOFT_TB_ITEM);
	int nLeft = START_LEFT, nTop = START_TOP, nLeftEx = START_LEFT, nTopEx = START_TOPEX;

	for (DWORD dwIndex = 0; dwIndex < dwLimit; dwIndex++)
	{
		if (toolbarItem[dwIndex].hwCtrl)
		{
			if (nLeft + toolbarItem[dwIndex].nWidth < wWidth_Toolbar - (DEFAULT_TB_RIGHT + 5))
			{
				MoveWindow(toolbarItem[dwIndex].hwCtrl, nLeft, nTop, toolbarItem[dwIndex].nWidth, DEFAULT_ITEM_HEIGHT, TRUE);
				ShowWindow(toolbarItem[dwIndex].hwCtrl, SW_SHOW);
				nLeft += toolbarItem[dwIndex].nWidth + 4;
			}
			else
			{
				ShowWindow(toolbarItem[dwIndex].hwCtrl, SW_HIDE);
			}
		}
	}

	Toolbar_Redraw();
	return 0;
}

int Toolbar_AddItem(PSOFT_TB_ITEM lptbItem)
{
	if (lptbItem == NULL) 
		return -1;

	if (lptbItem->hwCtrl != NULL) 
		return -2;

	DWORD dwWndStyle = WS_CHILD;

	switch (lptbItem->dwStyle)
	{
	case STBS_BUTTON:
	{
		dwWndStyle |= BS_CENTER | BS_VCENTER;

		if (CHK_FLAGS(lptbItem->dwFlags, STBF_ICON))
			dwWndStyle |= BS_ICON | BS_FLAT;
		else if (CHK_FLAGS(lptbItem->dwFlags, STBF_BITMAP))
			dwWndStyle |= BS_BITMAP | BS_FLAT;

		lptbItem->hwCtrl = CreateWindowExW(0, WC_BUTTONW, NULL, dwWndStyle, START_LEFT, START_TOP, lptbItem->nWidth, DEFAULT_ITEM_HEIGHT, hwToolbar, NULL, hMod, NULL);
		
		if (lptbItem->hwCtrl == NULL)
			break;

		if (CHK_FLAGS(lptbItem->dwFlags, STBF_ICON) || CHK_FLAGS(lptbItem->dwFlags, STBF_BITMAP))
		{
			if (lptbItem->hImage == NULL)
			{
				if (CHK_FLAGS(lptbItem->dwFlags, STBF_ICON))
					lptbItem->hIcon = LoadIcon(hMod, MAKEINTRESOURCE(lptbItem->nImageId));
				else if (CHK_FLAGS(lptbItem->dwFlags, STBF_BITMAP))
					lptbItem->hBitmap = LoadBitmap(hMod, MAKEINTRESOURCE(lptbItem->nImageId));
			}

			if (CHK_FLAGS(lptbItem->dwFlags, STBF_ICON))
				SNDMSG(lptbItem->hwCtrl, BM_SETIMAGE, IMAGE_ICON, (LPARAM)lptbItem->hIcon);
			else if (CHK_FLAGS(lptbItem->dwFlags, STBF_BITMAP))
				SNDMSG(lptbItem->hwCtrl, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)lptbItem->hBitmap);
		}
	}
	break;
	}

	if (lptbItem->hwCtrl)
	{
		SetWindowLong(lptbItem->hwCtrl, GWL_USERDATA, (LONG)lptbItem);
		if (lptbItem->lngWndId) 
			SetWindowLong(lptbItem->hwCtrl, GWL_ID, lptbItem->lngWndId);
	}

	return 0;
}

int Toolbar_DelItem(PSOFT_TB_ITEM lptbItem)
{
	if (lptbItem->hwCtrl)
	{
		DestroyWindow(lptbItem->hwCtrl);
		lptbItem->hwCtrl = NULL;
	}

	lptbItem->rect.left = 0;
	lptbItem->rect.top = 0;
	lptbItem->rect.right = 0;
	lptbItem->rect.bottom = 0;

	return 0;
}

int Toolbar_CreateItems(DWORD dwFlags)
{

	for (DWORD dwIndex = 0; dwIndex < (sizeof(toolbarItem) / sizeof(SOFT_TB_ITEM)); dwIndex++)
	{
		Toolbar_AddItem(&toolbarItem[dwIndex]);
	}

	Toolbar_UpdateItemsPos();

	return 0;
}

static BOOL blMove = FALSE;

LRESULT CALLBACK wpfn_ToolBar(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps), hCDC;
		BOOL blCDC = TRUE;
		HBITMAP hBM;
		RECT rect, rect2;
		int cx, cy;

		if (hDC == NULL)
			break;

		GetClientRect(hWnd, &rect);
		cx = rect.right - rect.left;
		cy = rect.bottom - rect.top;
		rect2 = rect;

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

		FillRect(hCDC, &rect, CreateSolidBrush(RGB(40, 58, 87)));

		rect2.top++;
		rect2.left = rect2.right - DEFAULT_TB_RIGHT;

		FillRect(hCDC, &rect2, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
		FrameRect(hCDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));


		int nX = rect2.left + 4;
		int nY1 = 20;

		SetPixelV(hCDC, nX, nY1 + 3, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 1, nY1 + 2, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 2, nY1 + 1, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 3, nY1, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 4, nY1 + 1, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 5, nY1 + 2, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 6, nY1 + 3, RGB(250, 250, 250));

		nY1 += 3;
		SetPixelV(hCDC, nX, nY1 + 3, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 1, nY1 + 2, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 2, nY1 + 1, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 3, nY1, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 4, nY1 + 1, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 5, nY1 + 2, RGB(250, 250, 250));
		SetPixelV(hCDC, nX + 6, nY1 + 3, RGB(250, 250, 250));


		if (blCDC)
		{
			BitBlt(hDC, rect.left, rect.top, cx, cy, hCDC, rect.left, rect.top, SRCCOPY);
			DeleteDC(hCDC);
		}

		EndPaint(hWnd, &ps);
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		int px = GET_X_LPARAM(lParam);

		if ((px >= wWidth_Toolbar - DEFAULT_TB_RIGHT) && (px < wWidth_Toolbar))
			blMove = TRUE;
		else
			blMove = FALSE;
	}
	break;

	case WM_SETCURSOR:
	{
		if (blMove)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
			return TRUE;
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		int px = GET_X_LPARAM(lParam);

		if ((px >= wWidth_Toolbar - DEFAULT_TB_RIGHT) && (px < wWidth_Toolbar))
		{
			dwTopHeight = DEFAULT_TB_HEIGHT;

			Toolbar_UpdateItemsPos();

			SetToolbarHeight((WORD)dwTopHeight);
			SizeMainWnd(FALSE);
		}
	}
	break;

	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == BN_CLICKED)
			{
				PSOFT_TB_ITEM lptbItem = (PSOFT_TB_ITEM)GetWindowLong((HWND)lParam, GWL_USERDATA);

				if ((lptbItem) && ((LPARAM)lptbItem->hwCtrl == lParam))
				{
					if (CHK_FLAGS(lptbItem->dwFlags, STBF_MENUEVENT))
					{
						fnMenuEvent = (func_tbMenuEvent)lptbItem->lParam2;
						lptbMenuItem = lptbItem;
					}
					if (lptbItem->fnEvent)
						lptbItem->fnEvent(TBEC_CLICKED, wParam, lParam, hWnd, lptbItem);
				}
				return 0;
			}
		}
		else if (wNc == 0)
		{
			if (fnMenuEvent)
			{
				fnMenuEvent(wId, lptbMenuItem);
				return 0;
			}
		}
	}
	break;

	case  WM_DRAWITEM:
	{
		UINT nIDCtl = (UINT)wParam;
		LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

		if (NULL != wParam || NULL == lpDIS)     //wParam==0表示为菜单发出的消息;
			return DefWindowProc(hWnd, msg, wParam, lParam);

		//获取菜单子项目文字;
		CString strText;
		CMenu menu;
		menu.Attach((HMENU)lpDIS->hwndItem);
		menu.GetMenuString(lpDIS->itemID, strText, MF_BYCOMMAND);
		WCHAR wstrText[20] = { 0 };
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		MultiByteToWideChar(CP_ACP, NULL, strText, -1, wstrText, sizeof(WCHAR) * 20 + 1);
		menu.Detach();
		menu.DestroyMenu();

		HFONT hFont = (HFONT)SNDMSG(lpDIS->hwndItem, WM_GETFONT, 0, 0);
		if (hFont)
			SelectObject(lpDIS->hDC, hFont);

		if (lpDIS->itemState&ODS_SELECTED)
		{
			OnDrawItem_POPMENU(hWnd, lpDIS, hBmp_Button1s);
			SetTextColor(lpDIS->hDC, RGB(240, 240, 0));
		}
		else
		{
			OnDrawItem_POPMENU(hWnd, lpDIS, hBmp_Button1);
			SetTextColor(lpDIS->hDC, RGB(240, 240, 240));
		}

		DrawTextW(lpDIS->hDC, wstrText, -1, &lpDIS->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		break;
	}

	case WM_MEASUREITEM:
	{
		UINT nIDCtl = (UINT)wParam;
		LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT)lParam;
		if (0==nIDCtl)			//0表示为菜单发出的信息;
		{
			lpmis->itemHeight = 30;
			lpmis->itemWidth = 80;
			break;
		}
		break;
	}

	case WM_LBUTTONDBLCLK:
	{
		SizeMainWnd(TRUE);
		InvalidateRect(hwSoftMenu, NULL, TRUE);
		UpdateWindow(hwSoftMenu);
		//InvalidateRect(hwSoftMenu2, NULL, TRUE);
		//UpdateWindow(hwSoftMenu2);
		InvalidateRect(hwToolbar, NULL, TRUE);
		UpdateWindow(hwToolbar);
	}
	break;

	case WM_FINETUNE:
	{
		PopWnd_Finetune(FALSE, (int)wParam, (int)lParam);
	}
	return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


void OnDrawItem_POPMENU(HWND hWnd, LPDRAWITEMSTRUCT lpDIS, HBITMAP hBmp)
{
	HDC hDC = lpDIS->hDC, hMDC;
	CRect rect;
	HBITMAP hmBM;

	rect = lpDIS->rcItem;
	hMDC = CreateCompatibleDC(hDC);

	if (NULL == hMDC)
	{
		hMDC = hDC;
		FillRect(hMDC, rect, GetStockBrush(GRAY_BRUSH));
		DeleteDC(hMDC);
		return;
	}
	else if (hmBM = CreateCompatibleBitmap(hDC, rect.Width(), rect.Height()))
	{
		SelectObject(hMDC, hmBM);
		DeleteObject(hmBM);
	}
	else
	{
		DeleteDC(hMDC);
		hMDC = hDC;
	}

	BITMAP bmp;

	GetObject(hBmp, sizeof(BITMAP), &bmp);

	SelectObject(hMDC, hBmp);

	SetStretchBltMode(hDC, HALFTONE);

	StretchBlt(hDC, rect.left, rect.top, rect.Width(), rect.Height(), hMDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	DeleteDC(hMDC);
	return;
}