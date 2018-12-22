#include "stdafx.h"

HPEN hPen_Gray = NULL;

HBRUSH hPatternBrush_LtBlue = NULL;
HBRUSH hBrush_Light = NULL;
HBRUSH hBrush_LightGreen = NULL;
HBRUSH hBrush_Dark = NULL, hCalDlg_bk = NULL;

HFONT hFont_cfg1 = NULL, hFont_cfg2;    //字体配置1

int WINAPI fnItemSelected_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem, int nIndex)
{
	if (nIndex == -1)
		nIndex = 0;

	if ((lpSubItem->lpThis) && (lpSubItem->lpVTable))
	{
		if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOT_ENTER))
		{
			OrigSoftMenu_UpdateItems(lpSubItem->lpThis);
			OrigSoftMenu_Enter(lpSubItem->lpThis);
		}

		OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, nIndex);
	}
	return 0;
}

int WINAPI fnUpdateData_GetSub_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	if (lpSubItem == NULL || lpSubItem->lpThis == NULL)
		return -1;

	int nIndex = GetSubMenuSelected(lpSubItem->lpThis);

	ComboBox_SetCurSel((HWND)lpSubItem->lpOpt[4], nIndex);
	return 0;
}

int WINAPI fnUpdateData_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;

	if (lpSubItem == NULL || lpSubItem->lpOpt[2] == NULL)
		return -1;

	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}
	OrigSoftMenu_UpdateItems(lpSubItem->lpThis);
	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);
	ComboBox_SetCurSel((HWND)lpSubItem->lpOpt[4], nIndex);

	return 0;
}

int WINAPI fnUpdateData_DEC_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem)
{
	int nIndex = 0;

	if (lpSubItem == NULL || lpSubItem->lpOpt[2] == NULL)
		return -1;

	if (lpSubItem->lpOpt[12])
	{
		lpSubItem->lpOpt[2] = (void*)((DWORD)lpSubItem->lpOpt[2] - BASE);
		lpSubItem->lpOpt[12] = 0;
	}

	GetButtonStateIndex((char *)lpSubItem->lpOpt[2], lpSubItem->lpOpt[3], &nIndex, (int)lpSubItem->lpOpt[0]);
	ComboBox_SetCurSel((HWND)lpSubItem->lpOpt[4], nIndex - 1);

	return 0;
}

