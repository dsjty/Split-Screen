#pragma once


// TD_Button

class TD_Button : public CMFCButton
{
	DECLARE_DYNAMIC(TD_Button)

public:
	TD_Button();
	TD_Button(PSOFT_SUB_ITEM m);
	virtual ~TD_Button();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetEXLBLToAttributes(PSOFT_SUB_ITEM lpSub);

	LRESULT SubCtrl_CheckButton_OnClicked();
	LRESULT SubCtrl_InputButton_OnClicked();

	void SetSoftSubItem(PSOFT_SUB_ITEM m_SSI);

private:
	PSOFT_SUB_ITEM m_ssItem;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


