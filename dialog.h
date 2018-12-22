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


typedef INT_PTR(WINAPI *func_CalDlgEvent)(struct _CALDLG_CONTEXT *lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2);

//Dialog Flags  对话框标志位
//启用对话框框架的静态标签1
#define DFL_LBL_INFO1               0x00000001

//启用对话框框架的静态标签2
#define DFL_LBL_INFO2               0x00000002

//启用对话框框架的上一步按钮
#define DFL_CMD_PREV                0x00000004

//启用对话框框架的下一步按钮
#define DFL_CMD_NEXT                0x00000008

//启用对话框框架的用户自定义按钮1
#define DFL_CMD_UD1                 0x00000010

//启用对话框框架的用户自定义按钮2
#define DFL_CMD_UD2                 0x00000020

//启用对话框框架的确认按钮
#define DFL_CMD_OK                  0x00000040

//对话框框架的取消按钮为必显示的按钮


//Dialog Event Code   对话框事件代码

//对话框进入
#define DEC_ENTER                   0
//对话框离开
#define DEC_LEAVE                   1
//对话框异常
#define DEC_EXCEPTION               3
//对话框激活
#define DEC_ACTIVE                  4


//对话框用户自定义按钮1被点击
#define DEC_CMD_UD1                 11

//对话框用户自定义按钮2被点击
#define DEC_CMD_UD2                 12

//对话框上一步按钮被点击
#define DEC_CMD_PREV                13

//对话框下一步按钮被点击
#define DEC_CMD_NEXT                14

//对话框确认按钮被点击
#define DEC_CMD_OK                  15

//对话框取消按钮被点击  (回调函数返回TRUE才会销毁对话框)
#define DEC_CMD_CANCEL              16

//对话框被关闭  (回调函数返回TRUE才会销毁对话框)
#define DEC_CMD_CLOSE               17

//校准对话框上下文
typedef struct _CALDLG_CONTEXT
{
  HWND                              hwClient;         //对话框被创建后的句柄
  int                               nDlgResId;        //对话框在NACore.dll的资源Id
  DWORD                             dwDlgFlags;       //对话框属性标志
  func_CalDlgEvent                  fnDlgEvent;       //内嵌对话框事件处理回调函数
  DLGPROC                           fnDlgProc;        //内嵌对话框窗口过程
  struct _CALDLG_CONTEXT          * lpLast;           //Reserve 保留
  void                            * lpReserve;
  void                            * lpReserve2;
  const WCHAR                     * lpszTitle;
  const WCHAR                     * lpszGroupTitle;
  const WCHAR                     * lpszLblInfo1;
  const WCHAR                     * lpszLblInfo2;
  const WCHAR                     * lpszCmdUD1;
  const WCHAR                     * lpszCmdUD2;
  const WCHAR                     * lpszCmdOK;
  const WCHAR                     * lpszCmdCancel;
  RECT                              rcWnd;
  DWORD                             dwReserve[4];
} CALDLG_CTXT, *PCALDLG_CTXT;

//对话框事件回调函数原型
typedef INT_PTR(WINAPI *func_DlgEvent)(struct _DIALOG_CONTEXT *lpDlgCtxt, DWORD dwCode, WPARAM wParam, LPARAM lParam, LPARAM lParam2);

//Dialog Flags

//Dialog Event Code
//参考上面的Dialog Event Code

typedef struct _DIALOG_CONTEXT
{
	HWND                              hwThis;
	int                               nDlgResId;
	DWORD                             dwDlgFlags;
	func_DlgEvent                     fnDlgEvent;
	DLGPROC                           fnDlgProc;
	RECT                              rcWnd;
} DLG_CTXT, *PDLG_CTXT;


