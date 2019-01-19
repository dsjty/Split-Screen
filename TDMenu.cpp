// TDMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "TDMenu.h"


extern WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_Toolbar;

// TDMenu

IMPLEMENT_DYNAMIC(TDMenu, CWnd)

TDMenu::TDMenu() :
	uiCurMenu(1)
{
}

TDMenu::TDMenu(int const iSer) :
	uiCurMenu(iSer)
{
}


TDMenu::~TDMenu()
{
}

BEGIN_MESSAGE_MAP(TDMenu, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


void TDMenu::DSM_Title(CDC *hDC, const LPPAINTSTRUCT lpps)
{
	RECT rect;
	hDC->SelectObject(hPatternBrush_LtBlue);
	hDC->RoundRect(2, 2, wWidth_SoftMenu - 4, 32, 8, 8);

	rect.left = 26;
	rect.top = 10;
	rect.right = wWidth_SoftMenu - 26;
	rect.bottom = 28;

	hDC->SetTextColor(RGB(240, 240, 60));
	hDC->SetBkMode(TRANSPARENT);
	hDC->SelectObject(hFont_cfg2);

	DrawTextW(hDC->m_hDC, GetStringByIndex(smCurMenu->lpszMenuTitle, nLangId), -1, &rect, DT_CENTER | DT_SINGLELINE);
}

void TDMenu::DSM_TagPage(CDC *hDC, const LPPAINTSTRUCT lpps)
{
	RECT rect, rect2;
	int nHeight;
	DWORD dwTmp;

	rect.left = wWidth_SoftMenu - WIDTH_SUBMENU;
	rect.top = 36;
	rect.right = wWidth_SoftMenu - 4;
	rect.bottom = HEIGHT_SOFTMENU - 6;

	nHeight = rect.bottom - rect.top;

	//按钮界面周围实线
	{
		hDC->SelectObject(CreatePen(PS_SOLID, 2, RGB(6, 28, 62)));
		//深色
		hDC->MoveTo(rect.left + 1, rect.top + 1);
		hDC->LineTo(rect.left + 1, rect.bottom + 1);

		hDC->MoveTo(rect.left + 2, rect.top + 1);//←
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU), rect.top + 1);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2) - 1, rect.top);//←↓
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1 + 2);//↓→
		hDC->LineTo(rect.left + 1, rect.bottom + 2);


		hDC->SelectObject(CreatePen(PS_SOLID, 2, RGB(48, 83, 123)));
		//浅色
		hDC->MoveTo(rect.left - 1, rect.top + 2);//↓
		hDC->LineTo(rect.left - 1, rect.bottom);

		hDC->MoveTo(rect.left, rect.top + 3);//←
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.top + 3);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2) + 1, rect.top + 2);//↙
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1);//↘
		hDC->LineTo(rect.left - 1, rect.bottom + 1);
	}

	rect2.left = wWidth_SoftMenu - (WIDTH_SUBMENU - 4);
	rect2.top = 36;
	rect2.right = rect2.left + (WIDTH_SUBMENU - 10);
	rect2.bottom = rect2.top;

	rect2.top = rect2.bottom + 4;
	rect2.bottom = rect2.top + (nHeight - 44);

	rcMenuButton.left = rect2.left;
	rcMenuButton.top = rect2.top;
	rcMenuButton.right = rect2.right;

	hDC->SelectObject(hFont_cfg1);

	for (dwTmp = 0; dwTmp < vcTagList.size(); dwTmp++)
	{
		if (rect2.top + 28 > rect2.bottom)
			break;

		LPCWSTR lpText;
		HBITMAP hBrush;
		int nPushed = 0;
		int Hight = 55;

		vcTagList.at(dwTmp).rect.left = rect2.left;
		vcTagList.at(dwTmp).rect.top = rect2.top;
		vcTagList.at(dwTmp).rect.right = rect2.right;
		vcTagList.at(dwTmp).rect.bottom = rect2.top + Hight;

		rect2.top += Hight + 3;

		lpText = (vcTagList.at(dwTmp).szTagText) ? vcTagList.at(dwTmp).szTagText : GetStringByIndex(vcTagList.at(dwTmp).lpszTagText, nLangId);

		hBrush = hBmp_Button2;

		if (CHK_FLAGS(vcTagList.at(dwTmp).dwFlags, TPF_ISFOCUS))
			nPushed++;

		if (nPushed)
		{
			hBrush = hBmp_Button2s;
			vcTagList.at(dwTmp).rect.left -= 4;
			vcTagList.at(dwTmp).rect.right -= 4;
			DrawSolidEdge(hDC, &vcTagList.at(dwTmp).rect, hBrush, 0x10, lpText);
			vcTagList.at(dwTmp).rect.left += 4;
			vcTagList.at(dwTmp).rect.right += 4;
		}
		else
			DrawSolidEdge(hDC, &vcTagList.at(dwTmp).rect, hBrush, 0x01, lpText);
	}

	rcMenuButton.bottom = rect2.top - 2;

	if (smCurMenu->fnEnter != menuRoot.fnEnter)
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

