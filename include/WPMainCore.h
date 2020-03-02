#ifndef _WP_MAIN_CORE_H_
#define _WP_MAIN_CORE_H_

#if __GNUC__ >= 4
#define WPMAINCORE_API __attribute__ ((visibility("default")))
#else
#define WPMAINCORE_API
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifndef CT_STD_TYPES
#define CT_STD_TYPES
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed int          INT32;
typedef long long           INT64;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;
#endif
typedef void *              HANDLE;


#define WP_SUCCESS							(0)
#define WP_ERROR_INVALID_PARAMETERS			(-1)
#define WP_ERROR_UNSUPPORTED				(-2)
#define WP_ERROR_EXCEPTION					(-3)
#define WP_ERROR_BUSY						(-4)
#define WP_ERROR_CREATEFAILED				(-5)
#define WP_ERROR_OPENFAILED					(-6)
#define WP_ERROR_TIMEOUT					(-7)
#define WP_ERROR_BUFFNOTENOUGH				(-8)
#define WP_ERROR_LACKOFRESOURCE				(-9)

#define MAX_METERING_REGIONS_NUM			4
#define MAX_LUT_NUM							4
#define MAX_SENSITIVITY_LEVEL				3

typedef struct _RawFrameInfo
{
	UINT32			Size;               /* sizeof(RawFrameInfo) */
	UINT32			ImageFormat;        /* YUV420SP, YUV422SP */
	UINT32          ImageWidth;
	UINT32          ImageHeight;
	UINT32			FrameIndex;
	UINT32		    Timestamp_sec;
	UINT32		    Timestamp_usec;
	UINT32			TriggerSource;      /* 1 -> continus frame, 2 -> soft trig, other -> external trig*/
	UINT32			FlashlampState;
	UINT32			ExposureTime;
	float			Gain;
	UINT32          LuminanceMin[MAX_METERING_REGIONS_NUM];
	UINT32          LuminanceMax[MAX_METERING_REGIONS_NUM];
	UINT32          LuminanceSum[MAX_METERING_REGIONS_NUM];
}RawFrameInfo;

typedef struct _WP_RAWFRAME
{
	UINT32			Version;
	void			*pDataBuf;
	UINT32			DataBufSize;
	RawFrameInfo	FrameInfo;
}WP_RAWFRAME;

enum ImageAcquisition_WorkMode
{
	IA_WorkMode_ContinuousFrame,
	IA_WorkMode_SingleFrame,
	IA_WorkMode_MAX
};

enum
{
	WP_RAWIMAGE_FORMAT_YUV420SP = 0,
	WP_RAWIMAGE_FORMAT_YUV422SP,
	WP_RAWIMAGE_FORMAT_BGR24,
	WP_RAWIMAGE_FORMAT_MONO,
	WP_RAWIMAGE_FORMAT_BAYER,
	WP_RAWIMAGE_FORMAT_MAX
};

enum
{
	WP_EXPOSUREMODE_MANUAL,
	WP_EXPOSUREMODE_AUTO,
	WP_EXPOSUREMODE_MAX
};

enum
{
	WP_WBMODE_DISABLE,
	WP_WBMODE_AUTO,
	WP_WBMODE_MANUAL,
	WP_WBMODE_MAX
};

enum
{
	WP_HDRMODE_DISABLE,
	WP_HDRMODE_WEAK,
	WP_HDRMODE_STAND,
	WP_HDRMODE_EXTREME,
	WP_HDRMODE_MAX
};

enum
{
	WP_LUTMODE_BY_TABLE,
	WP_LUTMODE_BY_GAMMA,
	WP_LUTMODE_BY_CONTRAST,
	WP_LUTMODE_MAX
};

enum
{
	WP_MATRIX_USE_TO_CORLORCORRECTION,
	WP_MATRIX_USE_TO_IMAGEENHANCEMENT,
	WP_MATRIX_USE_TO_MAX
};

#define WP_INVALID_LUT_ID		0xffffffff

