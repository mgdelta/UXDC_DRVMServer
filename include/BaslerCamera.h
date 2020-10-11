#ifndef BASLERCAMERA
#define BASLERCAMERA

#include "DeviceParameters.h"
#include "GeneralParameters.h"
#include <pylon/PylonIncludes.h>


class BaslerCamera
{
    private:
        Pylon::CInstantCamera *camera;
        GenApi::INodeMap *nodemap;

        const int max_framerate = 30;
        CamDeviceParameters cCamParams;
        CamGeneralParameters cCamGenParams;
        

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
        void UpdateDeviceParameters(bool bUpdateAll = false);




    struct ImageParameter{
        int gain;
        int exposuretime;
        float framerate;
        int brightness;
        int contrast;
    };
};

#endif