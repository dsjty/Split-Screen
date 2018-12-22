#include "stdafx.h"

//史密斯子条目
SOFT_SUB_ITEM subitemSimth[] =
{
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE | SIA_GROUP,
    SIS_RadioButton,
    0,
    L"Lin / Phase\0线性 / 相位\0線性 / 相位\0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_SIMTH,
    FAS_SIMTH,
    CA_SIMTH,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButton,
    1,
    L"Log / Phase\0对数 / 相位\0對數 / 相位\0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_SIMTH,
    FAS_SIMTH,
    CA_SIMTH,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButton,
    2,
    L"Real / Imag\0实部 / 虚部\0實部 / 虛部\0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_SIMTH,
    FAS_SIMTH,
    CA_SIMTH,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButton,
    3,
    L"R + jX\0R + jX\0R + jX\0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_SIMTH,
    FAS_SIMTH,
    CA_SIMTH,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
  ,
  {
    SIF_DIRECTFUNC,
    SIA_FULLLINE,
    SIS_RadioButton,
    4,
    L"G + jB\0G + jB\0G + jB\0\0",
    NULL,
    16,
    24,
    NULL,
    RESERVE_DWORD16,
    0,
    NULL,
    FA_SIMTH,
    FAS_SIMTH,
    CA_SIMTH,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
};

//史密斯子菜单
SOFT_SUB_MENU submenuSimth[] =
{
  {
    0,
    0,
    L"Simth\0史密斯圆图\0史密斯圓圖\0\0",
    NULL,
    sizeof(subitemSimth) / sizeof(SOFT_SUB_ITEM),
    subitemSimth,
    RESERVE_DWORD4,
    NULL,
    NULL,
    0,
    RESERVE_DWORD4
  }
};

//史密斯主菜单
SOFT_MENU menuSimth = 
{
  0,
  0,
  L"Simth\0史密斯圆图\0史密斯圓圖\0\0",
  NULL,
  sizeof(submenuSimth) / sizeof(SOFT_SUB_MENU),
  submenuSimth,
  NULL,
  NULL,
  0,
  RESERVE_DWORD4
};
