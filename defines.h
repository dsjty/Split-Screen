#pragma once

#ifndef _INC_WINDOWS
#include <Windows.h>
#endif

//菜单按钮宽度和高度;
#define BtnWidth_W	10
#define BtnHeith_H  36
#define BtnHeith_DH  22

#define BtnHeith_H2  46
#define BtnHeith_Root	34


//画笔句柄
extern HPEN hPen_Gray;

//画刷句柄
extern HBRUSH hPatternBrush_LtBlue;
extern HBRUSH hBrush_Light;
extern HBRUSH hBrush_LightGreen;
extern HBRUSH hBrush_Dark, hCalDlg_bk;

//新UI默认字体
extern HFONT hFont_cfg1, hFont_cfg2;      //字体配置1

//设置输入框类型的定义
#define ITID_UNKNOWN                    0       //未知, 交由原程序处理
#define ITID_GMK                        1       //响应GMk
#define ITID_NUM                        2       //响应num
#define ITID_TEXT                       3       //输入框是文本输入框 (交由原程序处理)
#define ITID_PW_GMK                     4       //浮动输入框的GMk

//曲线配置位图在原程序的资源Id
#define IDB_BMP_X1                      156

#define IDB_BMP_X2_1                    163
#define IDB_BMP_X2_2                    158
#define IDB_BMP_X2_3                    162
#define IDB_BMP_X2_4                    157

#define IDB_BMP_X3_1                    168
#define IDB_BMP_X3_2                    159
#define IDB_BMP_X3_3                    175
#define IDB_BMP_X3_4                    176
#define IDB_BMP_X3_5                    173
#define IDB_BMP_X3_6                    164

#define IDB_BMP_X4_1                    171
#define IDB_BMP_X4_2                    160
#define IDB_BMP_X4_3                    166

#define IDB_BMP_X6_1                    169
#define IDB_BMP_X6_2                    167

#define IDB_BMP_X8_1                    172
#define IDB_BMP_X8_2                    174

#define IDB_BMP_X9_1                    170

#define  IDB_BMP_ShuLShC				177

#define  IDB_BMP_SeLShC					154
#define  IDB_BMP_ShCSeL					150
#define  IDB_BMP_ShLSeC					152
#define  IDB_BMP_SeCShL					153
#define  IDB_BMP_ShLShC					151
#define  IDB_BMP_SeCShC					199	
#define  IDB_BMP_ShCSeC					200
#define  IDB_BMP_SeLShL					201
#define  IDB_BMP_ShLSeL					202
#define  IDB_BMP_User					155


#define GET_BYTE_0(n)           ((BYTE)(((DWORD_PTR)(n)) & 0xff))
#define GET_BYTE_1(n)           ((BYTE)((((DWORD_PTR)(n)) >> 8) & 0xff))
#define GET_BYTE_2(n)           ((BYTE)((((DWORD_PTR)(n)) >> 16) & 0xff))
#define GET_BYTE_3(n)           ((BYTE)((((DWORD_PTR)(n)) >> 24) & 0xff))


#define CHK_FLAGS(v, f)         (((v) & (f)) == (f))
#define CHK_NOFLAGS(v, f)       (((v) & (f)) != (f))
#define CHK_EMPTY(v, f)         (((v) & (f)) == 0)
#define CHK_NONEMPTY(v, f)      (((v) & (f)) != 0)
#define SET_FLAGS(v, f)         ((v) |= (f))
#define NOT_FLAGS(v, f)         ((v) &= ~(f))

#define INC_SUBTEXT             L"%s\r\n%s"
#define INVALID_INDEX           (DWORD)-1


#define ComboBox_AddStringW(hwndCtl, lpsz)  \
((int)(DWORD)::SendMessageW((hwndCtl), CB_ADDSTRING, 0L, (LPARAM)(LPCWSTR)(lpsz)))

#define ComboBox_InsertStringW(hwndCtl, index, lpsz)  \
((int)(DWORD)::SendMessageW((hwndCtl), CB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCWSTR)(lpsz)))

#define ComboBox_DeleteAll(hwnd)  \
	while ((int)SNDMSG((HWND)(hwnd), CB_DELETESTRING , 0, 0) > 0) {} 


extern DWORD dwBaseAdd;

#define BASE										dwBaseAdd

#define TA_ROOT										(void *)(0xD7CD4C)
#define CA_ROOT										(void *)(0x163AC88)




//Preset
#define TA_PRESET									(void *)(0xD820F4)
#define CA_PRESET									(void *)(0x163CA68)




//Calibration
#define CA_CALIBRAT									(void *)0x1639060
#define TA_CALIBRAT									(void *)0xD7727C

//Calibration :: ECal
#define CA_ECAL										(void *)0x1638E20
#define TA_ECAL										(void *)0xD778BC

//Calibration :: ECal::1-Port Cal
#define CA_ECAL_PORTCAL								(void *)0x1638B20
#define TA_ECAL_PORTCAL								(void *)0xD778EC

//Calibration :: ECal::Thru CAL
#define CA_ECAL_THRUCAL								(void *)0x1638CA0
#define TA_ECAL_THRUCAL								(void *)0xD779DC