enum
{
	WP_RESOLUTION_MODE_ALLPIXEL,
	WP_RESOLUTION_MODE_ROI,
	WP_RESOLUTION_MODE_FULLHD,
	WP_RESOLUTION_MODE_MAX
};

#define WP_MAX_OUT_IO_NUM		8
#define WP_MAX_IN_IO_NUM		8
#define WP_MAX_OWN_LED_STRENGTH	330
#define WP_MAX_EXT_LED_STRENGTH	1500
#define WP_MAX_STATUS_LED_NUM	3
#define WP_MAX_GLITCH_FILTER_INUS	(42*65535)

enum
{
	WP_MODE_DISABLED = 0,
	WP_MODE_ENABLED = 1
};

enum
{
	WP_TRIGIN_MODE_CLOSE,
	WP_TRIGIN_MODE_POS,
	WP_TRIGIN_MODE_NEG,
	WP_TRIGIN_MODE_BOTH,
	WP_TRIGIN_MODE_MAX
};

enum
{
	WP_LEDDRIVER_MODE_CLOSE,
	WP_LEDDRIVER_MODE_SYNC,
	WP_LEDDRIVER_MODE_STROBE,
	WP_LEDDRIVER_MODE_CONSTANT,
	WP_LEDDRIVER_MODE_MAX
};

enum
{
	WP_STATUSLED_CLOSED,
	WP_STATUSLED_RED,
	WP_STATUSLED_GREEN,
	WP_STATUSLED_RED_BLINK,
	WP_STATUSLED_GREEN_BLINK,
	WP_STATUSLED_RG_BLINK,
	WP_STATUSLED_MAX
};

enum
{
	WP_OUTPUTIOSTATE_TURN_ON = 0,
	WP_OUTPUTIOSTATE_TURN_OFF = 1,
	WP_OUTPUTIOSTATE_FLASHLAMP_SYNC,
	WP_OUTPUTIOSTATE_FLASHLAMP_STROBE,
	WP_OUTPUTIOSTATE_EXPOSURE_SYNC,
	WP_OUTPUTIOSTATE_MAX
};

enum
{
	WP_GLITCHFILTER_ID_IO_0,
	WP_GLITCHFILTER_ID_IO_1,
	WP_GLITCHFILTER_ID_IO_2,
	WP_GLITCHFILTER_ID_IO_3,
	WP_GLITCHFILTER_ID_IO_4,
	WP_GLITCHFILTER_ID_IO_5,
	WP_GLITCHFILTER_ID_IO_6,
	WP_GLITCHFILTER_ID_IO_7,
	WP_GLITCHFILTER_ID_IO_TRIGIN,
	WP_GLITCHFILTER_ID_IO_ALL,
	WP_GLITCHFILTER_ID_IO_MAX,
};


WPMAINCORE_API int Roseek_MainCore_Init(UINT32 IsShowLogWindow);
WPMAINCORE_API int Roseek_MainCore_UnInit();
WPMAINCORE_API int Roseek_MainCore_SetLogLevel(UINT32 Level);

