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

#include "misc.h"

extern HMODULE hMainMod;
extern HMODULE hMod;
extern ATOM wcSoftMenu;
extern ATOM wcSoftItem;
extern ATOM wcToolBar;
extern int nLangId;
extern int nTraces;
extern int nChannels;


extern HOOK_PTR HookPtr[];
extern CWnd *cwMainWnd;
extern CWnd *cwDrawRect;

extern HWND hwSoftMenu, hwSoftMenu2;
extern HWND hwSoftItem;
extern HWND hwToolbar;
extern HWND hwMainWnd;

//window hook 句柄
extern HHOOK hhkcwp_MainWnd;

extern HBITMAP hBmp_Button1, hBmp_Button1s, hBmp_Button2, hBmp_ButtonR, hBmp_ButtonU, hBmp_Button2s, hBmp_ButtonF;
extern HBITMAP hBmp_Checked, hBmp_Unchecked;

//菜单栈
extern SOFT_MENU menuRoot;
extern PSOFT_MENU lpMenuStack[256];
extern BYTE btMenuIndex;
extern DWORD dwTagPageIndex;

void wndTDRCHK();
int ResetHookPointer(HOOK_PTR lpHookPtr);
BOOL SetOffsetHook(int *lpOffset, int *lpOldAddress, int nAddress);
BOOL SetPointer(int *lpOffset, int *lpOldPointer, int nAddress);

//获取子菜单的指针
void *GetSubMenuPointer(void *lpThis, int nIndex);

bool GetButtonCheckState(void * lpBtnState, int nIndex);

//模拟__thiscall的2种函数
int WINAPI DirectCall(void *lpThis, void *lpFunction);
int WINAPI DirectCall_2(void *lpThis, void *lpFunction, int nIndex);

LPCSTR GetStringByIndexA(LPCSTR lpStr, int nIndex);
LPCWSTR GetStringByIndex(LPCWSTR lpWStr, int nIndex);
LPCWSTR GetStringByIndex(LPCWSTR lpWStr, int nIndex, int lParam);

int GetButtonStateIndex(const char *lpszCmd, void *lpUnk, int *lpIndex, int nVars);

int GetCommandVariant_Dbl(const char *lpszCmd, void *lpVTable, void *lpVTable2, void *lpUnk, double *lpDbl);


int FmtValueToString(void *lpInput, char *lpszBuffer, DWORD dwMaxLen, double *lpDblOut);
int FmtValueToStringEx(void *lpInput, char *lpszBuffer, DWORD dwMaxLen, double lpDblIn);
int FmtValueToStringExW(void *lpInput, LPWSTR lpszBuffer, DWORD dwMaxLen, double lpDblIn);


BOOL ScanfStringToValue(void *lpVal, LPCSTR lpszText, double *lpDbl);
BOOL ScanfStringToValueEx(void *lpInput, LPCSTR lpText, double *lpDbl);
BOOL ScanfStringToValueW(void *lpInput, LPCWSTR lpWcsText, double *lpDbl);

BOOL SetInputStringObjectW(void *lpInObj, LPCWSTR lpWcsText);

BOOL GetInputStringObjectW(void *lpInObj, LPWSTR lpWcsText, DWORD dwMaxLen, int *lpLimit);

//频标部分涉及
BOOL SetInputBtnStateIndex(void *lpBtnState, int nIndex);
BOOL GetMarkerStateIndex(void *lpBtnState, int *lpIndex, bool *lpBool, bool *lpBool2);


int OrigSoftMenu_Enter(void *lpThis);

int OrigSoftMenu_Leave(void *lpThis);

void OrigSoftMenu_ClearItems(void *lpThis);

int OrigSoftMenu_UpdateItems(void *lpThis);

int OrigSoftMenu_ItemClicked2(void *lpThis, void *lpOptVTable, int nItemIndex);

int OrigSoftMenu_GetItemState(void *lpThis, int nIndex, LPBOOL lpblEnable, LPBOOL lpblCheck, LPBOOL lpblRadio);

int GetSubMenuSelected(void *lpThis);

int GetSubMenuSelected_Radio(void *lpThis);

int GetSubMenuItemCount(void *lpThis);

LPSTR GetSubMenuItemText(void *lpThis, int nIndex);


BOOL InputFineTune(void *lpInput, double *lpDblOut, double dblCurrent, int iDelta);

BOOL InputFineTune2(void *lpInput, double *lpDblOut, double dblCurrent, int iDelta);

int TrimLeft(char *s, int nMax);
int BreakString(char *s, int nMax);
int MakeUnitStringW(void *lpInput, LPWSTR lpWText, int nMax, LPCSTR lpUnitChar);
//向E5070主窗口PostMessage 0x0432
void PSTMSG_432_2();


PSOFT_MENU GetCurrentSoftMenu();
LPCWSTR GetCurrentSoftMenuTitle();
LPCWSTR GetCurrentSoftMenuTitleByIndex(int nIndex);


