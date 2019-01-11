#include "stdafx.h"

static WNDPROC wpfn_InputBox = NULL;
static LRESULT CALLBACK wp_InputBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void SetInputType(int nNewType);
void SetInputItem(PSOFT_SUB_ITEM lpSubItem);
int WINAPI PhysEventHandler_Entry(WPARAM wParam, LPARAM lParam);


//Sub Control :: UpdatePos
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe)
{
	if (lpMe == NULL) return -1;

	if (lpMe->_hWnd)
	{
		RECT rcSub;

		GetClientRect(lpMe->_hWnd, &rcSub);

		rcSub.left += 8;
		rcSub.right -= 8;

		if (rcSub.bottom - 30 < 26)
			rcSub.top = 20;
		else
			rcSub.top = rcSub.bottom - 32;

		if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) || CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
		{
			//存在微调按钮
			LONG lngLeft;

			if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) && CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
			{
				//同时存在2种微调按钮
				rcSub.right -= 44;
				lngLeft = rcSub.right + 2;

				if (lpMe->lpOpt[5])
					MoveWindow((HWND)lpMe->lpOpt[5], lngLeft, rcSub.top - 3, 19, 18, TRUE);

				lngLeft += 21;

				if (lpMe->lpOpt[6])
					MoveWindow((HWND)lpMe->lpOpt[6], lngLeft, rcSub.top - 3, 19, 18, TRUE);

			}
			else
			{
				//存在单一一种微调按钮
				rcSub.right -= 22;
				lngLeft = rcSub.right + 2;

				if (lpMe->lpOpt[5])
					MoveWindow((HWND)lpMe->lpOpt[5], lngLeft, rcSub.top - 3, 19, 20, TRUE);
			}
		}

		if (lpMe->lpOpt[4])
			MoveWindow((HWND)lpMe->lpOpt[4], rcSub.left, rcSub.top, rcSub.right - rcSub.left, 20, TRUE);
	}

	return 0;
}

int SubCtrl_InputButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight)
{
	lpMe->_hWnd = CreateWindowExW(0, WC_BUTTONW, GetSoftItemTextByIndex(lpMe, nLangId),
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | (CHK_FLAGS(lpMe->dwAttributes, SIA_GROUP) ? WS_GROUP : 0) | BS_OWNERDRAW,
		x, y, nWidth, nHeight, hWnd, NULL, hMod, NULL);

	if (lpMe->_hWnd)
	{
		if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) || CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
		{
			//存在微调按钮

			if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE) && CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
			{
				//同时存在2种微调按钮

				lpMe->lpOpt[5] = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE,
					0, 0, 0, 0,
					lpMe->_hWnd, NULL, hMod, NULL);

				if (lpMe->lpOpt[5])
					SetWindowLong((HWND)lpMe->lpOpt[5], GWL_USERDATA, SIA_FINETUNE);

				lpMe->lpOpt[6] = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE,
					0, 0, 0, 0,
					lpMe->_hWnd, NULL, hMod, NULL);

				if (lpMe->lpOpt[6])
					SetWindowLong((HWND)lpMe->lpOpt[6], GWL_USERDATA, SIA_FINETUNE2);
			}
			else
			{
				//存在单一一种微调按钮
				LONG lngUserData = 0;

				lpMe->lpOpt[5] = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, lpMe->_hWnd, NULL, hMod, NULL);

				if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE))
					lngUserData = SIA_FINETUNE;
				else if (CHK_FLAGS(lpMe->dwAttributes, SIA_FINETUNE2))
					lngUserData = SIA_FINETUNE2;

				if (lpMe->lpOpt[5])
					SetWindowLong((HWND)lpMe->lpOpt[5], GWL_USERDATA, lngUserData);
			}
		}

		lpMe->lpOpt[4] = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL |
			(CHK_FLAGS(lpMe->dwAttributes, SIA_READONLY) ? ES_READONLY : 0), 0, 0, 0, 0, lpMe->_hWnd, NULL, hMod, NULL);

		if (lpMe->lpOpt[4])
		{
			WNDPROC wpTmp = (WNDPROC)SetWindowLong((HWND)lpMe->lpOpt[4], GWL_WNDPROC, (LONG)&wp_InputBox);

			if (wpfn_InputBox == NULL)
				wpfn_InputBox = wpTmp;
		}
		SubCtrl_InputButton_UpdatePos(lpMe);
	}

	return 0;
}


//Sub Control :: Event
LRESULT SubCtrl_InputButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd)
{
	if ((lpSubItem->lpOpt[4]) && (lpSubItem->lpOpt[1]))
	{
		if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_FN_CLICKED))
		{
			WCHAR wcsText[MAX_PATH];

			wcsText[0] = 0;

			if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOREPLY))
				OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);

			GetWindowTextW((HWND)lpSubItem->lpOpt[4], wcsText, MAX_PATH);

			if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
			{
				if (CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_READONLY))
					SetInputStringObjectW(lpSubItem->lpOpt[1], wcsText);

				GetInputStringObjectW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, NULL);
			}
			else
			{
				char szText[MAX_PATH] = { 0 };
				szText[0] = 0;

				if (CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_READONLY))
				{
					WideCharToMultiByte(CP_ACP, 0, wcsText, -1, szText, MAX_PATH, NULL, NULL);
					ScanfStringToValue(lpSubItem->lpOpt[1], szText, NULL);
				}

				FmtValueToString(lpSubItem->lpOpt[1], szText, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);
			}
			SetWindowTextW((HWND)lpSubItem->lpOpt[4], wcsText);
		}
	}

	return 0;
}

