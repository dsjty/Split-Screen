#pragma once


// TD_Edit

class TD_Edit : public CEdit
{
	DECLARE_DYNAMIC(TD_Edit)

public:
	TD_Edit(PSOFT_SUB_ITEM m_ssItem);
	virtual ~TD_Edit();

protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	PSOFT_SUB_ITEM lpSubItem;
};


