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

//Sub Item Flags
#define SIF_ISMENU                  0x00000001      //条目点击后是个SOFT_MENU,进入下一级菜单
#define SIF_ORIGCLICK               0x00000002      //控件点击时调用原程序的点击事件
#define SIF_SNDMSGCMD               0x00000004      //SendMessage WM_COMMAND
#define SIF_CALWND                  0x00000008      //弹出校准窗口
#define SIF_NOREPLY                 0x00000010      //不响应点击事件 (input button, check button 点击时不调用直接函数 ORIGCLICK; 存在SIF_UNCHECKFUNC时无效)
#define SIF_UNCHECKFUNC             0x00000020      //取消选中时调用另外的ORIGCLICK (checkbox) (仅频标)
#define SIF_NOT_ENTER               0x00000040      //不调用原软菜单类对象的Enter函数
#define SIF_POPINPUTWND             0x00000080      //使用弹出的浮动输入框 (仅频标)
#define SIF_DIALOG                  0x00000100      //弹出自定义对话框 (颜色向导)
#define SIF_FN_CLICKED              0x00010000      //存在额外的点击事件
#define SIF_FN_SELECTED             0x00020000      //存在条目被选中的事件 (下拉框)
#define SIF_FN_UPDATEDATA           0x00040000      //存在更新数据的事件过程
#define SIF_FN_SETFOCUS				0x00100000
#define SIF_FN_SWITCH				0x00200000		//专门应对需要在点击前获取动态this指针的。所以需要这个来指示先执行自定义函数 然后才点击

//Sub Item Attributes
#define SIA_FULLLINE                0x00000001      //条目绘制为整行 (独占一行)
#define SIA_GROUP                   0x00000002      //WS_GROUP
#define SIA_SHOWSUB                 0x00000004      //显示子菜单命中的条目
#define SIA_BITMAP                  0x00000008      //显示Image (位图按钮) (仅限ButtonEx, RadioButtonEx)
#define SIA_GETCHKSTATE             0x00000010      //在绘制时主动读取原始按钮[√]状态 (仅限用于CheckBox)
#define SIA_SETSTATEIDX             0x00000020      //在设置输入值时模拟修改按钮状态结构的索引
#define SIA_GETBTNSTATE             0x00000040      //在绘制时主动读取原始按钮[ON/OFF]状态 (仅限用于CheckBox)
#define SIA_READONLY                0x00000080      //输入框只读
#define SIA_FINETUNE                0x00000100      //带微调按钮的InputButton   (小微调)
#define SIA_FINETUNE2               0x00000200      //带微调按钮2的InputButton  (大微调)
#define SIA_UPDATEITEM              0x00000400      //点击后,更新当前显示的所有条目
#define SIA_UPDATEDATA              0x00000800      //支持Update Data 事件
#define SIA_INPUT_TEXT              0x00001000      //输入框为字符串输入
#define SIA_INPUT_TIME              0x00002000      //输入框为数值输入 (时间)
#define SIA_EXLBL                   0x00004000      //扩展标签 (Extend Label, 仅ButtonEx)
#define SIA_MAINRES                 0x00008000      //资源在E5070.exe中, 配合 SIA_BITMAP
#define SIA_UNREAD					0x00020000		//为序列号框定义的静态文本框

#define SIA_PSTMSG_432_2            0x00010000 

//Sub Item Attributes Extend
#define SIAE_CHECKED                0x01000000      //已选中
#define SIAE_DISABLED               0x02000000      //EnableWindow FALSE

//Sub Item Style
enum SubItemStyle : DWORD
{
  SIS_Delimiter = 0,        //分隔符
  SIS_ButtonEx,             //标准按钮
  SIS_RadioButtonEx,        //单选按钮
  SIS_CheckButtonEx,        //复选按钮
  SIS_InputButtonEx,        //输入按钮
  SIS_ComboButtonEx,        //下拉框按钮
  SIS_ComboRadioButtonEx,   //单选下拉框按钮
  SIS_Invalid
};


//Tag Page :: Enter & Leave function
typedef int(WINAPI *func_TagPageEnter)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage);
typedef int(WINAPI *func_TagPageLeave)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_TAG_PAGE *lpTagPage);

//Menu :: Enter & Leave function
typedef int(WINAPI *func_MenuEnter)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_MENU *lpSoftMenu);
typedef int(WINAPI *func_MenuLeave)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_MENU *lpSoftMenu);

typedef int(WINAPI *func_ItemEvent_Common)(DWORD dwFlags, DWORD dwCode, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
typedef int(WINAPI *func_ItemEvent_Clicked)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);
typedef int(WINAPI *func_ItemEvent_Selected)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem, int nIndex);
typedef int(WINAPI *func_ItemEvent_UpdateData)(DWORD dwFlags, WPARAM wParam, LPARAM lParam, struct _SOFT_SUB_ITEM *lpSubItem);

//软菜单项目点击事件的通知码
#define IC_CLICKED_FIRST              0     //首次点击 (在执行原版功能前)
#define IC_CLICKED_LAST               1     //最后点击 (在执行原版功能后)

//软菜单项目事件过程的Id
#define FNID_COMMON_EVENT             0
#define FNID_CLICKED                  1
#define FNID_SELECTED                 2
#define FNID_UPDATE_DATA              3

