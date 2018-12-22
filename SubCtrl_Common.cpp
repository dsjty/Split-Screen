#include "stdafx.h"

static WNDPROC wpfn_CommonButton = NULL;

void SetWndProc_Button(WNDPROC wpNewProc, BOOL blForce)
{
	if (blForce)
		wpfn_CommonButton = wpNewProc;
	else if (wpfn_CommonButton == NULL)
		wpfn_CommonButton = wpNewProc;
}

//公共按钮窗口过程
LRESULT CALLBACK wp_Button(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch (msg)
	{
	case WM_KEYDOWN:
	{
		HWND hParent = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hWnd, GWL_USERDATA);

		if (hParent != hwSoftItem || !lpSubItem)
		{
			if (wpfn_CommonButton)
				lResult = CallWindowProc(wpfn_CommonButton, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		switch (wParam)
		{
		case VK_F1:
			TagPage_ShowHelp(lpSubItem);
			break;

		case VK_UP:
			SoftItem_PrevItem();
			break;

		case VK_DOWN:
			SoftItem_NextItem();
			break;

		case VK_LEFT:
			TagPage_Prev();
			break;

		case VK_RIGHT:
			TagPage_Next();
			break;

		case VK_SPACE:
			keybd_event(VK_RETURN, 0, 0, 0);
			keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
			break;

		case VK_RETURN:
		{
			switch (lpSubItem->dwStyle)
			{
			case SIS_InputButtonEx:
				if (lpSubItem->lpOpt[4])
				{
					SetFocus((HWND)lpSubItem->lpOpt[4]);
					SelectAllText((HWND)lpSubItem->lpOpt[4]);
				}

				break;

			case SIS_ComboButtonEx:
			case SIS_ComboRadioButtonEx:
				if (lpSubItem->lpOpt[4])
				{
					SetFocus((HWND)lpSubItem->lpOpt[4]);
					ComboBox_ShowDropdown((HWND)lpSubItem->lpOpt[4], TRUE);
				}
				break;

			default:
				SNDMSG(hwSoftItem, WM_COMMAND,
					MAKEWPARAM(GetWindowLong(hWnd, GWL_ID), BN_CLICKED), (LPARAM)hWnd);
				break;
			}
		}
		break;

		default:
			if (wpfn_CommonButton)
				lResult = CallWindowProc(wpfn_CommonButton, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
	}
	break;

	case WM_KEYUP:
	{
		HWND hParent = GetParent(hWnd);
		PSOFT_SUB_ITEM lpSubItem = (PSOFT_SUB_ITEM)GetWindowLong(hWnd, GWL_USERDATA);

		if (hParent != hwSoftItem || !lpSubItem)
		{
			if (wpfn_CommonButton)
				lResult = CallWindowProc(wpfn_CommonButton, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}

		switch (wParam)
		{
		case VK_F1:
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_SPACE:
		case VK_RETURN:
			break;

		default:
			if (wpfn_CommonButton)
				lResult = CallWindowProc(wpfn_CommonButton, hWnd, msg, wParam, lParam);
			else
				lResult = DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
	}
	break;

	default:
		if (wpfn_CommonButton)
			lResult = CallWindowProc(wpfn_CommonButton, hWnd, msg, wParam, lParam);
		else
			lResult = DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return lResult;
}