//Calibration :: ECal::Enhanced Response
#define CA_ECAL_EnhRes								(void *)0x1638D00
#define TA_ECAL_EnhRes								(void *)0xD77A18

//Calibration :: ECal::Characterization
#define CA_ECAL_CHAR								(void *)0x1638D60
#define TA_ECAL_CHAR								(void *)0xD77A5C

//Calibration :: ECal::Orientation
#define CA_ECAL_ORIT								(void *)0x1638DC0
#define TA_ECAL_ORIT								(void *)0xD77AD0

//Calibration :: ECal::ECAL
#define CA_ECAL_ECAL								(void *)0x1639540
#define TA_ECAL_ECAL								(void *)0xD79564


//Calibration :: Calibrate
#define CA_CAL_CAL									(void *)0x1638AB8
#define TA_CAL_CAL									(void *)0xD7756C

//Calibration :: Calibrate::Response(open)
#define TA_CAL_CAL_Resp_OS							(void *)0xD7818C

//Calibration :: Calibrate::Response(open)::Select Port
#define TA_CAL_CAL_Resp_OS_SP						(void *)0xD77704

//Calibration :: Calibrate::Response(open)::Open
#define TA_CAL_CAL_Resp_OS_OP						(void *)0xD78020

//Calibration :: Calibrate::Response(Thru)
#define CA_CAL_CAL_Resp_T							(void *)0x16385D8
#define TA_CAL_CAL_Resp_T							(void *)0xD775CC

//Calibration :: Calibrate::Response(Thru)::SP
#define TA_CAL_CAL_Resp_T_SP						(void *)0xD77634

//Calibration :: Calibrate::Enhanced
#define CA_CAL_CAL_Enh								(void *)0x1638698
#define TA_CAL_CAL_Enh								(void *)0xD77674

//Calibration :: Calibrate::Enhanced::Select Port
#define CA_CAL_CAL_Enh_SP								(void *)0x1638638
#define TA_CAL_CAL_Enh_SP								(void *)0xD776A4

//Calibration :: Calibrate::XXX::Cancel		(通用)
#define CA_CAL_CAL_XX_CANCEL						(void *)0x1638458
#define TA_CAL_CAL_XX_CANCEL						(void *)0xD775fc

//Calibration :: Calibrate::1-Port Cal
#define CA_CAL_CAL_OnePCal							(void *)0x16386F8
#define TA_CAL_CAL_OnePCal							(void *)0xD776D4

//Calibration :: Calibrate::1-Port Cal::Select Port
#define TA_CAL_CAL_OnePCal_SP						(void *)0xD77704

//Calibration :: Calibrate::1-Port Cal::Open
#define TA_CAL_CAL_OnePCal_OP						(void *)0xD78020

//Calibration :: Calibrate::2-Port Cal
#define TA_CAL_CAL_TWOPCal							(void *)0xD77748
//Calibration :: Calibrate::2-Port Cal::Re
#define TA_CAL_CAL_TWOPCal_R						(void *)0xD77778
//Calibration :: Calibrate::2-Port Cal::Trans
#define TA_CAL_CAL_TWOPCal_T						(void *)0xD777D8
//Calibration :: Calibrate::2-Port Cal::Iso
#define TA_CAL_CAL_TWOPCal_I						(void *)0xD77808

//Calibration :: Calibrate::2-Port TRL Cal
#define TA_CAL_CAL_2TRLCal							(void *)0x0D77850

//Calibration :: Calibrate::2-Port TRL Cal::Thru/Line
#define TA_CAL_CAL_2TRLCal_TL							(void *)0x0D777D8
//Calibration :: Calibrate::2-Port TRL Cal::Reflect
#define TA_CAL_CAL_2TRLCal_REF							(void *)0x0D77880
//Calibration :: Calibrate::2-Port TRL Cal::Line/Match
#define TA_CAL_CAL_2TRLCal_LM							(void *)0x0D777D8


//Calibration :: Calibrate::AdapterRemoval
#define CA_CAL_CAL_AdaRe       					(void *)0x1638578
#define TA_CAL_CAL_AdaRe					    (void *)0xD77D88


//Calibration :: Clear
#define CA_CAL_CLS						(void *)0x1638A58
#define TA_CAL_CLS						(void *)0xD77534


//Calibration :: Cal Kit
#define CA_CAL_CALK						(void *)0x1638518
#define TA_CAL_CALK						(void *)0xD772AC

//Calibration :: Modify Cal Kit
#define CA_CAL_MCK						(void *)0x16389F8
#define TA_CAL_MCK						(void *)0xD772F0

//Calibration :: Modify Cal Kit :: Define STDs
#define CA_CAL_MCK_DSTD					(void *)0x16387B8
#define TA_CAL_MCK_DSTD					(void *)0xD77320

//Calibration :: Modify Cal Kit :: Define STDs::ALL
#define TA_CALMCK_DSTD_ALL			(void *)0xD77350

//Calibration :: Modify Cal Kit :: Define STDs::Short(m)::STD Type
#define CA_CAL_MCK_DSTD_SHORTm_STD			(void *)0x16392D8
#define TA_CAL_MCK_DSTD_SHORTm_STD			(void *)0xD771BC		//???