//软菜单子项目
typedef struct _SOFT_SUB_ITEM
{
  //项目标志  Sub Item Flags
  DWORD                   dwFlags;
  //项目属性  Sub Item Attributes
  DWORD                   dwAttributes;
  //项目样式  Sub Item Style
  DWORD                   dwStyle;            //控件类型 按钮、单选、复选、文本输入
  //对应原软菜单的Id (索引)
  DWORD                   dwFunctionId;
  //项目静态文本
  const WCHAR           * lpszItemText;
  //项目文本 (如果szItemText != NULL,那么将会忽略lpszItemText)
  WCHAR                 * szItemText;
  //项目最小宽度
  WORD                    wMinWidth;
  //项目高度
  WORD                    wHeight;
  //项目按钮句柄
  HWND                    _hWnd;

  /* 项目可选部分 (void *) * 16
  lpOpt ::
  0~3   : 常用参数 (输入输出)
  4~7   : 子控件句柄
  8~11  : 杂项

  lpOpt[0]                btVar                   //SIA_GETBTNSTATE
  lpOpt[1]                lpInputValue            //与输入框修改数值相关的指针
  lpOpt[2]                lpBtnState              //与复选框状态以及设置输入框复用相关的指针
  lpOpt[3]                lpBtnStateIndex

  lpOpt[4]                _hSubWnd                //Edit
  lpOpt[5]                _hSubWnd2               //msctls_updown32
  lpOpt[6]                _hSubWnd3               //msctls_updown32

  lpOpt[8]                Uncheck lpVTable        (取消选中的虚表地址)
  lpOpt[9]                Uncheck lpThis          (取消选中的类地址)
  lpOpt[10]               Uncheck dwFuncId        (取消选中的功能索引)
  lpOpt[11]               func_PopWndUpdateProc   (浮动输入框事件处理过程)
  取消选中的参数暂只在频标部分出现 (SIF_UNCHECKFUNC)
  lpOpt[12]				  STR_chk				//乱其名的，因为移植到WIN7需要做基址校准，所以这个用作标志位;
  */
  void                  * lpOpt[16];

  /* 项目事件 (void *) * 16
  lpEvent 0               fn Common
  lpEvent 1               fn Clicked (First / Last)
  lpEvent 2               fn Selected
  lpEvent 3               fn Update Data
  */
  void                  * lpEvent[16];

  union
  {
    //当前项目组中激活的索引,或者项目组头部索引
    DWORD                 dwActiveOffset;
    DWORD                 dwGroupIndex;     //if dwGroupIndex == INVALID_INDEX then 不在组中
  };

  union
  {
    //位图Id, 其它方式保留
    void                * lpDrawFunc;
    void                * lpFunctionUpdate;
    int                   nBitmapId;
  };

  WPARAM                  wParam;
  
  union
  {
    //软菜单虚表地址
    void                * lpVTable;
    LPARAM                lParam;
  };

  union
  {
    //软菜单类地址,下一级软菜单,对话框上下文
    void                * lpThis;
    void                * lpEventClick;
    struct _SOFT_MENU   * lpSoftMenu;
    PCALDLG_CTXT          lpCalDlgCtxt;
    PDLG_CTXT             lpDlgCtxt;
  };

  //附加参数的数量
  DWORD                   dwNumberOfParams;
  //指向附加参数
  const void            * lpParams;
  //项目窗口的矩形区域
  RECT                    rect;
  //保留
  //【3】用作判断lpParams是wstring还是LPWCSTR；
  DWORD                   dwReserve[4];
} SOFT_SUB_ITEM, *PSOFT_SUB_ITEM;

//Tag Page Flags
#define TPF_FN_ENTER                0x00000001
#define TPF_FN_LEAVE                0x00000002
#define TPF_DYNAMIC                 0x00000004

//软菜单标签页结构体
typedef struct _SOFT_TAG_PAGE
{
  //标签页标志 (Tag Page Flags)
  DWORD                   dwFlags;
  //标签页属性
  DWORD                   dwAttributes;
  //标签页静态文本
  const WCHAR           * lpszTagText;
  //标签页文本
  WCHAR                 * szTagText;
  //该标签页下子项目的数量
  DWORD                   dwNumOfSubItems;
  //指向该标签页子项目数组的指针
  PSOFT_SUB_ITEM          lpSubItem;
  //标签页矩形区域
  RECT                    rect;
  //标签页进入函数
  func_TagPageEnter       fnEnter;
  //标签页离开函数
  func_TagPageLeave       fnLeave;
  //该标签页下激活的项目索引 (已弃用)
  DWORD                   dwActiveIndex;
  //保留
  //[3]暂时用作LPWCTR转wstring用   0为LPWCSTR  1为wstring
  void                  * lpReserve[4];
} SOFT_TAG_PAGE, *PSOFT_TAG_PAGE;


//Soft Menu Flags
#define SMF_FN_ENTER                0x00000001
#define SMF_FN_LEAVE                0x00000002

//软菜单结构体
typedef struct _SOFT_MENU
{
  //软菜单标志 (Soft Menu Flags)
  DWORD               dwFlags;
  //软菜单属性
  DWORD               dwAttributes;
  //软菜单静态标题
  const WCHAR       * lpszMenuTitle;
  //软菜单标题
  WCHAR             * szMenuTitle;
  //该软菜单下标签页的数量
  DWORD               dwNumOfTagPages;
  //指向该软菜单下的标签页数组
  PSOFT_TAG_PAGE      lpTagPage;
  //软菜单进入函数
  func_MenuEnter      fnEnter;
  //软菜单离开函数
  func_MenuLeave      fnLeave;
  //该软菜单下激活的项目索引 (已弃用)
  DWORD               dwActiveIndex;
  //保留
  DWORD               dwReserve[4];
} SOFT_MENU, *PSOFT_MENU;