LRESULT CALLBACK wp_InputBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch (msg)
	{
	case WM_KEYDOWN:
	{
		HWND hItem = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hItem, GWL_USERDATA);

		if (GetParent(hItem) != hwSoftItem || !lpSubItem)
		{
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
		{
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		switch (wParam)
		{
		case VK_UP:
			SoftItem_Finetune(lpSubItem, 1, 1);
			break;

		case VK_DOWN:
			SoftItem_Finetune(lpSubItem, -1, 1);
			break;

		case VK_PRIOR:
			SoftItem_Finetune2(lpSubItem, 1);
			break;

		case VK_NEXT:
			SoftItem_Finetune2(lpSubItem, -1);
			break;

		default:
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
	}
	break;

	case WM_KEYUP:
	{
		HWND hItem = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hItem, GWL_USERDATA);

		if (GetParent(hItem) != hwSoftItem || !lpSubItem)
		{
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
		{
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		switch (wParam)
		{
		case VK_UP:
		case VK_DOWN:
		case VK_PRIOR:
		case VK_NEXT:
			break;

		default:
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
	}
	break;

	case WM_CHAR:
	{
		HWND hItem = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hItem, GWL_USERDATA);

		if (GetParent(hItem) != hwSoftItem)
		{
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		if (lpSubItem)
		{
			if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT) && (wParam != VK_RETURN))
			{
				if (wpfn_InputBox)
					lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
				else
					lResult = DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			}
		}

		switch (wParam)
		{
		case VK_RETURN:
			if (lpSubItem)
			{
				SetFocus(hItem);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case '-':
			if (lpSubItem)
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
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "G");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'M':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "M");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'k':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "k");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'a':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "a");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'f':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "f");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'p':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "p");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'n':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "n");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'u':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "\xEC\0");   //μ
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		case 'm':
			if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
			{
				WCHAR wcsText[MAX_PATH] = { 0 };

				GetWindowTextW(hWnd, wcsText, MAX_PATH);
				MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "m");
				SetWindowTextW(hWnd, wcsText);
				SNDMSG(hwSoftItem, WM_COMMAND, MAKEWPARAM(GetWindowLong(hItem, GWL_ID), BN_CLICKED), (LPARAM)hItem);
			}
			break;

		default:

			if ((lpSubItem) && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
			{
				if (((wParam >= 'A') && (wParam <= 'Z')) || ((wParam >= 'a') && (wParam <= 'z')))
					break;
			}

			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

	}
	break;

	case WM_LBUTTONUP:
	{
		static HWND hLastWnd = NULL;

		if (wpfn_InputBox)
			lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
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
	{
		if (wpfn_InputBox)
			lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		HWND hItem = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hItem, GWL_USERDATA);

		if (GetParent(hItem) != hwSoftItem)
			break;

		if (lpSubItem)
		{
			SetInputItem(lpSubItem);

			if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
			{
				SetInputType(ITID_TEXT);
				ShellExecuteA(hwSoftItem, "open", "C:\\Windows\\system32\\osk.exe", NULL, NULL, SW_SHOW);
			}
			else if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
				SetInputType(ITID_NUM);
			else
				SetInputType(ITID_GMK);
		}
	}
	break;

	case WM_KILLFOCUS:
	{
		if (wpfn_InputBox)
			lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		SetInputItem(NULL);
		SetInputType(ITID_UNKNOWN);

		HWND hItem = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hItem, GWL_USERDATA);

		if (GetParent(hItem) != hwSoftItem)
			break;

		if (lpSubItem && lpSubItem->lpOpt[1])
		{
			if ((HWND)wParam == lpSubItem->_hWnd)
				break;

			WCHAR wcsText[MAX_PATH] = { 0 };

			if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOREPLY) && lpSubItem->lpThis && lpSubItem->lpVTable)
			{
				OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
			}

			if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
			{
				GetInputStringObjectW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, NULL);
			}
			else
			{
				fn_GetDouble fnGetDbl = GetAddr_GetDbl((void*)(BASE + (DWORD)(lpSubItem->lpOpt[1])));
				FmtValueToStringExW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, fnGetDbl(lpSubItem->lpOpt[1]));
				SetWindowTextW(hWnd, wcsText);
			}
		}

	}
	break;

	case WM_MOUSEWHEEL:
	{
		HWND hItem = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hItem, GWL_USERDATA);
		short nDelta = GET_WHEEL_DELTA_WPARAM(wParam);

		if (GetParent(hItem) != hwSoftItem || lpSubItem == NULL)
		{
			if (wpfn_InputBox)
				lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);

			break;
		}

		SoftItem_Finetune(lpSubItem, nDelta, 1);
		return 0;
	}
	break;

	default:

		if (wpfn_InputBox)
			lResult = CallWindowProc(wpfn_InputBox, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);

		break;
	}

	return lResult;
}