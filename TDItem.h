#pragma once
#include "stdafx.h"
// TDItem

class TDItem : public CWnd
{
	DECLARE_DYNAMIC(TDItem)

public:
	TDItem();
	TDItem(PSOFT_TAG_PAGE CurTagPage);
	virtual ~TDItem();

public:
	int TagPage_UpdateItemsPos();
	void OnDrawItem_Button(int nCtrlId, LPDRAWITEMSTRUCT lpDIS, PSOFT_SUB_ITEM lpSubItem);	//绘制项目的过程 (按钮背景,复选框样式,扩展标签等)
	int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage);
	BOOL SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem);
	LRESULT OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd);
	int TagPage_DestroyItems(BOOL blLeave);	//销毁当前标签页的所有项目 (blLeave 是否调用离开函数)
	int TagPage_OnEnter();		//标签页进入事件




private:
	SOFT_TAG_PAGE stCurTagPage;
	WORD wWidth_SoftItem = 0, wHeight_SoftItem = 0;
	CRect rcItem, rcLastItem;
	DWORD dwFocusItem = 0;
	std::vector<SOFT_SUB_ITEM> ssSumItem;
	WNDPROC wpfn_InputBox = NULL;


protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


