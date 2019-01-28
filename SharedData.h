#pragma once

#include "TDMenu.h"
#include "TDItem.h"
#include "CalKit.h"

#define PORTNUM										2		//机器端口数


//当前活动的菜单窗口
extern unsigned int uiCurFocusMenu;

//CWnd对象
extern CWnd *cwMainWnd;

//E5070主窗口句柄
extern HWND hwMainWnd;

//软菜单窗口句柄
extern TDMenu *cwMenuWnd, *cwMenuWnd2;
extern HWND hwSoftMenu;
extern HWND hwSoftMenu2;

extern HMODULE hMod;
extern CalKit cCalkit;

extern WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_Toolbar;
extern HHOOK hhkcwrp_MainWnd, hhkcwp_MainWnd;
extern HWND hwToolbar;
extern DWORD dwTopHeight;
extern DWORD *lpdwTopHeight;


//SoftMenu Width
extern WORD wWidth_SoftMenu;
extern WORD wHeight_SoftMenu;

//记录主窗口两边的坐标值;
extern CRect crWnd1Rect, crWnd2Rect;

static int nInputType = 0;
static HWND hWnd_PopWnd = NULL, hInputEdit = NULL, hBtnEnter = NULL, hBtnClose = NULL, hUpDn1 = NULL, hUpDn2 = NULL;

static PSOFT_SUB_ITEM lpInputItem = NULL;
static WNDPROC wpfn_InputEdit = NULL;
static WNDPROC wpfn_ComboBox = NULL;


void SetInputType(int nNewType);
void SetInputItem(PSOFT_SUB_ITEM lpSubItem);

//子控件 :: 更新位置
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_ComboButton_UpdatePos(PSOFT_SUB_ITEM lpMe);