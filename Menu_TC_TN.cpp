#include "stdafx.h"

//曲线数子条目
SOFT_SUB_ITEM subitemTracesNum[] =
{
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE | SIA_GROUP,
    SIS_RadioButtonEx,
    0,
    L" 1 \0 1 \0 1 \0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_TRACESNUM,
    FAS_TRACESNUM,
    CA_TRACESNUM,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButtonEx,
    1,
    L" 2 \0 2 \0 2 \0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_TRACESNUM,
    FAS_TRACESNUM,
    CA_TRACESNUM,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButtonEx,
    2,
    L" 3 \0 3 \0 3 \0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_TRACESNUM,
    FAS_TRACESNUM,
    CA_TRACESNUM,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButtonEx,
    3,
    L" 4 \0 4 \0 4 \0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_TRACESNUM,
    FAS_TRACESNUM,
    CA_TRACESNUM,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
};

//曲线数子菜单
SOFT_SUB_MENU submenuTracesNum[] =
{
  {
    0,
    0,
    L"Number of Traces\0曲线数\0曲線數\0\0",
    NULL,
    sizeof(subitemTracesNum) / sizeof(SOFT_SUB_ITEM),
    subitemTracesNum,
    RESERVE_DWORD4,
    NULL,
    NULL,
    0,
    RESERVE_DWORD4
  }
};

//曲线数主菜单
SOFT_MENU menuTracesNum =
{
  0,
  0,
  L"Number of Traces\0曲线数\0曲線數\0\0",
  NULL,
  sizeof(submenuTracesNum) / sizeof(SOFT_SUB_MENU),
  submenuTracesNum,
  NULL,
  NULL,
  0,
  RESERVE_DWORD4
};
