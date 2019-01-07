// TDMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TDMenu.h"


extern WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_Toolbar;

// TDMenu

IMPLEMENT_DYNAMIC(TDMenu, CWnd)

TDMenu::TDMenu()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

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

	DrawTextW(hDC->m_hDC, GetCurrentSoftMenuTitleByIndex(nLangId), -1, &rect, DT_CENTER | DT_SINGLELINE);
}

void TDMenu::DSM_TagPage(CDC *hDC, const LPPAINTSTRUCT lpps)
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

	//��ť������Χʵ��
	{
		hDC->SelectObject(CreatePen(PS_SOLID, 2, RGB(6, 28, 62)));
		//��ɫ
		hDC->MoveTo(rect.left + 1, rect.top + 1);
		hDC->LineTo(rect.left + 1, rect.bottom + 1);

		hDC->MoveTo(rect.left + 2, rect.top + 1);//��
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU), rect.top + 1);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2) - 1, rect.top);//����
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1 + 2);//����
		hDC->LineTo(rect.left + 1, rect.bottom + 2);


		hDC->SelectObject(CreatePen(PS_SOLID, 2, RGB(48, 83, 123)));
		//ǳɫ
		hDC->MoveTo(rect.left - 1, rect.top + 2);//��
		hDC->LineTo(rect.left - 1, rect.bottom);

		hDC->MoveTo(rect.left, rect.top + 3);//��
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.top + 3);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2) + 1, rect.top + 2);//�L
		hDC->LineTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom);

		hDC->MoveTo(rect.left - (wWidth_SoftMenu - WIDTH_SUBMENU - 2), rect.bottom + 1);//�K
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

		rect2.top += Hight + 3;

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
			DrawSolidEdge(hDC, &rcRetButton, hBmp_ButtonF, 0x01, GetStringByIndex(L"Return\0����\0����\0\0", nLangId));
		else
			DrawSolidEdge(hDC, &rcRetButton, hBmp_ButtonR, 0x01, GetStringByIndex(L"Return\0����\0����\0\0", nLangId));
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
	CBitmap hFillBrush;
	hFillBrush.Attach(hBrush);

	rect.left -= 2;
	DrawStretchBitmap(hDC, &hFillBrush, &rect);
	rect.left += 2;

	rect.left += 2;
	rect.top += 2;
	rect.right--;
	rect.bottom--;


	//��������
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
				hDC->SetTextColor(RGB(255, 255, 0));//����������ɫ
			else
				hDC->SetTextColor(RGB(255, 255, 255));//����������ɫ

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

	//�����ϼ�ͷ
	if (nFlags & 0x02)
	{
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top;

		if ((nWidth >= 24) && (nHeight >= 10))
		{
			int nCenter = nWidth / 2;
			int nTop = (nHeight - 6) / 2;

			if (nFlags & 0x08)
				hDC->SelectObject(hPen_Gray);
			else
				hDC->SelectObject((HPEN)GetStockObject(BLACK_PEN));

			hDC->MoveTo(rect.left + nCenter, rect.top + nTop);
			hDC->LineTo(rect.left + nCenter + 1, rect.top + nTop);

			hDC->MoveTo(rect.left + nCenter - 2, rect.top + nTop + 1);
			hDC->LineTo(rect.left + nCenter + 3, rect.top + nTop + 1);

			hDC->MoveTo(rect.left + nCenter - 4, rect.top + nTop + 2);
			hDC->LineTo(rect.left + nCenter + 5, rect.top + nTop + 2);

			hDC->MoveTo(rect.left + nCenter - 6, rect.top + nTop + 3);
			hDC->LineTo(rect.left + nCenter + 7, rect.top + nTop + 3);

			hDC->MoveTo(rect.left + nCenter - 8, rect.top + nTop + 4);
			hDC->LineTo(rect.left + nCenter + 9, rect.top + nTop + 4);

			hDC->MoveTo(rect.left + nCenter - 10, rect.top + nTop + 5);
			hDC->LineTo(rect.left + nCenter + 11, rect.top + nTop + 5);
		}
	}

	//�����¼�ͷ
	if (nFlags & 0x04)
	{
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top;

		if ((nWidth >= 24) && (nHeight >= 10))
		{
			int nCenter = nWidth / 2;
			int nTop = (nHeight - 6) / 2;

			if (nFlags & 0x08)
				hDC->SelectObject(hPen_Gray);
			else
				hDC->SelectObject((HPEN)GetStockObject(BLACK_PEN));

			hDC->MoveTo(rect.left + nCenter - 10, rect.top + nTop);
			hDC->LineTo(rect.left + nCenter + 11, rect.top + nTop);

			hDC->MoveTo(rect.left + nCenter - 8, rect.top + nTop + 1);
			hDC->LineTo(rect.left + nCenter + 9, rect.top + nTop + 1);

			hDC->MoveTo(rect.left + nCenter - 6, rect.top + nTop + 2);
			hDC->LineTo(rect.left + nCenter + 7, rect.top + nTop + 2);

			hDC->MoveTo(rect.left + nCenter - 4, rect.top + nTop + 3);
			hDC->LineTo(rect.left + nCenter + 5, rect.top + nTop + 3);

			hDC->MoveTo(rect.left + nCenter - 2, rect.top + nTop + 4);
			hDC->LineTo(rect.left + nCenter + 3, rect.top + nTop + 4);

			hDC->MoveTo(rect.left + nCenter, rect.top + nTop + 5);
			hDC->LineTo(rect.left + nCenter + 1, rect.top + nTop + 5);
		}
	}
}