//Calibration :: Modify Cal Kit :: Define STDs::ALL::STD Type
#define CA_CAL_MCK_DSTD_ALL_STD				(void *)0x16392D8
#define TA_CAL_MCK_DSTD_ALL_STD				(void *)0xD781BC

//Calibration :: Modify Cal Kit :: Define STDs::Thru::LengthType
#define TA_CAL_MCK_DSTD_THRU_LENTP			(void *)0xD77380


//Calibration :: Modify Cal Kit :: Specify CLSs
#define CA_CAL_MCK_SPCCLS					(void *)0x16388D8
#define TA_CAL_MCK_SPCCLS					(void *)0xD773E0

//Calibration :: Modify Cal Kit :: Specify CLSs::Sub Class
#define CA_CAL_MCK_SPCCLS_SUBCLA				(void *)0x1638878
#define TA_CAL_MCK_SPCCLS_SUBCLA				(void *)0xD7744C

//Calibration :: Modify Cal Kit :: Specify CLSs::Open&Short&load
#define TA_CAL_MCK_SPCCLS_OSL					(void *)0xD78220
//Calibration :: Modify Cal Kit :: Specify CLSs::Open::SetAll
#define CA_CAL_MCK_SPCCLS_OSL_SA				(void *)0x1639130
#define TA_CAL_MCK_SPCCLS_OSL_SA				(void *)0xD78280
//Calibration :: Modify Cal Kit :: Specify CLSs::Open::Port
#define TA_CAL_MCK_SPCCLS_OSL_PORTn				(void *)0xD78250



//Calibration :: Modify Cal Kit :: Specify CLSs::Thru&TRLLine/Match
#define TA_CAL_MCK_SPCCLS_THRU					(void *)0xD782D4
//Calibration :: Modify Cal Kit :: Specify CLSs::Thru&TRLLine/Match::SetAll
#define CA_CAL_MCK_SPCCLS_THRU_SA					(void *)0x16391b0
#define TA_CAL_MCK_SPCCLS_THRU_SA					(void *)0xD78340
//Calibration :: Modify Cal Kit :: Specify CLSs::Thru&TRLLine/Match::Port
#define TA_CAL_MCK_SPCCLS_THRU_PORT					(void *)0xD78304

//Calibration :: Modify Cal Kit :: Specify CLSs::TRL Reflect
#define CA_CAL_MCK_SPCCLS_TRLREF						(void *)0x1638818
#define TA_CAL_MCK_SPCCLS_TRLREF						(void *)0xD77410


//Calibration :: Modify Cal Kit :: TRL Option
#define CA_CAL_MCK_TRLOp							(void *)0x1638998
#define TA_CAL_MCK_TRLOp							(void *)0xD776E8

//Calibration :: Modify Cal Kit :: Restore Cal Kit
#define CA_CAL_MCK_ResCalKit						(void *)0x1638938
#define TA_CAL_MCK_ResCalKit						(void *)0xD774A8

//Calibration :: PortExtensions
#define CA_CAL_PE								(void *)0x1638fa0
#define TA_CAL_PE								(void *)0xD77dc8

//Calibration :: PortExtensions::Auto Port Extension
#define CA_CAL_PE_AUTOPE								(void *)0x1638F40
#define TA_CAL_PE_AUTOPE								(void *)0xD77DF8

//Calibration :: PortExtensions::Auto Port Extension::SelectPorts
#define CA_CAL_PE_AUTOPE_SP							(void *)0x1638EE0
#define TA_CAL_PE_AUTOPE_SP							(void *)0xD77E58

//Calibration :: PortExtensions::Auto Port Extension::Measure OPEN/SHORT
#define TA_CAL_PE_AUTOPE_MOP							(void *)0xD77E88

//Calibration :: PortExtensions::Auto Port Extension::Method
#define CA_CAL_PE_AUTOPE_MT							(void *)0x1638e80
#define TA_CAL_PE_AUTOPE_MT							(void *)0xD77E28

//Calibration :: PortExtensions::Extension Port1
#define TA_CAL_PE_EP1								(void *)0xD77ee4

//Calibration :: PortExtensions::Extension Port1::Loss
#define TA_CAL_PE_EP1_LOS								(void *)0xD77f14


//Calibration ::Power Calibration
#define CA_CAL_PWCAL								(void *)0x163a988
#define TA_CAL_PWCAL								(void *)0xD7C1B0

//Calibration ::Power Calibration::SelectPort
#define CA_CAL_PWCAL_SP								(void *)0x163A860
#define TA_CAL_PWCAL_SP								(void *)0xD7C1E0

//Calibration ::Power Calibration::LossCompen
#define CA_CAL_PWCAL_LC								(void *)0x163A928
#define TA_CAL_PWCAL_LC								(void *)0xD7C210

//Calibration ::Power Calibration::LossCompen::Clear
#define CA_CAL_PWCAL_LC_CLS							(void *)0x163A8C0
#define TA_CAL_PWCAL_LC_CLS							(void *)0xD7C240

//Calibration ::Power Calibration::Sensor A Settings
#define TA_CAL_PWCAL_SAS							(void *)0xD7C41C

//Calibration ::Power Calibration::Sensor A Settings::Clear
#define TA_CAL_PWCAL_SAS_CLS						(void *)0xD7C460


