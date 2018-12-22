#pragma once

//编译时标志:

//显示新软菜单
#define CF_NEWMENU                        1

//创建工具条
#define CF_MYTOOLBAR                      1

//隐藏主菜单
#define CF_HIDEMENU                       1

//输入框跳过
#define CF_FNHK_PASS_004A8FA0             1

//文本输入框跳过
#define CF_FNHK_PASS_004A90A0             1

//009061C7 挂钩函数 (第四章 曲线信息栏 实现函数)
#define CF_FNHK_00906467                  0

//008C4B55 挂钩函数 (第五章 测试状态栏 实现函数)
#define CF_FNHK_008C4B55                  0

//处理多通道同步, Hook 鼠标点击函数
#define CF_FNHK_MOUSEEVENT                1

//修改窗口标题
#define CF_SET_TITLE                      1

//设置物理事件处理器 (物理键码处理函数) (第七章 用于挂钩前面板事件及主菜单事件)
#define CF_PHYSEVENT                      0		//启动前hook会被重置，换到time事件触发

//设置事件处理器 (虚拟键码处理函数) (第七章 用于挂钩前面板事件及主菜单事件)
#define CF_EVENTHANDLE                    1

//挂钩焦点 (保持E5070程序在激活窗口时,焦点始终在软菜单上)
#define CF_HOOKFOCUS                      1

//禁用编译时的警告
#define CF_DISABLE_WARN                   1

