#pragma once

#include "TDMenu.h"
#include "TDItem.h"
#include "CalKit.h"

#define PORTNUM										2		//�����˿���


//��ǰ��Ĳ˵�����
extern unsigned int uiCurFocusMenu;

//CWnd����
extern CWnd *cwMainWnd;

//E5070�����ھ��
extern HWND hwMainWnd;

//��˵����ھ��
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

//��¼���������ߵ�����ֵ;
extern CRect crWnd1Rect, crWnd2Rect;

static int nInputType = 0;
static HWND hWnd_PopWnd = NULL, hInputEdit = NULL, hBtnEnter = NULL, hBtnClose = NULL, hUpDn1 = NULL, hUpDn2 = NULL;

static PSOFT_SUB_ITEM lpInputItem = NULL;
static WNDPROC wpfn_InputEdit = NULL;
static WNDPROC wpfn_ComboBox = NULL;


void SetInputType(int nNewType);
void SetInputItem(PSOFT_SUB_ITEM lpSubItem);

//�ӿؼ� :: ����λ��
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_ComboButton_UpdatePos(PSOFT_SUB_ITEM lpMe);