//Calibration ::Receiver Calibration
#define CA_CAL_RECCAL								(void *)0x1639000
#define TA_CAL_RECCAL								(void *)0xD77B44

//Calibration ::Receiver Calibration::SelectPort&SourcePort
#define TA_CAL_RECCAL_SELP								(void *)0xD77B74






//Analysis
#define TA_ANALYSIS									(void *)(0xD74D44)
#define CA_ANALYSIS									(void *)(0x1636DC0)

//Analysis::Fixtre SiMulator
#define TA_ANALY_FIXSIM								(void *)(0xD74D74)
#define CA_ANALY_FIXSIM								(void *)(0x16366E0)

//Analysis::Fixtre SiMulator::Topology
#define TA_ANALY_FIXSIM_TOPO						(void *)(0xD74EE0)
#define CA_ANALY_FIXSIM_TOPO						(void *)(0x1636488)

//Analysis::Fixtre SiMulator::Topology::Device
#define TA_ANALY_FIXSIM_TOPO_DEV					(void *)(0xD7507C)
#define CA_ANALY_FIXSIM_TOPO_DEV					(void *)(0x1636420)

//Analysis::Fixtre SiMulator::Topology(SeBal)::Port1
#define TA_ANALY_FIXSIM_TOPO_SeBal_P1				(void *)(0xD75004)
#define CA_ANALY_FIXSIM_TOPO_SeBal_P1				(void *)(0x16363C0)

//Analysis::Fixtre SiMulator::Topology(bal)::Port1
#define TA_ANALY_FIXSIM_TOPG_BAL_P1					(void *)( 0xD74F50)
#define CA_ANALY_FIXSIM_TOPG_BAL_P1 				(void *)( 0x16362A0)

//Analysis::Fixtre SiMulator::Topology::Port2
#define TA_ANALY_FIXSIM_TOPO_P2						(void *)(0xD74F8C)
#define CA_ANALY_FIXSIM_TOPO_p2						(void *)(0x1636300)

//Analysis::Fixtre SiMulator::Topology::Port3
#define TA_ANALY_FIXSIM_TOPO_P3						(void *)(0xD74FC8)	 

//Analysis::Fixtre SiMulator::Port Matching
#define TA_ANALY_FIXSIM_PMATCH						(void *)(0xD74DA4)
#define CA_ANALY_FIXSIM_PMATCH						(void *)(0x1636120)

//Analysis::Fixtre SiMulator::Port Matching::Select Port
#define TA_ANALY_FIXSIM_SELPORT						(void *)(0xD74DD4)
#define CA_ANALY_FIXSIM_SELPORT						(void *)(0x16360C0)

//Analysis::Fixtre SiMulator::Port Matching::Select Circuit
#define TA_ANALY_FIXSIM_SELCIR						(void *)(0xD769E0)
#define CA_ANALY_FIXSIM_SELCIR						(void *)(0x1637000)

//Analysis::Fixtre SiMulator::Port ZConversion
#define TA_ANALY_FIXSIM_PZCON						(void *)(0xD750BC)
#define CA_ANALY_FIXSIM_PZCON						(void *)(0x16364F0)

//Analysis::Fixtre SiMulator::De-Embedding
#define TA_ANALY_FIXSIM_DeEMBED						(void *)(0xD74E14)
#define CA_ANALY_FIXSIM_DeEMBED						(void *)(0x1636180)

//Analysis::Fixtre SiMulator::De-Embedding::SelectPort
#define TA_ANALY_FIXSIM_DeEMBED_SELPORT				(void *)(0xD74DD4)
#define CA_ANALY_FIXSIM_DeEMBED_SELPORT				(void *)(0x16360C0)

//Analysis::Fixtre SiMulator::De-Embedding::SelectType
#define TA_ANALY_FIXSIM_DeEMBED_SELTYPE				(void *)(0xD76AAC)
#define CA_ANALY_FIXSIM_DeEMBED_SELTYPE				(void *)(0x1637110)

//Analysis::Fixtre SiMulator::Diff Matching
#define TA_ANALY_FIXSIM_DIFFMAT						(void *)(0xD750EC)
#define CA_ANALY_FIXSIM_DIFFMAT						(void *)(0x16365B0)

//Analysis::Fixtre SiMulator::Diff Matching::Select Bal Por
#define TA_ANALY_FIXSIM_DIFFMAT_SBP					(void *)(0xD7511C)
#define CA_ANALY_FIXSIM_DIFFMAT_SBP					(void *)(0x1636550)

//Analysis::Fixtre SiMulator::Diff Matching::Select Circuit
#define TA_ANALY_FIXSIM_DIFFMAT_SC					(void *)(0xD76A3C)
#define CA_ANALY_FIXSIM_DIFFMAT_SC					(void *)(0x1637088)

//Analysis::Fixtre SiMulator::Diff ZConversion
#define TA_ANALY_FIXSIM_DIFFZCON					(void *)(0xD7515C)
#define CA_ANALY_FIXSIM_DIFFZCON					(void *)(0x1636610)

//Analysis::Fixtre SiMulator::Cmn ZConversion
#define TA_ANALY_FIXSIM_CMNZCON						(void *)(0xD7519C)
#define CA_ANALY_FIXSIM_CMNZCON						(void *)(0x1636678)

