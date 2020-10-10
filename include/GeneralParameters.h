#ifndef GENERALPARAMETERS_H
#define GENERALPARAMETERS_H

#include <string>
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
        const bool GetReverseX();
        const bool GetReverseY();


        void SetGainAutoMode(const std::string& strValue);
        void SetPixelFormat(const std::string& strValue);
        void SetExposureAuto(const std::string& strValue);
        void SetExposureMode(const std::string& strValue);
        void SetLightPreset(const std::string& strValue);
        void SetUSBSpeedMode(const std::string& strValue);
        void SetReverseX(const bool& bValue);
        void SetReverseY(const bool& bValue);



};


#endif