//ImageAcquisition
WPMAINCORE_API int Roseek_ImageAcquisition_Start();
WPMAINCORE_API int Roseek_ImageAcquisition_Stop();
WPMAINCORE_API int Roseek_ImageAcquisition_FetchFrame(void *pFrameBuff, UINT32 BuffSize, RawFrameInfo *pFrameInfo, UINT32 TimeOutInMS);
WPMAINCORE_API int Roseek_ImageAcquisition_FetchFrameEx(WP_RAWFRAME **ppFrame, UINT32 TimeOutInMS);
WPMAINCORE_API int Roseek_ImageAcquisition_ReleaseFrame(WP_RAWFRAME *pFrame);
WPMAINCORE_API int Roseek_ImageAcquisition_SetWorkMode(UINT32 Mode);
WPMAINCORE_API int Roseek_ImageAcquisition_GetWorkMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_ImageAcquisition_SendSoftTrig();
WPMAINCORE_API int Roseek_ImageAcquisition_SetRawImageFormat(UINT32 Format);
WPMAINCORE_API int Roseek_ImageAcquisition_GetRawImageFormat(UINT32 *pFormat);
WPMAINCORE_API int Roseek_ImageAcquisition_SetSensitivityLevel(UINT32 Level);
WPMAINCORE_API int Roseek_ImageAcquisition_GetSensitivityLevel(UINT32 *pLevel);
WPMAINCORE_API int Roseek_ImageAcquisition_SetResolution(UINT32 ResolutionMode, UINT32 x, UINT32 y, UINT32 cx, UINT32 cy);
WPMAINCORE_API int Roseek_ImageAcquisition_GetResolution(UINT32 *pResolutionMode, UINT32 *pX, UINT32 *pY, UINT32 *pCX, UINT32 *pCY);
WPMAINCORE_API int Roseek_ImageAcquisition_GetMaxResolution(UINT32 *pWidth, UINT32 *pHeight);
WPMAINCORE_API int Roseek_ImageAcquisition_SetFrameRate(float FrameRate);
WPMAINCORE_API int Roseek_ImageAcquisition_GetFrameRate(float *pFrameRate);
WPMAINCORE_API int Roseek_ImageAcquisition_GetCurMaxFrameRate(float *pFrameRate);
WPMAINCORE_API int Roseek_ImageAcquisition_SetFramesPreConfig(UINT32 FrameNum, UINT32 FrameSize);
WPMAINCORE_API int Roseek_ImageAcquisition_GetFramesPreConfig(UINT32 *pFrameNum, UINT32 *pFrameSize);
WPMAINCORE_API int Roseek_ImageAcquisition_SetGlobalReset(UINT32 IsEnable);

//CapturingParameters
WPMAINCORE_API int Roseek_CapturingParameters_SetExposureMode(UINT32 ExposureMode);
WPMAINCORE_API int Roseek_CapturingParameters_GetExposureMode(UINT32 *pExposureMode);
WPMAINCORE_API int Roseek_CapturingParameters_SetAutoExposureAdjustGap(UINT32 Gap);
WPMAINCORE_API int Roseek_CapturingParameters_GetAutoExposureAdjustGap(UINT32 *pGap);
WPMAINCORE_API int Roseek_CapturingParameters_SetExposureTime(UINT32 ExposureTime_us);
WPMAINCORE_API int Roseek_CapturingParameters_GetExposureTime(UINT32 *pExposureTime_us);
WPMAINCORE_API int Roseek_CapturingParameters_GetCurRealExposureTime(UINT32 *pExposureTime_us);
WPMAINCORE_API int Roseek_CapturingParameters_SetExposureTimeUpperLimit(UINT32 ExposureTime);
WPMAINCORE_API int Roseek_CapturingParameters_GetExposureTimeUpperLimit(UINT32 *pExposureTime);
WPMAINCORE_API int Roseek_CapturingParameters_SetExposureTimeLowerLimit(UINT32 ExposureTime);
WPMAINCORE_API int Roseek_CapturingParameters_GetExposureTimeLowerLimit(UINT32 *pExposureTime);
WPMAINCORE_API int Roseek_CapturingParameters_SetGain(float Gain);
WPMAINCORE_API int Roseek_CapturingParameters_GetGain(float *pGain);
WPMAINCORE_API int Roseek_CapturingParameters_GetMaxGain(float *pGain);
WPMAINCORE_API int Roseek_CapturingParameters_GetCurRealGain(float *pGain);
WPMAINCORE_API int Roseek_CapturingParameters_SetGainUpperLimit(float Gain);
WPMAINCORE_API int Roseek_CapturingParameters_GetGainUpperLimit(float *pGain);
WPMAINCORE_API int Roseek_CapturingParameters_SetExpectedBrightness(UINT32 Brightness);
WPMAINCORE_API int Roseek_CapturingParameters_GetExpectedBrightness(UINT32 *pBrightness);
WPMAINCORE_API int Roseek_CapturingParameters_SetMeteringRegion(UINT32 id, UINT32 x, UINT32 y, UINT32 Width, UINT32 Height);
WPMAINCORE_API int Roseek_CapturingParameters_GetMeteringRegion(UINT32 id, UINT32 *pX, UINT32 *pY, UINT32 *pWidth, UINT32 *pHeight);
WPMAINCORE_API int Roseek_CapturingParameters_GetMeteringRegionMeanValue (UINT32 id, UINT32 *pYRGBValues);
WPMAINCORE_API int Roseek_CapturingParameters_GetMeteringRegionMeanValueBeforeLUT(UINT32 id, UINT32 *pYRGBValues);

