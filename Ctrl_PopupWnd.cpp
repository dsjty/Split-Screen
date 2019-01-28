#include "stdafx.h"

#define WM_REFRESHCTL               (WM_USER + 2)

LRESULT CALLBACK wpfn_PopupWnd(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wp_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern HFONT hFont_cfg1;
extern HBITMAP hBmp_Enter;

void *lpInputObject = NULL;
LPCWSTR lpwcsTitle = NULL;
DWORD dwCreateFlags = 0;
ATOM wcPopupWnd = 0;

WCHAR wcsSuffix[MAX_PATH] = { 0 };


int PopWnd_PopupInputBox(HWND hParent, LPCWSTR lpTitle, void *lpInput, PSOFT_SUB_ITEM lpSubItem, DWORD dwFlags)
{
	if (lpInput == NULL || lpSubItem == NULL)
		return -1;

	if (hWnd_PopWnd)
		EnableWindow(hWnd_PopWnd, FALSE);

	lpwcsTitle = lpTitle;
	lpInputObject = lpInput;
	lpInputItem = lpSubItem;
	dwCreateFlags = dwFlags;

	//注册SoftMenu窗口类
	if (wcPopupWnd == 0)
	{
		WNDCLASSEX wcex;

		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc = &wpfn_PopupWnd;
		wcex.hInstance = hMod;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_INACTIVEBORDER);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _T("WndCls_PopupWnd_X1");
		wcex.hIconSm = NULL;

		wcPopupWnd = RegisterClassEx(&wcex);

		if (wcPopupWnd == 0)
			return -2;
	}
	int popX = 0, popY = 0;
	if (uiCurFocusMenu==1)
	{
		popX = GetSystemMetrics(SM_CXFULLSCREEN) / 4;
		popY = GetSystemMetrics(SM_CYFULLSCREEN) / 4;
	}
	if (uiCurFocusMenu==2)
	{
		popX = GetSystemMetrics(SM_CXFULLSCREEN)+ GetSystemMetrics(SM_CXFULLSCREEN)/2;
		popY = GetSystemMetrics(SM_CYFULLSCREEN) ;
	}

	if (hWnd_PopWnd == NULL)
	{
		hWnd_PopWnd = CreateWindowExW(0, (LPCWSTR)wcPopupWnd, L"PopWnd_PopupInputBox", WS_POPUP | WS_BORDER | WS_VISIBLE, popX, popY, 238, 64, hParent, NULL, hMod, NULL);

		if (hWnd_PopWnd == NULL)
			return -3;

		SetFocus(hWnd_PopWnd);
	}
	else
	{
		SendMessage(hWnd_PopWnd, WM_REFRESHCTL, 0, 0);
		EnableWindow(hWnd_PopWnd, TRUE);
		SetFocus(hWnd_PopWnd);
	}

	return 0;
}

//判断焦点
BOOL PopWnd_IsFocus()
{
	HWND hFocus = GetFocus();

	if ((hFocus) && (hFocus == hWnd_PopWnd || hFocus == hInputEdit || hFocus == hBtnClose || hFocus == hBtnEnter || hFocus == hUpDn1 || hFocus == hUpDn2))
		return TRUE;

	return FALSE;
}

