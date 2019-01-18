// TD_Edit.cpp : 实现文件
//

#include "stdafx.h"
#include "TD_Edit.h"


// TD_Edit

IMPLEMENT_DYNAMIC(TD_Edit, CEdit)

TD_Edit::TD_Edit(PSOFT_SUB_ITEM m) :
	lpSubItem(m)
{

}

TD_Edit::~TD_Edit()
{
}


BEGIN_MESSAGE_MAP(TD_Edit, CEdit)
END_MESSAGE_MAP()



// TD_Edit 消息处理程序




LRESULT TD_Edit::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	switch (message)
	{
		case WM_KEYDOWN:
			{
				HWND hwSoftItem = NULL;
				if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
					DefWindowProc(message, wParam, lParam);

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
						DefWindowProc(message, wParam, lParam);
						break;
				}
			}
			break;

		case WM_KEYUP:
			{
				if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
					DefWindowProc(message, wParam, lParam);

				switch (wParam)
				{
					case VK_UP:
					case VK_DOWN:
					case VK_PRIOR:
					case VK_NEXT:
						break;

					default:
						DefWindowProc(message, wParam, lParam);
						break;
				}
			}
			break;

		case WM_CHAR:
			{
				if (lpSubItem)
				{
					if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT) && (wParam != VK_RETURN))
					{
						DefWindowProc(message, wParam, lParam);
						break;
					}
				}

				switch (wParam)
				{
					case VK_RETURN:
						if (lpSubItem)
						{
							SetFocus();
						}
						break;

					case '-':
						if (lpSubItem)
						{
							DWORD dwStart, dwEnd;
							char szText[MAX_PATH] = { 0 };
							char szText2[MAX_PATH] = { 0 };

							GetWindowText(szText,MAX_PATH);
							TrimLeft(szText, MAX_PATH);
							BreakString(szText, MAX_PATH);

							SNDMSG(GetSafeHwnd(), EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);

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

							SetWindowText(szText2);

							if (*szText2 == '-')
							{
								Edit_SetSel(GetSafeHwnd(), 1, 1);
							}
						}
						break;

					case 'G':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "G");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(),GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'M':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "M");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'k':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "k");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'a':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "a");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'f':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "f");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'p':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "p");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'n':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "n");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'u':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "\xEC\0");   //μ
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					case 'm':
						if (lpSubItem && lpSubItem->lpOpt[1] && CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TIME))
						{
							WCHAR wcsText[MAX_PATH] = { 0 };

							GetWindowTextW(GetSafeHwnd(), wcsText, MAX_PATH);
							MakeUnitStringW(lpSubItem->lpOpt[1], wcsText, MAX_PATH, "m");
							SetWindowTextW(GetSafeHwnd(), wcsText);
							SNDMSG(GetParent()->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GetSafeHwnd(), GWL_ID), BN_CLICKED), 0);
						}
						break;

					default:
						if ((lpSubItem) && CHK_NOFLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
						{
							if (((wParam >= 'A') && (wParam <= 'Z')) || ((wParam >= 'a') && (wParam <= 'z')))
								break;
						}

						DefWindowProc(message, wParam, lParam);
						break;
				}

			}
			break;

		case WM_LBUTTONUP:
			{
				DefWindowProc(message, wParam, lParam);

				SelectAllText(GetSafeHwnd());
			}
			break;

		case WM_SETFOCUS:
			{
				if (lpSubItem)
				{
					SetInputItem(lpSubItem);

					if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_INPUT_TEXT))
					{
						SetInputType(ITID_TEXT);
						ShellExecuteA(GetParent()->GetParent()->GetSafeHwnd(), "open", "C:\\Windows\\system32\\osk.exe", NULL, NULL, SW_SHOW);
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
				SetInputItem(NULL);
				SetInputType(ITID_UNKNOWN);

				HWND hItem = GetParent()->GetSafeHwnd();

				if (lpSubItem && lpSubItem->lpOpt[1])
				{
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
						SetWindowTextW(GetSafeHwnd(), wcsText);
					}
				}

			}
			break;

		case WM_MOUSEWHEEL:
			{
				short nDelta = GET_WHEEL_DELTA_WPARAM(wParam);

				SoftItem_Finetune(lpSubItem, nDelta, 1);
				return 0;
			}
			break;

		default:
			DefWindowProc(message, wParam, lParam);
			break;
	}
	return CEdit::WindowProc(message, wParam, lParam);
}