//Analysis::Fixtre SiMulator::De-Embedding SnP
#define TA_ANALY_FIXSIM_DeEmSNP						(void *)(0xD74E44)
#define CA_ANALY_FIXSIM_DeEmSNP						(void *)(0x1636240)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG				(void *)( 0xD74E74)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG				(void *)( 0x16361E0)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology::Select Topology
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG_SELTOP			(void *)( 0xD76B10)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG_SELTOP			(void *)( 0x1637198)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology::Ports
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG_PORTS			(void *)( 0xD757E4)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG_PORTS 			(void *)( 0x1636E20)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology::Type(nwk1)
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE1			(void *)( 0xD76B68)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE1 			(void *)( 0x1637218)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology::Type(nwk2)
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE2			(void *)( 0xD76BD0)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE2 			(void *)( 0x1637288)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology::Type(nwk3)
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE3			(void *)( 0xD76C38)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE3 			(void *)( 0x16372F8)

//Analysis::Fixtre SiMulator::De-Embedding SnP::Topology::Type(nwk4)
#define TA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE4			(void *)( 0xD76CA0)
#define CA_ANALY_FIXSIM_DeEmSNP_TOPG_TYPE4 			(void *)( 0x1637368)

//Analysis::Gating
#define TA_ANALY_GATING								(void *)( 0xD751E0)
#define CA_ANALY_GATING 							(void *)( 0x16367A0)
														    
//Analysis::Gating::Shape								    
#define TA_ANALY_GATING_SHAPE						(void *)( 0xD76D40)
#define CA_ANALY_GATING_SHAPE 						(void *)( 0x16373D8)
														    
//Analysis::Transform									    
#define TA_ANALY_TRANSFORM							(void *)( 0xD75218)
#define CA_ANALY_TRANSFORM 							(void *)( 0x1636808)
														    
//Analysis::Transform::Type								    
#define TA_ANALY_TRANSFORM_TYPE						(void *)( 0xD76DB8)
#define CA_ANALY_TRANSFORM_TYPE	 					(void *)( 0x1637458)
														    
//Analysis::Transform::Windows							    
#define TA_ANALY_TRANSFORM_WINDOWS					(void *)( 0xD75248)
#define CA_ANALY_TRANSFORM_WINDOWS	 				(void *)( 0x1636740)
														    
//Analysis::Conversion									    
#define TA_ANALY_CONVER								(void *)( 0xD755BC)
#define CA_ANALY_CONVER				 				(void *)( 0x1636740)

//Analysis::Conversion::Function
#define TA_ANALY_CONVER_FUN							(void *)( 0xD755EC)
#define CA_ANALY_CONVER_FUN				 			(void *)( 0x1636D00)

//Analysis::Limit Test
#define TA_LIMITTEST								(void *)( 0xD7528C)
#define CA_LIMITTEST								(void *)( 0x1636990)
															  
//Analysis::Limit Test::Edit Limit Line						  
#define TA_LT_ELL									(void *)( 0xD75300)
#define CA_LT_ELL									(void *)( 0x1636930)
															  
//Analysis::Limit Test::Edit Limit Line::Clear Limit Table	  
#define TA_LT_ELL_CLT								(void *)( 0xD75330)
#define CA_LT_ELL_CLT								(void *)( 0x1636868)
															  
//Analysis::Limit Test::Limit Line Offsets					  
#define TA_LT_LLO									(void *)( 0xD752BC)
#define CA_LT_LLO									(void *)( 0x16368D0)

//Analysis::Limit Test::Limit Line Offsets::Marker->Amplitude Offset					  
#define TA_LT_LLO_MAO								(void *)( 0xD75CB4)
#define CA_LT_LLO_MAO								(void *)( 0x10B34B8)
															  
//Analysis::Ripple Limit									  
#define TA_RIPPLELIMIT								(void *)( 0xD75394)
#define CA_RIPPLELIMIT								(void *)( 0x1636B78)

//Analysis::Ripple Limit::Ripple Value						  
#define TA_RL_RV									(void *)( 0xD75454)
#define CA_RL_RV									(void *)( 0x1636AB8)

//Analysis::Ripple Limit::Ripple Band						  
#define TA_RL_RBW									(void *)( 0xD754A8)
#define CA_RL_RBW									(void *)( 0x1636B18)

//Analysis::Ripple Limit::Edit Ripple Limit					  
#define TA_RL_ERL									(void *)( 0xD753C4)
#define CA_RL_ERL									(void *)( 0x1636A58)

//Analysis::Ripple Limit::Clear Ripple Limit Table			  
#define TA_RL_ERL_CRLT								(void *)( 0xD753F4)
#define CA_RL_ERL_CRLT								(void *)( 0x16369F0)

//Analysis::Bandwidth Limit									  
#define TA_BWLIMIT									(void *)( 0xD75D84)
#define CA_BWLIMIT									(void *)( 0x1636E80)

//Analysis::Point Limit										  
#define TA_POINTLIMIT								(void *)( 0xD754F4)
#define CA_POINTLIMIT								(void *)( 0x1636CA0)

