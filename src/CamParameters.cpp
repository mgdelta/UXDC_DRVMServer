#include "CamParameters.h"
#include <iostream>

void CamDeviceParameter::SetModelName(const std::string& strValue)
{
    strModelName = strValue;
}
void CamDeviceParameter::SetSerialNumber(const std::string& strValue)
{
    strSerialNumber = strValue;
}
void CamDeviceParameter::SetDeviceFactory(const std::string& strValue)
{
    strDeviceFactory = strValue;
}
void CamDeviceParameter::SetFriendlyName(const std::string& strValue)
{
    strFriendlyName = strValue;
}
void CamDeviceParameter::SetFullName(const std::string& strValue)
{
    strFullName = strValue;
}
void CamDeviceParameter::SetVendorName(const std::string& strValue)
{
    strVendorName = strValue;
}
void CamDeviceParameter::SetDeviceGUID(const std::string& strValue)
{
    strDeviceGUID = strValue;
}

const std::string CamDeviceParameter::GetModelName()
{
    return strModelName;
}
const std::string CamDeviceParameter::GetSerialNumber()
{
    return strSerialNumber;
}
const std::string CamDeviceParameter::GetDeviceFactory()
{
    return strDeviceFactory;
}
const std::string CamDeviceParameter::GetFriendlyName()
{
    return strFriendlyName;
}
const std::string CamDeviceParameter::GetFullName()
{
    return strFullName;
}
const std::string CamDeviceParameter::GetVendorName()
{
    return strVendorName;
}
const std::string CamDeviceParameter::GetDeviceGUID()
{
    return strDeviceGUID;
}