#pragma once

//CWnd����
CWnd *cwMainWnd = (CWnd *)NULL;

//E5070�����ھ��
HWND hwMainWnd = NULL;

//��˵����ھ��
TDMenu *cwMenuWnd, *cwMenuWnd2;
HWND hwSoftMenu = NULL;
HWND hwSoftMenu2 = NULL;

HMODULE hMod = NULL;
static int nInputType = 0;
static HWND hWnd_PopWnd = NULL, hInputEdit = NULL, hBtnEnter = NULL, hBtnClose = NULL, hUpDn1 = NULL, hUpDn2 = NULL;
CalKit cCalkit;



static PSOFT_SUB_ITEM lpInputItem = NULL;
static WNDPROC wpfn_InputEdit = NULL;
static WNDPROC wpfn_InputBox = NULL;
static WNDPROC wpfn_ComboBox = NULL;


void SetInputType(int nNewType);
void SetInputItem(PSOFT_SUB_ITEM lpSubItem);



//�ӿؼ� :: ����λ��
int SubCtrl_Button_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_RadioButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_CheckButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_InputButton_UpdatePos(PSOFT_SUB_ITEM lpMe);
int SubCtrl_ComboButton_UpdatePos(PSOFT_SUB_ITEM lpMe);

//�ӿؼ� :: ����
int SubCtrl_Button_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_RadioButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_CheckButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_InputButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);
int SubCtrl_ComboButton_Create(HWND hWnd, PSOFT_SUB_ITEM lpMe, int x, int y, int nWidth, int nHeight);

//�ӿؼ� :: ����¼�
LRESULT SubCtrl_Button_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_RadioButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_CheckButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_InputButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);
LRESULT SubCtrl_ComoboButton_OnClicked(PSOFT_SUB_ITEM lpSubItem, HWND hWnd);