//ISP
WPMAINCORE_API int Roseek_ISP_SetEnhancementLevel(UINT32 Level);
WPMAINCORE_API int Roseek_ISP_GetEnhancementLevel(UINT32 *pLevel);
WPMAINCORE_API int Roseek_ISP_SetEnhancementPreSetParams(UINT32 CMin, UINT32 CMax, float Sig);
WPMAINCORE_API int Roseek_ISP_GetEnhancementPreSetParams(UINT32 *pCMin, UINT32 *pCMax, float *pSig);
typedef struct _ScaleFactor
{
	float			Window;
	float			PowerCoff;
	INT32			Flag;
}ScaleFactor;
typedef struct _MSRParams 
{
	ScaleFactor		SW;
	ScaleFactor		MW;
	ScaleFactor		LW;
	float			Scale;
}MSRParams;
WPMAINCORE_API int Roseek_ISP_InitMSRParams(MSRParams *pParams, float SCoff, float MCoff, float LCoff);
WPMAINCORE_API int Roseek_ISP_InitMSRParamsForDefog(MSRParams *pParams, float SCoff, float MCoff, float LCoff);
WPMAINCORE_API int Roseek_ISP_SetMultiScaleRetinexParams(MSRParams Params);
WPMAINCORE_API int Roseek_ISP_GetMultiScaleRetinexParams(MSRParams *pParams);
WPMAINCORE_API int Roseek_ISP_SetMSRRefPoint(float *pVal, int Num);
WPMAINCORE_API int Roseek_ISP_SetColorSaturation(float Saturation);
WPMAINCORE_API int Roseek_ISP_GetColorSaturation(float *pSaturation);
WPMAINCORE_API int Roseek_ISP_SetBrightness(int Brightness);
WPMAINCORE_API int Roseek_ISP_GetBrightness(int *pBrightness);
WPMAINCORE_API int Roseek_ISP_SetGamma(float Gamma);
WPMAINCORE_API int Roseek_ISP_GetGamma(float *pGamma);
WPMAINCORE_API int Roseek_ISP_SetGammaPreSetParams(UINT32 Mode, UINT32 ThX_L, UINT32 ThY_L, UINT32 ThX_R, UINT32 ThY_R);
WPMAINCORE_API int Roseek_ISP_GetGammaPreSetParams(UINT32 *pMode, UINT32 *pThX_L, UINT32 *pThY_L, UINT32 *pThX_R, UINT32 *pThY_R);
WPMAINCORE_API int Roseek_ISP_SetHDRMode(UINT32 Mode);
WPMAINCORE_API int Roseek_ISP_GetHDRMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_ISP_SetWhiteBalanceMode(UINT32 Mode, float r, float g, float b);
WPMAINCORE_API int Roseek_ISP_GetWhiteBalanceMode(UINT32 *pMode, float *pR, float *pG, float *pB);
WPMAINCORE_API int Roseek_ISP_SetWhiteBalanceRegion(UINT32 x, UINT32 y, UINT32 Width, UINT32 Height);
WPMAINCORE_API int Roseek_ISP_GetWhiteBalanceRegion(UINT32 *pX, UINT32 *pY, UINT32 *pWidth, UINT32 *pHeight);
WPMAINCORE_API int Roseek_ISP_SetWhiteBalanceAdjustGap(UINT32 Gap);
WPMAINCORE_API int Roseek_ISP_GetWhiteBalanceAdjustGap(UINT32 *pGap);
WPMAINCORE_API int Roseek_ISP_SetLUT(UINT32 id, UINT32 Mode, float Value, UINT8 *pTable, UINT32 TableSize);
WPMAINCORE_API int Roseek_ISP_GetLUT(UINT32 id, UINT32 *pMode, float *pValue, UINT8 *pTable, UINT32 TableSize);
WPMAINCORE_API int Roseek_ISP_ResetLUT(UINT32 id);
WPMAINCORE_API int Roseek_ISP_SetSelectedLUT(UINT32 id);
WPMAINCORE_API int Roseek_ISP_GetSelectedLUT(UINT32 *pID);
WPMAINCORE_API int Roseek_ISP_SetRawLUT(UINT8 *pTable, UINT32 TableSize);
enum _DenoiseMode
{
	DENOISE_MODE_CLOSE,
	DENOISE_MODE_AUTO,
	DENOISE_MODE_AUTO_EX,
	DENOISE_MODE_MANUAL,
	DENOISE_MODE_MANUAL_EX,
	DENOISE_MODE_AUTO_SELFADAPT,
	DENOISE_MODE_MAX
};
WPMAINCORE_API int Roseek_ISP_SetDenoiseModeS(UINT32 Mode, UINT32 Level);
WPMAINCORE_API int Roseek_ISP_GetDenoiseModeS(UINT32 *pMode, UINT32 *pLevel);
WPMAINCORE_API int Roseek_ISP_SetDenoiseModeSBOffset(UINT32 Offset);
WPMAINCORE_API int Roseek_ISP_SetDenoiseModeSPreSetParams(UINT32 Offset, float Gamma, UINT32 ThYMin, UINT32 ThYMax, UINT32 ExThYMin, UINT32 ExThYMax);
WPMAINCORE_API int Roseek_ISP_GetDenoiseModeSPreSetParams(UINT32 *pOffset, float *pGamma, UINT32 *pThYMin, UINT32 *pThYMax, UINT32 *pExThYMin, UINT32 *pExThYMax);
enum _VLineCorrectionMode
{
	VLINECORRECTION_MODE_CLOSE,
	VLINECORRECTION_MODE_BYSENSOR,
	VLINECORRECTION_MODE_BYFACTORY,
	VLINECORRECTION_MODE_MAX
};
WPMAINCORE_API int Roseek_ISP_SetVLineCorrectionMode(UINT32 Mode);
WPMAINCORE_API int Roseek_ISP_GetVLineCorrectionMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_ISP_SetBlackLevel(UINT32 Level);
WPMAINCORE_API int Roseek_ISP_GetBlackLevel(UINT32 *pLevel);

