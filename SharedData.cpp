#include "stdafx.h"


//��ǰ��Ĳ˵�����
unsigned int uiCurFocusMenu = 1;

//CWnd����
CWnd *cwMainWnd = (CWnd *)NULL;

//E5070�����ھ��
HWND hwMainWnd = NULL;

//��˵����ھ��
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