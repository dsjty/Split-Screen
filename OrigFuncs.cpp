#include "stdafx.h"

/*
本文件包含来自于E5062.exe中函数调用的逆向结果及再工程函数
*/


int OrigSoftMenu_Enter(void *lpThis)
{
	if (lpThis == NULL) 
		return -1;

	DWORD dwLpthis = BASE + (DWORD)lpThis;

	void *lpVTable = *(void **)dwLpthis;

	if (lpVTable == NULL) 
		return -2;

	return DirectCall((LPVOID)dwLpthis, GetOffsetPointer(lpVTable, 0x18));
}

int OrigSoftMenu_Leave(void *lpThis)
{
	if (lpThis == NULL) 
		return -1;

	DWORD dwLpthis = BASE + (DWORD)lpThis;

	void *lpVTable = *(void **)dwLpthis;

	if (lpVTable == NULL) 
		return -2;

	return DirectCall((LPVOID)dwLpthis, GetOffsetPointer(lpVTable, 0x1C));
}

void OrigSoftMenu_ClearItems(void *lpThis)
{
	if (lpThis)
	{
		DWORD dwLpthis = BASE + (DWORD)lpThis;

		typedef void(__thiscall * fnClearItem)(void *dwLpthis);

		fnClearItem fnCI = (fnClearItem)(BASE + 0xA142D0);

		fnCI((void*)dwLpthis);
	}

	return;
}

int OrigSoftMenu_UpdateItems(void *lpThis)
{
	if (lpThis == NULL) 
		return -1;

	DWORD dwLpthis = BASE + (DWORD)lpThis;

	typedef void(__thiscall * fnClearItem)(void *dwLpthis);

	fnClearItem fnCI = (fnClearItem)(BASE+ 0xA142D0);
	void *lpVTable = *(void **)dwLpthis;

	fnCI((void*)dwLpthis);

	if (lpVTable == NULL) 
		return -2;

	return DirectCall((void*)dwLpthis, GetOffsetPointer(lpVTable, 0x08));   //刷新菜单控件
}

int OrigSoftMenu_ItemClicked2(void *lpThis, void *ulpOptVTable, int nItemIndex)
{
	if (lpThis == NULL) 
		return -1;

	DWORD dwLpthis = BASE + (DWORD)lpThis;
	DWORD lpOptVTable = BASE + (DWORD)ulpOptVTable;

	void *lpVTable = *(void **)dwLpthis;

	if (lpVTable == NULL)
	{
		lpVTable = (void *)lpOptVTable;

		if (lpVTable == NULL) 
			return -2;
	}

	return DirectCall_2((void*)dwLpthis, GetOffsetPointer(lpVTable, 0x0C), nItemIndex);
}

//************************************
// 函数名:    OrigSoftMenu_GetItemState
// 函数性质:    public 
// 函数类型:   int
// 描述:本函数是轮流刷新菜单按钮状态，参数2是按钮序号,每种按钮的状态的存放位置是后面几位参数;
//************************************
int OrigSoftMenu_GetItemState(void *lpThis, int nIndex, LPBOOL lpblEnable, LPBOOL lpblCheck, LPBOOL lpblRadio)
{
	DWORD dwLpthis = BASE + (DWORD)lpThis;

	typedef int(__thiscall * fnGetButtonState)(void *lpThis, int nIndex, DWORD dwState[4]);

	if (lpThis == NULL) 
		return -1;

	void *lpVTable = *(void **)dwLpthis;

	if (lpVTable == NULL) 
		return -2;

	fnGetButtonState fnGBS = (fnGetButtonState)GetOffsetPointer(lpVTable, 0x10);

	int nRet;

	DWORD dwData[4] = { (BASE + 0xE8D6EC), 1, 0, 0 };

	//刷新菜单控件
	OrigSoftMenu_UpdateItems(lpThis);

	nRet = fnGBS((void*)dwLpthis, nIndex, dwData);

	if (lpblEnable) 
		*lpblEnable = dwData[1];
	if (lpblCheck) 
		*lpblCheck = dwData[2];
	if (lpblRadio) 
		*lpblRadio = dwData[3];

	return nRet;
}