#pragma once

#include "config.h"

#if CF_DISABLE_WARN
#pragma warning (disable : 4553 4800 4733 4477 4244 4101 4996)
#endif

#ifndef ISOLATION_AWARE_ENABLED
#define ISOLATION_AWARE_ENABLED     1
#endif

#define  _WIN32_WINNT               0x0501
#include "targetver.h"

/*
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
*/

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#include <afxdisp.h>        // MFC 自动化类

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif

#if !defined(_AFX_NO_AFXCMN_SUPPORT) && !defined(__AFXCMN_H__)
#include <afxcmn.h>       // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT && __AFXCMN_H__

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#ifndef _INC_WINDOWSX
#include <Windowsx.h>
#endif

#ifndef _INC_COMMCTRL
#include <commctrl.h>
#endif

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32'   name='Microsoft.Windows.Common-Controls'   version='6.0.0.0'   processorArchitecture='x86'   publicKeyToken='6595b64144ccf1df'   language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32'   name='Microsoft.Windows.Common-Controls'   version='6.0.0.0'   processorArchitecture='*'   publicKeyToken='6595b64144ccf1df'   language='*'\"")
#endif

#define WM_SWITCH_SUBMENU                   WM_USER + 20
#define WM_TEST_FP                          WM_USER + 21
#define WM_FINETUNE                         WM_USER + 22
#define WM_REFRESH							WM_USER	+ 23
#define WM_UPDATEMENU							WM_USER	+ 24
#define NAKED                               __declspec(naked)
#define RESERVE_DWORD4                      { 0, 0, 0, 0} 
#define RESERVE_DWORD8                      { 0, 0, 0, 0, 0, 0, 0, 0} 
#define RESERVE_DWORD16                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} 


#include "resource.h"
#include "defines.h"
#include "dialog.h"
#include "softmenu.h"
#include "popwnd.h"
#include "toolbar.h"
#include "externs.h"
#include "inline.h"
#include "CalKit.h"
#include "TDMenu.h"
#include "TDItem.h"
#include "SharedData.h"