void DrawSolidEdge(HDC hDC, LPRECT lpRect, HBITMAP hFillBrush, int nFlags, LPCWSTR lpWStr)
{
	RECT rect = *lpRect;

	rect.left -= 2;
	DrawStretchBitmap(hDC, hFillBrush, &rect);
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
				SetTextColor(hDC, RGB(255, 255, 0));//设置文字颜色
			else
				SetTextColor(hDC, RGB(255, 255, 255));//设置文字颜色

			SetBkMode(hDC, TRANSPARENT);

			if (0 != nLangId)
			{
				if (wcslen(lpWStr) > 5)
				{
					rectTmp.top += 6;
					rectTmp.left += 6;
					rectTmp.top += 6;
					DrawTextW(hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
				}
				else
					DrawTextW(hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				if ((wcslen(lpWStr)) > 11)
				{
					rectTmp.top += 10;
					DrawTextW(hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
				}
				else
					DrawTextW(hDC, lpWStr, -1, &rectTmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}

	//绘制上箭头
	if (nFlags & 0x02)
	{
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top;

		if ((nWidth >= 24) && (nHeight >= 10))
		{
			int nCenter = nWidth / 2;
			int nTop = (nHeight - 6) / 2;

			if (nFlags & 0x08)
				SelectObject(hDC, hPen_Gray);
			else
				SelectObject(hDC, (HPEN)GetStockObject(BLACK_PEN));

			MoveToEx(hDC, rect.left + nCenter, rect.top + nTop, NULL);
			LineTo(hDC, rect.left + nCenter + 1, rect.top + nTop);

			MoveToEx(hDC, rect.left + nCenter - 2, rect.top + nTop + 1, NULL);
			LineTo(hDC, rect.left + nCenter + 3, rect.top + nTop + 1);

			MoveToEx(hDC, rect.left + nCenter - 4, rect.top + nTop + 2, NULL);
			LineTo(hDC, rect.left + nCenter + 5, rect.top + nTop + 2);

			MoveToEx(hDC, rect.left + nCenter - 6, rect.top + nTop + 3, NULL);
			LineTo(hDC, rect.left + nCenter + 7, rect.top + nTop + 3);

			MoveToEx(hDC, rect.left + nCenter - 8, rect.top + nTop + 4, NULL);
			LineTo(hDC, rect.left + nCenter + 9, rect.top + nTop + 4);

			MoveToEx(hDC, rect.left + nCenter - 10, rect.top + nTop + 5, NULL);
			LineTo(hDC, rect.left + nCenter + 11, rect.top + nTop + 5);
		}
	}

	//绘制下箭头
	if (nFlags & 0x04)
	{
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top;

		if ((nWidth >= 24) && (nHeight >= 10))
		{
			int nCenter = nWidth / 2;
			int nTop = (nHeight - 6) / 2;

			if (nFlags & 0x08)
				SelectObject(hDC, hPen_Gray);
			else
				SelectObject(hDC, (HPEN)GetStockObject(BLACK_PEN));

			MoveToEx(hDC, rect.left + nCenter - 10, rect.top + nTop, NULL);
			LineTo(hDC, rect.left + nCenter + 11, rect.top + nTop);

			MoveToEx(hDC, rect.left + nCenter - 8, rect.top + nTop + 1, NULL);
			LineTo(hDC, rect.left + nCenter + 9, rect.top + nTop + 1);

			MoveToEx(hDC, rect.left + nCenter - 6, rect.top + nTop + 2, NULL);
			LineTo(hDC, rect.left + nCenter + 7, rect.top + nTop + 2);

			MoveToEx(hDC, rect.left + nCenter - 4, rect.top + nTop + 3, NULL);
			LineTo(hDC, rect.left + nCenter + 5, rect.top + nTop + 3);

			MoveToEx(hDC, rect.left + nCenter - 2, rect.top + nTop + 4, NULL);
			LineTo(hDC, rect.left + nCenter + 3, rect.top + nTop + 4);

			MoveToEx(hDC, rect.left + nCenter, rect.top + nTop + 5, NULL);
			LineTo(hDC, rect.left + nCenter + 1, rect.top + nTop + 5);
		}
	}
}

void DrawCheckBox(HDC hDC, LPRECT lpRect, HBRUSH hFillBrush, HPEN hChkPen, int nChecked, int nFlags)
{
	if (hFillBrush)
		FillRect(hDC, lpRect, hFillBrush);
	else
		FillRect(hDC, lpRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	DrawEdge(hDC, lpRect, EDGE_RAISED, BF_RECT);

	if (nChecked)
	{
		RECT rect = *lpRect;

		rect.left += 3;
		rect.top += 3;
		rect.right -= 3;
		rect.bottom -= 3;

		if (hChkPen)
			SelectObject(hDC, hChkPen);
		else
			SelectObject(hDC, (HPEN)GetStockObject(BLACK_PEN));

		MoveToEx(hDC, rect.left, rect.top, NULL);
		LineTo(hDC, rect.right, rect.bottom);

		MoveToEx(hDC, rect.left, rect.bottom - 1, NULL);
		LineTo(hDC, rect.right, rect.top - 1);
	}
}

/* 绘制自动拉伸位图 */
int DrawStretchBitmap(HDC hDC, HBITMAP hBitmap, LPCRECT lpRect)
{
	if (hDC == NULL || hBitmap == NULL || lpRect == NULL)
		return -1;

	HDC hCDC = CreateCompatibleDC(hDC);
	BITMAP bmp;

	if (hCDC == NULL)
		return -2;

	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	SelectObject(hCDC, hBitmap);

	SetStretchBltMode(hDC, HALFTONE);
	StretchBlt(hDC,
		lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
		hCDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	DeleteDC(hCDC);
	return 0;
}

BOOL ClientToScreen(HWND hWnd, LPRECT lpRect)
{
	POINT pt;

	if (lpRect == NULL)
		return FALSE;

	pt.x = lpRect->left;
	pt.y = lpRect->top;
	ClientToScreen(hWnd, &pt);
	lpRect->left = pt.x;
	lpRect->top = pt.y;

	pt.x = lpRect->right;
	pt.y = lpRect->bottom;
	ClientToScreen(hWnd, &pt);
	lpRect->right = pt.x;
	lpRect->bottom = pt.y;

	return TRUE;
}

void SelectAllText(HWND hEdit)
{
	Edit_SetSel(hEdit, 0, -1);
}
