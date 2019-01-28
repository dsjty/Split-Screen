// TD_Button.cpp : 实现文件
//

#include "stdafx.h"


// TD_Button

IMPLEMENT_DYNAMIC(TD_Button, CMFCButton)

TD_Button::TD_Button()
{

}

TD_Button::TD_Button(PSOFT_SUB_ITEM m) :
	m_ssItem(m)
{

}

TD_Button::~TD_Button()
{
}


void TD_Button::SetEXLBLToAttributes(PSOFT_SUB_ITEM lpMe)
{
	LPCWSTR lpText = NULL;

	if (lpMe->lpOpt[2])
	{
		LPCWSTR *lppWStr = (LPCWSTR *)lpMe->lpParams;

		int nIndex = 0;

		if (lpMe->lpOpt[12])
		{
			lpMe->lpOpt[2] = (void*)((DWORD)lpMe->lpOpt[2] - BASE);
			lpMe->lpOpt[12] = 0;
		}

		GetButtonStateIndex((char *)lpMe->lpOpt[2], lpMe->lpOpt[3], &nIndex, (int)lpMe->lpOpt[0]);

		if ((*lppWStr) && ((DWORD)nIndex < lpMe->dwNumberOfParams))
			lpText = GetStringByIndex(lppWStr[nIndex], nLangId);
	}

	lpMe->lpOpt[4] = CreateWindowExW(WS_EX_CLIENTEDGE, WC_STATICW, lpText, WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 0, 0, 0, lpMe->_hWnd, NULL, hMod, NULL);

	if (lpMe->lpOpt[4])
		SubCtrl_Button_UpdatePos(lpMe);
}

LRESULT TD_Button::SubCtrl_CheckButton_OnClicked()
{
	UpdateCheckBoxState(m_ssItem);

	if (CHK_FLAGS(m_ssItem->dwFlags, SIF_UNCHECKFUNC))
	{
		//取消选中存在额外的函数
		if (CHK_FLAGS(m_ssItem->dwAttributes, SIAE_CHECKED))
		{
			//当前已命中,执行"取消选中函数"
			if (m_ssItem->lpOpt[8] && m_ssItem->lpOpt[9])
			{
				if (CHK_NOFLAGS(m_ssItem->dwFlags, SIF_NOT_ENTER))
					OrigSoftMenu_Enter(m_ssItem->lpOpt[9]);

				OrigSoftMenu_ItemClicked2(m_ssItem->lpOpt[9], m_ssItem->lpOpt[8], (DWORD)m_ssItem->lpOpt[10]);
			}
		}
		else
		{
			//当前未命中,执行"选中函数"
			if (m_ssItem->lpVTable && m_ssItem->lpThis)
			{
				if (CHK_NOFLAGS(m_ssItem->dwFlags, SIF_NOT_ENTER))
					OrigSoftMenu_Enter(m_ssItem->lpThis);

				OrigSoftMenu_ItemClicked2(m_ssItem->lpThis, m_ssItem->lpVTable, m_ssItem->dwFunctionId);
			}
		}

		UpdateCheckBoxState(m_ssItem);
	}
	else
	{
		if (m_ssItem->lpVTable && m_ssItem->lpThis)
		{
			if (CHK_NOFLAGS(m_ssItem->dwFlags, SIF_NOT_ENTER))
				OrigSoftMenu_Enter(m_ssItem->lpThis);

			OrigSoftMenu_ItemClicked2(m_ssItem->lpThis, m_ssItem->lpVTable, m_ssItem->dwFunctionId);
		}

		UpdateCheckBoxState(m_ssItem);
	}

	if (CHK_FLAGS(m_ssItem->dwFlags, SIF_POPINPUTWND) && (m_ssItem->lpOpt[1]))
	{
		if (CHK_FLAGS(m_ssItem->dwAttributes, SIAE_CHECKED))
		{
			DWORD dwFlags = 0;

			if (CHK_FLAGS(m_ssItem->dwAttributes, SIA_FINETUNE))
				SET_FLAGS(dwFlags, SIA_FINETUNE);

			if (CHK_FLAGS(m_ssItem->dwAttributes, SIA_FINETUNE2))
				SET_FLAGS(dwFlags, SIA_FINETUNE2);

			PopWnd_PopupInputBox(hwMainWnd, GetStringByIndex(m_ssItem->lpszItemText, nLangId),
				m_ssItem->lpOpt[1], m_ssItem, dwFlags);
		}
		else
			PopWnd_Destroy(m_ssItem, FALSE);
	}
	return 0;
}