//Analysis::Point Limit::Edit Point Limit					  
#define TA_POINTLIMIT_EPL							(void *)( 0xD75524)
#define CA_POINTLIMIT_EPL							(void *)( 0x1636C40)

//Analysis::Point Limit::Clear Point Limit Table			  
#define TA_POINTLIMIT_CPLT							(void *)( 0xD75554)
#define CA_POINTLIMIT_CPLT							(void *)( 0x1636BD8)

//Analysis::Conversion
#define CA_CONV										(void *)0x01636D60
#define TA_CONV										(void *)0x00D755BC

//Analysis::Conversion :: Function
#define CA_CONV_FN									(void *)0x01636D00
#define TA_CONV_FN									(void *)0x00D755EC


//Display
#define CA_DISPLAY									(void *)(0x16397D8)
#define TA_DISPLAY									(void *)(0xD798B4)

//Display :: Diaplay
#define CA_DISPLAY_DP								(void *)(0x16396B8)
#define TA_DISPLAY_DP								(void *)(0xD79924 )

//Display :: Data Math
#define CA_DISPLAY_DM								(void *)(0x1639718)
#define TA_DISPLAY_DM								(void *)(0xD79974)

//Display ::Alloc Channels
#define CA_ALLOCTRACES								(void *)(0x1639838)      //0x00536F80
#define TA_ALLOCTRACES								(void *)(0xD79C88)

//Display ::Num of Traces
#define CA_TRACESNUM								(void *)(0x1639658)        //0x00538C50
#define TA_TRACESNUM								(void *)(0xD798E4)

//Display ::Alloc Channels
#define CA_ALLOCCHAN								(void *)(0x16398A8)
#define TA_ALLOCCHAN								(void *)(0xD79D18)

//Display ::Data Hold
#define CA_DISPLAY_DH								(void *)(0x1639778)
#define TA_DISPLAY_DH								(void *)(0xD799E0)



//Trigger 
#define CA_TRIGGER									(void *)(0x163D298)
#define TA_TRIGGER									(void *)(0xD834C4)

//Trigger :: Trigger Source
#define CA_TRIGGER_TS								(void *)(0x163D238)
#define TA_TRIGGER_TS								(void *)(0xD834F4)



//Average
#define CA_AVERAGE									(void *)(0x1637BA8)
#define TA_AVERAGE									(void *)(0xD76FD4)




//Stimulus
#define CA_STIMULUS									(void *)(0x163C098)
#define TA_STIMULUS									(void *)(0xD816CC)




//Sweep Setup
#define CA_SWEEPSET									(void *)(0x163C860)
#define TA_SWEEPSET									(void *)(0xD81A44)

//Sweep Setup :: Power
#define CA_SS_PWR									(void *)(0x163C798)
#define TA_SS_PWR									(void *)(0xD81B8C)

//Sweep Setup :: Power :: Port Power
#define CA_SS_PWR_PP								(void *)(0x163C738)
#define TA_SS_PWR_PP								(void *)(0xD81BBC)

//Sweep Setup :: Sweep Type
#define CA_SS_ST									(void *)(0x163C6D8)
#define TA_SS_ST									(void *)(0xD81B24)

//Sweep Setup :: Edit Segment Table
#define CA_SS_EST									(void *)(0x163B2E0)
#define TA_SS_EST									(void *)(0xD7D7D4)

//Sweep Setup :: Edit Segment Table ::  Clear Segment Table
#define CA_SS_EST_CST								(void *)(0x163B278)
#define TA_SS_EST_CST								(void *)(0xD7D804)





//Marker
#define CA_MARKER									(void *)(0x1639FA8)         //0x005418F0
#define TA_MARKER									(void *)(0xD7AE4C)

//Clear Marker
#define CA_CLRMARKER								(void *)(0x1639EE8)         //0x005413F0
#define TA_CLRMARKER								(void *)(0xD7AE7C)

//More Marker
#define CA_MREMARKER								(void *)(0x1639F48)         //0x00541820
#define TA_MREMARKER								(void *)(0xD7AEE0)

//Marker Search
#define CA_MARKERSEA								(void *)(0x163A6C8)	       //0x005553E0
#define TA_MARKERSEA								(void *)(0xD7B454)

//Marker Search::Search Range
#define CA_SEARCHRANGE								(void *)(0x163A668)
#define TA_SEARCHRANGE								(void *)(0xD7B674)

//Marker Search::Peak 
#define CA_PEAKSEA									(void *)(0x163A3C8)
#define TA_PEAKSEA									(void *)(0xD7B520)

//Marker Search::Peak  -> Peak Polarity
#define CA_PEAKSEA_PP								(void *)(0x163A368) 
#define TA_PEAKSEA_PP								(void *)(0xD7B550)

//Marker Search::Target
#define CA_TARGSEA									(void *)(0x163A308)
#define TA_TARGSEA									(void *)(0xD7B484)

//Marker Search::Target -> Target Transition		
#define CA_TARGSEA_TT								(void *)(0x163A2A8)
#define TA_TARGSEA_TT								(void *)(0xD7B4B4)

//Marker Search::Multi Peak							
#define CA_MULPEAKSEA								(void *)(0x163A548)
#define TA_MULPEAKSEA								(void *)(0xD7B608)

