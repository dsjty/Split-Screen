#pragma once

#include "TDMenu.h"
#include "TDItem.h"
#include "CalKit.h"

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
static int nInputType = 0;
static HWND hWnd_PopWnd = NULL, hInputEdit = NULL, hBtnEnter = NULL, hBtnClose = NULL, hUpDn1 = NULL, hUpDn2 = NULL;
CalKit cCalkit;

WORD wWidth_MainWnd, wHeight_MainWnd, wWidth_Toolbar;
HHOOK hhkcwrp_MainWnd, hhkcwp_MainWnd;
HWND hwToolbar;
DWORD dwTopHeight;
DWORD *lpdwTopHeight;


static PSOFT_SUB_ITEM lpInputItem = NULL;
static WNDPROC wpfn_InputEdit = NULL;
static WNDPROC wpfn_ComboBox = NULL;


void SetInputType(int nNewType);
void SetInputItem(PSOFT_SUB_ITEM lpSubItem);

LRESULT CALLBACK wp_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wp_InputBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//子控件 :: 更新位置
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_RadioButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_CheckButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_ComboButton_UpdatePos(PSOFT_SUB_ITEM lpMe);

//子控件 :: 创建
int SubCtrl_Button_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_RadioButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_CheckButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_InputButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_ComboButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);

//子控件 :: 点击事件
LRESULT SubCtrl_Button_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_RadioButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_CheckButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_InputButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_ComoboButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);

