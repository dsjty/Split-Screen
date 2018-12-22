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


typedef int(WINAPI *func_tbEvent)(DWORD dwCode, WPARAM wParam, LPARAM lParam, HWND hToolbar, struct _SOFT_TOOLBAR_ITEM *lptbItem);
typedef int(WINAPI *func_tbMenuEvent)(DWORD dwMenuId, struct _SOFT_TOOLBAR_ITEM *lptbItem);

#define STBF_MENUEVENT        0x00000001
#define STBF_ICON             0x00000002
#define STBF_BITMAP           0x00000004


#define STBS_BUTTON           1

#define TBEC_CLICKED          1

//工具栏条目结构体
typedef struct _SOFT_TOOLBAR_ITEM
{
  HWND                hwCtrl;

  union
  {
    HANDLE            hImage;
    HICON             hIcon;
    HBITMAP           hBitmap;
  };

  int                 nImageId;
  DWORD               dwFlags;
  DWORD               dwStyle;
  void              * lParam;
  void              * lParam2;
  func_tbEvent        fnEvent;
  LPCWSTR             lpHelpText;
  LONG                lngWndId;
  int                 nWidth;
  RECT                rect;
  DWORD               dwReserve[4];
} SOFT_TB_ITEM, *PSOFT_TB_ITEM;