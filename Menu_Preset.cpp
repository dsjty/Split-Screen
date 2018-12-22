#include "stdafx.h"
extern bool bPreset;

//复位子条目
SOFT_SUB_ITEM subitemPreset[] =
{
	{
		SIF_ORIGCLICK | SIF_NOT_ENTER,
		SIA_FULLLINE,
		SIS_ButtonEx,
		0,
		L"Preset\0复位\0復位\0\0",
		NULL,
		BtnWidth_W,
		BtnHeith_H,
		NULL,
		RESERVE_DWORD16,
		RESERVE_DWORD16,
		INVALID_INDEX,
		NULL,
		NULL,
		TA_PRESET,
		CA_PRESET,
		0,
		NULL,
		RESERVE_DWORD4,
		RESERVE_DWORD4
	}
};

//复位子菜单
SOFT_TAG_PAGE submenuPreset[] =
{
	{
		0,
		0,
		L"Preset\0复位\0復位\0\0",
		NULL,
		sizeof(subitemPreset) / sizeof(SOFT_SUB_ITEM),
		subitemPreset,
		RESERVE_DWORD4,
		NULL,
		NULL,
		0,
		{ L"::/Setting_Control_Functions/Setting_the_preset_function.htm", 0, 0, 0 }
	}
};

//复位主菜单
SOFT_MENU menuPreset =
{
	0,
	0,
	L"Preset\0复位\0復位\0\0",
	NULL,
	sizeof(submenuPreset) / sizeof(SOFT_TAG_PAGE),
	submenuPreset,
	NULL,
	NULL,
	0,
	RESERVE_DWORD4
};


INT_PTR CALLBACK fndpPreset(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SetWindowTextW(GetDlgItem(hDlg, IDC_LBL_TEXT),
			GetStringByIndex(L"Preset operation will result in data reset, you sure you want to Preset it?\0"
			L"复位操作将导致数据重置, 您确定要复位吗?\0復位操作將導致數據重置, 您確定要復位嗎?\0\0", nLangId));

		SetWindowTextW(GetDlgItem(hDlg, IDYES), GetStringByIndex(L"Confirm Preset\0确认复位\0確認復位\0\0", nLangId));
		SetWindowTextW(GetDlgItem(hDlg, IDNO), GetStringByIndex(L"Do not Preset\0不复位\0不復位\0\0", nLangId));
		return TRUE;

	case WM_COMMAND:
	{
		WORD wId = LOWORD(wParam), wNc = HIWORD(wParam);

		if (lParam)
		{
			if (wNc == BN_CLICKED)
			{
				switch (wId)
				{
				case IDYES:
					EndDialog(hDlg, IDYES);
					break;

				case IDNO:
					EndDialog(hDlg, IDNO);
					break;
				}
				break;
			}
		}
	}
	break;

	case WM_CLOSE:
		EndDialog(hDlg, IDCLOSE);
		break;

	}

	return FALSE;
}

void ConfirmPreset()
{
	if (DialogBox(hMod, MAKEINTRESOURCE(IDD_PRESET), hwMainWnd, &fndpPreset) == IDYES)
	{		
		OrigSoftMenu_ItemClicked2(CA_PRESET, TA_PRESET, 0);
		SoftMenu_Reset();
	}
	bPreset = FALSE;
}