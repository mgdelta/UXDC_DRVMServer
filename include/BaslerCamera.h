#ifndef BASLERCAMERA
#define BASLERCAMERA

#include "CamParameters.h"
#include <pylon/PylonIncludes.h>


class BaslerCamera
{
    private:
        //const char Filename[] = "CamDefaultNodeMap.pfs";
        Pylon::CInstantCamera *camera;
        GenApi::INodeMap *nodemap;

        const int max_framerate = 30;
        CamParameter_Device cCamParams;

    public:
        BaslerCamera();
                ~BaslerCamera();

        void OpenFirstCamera();
        void SaveCamParametersToFile(std::string filename);
        void SetMandatoryDefaultParameters();
        void LoadCamParametersFromFile(std::string filename);
        void StartGrabbing();
        bool CamIsGrabbing();
        void GetGrabbedImage(Pylon::CGrabResultPtr &ptrImagePointer);

    struct CamDeviceInfo{
        std::string strModelName;
        std::string strSerialNumber;
        std::string strDeviceFactory;
        std::string strFriendlyName;
        std::string strFullName;
        std::string strVendorName;
        std::string strDeviceGUID;
    };

    struct CamSensorParameter{
        int width;
        int height;
        int offsetx;
        int offsety;
        bool reversex;
        bool reversey;
        int pixelformat;
        std::string strShutterMode;
        int autoexposurelowerlimit;
        int autoexposureupperlimit;
        std::string strExposureMode;
        std::string strLightPreset;

        //Width	1600
        //Height	1200
        //OffsetX	0
        //OffsetY	0
        //ReverseX	0
        //ReverseY	0
        //PixelFormat	BayerRG12
        //SensorShutterMode	Global
        //AutoExposureTimeLowerLimitRaw	100
        //AutoExposureTimeUpperLimitRaw	100000
        //ExposureMode	Timed
        //LightSourcePreset	Daylight5000K
        // Aktuelle Infos:
        // Gain(DB)
        // Exposure Time us
        // ResultingFrameRate
        // Brightness
        // Contrast
    };

    struct ImageParameter{
        int gain;
        int exposuretime;
        float framerate;
        int brightness;
        int contrast;
    };
};

#endif