//WP IO
WPMAINCORE_API int Roseek_IO_SetOutputIOState(UINT32 id, UINT32 State);
WPMAINCORE_API int Roseek_IO_GetOutputIOState(UINT32 id, UINT32 *pState);
WPMAINCORE_API int Roseek_IO_GetInputIOState(UINT32 id, UINT32 *pState);
WPMAINCORE_API int Roseek_IO_SetInputIOInterruptMode(UINT32 Mode);
WPMAINCORE_API int Roseek_IO_GetInputIOInterruptMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_IO_SetTrigInMode(UINT32 Mode);
WPMAINCORE_API int Roseek_IO_GetTrigInMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_IO_SetTriggerDelay(UINT32 Delay);
WPMAINCORE_API int Roseek_IO_GetTriggerDelay(UINT32 *pDelay);
WPMAINCORE_API int Roseek_IO_SetOwnLEDDriverMode(UINT32 Mode);
WPMAINCORE_API int Roseek_IO_GetOwnLEDDriverMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_IO_SetOwnLEDDriverStrength(UINT32 Strength);
WPMAINCORE_API int Roseek_IO_GetOwnLEDDriverStrength(UINT32 *pStrength);
WPMAINCORE_API int Roseek_IO_SetExtLEDDriverMode(UINT32 Mode);
WPMAINCORE_API int Roseek_IO_GetExtLEDDriverMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_IO_SetExtLEDDriverStrength(UINT32 Strength);
WPMAINCORE_API int Roseek_IO_GetExtLEDDriverStrength(UINT32 *pStrength);
WPMAINCORE_API int Roseek_IO_SetStatusLED(UINT32 id, UINT32 Status);
WPMAINCORE_API int Roseek_IO_SetGlitchFilter(UINT32 id, UINT32 Filter);
WPMAINCORE_API int Roseek_IO_GetGlitchFilter(UINT32 id, UINT32* pFilter);
WPMAINCORE_API int Roseek_IO_SetFlashLampPulseWidth(UINT32 Width);
WPMAINCORE_API int Roseek_IO_GetFlashLampPulseWidth(UINT32 *pWidth);
WPMAINCORE_API int Roseek_IO_SetFlashLampFrequency(UINT32 Frequency);
WPMAINCORE_API int Roseek_IO_GetFlashLampFrequency(UINT32 *pFrequency);
WPMAINCORE_API int Roseek_IO_SetFlashLampInadvance(UINT32 Value);
WPMAINCORE_API int Roseek_IO_GetFlashLampInadvance(UINT32 *pValue);
typedef int (*FUNC_IOIntCB)(UINT32 IntSrc);
WPMAINCORE_API int Roseek_IO_RegisterIntCallBack(FUNC_IOIntCB Func);

