#include "CamParameters.h"
#include <iostream>

void CamDeviceParameters::SetModelName(const std::string& strValue)
{
    strModelName = strValue;
}
void CamDeviceParameters::SetSerialNumber(const std::string& strValue)
{
    strSerialNumber = strValue;
}
void CamDeviceParameters::SetDeviceFactory(const std::string& strValue)
{
    strDeviceFactory = strValue;
}
void CamDeviceParameters::SetFriendlyName(const std::string& strValue)
{
    strFriendlyName = strValue;
}
void CamDeviceParameters::SetFullName(const std::string& strValue)
{
    strFullName = strValue;
}
void CamDeviceParameters::SetVendorName(const std::string& strValue)
{
    strVendorName = strValue;
}
void CamDeviceParameters::SetDeviceGUID(const std::string& strValue)
{
    strDeviceGUID = strValue;
}

const std::string CamDeviceParameters::GetModelName()
{
    return strModelName;
}
const std::string CamDeviceParameters::GetSerialNumber()
{
    return strSerialNumber;
}
const std::string CamDeviceParameters::GetDeviceFactory()
{
    return strDeviceFactory;
}
const std::string CamDeviceParameters::GetFriendlyName()
{
    return strFriendlyName;
}
const std::string CamDeviceParameters::GetFullName()
{
    return strFullName;
}
const std::string CamDeviceParameters::GetVendorName()
{
    return strVendorName;
}
const std::string CamDeviceParameters::GetDeviceGUID()
{
    return strDeviceGUID;
}

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