void SoftItem_ActivationItem(PSOFT_SUB_ITEM lpSubItem);

void SoftItem_ActivationItemByOffsetIndex(PSOFT_SUB_ITEM lpSubItem, int nIndex);

PSOFT_SUB_ITEM SoftItem_GetFocusItem();

PSOFT_SUB_ITEM SoftItem_GetLastFocusItem();

int SoftItem_SetFocusValue(DWORD dwNewFocus, DWORD dwNewFlags);


int SoftItem_InvalidLastFocus();

int SoftItem_SetFocus(DWORD dwNewFocus, DWORD dwNewFlags);

int SoftItem_PrevItem();

int SoftItem_NextItem();

PSOFT_TAG_PAGE SoftItem_GetCurrentTagPage();

int SoftItem_Finetune(PSOFT_SUB_ITEM lpSubItem, int nDelta, int nCount);

int SoftItem_Finetune2(PSOFT_SUB_ITEM lpSubItem, int nDelta);


DWORD TagPage_AddItem(PSOFT_TAG_PAGE lpTagPage, PSOFT_SUB_ITEM lpSubItem);

DWORD TagPage_FreeItem(PSOFT_TAG_PAGE lpTagPage);

int TagPage_SetIndex(DWORD dwNewIndex);

int TagPage_Prev();

int TagPage_Next();


void SoftMenu_Reset();

void SoftMenu_Push(PSOFT_MENU lpSoftMenu);

void SoftMenu_Pop();

void SizeMainWnd(BOOL blSync);

//标签页进入事件
int TagPage_OnEnter();
//标签页离开事件
int TagPage_OnLeave();
//显示当前标签页的帮助
void * TagPage_ShowHelp(PSOFT_SUB_ITEM lpSubPage);
//销毁当前标签页的所有项目 (blLeave 是否调用离开函数)
int TagPage_DestroyItems(BOOL blLeave);
//刷新当前标签页的项目
int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage);
int TagPage_RefreshItems(PSOFT_TAG_PAGE lpTagPage, BOOL blReload);
int TagPage_RefreshItems(BOOL blReload);
//更新当前项目在窗口的相对位置
int TagPage_UpdateItemsPos(DWORD dwFlags);

//创建工具栏
int Toolbar_Create(HWND hParent);
//重绘工具栏
int Toolbar_Redraw();
//更新工具栏及子控件位置
int Toolbar_UpdateItemsPos();

//复位的确认提示
void ConfirmPreset();

//汇编转正常调用约定的入口函数
int ef_CWnd__Create();
void ef_CWnd__OnSize_main();

//更新软菜单
void UpdateSoftMenu();

/*更新工具栏及软菜单对应原版程序控件的大小
工具栏占用的原版输入框的位置
软菜单占用原版软菜单的位置

!!!仅可实现工具栏及软菜单的尺寸调整,无法实现位置的调整!!!
*/
void UpdateSize_UI();


int WINAPI fnItemSelected_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem, int nIndex);

int WINAPI fnUpdateData_GetSub_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

int WINAPI fnUpdateData_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

int WINAPI fnUpdateData_DEC_Default(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);


//void DrawSolidRect(HDC hDC, LPRECT lpRect, HBRUSH hFillBrush, int nPushed, int nFlags, LPCWSTR lpWStr);
//绘制实体Edge
void DrawSolidEdge(HDC hDC, LPRECT lpRect, HBITMAP hFillBrush,int nFlags, LPCWSTR lpWStr);
//绘制复选框
void DrawCheckBox(HDC hDC, LPRECT lpRect, HBRUSH hFillBrush, HPEN hChkPen, int nChecked, int nFlags);
//绘制并拉伸位图
int DrawStretchBitmap(HDC hDC, HBITMAP hBitmap, LPCRECT lpRect);
//ClientToScreen
BOOL ClientToScreen(HWND hWnd, LPRECT lpRect);
//选择全部文本 (Edit Control)
void SelectAllText(HWND hEdit);

 //创建对话框 校准部分
 int CreateDialog_Cal(PCALDLG_CTXT lpDlgCtxt, DWORD dwFlags);
 //更新对话框 校准部分
 int UpdateDialog_Cal(PCALDLG_CTXT lpDlgCtxt, DWORD dwFlags);
 //弹出模态消息框 校准部分
 int DialogMsgBox_Cal(LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
 //销毁对话框 校准部分
 int DestroyDialog_Cal(DWORD dwFlags);
 //启用按钮 校准部分
 BOOL EnableButton_Cal(DWORD dwCode, BOOL bEnable);

 //创建对话框 默认
 int CreateDialog_Def(PDLG_CTXT lpDlgCtxt, DWORD dwFlags);
 //销毁对话框 默认
 int DestroyDialog_Def(DWORD dwFlags);

//更新复位确认的状态
void UpdatePresetState();

//更新当前语言翻译
void UpdateCurrentLocale();


