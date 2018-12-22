#pragma once

void *lpTestSet1 = nullptr;
void *lpTestSet1_Sel = nullptr;
void *lpTestSet1_Port1 = nullptr;
void *lpTestSet1_Port2 = nullptr;
void *lpTestSet1_Port3 = nullptr;
void *lpTestSet1_Port4 = nullptr;
void *lpTestSet1_Port5 = nullptr;
void *lpTestSet1_Port6 = nullptr;
void *lpTestSet1_Port7 = nullptr;
void *lpTestSet1_Port8 = nullptr;
void *lpTestSet1_Port9 = nullptr;
void *lpTestSet1_Port10 = nullptr;
void *lpTestSet1_CLA = nullptr;
void *lpTestSet1_CLB = nullptr;
void *lpTestSet1_CLC = nullptr;
void *lpTestSet1_CLD = nullptr;

void *lpTestSet2 = nullptr;
void *lpTestSet2_Sel = nullptr;
void *lpTestSet2_Port1 = nullptr;
void *lpTestSet2_Port2 = nullptr;
void *lpTestSet2_Port3 = nullptr;
void *lpTestSet2_Port4 = nullptr;
void *lpTestSet2_Port5 = nullptr;
void *lpTestSet2_Port6 = nullptr;
void *lpTestSet2_Port7 = nullptr;
void *lpTestSet2_Port8 = nullptr;
void *lpTestSet2_Port9 = nullptr;
void *lpTestSet2_Port10 = nullptr;
void *lpTestSet2_CLA = nullptr;
void *lpTestSet2_CLB = nullptr;
void *lpTestSet2_CLC = nullptr;
void *lpTestSet2_CLD = nullptr;

static WNDPROC wpfn_InputEdit = NULL;
static LRESULT CALLBACK wp_InputEdit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void SetInputType(int nNewType);



const LPCSTR TestSetList[] =
{
	"TD10191_9",
	"TD10191_13",
	"TD10191_16",
	"TD10192_13",
	"TD10192_16",
	"TD10192_22",
	"TD10192_28",
	"TD10192_x10"
};

const LPCSTR List91_9P1[] =
{
	"A",
	"T1"
};


const LPCSTR List91_9P2[] =
{
	"T1",
	"T2"
};

const LPCSTR List91_9P3[] =
{
	"R1+",
	"R2+",
	"R3+"
};

const LPCSTR List91_9P4[] =
{
	"R1-",
	"R2-",
	"R3-"
};

