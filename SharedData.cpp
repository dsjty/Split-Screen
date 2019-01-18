#include "stdafx.h"


//当前活动的菜单窗口
unsigned int uiCurFocusMenu = 1;

//CWnd对象
CWnd *cwMainWnd = (CWnd *)NULL;

//E5070主窗口句柄
HWND hwMainWnd = NULL;

//软菜单窗口句柄
TDMenu *cwMenuWnd, *cwMenuWnd2;
HWND hwSoftMenu = NULL;
HWND hwSoftMenu2 = NULL;

HMODULE hMod = NULL;
CalKit cCalkit;

WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_Toolbar;
HHOOK hhkcwrp_MainWnd, hhkcwp_MainWnd;
HWND hwToolbar;
DWORD dwTopHeight;
DWORD *lpdwTopHeight;

//SoftMenu Width
WORD wWidth_SoftMenu = WIDTH_SOFTMENU;
WORD wHeight_SoftMenu = 0;