//Network
enum
{
	WP_NETWORK_MODE_STATIC,
	WP_NETWORK_MODE_DHCP,
	WP_NETWORK_MODE_MAX
};
WPMAINCORE_API int Roseek_Network_ApplyCurSet();
WPMAINCORE_API int Roseek_Network_SetMode(UINT32 Mode);
WPMAINCORE_API int Roseek_Network_GetMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_Network_SetIP(UINT32 IP);
WPMAINCORE_API int Roseek_Network_GetIP(UINT32 *pIP);
WPMAINCORE_API int Roseek_Network_SetNetmask(UINT32 Netmask);
WPMAINCORE_API int Roseek_Network_GetNetmask(UINT32 *pNetmask);
WPMAINCORE_API int Roseek_Network_SetDefGateway(UINT32 Gateway);
WPMAINCORE_API int Roseek_Network_GetDefGateway(UINT32 *pGateway);
WPMAINCORE_API int Roseek_Network_SetDefDNS(UINT32 DNS);
WPMAINCORE_API int Roseek_Network_GetDefDNS(UINT32 *pDNS);
WPMAINCORE_API int Roseek_Network_SetMAC(UINT8 *pMAC, UINT32 Size);
WPMAINCORE_API int Roseek_Network_GetMAC(UINT8 *pMAC, UINT32 Size);

//UART

//Flash

//EEPROM
WPMAINCORE_API int Roseek_EEPROM_Write(UINT32 Offset, void *pBuff, UINT32 DataSize);
WPMAINCORE_API int Roseek_EEPROM_Read(UINT32 Offset, void *pBuff, UINT32 DataSize);

//RTC

//WatchDog
WPMAINCORE_API int Roseek_WatchDog_SetMode(UINT32 Mode);
WPMAINCORE_API int Roseek_WatchDog_GetMode(UINT32 *pMode);
WPMAINCORE_API int Roseek_WatchDog_SetTimer(UINT32 Time_sec);
WPMAINCORE_API int Roseek_WatchDog_GetTimer(UINT32 *pTime_sec);
WPMAINCORE_API int Roseek_WatchDog_Kick();

//System
enum
{
	WP_RESET_MODE_SOFT,
	WP_RESET_MODE_HARD,
	WP_RESET_MODE_MAX
};

#define WP_MAX_MODULES_NUM			30
#define WP_MAX_MODULE_INFO_SIZE		256

