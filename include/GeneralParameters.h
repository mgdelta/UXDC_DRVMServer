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

        const double GetGain();
        const double GetGainLowerLimit();
        const double GetGainUpperLimit();
        const double GetGamma();
        const double GetExposureTime();
        const double GetExposureLowerLimit();
        const double GetExposureUpperLimit();
        const double GetFPSLimit();
        const double GetFPSActual();
        const double GetBrightness();
        const double GetContrast();
        const double GetBalanceRatio();

        const int GetSensorWidth();
        const int GetSensorHeight();
        const int GetSensorROIWidthMax();
        const int GetSensorROIHeightMax();
        const int GetROIWidth();
        const int GetROIHeight();
        const int GetROIOffsetX();
        const int GetROIOffsetY();
        const int GetLinkspeed();
        const int GetSpeedlimit();

        void SetGainAutoMode(const std::string& strValue);
        void SetPixelFormat(const std::string& strValue);
        void SetExposureAuto(const std::string& strValue);
        void SetExposureMode(const std::string& strValue);
        void SetLightPreset(const std::string& strValue);
        void SetUSBSpeedMode(const std::string& strValue);
        void SetReverseX(const bool& bValue);
        void SetReverseY(const bool& bValue);

        void SetGain(const double& dValue);
        void SetGainLowerLimit(const double& dValue);
        void SetGainUpperLimit(const double& dValue);
        void SetGamma(const double& dValue);
        void SetExposureTime(const double& dValue);
        void SetExposureLowerLimit(const double& dValue);
        void SetExposureUpperLimit(const double& dValue);
        void SetFPSLimit(const double& dValue);
        void SetFPSActual(const double& dValue);
        void SetBrightness(const double& dValue);
        void SetContrast(const double& dValue);
        void SetBalanceRatio(const double& dValue);

        void SetSensorWidth(const int& iValue);
        void SetSensorHeight(const int& iValue);
        void SetSensorROIWidthMax(const int& iValue);
        void SetSensorROIHeightMax(const int& iValue);
        void SetROIWidth(const int& iValue);
        void SetROIHeight(const int& iValue);
        void SetROIOffsetX(const int& iValue);
        void SetROIOffsetY(const int& iValue);
        void SetLinkspeed(const int& iValue);
        void SetSpeedlimit(const int& iValue);
};


#endif