int TDMenu::DrawStretchBitmap(CDC *hDC, CBitmap *hBitmap, LPCRECT lpRect)
{
	if (hDC == NULL || hBitmap == NULL || lpRect == NULL)
		return -1;

	HDC hCDC = CreateCompatibleDC(hDC->m_hDC);
	BITMAP bmp;

	if (hCDC == NULL)
		return -2;

	hBitmap->GetBitmap(&bmp);
	SelectObject(hCDC, hBitmap);

	SetStretchBltMode(hDC->m_hDC, HALFTONE);

	StretchBlt(hDC->m_hDC,
		lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
		hCDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	DeleteDC(hCDC);
	return 0;
}

void TDMenu::UpdateSoftMenu()
{
	InvalidateRect(NULL,TRUE);
	UpdateWindow();
}

void TDMenu::SoftMenu_Switch(PSOFT_MENU lpSoftMenu, DWORD dwNewIndex, DWORD dwFlags)
{
	PSOFT_TAG_PAGE lpTagPage;
	BYTE btNew = 1;

	if (lpSoftMenu == NULL)
		return;

	if (CHK_FLAGS(dwFlags, 0x01))
		btNew = 1;

	if (btNew == 0)
		btNew = 0xFF;

	lpMenuStack[btNew] = *lpSoftMenu;

	if (lpMenuStack[btMenuIndex].lpszMenuTitle)
	{
		smCurMenu = lpMenuStack[btMenuIndex];

		if (CHK_FLAGS(smCurMenu.dwFlags, SMF_FN_LEAVE) && (smCurMenu.fnLeave))
		{
			smCurMenu.fnLeave(0, 0, 0, &smCurMenu);
		}
	}

	btMenuIndex = btNew;


	smCurMenu = lpMenuStack[btMenuIndex];

	if (CHK_FLAGS(smCurMenu.dwFlags, SMF_FN_ENTER) && (smCurMenu.fnEnter))
		smCurMenu.fnEnter(0, 0, 0, &smCurMenu);

	if ((dwNewIndex >= smCurMenu.dwNumOfTagPages))
		dwNewIndex = 0;

	dwTagPageIndex = dwNewIndex;
	lpTagPage = &(smCurMenu.lpTagPage[dwTagPageIndex]);
	
	if (IsWindowVisible() == FALSE)
	{
		SNDMSG(hwMainWnd, 0x0432, 9, MAKELPARAM(0x003B, 0x0001));
	}

	tdItem->TagPage_RefreshItems(lpTagPage);	//�ĳ��Ӵ����࣬���Ӵ����Լ�ˢ��	18-12-29;

	SoftItem_SetFocus(0, 0);
	UpdateSoftMenu();
	return;
}

// TDMenu ��Ϣ��������
int TDMenu::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  �ڴ�������ר�õĴ�������	
	memset(&lpMenuStack[1], 0, sizeof(PSOFT_MENU) * 255);

	//�������˵���Z��
	this->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	//��������
	hPen_Gray = CreatePen(PS_SOLID, 1, RGB(1, 107, 161));
	if (hPen_Gray == NULL)
		hPen_Gray = (HPEN)GetStockObject(WHITE_PEN);

	//������ˢ
	hPatternBrush_LtBlue = CreatePatternBrush(LoadBitmap(hMod, MAKEINTRESOURCE(IDB_BMP_BLUE)));
	if (hPatternBrush_LtBlue == NULL)
		hPatternBrush_LtBlue = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

	hBrush_Light = CreateSolidBrush(RGB(0, 120, 200));
	if (hBrush_Light == NULL)
		hBrush_Light = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

	hBrush_LightGreen = CreateSolidBrush(RGB(96, 180, 255));
	if (hBrush_LightGreen == NULL)
		hBrush_LightGreen = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

	//��ǩҳ����ɫ
	hBrush_Dark = CreateSolidBrush(RGB(28, 45, 71));
	if (hBrush_Dark == NULL)
		hBrush_Dark = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	//У׼�Ի��򱳾�ɫ;
	hCalDlg_bk = CreateSolidBrush(RGB(40, 68, 101));
	if (hCalDlg_bk == NULL)
		hCalDlg_bk = (HBRUSH)GetStockObject(DKGRAY_BRUSH);

	//��������
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
	
	tdItem = new TDItem(MenuStack[0].lpTagPage);
	tdItem->CreateEx(NULL, (LPCTSTR)wcSoftItem, NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
		16, 40, wWidth_SoftMenu - (WIDTH_SUBMENU + 4), wHeight_SoftMenu - 58, this->GetSafeHwnd(), NULL, lpCreateStruct->hInstance);

	hwSoftItem = tdItem->m_hWnd;

	if (tdItem)
	{
		btMenuIndex = 0;
		tdItem->TagPage_RefreshItems(MenuStack[0].lpTagPage);
		UpdateSoftMenu();
	}
	SetTimer(0x1, 100, NULL);
	return 0;
}

