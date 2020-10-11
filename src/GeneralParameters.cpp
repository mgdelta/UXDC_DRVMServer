#include "GeneralParameters.h"

/* General Parameters */
void CamGeneralParameters::SetGainAutoMode(const std::string& strValue)
{
    strGainAuto = strValue;
}
void CamGeneralParameters::SetPixelFormat(const std::string& strValue)
{
    strPixelFormat = strValue;
}
void CamGeneralParameters::SetExposureAuto(const std::string& strValue)
{
    strExposureAuto = strValue;
}
void CamGeneralParameters::SetExposureMode(const std::string& strValue)
{
    strExposureMode = strValue;
}
void CamGeneralParameters::SetLightPreset(const std::string& strValue)
{
    strLightPreset = strValue;
}
void CamGeneralParameters::SetUSBSpeedMode(const std::string& strValue)
{
    strUsbSpeed = strValue;
}

void CamGeneralParameters::SetReverseX(const bool& bValue)
{
    bReverse_X = bValue;
}
void CamGeneralParameters::SetReverseY(const bool& bValue)
{
    bReverse_Y = bValue;
}

void CamGeneralParameters::SetGain(const double& dValue)
{
    dGain_db = dValue;
}
void CamGeneralParameters::SetGainLowerLimit(const double& dValue)
{
    dGain_LowerLimit = dValue;
}
void CamGeneralParameters::SetGainUpperLimit(const double& dValue)
{
    dGain_UpperLimit = dValue;
}
void CamGeneralParameters::SetGamma(const double& dValue)
{
    dGamma = dValue;
}
void CamGeneralParameters::SetExposureTime(const double& dValue)
{
    dExposure_us = dValue;
}
void CamGeneralParameters::SetExposureLowerLimit(const double& dValue)
{
    dExposure_LowerLimit = dValue;
}
void CamGeneralParameters::SetExposureUpperLimit(const double& dValue)
{
    dExposure_UpperLimit = dValue;
}
void CamGeneralParameters::SetFPSLimit(const double& dValue)
{
    dFPS_Limit = dValue;
}
void CamGeneralParameters::SetFPSActual(const double& dValue)
{
    dFPS_Actual = dValue;
}
void CamGeneralParameters::SetBrightness(const double& dValue)
{
    dBrightness = dValue;
}
void CamGeneralParameters::SetContrast(const double& dValue)
{
    dContrast = dValue;
}
void CamGeneralParameters::SetBalanceRatio(const double& dValue)
{
    dBalanceratio = dValue;
}

void CamGeneralParameters::SetSensorWidth(const int& iValue)
{
    iSensor_Width = iValue;
}
void CamGeneralParameters::SetSensorHeight(const int& iValue)
{
    iSensor_Height = iValue;
}
void CamGeneralParameters::SetSensorROIWidthMax(const int& iValue)
{
    iSensor_ROI_WidthMax = iValue;
}
void CamGeneralParameters::SetSensorROIHeightMax(const int& iValue)
{
    iSensor_ROI_HeightMax = iValue;
}
void CamGeneralParameters::SetROIWidth(const int& iValue)
{
    iROI_Width = iValue;
}
void CamGeneralParameters::SetROIHeight(const int& iValue)
{
    iROI_Height = iValue;
}
void CamGeneralParameters::SetROIOffsetX(const int& iValue)
{
    iROI_OffsetX = iValue;
}
void CamGeneralParameters::SetROIOffsetY(const int& iValue)
{
    iROI_OffsetY = iValue;
}
void CamGeneralParameters::SetLinkspeed(const int& iValue)
{
    iLinkspeed_bps = iValue;
}
void CamGeneralParameters::SetSpeedlimit(const int& iValue)
{
    iSpeedlimit_Bps = iValue;
}

/* Getter */
const std::string CamGeneralParameters::GetGainAutoMode()
{
    return strGainAuto;
}
const std::string CamGeneralParameters::GetPixelFormat()
{
    return strPixelFormat;
}
const std::string CamGeneralParameters::GetExposureAuto()
{
    return strExposureAuto;
}
const std::string CamGeneralParameters::GetExposureMode()
{
    return strExposureMode;
}
const std::string CamGeneralParameters::GetLightPreset()
{
    return strLightPreset;
}
const std::string CamGeneralParameters::GetUSBSpeedMode()
{
    return strUsbSpeed;
}

const bool CamGeneralParameters::GetReverseX()
{
    return bReverse_X;
}
const bool CamGeneralParameters::GetReverseY()
{
    return bReverse_Y;
}

const double CamGeneralParameters::GetGain()
{
    return dGain_db;
}
const double CamGeneralParameters::GetGainLowerLimit()
{
    return dGain_LowerLimit;
}
const double CamGeneralParameters::GetGainUpperLimit()
{
    return dGain_UpperLimit;
}
const double CamGeneralParameters::GetGamma()
{
    return dGamma;
}
const double CamGeneralParameters::GetExposureTime()
{
    return dExposure_us;
}
const double CamGeneralParameters::GetExposureLowerLimit()
{
    return dExposure_LowerLimit;
}
const double CamGeneralParameters::GetExposureUpperLimit()
{
    return dExposure_UpperLimit;
}
const double CamGeneralParameters::GetFPSLimit()
{
    return dFPS_Limit;
}
const double CamGeneralParameters::GetFPSActual()
{
    return dFPS_Actual;
}
const double CamGeneralParameters::GetBrightness()
{
    return dBrightness;
}
const double CamGeneralParameters::GetContrast()
{
    return dContrast;
}
const double CamGeneralParameters::GetBalanceRatio()
{
    return dBalanceratio;
}

const int CamGeneralParameters::GetSensorWidth()
{
    return iSensor_Width;
}
const int CamGeneralParameters::GetSensorHeight()
{
    return iSensor_Height;
}
const int CamGeneralParameters::GetSensorROIWidthMax()
{
    return iSensor_ROI_WidthMax;
}
const int CamGeneralParameters::GetSensorROIHeightMax()
{
    return iSensor_ROI_HeightMax;
}
const int CamGeneralParameters::GetROIWidth()
{
    return iROI_Width;
}
const int CamGeneralParameters::GetROIHeight()
{
    return iROI_Height;
}
const int CamGeneralParameters::GetROIOffsetX()
{
    return iROI_OffsetX;
}
const int CamGeneralParameters::GetROIOffsetY()
{
    return iROI_OffsetY;
}
const int CamGeneralParameters::GetLinkspeed()
{
    return iLinkspeed_bps;
}
const int CamGeneralParameters::GetSpeedlimit()
{
    return iSpeedlimit_Bps;
}