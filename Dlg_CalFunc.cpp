#include "stdafx.h"

static HWND hwDlgCal = NULL;
static PCALDLG_CTXT lpContext = NULL;

static INT_PTR CALLBACK DlgProc_Cal(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

typedef struct _CalDlgSize
{
	CRect rcDlgSize;	//校准窗口坐标;
	CRect rcStaticSize;
	int iDlgDeffeX;
	int iDlgDeffeY;
}CalDlgSize, *pCalDlgSize;

BOOL ReSizeCalDlg(HWND hWnd, PCALDLG_CTXT lpDlgCtxt, CRect Crect);


//************************************
// 函数名:    CreateDialog_Cal
// Access:    public 
// 返回值类型:   int
// 参数: PCALDLG_CTXT lpDlgCtxt
// 参数: DWORD dwFlags
// 说明: 创建校准窗口
//************************************
int CreateDialog_Cal(PCALDLG_CTXT lpDlgCtxt, DWORD dwFlags)
{
	if (lpDlgCtxt == NULL)
		return -1;
	if (lpDlgCtxt->fnDlgEvent == NULL)
		return -2;
	if (lpDlgCtxt->fnDlgProc == NULL)
		return -3;
	if (hwDlgCal != NULL)
		return -4;

	if (lpContext)
	{
		lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 2);
		DestroyWindow(lpContext->hwClient);
		lpContext->hwClient = NULL;
	}

	hwDlgCal = CreateDialogParam(hMod, MAKEINTRESOURCE(IDD_CALWND), hwMainWnd, &DlgProc_Cal, (LPARAM)lpDlgCtxt);

	ShowWindow(hwDlgCal, SW_SHOWNORMAL);

	return 0;
}


//************************************
// 函数名:    InitDialogClient
// Access:    public 
// 返回值类型:   void
// 参数: HWND hDlg
// 说明: 初始化校准对话框
//************************************
void InitDialogClient(HWND hDlg)
{
	CRect rect;

	SetWindowTextW(GetDlgItem(hDlg, IDC_PREV), GetStringByIndex(L"Prev\0上一步\0後退\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg, IDC_NEXT), GetStringByIndex(L"Next\0下一步\0前進\0\0", nLangId));
	SetWindowTextW(GetDlgItem(hDlg,ID_EXIT),GetStringByIndex(L"Exit\0退出\0退出\0\0",nLangId));

	if (lpContext->lpszTitle)
		SetWindowTextW(hDlg, GetStringByIndex(lpContext->lpszTitle, nLangId));
	else
		SetWindowTextW(hDlg, GetStringByIndex(L"Calibration\0校准\0校準\0\0", nLangId));

	if (CHK_FLAGS(lpContext->dwDlgFlags, DFL_CMD_OK))
	{
		if (lpContext->lpszCmdOK)
			SetWindowTextW(GetDlgItem(hDlg, IDOK), GetStringByIndex(lpContext->lpszCmdOK, nLangId));
		else
			SetWindowTextW(GetDlgItem(hDlg, IDOK), GetStringByIndex(L"OK\0完成\0完成\0\0", nLangId));
	}

	if (lpContext->lpszCmdCancel)
		SetWindowTextW(GetDlgItem(hDlg, IDCANCEL), GetStringByIndex(lpContext->lpszCmdCancel, nLangId));
	else
		SetWindowTextW(GetDlgItem(hDlg, IDCANCEL), GetStringByIndex(L"Cancel\0取消\0取消\0\0", nLangId));


	//新添加的退出按钮;
	if (CHK_FLAGS(lpContext->dwDlgFlags, DFL_CMD_PREV) && lpContext->nDlgResId != IDD_CAL_7_1)
		ShowWindow(GetDlgItem(hDlg, ID_EXIT), SW_SHOW);
	else
		ShowWindow(GetDlgItem(hDlg, ID_EXIT), SW_HIDE);

	if (CHK_FLAGS(lpContext->dwDlgFlags, DFL_CMD_PREV))
		ShowWindow(GetDlgItem(hDlg, IDC_PREV), SW_SHOW);
	else
		ShowWindow(GetDlgItem(hDlg, IDC_PREV), SW_HIDE);

	if (CHK_FLAGS(lpContext->dwDlgFlags, DFL_CMD_NEXT))
	{
		ShowWindow(GetDlgItem(hDlg, IDC_NEXT), SW_SHOW);
		SetWindowTextW(GetDlgItem(hDlg, IDCANCEL), GetStringByIndex(L"Exit\0退出\0退出\0\0", nLangId));
	}
	else
		ShowWindow(GetDlgItem(hDlg, IDC_NEXT), SW_HIDE);

	if (CHK_FLAGS(lpContext->dwDlgFlags, DFL_CMD_OK))
		ShowWindow(GetDlgItem(hDlg, IDOK), SW_SHOW);
	else
		ShowWindow(GetDlgItem(hDlg, IDOK), SW_HIDE);

	if (lpContext->hwClient)
	{
		lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 1);
		DestroyWindow(lpContext->hwClient);
		lpContext->hwClient = NULL;
	}

	lpContext->hwClient = CreateDialogParam(hMod, MAKEINTRESOURCE(lpContext->nDlgResId), GetDlgItem(hDlg, IDC_GB), lpContext->fnDlgProc, (LPARAM)lpContext);

	if (lpContext->hwClient)
	{
		GetClientRect(GetDlgItem(hDlg, IDC_GB), rect);

		MoveWindow(lpContext->hwClient, rect.left, rect.top, rect.Width(), rect.Height(), TRUE);
		lpContext->fnDlgEvent(lpContext, DEC_ENTER, 0, 0, (LPARAM)lpContext->hwClient);
		ShowWindow(lpContext->hwClient, SW_SHOW);
	}
	else
		lpContext->fnDlgEvent(lpContext, DEC_EXCEPTION, DEC_ENTER, (LPARAM)hDlg, (LPARAM)GetLastError());

	return;
}


int UpdateDialog_Cal(PCALDLG_CTXT lpDlgCtxt, DWORD dwFlags)
{
	if (lpDlgCtxt == NULL)
		return -21;
	if (lpDlgCtxt->fnDlgEvent == NULL)
		return -22;
	if (lpDlgCtxt->fnDlgProc == NULL)
		return -23;
	if (lpContext == NULL) 
		return CreateDialog_Cal(lpDlgCtxt, dwFlags);

	lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 2);

	if (lpContext->hwClient)
	{
		DestroyWindow(lpContext->hwClient);
		lpContext->hwClient = NULL;
	}

	lpContext = lpDlgCtxt;

	if (hwDlgCal == NULL)
	{
		hwDlgCal = CreateDialogParam(hMod, MAKEINTRESOURCE(IDD_CALWND), hwMainWnd, &DlgProc_Cal, (LPARAM)lpDlgCtxt);
		if (hwDlgCal == NULL)
			return -24;
	}

	InitDialogClient(hwDlgCal);

	if (lpDlgCtxt->hwClient == NULL)
		return -25;

	return 0;
}


