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