#ifndef BASLERCAMERA
#define BASLERCAMERA

#include <pylon/PylonIncludes.h>


class BaslerCamera
{
    private:
        //const char Filename[] = "CamDefaultNodeMap.pfs";
        Pylon::CInstantCamera *camera;
        GenApi::INodeMap *nodemap;

        const int max_framerate = 30;


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

};



#endif