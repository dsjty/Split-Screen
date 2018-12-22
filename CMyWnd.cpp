#include "stdafx.h"

int ef_CMyWnd__Create = NULL;
CMyWnd__Create org_CMyWnd__Create = NULL;

BOOL __thiscall CMyWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /* = NULL */)
{
  void * lpRet = _ReturnAddress();
  char szTemp[MAX_PATH];

  if (lpRet != (void *)0x004A8D5B)
  {
    if (org_CMyWnd__Create)
      return (this->*org_CMyWnd__Create)(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
    else
      return FALSE;
  }

  sprintf_s(szTemp, MAX_PATH, "dwStyle: %d\r\nrect.left: %d\r\nrect.top: %d\r\npContext: %p\r\n", dwStyle, rect.left, rect.top, pContext);
  MessageBoxA(pParentWnd->m_hWnd, szTemp, "Info", MB_OK);

  return (this->*org_CMyWnd__Create)(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}