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
	void OnDrawItem_Button(LPDRAWITEMSTRUCT lpDIS, PSOFT_SUB_ITEM lpSubItem);	//������Ŀ�Ĺ��� (��ť����,��ѡ����ʽ,��չ��ǩ��)
	int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage);
	BOOL SoftItem_IsActive(PSOFT_SUB_ITEM lpSubItem);
	LRESULT OnCommand_Button(PSOFT_SUB_ITEM lpSubItem, int nItemIndex, int nCode, HWND hWnd);
	int TagPage_DestroyItems(BOOL blLeave);	//���ٵ�ǰ��ǩҳ��������Ŀ (blLeave �Ƿ�����뿪����)
	int TagPage_OnEnter();		//��ǩҳ�����¼�
	int SoftItem_SetFocus(DWORD dwNewFocus, DWORD dwNewFlags);	//������˵���Ŀ�Ľ���
	int SoftItem_ScrollFocus();
	void SoftItem_ActivationItem(PSOFT_SUB_ITEM lpSubItem);//���ü�����Ŀ��index
	void SoftItem_SetActiveSoftItem(DWORD dwIndex);
	DWORD GetCurrentSoftItemIndex(PSOFT_SUB_ITEM lpSubItem);
	PSOFT_SUB_ITEM GetGroupHeader(PSOFT_SUB_ITEM lpSubItem);
	DWORD GetGroupOffsetIndex(PSOFT_SUB_ITEM lpSubItem);
	int SoftItem_SetFocusValue(DWORD dwNewFocus, DWORD dwNewFlags);

	int SoftItem_PrevItem();	//���ý��㵽��ǰ�����ǰһ���ؼ���
	int SoftItem_NextItem();	//���ý��㵽��ǰ����ĺ�һ���ؼ���
	
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


