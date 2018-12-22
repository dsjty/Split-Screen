#include "stdafx.h"

typedef struct _NAC_RECORD
{
	DWORD             dwRandom;
	DWORD             dwNumberOfUsed;  //xor
	DWORD             dwRandom2[4];
	DWORD             dwCRC32[2];
} NAC_RECORD, *PNAC_RECORD;

static UINT CRC32[256];
// static NAC_RECORD nrFile, nrReg;

//#define NACRECORD_FILE             "D:\\agilent_record.bin"
#define NACRECORD_FILE              "C:\\WINDOWS\\system32\\XJQAZWSX.bin"
#define NACRECORD_REG               L"Software\\Microsoft\\Notepad"
//  D:\\Agilent\\Service\\record.bin

int QueryNetTime(PCSTR lpHost, PCSTR lpPort, LPSYSTEMTIME lpSysTime);

DWORD GetRandomDword()
{
	union DW64
	{
		DWORD64   dw64;
		DWORD     dw32[2];
	};

	DW64 udw64;

	udw64.dw64 = __rdtsc();

	return udw64.dw32[0] ^ udw64.dw32[1] ^ GetTickCount() ^ 0x85ED295A;
}

DWORD GetRandomDword2()
{
	union DW64
	{
		DWORD64   dw64;
		DWORD     dw32[2];
	};

	DW64 udw64;

	udw64.dw64 = __rdtsc();

	return udw64.dw32[0] ^ udw64.dw32[1] ^ GetTickCount() ^ 0xA5A5B45A;
}

//初始化表
static void init_table()
{
	int i, j;
	UINT crc;

	for (i = 0; i < 256; i++)
	{
		crc = i;
		for (j = 0; j < 8; j++)
		{
			if (crc & 1)
			{
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc = crc >> 1;
			}
		}
		CRC32[i] = crc;
	}
}

//crc32实现函数
UINT crc32(BYTE *buf, int len)
{
	static bool blInit = false;
	UINT ret = 0xFFFFFFFFu;
	int i;

	if (!blInit)
	{
		init_table();
		blInit = true;
	}

	for (i = 0; i < len; i++)
	{
		ret = CRC32[((ret & 0xFF) ^ buf[i])] ^ (ret >> 8);
	}

	ret = ~ret;
	return ret;
}

BOOL QueryReg(PNAC_RECORD lpRecord)
{
	HKEY hKey;
	LSTATUS nRet;
	DWORD dwDisp, dwType, dwSize;

	if (lpRecord == NULL)
		return FALSE;

	nRet = RegOpenKeyExW(HKEY_CURRENT_USER, NACRECORD_REG, 0, KEY_ALL_ACCESS, &hKey);

	if (nRet == ERROR_SUCCESS)
	{
		nRet = RegQueryValueExW(hKey, L"HardwareInfo", NULL, NULL, NULL, NULL);
		RegCloseKey(hKey);

		if (nRet == ERROR_FILE_NOT_FOUND)
			return FALSE;
	}
	else
		return FALSE;


	nRet = RegCreateKeyExW(HKEY_CURRENT_USER, NACRECORD_REG, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);

	if (nRet != ERROR_SUCCESS)
		return FALSE;

	dwType = REG_BINARY;
	dwSize = sizeof(NAC_RECORD);
	nRet = RegQueryValueExW(hKey, L"HardwareInfo", NULL, &dwType, (LPBYTE)lpRecord, &dwSize);
	RegCloseKey(hKey);

	if (nRet == ERROR_FILE_NOT_FOUND)
		return FALSE;

	return TRUE;
}