//更新输入框
void PopWnd_UpdateInputBox()
{
	if (lpInputItem && lpInputItem->lpOpt[11])
	{
		PWUPS pwups;

		pwups.lpSubItem = lpInputItem;
		pwups.lpInput = lpInputObject;
		pwups.lpTitle = lpwcsTitle;
		pwups.lpwcsSuffix = wcsSuffix;
		pwups.dwFlags = dwCreateFlags;

		func_PopWndUpdateProc fnUpdateProc = (func_PopWndUpdateProc)lpInputItem->lpOpt[11];
		fnUpdateProc(lpInputItem, &pwups, 0);

		if (pwups.lpSubItem == NULL || pwups.lpInput == NULL)
		{
			PopWnd_Destroy(NULL, TRUE);
			return;
		}

		lpInputItem = pwups.lpSubItem;
		lpInputObject = pwups.lpInput;
		lpwcsTitle = pwups.lpTitle;
		dwCreateFlags = pwups.dwFlags;
	}

	if (hWnd_PopWnd && hInputEdit && lpInputObject)
	{
		char szText[MAX_PATH] = { 0 };
		WCHAR wcsText[MAX_PATH] = { 0 };

		szText[0] = 0;
		wcsText[0] = 0;

		if (CHK_NOFLAGS(lpInputItem->dwFlags, SIF_NOREPLY) && lpInputItem->lpThis && lpInputItem->lpVTable)
		{
			OrigSoftMenu_ItemClicked2(lpInputItem->lpThis, lpInputItem->lpVTable, lpInputItem->dwFunctionId);
		}

		FmtValueToString(lpInputObject, szText, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);

		SetWindowTextW(hInputEdit, wcsText);

		if (GetFocus() == hInputEdit)
			SelectAllText(hInputEdit);
		
		InvalidateRect(hWnd_PopWnd, NULL, TRUE);
		UpdateWindow(hWnd_PopWnd);
	}
}

//设置标题前缀
void PopWnd_SetTitleSuffix(LPCWSTR lpSuffix)
{
	if (lpSuffix)
		wcscpy_s(wcsSuffix, MAX_PATH, lpSuffix);
	else
		wcsSuffix[0] = 0;

	if (hWnd_PopWnd)
	{
		InvalidateRect(hWnd_PopWnd, NULL, TRUE);
		UpdateWindow(hWnd_PopWnd);
	}
}

//销毁浮动输入框
BOOL PopWnd_Destroy(PSOFT_SUB_ITEM lpSubItem, BOOL blForce)
{
	if (hWnd_PopWnd == NULL)
	{
		hInputEdit = NULL;
		hBtnEnter = NULL;
		hBtnClose = NULL;
		hUpDn1 = NULL;
		hUpDn2 = NULL;
		lpInputItem = NULL;
		lpInputObject = NULL;
		lpwcsTitle = NULL;
		dwCreateFlags = 0;
		return TRUE;
	}
	else if (blForce)
	{
		DestroyWindow(hWnd_PopWnd);
		hWnd_PopWnd = NULL;
		hInputEdit = NULL;
		hBtnEnter = NULL;
		hBtnClose = NULL;
		hUpDn1 = NULL;
		hUpDn2 = NULL;
		lpInputItem = NULL;
		lpInputObject = NULL;
		lpwcsTitle = NULL;
		dwCreateFlags = 0;
		return TRUE;
	}
	else if (lpSubItem == lpInputItem)
	{
		DestroyWindow(hWnd_PopWnd);
		hWnd_PopWnd = NULL;
		hInputEdit = NULL;
		hBtnEnter = NULL;
		hBtnClose = NULL;
		hUpDn1 = NULL;
		hUpDn2 = NULL;
		lpInputItem = NULL;
		lpInputObject = NULL;
		lpwcsTitle = NULL;
		dwCreateFlags = 0;
		return TRUE;
	}

	return FALSE;
}

