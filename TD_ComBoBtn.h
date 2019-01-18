#pragma once


// TD_ComBoBtn

class TD_ComBoBtn : public CComboBox
{
	DECLARE_DYNAMIC(TD_ComBoBtn)

public:
	TD_ComBoBtn(PSOFT_SUB_ITEM m);
	virtual ~TD_ComBoBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnCbnSelchange();

private: 
	SOFT_SUB_ITEM m_sSubItem;
};


