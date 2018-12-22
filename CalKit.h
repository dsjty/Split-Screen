#pragma once

#include <wtypes.h>
#include <vector>
#include <xstring>

using std::wstring;

typedef struct _MENUPTRSTR
{
	void	*lpThis;		//0x0  
	int		MenuNum;		// 0x4
	void	*UnKnow;		// 0x8
	char	*lpMenuName;	// 0xc
	void	*UnKnow2;		// 0x10
	void	*SubMenuName;	//	0x14	//里面是LPCSTR数组;
	void	*UnKnow3;		// 0x18
	void	*UnKnow4;		// 0x1c
	void	*UnKnow5;		// 0x20
	void	*UnKnow6;		// 0x24
	void	*UnKnow8;		// 0x28
	void	*UnKnow9;		// 0x2c
	void	*UnKnowA;		// 0x30
	void	*SubMenuThisList;	// 0x34
}MENUPTRSTR, *PMENUPTRSTR;

typedef struct _CALKITOBJ
{
	DWORD dwreserve0;
	DWORD dwObjNameAdd;
	DWORD dwreserve1;
	DWORD dwreserve2;
}CALKITOBJ,*PCALKITOBJ;

class CalKit
{
public:
	CalKit();
	~CalKit();

public:
	CALKITOBJ GetCalKitName(int id);
	bool SetCalKitName(LPCSTR name, int id);

	wstring CalKitList[26];
	wstring OldCalKitList[26];
	wstring NewCalKitList[26];
	CALKITOBJ stCalKitObj;
private:

};

CALKITOBJ GetCalKitName();

//extern CalKit cCalkit;