int DialogMsgBox_Cal(LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return MessageBoxW(hwDlgCal, lpText, lpCaption, uType);
}


int DestroyDialog_Cal(DWORD dwFlags)
{
	if (hwDlgCal == NULL)
	{
		if (lpContext)
		{
			lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);

			if (lpContext->hwClient)
			{
				DestroyWindow(lpContext->hwClient);
				lpContext->hwClient = NULL;
			}

			lpContext = NULL;
		}
		return -1;
	}

	if (lpContext == NULL)
	{
		DestroyWindow(hwDlgCal);
		hwDlgCal = NULL;
		return -2;
	}

	lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);
	DestroyWindow(hwDlgCal);
	lpContext->hwClient = NULL;
	hwDlgCal = NULL;
	lpContext = NULL;

	return 0;
}


BOOL EnableButton_Cal(DWORD dwCode, BOOL bEnable)
{
	if (hwDlgCal == NULL)
		return FALSE;

	BOOL blResult = FALSE;

	switch (dwCode)
	{
	case DEC_CMD_PREV:
		blResult = EnableWindow(GetDlgItem(hwDlgCal, IDC_PREV), bEnable);
		break;

	case DEC_CMD_NEXT:
		blResult = EnableWindow(GetDlgItem(hwDlgCal, IDC_NEXT), bEnable);
		break;

	case DEC_CMD_OK:
		blResult = EnableWindow(GetDlgItem(hwDlgCal, IDOK), bEnable);
		break;

	case DEC_CMD_CANCEL:
		blResult = EnableWindow(GetDlgItem(hwDlgCal, IDCANCEL), bEnable);
		break;
	}

	return blResult;
}


