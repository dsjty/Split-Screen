#pragma once
#include "stdafx.h"
#include "TDItem.h"
#include "externs.h"


#define WIDTH_SOFTMENU_MIN          208				//����ȡֵ��������(N-0.5)/1.25Ϊ����...��Ϊ�����ڳ��������жϾ���...
#define WIDTH_SOFTMENU_MAX          240
#define WIDTH_SOFTMENU              WIDTH_SOFTMENU_MIN

#define WIDTH_SUBMENU               90

#define HEIGHT_DIFF_SOFTMENU        18

// TDMenu

class TDMenu : public CWnd
{
	DECLARE_DYNAMIC(TDMenu)

public:
	TDMenu();
	virtual ~TDMenu();

public:
	void DSM_Title(CDC *hDC, const LPPAINTSTRUCT lpps);
	void DSM_TagPage(CDC *hDC, const LPPAINTSTRUCT lpps);
	void DrawSolidEdge(CDC *hDC, LPRECT lpRect, HBITMAP hFillBrush, int nFlags, LPCWSTR lpWStr);
	int DrawStretchBitmap(CDC *hDC, CBitmap *hBitmap, LPCRECT lpRect);
	void UpdateSoftMenu();
	void SoftMenu_Switch(PSOFT_MENU lpSoftMenu, DWORD dwNewIndex, DWORD dwFlags);


protected:
	DECLARE_MESSAGE_MAP()


private:
	SOFT_MENU smCurMenu;
	SOFT_TAG_PAGE stCurTagPage;
	SOFT_SUB_ITEM ssiCurItem;

	HWND hwMenuWnd;
	LOGFONT logFont = { 0 };
	SOFT_MENU MenuStack[2] = { menuRoot };
	WORD wWidth_SoftMenu = WIDTH_SOFTMENU;
	WORD wHeight_SoftMenu = 0;
	TDItem *tdItem = 0;
	BOOL blCapture = FALSE;

	CRect rcMenuButton, rcRetButton;
	int nClickState = 0;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);


};

