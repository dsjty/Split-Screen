#include "stdafx.h"

BOOL WINAPI _CWnd__Create(CWnd *lpThis, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext);

void WINAPI _CWnd__OnSize_main(CWnd *lpThis, UINT nType, int cx, int cy);



NAKED int ef_CWnd__Create()
{


	ResetHookPointer(HookPtr[0]);
		
	//懒得找消息循环了，只好干脆隐藏原菜单，达到屏蔽闪屏的目的
	__asm
	{
		mov ebx,[esp+0x10]
		mov edx, dword ptr ds : [esi + 0x110]
		mov edx, dword ptr ds : [edx + 0x5C]
		push ebx
		push 0x84
		push esi
		push ebx
		xor ebx,ebx
		push 0x68000000
		lea ecx, DWORD PTR ds : [esi + 0x110]
		push ebx
		push ebx
		call edx
	}

	__asm lea ecx, DWORD PTR ds : [esi + 0x110]
	__asm pop eax
	__asm push ecx
	__asm push eax
	__asm jmp _CWnd__Create
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}

//0x0008AE219
NAKED void ef_CWnd__OnSize_main()
{
	__asm mov esp, ebp
	__asm pop ebp			//__asm add esp, 0x10
	__asm pop eax
	__asm push ecx
	__asm push eax
	__asm jmp _CWnd__OnSize_main
	__asm int 3
}