// TD_ComBoBtn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TD_ComBoBtn.h"


// TD_ComBoBtn

IMPLEMENT_DYNAMIC(TD_ComBoBtn, CComboBox)

TD_ComBoBtn::TD_ComBoBtn(PSOFT_SUB_ITEM m):
	m_sSubItem(m)
{

}

TD_ComBoBtn::~TD_ComBoBtn()
{
}


BEGIN_MESSAGE_MAP(TD_ComBoBtn, CComboBox)
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &TD_ComBoBtn::OnCbnSelchange)
END_MESSAGE_MAP()



// TD_ComBoBtn ��Ϣ�������

void TD_ComBoBtn::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nChar)
	{
		case VK_SPACE:
			keybd_event(VK_RETURN, 0, 0, 0);
			keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
			break;

		case VK_RETURN:
			SetFocus();
			break;
	}

	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}


void TD_ComBoBtn::OnCbnSelchange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_sSubItem->dwStyle == SIS_ComboRadioButtonEx)
		SET_FLAGS(m_sSubItem->dwAttributes, SIAE_CHECKED);

	if (CHK_FLAGS(m_sSubItem->dwFlags, SIF_FN_SELECTED) && (m_sSubItem->lpEvent[FNID_SELECTED]))
	{
		func_ItemEvent_Selected fnSelected = (func_ItemEvent_Selected)m_sSubItem->lpEvent[FNID_SELECTED];

		fnSelected(0, 0, 0, m_sSubItem, GetCurSel());

		UpdateCurrentItemsAndData();
	}

}
