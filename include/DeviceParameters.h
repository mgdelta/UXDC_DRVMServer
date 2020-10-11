#ifndef DEVICEPARAMETERS_H
#define DEVICEPARAMETERS_H

#include <string>

class CamDeviceParameters
{
    private:
        std::string strModelName;
        std::string strSerialNumber;
        std::string strDeviceFactory;
        std::string strFriendlyName;
        std::string strFullName;
        std::string strVendorName;
        std::string strDeviceGUID;

    public:
        const std::string GetModelName();
        const std::string GetSerialNumber();
        const std::string GetDeviceFactory();
        const std::string GetFriendlyName();
        const std::string GetFullName();
        const std::string GetVendorName();
        const std::string GetDeviceGUID();
        void SetModelName(const std::string& strValue);
        void SetSerialNumber(const std::string& strValue);
        void SetDeviceFactory(const std::string& strValue);
        void SetFriendlyName(const std::string& strValue);
        void SetFullName(const std::string& strValue);
        void SetVendorName(const std::string& strValue);
        void SetDeviceGUID(const std::string& strValue);
};

#endif