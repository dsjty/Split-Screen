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