//Marker Search::Multi Peak -> Peak Polarity		
#define CA_MULPEAKSEA_PP							(void *)(0x163A4E8)
#define TA_MULPEAKSEA_PP							(void *)(0xD7B638)

//Marker Search::Multi Target
#define CA_MULTARGSEA								(void *)(0x163A488)
#define TA_MULTARGSEA								(void *)(0xD7B598)


//Marker Search::Multi Target -> Target Transition
#define CA_MULTARGSEA_TT							(void *)(0x163A428)
#define TA_MULTARGSEA_TT							(void *)(0xD7B5C8)

//Marker Function
#define CA_MARKERFUNC								(void *)(0x163A1D8)
#define TA_MARKERFUNC								(void *)(0xD7B18C)

//Annotation Options
#define CA_MFAO										(void *)(0x163A178)
#define TA_MFAO										(void *)(0xD7B1BC)




//Measurement
#define TA_SPARAM									(void *)(0xD7B024)
#define CA_SPARAM									(void *)(0x163A0E8) 

//Measurement::Absolute										
#define TA_SPARAM_ABSOLUTE							(void *)(0xDA97D8)
#define CA_SPARAM_ABSOLUTE							(void *)(0x163A020)

//Measurement::Aux Input									
#define TA_SPARAM_AUXINPUT							(void *)(0xD7B084)

//Measurement::Aux Input::Sweep Port						
#define TA_SPARAM_AUXINPUT_SP						(void *)(0xD7B0B4)
#define CA_SPARAM_AUXINPUT_SP						(void *)(0x163A088)




//FORMAT
#define TA_FORMAT									(void *)(0xD7A30C)
#define CA_FORMAT									(void *)(0x1639B88)

//FORMAT::SIMTH
#define TA_SIMTH									(void *)(0xD7A348)
#define CA_SIMTH									(void *)(0x1639A88)

//FORMAT::Polar
#define TA_POLAR									(void *)(0xD7A378)
#define CA_POLAR									(void *)(0x1639B08)





//SCALE
#define TA_SCALE									(void *)(0xD7D384)
#define CA_SCALE									(void *)(0x163B1E8)

//SCALE::ELECTRICAL DELAY
#define TA_ELECTDELAY								(void *)(0xD7D3B4)
#define CA_ELECTDELAY								(void *)(0x163B188)  





//Macro Setup
#define CA_MACRO            (void *)(0x1639DF0)
#define TA_MACRO            (void *)(0xD7ABC4)

//Macro Setup :: Select Macro		 
#define CA_MACRO_SM         (void *)(0x1639D30)
#define TA_MACRO_SM         (void *)(0xD7AC80)

//Macro Setup :: User Menu			 
#define CA_MACRO_UM         (void *)(0x1639D90)
#define TA_MACRO_UM         (void *)(0xD7AB74)

//Macro Setup :: Load & Run			 
#define CA_MACRO_LR         (void *)(0x1639E50)
#define TA_MACRO_LR         (void *)(0xD7ACE4)



//Save/Recall
#define CA_SR               (void *)(0x163B060)
#define TA_SR               (void *)(0xD7CE1C)

//Save/Recall :: Save State			 
#define CA_SR_SS            (void *)(0x163AD60)
#define TA_SR_SS            (void *)(0xD7CE4C)

//Save/Recall :: Recall State		 
#define CA_SR_RS            (void *)(0x163ADC0)
#define TA_SR_RS            (void *)(0xD7CE88)

//Save/Recall :: Recall By File Name 
#define CA_SR_RBFN          (void *)(0x163B0C0)
#define TA_SR_RBFN          (void *)(0xD7D124)

//Save/Recall :: Save Channel		 
#define CA_SR_SC            (void *)(0x163AE80)
#define TA_SR_SC            (void *)(0xD7CEC8)

//Save/Recall :: Save Channel :: Clear States
#define CA_SR_SC_CS         (void *)(0x163AE20)
#define TA_SR_SC_CS         (void *)(0xD7CEF8)

//Save/Recall :: Recall Channel
#define CA_SR_RC            (void *)(0x163AEE0)
#define TA_SR_RC            (void *)(0xD7CF48)

//Save/Recall :: Save Type			 
#define CA_SR_ST            (void *)(0x163AF40)
#define TA_SR_ST            (void *)(0xD7CF94)

//Save/Recall :: Save Snp			 
#define CA_SR_SSNP          (void *)(0x163B000)
#define TA_SR_SSNP          (void *)(0xD7CFF8)

//Save/Recall :: Save Snp::Snp Format
#define CA_SR_SSNP_SF       (void *)(0x163AFA0)
#define TA_SR_SSNP_SF       (void *)(0xD7D028)

//Save/Recall :: Save Snp::S%nP	 
#define TA_SR_SSNP_S1P      (void *)(0xD7D094)




//System
#define CA_SYSTEM           (void *)(0x163D070)
#define TA_SYSTEM           (void *)(0xD82130)

//System::Multiport Test Set Setup	 
#define CA_SYSTEM_MTSS		(void *)(0x16399B0)
#define TA_SYSTEM_MTSS		(void *)(0xD79ECC)

//System::Multiport Test Set Setup::Test Set %d			
#define TA_SYSTEM_MTSS_TS		(void *)(0xD79EFC)