int PopWnd_Finetune(BOOL blFinetune2, int nDelta, int nCount)
{
	if (lpInputItem == NULL)
		return -1;

	double dblOutput;
	BOOL blRet;

	fn_GetDouble fnGetDbl = GetAddr_GetDbl((void*)(BASE + (DWORD)lpInputObject));
	fn_SetDouble fnSetDbl = GetAddr_SetDbl((void*)(BASE + (DWORD)lpInputObject));

	char szText[MAX_PATH] = { 0 };
	WCHAR wcsText[MAX_PATH] = { 0 };

	if (CHK_NOFLAGS(lpInputItem->dwFlags, SIF_NOREPLY) && lpInputItem->lpThis && lpInputItem->lpVTable)
		OrigSoftMenu_ItemClicked2(lpInputItem->lpThis, lpInputItem->lpVTable, lpInputItem->dwFunctionId);

	if (CHK_FLAGS(lpInputItem->dwAttributes, SIA_SETSTATEIDX) && lpInputItem->lpOpt[2])
		SetInputBtnStateIndex(lpInputItem->lpOpt[2], (int)lpInputItem->lpOpt[3]);

	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		if (blFinetune2)
			blRet = InputFineTune2(lpInputObject, &dblOutput, fnGetDbl((void*)(BASE + (DWORD)lpInputObject)), nDelta);
		else
			blRet = InputFineTune(lpInputObject, &dblOutput, fnGetDbl((void*)(BASE + (DWORD)lpInputObject)), nDelta);
	}

	if (blRet)
		blRet=fnSetDbl((void*)(BASE + (DWORD)lpInputObject), dblOutput);

	if (blRet)
		FmtValueToStringEx(lpInputObject, szText, MAX_PATH, fnGetDbl((void*)(BASE + (DWORD)lpInputObject)));
	MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);
	SetWindowTextW(hInputEdit, wcsText);

	if (CHK_FLAGS(lpInputItem->dwAttributes, SIA_PSTMSG_432_2))
		PSTMSG_432_2();

	if (CHK_FLAGS(lpInputItem->dwAttributes, SIA_UPDATEITEM))
		UpdateCurrentItems();

	if (CHK_FLAGS(lpInputItem->dwAttributes, SIA_UPDATEDATA))
		UpdateCurrentItemsAndData();

	return 0;
}