LRESULT TD_Button::SubCtrl_InputButton_OnClicked()
{
	if ((m_ssItem->lpOpt[4]) && (m_ssItem->lpOpt[1]))
	{
		if (CHK_NOFLAGS(m_ssItem->dwFlags, SIF_FN_CLICKED))
		{
			WCHAR wcsText[MAX_PATH];

			wcsText[0] = 0;

			if (CHK_NOFLAGS(m_ssItem->dwFlags, SIF_NOREPLY))
				OrigSoftMenu_ItemClicked2(m_ssItem->lpThis, m_ssItem->lpVTable, m_ssItem->dwFunctionId);

			GetWindowTextW((HWND)m_ssItem->lpOpt[4], wcsText, MAX_PATH);

			if (CHK_FLAGS(m_ssItem->dwAttributes, SIA_INPUT_TEXT))
			{
				if (CHK_NOFLAGS(m_ssItem->dwAttributes, SIA_READONLY))
					SetInputStringObjectW(m_ssItem->lpOpt[1], wcsText);

				GetInputStringObjectW(m_ssItem->lpOpt[1], wcsText, MAX_PATH, NULL);
			}
			else
			{
				char szText[MAX_PATH] = { 0 };
				szText[0] = 0;

				if (CHK_NOFLAGS(m_ssItem->dwAttributes, SIA_READONLY))
				{
					WideCharToMultiByte(CP_ACP, 0, wcsText, -1, szText, MAX_PATH, NULL, NULL);
					ScanfStringToValue(m_ssItem->lpOpt[1], szText, NULL);
				}

				FmtValueToString(m_ssItem->lpOpt[1], szText, MAX_PATH, NULL);
				MultiByteToWideChar(CP_ACP, 0, szText, -1, wcsText, MAX_PATH);
			}
			SetWindowTextW((HWND)m_ssItem->lpOpt[4], wcsText);
		}
	}

	return 0;
}

void TD_Button::SetSoftSubItem(PSOFT_SUB_ITEM m_SSI)
{
	m_ssItem = m_SSI;
}

