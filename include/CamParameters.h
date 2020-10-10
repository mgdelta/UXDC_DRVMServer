#ifndef CAMERAPARAMETERS_H
#define CAMERAPARAMETERS_H

#include <string>

class CamParameter_Device
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
        std::string GetModelName();
        std::string GetSerialNumber();
        std::string GetDeviceFactory();
        std::string GetFriendlyName();
        std::string GetFullName();
        std::string GetVendorName();
        std::string GetDeviceGUID();
        void SetModelName(std::string strValue);
        void SetSerialNumber(std::string strValue);
        void SetDeviceFactory(std::string strValue);
        void SetFriendlyName(std::string strValue);
        void SetFullName(std::string strValue);
        void SetVendorName(std::string strValue);
        void SetDeviceGUID(std::string strValue);
};
#endif