LRESULT CALLBACK wpfn_PopupWnd(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		if (lpInputObject == NULL || lpInputItem == NULL)
			return -1;

		SetWindowFont(hWnd, (HFONT)GetStockObject(SYSTEM_FONT), TRUE);

		hInputEdit = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 4, 34, 132, 23, hWnd, NULL, NULL, NULL);

		if (hInputEdit)
		{
			Edit_LimitText(hInputEdit, 40);
			SetWindowFont(hInputEdit, (HFONT)GetStockObject(SYSTEM_FIXED_FONT), TRUE);
			wpfn_InputEdit = (WNDPROC)SetWindowLong(hInputEdit, GWL_WNDPROC, (LONG)&wp_InputEdit);
		}

		if (CHK_FLAGS(dwCreateFlags, SIA_FINETUNE))
		{
			hUpDn1 = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS, 138, 34, 20, 23, hWnd, NULL, NULL, NULL);
			SetWindowPos(hUpDn1, NULL, 0, 0, 20, 23, SWP_NOOWNERZORDER | SWP_NOMOVE);
		}

		if (CHK_FLAGS(dwCreateFlags, SIA_FINETUNE2))
		{
			hUpDn2 = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE, 159, 34, 20, 23, hWnd, NULL, NULL, NULL);
			SetWindowPos(hUpDn2, NULL, 0, 0, 28, 22, SWP_NOOWNERZORDER | SWP_NOMOVE);
		}

		hBtnEnter = CreateWindowExW(0, WC_BUTTONW, L"->", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_BITMAP, 189, 34, 20, 23, hWnd, NULL, NULL, NULL);
		if (hBtnEnter)
		{
			SetWindowLong(hBtnEnter, GWL_ID, IDOK);
			SetWindowFont(hBtnEnter, (HFONT)GetStockObject(SYSTEM_FONT), TRUE);
			SendMessage(hBtnEnter, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp_Enter);
		}

		hBtnClose = CreateWindowExW(0, WC_BUTTONW, L"X", WS_CHILD | WS_VISIBLE, 211, 34, 20, 23, hWnd, NULL, NULL, NULL);
		if (hBtnClose)
		{
			SetWindowLong(hBtnClose, GWL_ID, IDCLOSE);
			SetWindowFont(hBtnClose, (HFONT)GetStockObject(SYSTEM_FONT), TRUE);
		}
	}
	return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps), hCDC;
		BOOL blCDC = TRUE;
		HBITMAP hBM;
		RECT rcClient, rcText;
		int cx, cy;
		WCHAR wcsTitle[MAX_PATH];

		if (hDC == NULL)
			break;

		GetClientRect(hWnd, &rcClient);
		cx = rcClient.right - rcClient.left;
		cy = rcClient.bottom - rcClient.top;

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

		SelectObject(hCDC, hFont_cfg1);
		SetBkMode(hCDC, TRANSPARENT);

		DrawStretchBitmap(hCDC, hBmp_Button1, &rcClient); //浮动输入框背景

		rcText = rcClient;
		rcText.left += 2;
		rcText.top += 4;
		rcText.right -= 2;
		rcText.bottom = rcText.top + 28;

		wcsTitle[0] = 0;

		if (lpwcsTitle) 
			wcscpy_s(wcsTitle, MAX_PATH, lpwcsTitle);

		wcscat_s(wcsTitle, MAX_PATH, wcsSuffix);
		DrawTextW(hCDC, wcsTitle, -1, &rcText, DT_CENTER);

		if (blCDC)
		{
			BitBlt(hDC, rcClient.left, rcClient.top, cx, cy, hCDC, rcClient.left, rcClient.top, SRCCOPY);
			DeleteDC(hCDC);
		}

		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_NCHITTEST:
	{
		RECT rect;
		POINT pt;

		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		GetClientRect(hWnd, &rect);
		ScreenToClient(hWnd, &pt);

		if (PtInRect(&rect, pt))
			return HTCAPTION;
	}
	break;
	case WM_ACTIVATE:
	{
		char szText[MAX_PATH] = { 0 };
		WCHAR wcsText[MAX_PATH] = { 0 };

		szText[0] = 0;
		wcsText[0] = 0;

		if (CHK_NOFLAGS(lpInputItem->dwFlags, SIF_NOREPLY) && lpInputItem->lpThis && lpInputItem->lpVTable)
		{
			OrigSoftMenu_ItemClicked2(lpInputItem->lpThis, lpInputItem->lpVTable, lpInputItem->dwFunctionId);
		}

		FmtValueToString(lpInputObject, szText, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);

		SetWindowTextW(hInputEdit, wcsText);

		SetFocus(hInputEdit);
		SelectAllText(hInputEdit);
	}
	return 0;
	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (wId == IDCLOSE)
		{
			PopWnd_Destroy(NULL, TRUE);
			return 0;
		}
		else if (wId == IDOK)
		{
			WCHAR wcsText[MAX_PATH] = { 0 };
			char szText[MAX_PATH] = { 0 };

			wcsText[0] = 0;
			szText[0] = 0;

			if (CHK_NOFLAGS(lpInputItem->dwFlags, SIF_NOREPLY) && lpInputItem->lpThis && lpInputItem->lpVTable)
			{
				OrigSoftMenu_ItemClicked2(lpInputItem->lpThis, lpInputItem->lpVTable, lpInputItem->dwFunctionId);
			}

			GetWindowTextW(hInputEdit, wcsText, MAX_PATH);
			WideCharToMultiByte(CP_ACP, 0, wcsText, -1, szText, MAX_PATH, NULL, NULL);

			if (CHK_NOFLAGS(lpInputItem->dwAttributes, SIA_READONLY))
				ScanfStringToValue(lpInputObject, szText, NULL);

			FmtValueToString(lpInputObject, szText, MAX_PATH, NULL);

			MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);

			SetWindowTextW(hInputEdit, wcsText);

			PopWnd_Destroy(NULL, TRUE);

			return 0;
		}
	}
	break;
	case WM_NOTIFY:
	{
		LPNMHDR lpNmHdr = (LPNMHDR)lParam;

		if (lpNmHdr->hwndFrom == hUpDn1 || lpNmHdr->hwndFrom == hUpDn2)
		{
			LPNMUPDOWN lpNmUpDn = (LPNMUPDOWN)lParam;
			int nDelta;

#if 1
			nDelta = -(lpNmUpDn->iDelta);
#else
			nDelta = lpNmUpDn->iDelta;
#endif

			if (lpNmHdr->hwndFrom == hUpDn1)
				PopWnd_Finetune(FALSE, nDelta, 1);
			else
				PopWnd_Finetune(TRUE, nDelta, 1);

			return 0;
		}
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		char szText[MAX_PATH] = { 0 };
		WCHAR wcsText[MAX_PATH] = { 0 };

		szText[0] = 0;
		wcsText[0] = 0;

		if (CHK_NOFLAGS(lpInputItem->dwFlags, SIF_NOREPLY) && lpInputItem->lpThis && lpInputItem->lpVTable)
			OrigSoftMenu_ItemClicked2(lpInputItem->lpThis, lpInputItem->lpVTable, lpInputItem->dwFunctionId);

		FmtValueToString(lpInputObject, szText, MAX_PATH, NULL);
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);

		SetWindowTextW(hInputEdit, wcsText);
	}
	break;
	case WM_REFRESHCTL:
	{
		if (!hInputEdit)
			hInputEdit = CreateWindowExW(0, WC_EDITW, lpwcsTitle, 0, 40, 2, 92, 24, hWnd, NULL, NULL, NULL);

		if (hUpDn1)
		{
			if (CHK_NOFLAGS(dwCreateFlags, SIA_FINETUNE))
			{
				DestroyWindow(hUpDn1);
				hUpDn1 = NULL;
			}
		}
		else
		{
			if (CHK_FLAGS(dwCreateFlags, SIA_FINETUNE))
				hUpDn1 = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE, 40, 76, 24, 24, hWnd, NULL, NULL, NULL);
		}

		if (hUpDn2)
		{
			if (CHK_NOFLAGS(dwCreateFlags, SIA_FINETUNE2))
			{
				DestroyWindow(hUpDn2);
				hUpDn2 = NULL;
			}
		}
		else
		{
			if (CHK_FLAGS(dwCreateFlags, SIA_FINETUNE2))
				hUpDn2 = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE, 40, 96, 24, 24, hWnd, NULL, NULL, NULL);
		}

		if (!hBtnEnter)
		{
			hBtnEnter = CreateWindowExW(0, WC_BUTTONW, L"->", WS_CHILD | WS_VISIBLE, 40, 104, 24, 24, hWnd, NULL, NULL, NULL);
			if (hBtnEnter) 
				SetWindowLong(hBtnEnter, GWL_ID, IDOK);
		}

		if (!hBtnClose)
		{
			hBtnClose = CreateWindowExW(0, WC_BUTTONW, L"X", WS_CHILD | WS_VISIBLE, 40, 114, 24, 24, hWnd, NULL, NULL, NULL);
			if (hBtnClose) 
				SetWindowLong(hBtnClose, GWL_ID, IDOK);
		}

		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}
	return 0;

	case WM_SETFOCUS:
		SetFocus(hInputEdit);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//浮动输入框的输入框窗口过程
