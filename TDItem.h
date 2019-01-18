#pragma once

#include "stdafx.h"
#include "TD_Button.h"
#include <vector>
// TDItem

class TDItem : public CWnd
{
	DECLARE_DYNAMIC(TDItem)

public:
	TDItem();
	TDItem(PSOFT_TAG_PAGE CurTagPage,int iSer);
	virtual ~TDItem();

public:
	int TagPage_UpdateItemsPos();
	int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage);
	BOOL SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem);
	LRESULT OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd);
	int TagPage_DestroyItems(BOOL blLeave);	//销毁当前标签页的所有项目 (blLeave 是否调用离开函数)
	int TagPage_OnEnter();		//标签页进入事件
	int SoftItem_SetFocus(DWORD dwNewFocus, DWORD dwNewFlags);	//设置软菜单条目的焦点
	int SoftItem_ScrollFocus();
	void SoftItem_ActivationItem(PSOFT_SUB_ITEM lpSubItem);//设置激活项目的index
	void SoftItem_SetActiveSoftItem(DWORD dwIndex);
	void SoftItem_ActivationItemByOffsetIndex(PSOFT_SUB_ITEM lpSubItem, int nOffsetIndex);
	DWORD GetCurrentSoftItemIndex(PSOFT_SUB_ITEM lpSubItem);
	PSOFT_SUB_ITEM GetGroupHeader(PSOFT_SUB_ITEM lpSubItem);
	DWORD GetGroupOffsetIndex(PSOFT_SUB_ITEM lpSubItem);
	int SoftItem_SetFocusValue(DWORD dwNewFocus, DWORD dwNewFlags);

	int SoftItem_PrevItem();	//设置焦点到当前焦点的前一个控件上
	int SoftItem_NextItem();	//设置焦点到当前焦点的后一个控件上
	
	PSOFT_SUB_ITEM GetItemByIndex(int nIndex);
	
	int SubCtrl_Button_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
	int SubCtrl_RadioButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight); 
	int SubCtrl_CheckButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
	int SubCtrl_ComboButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
	int SubCtrl_InputButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);


private:
	UINT const uiCurMenus;
	SOFT_TAG_PAGE stCurTagPage;
	std::vector<SOFT_SUB_ITEM> ssSumItem;
	std::vector<TD_Button*>vcButton;


	WORD wWidth_SoftItem = 0, wHeight_SoftItem = 0;
	CRect rcItem, rcLastItem;
	DWORD dwFocusItem = 0, dwLastFocus = 0;
	DWORD dwFocusFlags = 0;

private://radio button
	int iValueforRadioID = 0;
	int iRadioCurSel[5] = { 0 };

protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

};