void TDMenu::DrawSolidEdge(CDC *hDC, LPRECT lpRect, HBITMAP hBrush, int nFlags, LPCWSTR lpWStr)
{
	RECT rect = *lpRect;

	rect.left -= 2;
	DrawStretchBitmap(hDC->m_hDC, hBrush, &rect);
	rect.left += 2;

	rect.left += 2;
	rect.top += 2;
	rect.right--;
	rect.bottom--;


	//绘制文字
	if (((nFlags & 0x01) || (nFlags & 0x10)) && (lpWStr != NULL))
	{
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top;

		if (nHeight >= 20)
		{
			RECT rectTmp = rect;

			rectTmp.left += 2;
			rectTmp.top += 2;
			rectTmp.right--;
			rectTmp.bottom--;

			if (nFlags == 0x10)
				hDC->SetTextColor(RGB(255, 255, 0));//设置文字颜色
			else
				hDC->SetTextColor(RGB(255, 255, 255));//设置文字颜色

			hDC->SetBkMode(TRANSPARENT);

			if (0 != nLangId)
			{
				if (wcslen(lpWStr) > 5)
				{
					rectTmp.top += 6;
					rectTmp.left += 6;
					rectTmp.top += 6;
					DrawTextW(hDC->m_hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
				}
				else
					DrawTextW(hDC->m_hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				if ((wcslen(lpWStr)) > 11)
				{
					rectTmp.top += 10;
					DrawTextW(hDC->m_hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
				}
				else
					DrawTextW(hDC->m_hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
}

void TDMenu::UpdateSoftMenu()
{
	InvalidateRect(NULL, TRUE);
	UpdateWindow();
}

void TDMenu::SoftMenu_Switch(PSOFT_MENU lpSoftMenu, DWORD dwNewIndex, DWORD dwFlags)
{
	if (lpSoftMenu == NULL)
		return;

	PSOFT_MENU lpTSoftMenu = &MenuStack[1];

	if (lpTSoftMenu->fnLeave)
	{
		if (CHK_FLAGS(lpTSoftMenu->dwFlags, SMF_FN_LEAVE) && (lpTSoftMenu->fnLeave))
			lpTSoftMenu->fnLeave(0, 0, 0, lpTSoftMenu);
	}

	MenuStack[1] = *lpSoftMenu;

	smCurMenu = &MenuStack[1];

	if (CHK_FLAGS(smCurMenu->dwFlags, SMF_FN_ENTER) && (smCurMenu->fnEnter))
		smCurMenu->fnEnter(0, 0, 0, smCurMenu);

	vcTagList.clear();

	for (size_t i = 0; i < smCurMenu->dwNumOfTagPages; i++)
		vcTagList.push_back(smCurMenu->lpTagPage[i]);

	for (int i = 0; i < vcTagList.size(); i++)
		NOT_FLAGS(vcTagList.at(i).dwFlags, TPF_ISFOCUS);
	SET_FLAGS(vcTagList.at(0).dwFlags, TPF_ISFOCUS);

	stCurTagPage = &vcTagList.at(0);

	if (IsWindowVisible() == FALSE)
		SNDMSG(hwMainWnd, 0x0432, 9, MAKELPARAM(0x003B, 0x0001));

	tdItem->TagPage_RefreshItems(stCurTagPage);
	UpdateSoftMenu();

	return;
}

void TDMenu::SoftMenu_Reset()
{
	if (MenuStack[1].lpszMenuTitle)
	{
		PSOFT_MENU lpCurSoftMenu = &MenuStack[1];
		if (CHK_FLAGS(lpCurSoftMenu->dwFlags, SMF_FN_LEAVE) && (lpCurSoftMenu->fnLeave))
			lpCurSoftMenu->fnLeave(0, 0, 0, lpCurSoftMenu);
	}

	memcpy(&MenuStack[0], &menuRoot, sizeof(SOFT_MENU));
	memset(&MenuStack[1], 0, sizeof(SOFT_MENU));
	smCurMenu = &MenuStack[0];

	smCurMenu->fnEnter(0, 0, 0, smCurMenu);

	vcTagList.clear();
	for (size_t i = 0; i < smCurMenu->dwNumOfTagPages; i++)
		vcTagList.push_back(smCurMenu->lpTagPage[i]);

	iCurMenuSer = 0;
	for (int i = 0; i < vcTagList.size(); i++)
		NOT_FLAGS(vcTagList.at(i).dwFlags, TPF_ISFOCUS);
	SET_FLAGS(vcTagList.at(0).dwFlags, TPF_ISFOCUS);

	tdItem->TagPage_RefreshItems(&vcTagList.at(0));
	UpdateSoftMenu();
	return;
}

void TDMenu::SoftMenu_Pop()
{
	PSOFT_MENU lpCurMenu = { 0 };
	if (MenuStack[1].fnEnter)
	{
		lpCurMenu = &MenuStack[1];
	}

	smCurMenu = &MenuStack[0];


	if (lpCurMenu && (lpCurMenu->dwFlags, SMF_FN_LEAVE) && (lpCurMenu->fnLeave))
		lpCurMenu->fnLeave(0, 0, 0, lpCurMenu);

	smCurMenu->fnEnter(0, 0, 0, smCurMenu);

	vcTagList.clear();

	for (size_t i = 0; i < smCurMenu->dwNumOfTagPages; i++)
		vcTagList.push_back(smCurMenu->lpTagPage[i]);

	iCurMenuSer = 0;
	for (int i = 0; i < vcTagList.size(); i++)
		NOT_FLAGS(vcTagList.at(i).dwFlags, TPF_ISFOCUS);
	SET_FLAGS(vcTagList.at(0).dwFlags, TPF_ISFOCUS);

	stCurTagPage = &vcTagList.at(0);

	tdItem->TagPage_RefreshItems(stCurTagPage);
	UpdateSoftMenu();
}

int TDMenu::TagPage_SetIndex(DWORD dwNewIndex)
{
	iCurMenuSer = dwNewIndex;

	for (int i = 0; i < vcTagList.size(); i++)
		NOT_FLAGS(vcTagList.at(i).dwFlags, TPF_ISFOCUS);

	SET_FLAGS(vcTagList.at(dwNewIndex).dwFlags, TPF_ISFOCUS);
	stCurTagPage = &vcTagList.at(dwNewIndex);

	tdItem->TagPage_RefreshItems(&vcTagList.at(dwNewIndex));
	UpdateSoftMenu();

	return 0;
}

HWND TDMenu::GetItemHwnd()
{
	if (tdItem)
		return tdItem->m_hWnd;
	else
		return 0;
}

PSOFT_SUB_ITEM TDMenu::GetSoftSubItem(int index)
{
	if (!tdItem)
	{
		PSOFT_TAG_PAGE lpTagPage = stCurTagPage;

		if (lpTagPage == NULL)
			return NULL;
		if (index >= lpTagPage->dwNumOfSubItems)
			return NULL;
		return &(lpTagPage->lpSubItem[index]);
	}
	return tdItem->GetItemByIndex(index);
}

int TDMenu::GetCurrMenuSer()
{
	return uiCurMenu;
}

PSOFT_TAG_PAGE TDMenu::GetCurTagPage()
{
	return stCurTagPage;
}

// TDMenu 消息处理程序
int TDMenu::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码	
	memset(&MenuStack[1], 0, sizeof(SOFT_MENU));
	MenuStack[0] = menuRoot;
	smCurMenu = &MenuStack[0];

	this->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);	//设置软菜单的Z序

	SOFT_TAG_PAGE stTagPage = { 0 };

	for (size_t i = 0; i < MenuStack[0].dwNumOfTagPages; i++)
	{
		stTagPage = MenuStack[0].lpTagPage[i];
		vcTagList.push_back(stTagPage);
	}
	stCurTagPage = &vcTagList.at(0);
	SET_FLAGS(vcTagList.at(0).dwFlags, TPF_ISFOCUS);
	iCurMenuSer = 0;

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
	logFont.lfHeight = 14;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
	logFont.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
	strcpy_s(logFont.lfFaceName, LF_FACESIZE, "Tahoma");

	//Arial
	hFont_cfg1 = CreateFontIndirectA(&logFont);
	if (hFont_cfg1 == NULL)
		hFont_cfg1 = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);

	logFont.lfHeight = 16;
	hFont_cfg2 = CreateFontIndirectA(&logFont);
	if (hFont_cfg2 == NULL)
		hFont_cfg2 = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);

	SetTimer(0x1, 100, NULL);

	return 0;
}

LRESULT TDMenu::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message)
	{
		case WM_TIMER:
			{
				tdItem = new TDItem(MenuStack[0].lpTagPage, uiCurMenu);
				tdItem->CreateEx(NULL, (LPCTSTR)wcSoftItem, NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
					4, 40, (WIDTH_SOFTMENU - WIDTH_SUBMENU - 4), 980 - 58, GetSafeHwnd(), NULL, hMod);

				wndTDRCHK();
				SizeMainWnd(TRUE);
				PhysEventHook();

				KillTimer(0x1);
				break;
			}

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				CDC *hDC = BeginPaint(&ps), *hCDC = new CDC;
				BOOL blCDC = TRUE;
				HBITMAP hBM;
				RECT rect;
				int cx, cy;

				if (hDC == NULL)
					break;

				GetClientRect(&rect);
				cx = rect.right - rect.left;
				cy = rect.bottom - rect.top;

				//尝试使用双缓冲
				hCDC->CreateCompatibleDC(hDC);

				//判断双缓冲
				if (hCDC == NULL)
				{
					hCDC = hDC;
					blCDC = FALSE;
				}
				else if (hBM = CreateCompatibleBitmap(hDC->m_hDC, cx, cy))
				{
					hCDC->SelectObject(hBM);
					DeleteObject(hBM);
				}
				else
				{
					hCDC->DeleteDC();
					hCDC = hDC;
					blCDC = FALSE;
				}

				//绘制软菜单外边框
				hCDC->SelectObject(hBrush_Dark);
				hCDC->Rectangle(rect.left - 20, rect.top, rect.right, rect.bottom);

				//绘制
				DSM_Title(hCDC, &ps);
				DSM_TagPage(hCDC, &ps);

				if (blCDC)
				{
					hDC->BitBlt(rect.left, rect.top, cx, cy, hCDC, rect.left, rect.top, SRCCOPY);
					hCDC->DeleteDC();
				}

				EndPaint(&ps);
			}

		case WM_ERASEBKGND:
			return TRUE;

		case WM_LBUTTONUP:
			{
				int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);
				nClickState = 0;
				if (HitRect(rcMenuButton, px, py))
				{
					BOOL blNone = TRUE;

					for (DWORD i = 0; i < vcTagList.size(); i++)
					{
						if (HitRect(vcTagList.at(i).rect, px, py))
						{
							TagPage_SetIndex(i);
							blNone = FALSE;
							SetFocus();
							iCurMenuSer = i;
							return 0;
						}
					}
					SetFocus();
					return 0;
				}
				else if (HitRect(rcRetButton, px, py))
				{
					nClickState = 5;
					SoftMenu_Reset();
					TagPage_SetIndex(0);
					SetFocus();
					return 0;
				}
				else
				{
					UpdateSoftMenu();
					SetFocus();
					return 0;
				}
				break;
			}

		case WM_MOUSELEAVE:
			{
				ReleaseCapture();
				blCapture = FALSE;
				break;
			}

		case WM_LBUTTONDBLCLK:
			{
				uiCurFocusMenu = uiCurMenu;

				int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);
				RECT rect;

				rect.left = 2;
				rect.top = 2;
				rect.right = wWidth_SoftMenu - 4;
				rect.bottom = 32;

				if (HitRect(rect, px, py))
					SoftMenu_Pop();
				break;
			}

		case WM_SETFOCUS:
			{
				uiCurFocusMenu = uiCurMenu;
				if (tdItem)
					tdItem->SetFocus();
				else
					SetFocus();
				break;
			}

		case WM_SWITCH_SUBMENU:
			{
				if (lParam)
					SoftMenu_Switch((PSOFT_MENU)lParam, wParam, 0);
				break;
			}

		case WM_REFRESH:
			{
				tdItem->TagPage_RefreshItems(0);
				break;
			}
	}

	return CWnd::WindowProc(message, wParam, lParam);
}
