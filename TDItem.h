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
	void OnDrawItem_Button(LPDRAWITEMSTRUCT lpDIS, PSOFT_SUB_ITEM lpSubItem);	//绘制项目的过程 (按钮背景,复选框样式,扩展标签等)
	int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage);
	BOOL SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem);
	LRESULT OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd);
	int TagPage_DestroyItems(BOOL blLeave);	//销毁当前标签页的所有项目 (blLeave 是否调用离开函数)
	int TagPage_OnEnter();		//标签页进入事件
	int SoftItem_SetFocus(DWORD dwNewFocus, DWORD dwNewFlags);	//设置软菜单条目的焦点
	int SoftItem_ScrollFocus();
	void SoftItem_ActivationItem(PSOFT_SUB_ITEM lpSubItem);//设置激活项目的index
	void SoftItem_SetActiveSoftItem(DWORD dwIndex);
	DWORD GetCurrentSoftItemIndex(PSOFT_SUB_ITEM lpSubItem);
	PSOFT_SUB_ITEM GetGroupHeader(PSOFT_SUB_ITEM lpSubItem);
	DWORD GetGroupOffsetIndex(PSOFT_SUB_ITEM lpSubItem);
	int SoftItem_SetFocusValue(DWORD dwNewFocus, DWORD dwNewFlags);

	int SoftItem_PrevItem();	//设置焦点到当前焦点的前一个控件上
	int SoftItem_NextItem();	//设置焦点到当前焦点的后一个控件上
	
	PSOFT_SUB_ITEM GetItemByIndex(int nIndex);
	

private:
	SOFT_TAG_PAGE stCurTagPage;
	std::vector<SOFT_SUB_ITEM> ssSumItem;

	WORD wWidth_SoftItem = 0, wHeight_SoftItem = 0;
	CRect rcItem, rcLastItem;
	DWORD dwFocusItem = 0, dwLastFocus = 0;
	DWORD dwFocusFlags = 0;
	WNDPROC wpfn_InputBox = NULL;


protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


