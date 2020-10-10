#ifndef CAMERAPARAMETERS_H
#define CAMERAPARAMETERS_H

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
class CamGeneralParameters
{
    private:
        double dGain_db;
        double dGain_LowerLimit;
        double dGain_UpperLimit;
        double dGamma;
        int iSensor_Width;
        int iSensor_Height;
        int iSensor_ROI_WidthMax;
        int iSensor_ROI_HeightMax;
        int iROI_Width;
        int iROI_Height;
        int iROI_OffsetX;
        int iROI_OffsetY;
        bool bReverse_X;
        bool bReverse_Y;
        double dExposure_us;
        double dExposure_LowerLimit;
        double dExposure_UpperLimit;
        double dFPS_Limit;
        double dFPS_Actual;
        double dBrightness;
        double dContrast;
        double dBalanceratio;
        int iLinkspeed_bps;
        int iSpeedlimit_Bps;
        std::string strGainAuto;
        std::string strPixelFormat;
        std::string strExposureAuto;
        std::string strExposureMode;
        std::string strLightPreset;
        std::string strUsbSpeed;

    public:
        const std::string GetGainAutoMode();
        const std::string GetPixelFormat();
        const std::string GetExposureAuto();
        const std::string GetExposureMode();
        const std::string GetLightPreset();
        const std::string GetUSBSpeedMode();


        void SetGainAutoMode(const std::string& strValue);
        void SetPixelFormat(const std::string& strValue);
        void SetExposureAuto(const std::string& strValue);
        void SetExposureMode(const std::string& strValue);
        void SetLightPreset(const std::string& strValue);
        void SetUSBSpeedMode(const std::string& strValue);





};
class CamImageParameters
{
    private:

    public:

};
#endif