static INT_PTR CALLBACK DlgProc_Cal(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		return 0;
	case WM_INITDIALOG:
	{
		if (lParam == NULL)
			return FALSE;

		lpContext = (PCALDLG_CTXT)lParam;
		CRect Crect;
		GetWindowRect(hDlg, Crect);
		ReSizeCalDlg(hDlg, lpContext, Crect);
		InitDialogClient(hDlg);

		return TRUE;
	}
	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == BN_CLICKED)
			{
				switch (wId)
				{
				case IDOK:
					lpContext->fnDlgEvent(lpContext, DEC_CMD_OK, wParam, lParam, 0);
					return TRUE;

				case IDCANCEL:
					if (lpContext->fnDlgEvent(lpContext, DEC_CMD_CANCEL, wParam, lParam, 0))
					{
						lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);
						DestroyWindow(hwDlgCal);
						hwDlgCal = NULL;
					}
					return TRUE;

				case ID_EXIT:
					if (lpContext->fnDlgEvent(lpContext, DEC_CMD_CLOSE, wParam, lParam, 0))
					{
						lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);
						DestroyWindow(hwDlgCal);
						hwDlgCal = NULL;
					}
					return TRUE;

				case IDC_PREV:
					lpContext->fnDlgEvent(lpContext, DEC_CMD_PREV, wParam, lParam, 0);
					return TRUE;

				case IDC_NEXT:
					lpContext->fnDlgEvent(lpContext, DEC_CMD_NEXT, wParam, lParam, 0);
					return TRUE;

				}
			}
		}
	}
	break;
	case WM_CLOSE:
		if (lpContext->fnDlgEvent(lpContext, DEC_CMD_CLOSE, wParam, lParam, 0))
		{
			lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);
			DestroyWindow(hwDlgCal);
			hwDlgCal = NULL;
		}
		return TRUE;
	}

	return FALSE;
}

//************************************
// 函数名:    EnumCalDlgProc
// Access:    public 
// 返回值类型:   BOOL CALLBACK
// 参数: HWND hwnd
// 参数: LPARAM lParam
// 说明: 将校准窗口内各个控件移动位置(静态框改变大小)到合适位置;
//************************************
BOOL CALLBACK EnumCalDlgProc(HWND hwnd, LPARAM lParam)
{
	if (0 == hwnd)
		return FALSE;
	CWnd *cWnd = CWnd::FromHandle(hwnd);
	CalDlgSize *stCalDlg = (pCalDlgSize)lParam;
	CWnd *pWnd = cWnd->GetParent();
	CRect rect;
	cWnd->GetWindowRect(rect);
	pWnd->ScreenToClient(rect);
	if (GetDlgCtrlID(cWnd->GetSafeHwnd()) == IDC_GB)
		cWnd->SetWindowPos(0, 0, 0, rect.Width() - stCalDlg->iDlgDeffeX, rect.Height() - stCalDlg->iDlgDeffeY, SWP_NOZORDER | SWP_NOMOVE);
	else
		cWnd->SetWindowPos(0, rect.left - stCalDlg->iDlgDeffeX, rect.top - stCalDlg->iDlgDeffeY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);


	return TRUE;
}



//************************************
// 函数名:    ReSizeCalDlg
// Access:    public 
// 返回值类型:   BOOL
// 参数: HWND hWnd
// 参数: CRect Crect
// 说明: 根据lpDlgCtxt->nDlgResId确定子窗口大小.并枚举改变子窗口控件位置;
//************************************
BOOL ReSizeCalDlg(HWND hWnd, PCALDLG_CTXT lpDlgCtxt, CRect Crect)
{
	//获取CALWND中静态框大小做减法;
	CRect rcStaticRect;
	CalDlgSize stCalDlg;
	GetClientRect(GetDlgItem(hWnd, IDC_GB), rcStaticRect);
	stCalDlg.iDlgDeffeX = stCalDlg.iDlgDeffeY = 0;
	switch (lpDlgCtxt->nDlgResId)
	{
		stCalDlg.rcStaticSize = rcStaticRect;
		stCalDlg.rcDlgSize = Crect;
	case IDD_CAL_1:
		stCalDlg.iDlgDeffeX = rcStaticRect.Width() - 404;
		stCalDlg.iDlgDeffeY = rcStaticRect.Height() - 176;
		EnumChildWindows(hWnd, EnumCalDlgProc, (LPARAM)&stCalDlg);
		break;
	case IDD_CAL_2:
		stCalDlg.iDlgDeffeX = rcStaticRect.Width() - 383;
		stCalDlg.iDlgDeffeY = rcStaticRect.Height() - 276;
		EnumChildWindows(hWnd, EnumCalDlgProc, (LPARAM)&stCalDlg);
		break;
	case IDD_CAL_3:
		stCalDlg.iDlgDeffeX = rcStaticRect.Width() - 566;
		stCalDlg.iDlgDeffeY = rcStaticRect.Height() - 313;
		EnumChildWindows(hWnd, EnumCalDlgProc, (LPARAM)&stCalDlg);
		break;
	case IDD_CAL_7:
		stCalDlg.iDlgDeffeX = rcStaticRect.Width() - 610;
		stCalDlg.iDlgDeffeY = rcStaticRect.Height() - 358;
		EnumChildWindows(hWnd, EnumCalDlgProc, (LPARAM)&stCalDlg);
		break;
	default:
		break;
	}
	SetWindowPos(hWnd, NULL, Crect.left, Crect.top, Crect.Width() - stCalDlg.iDlgDeffeX, Crect.Height() - stCalDlg.iDlgDeffeY, SWP_NOZORDER | SWP_NOMOVE);
	return TRUE;
}

