#include "stdafx.h"

//极坐标子条目
SOFT_SUB_ITEM subitemPolar[] =
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
    FA_POLAR,
    FAS_POLAR,
    CA_POLAR,
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
    FA_POLAR,
    FAS_POLAR,
    CA_POLAR,
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
    FA_POLAR,
    FAS_POLAR,
    CA_POLAR,
    0,
    NULL,
    RESERVE_DWORD4,
    RESERVE_DWORD4
  }
};

//极坐标子菜单
SOFT_SUB_MENU submenuPolar[] =
{
  {
    0,
    0,
    L"Polar\0极坐标\0極坐標\0\0",
    NULL,
    sizeof(subitemPolar) / sizeof(SOFT_SUB_ITEM),
    subitemPolar,
    RESERVE_DWORD4,
    NULL,
    NULL,
    0,
    RESERVE_DWORD4
  }
};

//极坐标主菜单
SOFT_MENU menuPolar =
{
  0,
  0,
  L"Polar\0极坐标\0極坐標\0\0",
  NULL,
  sizeof(submenuPolar) / sizeof(SOFT_SUB_MENU),
  submenuPolar,
  NULL,
  NULL,
  0,
  RESERVE_DWORD4
};