BEGIN_MESSAGE_MAP(TD_Button, CMFCButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// TD_Button 消息处理程序


void TD_Button::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项

	HDC hDC = lpDrawItemStruct->hDC, hCDC;

	BOOL blCDC = TRUE;
	HBITMAP hBM;
	RECT rect2, rect = lpDrawItemStruct->rcItem;
	int cx, cy;
	LPCWSTR lpcSubText = NULL; 
	CWnd *hFocus;
	WCHAR wStr[MAX_PATH] = { 0 };

	cx = rect.right - rect.left;
	cy = rect.bottom - rect.top;

	rect2 = rect;

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

	{
		HFONT hFont = (HFONT)SNDMSG(GetParent()->GetSafeHwnd(), WM_GETFONT, 0, 0);
		if (hFont)
			SelectObject(hCDC, hFont);
	}

	SetBkMode(hCDC, TRANSPARENT);

	if (m_ssItem->dwStyle == SIS_CheckButtonEx)
		UpdateCheckBoxState(m_ssItem);

	if (IsWindowEnabled() == FALSE || CHK_FLAGS(m_ssItem->dwAttributes, SIA_UNREAD))
		DrawStretchBitmap(hCDC, hBmp_ButtonU, &rect);
	else if (CHK_FLAGS(lpDrawItemStruct->itemState, ODS_SELECTED) || CHK_FLAGS(m_ssItem->dwAttributes, SIAE_CHECKED) || (CHK_FLAGS(m_ssItem->dwFlags, SIF_ATCTION)))
		DrawStretchBitmap(hCDC, hBmp_Button1s, &rect);
	else
		DrawStretchBitmap(hCDC, hBmp_Button1, &rect);

	hFocus = GetFocus();

	//绘制焦点矩形
	if (CHK_FLAGS(lpDrawItemStruct->itemState, ODS_FOCUS) && (!CHK_FLAGS(m_ssItem->dwAttributes, SIA_UNREAD)))
		DrawStretchBitmap(hCDC, hBmp_Button1s, &rect);

	GetWindowTextW(m_hWnd, wStr, MAX_PATH);
	SetTextColor(RGB(240, 240, 240));	//修改菜单字体颜色

	rect2 = rect;



	if (CHK_FLAGS(m_ssItem->dwAttributes, SIA_BITMAP))  //位图
	{
		rect2.left += 2;
		rect2.top += 2;
		rect2.right -= 2;
		rect2.bottom -= 2;

		if (m_ssItem->lpOpt[4] == NULL)
			m_ssItem->lpOpt[4] = LoadImage((CHK_FLAGS(m_ssItem->dwAttributes, SIA_MAINRES) ? hMainMod : hMod), MAKEINTRESOURCE(m_ssItem->nBitmapId), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

		if (m_ssItem->lpOpt[4])
			DrawStretchBitmap(hCDC, (HBITMAP)m_ssItem->lpOpt[4], &rect2);
	}
	else  //default
	{
		switch (m_ssItem->dwStyle)
		{
			case SIS_CheckButtonEx:
				{
					RECT rect3;
					rect3 = rect2;
					if (CHK_FLAGS(m_ssItem->dwAttributes, SIA_FULLLINE))
					{
						rect2.left += (rect3.right - rect3.left) / 5 / 2 - 5;
						rect2.right = (rect3.right - rect3.left) / 5 / 2 + 9;
					}
					else
					{
						rect2.left += (rect3.right - rect3.left) / 5 - 5;
						rect2.right = (rect3.right - rect3.left) / 5 + 9;
					}
					rect2.top = m_ssItem->wHeight / 2 - 7;
					rect2.bottom = m_ssItem->wHeight / 2 + 7;

					if (CHK_FLAGS(m_ssItem->dwAttributes, SIAE_CHECKED))
						DrawStretchBitmap(hCDC, hBmp_Checked, &rect2);
					else
						DrawStretchBitmap(hCDC, hBmp_Unchecked, &rect2);
					rect3.left = rect2.right + 2;
					if (nLangId == 0)
					{
						if (wcslen(wStr) > 12)
						{
							rect3.top += 3;
							rect3.left += 6;
							rect3.right -= 7;
							rect3.bottom += 8;
							DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
						}
						else
							DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
					}
					else
					{
						if (wcslen(wStr) > 6)
						{
							rect3.top += 3;
							rect3.left += 7;
							rect3.right -= 8;
							rect3.bottom += 8;
							DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
						}
						else
						{
							rect3.top -= 3;
							DrawTextW(hCDC, wStr, -1, &rect3, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
						}
					}
				}
				break;

			case SIS_InputButtonEx:
			case SIS_ComboButtonEx:
			case SIS_ComboRadioButtonEx:
				rect2.left += 2;
				rect2.right -= 2;

				rect2.top += 4;
				rect2.bottom = rect.bottom - 23;		  //调整其他框字符}
				DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER);
				break;

			default: // SIS_ButtonEx:
				if (CHK_FLAGS(m_ssItem->dwAttributes, SIA_EXLBL) && CHK_FLAGS(m_ssItem->dwAttributes, SIA_UPDATEITEM))
				{
					rect2.left += 2;
					rect2.top += 3;
					rect2.right -= 2;
					rect2.bottom -= 2;
					DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_VCENTER);
				}
				else
				{
					if (nLangId == 0)
					{
						if (wcslen(wStr) > 15)
						{
							rect2.top += 2;
							rect2.left += 7;
							rect2.right -= 7;
							DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
						}
						else
							DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					else
					{
						if (wcslen(wStr) > 9)
						{
							rect2.left += 7;
							rect2.right -= 7;
							DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
						}
						else
							DrawTextW(hCDC, wStr, -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
				break;
		}
	}

	if (blCDC)
	{
		BitBlt(hDC, rect.left, rect.top, cx, cy, hCDC, rect.left, rect.top, SRCCOPY);
		DeleteDC(hCDC);
	}

	if ((m_ssItem->dwStyle == SIS_InputButtonEx) && (m_ssItem->lpOpt[1]) && (m_ssItem->lpOpt[4]))
	{
		if (CHK_NOFLAGS(m_ssItem->dwFlags, SIF_POPINPUTWND))
		{
			::InvalidateRect((HWND)m_ssItem->lpOpt[4], NULL, TRUE);
			::UpdateWindow((HWND)m_ssItem->lpOpt[4]);
		}
	}
}


void TD_Button::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PopWnd_Destroy(0, TRUE);

	PSTMSG_432_2();

	switch (m_ssItem->dwStyle)
	{
		case SIS_ButtonEx:
			break;

		case SIS_CheckButtonEx:
			SubCtrl_CheckButton_OnClicked();
			break;

		case SIS_InputButtonEx:
			SubCtrl_InputButton_OnClicked();
			break;

		case SIS_RadioButtonEx:
			SET_FLAGS(m_ssItem->dwAttributes, SIAE_CHECKED);
			break;

		case SIS_ComboButtonEx:
		case SIS_ComboRadioButtonEx:
			{
				if (m_ssItem->dwStyle == SIS_ComboRadioButtonEx)
					SET_FLAGS(m_ssItem->dwAttributes, SIAE_CHECKED);
				break;
			}
	}

	PSOFT_SUB_ITEM lpSubItem = m_ssItem;

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_SWITCH))
	{
		if (lpSubItem->lpEvent[FNID_CLICKED])
		{
			func_ItemEvent_Clicked fnClicked = (func_ItemEvent_Clicked)lpSubItem->lpEvent[FNID_CLICKED];
			fnClicked(0, IC_CLICKED_LAST, 0, lpSubItem);
		}
		else if (lpSubItem->lpEvent[FNID_SELECTED])
		{
			func_ItemEvent_Selected fnSelected = (func_ItemEvent_Selected)lpSubItem->lpEvent[FNID_SELECTED];

			fnSelected(0, 0, 0, lpSubItem, ComboBox_GetCurSel((HWND)lpSubItem->lpOpt[4]));

			UpdateCurrentItemsAndData();
		}
	}

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_ORIGCLICK))
	{
		if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOREPLY) && (lpSubItem->dwStyle != SIS_CheckButtonEx))
		{
			if (lpSubItem->lpVTable && lpSubItem->lpThis)
			{
				if (CHK_NOFLAGS(lpSubItem->dwFlags, SIF_NOT_ENTER))
					OrigSoftMenu_Enter(lpSubItem->lpThis);

				OrigSoftMenu_ItemClicked2(lpSubItem->lpThis, lpSubItem->lpVTable, lpSubItem->dwFunctionId);
			}
		}
	}
	else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_ISMENU) && (lpSubItem->lpSoftMenu))
		::SendMessage(GetParent()->GetParent()->m_hWnd, WM_SWITCH_SUBMENU, 0, (LPARAM)(lpSubItem->lpSoftMenu));

	else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_SNDMSGCMD))
		SNDMSG(cwMainWnd->m_hWnd, WM_COMMAND, lpSubItem->wParam, lpSubItem->lParam);

	else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_CALWND) && (lpSubItem->lpCalDlgCtxt))
		CreateDialog_Cal(lpSubItem->lpCalDlgCtxt, 0);

	else if (CHK_FLAGS(lpSubItem->dwFlags, SIF_DIALOG) && (lpSubItem->lpDlgCtxt))
		CreateDialog_Def(lpSubItem->lpDlgCtxt, 0);

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_CLICKED) && (lpSubItem->lpEvent[FNID_CLICKED]) && CHK_NOFLAGS(lpSubItem->dwFlags, SIF_FN_SWITCH))
	{
		func_ItemEvent_Clicked fnClicked = (func_ItemEvent_Clicked)lpSubItem->lpEvent[FNID_CLICKED];
		fnClicked(0, IC_CLICKED_LAST, 0, lpSubItem);
	}

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEITEM))
		UpdateCurrentItems();

	if (CHK_FLAGS(lpSubItem->dwAttributes, SIA_UPDATEDATA))
		UpdateCurrentItemsAndData();

	if (CHK_FLAGS(lpSubItem->dwFlags, SIF_FN_SETFOCUS))
		SetFocus();


	CMFCButton::OnLButtonDown(nFlags, point);
}


HBRUSH TD_Button::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMFCButton::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (m_ssItem->dwStyle == SIS_Delimiter)
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(255, 255, 00));
		HBRUSH hbr = CreateSolidBrush(RGB(88, 88, 88));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