LRESULT TDMenu::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ�����ר�ô����/����û���
	switch (message)
	{
	case WM_TIMER:
	{
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

		//����ʹ��˫����
		hCDC->CreateCompatibleDC(hDC);

		//�ж�˫����
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

		//�������˵���߿�
		hCDC->SelectObject(hBrush_Dark);
		hCDC->Rectangle(rect.left - 20, rect.top, rect.right, rect.bottom);

		//����
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

	case WM_LBUTTONDOWN:
	{
		int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);

		SetFocus();

		if ((px >= 0) && (px < 2))
		{
			nClickState = 0;

			if (!blCapture)
			{
				SetCapture();
				blCapture = TRUE;
				return 0;
			}
		}
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
		{
			nClickState = 0;
			UpdateSoftMenu();
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		int px = GET_X_LPARAM(lParam), py = GET_Y_LPARAM(lParam);

		if (blCapture)
		{
			nClickState = 0;
			UpdateSoftMenu();

			ReleaseCapture();
			blCapture = FALSE;
			SetFocus();
			return 0;
		}
		else if (HitRect(rcMenuButton, px, py))
		{
			PSOFT_MENU lpSoftMenu = GetCurrentSoftMenu();
			BOOL blNone = TRUE;

			for (DWORD i = 0; i < lpSoftMenu->dwNumOfTagPages; i++)
			{
				if (HitRect(lpSoftMenu->lpTagPage[i].rect, px, py))
				{
					if (nClickState == 20 + (int)i)
					{
						nClickState = 0;
						TagPage_SetIndex(i);
					}
					blNone = FALSE;
					break;
				}
			}
			SetFocus();
			return 0;
		}
		else if (HitRect(rcRetButton, px, py))
		{
			nClickState = 0;
			SoftMenu_Reset();

			TagPage_SetIndex(0);

			SetFocus();
			return 0;
		}
		else
		{
			nClickState = 0;
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
		SetFocus();
		break;
	}
	case WM_SWITCH_SUBMENU:
	{
		if (lParam)
			SoftMenu_Switch((PSOFT_MENU)lParam, wParam, 0);
		break;
	}
	default:
		break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}