LRESULT CALLBACK wp_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch (msg)
	{
	case WM_KEYDOWN:
	{
		if (lpInputItem)
		{
			switch (wParam)
			{
			case VK_UP:
				PopWnd_Finetune(FALSE, 1, 1);
				break;

			case VK_DOWN:
				PopWnd_Finetune(FALSE, -1, 1);
				break;

			case VK_PRIOR:
				PopWnd_Finetune(TRUE, 1, 1);
				break;

			case VK_NEXT:
				PopWnd_Finetune(TRUE, -1, 1);
				break;

			default:
				if (wpfn_InputEdit)
					lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
				else
					lResult = DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			}
		}
	}
	break;

	case WM_KEYUP:
	{
		if (lpInputItem)
		{
			switch (wParam)
			{
			case VK_UP:
			case VK_DOWN:
			case VK_PRIOR:
			case VK_NEXT:
				break;

			default:
				if (wpfn_InputEdit)
					lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
				else
					lResult = DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			}
		}
	}
	break;

	case WM_CHAR:
	{
		if (hWnd != hInputEdit)
		{
			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		if (lpInputItem)
		{
			if (CHK_FLAGS(lpInputItem->dwAttributes, SIA_INPUT_TEXT) && (wParam != VK_RETURN))
			{
				if (wpfn_InputEdit)
					lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
				else
					lResult = DefWindowProc(hWnd, msg, wParam, lParam);

				break;
			}
		}

		switch (wParam)
		{
		case VK_SPACE:
		case VK_RETURN:
			if (lpInputItem)
			{
				SNDMSG(hWnd_PopWnd, WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED), (LPARAM)hBtnEnter);
			}
			break;

		case '.':
		{
			WCHAR wcsText[MAX_PATH];
			GetWindowTextW(hWnd, wcsText, MAX_PATH);

			if (wcschr(wcsText, L'.') == NULL)
			{
				if (wpfn_InputEdit)
					lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
				else
					lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}
		break;

		case '-':
			if (lpInputItem)
			{
				DWORD dwStart, dwEnd;
				WCHAR wcsText[MAX_PATH] = { 0 };
				char szText[MAX_PATH] = { 0 };
				char szText2[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				WideCharToMultiByte(CP_ACP, 0, wcsText, -1, szText, MAX_PATH, NULL, NULL);
				TrimLeft(szText, MAX_PATH);
				BreakString(szText, MAX_PATH);

				SNDMSG(hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);

				if (dwStart == dwEnd)
				{
					if (*szText != 0)
					{
						if (*szText == '-')
							strcpy_s(szText2, MAX_PATH, &szText[1]);
						else
							sprintf_s(szText2, MAX_PATH, "-%s", szText);
					}
					else
						strcpy_s(szText2, MAX_PATH, "-");
				}
				else
					strcpy_s(szText2, MAX_PATH, "-");

				MultiByteToWideChar(CP_ACP, 0, szText2, -1, wcsText, MAX_PATH);
				SetWindowTextW(hWnd, wcsText);

				if (*szText2 == '-')
				{
					Edit_SetSel(hWnd, 1, 1);
				}
			}
			break;

		case 'G':
			if (lpInputItem && lpInputObject && CHK_NOFLAGS(lpInputItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpInputObject, wcsText, MAX_PATH, "G");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hWnd_PopWnd, WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED), (LPARAM)hBtnEnter);
			}
			break;

		case 'M':
			if (lpInputItem && lpInputObject && CHK_NOFLAGS(lpInputItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpInputObject, wcsText, MAX_PATH, "M");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hWnd_PopWnd, WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED), (LPARAM)hBtnEnter);
			}
			break;

		case 'k':
			if (lpInputItem && lpInputObject && CHK_NOFLAGS(lpInputItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpInputObject, wcsText, MAX_PATH, "k");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hWnd_PopWnd, WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED), (LPARAM)hBtnEnter);
			}
			break;

		default:

			if ((lpInputItem) && CHK_NOFLAGS(lpInputItem->dwAttributes, SIA_INPUT_TEXT))
			{
				if (((wParam >= 'A') && (wParam <= 'Z')) || ((wParam >= 'a') && (wParam <= 'z')))
					break;
			}

			if (wpfn_InputEdit)
				lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

	}
	break;

	case WM_LBUTTONUP:
	{
		static HWND hLastWnd = NULL;

		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		if (hLastWnd != hWnd)
		{
			hLastWnd = hWnd;
			SelectAllText(hWnd);
		}
	}
	break;

	case WM_SETFOCUS:
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		SetInputType(ITID_PW_GMK);
		break;

	case WM_KILLFOCUS:
	{
		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		if (hWnd != hInputEdit)
			break;

		SetInputType(ITID_UNKNOWN);

		if (lpInputObject)
		{
			WCHAR wcsText[MAX_PATH] = { 0 };

			if (CHK_NOFLAGS(lpInputItem->dwFlags, SIF_NOREPLY) && lpInputItem->lpThis && lpInputItem->lpVTable)
			{
				OrigSoftMenu_ItemClicked2(lpInputItem->lpThis, lpInputItem->lpVTable, lpInputItem->dwFunctionId);
			}

			fn_GetDouble fnGetDbl = GetAddr_GetDbl((void*)(BASE + (DWORD)lpInputObject));
			FmtValueToStringExW(lpInputObject, wcsText, MAX_PATH, fnGetDbl((void*)(BASE + (DWORD)lpInputObject)));
			SetWindowTextW(hWnd, wcsText);
		}
	}
	break;

	default:

		if (wpfn_InputEdit)
			lResult = CallWindowProc(wpfn_InputEdit, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		break;
	}
	
return lResult;
}