BOOL QueryFile(PNAC_RECORD lpRecord)
{
	HANDLE hFile;
	DWORD dwFileSize;

	if (lpRecord == NULL)
		return FALSE;

	hFile = CreateFileA(NACRECORD_FILE, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwFileSize = GetFileSize(hFile, NULL);

	if (dwFileSize != sizeof(NAC_RECORD))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	ReadFile(hFile, lpRecord, sizeof(NAC_RECORD), &dwFileSize, NULL);
	CloseHandle(hFile);
	return TRUE;
}

BOOL SaveReg(PNAC_RECORD lpRecord)
{
	HKEY hKey;
	LSTATUS nRet;
	DWORD dwDisp;

	if (lpRecord == NULL)
		return FALSE;

	nRet = RegCreateKeyExW(HKEY_CURRENT_USER, NACRECORD_REG, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);

	if (nRet != ERROR_SUCCESS)
		return FALSE;

	RegSetValueExW(hKey, L"HardwareInfo", 0, REG_BINARY, (BYTE *)lpRecord, sizeof(NAC_RECORD));
	RegCloseKey(hKey);

	return TRUE;
}

BOOL SaveFile(PNAC_RECORD lpRecord)
{
	HANDLE hFile;
	DWORD dwTmp;

	if (lpRecord == NULL)
		return FALSE;

	hFile = CreateFileA(NACRECORD_FILE, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	SetFilePointer(hFile, sizeof(NAC_RECORD), NULL, FILE_BEGIN);
	SetEndOfFile(hFile);

	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	WriteFile(hFile, lpRecord, sizeof(NAC_RECORD), &dwTmp, NULL);
	CloseHandle(hFile);
	return TRUE;
}

/*
BOOL CheckDate(WORD wYear, WORD wMonth, WORD wDay)
{
	SYSTEMTIME st;

	GetLocalTime(&st);

	if (st.wYear > wYear)
		return FALSE;
	else if ((st.wYear == wYear) && (st.wMonth > wMonth))
		return FALSE;
	else if ((st.wYear == wYear) && (st.wMonth == wMonth) && (st.wDay > wDay))
		return FALSE;

	return TRUE;
}

BOOL CheckNetDate(WORD wYear, WORD wMonth, WORD wDay)
{
	SYSTEMTIME st;

	if (QueryNetTime("cn.ntp.org.cn", "123", &st) == 0)
	{
		if (st.wYear > wYear)
			return FALSE;
		else if ((st.wYear == wYear) && (st.wMonth > wMonth))
			return FALSE;
		else if ((st.wYear == wYear) && (st.wMonth == wMonth) && (st.wDay > wDay))
			return FALSE;
	}

	return TRUE;
}

BOOL CheckLicense()
{
	NAC_RECORD nrReg, nrFile;
	DWORD dwCRC32Reg, dwCRC32File;

	//if (CheckNetDate(2016, 06, 5) && CheckDate(2016, 06, 05)) 
		return TRUE;

	if (QueryReg(&nrReg) == FALSE)
	{
		if (QueryFile(&nrFile) == FALSE)
		{
			//初始

			nrReg.dwRandom = GetRandomDword();
			nrReg.dwNumberOfUsed = 1 ^ nrReg.dwRandom;
			nrReg.dwRandom2[0] = GetRandomDword();
			nrReg.dwRandom2[1] = GetRandomDword();
			nrReg.dwRandom2[2] = GetRandomDword();
			nrReg.dwRandom2[3] = GetRandomDword();

			nrFile.dwRandom = GetRandomDword2();
			nrFile.dwNumberOfUsed = 1 ^ nrFile.dwRandom;
			nrFile.dwRandom2[0] = GetRandomDword2();
			nrFile.dwRandom2[1] = GetRandomDword2();
			nrFile.dwRandom2[2] = GetRandomDword2();
			nrFile.dwRandom2[3] = GetRandomDword2();

			dwCRC32Reg = crc32((BYTE *)&nrReg, sizeof(DWORD) * 6);
			dwCRC32File = crc32((BYTE *)&nrFile, sizeof(DWORD) * 6);

			nrReg.dwCRC32[0] = dwCRC32Reg ^ nrFile.dwRandom;
			nrReg.dwCRC32[1] = dwCRC32File ^ nrReg.dwRandom;

			nrFile.dwCRC32[0] = dwCRC32Reg ^ nrReg.dwRandom;
			nrFile.dwCRC32[1] = dwCRC32File ^ nrFile.dwRandom;

			SaveReg(&nrReg);
			SaveFile(&nrFile);

			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	if (QueryFile(&nrFile) == FALSE)
	{
		return FALSE;
	}

	nrReg.dwCRC32[0] ^= nrFile.dwRandom;
	nrReg.dwCRC32[1] ^= nrReg.dwRandom;

	nrFile.dwCRC32[0] ^= nrReg.dwRandom;
	nrFile.dwCRC32[1] ^= nrFile.dwRandom;

	dwCRC32Reg = crc32((BYTE *)&nrReg, sizeof(DWORD) * 6);
	dwCRC32File = crc32((BYTE *)&nrFile, sizeof(DWORD) * 6);

	if ((dwCRC32Reg != nrReg.dwCRC32[0]) || (dwCRC32Reg != nrFile.dwCRC32[0]))
		return FALSE;

	if ((dwCRC32File != nrReg.dwCRC32[1]) || (dwCRC32File != nrFile.dwCRC32[1]))
		return FALSE;

	nrReg.dwNumberOfUsed ^= nrReg.dwRandom;
	nrFile.dwNumberOfUsed ^= nrFile.dwRandom;

	if (nrReg.dwNumberOfUsed != nrFile.dwNumberOfUsed)
		return FALSE;

	nrReg.dwNumberOfUsed++;

	if (nrReg.dwNumberOfUsed > 60)
		return FALSE;

	nrFile.dwNumberOfUsed = nrReg.dwNumberOfUsed;

	nrReg.dwRandom ^= GetRandomDword();
	nrReg.dwNumberOfUsed ^= nrReg.dwRandom;
	nrReg.dwRandom2[0] ^= GetRandomDword();
	nrReg.dwRandom2[1] ^= GetRandomDword();
	nrReg.dwRandom2[2] ^= GetRandomDword();
	nrReg.dwRandom2[3] ^= GetRandomDword();

	nrFile.dwRandom ^= GetRandomDword2();
	nrFile.dwNumberOfUsed ^= nrFile.dwRandom;
	nrFile.dwRandom2[0] ^= GetRandomDword2();
	nrFile.dwRandom2[1] ^= GetRandomDword2();
	nrFile.dwRandom2[2] ^= GetRandomDword2();
	nrFile.dwRandom2[3] ^= GetRandomDword2();

	dwCRC32Reg = crc32((BYTE *)&nrReg, sizeof(DWORD) * 6);
	dwCRC32File = crc32((BYTE *)&nrFile, sizeof(DWORD) * 6);

	nrReg.dwCRC32[0] = dwCRC32Reg ^ nrFile.dwRandom;
	nrReg.dwCRC32[1] = dwCRC32File ^ nrReg.dwRandom;

	nrFile.dwCRC32[0] = dwCRC32Reg ^ nrReg.dwRandom;
	nrFile.dwCRC32[1] = dwCRC32File ^ nrFile.dwRandom;

	SaveReg(&nrReg);
	SaveFile(&nrFile);

	return TRUE;
}
*/