const LPCSTR List91_13P1[] =
{
	"A",
	"T1",
	"T2",
	"T3"
};
const LPCSTR List91_13P2[] =
{
	"T1",
	"T2",
	"T3",
	"T4"
};
const LPCSTR List91_13P3[] =
{
	"R1+",
	"R2+",
	"R3+",
	"R4+"
};
const LPCSTR List91_13P4[] =
{
	"R1-",
	"R2-",
	"R3-",
	"R4-"
};
const LPCSTR List91_16P1[] =
{
	"A1",
	"A2",
	"A3",
	"A4",
	"A",
	"T1",
	"T2",
	"T3"
};
const LPCSTR List91_16P2[] =
{
	"B1",
	"B2",
	"B3",
	"B4",
	"A",
	"T1",
	"T2",
	"T3"
};
const LPCSTR List91_16P5[] =
{
	"X1",
	"X2"
};
const LPCSTR List91_16P6[] =
{
	"Y1",
	"Y2"
};
const LPCSTR List91_16P7[] =
{
	"Z1",
	"Z2"
};
const LPCSTR List92_13P1[] =
{
	"A(1A)",
	"T1(8COM)",
	"T2(9COM)",
	"T3(10COM)"
};
const LPCSTR List92_13P2[] =
{
	"T1(8COM)",
	"T2(9COM)",
	"T3(10COM)",
	"T4(2D)"
};
const LPCSTR List92_13P3[] =
{
	"R1+(3A)",
	"R2+(3B)",
	"R3+(3C)",
	"R4+(3D)"
};
const LPCSTR List92_13P4[] =
{
	"R1-(4A)",
	"R2-(4B)",
	"R3-(4C)",
	"R4-(4D)"
};
const LPCSTR List92_16P1[] =
{
	"A1(1A)",
	"A2(1B)",
	"A3(1C)",
	"A4(1D)"
};
const LPCSTR List92_16P2[] =
{
	"B1(2D)",
	"B2(2A)",
	"B3(2B)",
	"B4(2C)"
};
const LPCSTR List92_16P5[] =
{
	"X1(8B)",
	"X2(8A)"
};
const LPCSTR List92_16P6[] =
{
	"Y1(9B)",
	"Y2(9A)"
};
const LPCSTR List92_16P7[] =
{
	"Z1(10B)",
	"Z2(10A)"
};
const LPCSTR List92_22P1[] =
{
	"A1(5A)",
	"A2(5B)",
	"A3(6A)",
	"A4(6B)",
	"A5(1C)",
	"A6(1D)"
};
const LPCSTR List92_22P2[] =
{
	"A7(8A)",
	"A8(8B)",
	"A9(2B)",
	"A10(2C)",
	"A11(2D)"
};
const LPCSTR List92_22P3[] =
{
	"B1(3A)",
	"B2(9A)",
	"B3(9B)",
	"B4(10A)",
	"B5(10B)",
	"B6(3D)"
};
const LPCSTR List92_22P4[] =
{
	"B7(4A)",
	"B8(4B)",
	"B9(7A)",
	"B10(7B)",
	"B11(4D)"
};
const LPCSTR List92_22P5[] =
{
	"A(10A)",
	"B(10B)"
};
const LPCSTR List92_28P1[] =
{
	"A(1A)",
	"B(1B)",
	"C(1C)",
	"D(1D)"
};
const LPCSTR List92_28P2[] =
{
	"A(2A)",
	"B(2B)",
	"C(2C)",
	"D(2D)"
};
const LPCSTR List92_28P3[] =
{
	"A(3A)",
	"B(3B)",
	"C(3C)",
	"D(3D)"
};
const LPCSTR List92_28P4[] =
{
	"A(4A)",
	"B(4B)",
	"C(4C)",
	"D(4D)"
};
const LPCSTR List92_28P5[] =
{
	"A(5A)",
	"B(5B)"
};
const LPCSTR List92_28P6[] =
{
	"A(6A)",
	"B(6B)"
};
const LPCSTR List92_28P7[] =
{
	"A(7A)",
	"B(7B)"
};
const LPCSTR List92_28P8[] =
{
	"A(8A)",
	"B(8B)"
};
const LPCSTR List92_28P9[] =
{
	"A(9A)",
	"B(9B)"
};
const LPCSTR List92_28P10[] =
{
	"A(10A)",
	"B(10B)"
};
const LPCSTR List92_X10P1[] =
{
	"1(5COM)",
	"3(6COM)",
	"5(7COM)",
	"7(1D)"
};
const LPCSTR List92_X10P2[] =
{
	"2(8COM)",
	"4(9COM)",
	"6(10COM)",
	"8(2D)"
};
const LPCSTR List92_X10P3[] =
{
	"2(8COM)",
	"4(9COM)",
	"6(10COM)",
	"10(3D)"
};
const LPCSTR List92_X10P4[] =
{
	"1(5COM)",
	"3(6COM)",
	"5(7COM)",
	"9(4D)"
};





const LPCSTR szTestSetCtrl[] =
{
	"SENSe1:MULTiplexer1:STATe",
	"SENSe1:MULTiplexer2:STATe"
};

const LPCSTR szTestSetProp[] =
{
	"SENSe1:MULTiplexer1:DISPlay:STATe",
	"SENSe1:MULTiplexer2:DISPlay:STATe"
};

const LPCSTR szTSCtrlLine1[] =
{
	"SENSe*:MULTiplexer1:OUTPut:DATA",
	"SENSe*:MULTiplexer2:OUTPut:DATA"
};

const LPCSTR szTSCtrlLine4[4][2] =
{
	{
		"SENSe*:MULTiplexer1:OUTPut:A:DATA",
		"SENSe*:MULTiplexer2:OUTPut:A:DATA"
	}
	,
	{
		"SENSe*:MULTiplexer1:OUTPut:B:DATA",
		"SENSe*:MULTiplexer2:OUTPut:B:DATA"
	}
	,
	{
		"SENSe*:MULTiplexer1:OUTPut:C:DATA",
		"SENSe*:MULTiplexer2:OUTPut:C:DATA"
	}
	,
	{
		"SENSe*:MULTiplexer1:OUTPut:D:DATA",
		"SENSe*:MULTiplexer2:OUTPut:D:DATA"
	}
};


