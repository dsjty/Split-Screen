#include "stdafx.h"

static HWND hwDlg = NULL;
static PDLG_CTXT lpContext = NULL;

int CreateDialog_Def(PDLG_CTXT lpDlgCtxt, DWORD dwFlags)
{
	if (lpDlgCtxt == NULL)
		return -1;
	if (lpDlgCtxt->fnDlgEvent == NULL)
		return -2;
	if (lpDlgCtxt->fnDlgProc == NULL)
		return -3;
	if (hwDlg != NULL)
		return -4;

	if (lpContext)
	{
		lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 2);
		DestroyWindow(lpContext->hwThis);
		lpContext->hwThis = NULL;
	}

	hwDlg = CreateDialogParam(hMod, MAKEINTRESOURCE(lpDlgCtxt->nDlgResId), hwMainWnd, lpDlgCtxt->fnDlgProc, (LPARAM)lpDlgCtxt);

	if (hwDlg)
	{
		lpContext = lpDlgCtxt;
		lpDlgCtxt->fnDlgEvent(lpDlgCtxt, DEC_ENTER, 0, 0, (LPARAM)hwDlg);
		ShowWindow(hwDlg, SW_SHOWNORMAL);
	}

	return 0;
}

int DestroyDialog_Def(DWORD dwFlags)
{
	if (hwDlg == NULL)
	{
		if (lpContext)
		{
			lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);

			if (lpContext->hwThis)
			{
				DestroyWindow(lpContext->hwThis);
				lpContext->hwThis = NULL;
			}

			lpContext = NULL;
		}
		return -1;
	}

	if (lpContext == NULL)
	{
		DestroyWindow(hwDlg);
		hwDlg = NULL;
		return -2;
	}

	lpContext->fnDlgEvent(lpContext, DEC_LEAVE, 0, 0, 0);
	DestroyWindow(hwDlg);
	lpContext->hwThis = NULL;
	hwDlg = NULL;
	lpContext = NULL;

	return 0;
}


