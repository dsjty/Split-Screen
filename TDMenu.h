#pragma once

#include "stdafx.h"
#include "TDItem.h"
#include "externs.h"


#define WIDTH_SOFTMENU_MIN          240
#define WIDTH_SOFTMENU              WIDTH_SOFTMENU_MIN

#define WIDTH_SUBMENU               90

#define HEIGHT_DIFF_SOFTMENU        18

// TDMenu

class TDMenu : public CWnd
{
	DECLARE_DYNAMIC(TDMenu)

public:
	TDMenu();
	TDMenu(int const iSer);

	virtual ~TDMenu();

public:
	void DSM_Title(CDC *hDC, const LPPAINTSTRUCT lpps);
	void DSM_TagPage(CDC *hDC, const LPPAINTSTRUCT lpps);
	void DrawSolidEdge(CDC *hDC, LPRECT lpRect, HBITMAP hFillBrush, int nFlags, LPCWSTR lpWStr);
	void UpdateSoftMenu();
	void SoftMenu_Switch(PSOFT_MENU lpSoftMenu, DWORD dwNewIndex, DWORD dwFlags);
	void SoftMenu_Reset();
	void SoftMenu_Pop();
	int TagPage_SetIndex(DWORD dwNewIndex);//���õ�ǰ��˵��м���ı�ǩҳindex
	HWND GetItemHwnd();		//��ȡ�˵����ڵ�hwnd
	PSOFT_SUB_ITEM GetSoftSubItem(int index);
	int GetCurrMenuSer();
	PSOFT_TAG_PAGE GetCurTagPage();




protected:
	DECLARE_MESSAGE_MAP()


public:
	TDItem *tdItem = NULL;
private:
	unsigned int const uiCurMenu;
	PSOFT_MENU smCurMenu;
	PSOFT_TAG_PAGE stCurTagPage;
	PSOFT_SUB_ITEM ssCurItem;

	HWND hwMenuWnd;
	LOGFONT logFont = { 0 };

	SOFT_MENU MenuStack[2] = { menuRoot };		//�˵�ջ
	std::vector<SOFT_TAG_PAGE> vcTagList;		//��ǰtag�б�

	BOOL blCapture = FALSE;

	CRect rcMenuButton, rcRetButton;
	int nClickState = 0;	//�Ի�ؼ���״̬ State
	int iCurMenuSer = 0;
	int iLastMenuSer = 0;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