//System::Multiport Test Set Setup::Test Set %d	::Port %d
#define TA_SYSTEM_MTSS_TS_P		(void *)(0xD79F6C)

//System::Multiport Test Set Setup::Test Set %d	::Select Test Set
#define TA_SYSTEM_MTSS_TS_STS   (void *)(0xD7A1AC)  


//System :: Misc Setup
#define CA_SYS_MISC         (void *)(0x163D010)
#define TA_SYS_MISC         (void *)(0xD82160)

//System :: Misc Setup :: GPIB Setup
#define CA_SYS_MISC_GPIB    (void *)(0x163CB88)
#define TA_SYS_MISC_GPIB    (void *)(0xD821C8)

//System :: Misc Setup :: GPIB Setup::Signal Generator Address
#define CA_SYS_MISC_GPIB_SGA    (void *)0x0
#define TA_SYS_MISC_GPIB_SGA    (void *)(0xD821F8)

//System :: Misc Setup :: Network Setup
#define CA_SYS_MISC_NET     (void *)(0x163CD10)
#define TA_SYS_MISC_NET     (void *)(0xD82358)

//System :: Misc Setup :: Power Meter Setup
#define CA_SYS_MISC_PMS     (void *)(0x163CCB0)
#define TA_SYS_MISC_PMS     (void *)(0xD82288)

//System :: Misc Setup :: Power Meter Setup :: Select Type
#define CA_SYS_MISC_ST     (void *)(0x163CBF0)
#define TA_SYS_MISC_ST     (void *)(0xD822B8)

//System :: Misc Setup :: Power Meter Setup :: USB
#define CA_SYS_MISC_USB     (void *)(0x163CC50)
#define TA_SYS_MISC_USB     (void *)(0xD822F4)

//System :: Misc Setup :: Beeper
#define CA_SYS_MISC_BEEP    (void *)(0x163CAC8)
#define TA_SYS_MISC_BEEP    (void *)(0xD82190)

//System :: Misc Setup :: Clock Setup
#define CA_SYS_MISC_CLOCK   (void *)(0x163CD70)
#define TA_SYS_MISC_CLOCK   (void *)(0xD82398)

//System :: Misc Setup :: Key Lock
#define CA_SYS_MISC_KL		(void *)(0x163CDD0)
#define TA_SYS_MISC_KL	    (void *)(0xD823D4)

//System :: Misc Setup :: Display Setup
#define CA_SYS_MISC_DS      (void *)(0x163CEF0)
#define TA_SYS_MISC_DS      (void *)(0xD82538)

//System :: Misc Setup :: Channel/Trace Setup
#define CA_SYS_MISC_CTS     (void *)(0x163D0D8)
#define TA_SYS_MISC_CTS     (void *)(0xD82C50)

//System :: Misc Setup :: Preset
#define CA_SYS_MISC_PR      (void *)(0x163CFB0)
#define TA_SYS_MISC_PR      (void *)(0xD82578)

//System :: Misc Setup :: Preset :: State
#define CA_SYS_MISC_PR_S    (void *)(0x163CF50)
#define TA_SYS_MISC_PR_S    (void *)(0xD825A8)



//System :: Misc Setup :: Display Setup :: Color Setup
#define CA_COLR              (void *)0x0163CE90
#define TA_COLR              (void *)0x00D82410

//System :: Misc Setup :: Display Setup :: Color Setup :: (Normal / Invert)
#define TA_COLR_XX           (void *)0x00D82440

//System :: Misc Setup :: Display Setup ::  Color Setup :: (Normal / Invert) :: Reset Color
#define TA_COLR_XX_RC        (void *)0x00D824E0

//System :: Misc Setup :: Display Setup :: Color Setup :: (Normal / Invert) :: RGB
#define CA_COLR_XX_RGB       (void *)0x0163CE30
#define TA_COLR_XX_RGB       (void *)0x00D82470

//System :: Misc Setup :: Display Setup :: Color Setup :: (Normal / Invert) :: RGB :: (R /G /B)
#define TA_COLR_XX_RGB_X     (void *)0x00D824A0


//System :: Service Menu
#define CA_SYS_SERMEU			(void *)(0x163BC90)
#define TA_SYS_SERMEU			(void *)(0xD7E0E0)

//System :: Service Menu ::Test Menu
#define CA_SYS_SERMEU_TEST		(void *)(0x163BB10)
#define TA_SYS_SERMEU_TEST		(void *)(0xD7E748)

//System :: Service Menu ::External Test Set
#define CA_SYS_SERMEU_ETS		(void *)(0x163BB70)
#define TA_SYS_SERMEU_ETS		(void *)(0xD7E784)

//System :: Service Menu ::Channel/Trace Setup
#define TA_SYS_SERMEU_CTS		(void *)(0xD7F4A0)

//System :: Service Menu ::Init Src Port
#define CA_SYS_SERMEU_ISP		(void *)(0x163BBD0)
#define TA_SYS_SERMEU_ISP		(void *)(0xD7E7D8)

//System :: Service Menu ::Security Level
#define CA_SYS_SERMEU_SECLEV	(void *)(0x163BC30)
#define TA_SYS_SERMEU_SECLEV	(void *)(0xD7E818)


