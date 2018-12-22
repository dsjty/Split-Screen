#pragma once

#ifndef _INC_WINDOWS
#include <Windows.h>
#endif

#ifndef _INC_WINDOWSX
#include <Windowsx.h>
#endif

#ifndef _INC_COMMCTRL
#include <commctrl.h>
#endif


typedef struct _POPWND_UPDATEPROCSTRUCT
{
  struct _SOFT_SUB_ITEM         * lpSubItem;
  void                          * lpInput;
  LPCWSTR                         lpTitle;
  LPWSTR                          lpwcsSuffix;
  DWORD                           dwFlags;
} PWUPS, *PPWUPS;

typedef int(WINAPI *func_PopWndUpdateProc)(struct _SOFT_SUB_ITEM *lpSubItem, PPWUPS lpPWUPS, DWORD dwFlags);

int PopWnd_PopupInputBox(HWND hParent, LPCWSTR lpTitle, void *lpInput, PSOFT_SUB_ITEM lpSubItem, DWORD dwFlags);
void PopWnd_UpdateInputBox();
void PopWnd_SetTitleSuffix(LPCWSTR lpSuffix);

BOOL PopWnd_Destroy(PSOFT_SUB_ITEM lpSubItem, BOOL blForce);//销毁浮动输入框
BOOL PopWnd_IsFocus();
int PopWnd_Finetune(BOOL blFinetune2, int nDelta, int nCount);