WPMAINCORE_API int Roseek_System_GetSerialPortName(UINT32 id, char *pNameBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_Reset(UINT32 Mode);
WPMAINCORE_API int Roseek_System_ResetPower();
WPMAINCORE_API int Roseek_System_Shutdown();
WPMAINCORE_API int Roseek_System_GetTemperature(float *pTemperature);
WPMAINCORE_API int Roseek_System_GetUniqueNums(UINT32 id, UINT8 *pNumsBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_GetDevModel(char *pModelBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_GetDevSN(char *pSNBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_RegisterModule(const char *pModuleInfo);
WPMAINCORE_API int Roseek_System_ReadDevInfo(char *pInfoBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_StoreRunParams();
WPMAINCORE_API int Roseek_System_RestoreRunParams();
WPMAINCORE_API int Roseek_System_SetUserAccount(const char *pUsername, const char *pPassword);
WPMAINCORE_API int Roseek_System_GetUserAccount(char *pUsername, UINT32 NameBuffSize, char *pPassword, UINT32 WordBuffSize);

//The following API functions have been discarded
WPMAINCORE_API int Roseek_System_GetHWMixVersion(char *pVerBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_GetFWMixVersion(char *pVerBuff, UINT32 BuffSize);
WPMAINCORE_API int Roseek_System_GetTemprature(float *pTemprature);

//The following API functions for internal use and is not recommended to users
WPMAINCORE_API int Roseek_Pcie_WriteReg32(UINT32 index, UINT32 addr, UINT32 value);
WPMAINCORE_API int Roseek_Pcie_ReadReg32(UINT32 index, UINT32 addr, UINT32 *pValue);
WPMAINCORE_API int Roseek_Pcie_WriteAfeReg32(UINT32 index, UINT32 addr, UINT32 value);
WPMAINCORE_API int Roseek_Pcie_ReadAfeReg32(UINT32 index, UINT32 addr, UINT32 *pValue);

WPMAINCORE_API int Roseek_Test_SetTrginCntCfg(UINT32 IsStart, UINT32 IsClear);
WPMAINCORE_API int Roseek_Test_GetTrginCnt(UINT32 *pCntValue);

WPMAINCORE_API int Roseek_Capture_Grab();
WPMAINCORE_API int Roseek_System_Private(void *pIn, UINT32 InSize, void *pOut, UINT32 *pInOutSize);
WPMAINCORE_API int Roseek_System_UpdateFPGA(const char *pFilePath, UINT32 *pProgress);
WPMAINCORE_API int Roseek_System_UpdateMCU(const char *pFilePath, UINT32 *pProgress);
WPMAINCORE_API int Roseek_System_UpdateExtMCU(const char *pFilePath, UINT32 *pProgress);

WPMAINCORE_API int Roseek_ISP_SetEnhancementLevelEx(UINT32 Threshold, float Level);
WPMAINCORE_API int Roseek_ISP_SetMatrix(UINT32 UseTo, float *pMat, UINT32 Size);
WPMAINCORE_API int Roseek_ISP_GetMatrix(UINT32 UseTo, float *pMat, UINT32 *pSize);
WPMAINCORE_API int Roseek_ISP_SetColorCut(UINT32 Threshold);
WPMAINCORE_API int Roseek_ISP_GetColorCut(UINT32 *pThreshold);
WPMAINCORE_API int Roseek_ISP_SetBadColorSuppressionMode(UINT32 Mode, UINT32 Level);
WPMAINCORE_API int Roseek_ISP_GetBadColorSuppressionMode(UINT32 *pMode, UINT32 *pLevel);
WPMAINCORE_API int Roseek_ISP_SetDenoiseMode(UINT32 Threshold, float Level);
WPMAINCORE_API int Roseek_ISP_GetDenoiseMode(UINT32 *pThreshold, float *pLevel);
WPMAINCORE_API int Roseek_ISP_SetDenoiseModeEx(UINT32 Mode, UINT32 ThX, UINT32 ThY);
WPMAINCORE_API int Roseek_ISP_GetDenoiseModeEx(UINT32 *pMode, UINT32 *pThX, UINT32 *pThY);

#ifdef __cplusplus
};
#endif

#endif
