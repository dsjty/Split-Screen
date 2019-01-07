#include "stdafx.h"
#include "CalKit.h"

CalKit::CalKit()
{	
	CalKitList[0] = L"TD1033E";
	CalKitList[1] = L"TD1033D";
	CalKitList[2] = L"TD1052D";
	CalKitList[3] = L"TD1032F";
	CalKitList[4] = L"TD1032B/E";
	CalKitList[5] = L"TD1036B/E";
	CalKitList[6] = L"TD1031B";
	CalKitList[7] = L"TD10350C/D";
	CalKitList[8] = L"TD1052C";
	CalKitList[9] = L"TD1038A/F/M";
	CalKitList[10] = L"TD1054D";
	CalKitList[11] = L"TD1056D";
	CalKitList[12] = L"TD1056K";
	CalKitList[13] = L"TD1039B";
	CalKitList[14] = L"X11644A";
	CalKitList[15] = L"P11644A";
	CalKitList[16] = L"K11644A";
	CalKitList[17] = L"TD1050B";
	CalKitList[18] = L"TD1052B";
	CalKitList[19] = L"TD1054B";
	CalKitList[20] = L"TD1056A";
	CalKitList[21] = L"User";
	CalKitList[22] = L"User";
	CalKitList[23] = L"User";
	CalKitList[24] = L"User";
	CalKitList[25] = L"User";

	NewCalKitList[0] = L"TD1033E";
	NewCalKitList[1] = L"TD1033D";
	NewCalKitList[2] = L"TD1052D";
	NewCalKitList[3] = L"TD1032F";
	NewCalKitList[4] = L"TD1032B/E";
	NewCalKitList[5] = L"TD1036B/E";
	NewCalKitList[6] = L"TD1031B";
	NewCalKitList[7] = L"TD10350C/D";
	NewCalKitList[8] = L"TD1052C";
	NewCalKitList[9] = L"TD1038A/F/M";
	NewCalKitList[10] = L"TD1054D";
	NewCalKitList[11] = L"TD1056D";
	NewCalKitList[12] = L"TD1056K";
	NewCalKitList[13] = L"TD1039B";
	NewCalKitList[14] = L"X11644A";
	NewCalKitList[15] = L"P11644A";
	NewCalKitList[16] = L"K11644A";
	NewCalKitList[17] = L"TD1050B";
	NewCalKitList[18] = L"TD1052B";
	NewCalKitList[19] = L"TD1054B";
	NewCalKitList[20] = L"TD1056A";
	NewCalKitList[21] = L"User";
	NewCalKitList[22] = L"User";
	NewCalKitList[23] = L"User";
	NewCalKitList[24] = L"User";
	NewCalKitList[25] = L"User";

	OldCalKitList[0] = L"85033E";
	OldCalKitList[1] = L"85033D";
	OldCalKitList[2] = L"85052D";
	OldCalKitList[3] = L"85032F";
	OldCalKitList[4] = L"85032B/E";
	OldCalKitList[5] = L"85036B/E";
	OldCalKitList[6] = L"85031B";
	OldCalKitList[7] = L"850350C/D";
	OldCalKitList[8] = L"85052C";
	OldCalKitList[9] = L"85038A/F/M";
	OldCalKitList[10] = L"85054D";
	OldCalKitList[11] = L"85056D";
	OldCalKitList[12] = L"85056K";
	OldCalKitList[13] = L"85039B";
	OldCalKitList[14] = L"X11644A";
	OldCalKitList[15] = L"P11644A";
	OldCalKitList[16] = L"K11644A";
	OldCalKitList[17] = L"85050B";
	OldCalKitList[18] = L"85052B";
	OldCalKitList[19] = L"85054B";
	OldCalKitList[20] = L"85056A";
	OldCalKitList[21] = L"User";
	OldCalKitList[22] = L"User";
	OldCalKitList[23] = L"User";
	OldCalKitList[24] = L"User";
	OldCalKitList[25] = L"User";
}

CalKit::~CalKit()
{
}

CALKITOBJ CalKit::GetCalKitName(int id)
{
	//要不然这里就做一个用处 就是hook住0x519D60  外面也不做处理!直接读取类元素;
	return stCalKitObj;
}

bool CalKit::SetCalKitName(LPCSTR name, int id)
{
	WCHAR pBuffer[100] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, name, -1, pBuffer, sizeof(WCHAR) * 100);
	for (int i = 0; i < 26; i++)
	{
		if (0 == wcscmp(pBuffer, OldCalKitList[i].c_str()))
		{
			wcscpy_s(pBuffer, NewCalKitList[i].c_str());
			break;
		}
	}
	CalKitList[id] = pBuffer;
	return true;
}


//************************************
// 函数名:    GetCalKitName
// Access:    public 
// 返回值类型:   NAKED CALKITOBJ
// 说明: hook校准件循环信息以更新新UI校准件名信息
//************************************
NAKED CALKITOBJ GetCalKitName()
{
	DWORD CalName;
	int id;

	__asm push ebp
	__asm mov ebp,esp
	__asm sub esp,0x20
	__asm push eax
	__asm push ecx
	__asm push edx
	__asm push ebx
	__asm push esp
	__asm push ebp

	__asm mov CalName, eax
	__asm mov id,esi
	cCalkit.SetCalKitName((LPCSTR)((PCALKITOBJ)CalName)->dwObjNameAdd, id);

	__asm pop ebp
	__asm pop esp
	__asm pop ebx
	__asm pop edx
	__asm pop ecx
	__asm pop eax

	__asm add esp,0x20
	__asm pop ebp

	__asm mov eax, [eax + 4]
	__asm retn 0x8
}

