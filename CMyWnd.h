#pragma once


class CMyWnd : CWnd
{
public:
  BOOL __thiscall Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /* = NULL */);

};

typedef BOOL (CMyWnd::* CMyWnd__Create) (LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /* = NULL */);

typedef CWnd __CWnd;